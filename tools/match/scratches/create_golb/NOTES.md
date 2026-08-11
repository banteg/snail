# create_golb

## 2026-07-14 spawn-source ownership closure

The Goldy input is now carried as a `Player*` throughout the movement selector.
The inherited render transform supplies the initial position and forward basis,
`shoot_flags` selects the projectile family, and `velocity.z` supplies every
launch-speed base. The six raw `+0x4134..+0x41ac` anchors are now the authored
`Snail::snail_hotspots_world` entries for left/right/top blaster fire,
left/right laser, and the rocket base. Windows `0x41554d..0x4155b9` and the
independent Android `cRSubGolb::Create` body agree that the optional vapour
z-floor is specifically the address of the left-laser hotspot's z component.

Kind 1 now names its enclosing-shot backlink at `GolbShot +0x114`, directly
after the exact 0x94-byte `Vapour` owner, and uses the shared secondary-body
list links and colour owner. Kind 0's `+0x248` slot is now a `Sprite*` across
creation, update, and exact teardown. Matrix identity and all lifetime/facing
steps use the recovered `TransformMatrix` and `cRSubGame::subgame_rate`
member surfaces.

These ownership substitutions are codegen-neutral: focused output remains
36.08%, 460/582 instructions, prefix 1/582, with 35 clean operands. Directly
spelling the two `+0x1bc/+0x1bd` initial clears through their named fields was
also tested, but changed VC6's opening register schedule and regressed to
35.70%; the raw stores are retained while the fields remain named in the
shared layout.

## 2026-07-13 flight-transform ownership closure

The old `basis_*_scratch`, `position`, padding, and `previous_output` window is
now represented as two adjacent 0x40-byte `TransformMatrix` owners at
`GolbShot +0x1c4` and `+0x204`. This function supplies the first owner directly
to `Vapour::add_vapour_point`, uses its position row at `+0x1f4` as the raw
projectile position, and seeds the second owner's position row at `+0x234` as
the previous rendered output. Only the second owner's position row is proven
live so far; the full type is pinned by its exact matrix-row placement and the
same 0x40 current/previous separation in the Android `cRSubGolb::Create` port.

Kind 2 also writes `this` at `+0x1a8`. That slot is now named
`rocket_owner_shot`: it is the parent backlink immediately following the
embedded tertiary body, consistent with the mobile `cRGolbRocket` class name
and its no-op AI callback. Focused matching is byte-for-byte unchanged at
36.08% (460/582 instructions, 35 clean masked operands).

## 2026-07-13 Golb vapour list ownership

The kind-1 presentation path inserts its embedded `Vapour +0x80` after
`cRSubGame::golb_vapour_list_head +0x355d24` (`GameRoot +0x3ca33c`).
Startup independently installs that sentinel into the root active BOD chain.
Replacing the raw root displacement with this owner is codegen-neutral:
focused matching remains 36.08%, 460/582 instructions, with all 35 operands
clean.

create_golb @ 0x415280 initializes one live Golb projectile slot from Goldy's
movement-flag family and the slot's index in Goldy's 12-entry shot bank.

Recovered semantics covered by this scratch:

- clears the one-tick skip and slug-bounce bytes, then links the slot into the
  shared active body list unless it is already linked;
- classifies `player+0x338` movement flags into Golb kind `0`, `1`, or `2`;
- initializes the live matrix, state, owner pointer, and spawn position from
  `player+0x68..0x70` plus half extents at `player+0x58..0x60`;
- handles all shoot-flag spawn-anchor families used by
  `cRSubGoldy::Shoot` (`shoot_subgoldy`): side offsets at
  `+0x4134/+0x414c/+0x4164`,
  attachment lanes at `+0x417c/+0x4188`, and the rocket lane at `+0x41ac`;
- for the `flags & 0x18` attachment family, repurposes the incoming selector as
  the optional vapour z-floor pointer at `player+0x4184` when the live-matrix
  forward-z lane at `player+0x60` is positive, otherwise passing null;
- seeds velocity from `player+0x418`, including the side-biased `+/-0.1`,
  `+/-0.5` x offsets, kind `1` velocity doubling, and kind `2` `0.8` scale;
- copies velocity to direction, sets per-kind lifetime step from game rate,
  and routes kind `0` through sprite allocation, kind `1` through vapour setup,
  and kind `2` through the exact `search_path_for_golb` helper;
- seeds the embedded follow state from `player+0x384` when the active player
  follow lane is available, otherwise clears it and installs the `-1.0f`
  path-entry z latch;
