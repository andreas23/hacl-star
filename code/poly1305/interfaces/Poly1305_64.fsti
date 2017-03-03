module Poly1305_64

open FStar.Mul
open FStar.ST
open FStar.Ghost
open FStar.Seq
open FStar.HyperStack
open FStar.Endianness
open FStar.Buffer


module U32  = FStar.UInt32
module U64  = FStar.UInt64


open Hacl.Spec.Bignum.AddAndMultiply
open Hacl.Impl.Poly1305_64


(* Type Aliases *)
type uint8_p = Buffer.buffer Hacl.UInt8.t
type key = k:uint8_p{length k = 32}

type state = poly1305_state
type live_state (h:mem) (st:state)
type stable (h:mem) (st:state)

(* val get_key: st:state -> Tot (b:Buffer.buffer Hacl.UInt32.t{length b = 3}) *)
(* val get_accumulator: st:state -> Tot (b:Buffer.buffer Hacl.UInt32.t{length b = 3}) *)
let get_key (st:state) = st.r
let get_accumulator (st:state) = st.h

#reset-options "--initial_fuel 0 --max_fuel 0 --z3rlimit 10"

val alloc:
  unit -> StackInline poly1305_state
    (requires (fun h -> True))
    (ensures (fun h0 st h1 -> modifies_0 h0 h1 /\ live_st h1 st /\ frameOf st.h == h0.tip
      /\ frameOf st.r = h0.tip /\ ~(contains h0 st.r) /\ ~(contains h0 st.h)))

val mk_state:
  r:buffer Hacl.UInt64.t{length r = 3} -> acc:buffer Hacl.UInt64.t{length acc = 3 /\ disjoint r acc} ->
  Stack state
    (requires (fun h -> live h r /\ live h acc))
    (ensures (fun h0 st h1 -> h0 == h1 /\ MkState?.r st == r /\ MkState?.h st == acc /\ live_st h1 st))


val init:
  st:state ->
  k:uint8_p{length k >= 16} ->
  Stack unit
    (requires (fun h -> live h k /\ live_state h st))
    (ensures (fun h0 _ h1 -> modifies_2 (get_key st) (get_accumulator st) h0 h1 /\ stable h1 st))


val update_block:
  st:state ->
  m:uint8_p{length m = 16} ->
  Stack unit
    (requires (fun h -> stable h st /\ live h m))
    (ensures  (fun h0 updated_log h1 -> modifies_1 (get_accumulator st) h0 h1 /\ stable h1 st))


#reset-options "--initial_fuel 0 --max_fuel 0 --z3rlimit 100"

val update:
  st:state ->
  m:uint8_p ->
  len:FStar.UInt32.t{length m >= 16 * UInt32.v len} ->
  Stack unit
    (requires (fun h -> stable h st /\ live h m))
    (ensures  (fun h0 updated_log h1 -> modifies_1 (get_accumulator st) h0 h1 /\ stable h1 st))

  
#reset-options "--initial_fuel 0 --max_fuel 0 --z3rlimit 10"

type before_finish (h:mem) (st:state)


#reset-options "--initial_fuel 0 --max_fuel 0 --z3rlimit 100"

val update_last:
  st:state ->
  m:uint8_p ->
  len:UInt32.t{UInt32.v len < 16 /\ UInt32.v len <= length m} ->
  Stack unit
    (requires (fun h -> stable h st /\ live h m))
    (ensures  (fun h0 _ h1 -> modifies_1 (get_accumulator st) h0 h1 /\ before_finish h1 st))


val finish:
  st:state ->
  mac:uint8_p{length mac = 16} ->
  k:uint8_p{length k = 16} ->
  Stack unit
    (requires (fun h -> before_finish h st /\ live h mac /\ live h k))
    (ensures (fun h0 _ h1 -> modifies_1 mac h0 h1))


val crypto_onetimeauth:
  output:uint8_p{length output = 16} ->
  input:uint8_p{disjoint input output} ->
  len:U64.t{U64.v len < pow2 32 /\ U64.v len = length input} ->
  k:uint8_p{disjoint output k /\ length k = 32} ->
  Stack unit
    (requires (fun h -> live h output /\ live h input /\ live h k))
    (ensures  (fun h0 _ h1 -> live h1 output /\ modifies_1 output h0 h1 /\ live h0 input /\ live h0 k
      /\ (let mac     = Hacl.Spec.Endianness.reveal_sbytes (as_seq h1 output) in
         let message = Hacl.Spec.Endianness.reveal_sbytes (as_seq h0 input) in
         let key     = Hacl.Spec.Endianness.reveal_sbytes (as_seq h0 k) in
         mac == Spec.Poly1305.poly1305 message key)))


