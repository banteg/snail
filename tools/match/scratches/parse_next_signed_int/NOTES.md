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

2026-06-20 parser-family owner-read pass: a hybrid source shape improves
focused Wibo to 70.10%, still 50/47 candidate/target instructions and no
masked operands. The accepted shape scopes the pre-scan `current` pointer but
spells the caller-owned character reads as `**cursor`, then uses the exact
`parse_next_int32` digit-loop idiom for the sign/digit tail. The related
`parse_next_float32` scratch accepts the same pre-scan owner-read idiom, so this
looks like a real parser-family source pattern rather than a one-off nudge.

Rejected/neutral probes in this pass:

- Adding a separate `initial = *cursor` gate before the pre-scan compiled
  identically to the retained 70.10% object.
- Rechecking `**cursor != '-'` in the do/while tail regressed to 69.39%.
- A `for (;;)` pre-scan with explicit `continue` compiled identically to the
  retained object.
- Reading the pre-scan byte as `*current` regressed to the old 28.87% family.

Remaining residual: native emits a distinct first `eax = *cursor; cmp [eax],
'-'` gate before loading the loop cursor in `edx`, while VC6 folds that first
minus check into the loop byte in the retained source. Native also delays the
`esi`/`edi` saves until after the pre-scan; the accepted source still leaves
three extra candidate instructions.

2026-06-20 numeric parser pre-scan pass: focused Wibo is now exact, 100.00%,
47/47 instructions, with no masked operands. The accepted source spells the
pre-scan as `while (**cursor != '-')`, but reads the classifier byte through
the scoped `current` pointer. That preserves the native first `eax = *cursor;
cmp [eax], '-'` gate, keeps the loop cursor in `edx`, and still delays the
`esi`/`edi` saves until after the scan. Intermediate probes were informative:
an explicit `goto after_scan` first gate and a first-byte local were both
codegen-neutral at 70.10%, while the `while` form with owner-read `**cursor`
improved only to 75.79% because VC6 inserted `mov eax, edx` before loading the
classifier byte.
