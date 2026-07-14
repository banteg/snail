# PINNED — 92.55%, 322/322 insns exact (2026-06-12)

Structure-exact; every remaining diff line is register allocation
(eax/edx/ecx swaps), one faddp vs fadd+fstp pair from upstream register
pressure, and the lea/push ordering in the orientation block. Semantics
fully proven. Source-shape notes: ramp branch is the fall-through
(`if (first > z)`), all three [0,1] clamps are `if (v<0) v=0; else if
(v>1) v=1;`, the pitch clamp clamps-then-calls once, and the steer roll
needs sequential assignments to stop VC6 folding -8*0.01745*0.17.

**Findings from the asm:**
- the exit roll while `attachment_exit_pending` reads player+0x42c — the
  ORIENTATION-B carryover (begin_post_follow_carryover writes
  `follow_state.orientation_b` there; the heading carryover at +0x430 still has
  no known consumer). player.h renamed semantically; the Zig camera
  already consumes the right lane (carryover_a = orientation_b phase).
- orientation_a at player+0x39c, orientation_b at +0x3a0 — third
  independent confirmation of the unified follow-struct slot order.
- lift-envelope kind table: {8, 9, 10, 0xe, 0x10, 0x24, 0x2b, 0x2d};
  WORM fov kind = 0x18.
- Cameraman layout: live 0x00 / desired 0x40 / previous 0x80 /
  player 0xc0 / game 0xc4 / fov 0xc8 / byte 0xcc / lift 0xd0 /
  smoothed 0xd4.

# Original dossier (322 insns, 1274 bytes)

update_cameraman @ 0x4461d0, behind 18 camera fix commits and the 06-10
audit findings (base matrix rows, subgame-rate blend). target.asm in this
directory is the normalized reference.

From the IDA export head (full read pending next session):

- thiscall on the cameraman object; player at a member, scratch byte
  +0xcc zeroed on entry
- desired matrix seeded via `initialize_matrix_from_values(&transform,
  1,0,0,0, 0,0.946001,0.324162,0, ...)` — the audit's base rows; the
  helper returns the matrix which is qmemcpy'd into
  `cameraman->desired_matrix`
- `player->cached_camera_target_world.x * 0.4` feeds the m30 lane
- the audited subgame-rate blend (`rate * 0.3`) and the
  `fld [eax+0x2964]` player read are in the body (see
  analysis/runtime/port-parity-audit-2026-06-10.md)
- helpers to declare: initialize_matrix_from_values (returns ptr,
  many float args), matrix blend/lerp helpers — several are already
  matched (set_matrix_identity family)

Next session: read the full IDA export, map the cameraman struct
(desired_matrix offset, player member, the +0x2964 field), write the
scratch. The matched matrix helpers in the corpus should make the calls
cheap to model.

## Full semantics (2026-06-12 read of the IDA export)

Pipeline per tick, all on the desired matrix before the final blend:
base rows (1,0,0 / 0,0.946001,0.324162 / 0,-0.324162,0.946001) with
position (target.x*0.4, 1.8, -0.5), orthogonalized; start-ramp before
first_block_row_count blends y*1.15/(1-t) + y*0.35*t with a
(1-t)*0.87249994 world-x rotation, after the ramp just y*0.35;
attachment lift envelope (kinds 8/9/10/family10/36/43/45/loopw|8):
cos envelope over (live z - anchor z)/segment_count_f scaled 0.35,
smoothed 0.1, cutscene pitch adds a 0.24 envelope at 4.712389*cycle +
pi/2; position x += target.x/3, z += target.z + 0.4 with previous-z
clamped into [z-3, z-1.7]; pitch (-2 - (y-0.49)*5)*0.017449999 clamped
+/-1.2215 world-x; roll = lane-lean cos envelope * amplitude * 2pi +
target.x * -8 * 0.017449999 * 0.17 world-z.

**Open-question answers:**
- when follow active: world-z rotate by orientation_a (via identity
  matrix multiply) THEN by orientation_b — the orientation lanes'
  consumers
- when attachment_exit_pending: world-z rotate by `post_follow_exit_roll`
  at player+0x42c — the orientation-b carryover written by
  `begin_post_follow_carryover`; the raw heading dword at +0x430 still has
  no known consumer
- heading_roll rotates last before the WORM FOV envelope
  (110 + 50 * cos envelope, debug stub call inside) and the 0.3 FOV
  smoothing
