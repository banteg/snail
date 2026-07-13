# initialize_game_assets_and_world @ 0x40acf0

Starter scratch for the large root-world bootstrap.

This is intentionally a semantic partial, not a line-for-line transcription. It
captures the recovered early root defaults, texture/object-list startup, overlay
registration, landscape/menu/audio/font/sprite setup, the first backdrop/pillar
world-object islands, and the first proven root-owned track/world asset banks.
Recovered root, subgame, viewport, overlay, player-camera, landscape, catalog,
and menu owners are typed; unrecovered later islands remain omitted.

Expected residuals:
- most later path-template, pickup, replay, score, and frontend pools are not
  modeled yet;
- the early overlay link still uses its local root-list helper, while the
  recovered subgame group links use the shared inline intrusive-list operation;
- later path-template and remaining world/catalog producers remain outside this
  semantic partial;
- string literals are used for concrete asset paths recovered from the binary,
  so masked-operand audit may still need reference-manifest promotion later.

2026-06-20 font bootstrap audit: the native FONT-MENU-HOVER setup call pushes
`0x3f400000` (`0.75f`) for the width scale and `0x3f800000` (`1.0f`) for the
height scale. The old scratch used `0.800000012f` and a `double` height
argument, which produced an extra high-dword push. The call now targets the
named startup wrapper at `0x432d20`:

```asm
00432d20  mov eax, [esp+0x10]
00432d24  mov ecx, [esp+0x0c]
00432d28  mov edx, [esp+0x08]
00432d2c  push eax
00432d2d  mov eax, [esp+0x08]
00432d31  push ecx
00432d32  push edx
00432d33  push eax
00432d34  call register_font_texture_sheet
00432d39  add esp, 0x10
00432d3c  ret
```

2026-06-20 reference audit: promoted the remaining raw startup globals used by
this semantic partial: `g_sprite_depth_buckets` (`0x4f7050`), the DirectX loader
scratch buffer (`0x74eb18`), and the startup sound-bank table
`g_sound_bank_entries` (`0x4a2140`). The existing built-in segment table is now
referenced as `g_builtin_segment_definitions`. Focused Wibo is still `4.73%`,
but masked audit now has no unresolved operands.

## 2026-07-10 path-constructor ownership

The constructor island spans the same embedded bank initialized through the
subgame view:

```text
GameRoot + 0x1066f2c
= GameRoot + 0x74618 + 0xff2914
= SubgameRuntime + 0xff2914
```

- Public `Path=` slots `0..50` occupy consecutive `0x150` pairs.
- The call at `0x40cda0` targets pair `42` (`game +0x106a64c`) and proves
  `initialize_halfpipe_path_template_pair` is the Windows `HALFPIPE` builder.
- Public pair `30` (`WARP`, `game +0x106968c`) has no constructor or later
  direct authored-code reference; it remains only generically initialized.
- Pairs `51..62` duplicate public families `0..7`, `25..27`, and `41`. Their
  strip meshes are installed as the public records' `+0xa0` transition meshes;
  `+0xa4` points back to the public records' own strip meshes.

## 2026-07-11 early subgame ownership

The bootstrap now uses the embedded `SubgameRuntime` directly for its pause
gate, blink-table initialization, rate setup, and `level_mode_arg` handoff.
This corrects two stale raw offsets in the semantic partial:

- the pause gate is root `+0x74621` (`SubgameRuntime +0x09`), not `+0x74659`;
- the mode argument is root `+0x7465c` (`SubgameRuntime +0x44`), not
  `+0x74654`.

The recovered thiscall shape removes the scratch's cdecl blink/rate shims and
raises the focused partial from 4.73% to 4.84% while keeping all operands
resolved (55 clean, 21 expected residual mismatches). This is still a semantic
partial of the 5,411-instruction bootstrap; the score change is supporting
evidence, not a completeness claim.

The Binary Ninja runtime sync was also made field-only when
`SubgameRuntime` already exists. Its sparse import header can seed a fresh
database, but it no longer flattens later `BodBase`, pool, and `Player`
ownership when adding these blink fields.

## 2026-07-11 root viewport and startup-service ownership

The early bootstrap now follows the constructor-proven `GameRoot` layout:

