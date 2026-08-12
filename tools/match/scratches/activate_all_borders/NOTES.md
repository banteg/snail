# activate_all_borders

The exact Windows body is the Android-authored
`void cRBorderManager::ActivateBorders()`. It walks the 150 manager-owned
records, restores `DISABLED` only when the saved disabled-state bit is clear,
then clears that saved bit, resets both padding targets to idle, and clears the
hover target. Android uses a platform pointer-backed pool; no offsets transfer
to Windows.

Focused Wibo result: 100.00%, 19/19 instructions, no masked operands.
