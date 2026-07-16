# initialize_track_colour_bank_a

CRT constructor body at `0x434990` for the 51-entry Windows counterpart of the
original mobile `gLocColourLookupCheckBlack` bank. It invokes the folded no-op
constructor across the full `0x330`-byte owner; `build_track_colours` later
supplies the authored white values. The A suffix remains only as the stable CRT
constructor-table identity.
The loop matches the native 12/12 instructions exactly, with both masked
operands resolved.
