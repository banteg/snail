# initialize_track_colour_bank_f

CRT constructor body at `0x434a50` for the 51-entry Windows counterpart of
`gLocColourLookupTrampoline`. The F suffix remains only as the stable CRT-table
identity. It invokes the folded no-op `tColour` constructor across the complete
owner before `build_track_colours` supplies the authored white values. The loop
matches the native 12/12 instructions exactly, with both masked operands
resolved.
