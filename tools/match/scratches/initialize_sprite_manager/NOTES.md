# WIP - sprite pool topology

This scratch is a relationship map for the shared sprite manager: it clears the paused flag and active owner buckets, seeds `g_sprite_free_head` with the first sprite, initializes all 3000 sprite nodes, links the free-list chain, and records the final bucket tail around `0x83cbc/0x83cc0`.

Current match: 50.55%, with a 6/45 exact prefix. The active bucket clear is
now modeled as a fixed-size `memset`-style clear, matching BN's recovered
`__builtin_memset(&arg1[0x83d64], 0, 0x14)` view and recovering the target's
separate `xor eax, eax` zero register.

Remaining residuals are register and block-layout differences around that clear
and the first/last-node special cases. Native writes the bucket clears as direct
`[esi+offset]` stores and delays saving/zeroing `edi`; the current source-shaped
clear routes those stores through a bucket pointer. The source should stay
topology-first until the exact VC6 loop shape is isolated.

`SpriteManager` is promoted in `tools/match/include/sprite.h` with the recovered
pool fields (`paused`, 3000 sprite slots at `+0x04`, five active heads at
`+0x83d64`, and `free_head` at `+0x83d78`). A fully field-access body was tested
but dropped because VC6 moved `this` to `edi` and reduced the score to 22.22%;
the retained body keeps the better topology-first shape.

Rejected/source-neutral probes:

- a literal dword-pointer body matching IDA's `this + 45*i` view compiled back
  to the same 47.19% register schedule as the old byte-offset body;
- separate byte/int/null zero locals and active-head pointer locals were
  optimized back into the same `ebx` zero stores;
- moving the loop-index declaration between active-head stores only shifted the
  `xor edi, edi` point; it did not recover the target's `eax` zero/direct-store
  sequence;
- result temporaries for the first/middle/last link writes were optimized away.
