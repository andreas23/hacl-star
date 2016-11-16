module Hacl.EC.Curve25519.Bignum.Fdifference

open FStar.Mul
open FStar.ST
open FStar.HyperStack
open FStar.Ghost
open FStar.Buffer
open FStar.Math.Lib

open Hacl.UInt64

open Hacl.EC.Curve25519.Parameters
open Hacl.EC.Curve25519.Bigint
open Hacl.EC.Curve25519.Utils

#reset-options "--initial_fuel 0 --max_fuel 0"

(* Module abbreviations *)
module HH = FStar.HyperHeap
module HS = FStar.HyperStack

module U8  = FStar.UInt8
module U32 = FStar.UInt32
module H8  = Hacl.UInt8
module H32  = Hacl.UInt32
module H64  = Hacl.UInt64

#reset-options "--initial_fuel 0 --max_fuel 0"

val add_big_zero_:
  b:bigint ->
  Stack unit
    (requires (fun h -> live h b))
    (ensures (fun h0 _ h1 -> live h1 b /\ modifies_1 b h0 h1))
let add_big_zero_ b =
  let two52m38 = (Hacl.Cast.uint64_to_sint64 0xfffffffffffdauL) in // pow2 52 - 38
  let two52m2 =  (Hacl.Cast.uint64_to_sint64 0xffffffffffffeuL) in // pow2 52 - 2
  let b0 = b.(0ul) in
  let b1 = b.(1ul) in
  let b2 = b.(2ul) in
  let b3 = b.(3ul) in
  let b4 = b.(4ul) in
  let c0 = b0 +%^ two52m38 in
  let c1 = b1 +%^ two52m2  in
  let c2 = b2 +%^ two52m2  in
  let c3 = b3 +%^ two52m2  in
  let c4 = b4 +%^ two52m2  in
  update_5 b c0 c1 c2 c3 c4


val add_big_zero:
  b:bigint ->
  Stack unit
    (requires (fun h -> live h b))
    (ensures (fun h0 _ h1 -> live h1 b /\ modifies_1 b h0 h1))
let add_big_zero b =
  add_big_zero_ b


val fdifference_:
  a:bigint ->
  b:bigint{disjoint a b} ->
  Stack unit
    (requires (fun h -> live h a /\ live h b))
    (ensures (fun h0 _ h1 -> live h1 a /\ modifies_1 a h0 h1))
let fdifference_ a b =
  let a0 = a.(0ul) in
  let a1 = a.(1ul) in
  let a2 = a.(2ul) in
  let a3 = a.(3ul) in
  let a4 = a.(4ul) in
  let b0 = b.(0ul) in
  let b1 = b.(1ul) in
  let b2 = b.(2ul) in
  let b3 = b.(3ul) in
  let b4 = b.(4ul) in
  let c0 = b0 -%^ a0 in
  let c1 = b1 -%^ a1 in
  let c2 = b2 -%^ a2 in
  let c3 = b3 -%^ a3 in
  let c4 = b4 -%^ a4 in
  update_5 a c0 c1 c2 c3 c4


val fdifference':
  a:bigint ->
  b:bigint{disjoint a b} ->
  Stack unit
    (requires (fun h -> live h a /\ live h b))
    (ensures (fun h0 u h1 -> live h1 a /\ modifies_1 a h0 h1))
let fdifference' a b =
  fdifference_ a b