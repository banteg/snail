# find_case_insensitive_substring

Initial scratch for the case-insensitive metadata/tag scanner at `0x44e600`.

Recovered relationships:

- Used broadly by X-mesh, animation, landscape, level, segment, and voice
  parsers.
- Calls the exact `ascii_upper_if_lowercase` helper for each compared byte; it
  is ASCII-only and does not call CRT substring helpers.
- Returns a pointer into the searched string when the pattern is found, or null
  otherwise. The current source is intentionally relationship-first because the
  native nested scan has unusual branch layout.

Focused Wibo result: 25.71%, 77/63 candidate/target instructions, with 2 masked
operands OK. The source maps the helper calls and return semantics, but native
loads the haystack pointer before saving registers and keeps a compact
`haystack - needle` delta across the inner scan.
