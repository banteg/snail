# `load_png_image` match result

## Score

| Metric | Result |
|---|---:|
| Match | **100.00%** |
| Target instructions | 371 |
| Candidate instructions | 371 |
| Common prefix | **371 / 371** |
| Masked operands | **78 clean, 0 unresolved, 0 mismatched** |

The recovered C++ is instruction-for-instruction exact across the complete
965-byte native function at `0x42f0a0..0x42f464`.

## Recovered ownership and source shape

- Promoted the helper out of the preceding Cage2 initializer's formerly coarse
  target range.
- Recovered the true seven-argument cdecl ABI: path, pixel-buffer owner,
  width/height/channel outputs, optional `bKGD` RGB output, and integer file
  offset.
- Identified `g_png_read_struct @ 0x5032f4` and
  `g_png_info_struct @ 0x5032f8` as file-scope scratch state owned exclusively
  by this loader.
- Identified all direct image calls as the statically linked libpng 1.2.5 API,
  keeping bundled library code outside the gameplay-function manifest.
- Used the authentic VC6 `<setjmp.h>` intrinsic over the libpng jump-buffer
  prefix. This both expresses the real error-recovery contract and naturally
  reproduces the native EBP frame and hidden setjmp3 frame argument.
- Recovered the complete signature check, transform setup, background/gamma
  handling, contiguous image allocation, row-table construction, read, and
  cleanup paths.

## Final audit

- Toolchain: `msvc6.5 /O2 /G5 /W3`.
- No inline assembly, naked functions, volatile padding, dummy branches,
  fabricated globals, fake aliases, or matcher/normalizer gaming.
