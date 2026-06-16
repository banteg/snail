# parse_next_signed_int

Initial scratch for the resource/level numeric token parser at `0x44e710`.

Recovered relationships:

- Advances the caller cursor until it finds `-`, `+`, `.`, or an ASCII digit.
- A leading `-` flips the sign and is consumed; leading `+` and `.` are
  recognized as scan terminators but are not consumed by the sign block.
- Accumulates base-10 digits using the same `value * 10 + digit - '0'` idiom as
  the exact lower-level `parse_next_int32` helper.

Focused Wibo result: 28.87%, 50/47 candidate/target instructions, no masked
operands. The semantic phases match BN, but native keeps the cursor owner in
`ecx` across the pre-scan and digit loop while the current source lets VC6
choose `edx`.
