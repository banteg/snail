# High progress — 83.20%, 188/187 insns

This is the per-cell `SubLoc` update, matching the iOS
`cRSubLoc::AI()` owner, not a pooled `FringeObject` method. The receiver's
inherited `BodBase` owns its list node, position, render arguments, object, and
color; the attachment-template backlink, tile id, and lane flags are the same
fields used by the exact runtime-grid builders and near-matched cell teardown.
Semantics complete:

The Windows `SubLoc` constructor installs the table at `0x497368`, whose entry
is this exact address. That direct callback edge closes the owner independently
of the cross-port symbol match.

- gate: `lane_and_flags & SUBLOC_FLAG_AI_ENABLED` (`0x2000`) plus
  `SubgameRuntime::subgame_pause_gate`
- tile 14 (wall2): fires only once `first_block_row_count` is behind the
  embedded player's z; 4% per-tick roll (`random_float_below(100) < 4`);
  spawn at the cell anchor with y+8 and an offset from the encoded
  `SUBLOC_MERGED_RUN_WIDTH_MASK` nibble (`lane_and_flags` bits 8..11);
  aimed at the player with +/-3 vertical jitter +8 z lead; fires only
  when the z delta < -4; direction normalized and scaled to 0.4/tick
  through the owned `SubLazerPool`; then the cull check
- tile 22: cull behind `Player::interaction_max_z`
- tiles 29/30 (attachment skirts): WORM templates fade by rate/30 with a
  fixed alpha; `SubgameRuntime::get_track_skirt_color` syncs into
  `runtime_rows[row].attachment_body.color` (`+0xd8` in the 0xf4-byte row);
  cull at `row_span_count + 5` behind
- default: cull behind the player interaction plane when also past
  `completion_row_start - 5`

RNG call convention is a debug/tag argument, not an RNG state pointer. Raw
image disassembly shows `random_float_below(100)` pushes `0x4a4dc8`, which
resolves to the one-character `"W"` tag, and the vertical jitter
`random_signed_float_below(3)` pushes `0x4a4dc0`, which resolves to `"Wall2"`.
The normalizer masks both pointers as `ADDR`, so the match percentage does not
expose this assumption.

Notable: this TU CACHES the game base (non-volatile pattern, reload
after calls) unlike the seed block in the swept entry — base-caching
behavior is per-function, worth remembering when modeling globals.

2026-06-16 pin audit: focused matcher verifies 42.34%, 172/187 insns.
Keep pinned; RNG tags, emitter cadence, projectile spawn direction, and cull
semantics are recovered, with only source-shape/register golf remaining.

2026-06-21 comparison-shape sweep: spelling the tile-22 cull as
`g_game->cull_plane_z <= position.z` instead of `position.z >=
g_game->cull_plane_z` improves focused Wibo to 43.90%, 182/187 candidate/target
instructions, with 27 clean masked operands. The branch semantics are identical;
the remaining gaps are still broad switch/register allocation shape.

2026-06-21 tile-dispatch pass: replacing the `switch` with the native-shaped
compare ladder for tiles 14, 22, 29/30, and default removes VC6's jump table and
improves focused Wibo to 45.41%. Keeping the lane nibble as `unsigned int`
recovers the native unsigned conversion class (`fild qword`) and improves to
46.36%, with 30 clean masked operands. Reordering the wall2 spawn staging so
`spawn_z` is captured before `spawn_y`, and reading the z delta back from
`direction[2]`, improves the retained shape to 46.77%, 185/187
candidate/target instructions. Function-scope scratch buffers and extra
lane/spawn temporaries were neutral or regressive, so the remaining residual is
still frame/register scheduling around the wall2 vector setup and skirt-color
sync.

2026-06-21 root-view naming: the cached global owner slice is now
`Wall2EmitterGameView` instead of generic `Game`, documenting that the offsets
are root-game globals rather than the embedded `SubgameRuntime`. Focused Wibo
remains 46.77%, 185/187 candidate/target instructions, with 30 clean masked
operands.

2026-07-11 ownership and vector-source pass: the synthetic root and receiver
views are removed. Every global offset now resolves through `GameRoot` into the
owned `SubgameRuntime`, embedded `Player`, `SubLazerPool`, or 0xf4-byte runtime
row. The receiver is the shared `SubLoc`, and the skirt-color
destination is specifically `TrackAttachmentRuntimeRow::attachment_body.color`.

The native 0x34-byte frame is recovered by the ordinary C++ shape: copy the
cell anchor into a `Vector3` spawn, offset y/lane, copy the player position into
a target, and assign `direction = target - spawn` before normalization. Direct
component arrays, constructor initialization, and initializer-form subtraction
all compiled worse; the retained copy/assignment form is semantic source, not a
coercion-only temporary. Spelling the tile-22 comparison as
`position.z >= interaction_max_z` becomes the native comparison order
after the owner rewrite. Focused Wibo improves from 46.77% to 82.67%, 188/187
candidate/target instructions, prefix 26/187, with 34 clean masked operands.

The live Binary Ninja prototypes now agree: this function is a void thiscall on
`TrackRowCell`, `get_track_skirt_color` is a `SubgameRuntime` method returning
`tColour*`, and `shoot_subgoldy` is a `SubLazerPool` method over two vectors.

2026-07-12 authored lifecycle name: the Windows constructor callback and the
high-confidence iOS `cRSubLoc::AI()` crosswalk make the former
`wall2_emitter_maybe_fire_sub_lazer` label actively misleading: Wall2 is only
one case in the full tile-family updater. The stable Windows harness name is
now `update_sub_loc`; this is an ownership clarification and leaves the honest
82.67% object unchanged.
- The rename also retires two downstream provenance errors: `remove_sub_loc`
  is not projectile teardown, and `0x4417d0` is `cRSubLazer::AI()`, not Salt.
  Projectile kill/update remain at `0x441740`/`0x4417d0`; the exact Salt AI is
  `0x441c10`.

2026-07-12 packed-field and vector-idiom pass: `lane_and_flags` is now an
unsigned packed field, agreeing with the analysis-side `uint32_t` layout and
recovering native `shr` for the authored lane nibble without changing any of
the ten dependent scratch scores. The local `Vector3::operator-` now follows
the explicit-result implementation already recovered independently in the
other vector-heavy game methods, rather than this scratch's lone
constructor-return spelling. Focused Wibo improves from 82.67% to 83.20%,
still 188/187 instructions with a 26-instruction prefix, while the clean mask
count rises from 34 to 35. The remaining mismatch is confined to temporary
allocation and scheduling inside the Wall2 spawn/direction block; constructor,
component-assignment, in-place-target, and declaration-order variants were
neutral or regressive and are not retained.

## 2026-07-14 BodBase ownership

All cell-anchor reads now name inherited `SubLoc::position`, while render
arguments, object, color, and active-list links resolve through the same
`BodBase` receiver. The exact constructor and 25,600-cell initialization loop
prove the base and 0x54 stride. Focused output remains byte-stable at 83.20%,
188/187 instructions, prefix 26/187, with all 35 operands clean.