- `player_count +0x40`, `frontend_link_latch +0x568`, the constructed inactive
  BOD sentinel at `+0x570`, and the active/free list anchor at `+0x5a8` replace
  duplicate raw words;
- three complete `Overlay` objects live at `+0x67c/+0x7c8/+0x914`, with their
  embedded cameras at `+0x6fc/+0x848/+0x994`;
- viewport 0 borrows overlay 0, viewport 2 borrows overlay 1, viewport 3
  borrows overlay 2, and viewports 1/4 borrow player 0/1 cameras. The recovered
  sort keys, scene flags, viewport rectangles, and player camera masks are now
  source-spelled through those owners;
- the inline BOD linker correctly reaches the global root list at `+0x5ac`.

The same target island proves the startup-service receivers and corrects stale
offsets in the old semantic partial:

- the exact `LandscapeManager` at root `+0x106c218` owns ten active entries,
  reset/count state, and the Starmap, Splash, Help, and Menubg script records;
- the exact `0x25cfb4`-byte `SMTracks` at `+0x1075ae4` owns both segment
  and level enumeration calls; its leading count is followed by 150 constructed
  entries and the aggregate ends exactly at the parcel pool;
- challenge setup at subgame `+0x125ffe0` and thanks at `+0x126000c` use the
  same folded `bind_subgame_owner`, while galaxy and the embedded player's
  cameraman keep their distinct methods;
- audio configuration is owned by `Options +0x4f388`, and the second
  complete level-definition owner is root `+0x224804` rather than the stale
  `+0x224a04`.

Focused Wibo is now 5.65%, with 358/5,411 candidate/target instructions,
prefix 0/5,411, 74 clean masked operands, no unresolved operands, and 17
expected mismatches across the still-sparse semantic partial. The native
`0x12c` frame and most later world and path-template islands remain absent; no
score-only scaffolding was added to imitate them.

## 2026-07-11 sprite render workspace ownership

The startup clear now uses the shared typed
`g_sprite_depth_buckets[SPRITE_DEPTH_BUCKET_COUNT]` owner rather than a local
`char[]` declaration and magic `0x400` size. `render_game_frame` proves all 256
heads and the adjacent 3000-entry `g_sprite_depth_nodes` workspace; using
`sizeof(g_sprite_depth_buckets)` preserves the native clear exactly.

## 2026-07-11 root frame counters

The early zero stores at root `+0x518/+0x51c` now use
`fixed_update_accumulator` and `frame_counter`. `run_frame_update` proves their
per-frame increment/consume behavior, `allocate_border` independently reads
the frame counter as a creation timestamp, and `update_game_input` proves the
adjacent `input_sampling_gate +0x520`. This naming is codegen-neutral within
the still-semantic startup partial, which remains at 5.65%.

## 2026-07-11 config selector ownership

The early handoff into `SubgameRuntime::level_mode_arg` now reads
`RuntimeConfig::landscape_backdrop_variant_selector` at config offset `+0xa4`
instead of the raw `unk_4DF9BC` spelling. The instruction stream and 5.65%
semantic score are unchanged, while the masked audit improves from 73 clean / 18
mismatched operands to 74 clean / 17 mismatched operands.

## 2026-07-11 level-definition scratch ownership

The built-in segment import now addresses
`subgame.level_definition_scratch` directly. Construction proves that root
`+0x224804` is a complete `0x1a5978` `SubTracks`, and startup first
uses the same owner to parse each `Levels/*.txt` entry before reseeding it from
the built-in definitions. The broad initializer remains at 5.65%, with its
existing 74 clean and 17 mismatched operands.

## 2026-07-11 cRCameraman owner

The startup initializer now uses the exact 0xd8-byte `Cameraman` embedded in
the subgame Player. Android `cRGame::Init2()` independently calls
`cRCameraman::Init()` and preserves every field offset through +0xd4. The broad
initializer remains at the honest 5.65% frontier with 74 clean and 17
mismatched operands.

## 2026-07-13 root track/world BOD catalog

The constructor and this producer jointly close `GameRoot +0x44100..+0x48e00`
as one 352-record `RootBodCatalog`. The recovered startup roles are:

- index 0: universe-hole quad;
- indices 5..17: floor/warning/slide corner banks and `Tramp.x`;
- indices 22..57: eight pillars, three eight-slice banks, three ramp edges,
  and the lazer donor;
