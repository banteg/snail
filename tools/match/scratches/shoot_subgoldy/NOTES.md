# WIP - 63.04% score, 44/48 insns on standard flags

Semantics recovered from the IDA/BN exports:

- `this` points at the first `SubLazerSlot`; 20 slots, stride `0xb0`.
- The free-slot scan checks each slot state at `+0x80`.
- Spawn origin copies input `x/z`, offsets `y` by `slot_index * -0.01`,
  then calls `spawn_sub_lazer_projectile(slot, &origin, direction)`.
- The successful allocation edge plays positional sound effect `15` from the
  original input origin through the global positional sound helper at
  `0x78ff88`.

Current residuals:

- loop branch layout differs (`jge` vs target `jl` fallthrough shape)
- stack frame is smaller because VC6 keeps the temporary spawn vector tighter
- y-offset expression still compiles as `fsubr` instead of the target
  `fmul`/`fadd` sequence

Do not force these with dummy branches or fake globals; the next iteration
should find the original source shape that produces the target stack layout.
