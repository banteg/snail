# reset_tooltip @ 0x403be0

Stable scratch identity for the authored `void cRToolTip::ReSet()` member.
All seven Windows callsites load `ECX = cRBorder + 0x28c`, proving that the
receiver is the embedded 0x40-byte tooltip controller. State 3 releases the
manager-owned tooltip widget and falls through to the state-2 idle reset;
other states return unchanged.

Android preserves `cRToolTip::ReSet()` and the same state machine. The Windows
source selects `?ReSet@cRToolTip@@QAEXXZ` and matches exactly at 16/16
instructions with both masked operands clean.
