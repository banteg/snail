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

## 2026-07-13 snail cutscene animation ownership

The first animation bank after path construction is owned by the embedded
`SubgameRuntime::player.presentation` snail. Startup constructs and loads its
ten `cutscene_animation_slots` in native order: a config-selected base clip,
then move, bobalong, left/right lookback, fall, damaged, into-shell, skid-stop,
and talk. The base name is copied from the loader's `Test:` line through its
extension when present, with `turbo-base-000.x` as the native fallback. All ten
slot objects and the snail's main object receive toon mode and zeroed distortion.

The adjacent hotspot storage is not a loose model pointer plus an unrelated
matrix. Calls and consumers prove one complete `RenderableBod` at snail
`+0x164c`: its object is at `+0x1670` and its transform at `+0x1684`.
`initialize_cutscene` and `update_snail_skin` remain exact after spelling that
shared owner; `build_snail_hotspots` remains unchanged at 83.78%.

Focused Wibo rises from 49.81% (4,078/5,411 candidate instructions) to 51.10%
(4,260/5,411), with clean masked operands rising from 1,300 to 1,352. The broad
alignment audit reports one unresolved early helper and 39 expected mismatches;
the added native island's object offsets, asset order, and calls were checked
directly against `0x40f284..0x40f57d`. No padding or score-only scaffolding was
added.

## 2026-07-13 snail equipment animation ownership

The contiguous animation producer continues through the embedded jetpack and
three weapon channels. The jetpack channel owns its main base object plus base
and draw slots `0..1`. The weapon channel array's authored order is left,
right, top; each channel owns one main base object and five slots:

- left: blaster base/draw/fire, then laser base/draw;
- right: blaster base/draw/fire, then laser base/draw; and
- top: blaster base/draw/fire, then rocket-launcher base/draw.

Startup allocates every object through `g_object_list`, loads the exact native
clip spelling (including the original mixed-case names), and applies the same
toon flag and zero distortion to every slot object and channel main object.
Direct root-relative member accesses are intentional: retaining a temporary
channel pointer made VC6 rebase the remaining function around that subobject,
unlike native, and was rejected.

The recovered producer now reaches `0x40fb40`. Focused Wibo rises from 51.10%
(4,260/5,411 candidate instructions, 1,352 clean operands) to 52.00%
(4,565/5,411, 1,401 clean operands). The broad alignment audit reports one
unresolved early helper and 49 expected mismatches; native object offsets,
assets, call order, and the repeated two/five-slot loops were checked directly.
No fake padding or operand-only matching was introduced.

## 2026-07-13 post-animation runtime ownership

The contiguous startup producer now continues through the texture, projectile,
barrier, and render-cache handoff at `0x40fb46..0x40ffd6`:

- `SnailSkin +0x04` owns three `TextureRef*` material overrides for the base,
  damage, and invincible snail skins. The former integer-slot spelling was
  rejected by the three direct `get_or_create_texture_ref` stores.
- `Invincible` is a real `RenderableBod` child, not a flattened
  vtable/padding view. Its inherited object at `+0x24` owns
  `invincible-base-000.x`; startup clears
  `OBJECT_FLAG_DISABLE_CULLING` after loading it.
- Each `GolbShot` overlays a `Vapour` at `+0x080` with its secondary render
  body, while the tertiary rocket body at `+0x118` overlaps the live matrix at
  `+0x150`. The shared rocket mesh is owned by shot zero and borrowed by all
  twelve shots. The checked C and C++ layouts retain this as a union; the
  Binary Ninja projection deliberately does not flatten the overlapping views.
- The animation donors and their live presentation objects raise
  `OBJECT_FLAG_DYNAMIC_VERTICES`; vapour output combines that bit with
  `OBJECT_FLAG_DISABLE_CULLING`. These are shared render-object policies, not
  startup-local magic masks.
- `GameRoot +0xb24` is the exact `Track` (`cRTrack`) owner: four primary track
  textures, four secondary slide textures, and the current set at `+0x20`.
  Startup also applies the recovered texture flags and two-level mip policy.
