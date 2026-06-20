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
- 2026-06-20 parser-family owner-read pass: 63.57%, 65 candidate vs 64 target
  instructions, 9 masked operands ok. The accepted source scopes the pre-scan
  `current` pointer but reads classifier bytes through `**cursor`, matching the
  same improvement in `parse_next_signed_int`. Rewriting the decimal loop as a
  dot-first `if` also trims the old duplicated decimal-point branch.

Residuals:

- Same family as `parse_next_signed_int`: native keeps the caller-owned cursor
  pointer in `ecx` and the active text cursor in `edx`, while this natural
  source shape gives VC6 `edx` for the owner and `ecx` for the active cursor.
- The decimal loop semantics match the decompile. The retained dot-first
  source gives the best object so far, but native checks the digit range before
  the decimal-point case and keeps different scratch-register ownership around
  the integer-to-float conversion.

Rejected probes:

- `double` return/locals regressed to 26.47% and changed the native float-width
  constants into qword loads.
- A `cursor_owner` local compiled identically to the baseline and did not move
  the cursor owner into `ecx`.
- A range-first decimal loop matched the native branch story on paper, but
  regressed the object to 58.91% by moving the dot case below the digit arm.
- A staged `digit_value` local was neutral after the dot-first loop; the simpler
  digit expression is retained.
- The exact `parse_next_signed_int` pre-scan idiom does not transfer directly.
  Rewriting this pre-scan as `while (**cursor != '-')` with either a scoped
  `*current` classifier byte or an owner-read `**cursor` regressed to 36.51% and
  36.22% respectively by moving the caller cursor owner from `ecx` to `eax`.
  Keep the retained `if` plus `do/while` pre-scan until a float-specific owner
  lifetime lead appears.
