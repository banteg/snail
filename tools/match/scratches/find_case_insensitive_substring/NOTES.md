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

2026-06-20 larger case-folding pass: focused Wibo improves from 65.00% to
69.29%, with 64 candidate instructions versus 63 target instructions and 4
clean masked operands. The retained source makes the inner termination explicit:
when the searched string ends before the pattern, return null immediately;
when both cursors end together, return the current searched cursor. That matches
the native semantics more closely than the old `break` plus post-loop
`*needle_cursor` test. Rejected followups: sharing null or success epilogues
regressed to 65.55%, the IDA-style postincrement condition plus explicit null
return regressed to 60.32%, and moving the searched cursor local inside the
outer non-empty guard or spelling the outer loop as `do/while` was codegen
neutral. The remaining debt is still the native pre-prologue searched-byte load
and VC6's branchless select for the adjacent null/success returns.

2026-06-20 larger helper sweep: focused Wibo still reports 69.29%, 64/63
candidate/target instructions, 0/63 prefix, and four clean masked operands.
Inverting only the inner `needle_cursor[delta] == 0` success/null test was
codegen-neutral: VC6 still selected the same branchless pointer-or-null tail
instead of native's explicit searched-ended-before-pattern branch. Keep the
current explicit termination source; the remaining gap is tail layout and the
pre-prologue searched-byte load, not a different substring semantic.

2026-06-21 split-zero retry: separating the searched-ended-first null return
from the both-cursors-ended success return, without naming a byte temporary,
moves focused Wibo to 71.43%, with 63/63 instructions, an 8/63 prefix, and four
clean masked operands. This recovers native's initial searched-pointer load and
first-byte test before the saved-register block. A named `haystack_value` local
also recovered the prologue but regressed to 66.67% by spilling the byte; a
double-test/`else` spelling fell back to the old branchless select at 69.29%.
The retained residual is now the inner success tail: native keeps the searched
byte in `al` and branches directly back to the compare loop, while the scratch
emits an extra post-compare pattern-ended check.
