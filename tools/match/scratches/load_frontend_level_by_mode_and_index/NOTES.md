# load_frontend_level_by_mode_and_index @ 0x443650

Initial shape:

- Formats a level definition filename into a 128-byte stack buffer from the
  frontend mode and level index.
- The receiver is the same `SubTracks` object that owns
  `load_level_definition_file`; symbol-preserving iOS builds name the authored
  class `cRSubTracks` and this method `Load(int, int)`.
- Mode `0` is postal/arcade. Indexes `0..50` format as `Arcade%03i.txt`; index
  `51` uses `ArcadeExtra000.txt`.
- Mode `1` loads `Challenge000.txt`; modes `2` and `3` load `Arcade000.txt`;
  mode `4` is time-trial, using `TimeTrialExtra%03i.txt` above index `50`;
  mode `7` loads `Tutorial.txt`.
- Native falls through to `load_level_definition_file(path)` even for default
  modes and for mode `0` indexes above `51`, so the scratch preserves the
  uninitialized stack-buffer behavior instead of adding a guard.

Status:

- 2026-06-18: 81.36%, 57 target instructions vs 61 candidate instructions.
  Masked operands are clean except the switch jump-table displacement, which
  the matcher currently reports as the native table bytes at `0x44370c` versus
  the scratch-local `$L319` table.
- The remaining body residual is VC6 tail sharing around the two indexed
  `sprintf` calls: native shares part of the `Arcade%03i.txt` and
  `TimeTrialExtra%03i.txt` setup, while the clean source emits one extra direct
  call block. An explicit shared-label probe made the function much worse, so
  keep this as a documented source-shaped partial until there is a better
  idiom lead.

2026-06-21 argument-order follow-up: `sprintf(&path[0], ...)`, a reusable
`char* path_ptr`, and declaring that pointer immediately before the switch are
all codegen-neutral at 81.36% and leave the same indexed-call tail sharing
residual. A volatile path pointer collapses the prologue and regresses to
31.67%. Keep the direct `sprintf(path, ...)` calls; argument spelling alone does
not recover native's shared path/call tail.

2026-07-09 shared-tail campaign: format-pointer locals, combined case 0/4,
post-switch format dispatch, if-ladder mode selection, and goto-shared
indexed/`plain` sprintf epilogues all failed to recover native's
`push index; push format; jmp shared_lea_path` merge between arcade and
time-trial-extra. Best remains 81.36% with the direct switch + call shape.
The jump-table masked mismatch is still the local `$L` vs image table pair
while body block sizes differ.

2026-07-11 cross-port owner promotion: the shared class is now `SubTracks`,
backed by all four iOS member symbols (`Load`, both `Init` overloads, and
`ImportSegment`). Renaming the owner and header preserves the focused 81.36%
result; the remaining Windows gap is still only VC6 tail sharing and the
resulting local jump-table label.

2026-07-11 return-contract correction: `cRSubTracks::Load(int, int)` is a void
member, and every Windows callsite discards the value incidentally forwarded
from `Init(char*)`. Removing the synthetic pointer result preserves 81.36%,
61/57 instructions, prefix 5/57, and the existing single local jump-table
masked mismatch.

## 2026-07-18 durable loader ABI

The segment-catalog replay now reanalyzes this entry together with the import,
file parser, built-in initializer, catalog loader, and level enumerator. IDA's
checked-in artifact consequently retains the authored void
`SubTracks::Load(int, int)` receiver instead of the stale `_DWORD*`/`char*`
shell. Its default arm still falls through to the final load with the native
uninitialized filename behavior; no safety guard or score-shaped branch was
invented. Focused matching remains honestly unchanged at 81.36% with the one
known jump-table relocation mismatch.

## 2026-07-24 gameplay-mode table identity

The 32 bytes at `0x44370c` are the loader's eight-entry switch table, not the
accidental short string `"m6D"` inferred from its first pointer bytes. Binary
Ninja reads the entries as cases `0`, `1`, shared `2/3`, `4`, shared default
`5/6`, and `7`; IDA independently reconstructs the same switch. The reference
manifest now bounds and names the table and associates it with VC6's
candidate-local `$L777` symbol.

Focused similarity remains the honest 81.36% (`61/57` instructions). The sole
masked operand also correctly remains a mismatch: jump-table references are
content-audited, and the candidate's residual unshared formatting tail gives
its case labels different function-relative offsets. Treating the alias alone
as proof would hide that real layout difference.

## 2026-07-29 indexed formatting closure

Three recorded mutation sweeps bound the remaining formatting tail. The
standard `sprintf(char*, const char*, ...)` declaration and its explicit
`__cdecl`/C-linkage forms are byte-neutral; the correct const-qualified
prototype is retained. The project's SP5 Processor Pack and SP6-style profiles
emit the same bytes, and the RTM-style profile reaches the same result once
given that standard prototype. For this source form, those preserved profiles
do not discriminate the residual.

All five alternate orders of the three plain-path cases retain the same fuzzy
score but worsen reference alignment. Across 19 predicate and index-lifetime
variants, an `else if`, mutating `level_index`, and a scoped `extra_index` are
neutral. Reversing the time-trial predicate drops to `77.48%`; reversing the
postal predicate drops to `68.97%`, and reversing both reaches `65.52%`.

Focused Wibo therefore remains `81.36%`, 57 target versus 61 candidate
instructions, prefix `5`, with twelve clean references and the duplicated call
left unaudited. The four-instruction excess is bounded to VC6's native
cross-format `sprintf` tail sharing. No label, synthetic dispatcher, or other
control-flow scaffolding is retained to force that optimizer layout.

## 2026-08-12 recovery classification

The recovery is semantic-complete. The live Windows switch and both verified
mobile symbols agree on the `cRSubTracks::Load(int, int)` owner. Every Windows
mode, filename, boundary case, and the intentional fallthrough to
`load_level_definition_file` is represented, including the native undefined
buffer contents for unsupported inputs.

The remaining four candidate instructions and one unaudited `sprintf` call are
caused by native cross-case tail sharing that the clean source does not
reproduce. This is compiler/reference layout, not an omitted mode, filename,
or receiver relationship, and its classification does not depend on the prior
probe count.

## 2026-09-05 whole format lifetime probes

Seven whole-function forms vary the extra-level argument lifetime (mutated
parameter, shared index, scoped value) and the path-buffer borrow. All are
neutral at 81.36%; canonical source is unchanged. The duplicated sprintf
region still needs a different source-shape explanation.

## 2026-09-05 indexed formatting operation

Five forms in `whole-indexed-format-operation-20260905-mutations.json` test
a shared indexed `sprintf` operation with a buffer pointer or array reference,
and the two indexed string literals independently confirmed by the Windows
IDA export. All retain 81.36%, 61/57 instructions, prefix 5, and the duplicated
call. Literal spellings additionally expose three reference-identity mismatches
against the curated global symbols; no audit rule is weakened and no form is
retained. The native cross-case tail sharing still needs a source explanation.
