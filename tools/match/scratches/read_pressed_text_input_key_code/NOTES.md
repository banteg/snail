# read_pressed_text_input_key_code

First scratch for `read_pressed_text_input_key_code @ 0x432440`.

The helper maps newly pressed DirectInput keyboard scancodes to the shared
frontend text-input byte codes:

- letters `a` through `z`, uppercased when either shift key is down;
- space, digits, comma, period, apostrophe, and backslash;
- edit/navigation control codes used by border text editing and frontend
  shortcuts;
- Enter returns `5` or `6` depending on whether Ctrl is held.

The native keeps the accumulated byte in `bl`; this source keeps the same
single `char result` shape and leaves the exact keyboard edge/down helpers as
calls.

## Exact match notes

Focused matcher result: 100.00%, 338 candidate instructions versus 338 target
instructions, full 338-instruction prefix, and 55 clean masked operands.

The final Enter/Ctrl tail must normalize the Ctrl key-down result through a
`char ctrl_down` local before adding `5`. A full-width `int` normalization
compiled to a `neg`/`sbb` boolean idiom, while directly adding the helper result
left the raw byte in `eax`. The byte local recovers native `test al; setne al`
without barriers or fake temporaries.