- stores the velocity magnitude into `path_factor`, copies the starting
  position to the previous-output vector, and dispatches through the slot
  vtable just like the native tail.

Residuals:

- Current matcher result: 36.08% (`tools/match/match.sh
  tools/match/scratches/create_golb --full`).
- The function is pinned: all native semantic lanes are represented, and the
  remaining source-shape leads have either been tested below or require new
  source/provenance evidence.
- Remaining diff is dominated by source-shape, especially the branchy
  movement-flag selector. Native keeps a compact fallthrough tree with several
  shared velocity-staging labels; the scratch uses clearer C++ branches.
- Native stages several vector copies through stack locals and callee-saved
  registers. The scratch writes most `Vec3` fields directly, so register choice
  and stack frame use differ even where the same fields are covered.
- The sprite path's position copy now uses whole-`Vec3` assignment, improving
  local pointer-copy shape. The same source shape was tested and rejected for
  the velocity-to-direction copy (27.21% -> 21.10%) and previous-output copy
  (27.21% -> 26.99%) in isolated trials. After the allocation-shape pass, the
  direction whole-copy was retested and rejected again because it regressed to
  15.92%, while the previous-output whole-copy improved the scratch from
  28.38% to 28.54%, 448/582 instructions.
- 2026-06-13 source-shaping follow-up: narrowing the `position`/`velocity`
  pointer lifetimes until after the list/kind setup improves the scratch from
  27.93% to 28.16%, 448/582 instructions. Splitting the `player+0x338` read
  into a kind-classification `kind_flags` read and a later movement-tree
  `shoot_flags` read matches the native reload better and improves the
  scratch to 28.38%, 447/582 instructions. Re-testing the previous-output
  whole-copy on top of that accepted source shape improves the scratch to
  28.54%, 448/582 instructions.
- 2026-06-13 source-shaping follow-up 2: the `(shoot_flags & 5)` selector
  now uses the native direct compare order with a shared movement-source copy
  label visible in BN's disassembly. A cleaner `if/else if` spelling improved
  the scratch to 28.57%, but still emitted a null-source guard; the shared-label
  spelling removes that guard and improves the scratch to 28.63%, 445/582
  instructions.
- 2026-06-15 type cleanup: `SpriteManager` and `tColour` now come from the
  shared sprite header, including the float-shaped `store_color4f` callsite
  declaration. This is score-neutral at 28.63% and removes the final
  scratch-local `SpriteManager` copy.
- Rejected source-shape trials from the same pass: an explicit
  `player_position` source pointer for the initial spawn-position copy emitted
  the same score on its own; a whole-`Vec3` initial copy regressed to 28.10%;
  staging the half-extents as named locals regressed to 28.32%.
- 2026-06-13 rejection pass 2: staging only the y/z spawn half-extents as
  named locals regressed the current scratch from 28.63% to 28.57%, so keep
  the direct field adds. Repeatedly reloading the kind-0 sprite from the slot
  word instead of keeping the typed sprite pointer regressed to 20.96%.
  Rewriting the post-direction kind dispatch as a decrementing labeled tree
  regressed to 22.37%. A top-level `zero_byte` local for the initial byte
  clears emitted the same 28.63% code and was reverted as neutral churn.
- 2026-06-16 Sprite audit: the kind-0 sprite path now uses the shared `Sprite`
  fields for progress, gravity, color, `size_start`/`size_end`, position, and
  facing rotation. This keeps the local `Sprite*` shape called out above and
  improves the scratch from 28.63% to 30.93%, 446/582 instructions, with the
  same single masked-operand mismatch.
- 2026-06-17 Vapour consolidation: the kind-1 vapour path now uses the
  shared `vapour.h` method surface. `initialize_vapour` and
  `reset_vapour` pin flags `+0x04`, owner `+0x24`, point count/capacity,
  half-width bits at `+0x88`, optional z-floor/clamp pointer slot at `+0x8c`,
  and points `+0x90`; `create_golb` remains unchanged at 30.96%, 445/582
  instructions.
- The kind-specific setup lanes are complete, but vapour/list insertion, sprite
  color copy, and some path-search/list handling still differ in local ordering.
  Do not add dummy temporaries solely to force those byte layouts without
  stronger source evidence.
- 2026-06-18 vector alias cleanup: the scratch-local `Vec3` view now aliases the
  shared `Vector3` type, including the existing `vector_magnitude` method
  surface. Focused Wibo remained `30.96%`, `445/582`, with `31 ok` masked
  operands and the known mismatch.
