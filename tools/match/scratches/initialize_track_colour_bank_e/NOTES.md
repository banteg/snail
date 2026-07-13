# initialize_track_colour_bank_e

CRT constructor body at `0x434a20` for the 51-entry bank E. It invokes the
folded no-op `Color4f` constructor across the complete owner before
`build_track_colours` supplies the authored white values. The loop matches the
native 12/12 instructions exactly, with both masked operands resolved.
