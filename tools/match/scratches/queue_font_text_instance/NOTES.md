# FontPrint

`FontPrint(char*, int, float, float, float, int, float, int, tColour, float,
bool)` owns the Windows routine at `0x44a790`. The focused match is exact:
73/73 instructions and 24 clean references.

It copies text into the transient buffer, appends a `cFontPrintBuffer` record,
and publishes the new queue count. Android retains the authored `Font.o`
symbol; the iOS corpus has no retained export. Windows locally proves borrowed
`tColour*` and byte-sized boolean storage where the mobile ABI uses values.

The directory and manifest retain `queue_font_text_instance` as the stable
matcher identifier.

## Register-hint cleanup (2026-08-13)

Removing the legacy `register` hint from the text source cursor is byte-neutral:
the focused result remains exact at **100.00%**, 73/73 instructions, with all
24 references clean. The source now records only the authored cursor lifetime.
