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
