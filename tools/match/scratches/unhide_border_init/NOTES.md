# unhide_border_init @ 0x401110

Exact authored `cRBorder::UnHideInit()` transition on the shared
`FrontendWidget` owner.

Android preserves the same two state updates: restore `hide_blend` to one and
clear `FRONTEND_WIDGET_FLAG_HIDDEN`. Every Windows caller discards EAX, so the
updated flags word left in the register is incidental. Correcting the member to
`void` preserves the exact 5/5 instruction stream.
