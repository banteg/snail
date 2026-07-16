# initialize_track_colour_bank_k

CRT constructor body at `0x434b40` for the 51-entry Windows counterpart of
`gLocColourLookupPathWarp`. The K suffix remains only as the stable CRT-table
identity. It invokes the folded no-op `tColour` constructor across the complete
owner before `build_track_colours` supplies the authored white values. Mobile
and Windows `BuildColours` intentionally visit this same owner twice. The loop
matches the native 12/12 instructions exactly, with both masked operands
resolved.
