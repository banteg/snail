# Exact match

`Tutorial::uninit_tutorial` @ `0x448dd0` is the Windows
`cRTutorial::UnInit()`. It delegates tutorial UI teardown to the root
`TipManager`; the embedded tutorial object owns no tip allocation.

The primary 0x1c-byte `Tutorial` owner remains exact at 3/3 instructions with
both operands clean.
