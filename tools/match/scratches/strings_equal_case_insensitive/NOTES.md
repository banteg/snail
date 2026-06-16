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

Focused Wibo result: 29.13%, 53/50 candidate/target instructions, no masked
operands. The first-pass source has the right semantics, but native keeps the
right string in `esi`, left string in `edi`, and compares folded bytes through
`dl/bl/cl/al` without the current source's pointer-delta loop shape.
