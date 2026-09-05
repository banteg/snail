# Exact backdrop rendering

`cRBackdrop::render_backdrop()` at `0x411040` matches **192/192 native
instructions**, the full prefix, and **29 clean references** with
`msvc6.5 /O2 /G5 /W3`.

The final source carries the next column as a float between iterations and
reads it into a body-local double coordinate. Geometry and UV operations
retain their float conversions. The carried float also controls the loop,
reproducing both the native dword zero load and the non-popping x87 comparison.
The earlier 99.22% source loaded that loop value twice and had 193 instructions.

All 7-by-7 quads, distortion-grid offsets, flipped UVs, colors, and render calls
remain native-backed. No shared header, ABI, compiler option, fake constant,
or matcher rule changed. The exact source does not uniquely identify the
original author's local variable declarations; the measured alternatives and
the rejected precision simplifications are recorded in the notes and ledger.
