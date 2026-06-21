# classify_archive_entry_extension

- Rebuild helper used while converting `SnailMail.dam` into `SnailMail.dat`.
- Copies the entry name stem before the first dot into the caller buffer.
- Returns `1` for uppercase `TGA`, `2` for uppercase `WAV`, `3` for uppercase
  `MP3`, and `0` for anything else or an entry without an extension.
- `rebuild_game_archive_if_needed` only special-cases the `TGA` class: it writes
  the archived bytes to `0.png`, reloads them through the image path, and emits
  a TGA-style record in the rebuilt archive. The other classes currently fall
  through to the byte-copy path.
- `/Os`-style codegen naturally gives the native opening allocation
  (`eax` input cursor, `edx` output cursor, `cl` byte), but it also emits a
  compact loop/tail-return shape that does not match native. Keep the default
  compiler flags unless a source-shape explanation accounts for both halves.

2026-06-20 larger-helper pass: rewriting the function to the IDA-style
`char* cursor` / direct `stem_out++` loop was score-neutral once the native
`*++cursor` extension shape was restored (26.37%), and the no-increment variant
only reached 26.67% while moving the tail away from native offsets. The raw
`unsigned char*` source remains clearer until a real cursor-register owner lead
appears.

2026-06-20 archive-cursor retry: the focused matcher still reports 26.37%,
45/46 candidate/target instructions, and no masked operands. Reordering the
initial `value`/`output` locals, switching to signed `char`, adding `const` to
the input cursor, spelling the three extension checks as independent `if`
statements, and trying the archive-family C mode (`/TC`) were all codegen
neutral. A direct-dereference stem loop reached 30.77%, but it was rejected
because it stores before advancing/loading the input cursor, unlike the native
`inc eax; mov [edx], cl; inc edx; mov cl, [eax]` loop. Keep the retained source
until a real `eax` cursor / `cl` byte owner lead appears.

2026-06-21 extension-tail retry: focused Wibo improves to 28.26%, with
46/46 candidate/target instructions, by keeping the explicit `++path` but
checking the extension selector as direct `*path` reads. This makes VC6 preserve
the native-style reusable `'A'` byte in `dl` across the TGA/WAV checks. Reloading
the selector into `value` after the increment falls back to the old 26.37% tail,
and `/Os` is still a hard regression despite its attractive opening register
allocation. At this point the first mismatch was the input cursor/value lane:
native used `eax` plus `cl`, while the source kept `ecx` plus `al`.

2026-06-21 primed-loop pass: rewriting the stem copy as a primed
`while (1)` loop with explicit zero/dot breaks recovers the native input cursor
and byte owner (`eax` plus `cl`) under the default flags while preserving the
native copy order (`inc path`, store prior byte, advance output). Focused Wibo
improves from 28.26% to 66.67% and moves the scratch into Mid Progress. The
retained residual is that VC6 emits a shorter top-tested loop with an
unconditional jump back to the reload, while native uses a bottom
`mov cl, [eax]` / `test cl, cl` / `jne` pair; attempts to combine the primed
register ownership with the original bottom-tested source fall back to the old
`ecx`/`al` cursor allocation.
