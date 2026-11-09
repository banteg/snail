# cRBorder::InputText @ 0x4035b0

## 2026-11-09: empty-submission policies across builds

The iPad 1.0.6 executable (SHA-256
`5960c4e4ea8a9636ae651da2e2b245c1afe100ecd957be83a87ace269536fcf4`)
retains a third completion path. In `InputText` at `0x2e66c`, the code
decrements the length, clears the active bit, then loads `text[0]` at
`0x2e76e`. An empty string branches at `0x2e774` to ordinary editor
postprocessing. Only a nonempty string sets the completion bit and calls
layout and optional button teardown. Wii restores the saved name on its
empty path. Both iPhone 1.9 slices publish completion unconditionally after
clearing the active bit (ARMv6 `0x3938c..0x393b0`, ARMv7
`0x39f8c..0x39fb0`).

Two Windows games using the same editor distinguish an optional copy from the
common completion operation. Chromadrome 1.00 tests the first character at
`0x403af6`; on empty, it copies the saved name to the edit buffer at
`0x403b10`. Both paths converge at `0x403b1e` to publish completion, call
layout and tear down the button. Chromentum 1.10 copies only on the empty
path (`0x403330..0x403343`), then converges at `0x403346`.

The RealArcade Windows predecessor (SHA-256
`4dbc39d84a00bc18dd0469cd82e29794e5e33d15c6d1b2e90fb27679faec6260`)
also retains the first-character load at `0x403b91`. Its entire editor
extent differs from the Reflexive target by two relocated operand bytes.
The native execution comparison now includes the high-score callers' actual
mode `0x10` and capacity 16. Across all 28 empty submissions in that mode,
the target leaves the text empty, clears `ACTIVE`, sets `COMPLETE`, and
calls layout, including 14 cases with a nonempty saved name at `+0x6cc`.
All 43,776 editor fixtures match the reconstructed behavior
across 117,346 callbacks.

The iPad also has a cursor-removal helper at `0x2f4f0` that clears
`ACTIVE`. An equivalent inline helper in the Windows whole-unit control
gives 440/446 instructions and still omits the first-character load. A
cursor-removal-only helper is neutral. Sharing the first-character read
between submission and the ordinary numeric filter also fails to reproduce
the native code. Specializing an optional saved-name operation with a null
fallback removes both the copy and the load under VC6 SP3, leaving the
canonical 443/446 instructions with the same flag stores. The platform
evidence locates the read at the historical
acceptance decision, but the Windows source form remains unresolved.

## 2026-11-09: numeric trim buffer and empty submission

Numeric trim keeps a single pointer to the text buffer for its test, removal
and advance. On Wii, `0x80020098` forms the buffer base and the loop uses it
for both the indexed character load and the removal pointer at
`0x800200f0..0x800200f4`. With the same owner, VC6 SP3 emits native SIB
`31` at offsets `+1252` and `+1259`. Those two bytes are the only changes
to the compiled editor. All 34 other Border members retain their instruction
bytes and scores. Two exact peers have renumbered local jump labels.

The Wii completion path independently explains a use for the first character.
After removing the cursor, it loads the first character at `0x8001f838`,
decrements the length, clears the active bit and branches at `0x8001f858`.
For empty text it copies the saved name back, marks input complete and jumps
to the ordinary input postprocessing. For nonempty text it marks input
complete and runs layout and optional OK-button teardown. Wii's initializer
saves the fallback with the same string-copy function. This can be checked
in the US DOL, SHA-256
`523f848f2a0b8ef8c9dfe2714744bf0479a4feec79b25f0d1f5e035a6487c096`.

The Windows initializer also saves a string, at `text_buffer + 0x400`.
At submission the retail Windows image loads the first character at
`0x403b91`, and the separate Shockwave demo does so at `0x403ac1`. In both
Windows builds empty submissions retain the empty text and take the same
layout and teardown path as nonempty submissions. Android and iOS also
publish completion unconditionally. The Wii fallback would change Windows
behavior. Duplicating completion in identical arms merely to retain a load
would invent a distinction in the reconstructed program.

The current whole-unit build has **443/446 instructions**, **98.99%**
agreement, a **423-instruction prefix** and eight clean references. The
remaining differences are in completion. The native comparison runner
checked 35,568 editor cases with 100,930 callbacks and zero state or callback
differences. Its one-byte corruption control identified the changed case
and byte.

