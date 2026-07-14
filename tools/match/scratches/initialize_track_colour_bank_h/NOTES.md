# initialize_track_colour_bank_h

CRT constructor body at `0x434ab0` for the 51-entry bank H. It invokes the
folded no-op `tColour` constructor across the complete owner before
`build_track_colours` supplies the authored white values. The loop matches the
native 12/12 instructions exactly, with both masked operands resolved.
