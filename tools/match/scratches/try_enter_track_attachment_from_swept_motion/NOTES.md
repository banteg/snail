# Byte-proven swept path search

The stock VC6 SP3 Path build matches all 800 bytes of `cRPath::Search`,
including 204 instructions and 47 resolved references. Both probes subtract
their sample origin and rotate the result. The second probe first computes
the endpoint as `sweep + position`.

Implementing subtraction as a const member on the left-hand vector, with
the right-hand vector passed by const reference, reproduces the native
x87 operand order. At the endpoint Windows loads sweep X first, then
position Y and position Z first. A private before/after build of every
registered unit found identical code and relocation targets for all 784
other candidates.

The preserving VC6 trace identifies the ordinary compiler decision.
Inline parameter propagation creates the sweep-X field at slot `0x142`
and position-X at `0x131`. Copy propagation creates the Y and Z fields
in the opposite order: position/sweep at `0x154/0x153` and
`0x158/0x157`. Running the three alternate sources below against the
member operator gives 99.02%, 99.02% and 98.04%, all with 47 references.

Run `uv run snail match scratch try_enter_track_attachment_from_swept_motion`
for the encoded-body and reference check.

## Earlier free-operator comparison and argument-component creation

Before the subtraction member was recovered, two instructions differed in the X `fld`/`fadd`
pair. The native sequence at `0x42c8ef` loads sweep X before position X.
It loads position before sweep on Y and Z. A preserving trace of the SP3
backend now identifies each component by its formal parameter name, part
offset, symbol slot, and creation callsite.

| Source | X loaded first | Y/Z loaded first | Whole-Path match |
| --- | --- | --- | --- |
| Retained position copy shared by the two probes | position | position | 99.02% |
| Use the original position independently in each probe | sweep | sweep | 98.04% |
| Construct the motion vector from its first float after rotating the first probe | position | sweep | 97.06% |

The three sources all compile to 204 instructions with 47 audited references.
In the retained source, copy propagation through the saved world position
creates all three position part records at `C2+0x7409`. These sorts use higher
slots than the corresponding sweep fields. In the two controls that read the
original position directly, both X records originate in inline formal
substitution (`C2+0x5ac5e`). Both Y/Z pairs originate when the optimizer
propagates address copies into individual uses (`C2+0x4203c`). The typed
motion control reverses X relative to its other two lanes in the emitted
object, with the opposite order from retail. Each trace checks that its
ordinary, captured, replayed and observed whole objects agree except for the
timestamp.

The older iPad 1.0.6 Search (`0x51920`) and Wii Search rotate independently
supplied start and end positions. Chromadrome 2 also supplies both points:
its caller at `0x4a2510` saves the player's transform before adding velocity,
then passes the previous and current positions into the homolog at
`0x473940`. These versions have no corresponding parameter-plus-velocity
addition to identify the retail operand ownership.

Two exact routines in Path do produce retail Search's mixed lane order for
an ordinary nested vector sum. The anchor and terminal sample switch operand
order on X relative to Y/Z at `0x420fba` in
`update_track_attachment_follow_state` and `0x42192e` in
`traverse_path_follow_golb`. Those operands come from pointed-to fields.
The Search traces above instead observe split records of stack arguments.

The earlier receipts used the free subtraction operator at commit `5d6fdfbb5`.
The recipe also runs against the current source. To inspect how the active
compiler creates the endpoint arguments, choose new output directories:

```sh
scratch=tools/match/scratches/try_enter_track_attachment_from_swept_motion
uv run "$scratch/trace_operands.py" --out /tmp/search-ordinary
uv run snail match mutate "$scratch" --spec "$scratch/swept-argument-part-origins-20261109.json" \
    --export-candidate endpoint/typed-motion-after-start-probe --export-dir /tmp/search-control
uv run "$scratch/trace_operands.py" --source /tmp/search-control/candidate.cpp --out /tmp/search-typed
```

## 2026-11-09: sample origins and whole-Path x87 trace

Both reverse-scan probes now form their origin as a vector sum of the
sample's transform position and the copied cell anchor. Wii Search uses this
operand order for all three components at 0x8006f310, 0x8006f33c and
0x8006f364. Wii SearchPos also adds the sample position to the anchor.
Compiling the old and new Windows sources under the standard msvc6.3 Path
unit produced identical code and relocation fingerprints for all 43 members.
The search is still 99.02%, 204/204 instructions, prefix 109, 47 clean
references. Only the X component's load/add operand order differs from native.

A fresh preserving C2 trace of the two-vector-by-value prototype, in the full
Path unit, measured the following operand slots at the swept addition:

| lane | position | sweep | loaded first | native |
| --- | ---: | ---: | --- | --- |
| X | 0xb5 | 0x142 | sweep | sweep |
| Y | 0x14f | 0x15a | sweep | position |
| Z | 0x153 | 0x15c | sweep | position |