- 2026-06-19 shoot-tree layout: inverting the top-level `(shoot_flags & 5)`
  source branch keeps the non-`&5` movement families as the fallthrough path and
  moves the `&5` anchor-copy body out-of-line, matching the native tree shape
  better without changing spawn semantics. Focused Wibo improves to `31.71%`,
  `446/582`, and the masked operand audit is now clean at `33 ok`, `0 mismatch`.
- 2026-06-20 GolbShot type split: the scratch now consumes `include/golb.h` for
  the `GolbShot::create_golb(Player*, int, int)` declaration. The final slot-0
  callback is still spelled through a local `GolbShotPrimaryBodyView`, matching
  the renderable BOD vtable installed at offset zero by `initialize_golb_shot`.
  Focused Wibo stays `31.71%`, `446/582`, with `33 ok` masked operands.
- 2026-06-21 helper surface pass: replacing the stale free
  `add_vapour_point(vapour, matrix)` call with the recovered
  `Vapour::add_vapour_point` member call improves focused Wibo to
  `31.94%`, `445/582`, with `33 ok` masked operands. This matches the native
  kind-1 vapour call surface (`ecx = self + 0x80`, one matrix argument) and
  removes the extra caller stack cleanup from the old free-function spelling.
- 2026-06-21 kind-2 path-hit pass: the `self + 0x118` node is now exposed as a
  local word slice for its active-list flags/links, the stale local
  `GolbPathSampleBank` shim is replaced by the shared `GolbPathBank` member
  call, and the path-search hit copies the three coordinate words through a
  `Vec3` view rooted at `sample + 4`. Focused Wibo improves to `34.79%`,
  `447/582`, with `35 ok` masked operands. Rejected neighbors: using the real
  `GolbPathBank` call alone was score-neutral, using the coordinate `Vec3` copy
  without the node word slice regressed to `28.18%` with a mask mismatch, and
  applying the same word-slice treatment to the kind-1 vapour node either
  stayed lower or regressed combined variants.
- 2026-07-10 attachment z-floor and ownership pass: Windows instructions
  `0x415565..0x4155b9` and the independent iOS
  `cRSubGolb::Create(cRSubGoldy*, int, int)` implementation in `Golb.o` both
  show that the `flags & 0x18` lane overwrites the incoming selector with an
  optional `float*`; the iOS `cRVapour::ReSet(float*)` symbol
  (`__ZN8cRVapour5ReSetEPf`) independently pins the callee type. When the
  live-matrix forward-z lane at `player+0x60` is
  positive it points at `player+0x4184`, the z component of the first
  `player+0x417c` attachment anchor; otherwise it is null. This value is later
  passed to `Vapour::reset_vapour` as its z-floor/clamp pointer. The
  scratch no longer mistakes selector values `1` and `2` for raw pointers.
  Narrowing the owner lifetime, using the owned `GolbShot::velocity` fields,
  and preserving the typed player owner through sprite allocation improves the
  focused result to `36.15%`, `458/582`, with `35 ok` masked operands. The
  follow-state tail now copies the typed owner record, including the whole
  output-position vector and its z latch, matching the native ownership and
  aggregate-copy evidence; that clarification is retained at `36.08%`,
  `460/582`, despite the `0.07` point SequenceMatcher movement.
- The primary live-body insertion now uses the shared `BodNode` ownership
  already proven by exact initialization and teardown scratches. This and the
  promoted `float*` vapour z-floor type are codegen-neutral for `create_golb`;
  `reset_vapour` remains exact at `7/7` instructions.
- The remaining stable `GolbShot` owners are now used directly for kind/state,
  source matrix, flight/previous-flight transforms, direction, lifetime, game,
  sprite body, shot-bank identity, and path factor. Later caller/mobile
  evidence closes `+0x274` as the integer shot-bank index; only the downstream
  trail Sprite stores it through that separate owner's opaque `object_ref` ABI.
  This promotion is also codegen-neutral at `36.08%`, so no byte-shaping was
  introduced to obtain it.
- Rejected 2026-07-10 neighbors: narrowing only the player pointer regressed to
  `30.37%`; staging every velocity assignment through `Vec3` temporaries
  regressed to `34.59%` with a masked-operand mismatch; doing so only in the
  attachment lane regressed to `29.44%` with a mismatch; moving the position
  declaration earlier was score-neutral but hoisted its address before the
  native lifetime begins.
