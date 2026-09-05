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

## 2026-09-05 frame and slider value ownership

The old `compiler` attribution is withdrawn. Native Draw preserves the original layout dimensions for its slider and separately selects the dimensions of the later frame inside each inset branch. The former scratch mutated one shared width/height pair and initialized frame coordinates before the branch. Recovering the separate base and frame values together with live slider-position reads improves 85.13% to 99.30%, with exact 712/712 instruction count and all 68 references clean. Testing live slider reads alone looked worse (70.56%) because it changed allocation in the still-wrong frame model; the coupled recovery demonstrates why that isolated score was not evidence against the source shape.

Publishing blend mode after the two alpha assignments extends the prefix to 211 and reaches 99.44%. A local edge value for the ordinary sprite width then restores that argument's native x87 addition order, giving 99.72%, prefix 253, and the same exact instruction count and clean references. The only remaining difference is the commuted width addition in the optional shadow draw. Fourteen sprite-width/mode combinations, twelve padding expressions, nine edge borrows, and six shadow-edge lifetime forms are recorded; no higher-scoring form with a metric tradeoff is retained. The shadow expression remains open.

Seven shadow-edge reference, pointer, and inline getter probes are byte-neutral at 99.72%. The exact sprite-width addition can be recovered through the earlier edge-value lifetime; these borrowed shadow-edge forms do not recover the remaining operand order. No helper or borrow is retained.

## 2026-09-05 operation-boundary checks

Nine shadow-dimension helper forms test scalar value, reference and pointer arguments for expanded width, height or both. They regress from 99.72% and disturb much earlier allocation. No helper is retained; the two-instruction shadow-width operand-order difference remains open.
