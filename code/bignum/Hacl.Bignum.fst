module Hacl.Bignum

open FStar.Mul
open FStar.HyperStack
open FStar.Buffer

open Hacl.Bignum.Constants
open Hacl.Bignum.Parameters
open Hacl.Bignum.Limb
open Hacl.Spec.Bignum.Bigint
open Hacl.Spec.Bignum.Modulo
open Hacl.Spec.Bignum.Fproduct
open Hacl.Spec.Bignum.Fsquare
open Hacl.Spec.Bignum.Fmul
open Hacl.Spec.Bignum.Crecip
open Hacl.Spec.Bignum
open Hacl.Bignum.Modulo
open Hacl.Bignum.Fscalar
open Hacl.Bignum.Fsum
open Hacl.Bignum.Fdifference
open Hacl.Bignum.Fproduct
open Hacl.Bignum.Fmul
open Hacl.Bignum.Fsquare
open Hacl.Bignum.Crecip


module U32 = FStar.UInt32
module F   = Hacl.Spec.Bignum.Field


#set-options "--initial_fuel 0 --max_fuel 0"

[@"c_inline"]
val fsum:
  a:felem ->
  b:felem{disjoint a b} ->
  Stack unit
    (requires (fun h -> live h a /\ live h b
      /\ red_c h a len /\ red_c h b len))
    (ensures (fun h0 _ h1 -> live h0 a /\ live h0 b /\ red_c h0 a len /\ red_c h0 b len
      /\ live h1 a /\ modifies_1 a h0 h1
      /\ eval h1 a = eval h0 a + eval h0 b
      /\ as_seq h1 a == fsum_tot (as_seq h0 a) (as_seq h0 b)))
[@"c_inline"]
let fsum a b =
  let h0 = ST.get() in
  fsum_ a b clen;
  let h1 = ST.get() in
  Hacl.Spec.Bignum.Fsum.lemma_fsum_eval (as_seq h0 a) (as_seq h0 b)


assume val lemma_diff: a:int -> b:int -> p:pos ->
  Lemma ( (a - b) % p = ((a%p) - b) % p /\ (a - b) % p = (a - (b % p)) % p)


#set-options "--z3rlimit 20"

[@"c_inline"]
val fdifference:
  a:felem ->
  b:felem{disjoint a b} ->
  Stack unit
    (requires (fun h -> live h a /\ live h b /\ add_zero_pre (as_seq h b)
      /\ Hacl.Spec.Bignum.Fdifference.gte_limbs (as_seq h a) (add_zero_spec (as_seq h b)) len))
    (ensures (fun h0 _ h1 -> live h0 a /\ live h0 b
      /\ live h1 a /\ modifies_1 a h0 h1
      /\ add_zero_pre (as_seq h0 b)
      /\ Hacl.Spec.Bignum.Fdifference.gte_limbs (as_seq h0 a) (add_zero_spec (as_seq h0 b)) len
      /\ eval h1 a % prime = (eval h0 b - eval h0 a) % prime
      /\ as_seq h1 a == fdifference_tot (as_seq h0 a) (as_seq h0 b)
      ))
[@"c_inline"]
let fdifference a b =
  let hinit = ST.get() in
  push_frame();
  let tmp = create limb_zero clen in
  blit b 0ul tmp 0ul clen;
  let h = ST.get() in
  Hacl.Spec.Bignum.Fmul.lemma_whole_slice (as_seq h b);
  Hacl.Spec.Bignum.Fmul.lemma_whole_slice (as_seq h tmp);
  FStar.Seq.lemma_eq_intro (as_seq h b) (as_seq h tmp);
  add_zero tmp;
  let h' = ST.get() in
  cut (eval h' tmp % prime = eval hinit b % prime);
  fdifference_ a tmp clen;
  let h1 = ST.get() in
  Hacl.Spec.Bignum.Fdifference.lemma_fdifference_eval (as_seq hinit a) (as_seq h' tmp);
  lemma_diff (eval h' tmp) (eval hinit a) prime;
  lemma_diff (eval hinit b) (eval hinit a) prime;
  pop_frame()


open Hacl.Spec.Bignum.Fscalar
open Hacl.Spec.Bignum.Fproduct


[@"c_inline"]
val fscalar:
  a:felem ->
  b:felem{disjoint a b} ->
  s:limb ->
  Stack unit
    (requires (fun h -> live h b /\ live h a
      /\ carry_wide_pre (fscalar_spec (as_seq h b) s) 0
      /\ carry_top_wide_pre (carry_wide_spec (fscalar_spec (as_seq h b) s) 0)
      /\ copy_from_wide_pre (carry_top_wide_spec (carry_wide_spec (fscalar_spec (as_seq h b) s) 0)) ))
    (ensures (fun h0 _ h1 -> live h0 a /\ live h0 b /\ modifies_1 a h0 h1 /\ live h1 a
      /\ eval h1 a % prime = (eval h0 b * v s) % prime
      /\ carry_wide_pre (fscalar_spec (as_seq h0 b) s) 0
      /\ carry_top_wide_pre (carry_wide_spec (fscalar_spec (as_seq h0 b) s) 0)
      /\ copy_from_wide_pre (carry_top_wide_spec (carry_wide_spec (fscalar_spec (as_seq h0 b) s) 0))
      /\ as_seq h1 a == fscalar_tot (as_seq h0 b) s
    ))
[@"c_inline"]
let fscalar output b s =
  let hinit = ST.get() in
  push_frame();
  let tmp = create wide_zero clen in
  fscalar tmp b s;
  lemma_fscalar_eval (as_seq hinit b) s;
  carry_wide_ tmp 0ul;
  let h' = ST.get() in
  cut (eval_wide h' tmp = eval hinit b * v s);
  carry_top_wide tmp;
  let h'' = ST.get() in
  lemma_carry_top_wide_spec (as_seq h' tmp);
  copy_from_wide_ output tmp clen;
  lemma_copy_from_wide (as_seq h'' tmp);
  pop_frame()


[@"c_inline"]
val fmul:
  output:felem ->
  a:felem ->
  b:felem ->
  Stack unit
    (requires (fun h -> live h output /\ live h a /\ live h b
      /\ fmul_pre (as_seq h a) (as_seq h b)))
    (ensures (fun h0 _ h1 -> live h0 output /\ live h0 a /\ live h0 b
      /\ modifies_1 output h0 h1 /\ live h1 output
      /\ fmul_pre (as_seq h0 a) (as_seq h0 b)
      /\ eval h1 output % prime = (eval h0 a * eval h0 b) % prime
      /\ as_seq h1 output == fmul_tot (as_seq h0 a) (as_seq h0 b)
      ))
[@"c_inline"]
let fmul output a b = fmul output a b


[@"c_inline"]
val crecip:
  out:felem ->
  z:felem{disjoint out z} -> Stack unit
  (requires (fun h -> live h out /\ live h z /\ crecip_pre (as_seq h z)))
  (ensures (fun h0 _ h1 -> live h1 out /\ modifies_1 out h0 h1 /\ live h0 z
    /\ crecip_pre (as_seq h0 z)
    /\ as_seq h1 out == crecip_tot (as_seq h0 z)
  ))
[@"c_inline"]
let crecip output input =
  crecip output input
