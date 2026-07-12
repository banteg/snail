# Exact match

`initialize_tip_manager` matches exactly at 7/7 instructions and is the Windows
`cRTipManager::Init()` member. It clears the three inline 0x20-byte Tips at
Windows manager offset 0x38. The corresponding iOS array begins at 0x2c because
that port's BodBase prefix is smaller; the array ownership and element layout
are otherwise independently confirmed.
