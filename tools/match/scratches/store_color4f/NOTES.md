# store_color4f @ 0x44dbb0

Stable Windows harness identity for the authored four-float `tColour`
constructor role retained by Android. It stores RGBA at `+0/+4/+8/+12` and is
exact at 9/9 instructions as a void write. The value left in `edx` after the
last store is incidental; all covered callers consume the constructed colour,
not a helper return.
