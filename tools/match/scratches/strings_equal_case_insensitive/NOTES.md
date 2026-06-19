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
