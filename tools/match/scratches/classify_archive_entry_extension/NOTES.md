# classify_archive_entry_extension

## Exact recovery (2026-09-07)

The project-standard `msvc6.5 /O2 /G5 /W3` build now matches **100.00%**:
46/46 instructions, a complete 46-instruction prefix, and no masked operands.

The stem loop tests the cached current byte for NUL or a dot, copies from the
input cursor with `*output = *path++`, then advances the output cursor. This
ordinary copy idiom lets VC6 retain the native input cursor and byte registers
while emitting the bottom NUL test. Copying the cached guard byte instead
changes register allocation; combining both pointer increments into one
assignment changes the reload schedule. The loop condition and copy expression
needed to be recovered together.

The classifier still stops at the first dot, terminates the copied stem, and
recognizes the uppercase TGA/WAV/MP3 prefixes. The extension checks, enum values,
ABI, and compiler profile are unchanged. Native evidence is in the Windows
decompiles at `analysis/decompile/{binja,ida}/functions/004050c0-`
`classify_archive_entry_extension.c`. The focused four-form experiment is
recorded in `stem-copy-lifetimes-20260907.json` and `experiments.jsonl`.

This exact result supersedes the partial scores and residual assessments below.

## Earlier investigation

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

2026-06-21 local-order pass: moving the `stem_out` cursor initialization after
the initial byte read improves focused Wibo to 70.33%, 45/46 candidate/target
instructions, and a 4/46 prefix. This recovers the native opening load order
(`path`, `stem_out`, then `cl = *path`) while preserving the primed loop's
`eax`/`cl` ownership. Reintroducing a bottom-tested loop with this local order
still regresses to the old cursor-allocation family, so the remaining residual
is unchanged: VC6 emits a shorter top-tested reload jump where native keeps the
bottom `mov/test/jne` pair.

2026-06-21 bottom-test follow-up: source spellings that looked closer to the
native loop tail still lose the retained cursor ownership. `while (value != 0
&& value != '.')`, split `while (value != 0)` plus dot break, `for` forms,
guarded `do/while`, and an explicit break after the reload all regress to
28.26%-34.04% with a zero-instruction prefix. Keep the primed `while (1)` loop
until a form preserves `eax`/`cl` and also emits the bottom zero test.

2026-07-12 ownership pass:

- `ArchiveEntryExtensionClass` now lives in shared `archive_index.h`, so the
  classifier and archive rebuild agree on UNKNOWN/TGA/WAV/MP3 ownership instead
  of duplicating magic integer returns; both focused objects are codegen-neutral
  at 70.33% and 66.38%, respectively;
- a direct two-entry label form modeled native's initial NUL test and loop-back
  to the dot test, but VC6 changed the cursor owner to `ecx`/`al`, duplicated the
  dot test, and regressed to 34.04%, so it was rejected;
- the retained 45/46 object is missing only native's bottom `test cl, cl`; adding
  a fake spill or branch dependency to force that instruction would not recover
  new behavior or ownership.

## 2026-07-25 decompiler cursor ownership

Binary Ninja and IDA now replay the same four source roles at `0x4050c0`:
`path_cursor`, `stem_cursor`, `current_char`, and `extension_cursor`. The
exported decompiles preserve `ArchiveEntryExtensionClass` returns instead of
collapsing the result back to magic integers.

This analysis-only improvement is intentionally codegen-neutral: the retained
scratch remains 70.33%, 45/46 instructions, with a four-instruction prefix and
no masked operands. A label/bottom-tested spelling was retried against the
native loop but regressed to the known `ecx`/`al` allocation family, so it was
rejected rather than forcing the missing test with a fake dependency.

## 2026-08-11 reopened stem-loop sweep

Seven additional natural loop spellings were compiled and recorded, including
guarded `for`/`do` forms and the native-looking label shape. Every variant
regresses to 25.53%-34.04% and loses the retained four-instruction prefix.
That bounds this particular loop-shape family, but does not mark the scratch
tested; the remaining missing bottom `test cl, cl` is still compiler-shape
debt rather than a reason to add a fake dependency.
