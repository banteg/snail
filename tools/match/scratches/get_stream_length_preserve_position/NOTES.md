# get_stream_length_preserve_position @ 0x405170

Saves the current stream offset, seeks to `SEEK_END`, reads the byte length,
then restores the original position with `SEEK_SET`.

2026-07-15 CRT ownership: the parameter and offsets now use VC6's authentic
`FILE*` and `long` contracts from `<stdio.h>` instead of an opaque `File` plus
hand-written `ftell`/`fseek` declarations. The focused object remains exact at
24/24 instructions with four clean masked operands.
