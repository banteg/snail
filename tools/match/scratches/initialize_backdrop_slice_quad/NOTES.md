# initialize_backdrop_slice_quad @ 0x41a1c0

Builds the same 1x1 four-vertex backdrop quad shape as the universe helper,
sets the low byte of `Object::flags` with `0x80`, and maps the texture to one
horizontal `1/8` UV slice. `x_offset` selects the negative left U edge via
`(x_offset + 1.0f) * -0.125f`; the right U edge stays zero.

Focused match: 100%, 61/61 instructions, with seven clean masked operands. The
decompiler's `0x3e000000` return is the leftover `eax` from storing `0.125f`
into the first two V components; the source shape is void.
