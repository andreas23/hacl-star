module Hacl.Cast

open FStar.Int.Cast

module U8 = FStar.UInt8
module S8  = Hacl.UInt8
module U32 = FStar.UInt32
module S32 = Hacl.UInt32
module U64 = FStar.UInt64
module S64 = Hacl.UInt64
module S128 = Hacl.UInt128

(** Uints to Sints **)
val sint8_to_sint128: a:S8.t -> Tot (b:S128.t{S128.v b = S8.v a})
let sint8_to_sint128 a = uint64_to_uint128 (uint8_to_uint64 a)
val sint8_to_sint64: a:S8.t -> Tot (b:S64.t{S64.v b = S8.v a})
let sint8_to_sint64 a = uint8_to_uint64 a
val sint8_to_sint32: a:S8.t -> Tot (b:S32.t{S32.v b = S8.v a})
let sint8_to_sint32 a = uint8_to_uint32 a

val sint32_to_sint128: a:S32.t -> Tot (b:S128.t{S128.v b = S32.v a})
let sint32_to_sint128 a = uint64_to_uint128 (uint32_to_uint64 a)
val sint32_to_sint64: a:S32.t -> Tot (b:S64.t{S64.v b = S32.v a})
let sint32_to_sint64 a = uint32_to_uint64 a
val sint32_to_sint8 : a:S32.t -> Tot (b:S8.t{S8.v b = S32.v a % pow2 8})
let sint32_to_sint8 a = uint32_to_uint8 a

val sint64_to_sint128: a:S64.t -> Tot (b:S128.t{S128.v b = S64.v a})
let sint64_to_sint128 a = uint64_to_uint128 a
val sint64_to_sint32: a:S64.t -> Tot (b:S32.t{S32.v b = S64.v a % pow2 32})
let sint64_to_sint32 a = uint64_to_uint32 a
val sint64_to_sint8 : a:S64.t -> Tot (b:S8.t{S8.v b = S64.v a % pow2 8})
let sint64_to_sint8 a = uint64_to_uint8 a

val sint128_to_sint64: a:S128.t -> Tot (b:S64.t{S64.v b = S128.v a % pow2 64})
let sint128_to_sint64 a = uint128_to_uint64 a
val sint128_to_sint32: a:S128.t -> Tot (b:S32.t{S32.v b = S128.v a % pow2 32})
let sint128_to_sint32 a = uint64_to_uint32 (uint128_to_uint64 a)
val sint128_to_sint8 : a:S128.t -> Tot (b:S8.t{S8.v b = S128.v a % pow2 8})
let sint128_to_sint8 a = uint64_to_uint8 (uint128_to_uint64 a)

val uint64_to_sint128: a:U64.t -> Tot (b:S128.t{S128.v b = U64.v a})
let uint64_to_sint128 a = uint64_to_uint128 a
val uint64_to_sint64: a:U64.t -> Tot (b:S64.t{S64.v b = U64.v a})
let uint64_to_sint64 a = a
val uint64_to_sint32: a:U64.t -> Tot (b:S32.t{S32.v b = U64.v a % pow2 32})
let uint64_to_sint32 a = uint64_to_uint32 a
val uint64_to_sint8: a:U64.t -> Tot (b:S8.t{S8.v b = U64.v a % pow2 8})
let uint64_to_sint8 a = uint64_to_uint8 a

val uint32_to_sint128: a:U32.t -> Tot (b:S128.t{S128.v b = U32.v a})
let uint32_to_sint128 a = uint64_to_uint128 (uint32_to_uint64 a)
val uint32_to_sint64: a:U32.t -> Tot (b:S64.t{S64.v b = U32.v a})
let uint32_to_sint64 a = uint32_to_uint64 a
val uint32_to_sint32: a:U32.t -> Tot (b:S32.t{S32.v b = U32.v a})
let uint32_to_sint32 a = a
val uint32_to_sint8: a:U32.t -> Tot (b:S8.t{S8.v b = U32.v a % pow2 8})
let uint32_to_sint8 a = uint32_to_uint8 a

val uint8_to_sint128: a:U8.t -> Tot (b:S128.t{S128.v b = U8.v a})
let uint8_to_sint128 a = uint64_to_uint128 (uint8_to_uint64 a)
val uint8_to_sint64: a:U8.t -> Tot (b:S64.t{S64.v b = U8.v a})
let uint8_to_sint64 a = uint8_to_uint64 a
val uint8_to_sint32: a:U8.t -> Tot (b:S32.t{S32.v b = U8.v a})
let uint8_to_sint32 a = uint8_to_uint32 a
val uint8_to_sint8: a:U8.t -> Tot (b:S8.t{S8.v b = U8.v a})
let uint8_to_sint8 a = a