open Spec.Chacha20Poly1305
open Hacl.Spec.Endianness
open Hacl.Spec.Poly1305_64


module I = Hacl.Impl.Poly1305_64

val poly1305_blocks_init:
  st:state ->
  input:uint8_p{disjoint I.(st.r) input /\ disjoint I.(st.h) input} ->
  len:U32.t{U32.v len = length input} ->
  k:uint8_p{length k = 32 /\ disjoint k I.(st.r) /\ disjoint k I.(st.h)} ->
  Stack I.log_t
    (requires (fun h -> I.live_st h st /\ live h input /\ live h k))
    (ensures (fun h0 log h1 -> I.live_st h1 st /\ live h0 input /\ live h0 k
      /\ modifies_2 I.(st.r) I.(st.h) h0 h1
      /\ (let r   = as_seq h1 I.(st.r) in
         let acc = as_seq h1 I.(st.h) in
         let log = reveal log in
         let m   = reveal_sbytes (as_seq h0 input) in
         let kr  = reveal_sbytes (as_seq h0 (Buffer.sub k 0ul 16ul)) in
         Hacl.Spe.Poly1305_64.invariant (MkState r acc log)
         /\ Hacl.Spec.Poly1305_64.seval r = Spec.Poly1305.encode_r kr
         /\ log == Spec.Poly1305.encode_bytes (pad_16 m))
    ))


val poly1305_blocks_continue:
  log:I.log_t ->
  st:I.poly1305_state ->
  input:uint8_p{disjoint I.(st.h) input} ->
  len:U32.t{U32.v len = length input} ->
  Stack I.log_t
    (requires (fun h -> I.live_st h st /\ live h input
      /\ (let r = as_seq h I.(st.r) in
         let acc = as_seq h I.(st.h) in
         let log = reveal log in
         Hacl.Spe.Poly1305_64.invariant (Hacl.Spec.Poly1305_64.MkState r acc log))
    ))
    (ensures (fun h0 log' h1 -> I.live_st h0 st /\ I.live_st h1 st /\ live h0 input
      /\ modifies_1 I.(st.h) h0 h1
      /\ (let r = as_seq h0 I.(st.r) in
         let acc = as_seq h0 I.(st.h) in
         let log = reveal log in
         let acc' = as_seq h1 I.(st.h) in
         let log' = reveal log' in
         let m    = reveal_sbytes (as_seq h0 input) in
         Hacl.Spe.Poly1305_64.invariant (Hacl.Spec.Poly1305_64.MkState r acc log)
         /\ Hacl.Spe.Poly1305_64.invariant (Hacl.Spec.Poly1305_64.MkState r acc' log')
         /\ log' == Seq.append (Spec.Poly1305.encode_bytes (pad_16 m)) log)
    ))


val poly1305_blocks_finish:
  log:I.log_t ->
  st:I.poly1305_state ->
  input:uint8_p{disjoint I.(st.h) input /\ length input = 16} ->
  mac:uint8_p{disjoint I.(st.h) mac /\ disjoint mac input /\ length mac = 16} ->
  key_s:uint8_p{disjoint key_s I.(st.h) /\ disjoint key_s mac /\ length key_s = 16} ->
  Stack unit
    (requires (fun h -> I.live_st h st /\ live h input /\ live h mac /\ live h key_s
      /\ (let r = as_seq h I.(st.r) in
         let acc = as_seq h I.(st.h) in
         let log = reveal log in
         Hacl.Spe.Poly1305_64.invariant (Hacl.Spec.Poly1305_64.MkState r acc log))
    ))
    (ensures (fun h0 _ h1 -> I.live_st h0 st /\ live h0 key_s /\ live h0 input
      /\ modifies_2 mac I.(st.h) h0 h1 /\ live h1 mac
      /\ (let mac = as_seq h1 mac in
         let r   = (as_seq h0 I.(st.r)) in
         let acc = as_seq h0 I.(st.h) in
         let log = reveal log in
         let m   = reveal_sbytes (as_seq h0 input) in
         let k   = Hacl.Spec.Endianness.hlittle_endian (as_seq h0 key_s) in
         Hacl.Spe.Poly1305_64.invariant (Hacl.Spec.Poly1305_64.MkState r acc log)
         /\ Hacl.Spec.Endianness.hlittle_endian mac
           == (Spec.Poly1305.poly (Seq.cons m log) (seval r) + k) % pow2 128)
    ))