- The final island constructs the embedded `SubgameRuntime::barrier`, loads its
  object, clears its inherited position, applies the authored translucent
  color/blend mode, and initializes the owned `SegmentCache`.

Focused Wibo rises from 52.00% (4,565/5,411 candidate instructions, 1,401 clean
operands) to 54.48% (4,887/5,411, 1,516 clean operands). The one unresolved
early helper remains, with 56 expected broad-alignment mismatches. The native
Golb loop chooses an object-field induction pointer while the semantic source
keeps a `GolbShot*`; that small code-shape difference is retained rather than
replacing the recovered owner with offset arithmetic. No fake padding or
score-only scaffolding was added.

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

2026-07-14 sound-bank ownership: the startup call now passes the typed
52-record `SoundBankEntry` array directly instead of taking the address of a
single `void*`. iOS names the authored record `cRSoundBank`, while Android
names the corresponding global `gSFXBank`; both preserve Windows' 12-byte
path/sample-id/normalization layout. The caller remains byte-identical.

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

## 2026-07-13 hump and dump height profiles

The next four mirrored pairs form two matched `HUMP`/`DUMP` profiles. Pairs
`16` and `17` use curve scale `4`, height `1`, width `3`, and side mode `1`;
pairs `18` and `19` repeat those owners at the native `0.300000012` height.
All four retain the standard Slide0/Back/VeryDark material set and separately
owned primary, secondary, and fringe render bodies.

The focused bootstrap rises from 34.49% (2,284 candidate instructions) to
36.46% (2,460/5,411), with clean masked operands increasing from 707 to 767
and the existing problem counts unchanged.

## 2026-07-13 hill, valley, and S-bend profiles

The following seven mirrored pairs form one native undulation band:

1. rising `HILL_VALLEY` pairs `8`, `10`, and `9`, covering width `8` centered,
   width `4` uncentered, and width `4` centered at height `4` and length `20`;
2. pair `14`, an `SBEND` with width/height `8`, z amplitude `14`, and Track0 on
   both main surfaces; and
3. descending `HILL_VALLEY` pairs `11`, `13`, and `12`, using the same width and
   centering pattern at height `-4` and length `20`.

The wide hill/valley records use Slide0 on both main surfaces, while the two
rising width-4 variants retain Back as the secondary surface. All seven own
independent primary and mirrored secondary render bodies plus two fringe
bodies. The focused bootstrap rises from 36.46% (2,460 candidate instructions)
to 39.61% (2,768/5,411), with clean masked operands increasing from 767 to 870
and the existing problem counts unchanged.

## 2026-07-13 dip, screw, and slalom family

The next native construction island owns five ordinary mirrored `PathPair`
records in authored order: dip pair `20`, screw pair `21`, slalom pair `22`, big
slalom pair `23`, and double-slalom pair `32`. Pair `32` is therefore grouped
with the slalom family by construction order even though its storage follows a
later run of unrelated templates.

Each primary receives a separately allocated render body, each secondary
receives another body before mirroring the primary, and both paths build and own
their own fringe bodies. The dip uses width `2`; the screw uses 24 curve samples
and width `3`; all three slalom variants use 32 curve samples and width `4`.
Slide0 is the primary surface throughout, with Slide0 retained on the screw and
Back used by the other four variants. The focused bootstrap rises from 39.61%
(2,768 candidate instructions) to 41.70% (2,983/5,411), with clean masked
operands increasing from 870 to 945 and the existing problem counts unchanged.

## 2026-07-13 worm render ownership

Pair `24` owns the worm primary and a separately allocated mirrored secondary,
but its embedded fringe bodies follow a distinct lifecycle from every preceding
path family. Both fringe bodies receive real `Object` allocations and are then
passed to the independently proof-grade `disable_object_rendering` helper
instead of building visible fringe meshes. The two visible path objects retain
blend mode `8`.

