# parse_next_float32 @ 0x431f20

Initial shape:

- Advances the caller-owned cursor to `-`, `+`, `.`, or an ASCII digit.
- Consumes a leading `-` as the sign; leading `+` and `.` are scan terminators
  but are not consumed by the sign block.
- Accumulates decimal digits into a float value and tracks a decimal scale that
  starts at `1.0` only after seeing the decimal point.

Status:

- 2026-06-18: 44.12%, 72 candidate vs 64 target instructions, 9 masked
  operands ok.

Residuals:

- Same family as `parse_next_signed_int`: native keeps the caller-owned cursor
  pointer in `ecx` and the active text cursor in `edx`, while this natural
  source shape gives VC6 `edx` for the owner and `ecx` for the active cursor.
- The decimal loop semantics match the decompile, but the candidate emits an
  extra duplicated decimal-point branch because of the current high-level
  `(digit range) || '.'` source shape.

Rejected probes:

- `double` return/locals regressed to 26.47% and changed the native float-width
  constants into qword loads.
- A `cursor_owner` local compiled identically to the baseline and did not move
  the cursor owner into `ecx`.
