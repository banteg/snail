# Near match — 95.78% score, 199/204 instructions on standard flags

The candidate uses the project-standard `msvc6.5 /O2 /G5 /W3`. Current
source-shape recoveries:

- `cell->position` is copied as a `Vector3`, reproducing the native
  anchor-load prologue and three persistent stack lanes.
- Both local probes are real vector subtractions. The swept endpoint is a
  vector addition before the second subtraction; the obsolete scalar-copy
  scaffolding was removed without changing codegen.
- The two sample gates read the array element before forming a pointer. This
  recovers both native sample-base calculations and raises the honest focused
  score from 75.63% to 84.69%.
- `do { ... } while (--idx >= 0); return;` plus the accepted-probe jump keeps
  the closest honest seed-after-return layout. A structured
  `break`/exhaustion form introduces an extra index check and regresses the
  current candidate to 95.31%, so it remains rejected.

Recovered behavior and ownership:

- Scan `Path::secondary_samples` backward from `segment_count - 1`, with the
  exact 0xa8-byte `AttachmentSample` stride, skipping samples whose authored
  world-up Y component is non-positive.
- Rotate `position - (cell anchor + sample position)` into sample-local space;
  require the integer-half-width bounds plus `y >= -0.2`, `z > 0`, and
  `z < delta_length`.
- Rotate `(position + sweep) - sample origin` again and accept when local
  `y <= 0.001f`.
- On acceptance, `0x42c98a` clears
  `Player::attachment_exit_pending` at player+0x41d. The caller rechecks that
  byte before its secondary-slot probe, so a successful primary entry retires
  the gate while a miss leaves the secondary candidate eligible.
- The seeded block at game+0x430100 is the Player-embedded
  `cRPathFollowGoldy` at player+0x384,
  not a standalone global. It owns the borrowed `Path`, borrowed `cRSubLoc`,
  sample index, progress, vertical offset, orientation fields, and Player
  backlink.
- The same Player owns the adjacent position, velocity, exit byte, and inline
  `cRSquidge`; the installed heading comes from
  `cRSubGame::runtime_rows[row].installed_heading_delta`.
- The final validation is
  `cRPathFollowGoldy::update_track_attachment_follow_state(player.velocity.z,
  &player.transform.position, &player.velocity)`.

The two native callers discard EAX, both empty exits return without producing
a value, and the final helper result is not semantically consumed. Binary Ninja
now records `void __thiscall(Path*, six floats, cRSubLoc*)`, replacing the
stale `int PathTemplate::*` view. iOS names the broader family
`cRPath::Search(cRSubGoldy*, tVector, tVector, tVector, cRSubLoc*)`; the Windows
split keeps only seven stack dwords for position, sweep, and the borrowed cell.

## 2026-07-14 canonical root ownership

The fixed player is now reached through
`GameRoot::subgame.player`; every accepted-entry write traverses canonical
`Player` fields, including the embedded `follow_state`, inherited transform, velocity,
exit gate, and `Squidge`. The installed heading likewise comes from the real
`cRSubGame::runtime_rows[row]` owner. Seven field-first absolute globals
are no longer needed by matching sources.

This ownership recovery improves the focused candidate from 84.69%, 188/204
instructions, 24 clean operands plus one mismatch to 95.78%, 199/204,
47 clean operands, with no unresolved or mismatched masked references. The
reference manifest now bounds `g_player_block` to the proven 0x4364-byte
`Player`, allowing canonical base-plus-field relocations to audit against older
narrow field aliases.

The entire accepted-entry seed block is instruction-identical. Remaining
honest deltas are one commutative swept-X addition order and VC6's placement of
the exhausted-loop epilogue: native duplicates the epilogue before the seed
block, while the current source branches to the shared tail. Volatile aliases,
dummy reloads, and neutral arithmetic remain rejected as fakematching.

## 2026-07-14 root declaration closure

The implementation now carries the recovered process root as `GameRoot*`
instead of retaining a byte pointer around otherwise canonical player and
runtime-row traversals. Focused output is unchanged at 95.78%, 199/204
instructions, with the 16-instruction prefix and all 47 operands clean.

## 2026-07-16 analysis replay closure

The recovered Windows method ABI is now part of the shared analysis header and
both replay paths: `Path*`, six scalar position/sweep components, and the
borrowed `cRSubLoc*`. A fresh BN/IDA replay therefore recovers
`Path::secondary_samples` and `cRSubLoc::anchor_position` without relying
on database-local argument edits.

IDA had seven accepted-tail displacements rendered through unrelated symbols
whose numeric addresses collide with the relocatable `GameRoot` offsets. The
replay now normalizes only those instruction operands to numeric displacements;
it preserves the symbols themselves and lets the existing `GameRoot*` type
fold the accesses into `Player::attachment_exit_pending`, `Squidge`, the
embedded `cRPathFollowGoldy`, its Player backlink and orientation fields, and
`cRSubGame::runtime_rows[row].installed_heading_delta`. BN independently
shows the same owner chain. Tracked health checks guard both exports against
the old raw-global and integer-receiver forms.

