# initialize_track_colour_bank_d

CRT constructor body at `0x4349f0` for the 51-entry bank D. It invokes the
folded no-op `Color4f` constructor across the complete owner before
`build_track_colours` supplies the authored white values. The loop matches the
native 12/12 instructions exactly, with both masked operands resolved.
