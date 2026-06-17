# reset_subgame

First relationship scratch for the subgame runtime reset helper at `0x437b10`.

Recovered behavior:

- clears the eight health pickup slots, two singleton pickup runtimes, the
  fifty garbage slots, eight slug slots, and two ring/special-effect parents;
- preserves/restores the saved run score/timer snapshot when the replay/restore
  byte is armed and the current level mode matches the saved level mode;
- otherwise clears score buckets for mode `2`, zeros the live timer counters,
  and clears the two saved score/timer tail fields;
- re-arms the two live subgame bytes, clears the replay/restore byte, and
  resets the active garbage chain head.

This first scratch intentionally keeps the large `Game` owner as raw dword
offsets until the surrounding reset/update functions agree on field names.

Current focused result:

- 98.67%, 75/75 instructions, prefix 44/75
- masked comparison: 2 ok, 0 unresolved, 0 mismatch

Important source-shape correction:

- The saved timer snapshot copy must be spelled as C-linkage intrinsic
  `memcpy`. A manual six-dword copy regressed the function to 35.06% by keeping
  `this` in `esi`; a plain declared `memcpy` regressed to 30.07% by emitting a
  real call. `extern "C"` plus `#pragma intrinsic(memcpy)` recovers the native
  `push esi; push edi; mov ecx, 6; rep movsd` block and the `ebp` owner
  register.

Remaining residual:

- Native loads the saved tail fields as score, tail-a, tail-b. VC6 keeps the
  equivalent source values but loads tail-b before tail-a. Local-order probes
  were codegen-neutral, so leave this as a register/scheduling residual unless
  new source evidence appears.
