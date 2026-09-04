# Dossier — matching scratch (639 target insns, 2396 bytes)

place_parcels_on_track @ 0x4438e0. target.asm committed.

## Candidate-bank layout decoded (2026-06-13)

IDA's flt_4DFAFC/unk_648xxx soup resolves to TWO parallel banks of 2048
entries, 524 bytes (131 dwords) each, identical struct:

- entry +0x000: 32 payload quads (vec3 written at quad+0..+8)
- entry +0x200: int candidate_count
- entry +0x204: int set_id (the parcel digit 1-9; bank A entries are the
  digit-0 pool and keep 0 here)
- entry +0x208: int segment_index

Bank A (digit-0 parcels): base 0x53D190 (= flt_4DFAFC viewed at +95653
dwords), indexed by v5/v76. Bank B (parcel sets): base 0x6487E8,
indexed by v79; unk_6489E8 = count lane (+0x200), unk_6489EC = set id,
unk_6489F0 = segment, unk_648BF4 = the next entry's count (the
compaction loop reads it at -259/-131 dword deltas). The reset loop
zeroes both count lanes across all 2048 entries.

Selection consumes `(int)random_float_below(live_entry_count)` per draw
— bank B sets first until `80%% * required / 100 - max_set_size`
parcels place, then bank A digit-0 singles until the required count;
each placed entry compacts its bank down by one (the memmove loops).
Row record writes: flags |= 0x11 (0x10 occupied + 0x01), payload vec3
at record +0x90 (0x5CCB58), row-center accumulator += row + 0.5 and
count += 1.0 (the float pair the June-10 grid fix modeled), flag 0x20
mirrors the lateral sign. Required count at game+0x74622+1293246 with
the shortage warnings; mismatch rescales game+...+1293254.

The tail loop re-projects flagged rows (flags & 1 && flags & 0x40) onto
attachments: template kind 42 via compute_kind42_attachment_transform,
others via get_path_position_at_node — the "project flagged parcel
offsets onto generated track rows" pass.

- mode dispatch: level_mode 1 delegates to
  place_challenge_parcels_on_track; modes 0 (postal) and 7 (tutorial)
  run the seeded placement here
- candidate bank: 2048 entries of 131 dwords at fixed VAs (unk_6489E8
  count lane, unk_6487EC payload lane, unk_6489F0 segment-bank index),
  reset loop zeroes count + a float lane per entry
