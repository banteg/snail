# strings_equal_case_insensitive

Initial scratch for the shared ASCII case-insensitive equality helper at
`0x431dc0`.

Recovered relationships:

- Used by `get_or_create_texture_ref` and `load_object_definition`.
- Converts only lowercase ASCII `a..z` to uppercase by subtracting `0x20`; it
  is not locale aware and does not call CRT string helpers.
- Returns whether the right cursor reached the null terminator after the
  comparison loop. This means prefix-style matches can succeed when `right`
  ends at the current comparison point.

Focused Wibo result after the peeled-loop rewrite: 66.02%, 53/50
candidate/target instructions, 5/50 prefix, no masked operands. The source now
keeps the prefix-style semantics (`right` reaching NUL is success) while
avoiding the old pointer-delta loop shape.

Remaining residual: native loads the initial right/left raw bytes straight into
`dl`/`bl`, copies them to `cl`/`al`, and tests left then right. The current
source still has VC6 load the fold lanes first (`cl`/`al`), then copy to
`dl`/`bl`, with the same recovered semantics but different byte-lane ordering.

2026-06-20 caller-shape pass: two direct decompiler-shaped rewrites were tested
and rejected. Explicit `left_cursor`/`right_cursor` locals made VC6 collapse the
two pointers into a pointer-delta loop and regressed to 29.13%. A direct
IDA-style `do` loop over the original arguments also regressed to 35.85% by
materializing `sub 0x20` lanes and extra tests. Keep the peeled-loop source
until a source shape preserves the native `dl`/`bl` raw-byte lanes without
introducing the pointer-delta form.

2026-06-20 larger-helper pass: retesting the native left-byte outer gate with
raw-byte locals declared before folded-byte locals regressed to 36.19% by
switching to `sub 0x20` lanes and extra zero tests. Changing only the outer gate
was score-neutral at 66.02% and merely swapped the scratch raw-byte lane roles,
so the retained source stays on the existing peeled-loop spelling.