The vector signature scored 98.04% with the direct vector operators, with
both complete origin expressions fused, and with the accepted handoff
inside the hit branch. Copying the first by-value argument into a named
vector used in both probes reproduced the six-scalar result (99.02%,
prefix 109). A snapshot used only for the first probe stayed at 98.04%.
The accepted source now gives the caller and callee one declaration,
`cRPath::Search(tVector position, tVector sweep, cRSubLoc*)`. For each
eligible sample it copies the start point, checks that point, advances the
copy by the sweep, and checks the endpoint. Both Windows caller sites already
pass two whole vectors. The adjacent exact SearchPos, the mobile Search
symbols and the seven-dword Windows stack extent corroborate the types.
The port calls the recovered member directly on both Windows-style search
paths. The old caller-only class and the manual argument-unpacking shim
are gone.

A second preserving trace explains the remaining X difference with a position
copy. VC6 assigned the position components slots 0x166, 0x167, 0x168 and the
sweep components 0x143, 0x15b, 0x15d. This sorts position first for all lanes.
Both spellings leave the width test, rotated endpoints and follow handoff
intact. A fresh source-only proof still requires the native X operand order.

## 2026-10-16: msvc6.3 whole-TU retest of the vector signature

The lead was the authored `(tVector position, tVector sweep, cRSubLoc*)` signature,
matching the adjacent `cRPath::SearchPos` and the `SubgoldyPathView` caller view in
`update_subgoldy.cpp`. With a header shadow, compiled in the Path TU:
`position + sweep`, `sweep + position`, a fused `position + sweep - hit_origin`
and a parenthesized fused form all give **98.04%**, 204/204, prefix 111. That matches
the 2026-09-25 result: X loads sweep first as native does, but Y/Z flip. The scalar
signature (99.02%) stays. `addrorder.py --nodes` on the 43-function Path unit exceeds
the observer's 60 s replay timeout, so this retest has no new slot listing.

## 2026-09-25: vector-value signature retest on the current body

This used a local header shadow with `(Vector3 position, Vector3 sweep, cRSubLoc* cell)` and
`position + sweep`. The result is 98.04%, 204/204 instructions, prefix 111, 47 clean references. The
last scalar result (99.02%) is kept.

- **Operand order.** The X lane now loads sweep first, as native does. Y and Z flip: they also load sweep
  first, but native loads position first there.
- **Why.** `addrorder.py --nodes 44` shows the scalarized component slots:

  | Component | Slot |
  | --- | --- |
  | position.x | 0xb5 |
  | sweep.x | 0x142 |
  | position.y | 0x14f |
  | position.z | 0x153 |
  | sweep.y | 0x15a |
  | sweep.z | 0x15c |

  Native needs position.y/z to rank above sweep.y/z, while position.x stays below sweep.x.
- **Neutral (98.04%):** `sweep + position`, a fused `position + sweep - hit_origin`, a branch-local swept
  copy, and a `Vector3(position)` copy.
- **Regressions:** `+=` forms and a reordered hit origin (76–90%).

The slots come from pool reuse, so this is the same id lottery as the other operand-order residues. No
source or header change.

## 2026-09-25 x87 operand order of the swept X lane

Rule: [x87-order.md](../../c2/x87-order.md). VC6 loads the first-sorted
operand; for two parameters that is the higher slot.

- Parameters are numbered right to left: px 8, py 7, pz 6, sx 5, sy 4, sz 3.
  So with scalar parameters every lane loads p. Native does this for Y/Z but
  loads sx for X.
- Before copy propagation, the Vector3 temporaries' components are the
  operands:
  - X: slots 0x164/0x163;
  - Y and Z: 0x186/0x182 and 0x188/0x184, a different slot block.
  Native's order matches such component symbols surviving to the final sort.
  That is what the mobile two-`Vector3`-by-value signature would give, and it
  would need a shared-header change.
- Six body controls stay at 99.02%, 2/2 structural; propagation turns each
  back into parameters:
  - named position or sweep copies at function or branch scope;
  - both copies;
  - `Vector3(px + sweep_x, ...)`.

No source change.

## 2026-09-23 backward-loop exit ownership

An ordinary pretested `for` loop over the sample index gives VC6 the native
fallthrough miss epilogue before the success block. The earlier post-tested
loop merged that epilogue with the later empty exit, losing five instructions.
This improves the focused result from 95.78%, 199/204, prefix 16 to **99.02%,
204/204, prefix 109**, with all 47 positional references clean. The only
normalized difference is the order of `fld` and `fadd` for swept X. This is
still partial and earns no exact-match credit.

Equivalent pretested `while` and unbounded `for` spellings reproduce the same
object. Swapping vector operands or naming the two temporary vectors does not
change the X operand order. A diagnostic two-`Vector3` parameter view, which
has the same seven-dword stack ABI as the current scalar declaration and is
suggested by the caller and mobile family, recovers X but reverses the Y and Z
adds. Uniform constructor, assignment, compound-add, and inline-operation
forms do not close the full region. The authored parameter grouping remains
unsettled; no mixed per-component addition or header change is retained.