- 2026-07-11 contact-target correction: exact search and register helpers prove
  that the kind-2 lookup reads the subgame's `EnemyManager`, not a
  Golb-specific sample bank. The hit is now a `ContactTargetEntry*`; its object
  pointer is retained at `GolbShot +0x198`, kind zero reserves that object with
  `BOD_FLAG_SUPPRESS_CONTACT`, and its position is copied into the homing
  target. This keeps the existing honest `36.08%`, `460/582`, with 35 clean
  masked operands.

## 2026-07-13 void AI-dispatch contract

- The sole Windows caller, authored as `cRSubGoldy::Shoot` and retained as
  `shoot_subgoldy` in the stable analysis catalog, discards EAX. The
  independent iOS `cRSubGolb::Create(cRSubGoldy*, int, int)` body also ends by
  invoking the actor's slot-zero AI callback and returns without establishing
  a result value.
- `GolbShot::create_golb` is therefore `void`. Its scratch-local
  return-valued virtual shell is replaced by the shared, cast-only
  `BodAiDispatch` ABI view; this does not add a second vptr to `GolbShot`.
- Focused Windows output is byte-shape neutral at 36.08%, 460/582
  instructions, prefix 1/582, with all 35 masked operands clean.

## 2026-07-14 root-list closure

- Both primary and kind-2 active-list insertions now start at
  `GameRoot::active_bod_list.first`; the kind-1 insertion starts at the
  subgame-owned `golb_vapour_list_head`.
- The source retains its existing typed/raw splice schedules, but no longer
  invents global anchors from root offsets. Focused output is unchanged at
  36.08%, 460/582 instructions, prefix 1/582, with 35 clean operands.

## 2026-07-14 complete projectile receiver ownership

The final byte-shaped `self` alias is gone. The two creation latches are the
shared `GolbShot::skip_one_tick` and `slug_bounce_armed` fields, including the
attachment-family arm that raises the skip latch. The tail virtual dispatch
now borrows the zero-offset `primary_body` explicitly, which is the
`RenderableBod` that owns the installed callback word; it does not invent a
second vptr on `GolbShot`.

This promotion is byte-stable at the honest 36.08%, 460/582 instruction
frontier, prefix 1/582, with all 35 masked operands clean. The deliberately
raw kind-2 list splice remains unchanged because its word-slice schedule is a
measured source-shape improvement, not missing projectile ownership.

## 2026-07-16 analysis replay closure

The proven `void __thiscall create_golb(GolbShot*, Player*, int32_t, int32_t)`
contract is now durable in both analysis replay catalogs and the tracked
Binary Ninja/IDA artifacts. This replaces IDA's stale
`int __thiscall(char*, int, int32_t, int)` shell and lets both decompilers
propagate the complete `GolbShot` and `Player` owners through the movement,
presentation, and path-follow branches. The matcher source is unchanged at
the honest 36.08% frontier.

## 2026-07-17 active-list insertion lifetime replay

The two inlined `BodList::add_bod` sites now retain their exact intrusive-node
owners in Binary Ninja and the independently refreshed IDA artifact. The first
site borrows the zero-offset `GolbShot::primary_body.bod.bod`; the kind-2 site
borrows `GolbShot::tertiary_body.bod.bod` at `+0x118`. Neither splice transfers
ownership of the enclosing `GolbShot` or allocates a list node.

Fourteen exact Binary Ninja register lifetimes preserve the shared
`GameRoot::active_bod_list.first` anchor across ECX/EAX/EDX reuse. This removes
the stale `(eax_2 - 0x5ac)` root reconstruction and the
`__offset(GolbShot, 0x118)` alias from the tracked decompile. IDA independently
propagates `BodNode**`/`BodNode*` through both splices from the canonical root
field, with no `FrameBodBase` casts. Both lanes are guarded by durable health
checks.

The matcher source is deliberately unchanged. Focused Wibo remains at the
honest 36.08%, 460/582 instructions, prefix 1/582, with 35 clean masked
operands and no unresolved or mismatched operands; this slice improves analysis
ownership only and introduces no byte-shaping.

## 2026-07-17 nested projectile-owner closure

Kind 1 now links and initializes the complete `GolbShot::vapour` child rather
than a `secondary_body`/union view; kind 2 continues through the independent
`tertiary_body` at `+0x118`. The exact `sizeof(Vapour) == 0x94` boundary ends at
the enclosing-shot backlink at `+0x114`, and the tertiary body's transform at
`+0x150` accounts for the old direct matrix alias.

