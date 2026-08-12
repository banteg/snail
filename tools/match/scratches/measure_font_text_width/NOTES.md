# FontGetStringX

`FontGetStringX(char*, int, float)` is the native-authored owner of the Windows
routine at `0x449e90`. The focused match is exact: 60/60 instructions and nine
clean references.

It accumulates atlas glyph widths and applies the native trailing-space
adjustment before returning the measured width. Android exports the same
`Font.o` symbol; the iOS corpus has no retained export. Live Windows analysis
finds four callers.

The directory and manifest retain `measure_font_text_width` as the stable
matcher identifier.