- indices 58..345: the complete 8x4x3x3 fringe catalog; and
- index 351: the `salt.x` donor copied into the 40 runtime salt records later
  in the target.

Indices 1..4, 18..21, and 346..350 remain numbered unknowns because no producer
or consumer has established a role. The corner initializer also proves the
authored-id-to-storage order `0, 1, 3, 2`; the source exposes that mapping
explicitly rather than pretending the physical bank is authored order.

The source now spells the native sprite registration sequence inline, corrects
`StarTail.tga`, restores the missing particle/collision/progress/jet-thrust and
ghost registrations, uses the native Track0/TrackWarn/Slide0 slice families,
and initializes the pillar, ramp, corner, trampoline, hole, and lazer donors
through their actual root owner. Focused Wibo rises from 5.65% (358 candidate
instructions) to 19.90% (1,011/5,411), with 332 clean operands, one unresolved
early helper reference, and 33 expected mismatches across the still-partial
function. The first stack-local no-op constructor is now present; the candidate
frame remains `0x54` versus native `0x12c` because later locals and islands are
still honestly absent.

## 2026-07-13 owned SubLazer and salt clone pools

The next native producer island copies the root `lazer_model` donor into the
20 inline `SubLazer` records at `SubgameRuntime +0x356b00` (stride `0xb0`),
then loads root `salt_model` from `salt.x` and copies it into the 40 inline
`Salt` records at `+0x3578c0` (stride `0x98`). Both slot families retain a
borrowed `SubgameRuntime*` at slot `+0x88`; the lazer pass also registers the
shared texture, sets alpha `0.7` and blend mode `9`, while the salt pass sets
alpha `0.9`, blend mode `12`, and an identity transform.

The source intentionally follows native's field-first induction variables:
the lazer loop advances `object +0x24`, and the salt loop advances
`owner_game +0x88`. This recovers the real ownership and instruction schedule
without padding the candidate. Focused Wibo rises from 19.90% (1,011/5,411)
to 20.29% (1,074/5,411), with 342 clean masked operands, one unresolved early
helper reference, and the same 33 expected mismatches. The later banner and
remaining world/path-template producer islands are still absent.

## 2026-07-13 Banner producer and subgame BOD-group topology

Startup initializes both embedded `BannerPool` records from a root-relative
`index * 0x60` cursor. Each receives a fresh object loaded from
`postofficestop.x`, a zero position, its `SubgameRuntime* owner_game`,
visibility mode `0` or `1`, zero phase, and the exact phase step
`0x3be38e38` (`0.006944444f`). The source keeps that native cursor shape while
using the shared `Banner` fields; a compact `Banner&` trial was rejected because
VC6 retained the full record pointer in a spare register and regressed the
focused match.

The following island proves the live-list ownership of the adjacent ten
constructed `BodBase` records. Startup adds `track_body_list_head` to
`GameRoot::active_bod_list`, then inserts eight siblings after that same head in
this authored order:

1. `barrier_sub_lazer_list_head`
2. `salt_hazard_list_head`
3. `golb_vapour_list_head`
4. `fringe_attachment_list_head`
5. `special_track_cell_list_head`
6. `unknown_bod_355cec`
7. `landscape_slice_list_head`
8. `unknown_bod_355c7c`

Because every insertion is directly after the track head, runtime traversal is
the reverse of that sibling order. The tenth constructed record at `+0x355d5c`
is not linked here. A full-binary displacement scan found no direct consumer for
`+0x355c7c`, `+0x355cec`, or `+0x355d5c`, so those roles remain unnamed. The
same scan proves `+0x355c44` as the ten-slice landscape anchor in
`activate_landscape_entry` and `+0x355d24` as the embedded Golb vapour anchor in
`create_golb`.

The shared `BodNode::add_bod_after` helper reproduces the authored
`cLinkedList<cRBod>::AddAfter` semantics without padding or volatile scheduling.
Focused Wibo rises from 20.29% (1,074/5,411 candidate instructions) to 21.02%
(1,288/5,411), with clean masked operands increasing from 342 to 360 and
expected mismatches falling from 33 to 31. Binary Ninja now carries the whole
ten-record band in `FrameSubgameRuntime`; field-xref search remains empty for
the two global-root consumers because they address through the relocatable game
base rather than a typed receiver.