This proves that `Path::fringe_mesh_bod` is always owned storage, while the
presence of an allocated object does not imply visible fringe geometry. The
shared object header now exposes the helper with its recovered `Object*`
contract, and the same name and prototype are applied in Binary Ninja. The
focused bootstrap rises from 41.70% (2,983 candidate instructions) to 42.13%
(3,030/5,411), with clean masked operands increasing from 945 to 962 and the
existing problem counts unchanged.

## 2026-07-13 sweep, cage, and P transitions

The next authored island crosses storage order again: sweep pair `28`, cage pair
`15`, then P-transition pairs `33`, `34`, and `35`. All five use independently
allocated primary and secondary path objects, mirror into the secondary, and own
one fringe body per side.

The sweep uses scale/width `4`; the cage uses width `3`. The P variants share
scale `4`, width `3`, and 14 curve segments, but form an intentional three-part
lateral sequence: `0.5` to `-2.5`, `-2.5` to `2.5`, then `2.5` to `0.5` for
variants `0`, `1`, and `2`. All five use Slide0/Back/VeryDark materials. The
focused bootstrap rises from 42.13% (3,030 candidate instructions) to 44.21%
(3,252/5,411), with clean masked operands increasing from 962 to 1,037 and the
existing problem counts unchanged.

## 2026-07-13 snake and handed toad fringes

Snake pair `29` is followed in native order by toad pairs `47` through `50`,
again proving that construction families are not laid out contiguously in the
template bank. All five records own independent primary, mirrored secondary,
and per-side fringe render bodies. The snake uses scale `2`, width `4`, and the
Slide0/Track0/VeryDark material set.

The toads encode left/right shape in the constructor flag and also author their
fringe placement independently. Pairs `47` and `48` use centered fringes for
constructor modes `1` and `0`. Pair `49` uses `-1` on the primary and `1` on the
mirror; pair `50` reverses those offsets. This shows that mirroring path geometry
does not implicitly mirror the fringe-builder offset. The focused bootstrap
rises from 44.21% (3,252 candidate instructions) to 45.93% (3,459/5,411), with
clean masked operands increasing from 1,037 to 1,112 and the existing problem
counts unchanged.

## 2026-07-13 borrowed loop-entry meshes

Auxiliary loop pairs `51`, `52`, and `53` own scale/width combinations `6/3`,
`6/2`, and `8/4`. Their primary and mirrored secondary paths each own a render
body and fringe body exactly like visible path pairs, but their strip meshes are
then borrowed by public pairs `0`, `1`, and `2` as entry-transition geometry.

For each public path, `entry_transition_strip_mesh` points to the corresponding
auxiliary path object while `entry_base_strip_mesh` points back to the public
path's own object. No object ownership is transferred by these assignments. The
native initializer also constructs a separate white path-transition color with
alpha `0.60000002` immediately before this auxiliary bank. The focused bootstrap
rises from 45.93% (3,459 candidate instructions) to 47.02% (3,620/5,411), with
clean masked operands increasing from 1,112 to 1,159 and the existing problem
counts unchanged.

## 2026-07-13 remaining public loop-entry meshes

The same borrowed transition contract extends across the rest of the public
loop bank in native construction order: loop-the-loop-wide pair `57` feeds
public pair `6`; width-2/3/4 loop pairs `54`, `55`, and `56` feed public pairs
`3`, `4`, and `5`; and loopbow pair `58` feeds public pair `7`.

Every auxiliary pair still owns its primary, mirrored secondary, and both
fringe bodies. Public pairs `3` through `7` retain their own objects in
`entry_base_strip_mesh` and borrow only the corresponding auxiliary objects in
`entry_transition_strip_mesh`. Together with the preceding slice, this recovers
the complete auxiliary ownership graph for public loop pairs `0` through `7`.
The focused bootstrap rises from 47.02% (3,620 candidate instructions) to 48.52%
(3,875/5,411), with clean masked operands increasing from 1,159 to 1,234 and the
existing problem counts unchanged.

