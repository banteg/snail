# hide_border_init @ 0x4010e0

Stable scratch identity for the authored `void cRBorder::HideInit()` member.
It returns when already hidden; otherwise it sets the hidden flag, clears
`hide_blend`, and resets the embedded `cRToolTip` at +0x28c. Android preserves
the authored member and the same complete control flow, while live Windows
analysis confirms the typed `cRBorder` receiver and owned tooltip call.

The Windows source matches exactly at 9/9 instructions with its call operand
clean.