No matching source changed. A fresh focused compile remains at 95.78%, 199/204
instructions, a 16-instruction prefix, and 47 clean operands. The remaining
delta is still the one commutative swept-X addition order plus the native
duplicated exhausted-loop epilogue; neither warrants source-shape fakematching.

## 2026-07-28 authored follow-class ownership

The expanded Android and iOS reference bodies close the class identity that
Windows cannot spell by itself. Both ports retain exact
`cRPathFollowGoldy::{Init,Traverse}` symbols, and their `cRPath::Search` success
tails hand ownership to that class. Windows remains authoritative for the
embedded address at `Player +0x384`, the 0x40-byte extent, every member offset,
and this split function's scalar ABI.

The shared matcher and analysis headers now make `cRPathFollowGoldy` the
primary owner; `FollowState` is retained only as a compatibility alias. Player,
both follow-method prototypes, and the BN/IDA replay paths use the authored
name directly. No mobile offset or ARM-only control flow was transferred.

This is intentionally codegen-neutral. The focused Windows candidate remains
95.78%, 199/204 instructions, a 16-instruction prefix, and 47 clean operands.
The only differences remain the commutative x87 addition order and VC6's
duplicated exhausted-loop epilogue, so no source-shape forcing was added.

IDA 9.4 reanalysis now keeps the two swept-search cursors as
`PathTemplateSample*` values instead of reducing them to adjacent
`TransformMatrix*` pointers. The tracked health contract therefore checks the
sample bank, transform basis, and inverse-matrix ownership independently of
that presentation choice. The function bytes, ABI, and matcher score did not
change.

## 2026-07-29 recorded control-flow and TU audit

`loop-exit-mutations.json` exhausts all 24 one- and two-site combinations of
four natural swept-vector additions and four exhaustion spellings. Every
variant is byte-identical to the 95.78% baseline. The separate
`break-control-mutations.json` records four structured `break`/post-loop
guards; the best three add two instructions and regress to 95.31%, while the
`idx == -1` form moves the first mismatch into the prologue and falls to
92.57%. The complete results and source hashes are retained in
`experiments.jsonl`.

The remaining regions are therefore exact and bounded. Native loads
`sweep_x` then adds `px`, while VC6 emits the commuted x87 pair; all four
vector spellings preserve that pair. At loop exhaustion native emits a second
five-instruction `pop/pop/pop/add/ret 0x1c` epilogue before the accepted seed
block, while every semantics-preserving `goto` form folds it into the final
epilogue. Structured `break` forms instead require an extra post-loop test.

`probe_neighbor_translation_unit.cpp` then compiles the exact native address
island in order: exact `cRPath::CalcLengthZ`, this search split, and exact
`cRPath::SearchPos`. The target remains byte-for-byte at 95.78%, 199/204,
prefix 16, and 47 clean operands; the two control functions remain exact at
113/113 and 111/111. This falsifies same-TU neighbor presence as the cause of
the x87 or duplicated-epilogue residual, so no production TU cluster is
introduced.

## 2026-07-29 mobile control-flow and vector-lifetime closure

The verified Android and iOS `cRPath::Search` bodies retain the authored
high-level shape: guard the reverse scan with `idx >= 0`, perform the
`cRPathFollowGoldy` handoff inside the accepted-hit branch, return there, and
otherwise fall through after exhausting the loop. The complete
`probe_mobile_control_flow.cpp` overlay transfers only that structure while
keeping the Windows split ABI, layouts, and arithmetic. VC6 compiles it
byte-for-byte identically to the tracked 95.78% candidate, so block nesting
does not explain the duplicated native miss epilogue.

The final recorded sweep tests eight previously uncovered lifetimes for the
swept-position sum. Direct field updates and staged scalar sums remain
byte-identical, including the commuted x87 x-lane pair. Both `operator+=`
orders and both staged-vector forms instead select a different temporary-copy
family and regress to 69.88%. Together with the earlier expression and loop
exit sweeps, the ledger now contains 36 unique variants across three
non-improving sweeps and two evidence probes, with no repeats or errors.

The native/candidate comparison remains at 95.78%, 199/204 instructions,
prefix 16, and 47 clean operands. The remaining five-instruction delta is
bounded to compiler scheduling and tail duplication; forcing it would not
recover additional behavior, ownership, ABI, or data layout.

## 2026-08-12 recovery classification

The recovery is semantic-complete. The live Windows decompile, caller gates,
and both mobile `cRPath::Search` bodies close the reverse sample scan, local
space bounds, swept hit test, embedded `cRPathFollowGoldy` handoff, Player
velocity/Squidge state, source cell, installed row heading, and final follow
update. The Windows split ABI and every embedded offset remain native-derived.

All 47 references are clean. The sole arithmetic delta is a commuted x87
addition, and the five missing candidate instructions are a duplicated native
miss epilogue. These are compiler residuals, not omitted behavior or ownership.
