# sample_tga_pixel_rgb

Initial scratch for the image-buffer pixel sampler at `0x44e780`.

Recovered relationships:

- Only called by `register_font_texture_sheet`.
- Reads the shared `TgaImageView` from `tools/match/include/tga_image_view.h`:
  width at `+0x0c`, height at `+0x0e`, bits-per-pixel at `+0x10`, and pixel
  bytes beginning at `+0x12`.
- Samples bottom-up rows via `(height - y - 1) * width + x`.
- For 8-bit images it expands the single byte to grayscale RGB; otherwise it
  returns the first three pixel bytes as packed `0xRRGGBB`.

The first assumption that this neighborhood was all parser/string code was
wrong; this helper is part of font atlas registration.

Focused Wibo result: 25.29%, 38/49 candidate/target instructions, no masked
operands. The `TgaImageView` field layout and bottom-up 8/24-bit semantics are
clear, but native keeps the image pointer in `edx`, offset in `ecx`, and uses
`esi`/`edi` byte lanes for RGB packing. Source-shape probes with direct indexed
loads, raw byte-buffer parameters, unsigned bpp locals, register hints, and
stepwise RGB packing did not improve the allocation, so this remains an honest
relationship scratch rather than a forced match.

2026-06-20 parser/resource helper retry: focused Wibo still reports `25.29%`,
`38/49` candidate/target instructions, and no masked operands. Removing the
`pixel` pointer and indexing `image->pixels[offset + n]` directly regressed to
`16.09%` by moving the image owner to `esi` and offset to `eax`. Naming an
`int bits_per_pixel` local regressed to `22.99%` and introduced signed-shift
shape; a raw byte-buffer header view regressed to `25.00%` with a stack byte
spill. Stepwise RGB packing was codegen-neutral at `25.29%` and still did not
recover native's `esi`/`edi` byte lanes. At that point the typed `TgaImageView`
plus `pixel` pointer source was the best relationship scratch; the residual was
register allocation around the image base, offset, and RGB packing lanes.

2026-06-21 exact pass: generated source-shape variants showed the missed shape
was not the `TgaImageView` layout, but the lifetime of the bits-per-pixel byte
and the RGB result locals. Removing the named pixel pointer, using direct
`image->bits_per_pixel` reads, and folding both 8-bit and 24-bit cases through
one `red`/`green`/`blue` return path recovers native's `edx` image base,
`ecx` byte offset, and `esi`/`edi` packing registers. For grayscale, assigning
the sampled value in `blue`, `green`, then `red` order gives the native
`ecx -> edi -> esi` copy chain. Focused matcher result is now 100.00%, 49/49
instructions, full 49/49 prefix, and no masked operands.

## 2026-07-23 TGA payload ownership

The analysis header and both decompiler replays now carry the exact `0x14`-byte
`TgaImageView` owner rather than a generic file buffer. Binary Ninja exposes
`height`, `bits_per_pixel`, `width`, and the trailing `pixels` payload directly;
the remaining `+0x13`/`+0x14` expressions are honest indexing of the second and
third bytes after the flexible payload start.

Both xrefs are the two atlas-marker probes inside
`register_font_texture_sheet`. This analysis-only ownership recovery leaves the
exact matcher source untouched and preserves 100.00%, 49/49 instructions, a
49/49 prefix, and no masked operands.

## 2026-08-12 authored helper and source-unit recovery

Android retains the exact exported helper
`GetTgaColour(cTgaHeader*, int, int)`. Its body reproduces every material
operation in the Windows scratch: the bottom-up row calculation, byte stride
from bits-per-pixel, 8-bit grayscale expansion, and the first three 24-bit
bytes packed as `0xRRGGBB`.

The Android helper begins the compact `RTexture.o` linker run. It is followed
by the texture-name and TGA-loop helpers and then by the independently
STABS-sourced `cRTextures::Add` and `cRTextures::Init`, before the next cRBod
unit. Windows independently places this exact helper immediately before its
verified `RTexture.o` Init/Add pair. The crosswalk therefore records the
authored Android-only symbol and `RTexture.o` provenance; iOS has no retained
body, and no mobile field offsets are copied into the Windows layout.
