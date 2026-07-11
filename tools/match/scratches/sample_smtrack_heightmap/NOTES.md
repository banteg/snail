# sample_smtrack_heightmap @ 0x41a360

First tracked scratch for the SMTrack replacement-heightmap sampler.

Recovered behavior:

- the fourth argument is a `TextureRef*`; textures retained with flag `0x20`
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