## 2026-07-13 final auxiliary transition group

The path bank closes with auxiliary invert pair `62`, then loopout pairs `59`,
`61`, and `60` in native construction order. They own independent primary and
mirrored secondary objects plus both fringe bodies. Public invert pair `41`
borrows pair `62`; public loopout pairs `25`, `27`, and `26` borrow pairs `59`,
`61`, and `60` respectively. As before, each public path retains its own object
as `entry_base_strip_mesh`, so none of these links transfer ownership.

Pair `60` is the only path record whose four positions are cleared by calls to
`zero_vector3` instead of inline stores. The independently exact helper has five
total xrefs: these four embedded path/fringe `BodBase.position` vectors and the
barrier position. This disproves the old scratch-local `initialize_distort`
owner and recovers a shared `Vector3` operation. The native path phase then
closes with `debug_report_stub("path generation end\n")` before snail animation
assets begin. The focused bootstrap rises from 48.52% (3,875 candidate
instructions) to 49.81% (4,078/5,411), with clean masked operands increasing
from 1,234 to 1,300 and the pre-existing audit problem counts unchanged.

## 2026-07-14 root player-array ownership

The final two-record player bootstrap is authored through the enclosing
`GameRoot::players` array, not through a cached `GamePlayer*`. Native computes
`GameRoot + player_index * 0x1f8` and then accesses the record through biased
root-relative offsets; adding the array's `+0x124` base maps those accesses
exactly to the recovered `GamePlayer` fields. Direct array expressions restore
that induction base while retaining the typed transform, camera, input,
frontend-overlay, cursor, score-entry, and player-name owners.

The Help and menu-background loads now use the already curated
`g_help_script_path` and `g_menu_background_script_path` globals rather than
creating duplicate string-literal references. Focused Wibo rises from 80.28%
to 80.49% with the candidate still at 5,391/5,411 instructions. Clean masked
operands rise from 1,540 to 1,542; unresolved operands remain 75 and broad
alignment mismatches fall from 35 to 33.

Native also reserves a distinct final `0x40` matrix temporary for the player
initializer. A second typed `TransformMatrix` was rejected because the shared
`Vector3` default-constructor view adds code absent from this native function;
a raw backing array exposed the expected lifetime but left every fixed local
four bytes high due an earlier animation-name spill and did not improve the
aggregate match. Neither experiment is retained. The semantic source keeps the
existing typed matrix until the preceding path/animation register allocation
can recover the native stack layout without padding, undersized storage, or
other score-only scaffolding.

## 2026-07-14 replay-suppression owner closure

The startup clear at root `+0x4f2e0` now names
`GameRoot::intro.hide_for_replay_latch`. Exact `Intro::update_new_game_menu`
proves the owning controller and `update_subgame` proves the downstream HUD
suppression lifecycle. The broad initializer remains byte-identical at 80.49%,
5,391/5,411 instructions, with 1,542 clean operands.

## 2026-07-14 canonical bootstrap root graph

The startup environment block now names the root-owned fog color and scalar
state, fixed-step count and accumulator, frame counter, and render-skip count.
Exact frame-loop and renderer consumers independently prove those members. The
inline BOD linker reaches `GameRoot::active_bod_list.first` through the typed
root owner while retaining the native global reload.

The startup services now borrow `subgame.landscape_manager` directly. The
second menu-background load retains its independent global root reload but
follows the same canonical `GameRoot -> SubgameRuntime -> LandscapeManager`
path. Sub-lazer and salt slots likewise store `&subgame` as their borrowed
owner backlink instead of reconstructing it from root `+0x74618`. Focused
output remains byte-identical at 80.49%, 5,391/5,411 instructions, with 1,542
clean operands; the two still-unknown startup words at root `+0x514/+0xb48`
remain raw.

## 2026-07-14 inline hazard renderable inheritance

