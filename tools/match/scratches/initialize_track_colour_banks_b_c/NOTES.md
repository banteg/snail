# initialize_track_colour_banks_b_c

CRT constructor body at `0x4349c0` for the 102-entry contiguous Windows owner
holding the 51-entry Floor bank followed by the first 51-entry Slide bank. The
mobile ports preserve these names as `gLocColourLookupFloor` and
`gLocColourLookupSlide`; Windows' single constructor proves that its two views
share one `0x660`-byte allocation. It invokes the folded no-op `tColour`
constructor across the complete owner before `build_track_colours` supplies the
authored white values. The B/C suffix remains only as the stable CRT-table
identity. The loop matches the native 12/12 instructions exactly, with both
masked operands resolved.
