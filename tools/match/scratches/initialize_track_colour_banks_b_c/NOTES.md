# initialize_track_colour_banks_b_c

CRT constructor body at `0x4349c0` for the 102-entry contiguous B/C allocation. It invokes the
folded no-op `Color4f` constructor across the complete owner before
`build_track_colours` supplies the authored white values. The loop matches the
native 12/12 instructions exactly, with both masked operands resolved.