The SubLazer and Salt bootstrap loops now consume the shared inherited
`RenderableBod` prefix: typed `Object*`, `tColour`, and `TransformMatrix`
members replace duplicated prefix lanes while each manager retains its exact
inline array extent. The large initializer remains at its prior 80.49%,
5,391/5,411 baseline; exact constructors, spawners, and Salt updater remain
byte-identical, and the near-exact SubLazer updater is byte-stable.

## 2026-07-14 animation-channel object ownership

Jetpack and all three weapon channels now install their animated `Object*`
through inherited `BodBase::set_bod_object`, without cast-only prefix views.
Their slot banks remain separately owned by each channel. The broad initializer
is byte-identical at 80.49%, 5,391/5,411 instructions, with 1,542 clean
operands.

The same inherited-owner rule now covers the root `Snail` presentation and
each manager-owned `Salt` slot. Both call `set_bod_object` through their
recovered `RenderableBod` base directly; the field-first SubLazer induction
remains intentionally explicit because that loop's native source shape walks
the embedded `object` lane rather than whole records.

## 2026-07-14 active-list method ownership

The final startup insertions now invoke `add_bod_to_front` and
`append_bod_to_end` on `GameRoot::active_bod_list` itself. Their exact bodies,
the root constructor, and all inline list users agree on the same 0x0c-byte
`BodList`; the former `BodListEndpointsView` had no separate storage or ABI
role and is retired. This is an ownership clarification, not a derived-list
relationship.

## 2026-07-14 sound-manager method ownership

The startup sound-bank call now uses `g_sound_effect_manager` as its receiver.
Native pushes the 52-entry bank, loads the manager at `0x78ff88` into `ecx`,
and calls exact `SoundEffectManager::initialize_sound_bank`; Android likewise
binds `gSFXBank` through `gRSound`. This closes the owner shared with the exact
positional/default/scaled playback overloads.

The focused bootstrap improves from 80.49% (5,391/5,411 instructions, 1,549
clean operands) to 80.50% (5,392/5,411, 1,550 clean operands), while the 101
broad alignment mismatches remain unchanged.

## 2026-07-14 startup-only root dwords

The two remaining raw root stores at `+0x514` and `+0xb48` are now canonical
`GameRoot` members with their proven dword width, while deliberately retaining
offset-based names. A complete Binary Ninja constant sweep finds no field
consumer for either lane beyond startup's zero stores; other `0x514` hits are
stack-frame displacements and the other `0xb48` hit is unrelated data. That is
enough evidence to distinguish owned four-byte storage from padding, but not to
assign gameplay semantics. The initializer now writes
`unknown_000514`/`unknown_000b48` directly with no guessed name or fake owner.

## 2026-07-14 derived field-first pool cursors

The two deliberately field-first startup loops retain their native induction
shape while deriving every remaining owner-sensitive constant. The SubLazer
cursor now gets its 20-slot extent, `BodBase::object` backtrack, and
`SubLazer::owner_game` delta from the recovered manager and inherited layouts.
The banner cursor similarly derives its root-relative pool base from
`GameRoot::subgame` plus `SubgameRuntime::banners`, and its two-slot extent from
`BannerPool::slots`. No pointer was promoted to a whole-record iterator because
that would discard the native source shape encoded by the generated loop.

The focused result remains 80.50% (5,392/5,411 instructions, 1,550 clean
operands, 101 known broad mismatches). A separately saved pre-change object and
the rebuilt object produce the same normalized candidate-listing SHA-256,
`df7a171903be7dac262a2012d9000dfb6d1df49b3764539fae538cfd6486efd3`.

## 2026-07-14 paired root player/input capacity

`GAME_ROOT_PLAYER_SLOT_COUNT` now owns the shared two-entry extent of
`GameRoot::game_inputs` and `GameRoot::players`. Startup stores that capacity
in `player_count`, initializes both input records, then initializes each player
and gives it the correspondingly indexed borrowed `GameInput*`. The root
constructor independently walks two complete 0x70-byte input owners and two
complete 0x1f8-byte player owners. Binary Ninja also pins the arrays at
`+0x44` and `+0x124` and the runtime count at `+0x40`. This is a derived paired
capacity, not a guessed limit or an original-symbol spelling claim.

