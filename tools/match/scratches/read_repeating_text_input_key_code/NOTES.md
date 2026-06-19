# read_repeating_text_input_key_code

First scratch for `read_repeating_text_input_key_code @ 0x4327e0`.

The helper maps held DirectInput scancodes to the same text-input byte codes as
`read_pressed_text_input_key_code`, then applies the native autorepeat state:

- `g_text_input_repeat_accumulator` gates the initial held-key delay;
- `g_text_input_repeat_step` controls the later repeat cadence;
- `g_text_input_last_repeat_code` is compared case-insensitively so shifted
  letters do not reset the held-key lane.

The source keeps the native two-byte shape: `result` is the active return code,
while `repeat_code` preserves the pre-repeat comparison byte.

## Current match notes

Focused matcher result: 99.09%, 440 candidate instructions versus 440 target
instructions, 386-instruction prefix, and 73 clean masked operands.

Swapping the operands in the case-fold equality is source-equivalent and nudges
VC6 toward the native comparison order, reducing the repeat-tail residual
without changing the autorepeat behavior.

Remaining residuals:

- Enter/Ctrl byte-code addition: native widens the final add to `ebx`, while
  clear byte-shaped source compiles as the equivalent `add bl, 5`.
- The repeat comparison still loads `g_text_input_last_repeat_code` before the
  stack `repeat_code`; a named `char` temporary fixed call order but worsened the
  preservation register, and an `int` temporary or subtraction-style comparison
  changed the stack frame. Leave those variants rejected.
- 2026-06-19 repeat-tail audit: the exact sibling
  `read_pressed_text_input_key_code` still matches 100.00%, 338/338, with 55
  clean masked operands. Focused Wibo for this repeat helper remains 99.09%,
  440/440, 386/440 prefix, and 73 clean masked operands. Swapping the
  case-fold equality operands regresses to 98.86% by changing only the final
  compare. A named folded-repeat byte recovers the native call order but
  regresses to 98.75% because VC6 preserves the first folded value through a
  stack byte instead of `dl`; widening that temporary to `int` changes the
  frame and collapses the prefix. Widening the top-level `result` to `int`
  also collapses the prefix by turning every `mov bl, imm8` into `mov ebx,
  imm32`. Enter/Ctrl variants using direct result assignment, a single
  expression, assignment through `repeat_code`, or swapped result/repeat stores
  are all codegen-neutral and keep `add bl, 5`. Keep the current byte-shaped
  baseline.
