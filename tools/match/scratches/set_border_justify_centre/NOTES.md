# set_border_justify_centre

The exact Windows body is the dual-mobile-authored
`void cRBorderManager::SetJustifyCentre(float)`. It stores the argument in the
manager's final dword at `+0x435b0`. All ten Windows callers load the same
root-owned manager at `cRGame +0xb4c`, pass either `0.0f` or `25.0f`, and
discard `EAX`; the copied argument bits are compiler residue.

Focused Wibo result: 100.00%, 3/3 instructions, no masked operands.