## 2026-07-13 first authored path-template family

The next producer begins with the native debug marker
`"path generation start\n"`, then fills the already-constructed embedded path
bank in authored order. The first coherent family is deliberately non-linear:

1. pairs `0`, `1`, and `2`: `LOOPTHELOOP` with `(6,3)`, `(6,2)`, and `(8,4)`;
2. pair `6`: `LOOPTHELOOPW` with `(8,4)`; and
3. pairs `3`, `4`, `5`, and `7`: the `(3,2..4)` loop variants followed by
   `LOOPBOW (6,4)`.

Every primary path receives a fresh strip-mesh object, the authored builder and
Slide0/Back/VeryDark texture set, and a zero body position. Its secondary path
receives a fresh object, mirrors the primary across X, and is likewise reset.
Both paths then build a Fringe-textured side mesh whose owned `fringe_mesh_bod`
position is zeroed.

The constructor independently proves that `Path` owns the leading `BodBase`
and a second `BodBase` at `+0x60`; the source and analysis headers now encode
both relationships, and Binary Ninja carries the same exact `0xa8` layout.
Adding this real producer family raises the focused bootstrap from 21.02%
(1,288 candidate instructions) to 26.16% (1,629/5,411), with 474 clean masked
operands. The one unresolved early constructor call and 36 alignment-dependent
operand mismatches remain outside this path slice.

## 2026-07-13 advanced turn path family

The next contiguous native producer island fills another deliberately
non-linear authored family:

1. pairs `37` and `38`: `TURNOVER` and `TURNOVERDOUBLE`, both `(6,4,1)`;
2. pairs `43` and `44`: `TWISTER (2.5,3)` with handedness `1` and `0`;
3. pairs `45` and `46`: `TWISTER2 (2.5,3)` with handedness `1` and `0`;
4. pair `39`: `TURNUNDER (6,4,1)`; and
5. pair `41`: `INVERT (6,8,1)`.

Each producer follows the same owned `PathPair` lifecycle as the first family:
allocate the primary and secondary render objects, build the primary, mirror it
into the secondary, zero both inherited body positions, build both fringe
meshes, then zero both owned fringe-body positions. The focused bootstrap rises
from 26.16% (1,629 candidate instructions) to 30.58% (1,973/5,411), with 594
clean masked operands. The pre-existing one unresolved call and 36
alignment-dependent operand mismatches are unchanged.

## 2026-07-13 independently authored path-pair members

The following native island first completes the mirrored advanced shapes, then
proves that not every `PathPair` derives its secondary record from its primary:

1. pair `42`: `HALFPIPE (6-bit-pattern,8,1)`, mirrored with the standard
   Slide0/Back/VeryDark surfaces;
2. pair `40`: `WIBBLE (6,8,1)`, mirrored with Slide0 on both main surfaces;
3. pair `31`: two separately initialized `SUPERTRAMP (6,2,1)` records, each
   owning the TrackWarn underside and using `BuildFringeSuperTramp`; and
4. pair `36`: two separately initialized `START (4,8,1)` records, where the
   secondary uses the distinct `Slidex.tga` middle surface.

The independent records each allocate their own render object and run the full
builder rather than calling `mirror_path_template_pair_x`. This recovers a real
per-member ownership distinction that the `PathPair` container alone could not
express. The focused bootstrap rises from 30.58% (1,973 candidate instructions)
to 33.02% (2,155/5,411), with 662 clean masked operands and unchanged problem
counts.

## 2026-07-13 loop-out path family

The next authored family fills mirrored `LOOPOUT` pairs in native order rather
than array order: pair `25` uses `(3,4,1)`, pair `27` uses `(5,4,1)`, and pair
`26` uses `(3,3,1)`. All three own the standard Slide0/Back/VeryDark surfaces
and independent primary and secondary render objects; the secondary geometry
is produced by mirroring the primary before both records build their fringe
body.

This family raises the focused bootstrap from 33.02% (2,155 candidate
instructions) to 34.49% (2,284/5,411), with clean masked operands increasing
from 662 to 707 and the existing problem counts unchanged.