This is deliberately an ownership correction, not a fakematch. Focused output
remains at the current honest 34.77% frontier (459/582 instructions) with all
35 masked operands clean. Both analysis lanes now preserve `vapour.body`, the
backlink, and `tertiary_body` directly.

## 2026-07-23 presentation and contact-owner replay

All native references to `GolbShot +0x248` are kind-zero Sprite operations
across creation, AI, and exact teardown. The canonical analysis field is now
therefore `Sprite* render_sprite`, matching the existing source header instead
of retaining a generic `void*` alias.

Binary Ninja's one merged EAX lifetime also crossed three unrelated kind
branches: a scalar kind discriminator, `shot->game` for the Sprite facing
step, and the `ContactTargetEntry*` returned by `search_path_for_golb`. The
replay splits only the two pointer definitions and leaves the scalar residual
automatic. The constructor now exposes the target entry's `kind`, `position`,
and borrowed `object`, plus the real subgame-rate field.

Six additional complete lifetimes name the shared velocity cursor, selected
Snail hotspot, vapour-list sentinel, allocated Sprite, Sprite color, and Sprite
position. No source or masks changed: the current focused result remains the
honest 34.77%, 459/582 instruction frontier, prefix 1/582, with all 35 masked
operands clean. BN's printable immediate rendering of `spin_step` as a
four-byte `strncpy` remains an analyzer artifact; no fake tail or string owner
was introduced to hide it.

## 2026-07-27 mobile-authored creation shape

The independently shipped Android
`cRSubGolb::Create(cRSubGoldy*, int, int)` at `0x62d2c` and iOS copy at
`0x3f9a4` preserve the same authored creation phases as Windows: intrusive
body insertion, kind selection, identity/source-transform setup, the paired
shoot-flag tree, kind-specific presentation setup, path-follow inheritance,
and the initial AI callback. Their object offsets and presentation constants
remain platform-specific; only the common control and ownership evidence was
used here.

That evidence closes several Windows source shapes:

- Both the zero-offset primary body and kind-2 tertiary body use the shared
  `BodList::add_bod` surface instead of handwritten word-slice splices.
- The spawn position, hotspot anchors, direction, homing target, Sprite
  position, and previous-flight position are whole `Vector3` values. The
  half-forward offset is the authored by-value multiply/add pair.
- `spawn_player` owns the initial transform read, while a separately reloaded
  `player` owns the shoot-flag tree. Moving `state = 1` into that boundary
  recovers the exact first 81 Windows instructions.
- The mobile nested flag family and Windows CFG agree on the `0x02`, `0x18`,
  `0x60`, `0x29`, and `0x52` lanes. Windows retains distinct stack-staged
  launch vectors for the first blaster, `0x29`, `0x52`, rocket, and laser
  lanes, while the mobile optimizers merge equivalent assignments into shared
  labels.
- The presentation discriminator is an authored `switch`. Kind zero stores
  the allocated `Sprite*` directly in `render_sprite`; kind two retains a
  borrowed `ContactTargetObject*`; kind one ends with the Vapour child's
  slot-zero virtual AI callback, matching the explicit `cRVapour::AI` call on
  both mobile builds.

The focused Windows result rises from 34.77%, 459/582 instructions, prefix
1/582, with 41 clean and 10 unaudited masked operands to 77.98%, 549/582
instructions, prefix 81/582, with 47 clean operands, no unresolved or
mismatched operands, and one unaudited target operand. The residual at
`0x415724` is the second emitted copy of the default
`player->velocity.z + 1.0f` launch constructor. Expressing a synthetic extra
temporary reproduces that constant but forces EBP into the function prologue
and destroys the otherwise native register schedule, so it is deliberately
not retained.

Rejected neighboring forms include a single shared launch label (67.91%), a
fully structured `else if` ladder with direct `Vector3(...)` assignments
(45.03%), the same ladder with explicit temporaries (51.20%), an explicit
long-lived `Vapour*` local (56.51%), and staging only the final default launch
copy (53.18%). These were useful compiler-lifetime probes, not candidates for
score-only retention.

## 2026-07-28 mobile random-angle provenance

Android `cRSubGolb::Create` at `0x62d2c` and iOS at `0x3f9a4`
independently preserve the kind-zero Sprite angle as
`(rand - 16384) * (1 / 16384) * pi`. The Windows compiler folded the two
constant factors into `0.0001917476`; restoring the semantic signed-unit
normalizer and half-turn range is byte-identical at the honest 77.98%,
549/582-instruction frontier, prefix 81, with 47 clean masks and the one
documented unaudited target operand.

