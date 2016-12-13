module Hacl.Bignum.Modulo

open FStar.Mul
open FStar.HyperStack
open FStar.Buffer

open Hacl.Bignum.Parameters
open Hacl.Bignum.Bigint
open Hacl.Bignum.Limb
open Hacl.Bignum.Modulo.Spec

inline_for_extraction let two54m152 =
  assert_norm (pow2 64 > 0x3fffffffffff68); uint64_to_limb 0x3fffffffffff68uL
inline_for_extraction let two54m8   =
  assert_norm (pow2 64 > 0x3ffffffffffff8); uint64_to_limb 0x3ffffffffffff8uL
inline_for_extraction let nineteen  = assert_norm(19 < pow2 64); uint64_to_limb 19uL
inline_for_extraction let mask_51    =
  assert_norm (0x7ffffffffffff < pow2 64);uint64_to_limb 0x7ffffffffffffuL


let add_zero b =
  let b0 = b.(0ul) in
  let b1 = b.(1ul) in
  let b2 = b.(2ul) in
  let b3 = b.(3ul) in
  let b4 = b.(4ul) in
  b.(0ul) <- b0 +^ two54m152;
  b.(1ul) <- b1 +^ two54m8;
  b.(2ul) <- b2 +^ two54m8;
  b.(3ul) <- b3 +^ two54m8;
  b.(4ul) <- b4 +^ two54m8


let carry_top b =
  let b4 = b.(4ul) in
  let b0 = b.(0ul) in
  let mask = (limb_one <<^ climb_size) -^ limb_one in
  let nineteen = (limb_one <<^ 4ul) +^ (limb_one <<^ 1ul) +^ limb_one in
  let b4' = b4 &^ mask in
  let b0' = b0 +^ (nineteen *^ (b4 >>^ climb_size)) in
  b.(4ul) <- b4';
  b.(0ul) <- b0'


let reduce b =
  let nineteen = (limb_one <<^ 4ul) +^ (limb_one <<^ 1ul) +^ limb_one in
  let b0 = b.(0ul) in
  b.(0ul) <- nineteen *^ b0


let carry_top_wide b =
  let b4 = b.(4ul) in
  let b0 = b.(0ul) in
  let nineteen = (limb_one <<^ 4ul) +^ (limb_one <<^ 1ul) +^ limb_one in
  let open Hacl.Bignum.Wide in
  let mask = (wide_one <<^ climb_size) -^ wide_one in
  let b4' = b4 &^ mask in
  let b0' = b0 +^ (nineteen *^ (wide_to_limb (b4 >>^ climb_size))) in
  b.(4ul) <- b4';
  b.(0ul) <- b0'