## 2026-10-18: identical-arm branch on `text_buffer[0]` reproduces the store pair

Unchanged at **98.99%**, 443/446, prefix 423, in the whole Border unit.

The completion residual is native's dead `mov cl, byte [esi+0x2cc]` between
the flag stores, with the first `widget_flags` store kept. A read of
`text_buffer[0]` that C1 or early C2 drops does not reproduce it. All of these
are byte-identical to the current source:

- an empty `if (text_buffer[0] == 0) {}`, before or after `--input_length`;
- `(void)text_buffer[0];` and an unused `char first = text_buffer[0];`;
- dead assignments to the function-scope `final_character`, `key` or
  `insertion_end`;
- `switch (text_buffer[0]) { default: ... }`;
- `input_length -= text_buffer[0] != 0 ? 1 : 1;`.

A branch whose two arms stay identical until the late cross-jump does
reproduce it. `if (text_buffer[0] != 0) --input_length; else --input_length;`
keeps both `widget_flags` stores and the `mov cl, byte [esi+0x2cc]` load,
scheduled ahead of the first store as in native. That confirms that native's
IL holds a char read between the stores until after dead-store elimination.
The form also leaves a dead `test cl, cl`, which native lacks. It moves the
whole function off `edi` (`push edi` is gone, prefix 2), at 93.14%, 443/446.
The same holds with the branch on `== 0`, around the second store, around
both statements, as `switch (text_buffer[0]) { case 0: ... default: ... }`,
or as an always-true `||` condition (93.03–93.24%).

So native's read is in the IL and then disappears without a test or branch,
and costs no global register. The construct is still unknown. No source
change.

## 2026-10-16: msvc6.3 whole-TU retest, two-flag OK-placement test

**98.76% -> 98.99%**, 443/446 instructions, prefix **6 -> 423**, eight clean
references, compiled inside the Border translation unit.

- **Opening load width (fixed).** `(input_flags & 4) != 0 || (input_flags & 8) != 0`
  compiles to native's `mov eax, dword [esi+0x70c]; test al, 0xc`. The single
  mask `(input_flags & 0x0c) != 0` narrows to `mov al, byte [...]`. C2 still
  merges the two bit tests into one `test al, 0xc`, but keeps the dword load
  (not traced). The spelling is plausible source: `cRInputOK::AI` tests the same two bits
  separately (4 places OK to the right, 8 to the left). The teardown test
  compiles to native's `test byte [esi+0x70c], 0xc` with either spelling, so
  both sites now use the two-flag form. Neutral: a named `mode` copy, an
  `int ok_mode = input_flags & 0x0c` local, `if (input_flags & 0x0c)`;
  `(int)(input_flags & 0x0c) > 0` regresses to 98.54%.
- **Completion staging (simplified, byte-identical).** The three staged
  temporaries become mobile's shape: `flags = widget_flags; widget_flags =
  flags & ~ACTIVE; --input_length; widget_flags = (flags & ~ACTIVE) | COMPLETE`.
  The normalized listing is identical to the staged form. Compound `&=`/`|=`
  forms and a single `flags & ~ACTIVE` local both change the prologue
  allocation (`mov esi, ecx` at 2) and regress to 92.33% and 93.23% (440 instructions).
- **Still open.** Native keeps the first `widget_flags` store and a dead
  `mov cl, byte [esi+0x2cc]` (`text_buffer[0]`) between the stores. Ours
  eliminates the first store. A `char` read between the stores is what would
  block that elimination (it may alias), but no source construct that reads
  `text_buffer[0]` and discards it reads as authored code. Not added.

## 2026-09-11: shared insertion and Home recovery

Current agreement is **98.76265467%**, **443/446 instructions**, prefix **6**,
with **eight clean references**. Shared terminal insertion publication,
displaced-character lifetimes and Home insertion through the published cursor
improve the previous 75.25423729% source. Four local encoded certificates cover
**1,514/1,581 body bytes**. The opening load width, two hidden SIB differences
and completion publication remain different; the function is still partial.

The [report and complete receipt](../../border-input-insertion-home-owners-20260911.md)
preserve source controls, reversals, exact byte ranges and references, and a
**35,568-case native comparison** of complete widget contents and callback order
at explicit harness seams. All 1,104 tests and 785 scratch checks pass.

### Earlier observations

The entries below describe historical source versions. Their current-result
figures and compiler-residual labels are superseded above. Finite experiments
do not establish a compiler limit.

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
