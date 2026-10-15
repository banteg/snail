# cRBorder::InputText @ 0x4035b0

## 2026-10-15: 100% byte-exact under msvc6.3

Result: **100.00% proof-grade byte-exact** (`446/446` instructions, prefix
`446`, `body_byte_exact = true`, `8/8` masked operands clean) under `msvc6.3`.

- Binding `cRInputOK* ok = input_ok_state()` before the `input_flags` check
  promotes `input_flags` (`[esi+0x70c]`) to a 32-bit CSE temporary in `eax`
  (`mov eax, dword ptr [esi+0x70c]; test al, 0xc`) while keeping `lea ecx,
  [esi+0x2a8]` ahead of the branch so `C2+0x3465c` tail-merges `ok->AI()` and
  `C2+0x36566` eliminates `test eax, eax` + `je`.
- Declaring `char* buf = text_buffer;` before `int index = 0;` in the numeric
  filter loop assigns `buf` (`local slot 0x133`, cost `0x12660`) as the CSE
  holder in `C2+0x10bfe` (`[eax+0x14] != 0`) so `index` (`local slot 0x134`,
  cost `0x12680`) outranks `buf` in `C2+0xf349`, producing `[ecx+esi+0x2cc]` at
  both `mov dl, byte ptr [ecx+esi+0x2cc]` and `lea eax, [ecx+esi+0x2cc]`.
- Ordering `--input_length;` before `widget_flags &=
  ~FRONTEND_WIDGET_FLAG_TEXT_INPUT_ACTIVE;` and the `text_buffer[0] != 0`
  completion branch gives `input_length` `edi` and `widget_flags` `edx`/`eax` in
  the local allocator, while `/G5 memory-operand split` (`C2+0x31e76`) and
  `C2+0x3465c` leave the orphaned `mov cl, byte ptr [esi+0x2cc]` before `or ah,
  0x40`.
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