- final: linear_interpolate_matrix(live, previous_desired, desired,
  subgame_rate * 0.3) — the audited blend, now mirrored in
  native/matrix_math.zig — then previous_desired = desired

## Type consolidation note (2026-06-15)

The player fields at +0x384..+0x3c3 are the shared embedded 0x40-byte
`FollowState`; velocity, exit state, and post-follow carryover are adjacent
`Player` fields. The canonical embedded member is now proven codegen-neutral
in this scratch.

2026-07-14 Player matrix consolidation: `player.h` now embeds the complete
`TransformMatrix live_matrix` at `Player+0x38`; its position row lands at
+0x68. This replaces the former offset-only row view and is codegen-neutral in
this scratch at 92.55%, 322/322 instructions, with the same one masked call
mismatch.

Scratch next: structure is linear with two matrix locals; the matched
matrix helpers cover every call.

## Verify pass (2026-06-12): Zig camera confirmed against the pipeline

gameplay/camera.zig already carries the full recorded pipeline: base
rows, pitch formula with the +/-1.22149992 clamp, z-deadzone [1.7, 3.0],
FOV 110 + 50*envelope WORM lane with 0.3 blend, lateral roll
-8*0.0174499992*0.17, orientation_a (local z) then orientation_b
(world z) sequence, and the player+0x42c post-follow exit roll. The camera
model is sound; the full match is proof-polish and drops in priority
like collisions. The orientation_a SOURCE remains the basis-derived
proxy (builder rotation scalars still unstored — checklist item).

## Player header consolidation (2026-06-16)

The scratch now includes shared `player.h` instead of carrying a local
`Player` slice. The promoted fields are the lane-lean window at
`+0x350..+0x35c`, `follow_state.template_record +0x388`,
`follow_state.source_cell +0x38c`, `follow_state.orientation_a +0x39c`,
`follow_state.orientation_b +0x3a0`, and `post_follow_exit_roll +0x42c`.
The embedded owner keeps the focused match at `92.55%`, `322/322`, with the
same single masked call mismatch.

## Cameraman header consolidation (2026-06-16)

`Cameraman` now lives in `include/cameraman.h` and is shared with
`initialize_cameraman`. The initializer is exact (`100%`, `20/20`) and this
updater remains at `92.55%`, `322/322`, with the same single masked call
mismatch. The shared layout is live/desired/previous matrices at
`0x00/0x40/0x80`, `player +0xc0`, `game +0xc4`, `fov_degrees +0xc8`, scratch
byte `+0xcc`, and lift envelope fields `+0xd0/+0xd4`.

## 2026-06-21 subgame owner typing

`Cameraman::game` is now typed as `SubgameRuntime*`, removing this
scratch's local `Game` shell. The two consumed owner lanes were already shared
as `SubgameRuntime::subgame_rate` and `first_block_row_count`; focused Wibo
remains at `92.55%`, `322/322`, with the same single masked call mismatch.

## 2026-07-11 authored cRCameraman owner

Android and iOS retain `cRCameraman::AI()`. Android consumes the identical
+0xc0/+0xc4 owner pointers, +0xc8/+0xcc FOV and gate, and +0xd0/+0xd4
envelope pair through the same exact 0xd8-byte layout; `cRSubGame::CameraAI()`
owns the call edge. The shared Windows type is now `Cameraman`, and both
analysis prototypes are corrected from incidental `int` to `void`. Focused
Wibo remains an honest 92.55%, 322/322 instructions, prefix 36/322, with 72
clean masked operands and the existing single call mismatch.

## 2026-07-14 force-camera-update ownership

The former `unresolved_cc` byte is now `force_camera_update`. The outer
`cRSubGame::CameraAI()` path copies `Cameraman +0xcc` into
`SubgameRuntime::camera_snap_requested`, exactly as its alternate cutscene
branch copies `CutScene::force_camera_update` into that gate. This Cameraman AI
clears the request at entry in the Windows build. The rename preserves the
focused 92.55%, 322/322 instruction result and its existing single call-name
mismatch.

The follow-state composition now calls the recovered void const-reference
matrix multiply member directly. Focused output remains 92.55%, 322/322
instructions, prefix 36/322, with the same 72 clean operands and unrelated
pre-existing call mismatch.
