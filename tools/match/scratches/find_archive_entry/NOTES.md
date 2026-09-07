# `find_archive_entry` recovery notes

Target: `find_archive_entry @ 0x431250` (`cdecl`, `ret`).

Scans the loaded archive-index record array for a path match. The archived path
is already uppercase; the requested path is uppercased one byte at a time while
comparing.

The native not-found path is shared for the missing-index, non-positive-count,
and exhausted-loop cases. The source uses explicit `goto` labels to preserve
that control-flow shape without introducing fake dependencies.

Earlier retained Wibo result: 66.12%, 60 target instructions vs 61 candidate
instructions, with two clean masked global references. The semantic blocks were
all present, but VC6 laid out the candidate not-found block after the found
return and chose the opposite `ecx`/`edx` split for the archive cursor and
current archive character. The uppercase conversion also emitted equivalent
`add al, 0xe0` instead of native `sub al, 0x20`.

Rejected/no-op variants:

- Structured `do/while` source compiled identically to the retained goto form.
- `unsigned char` fixed neither the layout nor arithmetic encoding and changed
  the signed `jl`/`jg` range tests to unsigned branches.
- Splitting cursor/character initialization and spelling the subtraction as
  `requested_char = requested_char - 32` did not improve codegen.

2026-06-20 archive-cursor retry:

- Rerun baseline stayed at 66.12%, 61/60 candidate/target instructions, with
  the same two clean masked global references.
- Initializing `archive_cursor` before `requested_cursor` was codegen-neutral;
  the candidate still keeps the archive cursor in `ecx` and the archive byte in
  `dl` while native uses `edx` plus `cl`.
- Replacing the shared `not_found` label with direct `return 0` exits compiled
  identically, so the explicit label remains the clearest source for the native
  shared not-found semantics.
- The residual matches the classifier helper's register-owner pattern rather
  than a local block-layout spelling issue.

2026-06-21 direct archive-byte pass:

- Rewriting the inner loop to compare `*archive_cursor` directly instead of
  carrying a named `archive_char` local recovers native's archive cursor and
  byte owner (`edx` plus `cl`) and raises focused Wibo to 79.34%, with 61/60
  candidate/target instructions and two clean masked global references.
- Lowercase conversion still emits the equivalent `add al, 0xe0`; `-= 0x20`,
  nested range checks, an intermediate `upper` local, and integer/unsigned byte
  variants were neutral or regressed.
- Explicit `entry_index >= count`, direct `return 0`, and found-before-not-found
  tail spellings all preserve the same found/not-found block layout, leaving
  the native shared not-found fallthrough as the main residual.

## 2026-07-25 lookup lifetime replay

Binary Ninja and IDA now retain the archive index, entry-count snapshot, entry
index, requested path, typed `ArchiveEntry*` cursor, both byte cursors, and
their current character values. Binary Ninja still exposes the physical
compiler spill used for the entry-count snapshot; that is an honest stack
lifetime rather than a second semantic count owner.

This is analysis-only and leaves the focused result at 79.34%, 61/60
instructions, a 7-instruction prefix, and two clean masked references. The
remaining differences are the shared not-found block placement and equivalent
ASCII-fold instruction encoding.

## 2026-09-07 search-loop operation probes

Sixteen recorded variants compare nested and early-exit for/do searches,
returning at the successful entry, and char/int uppercase expressions with
or without an inline operation. None improves the retained 79.34% result.
Early-exit do loops with a char expression or inline char conversion are
byte-identical to the baseline. The other tested forms regress. The recipe
is `lookup-loop-operation-20260907.json`; this does not establish source-shape
exhaustion or compiler provenance.
