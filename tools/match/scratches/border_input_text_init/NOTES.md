# cRBorder::InputTextInit @ 0x403410

Exact match: 100.00%, 46/46 instructions, with all three masked operands clean.

The method initializes the complete inline editor tail, appends the visible
cursor marker, relayouts the border, and conditionally initializes its
embedded `cRInputOK`. Android and iOS `Border.o` preserve the authored owner
and lifecycle. Live Windows analysis confirms a void thiscall and two native
callsites.

The stable matcher identity remains `border_input_text_init`; source and
relocations use the authored member name.

## Saved-name storage

The Windows initializer passes `this + 0x6cc` to `Rstrcpy` at
`0x40341d..0x40342a`, then scans the editable string at `this + 0x2cc`
and appends its cursor marker. The next field, `font_id`, begins at
`+0x6ec`. The recovered layout gives the edit buffer 0x400 bytes and
the saved string the following 0x20-byte span. Android and iOS place the
two strings at `+0x2c4` and `+0x6c4`, with their font ID at `+0x6e4`.
Chromadrome and Chromentum independently use the saved string during
submission and also place the next font field 0x20 bytes later. The older
analyzer headers describe both regions together as one 0x420-byte extent.

The Windows high-score callers pass capacity 16 for editing. The initializer
copies the supplied string with the original `Rstrcpy`. Separating the arrays
preserves the initializer's exact code. With the new layout, a diagnostic
completion helper that restores the named saved buffer on empty input produces
the copy seen in the predecessor games. Disabling restoration also removes the
first-character load, leaving the Windows editor at 443/446 instructions.
See the [completion evidence](../border_input_text/NOTES.md).
