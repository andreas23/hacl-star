module Test.Hacl.Hardware.Intel.DRNG

open FStar.Buffer
open FStar.UInt32
open Hacl.Hardware.Intel.DRNG

module R = Hacl.Hardware.Intel.DRNG


(* Entry point *)
val main: unit -> ST FStar.Int32.t
  (requires (fun h -> True))
  (ensures  (fun h0 r h1 -> True))
let main () =
  push_frame();
  
  (* Allocate space to get randomness from the CPU *)
  let size = 64ul in
  let result = create 0uy size in
  
  (* Call the Random Number Generator *)
  R.random_bytes result size;

  (* Generate and display some randomly generated bytes *)
  C.print_string (C.string_of_literal "Randomly generated bytes: \n");
  C.print_bytes result size;

  pop_frame();
  C.exit_success