## 2026-07-14 presentation animation bank extents

The startup post-load passes now derive the ten-slot cutscene extent and each
five-slot weapon-channel extent from their owned
`PresentationAnimationSlot` arrays. The exact Snail constructor independently
walks those same full banks, and Binary Ninja types them as `[10]` at
`Snail +0x14c` and `[5]` at every channel `+0x150`. The jetpack pass
intentionally remains a count of two: its channel owns five slots, but startup
loads and post-processes only the base and draw clips. Keeping that subset
separate avoids falsely equating populated assets with storage capacity.

## 2026-07-14 canonical live-root service access

The three deliberate singleton reloads in the world initializer now retain the
canonical `GameRoot* g_game` type. The field-first active-list helper, menu
landscape load, and star-manager insertion still reload the live process root,
but no longer discard its `active_bod_list`, `subgame`, or
`landscape_manager` ownership through a `char*` cast.

This is byte-stable at the existing 80.50%, 5,392/5,411 instruction frontier,
with 1,550 clean operands and the same 101 broad alignment mismatches.

## 2026-07-14 render-scene ownership

The five camera-slot high bits are now one shared `RenderSceneFlag` contract:
slots 0, 2, and 3 own overlay scenes 0, 1, and 2; slot 1 owns player 0; and
slot 4 owns player 1. The two embedded player cameras receive the same scene
bits as their borrowing slots. `render_game_frame`, the exact font queue drain,
the exact front-end overlay draw, and BOD construction independently consume
the same high-byte mask.

Replacing the seven startup literals with those named owners is codegen-neutral
at the existing 80.50% frontier (5,392/5,411 instructions, 1,550 clean operands,
101 known broad mismatches).

## 2026-07-15 live root-overlay replay

The narrow Binary Ninja overlay sync now persists the same three constructor-
proven `GameRoot` owners used by the matcher: `overlay_0 +0x67c`,
`overlay_1 +0x7c8`, and `overlay_2 +0x914`. The sync applies those fields and
the overlay prototypes through one previewed batch, avoiding a separate full
analysis/save cycle for every field.

Refreshing the initializer recovered its previously skipped 2,432-line HLIL
body. The tracked export now spells every camera loan and constructor call
through the corresponding overlay owner, while a focused health check rejects
regression to raw `+0x67c/+0x7c8/+0x914` root offsets or an unavailable body.
No matcher source changed, so the existing 80.50% frontier is preserved.

## 2026-07-15 root DirectX-loader replay

The exact `DirectXLoader` extent at root `+0x48e00` is now part of the durable
object-render sync. Its 0x5e10 bytes end exactly where the independently proven
`Backdrop` begins at `+0x4ec10`; the initializer and the loader's four exact
methods supply 48 mesh/animation callsites plus the direct `animation_bytes`
consumer.

The refreshed HLIL replaces every raw `game +0x48e00` receiver with
`game->directx_loader`, including the cutscene, equipment, and projectile
animation banks. The object-render sync now batches its struct fields and
prototypes in one previewed transaction, and the initializer health check
rejects loss of the root loader owner. Matcher output remains byte-stable at
80.50% because this closes analysis replay rather than changing source shape.

## 2026-07-15 root BOD-catalog replay

The constructor-proven `RootBodCatalog` is now installed at `GameRoot
+0x44100` by the repeatable Binary Ninja sync. Its exact 0x4d00-byte extent
ends at `directx_loader +0x48e00`, so this names the complete 352-record owner
without consuming any unknown neighboring storage. The sync now batches its
root field and initializer prototype in one previewed transaction.

