
let disjoint_only_lemma t b t' b' = ()  
let eq_lemma h0 h1 size a mods = ()
let modifies_transitivity_lemma mods h0 h1 h2 = ()
let modifies_subset_lemma mods submods h0 h1 = ()
let modifies_empty_lemma h = ()
let modifies_fresh_lemma h0 h1 mods size b = ()

type ('a, 'b, 'c, 'd) disjoint = unit
type ('a, 'b, 'c) live = unit

type abuffer = unit
                           
type 'a buffer = {
    content:'a array;
    idx:int;
    length:int;
  }

type uint32 = int

type u8s = Hacl_UInt8.uint8 buffer
type u32s = Hacl_UInt32.uint32 buffer 
type u64s = Hacl_UInt64.uint64 buffer 
type u128s = Hacl_UInt128.t buffer
                               
type s8 = Hacl_UInt8.t                                  
type s32 = Hacl_UInt32.t                                  
type s64 = Hacl_UInt64.uint64
type s128 = Hacl_UInt128.t
                
let create init len = {content = Array.make len init; idx = 0; length = len}
let index b n = Array.get b.content (n+b.idx)
let upd (b:'a buffer) (n:int) (v:'a) = Array.set b.content (n+b.idx) v
let sub b i len = {content = b.content; idx = b.idx+i; length = len}
let offset b i  = {content = b.content; idx = b.idx+i; length = b.length-i}
let blit a idx_a b idx_b len = Array.blit a.content (idx_a+a.idx) b.content (idx_b+b.idx) len
let fill () a z len = Array.fill a.content 0 len z
let split a i = (sub a 0 i, sub a i (a.length - i))
let of_seq s l = ()
let copy b l = {content = Array.sub b.content b.idx l; idx = 0; length = l} 
                
type ('a, 'b, 'c, 'd) modifies_buf = ()
let op_Plus_Plus a b = BatSet.empty
let only a = BatSet.empty
