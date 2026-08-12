# initialize_global_color4f_bank_32_thunk

CRT table entry `0x4a1014` points to this one-instruction thunk at `0x410c00`,
which tail-jumps over 11 alignment nops to the adjacent 32-entry tColour
constructor loop. The source-level tail call matches the native 1/1 instruction
exactly, with its target resolved.

## 2026-08-12 source-unit provenance

The thunk and its body form one uninterrupted startup run between verified
`Game.o` implementations of `cRPlayer::AI()` and
`cRBackdrop::SetZoom(float)`. This recovers `Game.o` as the compilation unit
without assigning a speculative gameplay class to the otherwise unused colour
bank. The exact 1/1 thunk is unchanged.
