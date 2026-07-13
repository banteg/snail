# border_input_text @ 0x4035b0

Starter scratch for front-end inline text editing.

Models the recovered autorepeat key codes, cursor marker movement, insertion,
delete/backspace, word-ish moves across `>` separators, numeric/space filter
flags, blink timer, layout refresh, and OK-button finalization. It uses raw
widget offsets matching `border_input_text_init`.

2026-06-20 ABI cleanup:

- Replaced the scratch-local `InputOkState::update_input_ok()` `int` stub with
  `include/input_ok_state.h`; the exact `update_input_ok` and
  `initialize_input_ok` scratches prove the `FrontendWidget*` return.
- Replaced the scratch-local `BorderManager::kill_border(void*)` stub with the
  shared `BorderManager::kill_border(FrontendWidget*)` declaration.
- Focused matcher stayed at 17.77% with 297/446 candidate/target instructions
  and 8 clean masked operands. This removes the `InputOkState` ABI-conflict
  row and contributes to the shared `BorderManager` row cleanup.

## 2026-07-13 editor state and control-flow recovery

The previous `switch` plus four scratch-local convenience helpers compiled as
a jump table and out-of-line calls, shrinking the candidate to 297 of the
native function's 446 instructions. The native function instead has an
authored `if`/`else if` ladder in key-code order `6, 3, 4, 7, 8, 9, 10, 1, 2`
and duplicates each character-shift loop inline. Recovering that structure
raises the focused Wibo score from 17.77% to 64.64%, with 442/446 instructions
and all eight masked operands clean.

Key code 6 also has a non-obvious filter relationship: flag bit 1 makes it
fall through to ordinary character filtering rather than suppressing the key,
while flag bit 2 suppresses newline insertion. The previous switch could not
express that fallthrough correctly. The vertical and separator moves now
follow the native scan/update order, including the next-line cursor expression
`separator + column - 1`.

The final lanes before the child-widget union are now typed as one editor state:

- `+0x6fc` cursor index;
- `+0x700` cursor visibility;
- `+0x704/+0x708` blink progress and step;
- `+0x70c` input/filter flags;
- `+0x710/+0x714` current length and capacity.

The exact `border_input_text_init` and `update_input_ok` siblings independently
corroborate these owners and remain 46/46 and 32/32 instructions. Remaining
debt is ordinary prologue/register allocation and local shift-loop scheduling;
no volatile locals, dummy operations, barriers, or pointer fakematching were
retained.

## 2026-07-13 tooltip-tail overlay ownership

The conditional OK-button controller is an exact 0x24-byte `InputOkState`
view beginning at widget `+0x2a8`, inside the 0x40-byte interaction block at
`+0x28c`. Its `source_widget +0x1c` and `ok_widget +0x20` therefore occupy the
last two pointer lanes at widget `+0x2c4/+0x2c8`. `FrontendWidget::input_ok_state()`
centralizes that proven overlay instead of repeating raw interior casts.

The editor teardown now reaches the embedded root `BorderManager` directly.
`border_input_text` stays at 64.64% with 442/446 instructions and eight clean
operands; `border_input_text_init`, `initialize_input_ok`, and
`update_input_ok` remain exact at 46/46, 23/23, and 32/32 instructions.
