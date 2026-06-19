# `find_archive_entry` recovery notes

Target: `find_archive_entry @ 0x431250` (`cdecl`, `ret`).

Scans the loaded archive-index record array for a path match. The archived path
is already uppercase; the requested path is uppercased one byte at a time while
comparing.

The native not-found path is shared for the missing-index, non-positive-count,
and exhausted-loop cases. The source uses explicit `goto` labels to preserve
that control-flow shape without introducing fake dependencies.

Current retained Wibo result: 66.12%, 60 target instructions vs 61 candidate
instructions, with two clean masked global references. The semantic blocks are
all present, but VC6 lays out the candidate not-found block after the found
return and chooses the opposite `ecx`/`edx` split for the archive cursor and
current archive character. The uppercase conversion also emits equivalent
`add al, 0xe0` instead of native `sub al, 0x20`.

Rejected/no-op variants:

- Structured `do/while` source compiled identically to the retained goto form.
- `unsigned char` fixed neither the layout nor arithmetic encoding and changed
  the signed `jl`/`jg` range tests to unsigned branches.
- Splitting cursor/character initialization and spelling the subtraction as
  `requested_char = requested_char - 32` did not improve codegen.