The historical notes below describe the earlier post-tested-loop candidate.

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
  `cRPathFollowGoldy::Traverse(player.velocity.z,
  player.transform.position, &player.velocity)`.

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
exit gate, and `cRSquidge`. The installed heading likewise comes from the real
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
fold the accesses into `Player::attachment_exit_pending`, `cRSquidge`, the
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
and this split function's seven stack-word argument extent; that extent alone does not distinguish scalar floats from vectors passed by value.

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
velocity/`cRSquidge` state, source cell, installed row heading, and final follow
update. The Windows split ABI and every embedded offset remain native-derived.

All 47 references are clean. The sole arithmetic delta is a commuted x87
addition, and the five missing candidate instructions are a duplicated native
miss epilogue. These are observed code-generation differences. The original source expression and argument grouping remain open; they are not proof of a compiler limitation.

## 2026-09-05 argument grouping confidence correction

The seven Windows stack dwords prove the argument extent, not a six-scalar source signature: two three-float vectors passed by value plus the cell pointer have the same extent. Both mobile symbols explicitly retain vector-value arguments, and the current Windows `update_subgoldy` scratch already declares the same call through `SubgoldyPathView` with two `Vector3` values. The shared exact `SearchPos` family also uses vector-value arguments. The scalar declaration is therefore a compatibility reconstruction, not a proven authored Windows prototype. Earlier scalar-ABI closure statements must be read with this correction.

Two local header-shadow probes test vector-value arguments with vector or component expressions; eight more test scalar copies, const copies, explicit components, reversed operands, and temporary scopes. They give 94.79% versus the canonical 95.78%, with all 47 references clean. The X addition order improves while Y/Z ordering changes, and the duplicated miss epilogue remains absent. No shared ABI is changed on this score evidence. Caller result non-use alone likewise does not prove a void return type; the empty native exits and path-dependent register residue are the stronger evidence here.

## 2026-09-05 sample vector scopes

Six complete source forms narrow the sample/hit origin, swept-position and
probe vector declarations to their consuming branches, independently or
together. Five are neutral at 95.78%; replacing the copied cell anchor with
three direct scalar loads regresses to 79.10%. All retain 47 clean references.
No source change is retained, and these scopes do not explain the missing
native exhausted-loop epilogue.

## 2026-09-07 coupled vector arguments and search exits

Ten complete source controls combine the independently supported vector-value
argument grouping with the mobile-style nested scan, explicit miss returns,
break-on-exhaustion, complete anchor-vector additions, and a complete accepted
handoff helper borrowing the local probe. The older exit experiments used the
six-scalar compatibility declaration; these controls test the interaction.

All compile with 199/204 instructions, prefix 16, and 47 clean references.
The seven vector-argument forms remain 94.79%; the three scalar-argument
controls remain 95.78%. Neither argument grouping changes the missing native
miss epilogue. Complete anchor-vector expressions and the borrowed-probe
handoff helper do not improve either grouping. The recipe and current-epoch
receipt retain every tested source; no shared declaration or canonical source
is changed.

## 2026-09-07 version-verified VC6 controls

Unchanged-source probes under the coherent `msvc6.0` and `msvc6.3` component
sets preserve this function's current normalized instructions and reference
state. The seven-function batch pairs the selector/search residuals with four
exact neighboring controls. No compiler override or source change follows
from this comparison. Component versions, hashes, measured results and the
separate mislabeled VC7-archive check are recorded in
[the compiler-control report](../../compiler-profile-controls-20260907.md).

## 2026-09-09 complete scan operation controls

`swept-scan-operation-boundary-20260909.json` factors the complete reverse
scan into an ordinary inline operation, preserving sample order, bounds,
vector calculations, and the accepted handoff. Returning the sample index
adds two instructions and regresses to **95.31%, 201/204, prefix 16**. Returning
acceptance with sample-index and local-vector outputs emits the unchanged
**95.78%, 199/204, prefix 16** baseline. Both keep 47 clean references.

Neither form recovers the separate native miss epilogue or the commuted X
addition. The helper is a diagnostic source hypothesis, not an established
authored API, and is not added to canonical code. These receipts complement
the earlier accepted-handoff helper controls by testing the scan boundary.


## 2026-09-30 current-source ownership controls

The [five-function campaign](../../five-game-functions-20260930.md) recompiled
15 complete source variants against the current canonical body.
No tested variant improves its 99.02% normalized score;
no source change or exact-match credit is retained. The recipes and hash-bound
results are in `source-ownership-20260930-mutations.json`; receipts are appended
to `experiments.jsonl`. These controls bound the tested ownership forms and
their interactions; they do not establish source exhaustion or a compiler limit.