- selection: `entry = 131 * (int)random_float_below(candidate_count)`
- placement writes go through the per-row record table (244-byte stride,
  the same row records as the follow milestones) with flag byte 0x10 =
  occupied (duplicate triggers report_errorf "Duplicate Parcel Request
  in %s"), 0x11 set on claim, plus the +0.5 center and +1.0 count
  accumulators on the row record
- allocation shortage warns "Parcel Allocation could fail in %s. Add
  more 0 parcels"

The separate `game+0x641184` table is the follow-runtime row-slot table used
by `cRPathFollowGoldy::Traverse`, not this parcel row table.

## WIP scratch — 23.40%, 643/639 insns (2026-06-13)

Structure complete and ordered: mode dispatch, the dual-bank reset, the
segment/set/row/lane scan with both probe lanes (authored records at
segment+0x814 stride 56, character grid at +0x14 lane-major stride 256),
min/max set statistics, both warning gates, the "P1" set selection with
same-segment compaction, the "P2" digit-0 selection with entry shifts,
the requirement rescale, and the attachment projection tail
(kind 42 vs get_path_position_at_node).

Cross-finding: `random_float_below`'s true prototype carries a debug tag
— callers push ("P1"/"P2" here) a string immediate as the SECOND arg;
the matched body never reads it, which is why the one-arg scratch still
pins at 100%.

Golf leads (next pass):
1. The asm folds bank lanes as `[eax+ADDR]` with eax = the dword-scaled
   131*entry offset — flat parallel arrays per lane, NOT struct-member
   displacements (a full flat-lane rewrite measured 17% because the diff
   re-anchored; reconcile the two shapes region by region instead of
   wholesale).
2. The original keeps more loop state in registers (pushes
   ebx/ebp/edi early; frame 0x214 vs 0x208) — the scan loop's
   row/lane/set counters live in a different spill pattern.
3. The grid-scan zero-entry append maintains `131*entry` incrementally
   (add 0x20c inside the lane loop) while the authored append recomputes
   it — split the two append helpers accordingly.

## Row projection payload cross-check (2026-06-16)

The claim loops now use the shared `TrackAttachmentRuntimeRow` view. Focused
Wibo moves from 23.40% to 26.30%, 646/639 candidate instructions, with masked
operands 26 ok / 0 unresolved / 5 mismatch. The useful finding is type/layout
evidence for `TrackAttachmentRuntimeRow::projection_payload`.

The parcel claim path writes the candidate lateral/local lane to row +0x90,
increments row +0x94 by 1.0 as a claim/count lane, and accumulates
`absolute_row + 0.5` into row +0x98. It also mirrors +0x90 when the row's
0x20 flag is set. The later attachment-projection tail consumes the same
vector-shaped storage: kind 42 passes payload.x and payload.y into
`compute_kind42_attachment_transform` and writes the resulting transform x/y
back into the payload, while the non-kind42 path passes the payload to
`get_path_position_at_node` as both input and output.

That makes +0x90..+0x9b an overloaded parcel projection payload rather than a
simple position. Keep it as `Vector3 projection_payload` for now because the
tail still treats it as vector-shaped storage; promote to a union only after
another row consumer agrees on the lane meanings.

## Receiver cleanup (2026-06-21)

The scratch now defines `cRSubGame::PlaceParcels` directly and
calls the shared `place_challenge_parcels_on_track` declaration for mode 1.
The fragile candidate-bank and segment-record shapes stay scratch-local, with
the segment base still addressed as `this + 0xa878`. Focused Wibo remains
26.30%, 646/639 candidate instructions, prefix 0/639, with 26 clean masked
operands and the same five masked mismatches. `uv run snail match types --paths`
now reports `partial-compatible Game: 5`, with both parcel placement scratches
removed from the remaining generic owner list.

## Rejected projection-tail probes (2026-06-16)

Two source-shape probes tried to chase the native projection tail order and both
regressed, so neither should be kept as an assumed fix:

- A raw `char*` row cursor for the projection loop made the disasm start from
  the row-record base more like the target, but regressed the scratch from
  23.40% to 22.72% and expanded the candidate to 646 insns.
- Inlining `live_cell->get_track_cell_row_index()` directly in the
  `get_path_position_at_node` argument list produced the same 22.72% / 646-insn
  regression. The target does push the payload pointer before the row-index
  call in the non-kind42 path, but the typed `TrackAttachmentRuntimeRow` source
  remains the better baseline until another code-shape constraint explains that
  ordering.

## Embedded level owner and candidate-bank consolidation (2026-07-10)

`cRSubGame +0xa874` is now the exact embedded `SubTracks`,
not a loose segment-count field followed by anonymous storage. Its `0x1a5978`
extent accounts for the 100 authored `SubSegment` records, first/last
segments, level display name, parcel count, texture set, and quota through
`subgame+0x1b01e8`. Placement now walks those shared slots and authored rows
directly and writes the owned `runtime_rows[absolute_row]` slab.

The two global candidate banks now share `ParcelBucket`: 32 semantic
`ParcelCandidate` records followed by `candidate_count`, `set_id`, and
`segment_index`. Both exact 2048-entry pool constructors remain 100%, proving
the `0x20c` bucket stride and that these banks are global scratch storage, not
cRSubGame-owned state. The placement scratch remains honestly at 26.30%
(646/639, 26 clean operands and five known mismatches); the ownership rewrite
neither improves nor regresses its code-shape score.

## Direct runtime-row claims and kind-42 owner (2026-07-10)

Both the parcel-set and digit-0 claim passes now preserve the source's direct
`runtime_rows[absolute_row]` indexing instead of introducing a cached row
pointer. That independently agrees with the survival placement routine and
confirms that the claimed row remains owned by the `cRSubGame` slab while
the selected `ParcelBucket` is temporary global pool state. The kind-42 tail
also dispatches through `Path`, matching the same member
owner recovered in the survival path rather than treating the transform helper
as a free function.

Focused Wibo improves from 26.30% to 29.83%, with 635/639 candidate
instructions and 40 clean masked operands. Three address alignments remain:
two candidate-bank lanes and the zero-bank/runtime-row base. The native frame
also remains 0x214 versus the candidate's 0x208. Constructor-shaped glyph
temporaries and a container-of cursor can reproduce pieces of those byte
patterns, but both were rejected: they regress the global comparison and do
not add ownership evidence.

## Sequential runtime-row projection cursor (2026-07-14)

The attachment-projection tail now retains a cursor rooted at
`cRSubGame::runtime_rows[0]` and advances it by one owned `SubRow` per
iteration. This is the lifetime visible in the Windows loop: its induction
pointer starts at the row flags, then reaches the borrowed primary attachment
cell and overloaded projection payload through `SubRow` fields. The previous
per-index spelling let VC6 root the induction at the attachment-cell field,
obscuring the actual owner and leaving the runtime-row base as a masked-address
mismatch.

Focused Wibo improves from 29.83% to 30.93%, remains 635/639 instructions, and
keeps 40 clean masked operands while reducing known address mismatches from
three to two. Directly repeating the row-to-cell-to-path expression was also
tested and rejected: it expands the candidate to 641 instructions, loses the
native helper-call alignment, and regresses to 27.19%. The cached borrowed cell
and path views therefore remain the best honest expression of that part of the
tail.

## Parcel-pool extent closure (2026-07-14)

The dual reset preserves native's byte-offset induction variable, but the
pool byte extent, bucket stride, and `candidate_count` lane now derive from the
complete `g_zero_parcel_buckets` array and `ParcelBucket` layout. This removes
the repeated raw `0x106000 / 0x20c / 0x200` geometry without changing codegen:
focused Wibo remains 30.93%, 635/639 instructions, with 40 clean operands and
the same two honest address-shape mismatches in later compaction code.

## Receiver and early-runtime owner closure (2026-07-14)

The Windows and Android bodies both preserve the `cRSubGame` receiver across
the normal/survival dispatch, while the iOS object symbols name both methods on
that same owner. Binary Ninja prototype previews independently accepted
`cRSubGame*` for the normal and survival functions, so the canonical
header and both decompiler sync paths now replay the two `__thiscall`
receivers. The tracked exports consequently expose `level_definition`,
`runtime_rows`, and the global parcel pools without the old `Game*` shell.

This pass also closes `cRSubGame +0x20..+0x33`: the rolling runtime-row
scan begin/end pair, completion-bonus x/y sources, and the shared
`RuntimeRateOrLevelArg` union. Those lanes are independently consumed by
`update_subgame`, `complete_subgame`, the level builders, rate calculation,
and survival parcel placement. They are owned runtime state; the two 2048-slot
parcel banks and 4096-entry survival row bank remain global scratch.

A persistent local `cRSubGame* game = this` spelling was tested because
Windows spills the receiver and Android retains a receiver alias. It left the
candidate at 635 instructions but regressed the focused score from 30.93% to
30.46% and did not recover the native prologue, so it was rejected rather than
retained as register-allocation matching.

## 2026-07-14 parcel row-flag ownership

Candidate, selected-spawn, mirror, and primary-attachment tests now use the
shared `SubRowFlag` owner; the catalog scan uses the distinct authored Parcel
bit. The native `0x11` claim write is the named combination of candidate and
spawn-request state, matching its duplicate-request diagnostic. Focused output
remains 30.93%, 635/639 instructions, with 40 clean operands and the same two
honest operand mismatches.

## Final-segment scratch lifetime and void ABI (2026-07-16)

Windows initializes the maximum parcel-set size inside the outer segment loop,
not once for the whole level. Android's `cRSubGame::PlaceParcels()` independently
resets the analogous local at the start of every segment and uses its value
after the loop. The post-loop 80-percent target therefore intentionally
subtracts the final segment's maximum. Naming that lifetime directly improves
focused Wibo from 30.93% (635/639) to 31.50% (631/639).

The method is also authored `void`. Android exposes unrelated path-helper and
loop residues on different exits, while Windows exposes the mode value, the
survival call residue, or the final row counter depending on the path; its only
caller ignores EAX. Restoring the void member ABI improves focused Wibo again
to 33.81% (633/639), retaining 40 clean operands and the same two honest
candidate-bank address-shape mismatches. A constructor-shaped scoped `Vector3`
glyph temporary was re-tested against the newly recovered lifetime and rejected:
it expands the frame from the candidate's 0x204 to 0x220 and regresses the
focused score to 27.70% without adding ownership evidence.

## Runtime-row claim ownership replay (2026-07-17)

The two placement passes and the final projection pass now agree across source,
Binary Ninja, and IDA on one ownership model. The parcel-set and digit-0 loops
retain a containing `cRSubGame` base while advancing to a borrowed
`SubRow` at the native `0xf4` stride; the final pass carries a direct borrowed
`SubRow*` cursor through the owned `runtime_rows` slab. Neither candidate bank
nor any row cursor owns or transfers that storage.

## Positive-set candidate cursor (2026-07-25)

The positive-set claim loop keeps EBX rooted at
`ParcelCandidate::position`, reads the candidate's row from the preceding
dword, and advances by the complete `0x10` candidate stride. A field-first
`ParcelCandidatePositionCursorView` now records that physical lifetime in
Binary Ninja, while IDA uses the equivalent shifted `Vec3*` view at
`0x443d80`. The cursor borrows one candidate from the selected global
`ParcelBucket`; the runtime row receives copied position data and no ownership
is transferred.

The earlier `BuildLevel()` parcel-set and ring-speed stores were also checked
before this slice. Both are direct compiler address arithmetic with no durable
pointer lifetime, so no synthetic row or ring cursor was added.

Binary Ninja replay pins the exact register-variable identities 1239/ESI and
1832/EDI as `RuntimeRowStrideAnchor*`, plus 2177/ESI as `SubRow*`. IDA replay
pins the corresponding definition addresses `0x443db8`, `0x444009`, and
`0x444162` and normalizes only the eleven proven row-slab operands whose
numeric displacements collided with `byte_5CCAC8` and `unk_5CCB58`. Readback in
both lanes now exposes `row.flags`, `row.projection_payload`, and
`primary_attachment_cell` without absolute-data aliases. A separate payload
local was previewed and rejected because the normalized IDA expression folds
that lifetime into the row field and no longer has a stable local identity.

No scratch source change was justified: it already expresses the direct
`runtime_rows[absolute_row]` claims and sequential projection cursor. Focused
Wibo therefore remains honestly at 33.81% (633/639 instructions, 40 clean
masked operands, two known candidate-bank address-shape mismatches).

## 2026-07-18 final projection Path borrow

The final runtime-row projection call now shares the exact
`get_path_position_at_node(Path*, Vec3*, int32_t, int32_t, Vec3*)` ABI in both
analysis lanes. Its receiver is the borrowed
`primary_attachment_cell->attachment_template_record`, while
`projection_payload` is borrowed as both input and output; neither helper nor
row cursor owns either object. Refreshed IDA output no longer represents the
receiver through the address of the Path's zero-offset BOD vtable.

No source-shape change was made. Focused Wibo remains honestly at 33.81%,
633/639 instructions, with 40 clean operands and the same two known
candidate-bank address-shape mismatches.

## Parcel scratch-bank cursor lifetimes (2026-07-19)

Binary Ninja now retains five exact borrowed lifetimes across the two pool
compaction paths. The positive-set path carries `ParcelCandidate*` source,
destination, and write cursors while copying the next bucket's 16-byte records;
the digit-0 path carries a `Vec3*` candidate-position borrow and a
`ParcelBucket*` destination cursor while publishing the copied candidate and
its `candidate_count`, `set_id`, and `segment_index`. These views expose the
already-proven `ParcelCandidate` and `ParcelBucket` fields without moving either
2048-entry global scratch bank under `cRSubGame` ownership.

A stack-variable split at the digit-0 destination definition was tested and
rejected. Splitting the reused `out_angle` slot changed downstream MLIL variable
identities and attached otherwise-valid register types to unrelated
temporaries. The split and all displaced annotations were removed, the original
stack variable was restored, and the five stable register lifetimes were then
replayed twice with identical results. No source-shape change was justified;
focused Wibo remains honestly at 33.81% (633/639 instructions, 40 clean masked
operands, two known candidate-bank address-shape mismatches).

## Authored segment scan and zero-pool source ownership (2026-07-24)

The first placement pass now exposes the unusual Windows induction without
pretending that its EBX value is a direct `SubSegment*`. Native roots EBX at
`SubSegment::row_count`, saves that same borrowed address across the inner
loops, and advances it by the full 0x4220-byte segment stride. The
`SubSegmentParcelScanAnchor` analysis view therefore starts at `row_count` and
uses the next segment's `row_base` only as its final stride-overlap word;
`SubTracks::segment_slots` remains the sole owner of the storage.

Binary Ninja can keep the two subordinate cursor lifetimes explicit:
`glyph_row_cursor` advances one byte per authored row while
`glyph_lane_cursor` advances 0x100 bytes across the eight lane-major glyph
planes. The parallel EDI borrow starts at `rows[0].local_position` and advances
one 0x38-byte `AuthoredSegmentRow` per row. The BN-only
`AuthoredSegmentRowPositionCursorView` records that EDI is an offset pointer at
`AuthoredSegmentRow::local_position` (+0x08), so the two native reads behind
the pointer now render as `authored_parcel_row->flags` and
`authored_parcel_row->parcel_set_id` rather than false `Vec3` offsets. The view
mirrors the complete 0x38-byte row, inherits the live `Vec3` at +0x08, and is
guarded against either owner changing width.

IDA independently proves the same geometry and safely retains the two
register-backed anchor/position views. Hex-Rays has no equivalent pointer-offset
type, so its honest `Vec3 *authored_parcel_position` continues to expose the
preceding words as `[-1].y`/`[-1].z` and the row step as `+56`. Its three stack
locals were deliberately rejected for replay because Hex-Rays reuses those
slots in the later scratch-bank compaction; naming them as glyph cursors leaked
false ownership into unrelated code. Android also separates the active
segment, glyph-grid, and authored-row pointers while using its port-specific
pointer-backed segment layout.

Adding the second BN pointer-offset view also exposed a replay-tooling gap:
parsing this self-contained header against the live type container can make
Binary Ninja report false forward-declaration redefinitions. The exact-type
audit now retries in an isolated parser container only when the live-container
parse fails; partial headers that genuinely depend on live declarations still
fail closed if that retry cannot resolve them.

The digit-0 compactor also now proves its source/destination relationship.
Windows sets ESI to `destination + sizeof(ParcelBucket)` before copying the
first 16-byte candidate, so Binary Ninja renders those reads as
`zero_destination_bucket[1].candidates[0]`. The two later metadata reads remain
honest raw +0x40c/+0x414 expressions because native reloads them from the
destination base after ESI has been reused; no synthetic pair owner was added.

No scratch source change is justified by these analysis-only ownership
recoveries. Focused Wibo remains 33.81% (633/639 instructions), with 40 clean
masked operands and the same two known candidate-bank address-shape
mismatches. The focused BN/IDA export and all 934 strict decompile-health checks
pass.

## 2026-07-24 parcel spawn-position ownership

The former `projection_payload` at `SubRow +0x90` is now
`parcel_spawn_position`. Its producer/transform/consumer chain is complete:
the runtime-grid builder copies authored parcel-local coordinates, this helper
claims a row and applies mirror/height/absolute-row adjustments before
attachment projection, and `update_subgame` passes the finished vector to
`spawn_track_parcel` as world position. The one-unit y increment is therefore
a spawn-height adjustment, not a count lane.

Both decompiler lanes agree on the same 12-byte field and no other native
consumer gives it a competing meaning. The rename changes no layout or
generated code; focused Wibo remains 33.81% (633/639 instructions), with 40
clean operands and the same two documented address-shape mismatches.

## Cross-port global parcel-bank lifetime (2026-07-26)

Android's authored `cRSubGame::PlaceParcels()` keeps `gGroup` and `gGroup0` as
global scratch banks throughout catalog construction and both compaction
passes. iOS independently exposes the same `_gGroup` bank plus its parallel
count, set-id, and segment-index lanes. Neither port gives a selected or moved
bucket ownership of the pool. Windows agrees: the scan and compaction loops
carry `0x20c`-scaled indices and fixed bank-lane addresses rather than a
durable containing `ParcelBucket*`.

The scratch now preserves that lifetime by indexing the two global
`ParcelBucket` arrays directly while building candidates, selecting a positive
set, and compacting both banks. This is still the shared semantic struct:
direct indexing changes only expression lifetime and does not flatten the
fields back into anonymous parallel arrays. Focused Wibo improves in four
bounded steps:

- catalog construction: 33.81% to 36.56%;
- positive-set compaction: 36.56% to 38.61%;
- digit-0 compaction: 38.61% to 40.13%;
- positive-set selection: 40.13% to 40.44%.

The accepted candidate is 627/639 instructions with 52 clean masked operands,
two unresolved legacy aliases, and no audited mismatch. The former
`g_parcel_set_buckets + 0x40c` compaction mismatch is gone.

Two tempting spellings remain rejected. Constructor-shaped glyph `Vector3`
temporaries reproduce a local copy pattern seen in Windows, but expand the
candidate frame to `0x220` and regress the focused comparison. Removing the
short-lived digit-0 selection borrow also regresses 40.44% to 40.10%, so that
one `ParcelBucket*` remains an honest temporary view while the banks themselves
remain global scratch storage.

## Mobile-assisted catalog control and segment borrow (2026-07-26)

The verified Android and iOS `cRSubGame::PlaceParcels()` bodies independently
separate digit-0 candidates from positive parcel sets in both authored-row and
glyph-grid discovery. Their control flow agrees with the Windows branch shape:
digit 0 stays on the natural path and positive set IDs take the alternate path.
Expressing that source order in both Windows catalog probes improves focused
Wibo from 40.44% to 40.92%, still 627/639 instructions, with one unresolved
legacy zero-bank alias and no audited operand mismatch.

Windows adds a platform-specific ownership detail that the pointer-backed
mobile layouts cannot show directly. Its outer scan roots the cursor at
`SubSegment::row_count`, reaches `glyph_rows` and `rows` relative to that
field, and advances by the complete `0x4220`-byte segment stride. The shared
`SubSegmentParcelScanAnchor` now records that field-first borrow, including the
final word that overlaps the next segment's `row_base`; the containing
`SubTracks::segment_slots` array remains the sole owner.

Two source-real but incomplete probes remain rejected. Restoring the two
Windows glyph `Vector3` staging copies reproduces their local copy sequences,
but the current source shape grows the frame from `0x200` to `0x21c` instead
of the native `0x214` and rotates all three long-lived scan registers. Inlining
the final attachment row-index call likewise reproduces the native argument
evaluation order locally but destroys the stronger runtime-row cursor
alignment. Neither regression is retained, and no synthetic stack padding or
register forcing was introduced.

## Exact affine zero-bank references (2026-07-27)

The remaining audited zero-bank ambiguity was address arithmetic, not shared
ownership. In the glyph digit-0 path Windows adds the complete `0x20c`
`ParcelBucket` stride to its byte offset before finishing the current bucket.
VC6 consequently relocates the remaining current-bucket accesses against
`g_zero_parcel_buckets` with exact addends `-0x208`, `-0x204`, `-0x200`,
`-0xc`, and `-0x8`. After the already-incremented index participates in the
effective address, those land on the current candidate position,
`candidate_count`, and `set_id` fields. Android's named `gGroup0` continues to
prove that the bank itself is global scratch storage.

Numerically, the five relocation bases fall inside the preceding Windows
`g_loc_colour_lookup_wall` extent. The reference manifest now records only
those exact permitted pre-base offsets, and the matcher renders their COFF
addends as signed values. It does not treat the intervening colour-bank range
as parcel storage, and an unlisted pre-base addend remains unresolved.

No scratch source changed. Focused Wibo stays at 40.92% and 627/639
instructions, while the operand audit improves from 50 clean, one unresolved,
and 98 unaudited references to 56 clean, zero unresolved, and 88 unaudited
references, with no mismatch.

## Branch-local projection outputs (2026-07-27)

The final attachment pass now limits its `TransformMatrix` and angle output to
the nonlinear-path branch that actually borrows them. Android and iOS likewise
allocate their projection outputs only for the half-pipe/half-pole calls, and
the Windows survival placement method preserves the same branch-local source
shape. Neither output escapes the helper call; only the resulting matrix
position is copied back into the owned runtime row.

That lifetime lets VC6 reuse the dead scalar slot at native `esp+0x18` for the
angle output. Focused Wibo improves from 40.92% to 41.07%, remains 627/639
instructions, and retains 56 clean masked operands with zero unresolved or
mismatched references. The candidate frame contracts from `0x200` to `0x1fc`;
the native `0x214` frame still includes two catalog-only glyph temporaries that
the current source cannot yet reproduce without a larger regression.

Two bounded glyph probes were rejected. Inline `Vector3(...)` assignment
temporaries recover the native construction timing and full 12-byte copies,
but produce a `0x218` frame and regress the global comparison to 39.22%
(641 instructions). Named branch locals are worse at 37.43% with a `0x21c`
frame. Moving the matrix or angle declaration outside the branch does not
change the accepted codegen, so no artificial padding or forced lifetime is
kept.

## Mobile-backed glyph staging and catalog-target lifetime (2026-07-27)

The verified Android and iOS `cRSubGame::PlaceParcels()` bodies close the
remaining glyph value semantics: a matching digit contributes a `tVector`
whose lateral coordinate is `(float)lane - 4.0f + 0.5f` and whose other two
lanes are zero, then publishes that value to `gGroup0` for digit 0 or `gGroup`
for a positive set. Windows preserves those same values but, unlike the mobile
ports, materializes one branch-specific `tVector` at `esp+0x3c` and another at
`esp+0x48` before the complete three-dword copies into the global banks.

The earlier inline-vector probe was incomplete because it treated the catalog
set index and the later 80-percent placement target as independent source
locals. Windows reuses the `esp+0x24` scalar: it counts set IDs from 0 through
9 during catalog construction, then receives
`80 * parcel_count / 100 - final_segment_max_set_size` before the selection
loop. IDA exposes that exact dual role as `v73`. Keeping one honest
`set_or_target` lifetime lets the two normal `Vector3(...)` assignments occupy
exactly the native 24 bytes without padding or forced register choices.

Focused Wibo improves from 41.07% to 43.59%. The candidate is 641/639
instructions, the exact `0x214` native frame and both glyph temporary offsets
are recovered, the exact prefix grows from 0 to 7 instructions, and the
masked-reference audit improves from 56 clean / 88 unaudited to
62 clean / 70 unaudited with no unresolved or mismatched references. The
remaining catalog residual is the surrounding EBX/EBP/EDI rotation and broader
scan source shape, not missing vector ownership. A separately named pair of
branch locals remains rejected at 37.43%; an explicit outer segment cursor was
also score-neutral and emitted its borrow before the native zero-segment gate,
so neither spelling is retained.

## Mobile-backed claim precision and Windows bank control (2026-07-28)

Android and iOS independently compute each claimed row center in float:
`float(absolute_row) + parcel_spawn_position.z + 0.5f`. Windows agrees with an
`fild` of the integer row followed by two dword `fadd` operations. Removing the
scratch's explicit double conversion from the positive-set path improves
focused Wibo from 43.59% to 43.91%. Applying that change to the digit-0 path
before recovering its surrounding bank lifetime rotates the complete selection
loop and regresses to 38.75%, so that incomplete probe was rejected.

The missing lifetime was the one exposed by all three binaries: the selected
digit-0 entry never becomes a durable `ParcelBucket*` owner. Android retains a
`0x20c`-scaled `gGroup0` offset, iOS accesses the `_gGroup0` field lanes with
the same scaled index, and Windows carries that offset in ESI while it copies
the candidate into the owned runtime row. Direct global indexing preserves the
semantic `ParcelBucket` layout without inventing a bucket owner. Together with
the float row-center expression, it improves the scratch from 44.06% to
68.64%.

Windows also publishes the digit-0 compaction metadata in
`candidate_count`, `segment_index`, then cleared `set_id` order. Reordering
those independent field writes improves 43.91% to 44.06% before the larger
lifetime recovery. Both mobile ports confirm the same moved metadata, although
their compiler schedules differ.

An earlier reading treated the Windows bank-count tests as one-shot prechecks
and the claim passes as quota-only `do`/`while` loops. That interpretation was
incomplete: the addressed back edges were rechecked in August and both return
through their bank-exhaustion tests. The Android and iOS bodies independently
retain the same safety property. The one-shot source shape was useful for
recovering the broad block layout at this stage, but was not behaviorally
complete.

At this stage the candidate was 637/639 instructions with the exact `0x214`
frame, 7-instruction prefix, and all 98 masked operands clean: zero unresolved,
zero mismatched, and zero unaudited. The residual is stack-slot coloring plus
the already-documented final projection evaluation order. No volatile barrier,
synthetic dependency, stack padding, or register forcing is present.

## 2026-08-12 recovery classification

A fresh canonical match, both verified mobile bodies, and live Binary Ninja
readback agree that every authored lane is represented: mode dispatch, both
global scratch-bank constructors and scans, per-segment set accounting, the two
claim/compaction loops, quota correction, runtime-row ownership, and both final
attachment projection paths. The live database retains the `cRSubGame`
receiver, field-first segment scan, borrowed candidate cursors, three owned-row
anchors, and sequential `SubRow` projection cursor. All 98 references remain
clean, with no unresolved, mismatched, or unaudited operand.

The 637/639-instruction candidate still differs in stack-slot coloring and the
evaluation order of the final projection arguments, but those differences do
not hide a behavior or ownership lane. Recovery is therefore
`semantic-complete` with compiler residue; no source-shape coercion is justified.

## Borrowed projection-path lifetime (2026-08-13)

A fresh Windows comparison showed one source-real lifetime still hidden by the
2026-08-12 classification. The final projection loop borrows the attachment's
`Path*` before dispatching on its kind, and both branches consume that same
borrow. Keeping `template_record` live across the ordinary-path `Yi()` call,
rather than re-deriving the path from `live_cell`, improves focused Wibo from
87.77% to 88.09% (+8 fuzzy bytes) with the same 637/639 instructions,
7-instruction exact prefix, and all 98 references clean.

The recorded four-variant sweep also tried reloading the cell from its owning
row, spelling both calls through that reload, and introducing a fresh borrowed
cell after `Yi()`. All three regress to 79.91%; only reuse of the already
borrowed `Path*` improves. This corrects the earlier claim that no further
ownership lifetime remained. The residual is still compiler scheduling and
stack coloring, but the retained change is an ordinary semantic borrow with no
volatile barrier, dummy dependency, register coercion, or reference tradeoff.

## Recovered bank-exhaustion back edges (2026-08-13)

Fresh addressed Windows readback resolves the stale control-flow
classification above. At `0x443f66`, the positive-set loop jumps back to
`0x443d34`, which tests the current `set_entry_count` before another `P1`
draw. At `0x440ff`, the digit-0 loop jumps back to `0x443f83`, which tests the
current `zero_entry_count` before another `P2` draw. These are live guards, not
entry-only validation. Android's verified body expresses the same two loops as
quota-and-bank-count conditions.

The source now keeps both count tests on their loop paths. The digit-0 pass
also retains `last_zero_entry = zero_entry_count - 1` across compaction and
decrements it with the pool count; that is the lifetime exposed by Windows'
`esp+0x1c` slot and by both mobile pool cursors. This removes the scratch-only
possibility of drawing from an exhausted bank and improves focused Wibo from
88.09% to 88.71%, still 637/639 instructions with the 7-instruction exact
prefix and all 98 masked references clean. No register forcing, dummy
dependency, or platform-specific behavior was introduced.

## Bounded receiver/segment stack coloring (2026-07-30)

The dominant remaining catalog-and-claim diff swaps two long-lived stack
colors: native stores the `cRSubGame*` receiver at `esp+0x28` and the outer
segment index at `esp+0x2c`; the candidate assigns those same values to
`esp+0x2c` and `esp+0x28`. The complete frame size, values, control flow, and
98 reference operands already agree.

Three recorded sweeps tested the source-faithful ways to alter that
interference order:

- six placements and initialization forms for a function-scoped segment
  index around the existing catalog locals;
- entry-scoped declared and initialized segment indices paired with the outer
  loop;
- a typed `cRSubGame* game = this` alias spanning the mode dispatch and final
  projection loop.

Across 14 unique variants, ten compiled byte-identically and four incomplete
interactions failed to compile; none improved or regressed a valid build. The
ledger records those shapes at 87.77%, 637/639 instructions, with all 98
references clean.
Retain the natural scoped source. These bounded probes did not recover the slot permutation. They do not
exclude other source expressions or interactions with the rest of the function.

## 2026-09-05 direct segment ownership and projection lifetime

Direct indexing through `level_definition.segment_slots[segment]`, together
with typed parcel-bucket reset indexing, raises 88.71% to 89.34%. This removes
the scratch's interior `SubSegmentParcelScanAnchor` cast; the native compiler
can derive its row-count cursor from the actual segment array. A typed local
segment borrow regresses, so that cursor representation was not sufficient.

Replacing the final manual row-pointer walk with indexed rows and reloading
the cell/template at the GetPos call further improves to 89.90%. Both recorded
fresh-cell and direct second-Yi variants score equally; the retained direct
form avoids a cross-call borrow. The candidate remains partial, 638/639
instructions with all 98 references clean. The stack-slot permutation and
projection call register lifetimes remain visible; none is declared exhausted.
