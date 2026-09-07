# cRSubGolb::Create @ 0x415280

Authored void `cRSubGolb::Create(cRSubGoldy*, int, int)` over one inactive slot
in the player's 12-entry cRSubGolb bank. Binary Ninja confirms the exact
three-argument `__thiscall`; the sole Windows caller supplies its cRSubGoldy,
spawn selector, and bank index. Android and iOS each retain one matching
`cRSubGolb::Create` body in `Golb.o`.

Create links the inherited zero-offset body, selects launch anchors and
velocity from the player's shoot flags, records the bank index, and installs
the kind-zero Sprite, embedded Vapour, or tertiary rocket/path-follow
presentation. The recovered owner layout includes the current/previous flight
matrices, kind-specific backlinks, target reservation, cRSubGame backlink, and
the cRPathFollowGolb child. `Kill` and `AI` account for every created branch.

The scratch exports `?Create@cRSubGolb@@QAEXPAVcRSubGoldy@@HH@Z`. It is
semantic-complete at **99.14%, 582/582 instructions, prefix 156**, with all
48 references clean. Native-backed launch-vector and vapour pointer ownership
recover the earlier 33-instruction gap. Four instruction-order regions remain
open; the old compiler/reference classification was not justified.

## 2026-09-05 coupled launch-vector scopes

Twelve `whole-launch-vector-scopes-20260905-mutations.json` forms couple
true-family velocity staging with the first forward offset's temporary,
narrow block, or complete spawn block. The existing velocity spelling is
neutral at 77.98%; all staged/constructor/shared-owner transfers regress.
The fully staged form with a temporary forward offset is 53.86%, 584/582
instructions, and all 48 references clean: it recovers the previously
missing constant and comes within two instructions, but moves the zero owner
from EBX to EBP, saves EBP earlier, and loses the 81-instruction prefix.
It is not retained. This is useful evidence that the aggregate velocity
operations and the opening list/kind lifetimes must be reconciled together.

Six `whole-shared-launch-vector-20260905-mutations.json` forms reuse the
initial work vector for the true launch family or all launch families, with
three declaration placements. All regress further to 46.51–51.45%, although
all 48 references remain clean. No shared work vector is retained, and the
recorded scope tests do not establish a compiler limitation.


## 2026-09-05 launch and trail ownership recovery

The previous source overwrote the integer `spawn_selector` with a laser
hotspot pointer and later cast the integer back for `cRVapour::ReSet(float*)`.
Windows reuses the argument stack slot once the selector is dead; that is not
an authored integer/pointer relationship. Android's
`00062d2c-_ZN9cRSubGolb6CreateEP10cRSubGoldyii.c` keeps the separate float-pointer
value in `unaff_r9`. Both laser position branches choose the **left** laser
hotspot's Z address when forward Z is positive, otherwise null. The right
position branch must not be changed to the right hotspot's Z address.

A separate `vapour_z_floor` now represents that value. The exact `Shoot`
caller accepts only the supported weapon families; kind 1 is reached through
the laser branch that initializes the pointer. `SetShootFlags` independently
supplies those supported masks. No fabricated initial pointer is needed for
unreachable invalid-mask paths. The existing fallback launch branches are
preserved even though the preceding bit tests exclude them.

This pointer recovery is byte-neutral alone. Coupled with genuine temporary
launch vectors, it restores EBX zero ownership and the late EBP save instead
of the earlier staged-vector regression. `tVector` constructors, owned hotspot
copies, laser flag publication, and direct owned homing/history copies then
recover the complete 582-instruction count and all 48 references. The positive
spread branch snapshots its spawn X while the launch vector is live. The
vapour splice borrows its links through the existing `BodNode` and its signed
flag field by reference, preserving the native embedded-owner addressing.

The eleven `whole-*` recipes added in this recovery contain 112 evaluated
variants: 108 compile and four initial flag-reference diagnostics used the
wrong unsigned type. The following signed-field recipe corrects those
experiments; neither invalid source nor a shared layout change is retained.
The best source improves **77.98% to 99.14%**, prefix **81 to 156**, instruction
count **549 to 582**, and references **47 clean plus one unaudited to 48 clean**.

Remaining native differences are local ordering: the fallback selector's
position-X load relative to its comparison and velocity-Z store; the laser
skip-byte store relative to velocity construction/copy; and the two spread
branches' final velocity-Z stores relative to position-X arithmetic. Direct
member X access, scalar borrows, moving the laser flag around hotspot setup,
and scalar vector-copy forms do not resolve them. These receipts constrain
those tested forms, not the underlying source shape or compiler provenance.


## 2026-09-05 late member-publication follow-up

Eight pointer/reference forms begin the skip-byte or launch-vector borrow at
its publication site, instead of spanning construction or the whole function.
All are byte-neutral at 99.14%, 582/582 instructions, prefix 156, with all
48 references clean. The exact parcel-placement publication recovery does not
transfer to these launch stores. No additional source change is retained.

## 2026-09-05 projectile latch type diagnostics

`whole-projectile-latch-types-20260905-mutations.json` embeds an unchanged
`golb.h` control and three alternatives making `skip_one_tick`,
`slug_bounce_armed`, or both boolean, including the homing overlay copies.
All four are neutral at 99.14%, 582/582 instructions, prefix 156, and 48 clean
references. The paired AI replay is likewise neutral. Observed zero/one
writes alone do not settle the authored byte type; no shared type is changed.

## 2026-09-05 shared vector operator ownership diagnostics

Four `whole-vector-operator-ownership-20260905-mutations.json` variants embed
an unchanged vector header control and move addition, subtraction, or both
from free const-reference functions to const members with identical explicit
result bodies. All are neutral in this caller. The same four-way replay in
S-bend, star-field initialization, CreateGolb, and exact LookAt also stays
neutral, with unchanged instruction counts, prefixes, and clean references.

These results do not independently prove free-versus-member authored spelling;
they show that this distinction does not explain the tested native differences.
No shared header or caller-specific operator implementation is changed.


## 2026-09-05 diagnostic-export batch

Ten paired launch-position/velocity forms test snapshots for the fallback, positive spread, negative spread, both spread branches, or all three, and either final publication order. All regress to 68.51–88.59% from 99.14% and differ from instruction zero. Eight also introduce one unaudited reference; the other two retain all 48 clean references. Whole-position snapshots therefore do not recover the residual scalar/store interleaving in these forms. No source, type, or reference-manifest change is retained.

The receipts bound these hypotheses only. No new exact match or unsupported ownership/return contract was inferred.

## 2026-09-07 broader core controls

`authored-list-node-reference-20260907.json` tests the mobile-authored
`cLinkedList<cRBod>::Add(cRBod&)` argument contract, using either a direct
reference call or a pointer compatibility wrapper. The source overlay retains
the Windows link-publication and flag order; the shared header is unchanged.

Both forms preserve 99.14%, 582/582 instructions, prefix 156, and all 48
clean references. The complete batch includes seven functions; only the
pointer-wrapper variant of `initialize_game_assets_and_world` regresses.
No shared declaration change is supported by this experiment.
