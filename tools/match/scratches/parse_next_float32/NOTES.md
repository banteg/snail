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

2026-06-20 follow-up after proving `parse_next_signed_int`: focused Wibo remains
63.57%, 65/64 instructions, with 9 clean masked operands. Retesting the signed
integer pre-scan with an explicit `owner` local still regressed to 36.51% by
moving the caller cursor owner to `eax`. Decimal-loop probes also did not land:
the decompiler-style combined non-digit/non-dot rejection regressed to 63.24%
by duplicating the dot block, the cleaner range-first branch reproduced the
known 58.91% regression, and reading the decimal-loop byte as `*current` was
codegen-neutral. Reading the pre-scan classifier as `*current` under the
retained `if`/`do` shape regressed to 43.41% by moving the owner to `edx`. Keep
the current dot-first decimal loop and owner-read pre-scan.

2026-06-20 parser/resource helper retry: focused Wibo still reports `63.57%`,
`65/64` candidate/target instructions, `1/64` prefix, and nine clean masked
operands. Naming only the initial `char* initial = *cursor` before the
pre-scan guard is codegen-neutral: VC6 still folds the first owner read into
`edx` instead of native's separate `eax = [ecx]` / `cmp byte [eax], '-'`
sequence. The retained source remains the best known float-specific shape; the
first mismatch is still cursor-owner register allocation, not a missing
semantic pre-scan branch.

## 2026-07-12 exact parser source recovery

The preserved iOS and Android symbol is `Rstrfloat(char**)`, and the Android
body confirms the same sign/dot/digit scan, decimal accumulator, scale, and
caller-owned cursor contract. The Windows parser uses the same authored
pre-scan shape as the already-exact signed-integer parser: a
`while (**cursor != '-')` loop whose classifier byte comes from the scoped
current pointer. Expressing the decimal body as a real `digit-or-dot` loop
condition then preserves native's range checks and shared dot body instead of
duplicating the decimal-point arm.

Within the digit arm, accumulating the parsed digit before advancing the
caller-owned cursor recovers native's `eax` digit temporary while the current
text pointer remains live in `edx`. Together these source changes raise the
focused result from 63.57% (65/64 instructions, prefix 1) to **100.00%**,
64/64 instructions, with all nine masked operands clean.

The earlier decompiler-shaped `if` plus `do/while` pre-scan had allowed VC6 to
fold away the distinct leading-minus test. A combined rejection expression
for non-digits and non-dots also duplicated the dot body; neither form is
retained. The exact source has no volatile locals, dummy branches, or other
code-generation coercions.