Refreshing the seven real consumers propagates the same owner graph through
the initializer, runtime track-cell population, run condensing, warning
promotion, floor/slide harmonization, edge selection, and fringe construction.
Health checks pin representative pillar, corner, slice, ramp, universe-hole,
and fringe accesses; `construct_game_runtime` was inspected but deliberately
left unexported because its HLIL did not improve. Matcher output remains at the
byte-stable 80.50% initializer frontier.

## 2026-07-15 front-end presentation owner replay

The remaining constructor-proven presentation block is now durable in Binary
Ninja: `Intro +0x4f2dc` spans exactly 0x48 bytes, `StarManager +0x4f33c`
spans exactly 0x4c bytes, and `Logo +0x4f400` spans exactly 0x25218 bytes to
the independently proven `SubgameRuntime +0x74618` boundary. The refreshed
initializer consequently names its replay latch, logo open, active-list
insertion, and star-field open through those real embedded owners.

The shared declaration helper now previews broad header imports and refuses a
complete-struct to zero-width regression. Intro and Logo additionally replay
only their owned exact-size types, preventing their dependency declarations
from replacing richer canonical rendering or widget layouts.

## 2026-07-15 front-end menu owner replay

The constructor-proven control block is now complete around the presentation
owners: `MainMenu +0x4f324` is exactly 0x18 bytes, `Options +0x4f388` is
exactly 0x24 bytes, and `Exit +0x4f3ac` is exactly 0x1c bytes. The initializer
now reaches the audio configuration helper through `game->options`; the
remaining incidental scalar assignment is Binary Ninja's x87-control lift,
not an authored return contract.

## 2026-07-15 shared front-end root ownership

The IDA receiver is now `GameRoot *`, and the complete constructor-proven
front-end block composes with `SubgameRuntime`, `HighScore`, `TipManager`, and
the other established tail owners in one guarded graph. The initializer now
names its path-template bank, tip manager, star manager, and backdrop through
their real embedded owners. The replay refuses to overwrite any independently
typed overlap and falls back to the tail-only graph until every exact front-end
type is available.

This ownership-only improvement leaves the focused native frontier at 80.50%
(5,392/5,411 instructions; 1,550 clean and 101 mismatched operands).

## 2026-07-15 catalog and loader root composition

The guarded IDA root replay now composes the constructor-proven
`RootBodCatalog +0x44100` (exactly `0x4d00` bytes) and
`DirectXLoader +0x48e00` (exactly `0x5e10` bytes) immediately before
`Backdrop +0x4ec10`. The initializer consequently exposes the catalog's real
corner, slice, pillar, fringe, and universe-hole owners together with the
loader's cached-mesh and animation storage. There is no invented gap or
overlapping convenience view between these independently bounded owners.

This is an analysis-only replay: the matching source is unchanged and the
focused frontier remains 80.50% (5,392/5,411 instructions; 1,550 clean and
101 mismatched operands).

## 2026-07-15 root prefix and border-pool composition

The guarded BN/IDA replay now closes the exact root prefix before the existing
catalog graph: callback/fog state through `+0x24`, `frontend_link_latch` at
`+0x568`, three overlays, the standalone no-op renderable, and the complete
`BorderManager +0xb4c`. The manager names its `BorderStack`, 150 exact
`BorderRecord` backing slots, and delayed-widget tail without conflating those
slots with the `FrontendWidget*` view returned to callers.

This remains analysis-only. A fresh focused compile is unchanged at 80.50%
(5,392/5,411 instructions, 1,550 clean and 101 mismatched operands).

## 2026-07-16 texture descriptor ownership closure

The shared `TextureRef` replay now names `loaded_width +0x04`,
`loaded_height +0x08`, and `mip_levels +0xa0` consistently in both
decompilers. Exact `load_registered_texture_ref` writes the two dimensions and
passes `mip_levels` to both D3DX creation paths; exact
`get_or_create_texture_ref` initializes the latter to one. This initializer's
eleven direct stores then raise selected world and track textures to two mip
levels. No unknown padding was promoted without a concrete consumer, and the
matcher source remains byte-stable.
