# sample_smtrack_heightmap @ 0x41a360

First tracked scratch for the SMTrack replacement-heightmap sampler.

Recovered behavior:

- the fourth argument is a `TextureRef*`; textures retained with
  `TEXTURE_REF_RETAIN_SOURCE_BYTES` (`0x20`)
  keep their source TGA bytes at `TextureRef::texture_ref +0x98`;
- source is the borrowed SMTrack `Object`; specialized fields `+0x1c`, `+0x24`,
  and `+0x28` derive the sampled row count, while inherited
  `Object::vertices +0x38` is the 12-byte output vector array;
- the loop bounds are inclusive float counters, matching the native x87
  `test ah, 0x41` comparisons;
- each sample looks up a bottom-up RGB texel, averages the three channels with
  `1/255` and `1/3` factors, optionally cubes the value, then writes
  `base + value * scale` to the output record's y lane.

Focused Wibo result: 59.09%, 111/109 instructions, prefix 0/109, with 12 clean
masked operands. Remaining differences are allocator/scheduling shape: the
scratch keeps the output pointer on the stack while the native keeps it in
`ebp`, and the compiler folds later channel additions into `fiadd`.

2026-06-21 sample-pointer retry: marking the former scratch-local output cursor
as `register` is codegen-neutral at 59.09%. VC6 still spills the output cursor
and only saves `ebp` inside the loop, so the native `ebp` sample-cursor
ownership needs a different source shape.

2026-07-11 ownership consolidation: replacing the scratch-local image,
replacement, and output records with shared `TgaImageView`, `TextureRef`,
`Object`, and `Vector3` types preserves the honest 59.09% baseline, 111/109
instruction shape, and all 12 clean operands.

2026-07-12 grid-field and RGB ownership pass:

- `Object +0x1c/+0x24/+0x28` are now shared as the SMTrack heightmap sample
  count, row-aspect divisor, and row-aspect numerator. The sampler is their
  only covered reader; it derives the inclusive row count before borrowing
  `Object::vertices` as its output cursor.
- Declaring the red, green, and blue samples as floats recovers the native
  three independent byte-to-float conversions and `faddp` chain. This is a
  real source-type correction, improving the focused result from 59.09% to
  60.36%, with 113/109 instructions and all 12 operands still clean.
- Direct payload indexing, alternate pixel-index expressions, declaration
  ordering, `register`, and pre/post-increment cursor spellings either
  preserved the same allocation or regressed it. The honest residual remains
  VC6 register scheduling: native reserves `ebp` for the borrowed vertex
  cursor while the candidate spills that cursor and uses `ebp` for the texel
  offset.

## 2026-07-16 ABI and Object-field promotion

- The only native caller passes a borrowed `Object*`, two floats, the current
  `TextureRef*`, and a byte flag, then discards EAX. Replaying that exact void
  cdecl contract removes the former pointer-result/floating-argument fiction in
  both decompilers.
- `Object +0x1c/+0x24/+0x28` are promoted into the shared analysis owner as
  `heightmap_sample_count`, `heightmap_sample_divisor`, and
  `heightmap_sample_scale`. The complete 0xdc-byte Object extent is unchanged.
- Focused matching honestly remains 60.36%, 113/109 instructions, with all 12
  operands clean. This pass recovers ownership and ABI only; it does not hide
  the remaining VC6 register-scheduling difference.
