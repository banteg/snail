# cRBorder::Draw @ 0x401130

Current recovery: semantic-complete (`compiler` residual). The Windows body is
a `void __thiscall cRBorder` member, and Android/iOS independently retain it as
`cRBorder::Draw()` in `Border.o`. Its sole Windows caller supplies the widget in
`ecx` and discards `eax`.

The recovered body covers the render gate, slider strips, extended and ordinary
sprites, optional shadow, nine-slice frame, and the manager-owned delayed glow.
Live disassembly bounds the function at the glow tail; there is no missing text
or special-widget branch.

Focused VC6 result: **85.13%**, 707/712 candidate/target instructions, prefix
16/712, with all 68 relocation operands audited and clean. The remaining gap is
local color/blend lifetime and x87 argument scheduling, not missing behavior.

The matcher source now uses the authored `Draw` method and exact VC6 symbol
`?Draw@cRBorder@@QAEXXZ`; `draw_frontend_widget` remains only the stable scratch
and Windows-address identity.
