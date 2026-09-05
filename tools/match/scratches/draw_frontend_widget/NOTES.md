# cRBorder::Draw @ 0x401130

Current recovery: semantic-complete (`analysis` residual). The Windows body is
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

## 2026-09-05 paired shadow-dimension lifetimes

Six complete shadow-width/height forms stage both dimensions after the color
call, in either order, using sums, compound additions, or a reused edge local.
All compile with 68 clean references but regress from 99.72% to 98.46–98.74%.
They do not recover the remaining width operand order without disturbing
neighboring argument setup. Canonical source is unchanged.

## 2026-09-05 shared sprite/shadow scalar lifetimes

Four combinations reuse the ordinary sprite padding and reload either the
existing sprite-edge variable or a fresh edge after the shadow-color Set
call. Padding reuse alone is neutral at 99.72%; the post-Set edge snapshots
give 98.74%, prefix 234, with all 68 references clean. They do not improve
the current source, and none is retained.

The otherwise surprising four constructor calls at function entry are also
present in the Android 0x5f5b0 and iOS 0x391a0 Draw exports, including the two
alpha assignments in the render-mode branch. Their presence is independently
supported; the unnamed prologue colors are not removed based only on their
limited later use in the Windows body. This check does not establish a new
shared color constructor or return contract.

## 2026-09-05 continued 590-match investigation

Four shadow-width precision forms (edge, width, both operands, or the completed sum promoted to double) are neutral at 99.72%, prefix 253, with 68 clean references. No source change is retained.

These receipts bound the tested forms and do not establish source exhaustion.


## 2026-09-05 diagnostic-export batch

Twelve paired normal/shadow dimension forms test whole-operation lifetimes: separate or reused width/height values, sums, compound updates, and edge snapshots. All compile with 68 clean references but regress to 67.46–69.00%, losing the native prefix at instruction 16. Raw code identities collapse the twelve forms into four groups. The regression begins well before the shadow call; it is not a repair of the shadow width in isolation. No source is retained.

The remaining native difference is still the shadow call's `fld [esi+0x258]; fadd [esi+0x250]` versus the reversed source loads. The original sprite/frame recovery remains intact at 99.72%.

The receipts bound these hypotheses only. No new exact match or unsupported ownership/return contract was inferred.
