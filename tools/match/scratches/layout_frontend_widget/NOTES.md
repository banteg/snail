# cRBorder::RePosition @ 0x4024a0

Current recovery: semantic-complete (`compiler` residual). Binary Ninja types
the Windows entry as `void __thiscall(FrontendWidget*)`; all 24 Windows callers
discard `eax`. Android and iOS independently retain the same owner and method as
`cRBorder::RePosition()` in `Border.o`.

The body selects sprite, authored-rectangle, or measured-text geometry; clamps
the hit rectangle unless off-screen placement is allowed; and recursively
repositions the attached slider children. The shared field layout is supported
by the initializers, draw path, mouse path, and mobile bodies.

Focused VC6 result: **99.44%**, exact 177/177 instruction parity, prefix 66/177,
with all 20 relocation operands audited and clean. The sole residual is the
ordering of two independent loads around the first hit-rectangle stores.

The matcher source now uses the authored `RePosition` method and exact VC6
symbol `?RePosition@cRBorder@@QAEXXZ`; `layout_frontend_widget` remains only the
stable scratch and Windows-address identity.
