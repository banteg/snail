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

2026-06-20 native cursor rewrite: focused Wibo improves to 65.00%, with 57/63
candidate/target instructions and 4 clean masked operands. IDA shows the first
argument is the pattern and the second argument is the searched cursor, and the
success return points into the second argument. Rewriting the scratch around
that ownership, then spelling the inner scan as a preincremented pattern cursor
with a `haystack_cursor - needle` delta, recovers the native compact scan shape.
The remaining residual is the prologue/cursor ownership: native loads the
searched cursor and its first byte before saving registers, while VC6 still
saves registers first. A direct mutation of the `haystack` argument regressed to
34.11%, so the retained source keeps the separate `haystack_cursor` local.

2026-06-20 larger-helper pass: spelling the inner loop as the IDA-style
postincrement condition `(needle_cursor++)[delta + 1]` regressed to 39.39% by
adding a stack temp, `push ecx`, and a wider branch tail. The existing
preincrement-plus-break loop remains the only accepted compact scan shape.

2026-06-21 resource-string family pass: two plausible source-shape probes were
rejected. Holding the outer searched byte in a local to mimic native's
pre-prologue first-byte read regressed to 63.41% and introduced a stack byte
spill. Rewriting the inner scan as a preincremented `while
((++needle_cursor)[delta] != 0)` condition also regressed to 39.39%, landing in
the same stack-temp family as the previous postincrement probe. Keep the
current 65.00% explicit preincrement-plus-break source; the remaining prologue
and inner-success tail differences are scheduler/control-flow layout debt.
