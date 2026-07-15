# file_exists @ 0x405140

Probes one filesystem path by opening it in binary-read mode, closes a
successful stream, and returns a byte boolean.

2026-07-15 CRT ownership: the scratch uses VC6's real `<stdio.h>` `FILE*`,
`fopen`, and `fclose` contracts rather than an opaque local `File`. The focused
object remains exact at 14/14 instructions with three clean masked operands.
