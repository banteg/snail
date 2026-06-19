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

## Current match notes

Focused matcher result: 99.41%, 336 candidate instructions versus 338 target
instructions, 326-instruction prefix, and 55 clean masked operands.

The only remaining mismatch is the Enter/Ctrl tail. Native normalizes the Ctrl
key-down byte with `test al; setne al` before adding `5`; the clear source
spelling leaves the exact helper's return byte in `eax` and adds `5` directly.
