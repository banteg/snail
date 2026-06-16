# sample_tga_pixel_rgb

Initial scratch for the image-buffer pixel sampler at `0x44e780`.

Recovered relationships:

- Only called by `register_font_texture_sheet`.
- Reads a TGA-like buffer with width at `+0x0c`, height at `+0x0e`,
  bits-per-pixel at `+0x10`, and pixel bytes beginning at `+0x12`.
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
