# Wibble and Invert phase owners (2026-09-13)

Wibble now has a complete 2,213-byte encoded body and Invert a complete 2,182-byte
body under strict positional reference auditing. Both were normalized matches
before this change. The gain is 4,395 byte-exact body bytes; normalized coverage
is unchanged.

Wibble's curve helper owns the current sample's metadata, position, orientation,
and secondary offset through both live sample banks. Invert's existing frame
helper now also owns its secondary offset. Both use the same delta helper shape:
`const int &count`, then the two live bank references, with a physical sample
cursor and a separate logical loop counter. These references retain reloads after
calls and writes; they do not cache a bank pointer or a segment count across
`Normalize`.

Wibble had eight curve SIB-byte differences (540, 547, 564, 642, 668, 672, 676,
735) and five primary-delta differences (901, 908, 912, 967, 982). Invert had
three frame differences (760, 770, 774) and ten delta differences (870, 877, 881,
936, 951, 961, 968, 972, 1027, 1043). Each function's curve-only and delta-only
reversals restore exactly their respective byte groups. Combining the phases
removes all 13 differences in each function.

Source form matters beyond normalized instructions. For example, Wibble's typed
array delta loop introduces five secondary-bank differences, even with explicit
bank references. A bank-first helper argument order leaves five differences;
count-first plus the physical cursor is exact. Invert also needs the smaller
frame boundary: wrapping its entire curve in an additional helper regresses
encoded bytes. The receipt preserves these negative controls rather than
assuming that a useful pattern transfers unchanged to every caller.

These are source hypotheses supported by compilation and independent native
byte proofs, not claims about the original source spelling. There are no changes
to compiler flags, shared headers, reference identities, matchers, or normalizers.

## Evidence and validation

The accompanying JSON contains 40 replayable source controls, forward/reverse
probe records, complete raw bytes and disassembly, independent positional audits,
and the audit script. Wibble has 608 instructions and 39 strict reference fields;
Invert has 600 instructions and 35 fields. Each has 23 unchanged local branches.
Every candidate body relocation is accounted for, and all remaining bytes compare
literally. Their native extents are 2,224 and 2,192 bytes respectively; only the
11 and 10 terminal padding bytes are excluded.

All 785 scratches, 1,140 tests, strict experiment/spec checks, extern lint, and the
exact-reference audit pass. The public proof changes are restricted to these two
source fingerprints and encoded-body fields, apart from COFF timestamps.

```sh
uv run tools/match/replay_four_builder_controls_20260912.py \
  --receipt tools/match/wibble-invert-phase-owners-20260913.json \
  --function initialize_wibble_path_template_pair \
  --batch independent-reversals --label retained --replay
```
