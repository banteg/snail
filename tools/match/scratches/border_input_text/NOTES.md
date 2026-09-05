# cRBorder::InputText @ 0x4035b0

Current recovery: semantic-complete (`compiler` residual). Binary Ninja types
the Windows entry as `void __thiscall(FrontendWidget*)`, and its sole Windows
caller ignores `eax`. Android and iOS independently retain the same owner and
method as `cRBorder::InputText()` in `Border.o`.

The recovered body covers autorepeat key dispatch, cursor-marker swaps,
insertion/deletion, separator-aware movement, numeric and space filters, blink
and relayout, completion publication, and optional `cRInputOK` teardown. The
mobile bodies corroborate the editor-state field order despite their shorter
platform prefix.

Focused VC6 result: **74.80%**, 439/446 candidate/target instructions, prefix
6/446, with all eight relocation operands audited and clean. Remaining
differences are register rotation and duplicated shift-loop scheduling; no
missing editor branch is known.

The matcher source now uses the authored `InputText` method and exact VC6 symbol
`?InputText@cRBorder@@QAEXXZ`; `border_input_text` remains only the stable
scratch and Windows-address identity.

## 2026-09-05 text-shift operation and carry lifetimes

The current shared-header baseline is 75.25%, 439/446 instructions, prefix 6,
and eight clean references. Its low fuzzy percentage includes many displaced
branch targets: the full comparison has small non-branch gaps at the opening
flag load, two character-rotation loops, Home movement, and completion.

Eight deletion/cursor-shift helper combinations and three consumed-key carry
forms are neutral. Four staged-displacement/pointer-owner rotations and two
returned-character operations are neutral or worse. Three final-character
publication forms also regress. The latter follow the separate loop-carried
and final-output values visible in both Windows and the Android newline
branch, but still do not reproduce the Windows compilation. No helper or
character temporary is retained.

Native retains extra carry copies in the two insertion arms and, at completion,
a redundant first-character load plus separate cleared/final flag publication.
The current source does not recover those instructions. Mobile has additional
capitalization behavior on its ordinary path; importing it into Windows or
adding an unused load solely to reproduce bytes is not justified. These are
source-recovery questions, not proof of an irreducible compiler residual.