The mobile Sprite offsets and rate source remain platform-specific. Only the
corroborated random-expression hierarchy is transferred to the Windows source.

## 2026-07-28 inherited cRSubGolb active-list owner

The expanded Android `cRSubGoldy` constructor explicitly constructs
`cRBodPos` at each `cRSubGolb` slot start and installs the actor vtable at that
same address. Together with the Windows constructor, first active-list splice,
and final slot-zero dispatch, this proves that the former `primary_body` is the
inherited base of the enclosing shot rather than an independently owned child.

The matcher now inserts `this` through its inherited `BodNode` base and
dispatches the same zero-offset table. Focused output is unchanged at the
honest 77.98%, 549/582-instruction frontier, prefix 81/582, with 47 clean masks
and the one documented unaudited target operand. Both tracked decompilers now
show the inherited `shot->bod.bod` path and reject the synthetic
`primary_body` alias during replay.

## 2026-07-29 shoot-velocity lifetime closure

Windows stages the `(shoot_flags & 5)` true-family velocity values through the
same 12-byte stack area used by the false-family launch constructors, while
the current candidate writes those four true-family values directly. Android
and iOS also expose one three-float local around this tree, so three bounded
sweeps tested real aggregate ownership rather than padding or volatile stores.

Fifteen combinations of separately scoped `Vec3` temporaries top out at
`54.96%`; by-value `Vec3(x, y, z)` expressions top out at `58.86%`. A vector
owned by the whole true-family branch is byte-neutral while unused, but its
first actual use again drops to `54.96%`, and routing all four exits through it
lands at `53.86%`. A full-tree owner likewise produces 584 instructions,
prefix `3`, and `53.86%`. Every material aggregate lifetime makes VC6 save EBP
and perturbs the function-wide register schedule.

The retained mobile-authored control tree therefore remains the strongest
source evidence at `77.98%`, 549/582 instructions, prefix `81`, with 47 clean
references and one native-only constant left unaudited. The 33-instruction
deficit is bounded to native whole-tree stack/register allocation; no
synthetic temporary is retained merely to reproduce one launch constructor.

## 2026-08-09 shot-pool identity closure

The third `Create` argument is the index of the live shot in Goldy's owned
12-entry `GolbShot` bank, not an emitter owner. Exact Windows
`cRSubGoldy::Shoot` passes its bank-loop index, and the independently shipped
Android `cRSubGoldy::Shoot` does the same. Android and iOS `cRSubGolb::Create`
then store that value in the same per-shot word for all three presentation
kinds.

The surrounding exact lifecycle rules out a second pointer owner at that
word: `initialize_golb_shot` constructs the fixed 0x2e8-byte slot,
`search_path_for_golb` returns the separate kind-2 target retained at `+0x198`,
and `kill_golb` releases that target reservation without consulting `+0x274`.
`update_golb_ai` reaches the word only through its kind-0 trail path:
`spawn_golb_trail_sprite` forwards `+0x274` to each trail Sprite as an opaque
`object_ref`. The scratch definition therefore names the incoming control
value `shot_slot_index`; the distinct Sprite owner retains its own opaque
`object_ref` field for the downstream ABI.

The recorded `shot-pool-slot-identity` probe is byte-neutral at the honest
77.98% frontier: 549/582 instructions, prefix 81/582, 47 clean references,
and the one documented unaudited constant. A second
`shot-pool-slot-field-identity` receipt covers the field rename; its
source SHA-256 is
`a1a05fd8a45a612f747f20b963872d176a34d7d1df047d500a2b48f40054ee80`.
No launch-vector lifetime or source-shape coercion was retried.

## 2026-08-12 recovery classification

Live Binary Ninja and IDA readback now carry `shot_slot_index` continuously
from `shoot_subgoldy`'s 12-entry bank scan, through the `create_golb`
argument, into `GolbShot +0x274`, and finally into the trail Sprite's separate
opaque `object_ref` field. Windows and both mobile bodies account for every
authored creation branch and owned child. The lone unaudited target constant
is the native-only duplicate default launch constructor documented above;
the remaining 33-instruction delta is compiler allocation and factoring, not
an unrepresented behavior lane. Recovery is therefore semantic-complete,
with compiler/reference residuals retained explicitly rather than hidden by
source-shape coercion.
