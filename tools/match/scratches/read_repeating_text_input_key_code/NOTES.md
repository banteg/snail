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

Focused matcher result: 98.86%, 440 candidate instructions versus 440 target
instructions, 386-instruction prefix, and 73 clean masked operands.

The only remaining semantic mismatch is the Enter/Ctrl byte-code addition:
native widens the final add to `ebx`, while VC6 keeps the clear source addition
on `bl`.
