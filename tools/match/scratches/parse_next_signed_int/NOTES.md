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

2026-06-20 parser-family cursor pass: spelling the caller cursor's pointee as a
loop-carried `current` pointer improves focused Wibo to 32.99%, still 50/47
candidate/target instructions and no masked operands. The source remains the
same semantic parser: scan to `-`, `+`, `.`, or a digit, consume a leading
minus, accumulate decimal digits, and leave the caller cursor after the token.
The improvement comes from using `current` for the sign gate and digit loop,
which reduces some cursor reload mismatches. The remaining residual is honest
source shape: VC6 now saves `esi`/`edi` at entry and keeps the caller cursor in
`esi`, while native delays those saves until after the pre-scan and keeps the
caller cursor in `ecx`. Narrower owner-alias rewrites compiled back to the old
28.87% object; related classifier/TGA/archive-entry cursor probes were neutral
or regressed, so no shared parser/header change was accepted.

2026-06-20 larger-helper pass: a more literal decompiler-style `**cursor`
pre-scan plus scoped digit-loop cursor regressed to 25.49% and introduced an
extra saved register. The retained loop-carried `current` source remains the
best observed parser shape.
