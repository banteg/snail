# update_subgoldy @ 0x43b120 — 72.44%, 2067/2091 insns, structure complete

The boss of bosses (2091 insns, 8456 bytes) has a full scratch: every block
of the function is transcribed and the diff is dominated by
register-allocation residuals, not semantics. The previously-unread
track-mode slice (steering, replay record/playback, completion handoff,
ghost marking, emitters) is now pinned.

2026-06-13 matcher padding rebaseline: terminal object-padding normalization
removes untargeted bytes after final `ret` instructions, so the same source now
reports 72.44%, 2067/2091 instructions. This is a measurement correction, not
a source-shape change.

## Semantics recovered beyond the old dossier

The dossier covered the follow-consumer block and the exit lanes. The
scratch additionally pins:

- **Steering model** (the oracle's lateral lane): `track_z_offset` is a
  mouse-anchor accumulator clamped to [0, 639];
  `resolve_uncaptured_cursor_sensitivity_scale(flt_4DF950[steering_mode_selector])`
  is called for its side effect each tick; selector 1 maps `steering_x`
  absolutely; steer target = `(320 - offset) * 0.0125` clamped ±3.7;
  `x += rate*0.2 * (target - x)` unless movement_state == 2. Under control
  override the offset is pulled by `-2 * presentation.live_basis_up.x`.
- **Lateral quantization EVERY tick**: `position.x =
  convert_math_type16_to_32(convert_math_type32_to_16(x, 16.0), 16.0)` —
  live x snaps to the 16-bit replay codec grid each frame before being
  recorded. PORT IMPLICATION: a port that doesn't quantize x identically
  accumulates lateral drift against recordings.
- **Replay record**: z stored as 16-bit per-tick DELTA against the
  accumulator `unk_643194` (which re-accumulates the decoded value, so
  codec error never compounds); flags bit0/bit1 = fire buttons, bit2 =
  latch, bit3 = end marker. Recording flags only written while
  `track_state_latch` (game+0xa854) is set; the latch arms when both fire
  bits are released, or unconditionally at cursor > 20.
- **Replay playback**: recorded lateral_x drives position.x directly;
  flags bit2 drives the latch; bit3 triggers the frontend fade-out
  (app states 26/10 + skip byte).
- **Completion handoff machine**: timer step 1/60; entry resets voice
  gate, clamps vz into [rate*0.17, rate*0.5], `reset_voice_manager`,
  `end_jetpack_hover`, cutscene state 5, sound 0; past start+2.5 decays vz
  by 2×quantum; voice 8 at t>2; skip lanes (display gate_18 + fire, or
  display state 5, level_mode ≤ 1) jump the timer to 5.0999999; t>5 holds
  by re-subtracting the step while display state != 5; then frontend fade
  state 0 → begin fade-out, state 4 → flush display + `complete_subgame`
  dispatch (last-level via app+0x12d4644 - 1 → states 29/26; level 7 →
  26/2; else substate = state, state = persistent ? 26 : 27).
- **Cruise window**: every non-handoff tick with z < completion_row_start
  (or exit pending) and no boost/override: vz floored at rate*0.17 and
  capped at rate*0.5. With the track-mode accel only firing below
  first_block_row_count, the steady-state z-velocity oscillation
  (oracle's 0.24–0.31) must come from the COLLISION boosts (speedup
  pickup and ring effects set vz = rate*0.5) decaying through
  (1 - rate*0.003) toward the 0.17 floor — the "tile-boost cadence"
  hypothesis is dead; it's ring/speedup cadence.
- **Ghost marking (level_mode 4)**: record block at game + 129728*arg;
  active flag +0x944150, cursor base +0x944174, count +0x9441bc, ghost
  words stride 6 at +0x9441c2; payload = min(accumulated ghost z, z+20)
  through flt_643190, anchored by player+0x304;
  `mark_current_track_pair_with_payload(float)` each tick.
- **Movement-fire emitters**: require runtime_flags & 0x400000, no
  handoff/override, movement_state 0 or 4; fire cooldown via +0x2730
  progress (+0.3 bias on flags_a fire); replay flags bits 1/2 replay the
  fire actions; app+0x1066bf4 < 10 (the 9-tick startup hold) re-arms the
  cooldown.
- **Wall-14 stall**: probe at z+0.49, y < 6.5; vz = 0,
  z = trunc(z+0.49) - 0.5, squidge z -0.33 (sound 47 on first), stall
  timer at +0x328 → carryover when it wraps past 1.0.
- **Tail**: collisions, 5 anim managers (presentation +0x104, jetpack
  channel +0x12e8, weapon channels +0x754 stride 0x3dc), track parcels
  (game+0x125e480), initialize_cutscene, update_player_movement_flags,
  row event display, frame counter game+0xfd2b7c++, cursor++ == 21000 →
  times-up (game+0x1272828).

## Struct facts (player block)

damage_gauge at +0x3c4 (state is the FIRST field; skin_hold_ticks +0x18),
progress_bar +0x3f0, warning +0x3f4, nuke +0x150, presentation +0x2984
(visual_root* +0x24 with lateral/squidge floats at +0x80/84/88, live
basis_up.x +0x48, cutscene state +0x1964), squidge +0x4344 (y_out +0x00,
z_out +0x0c), slow commentary +0x435c/+0x4360, movement fire +0x2730/4,
slide threshold +0x2738, track_z offset/anchor +0x273c/+0x2740, handoff
cycle +0x2744/8, jetpack gauge +0x2750 (state +0xc, wobble x/y/alpha
+0x14/18/1c), camera target +0x2964, steering selector +0x2970,
interaction_max_z +0x2980, movement_mode_selector +0x40c (0/2 = early
out), movement_state +0x120, resurrect_active +0x84, row event id +0x1e8
+ tip def +0x1ec, ghost anchor +0x304, wall stall +0x328/c, exit voice
timer +0x330/4, lane lean +0x350..+0x35c, timer pair +0x360/+0x368/+0x36c,
nuke progress +0x374/8, handoff timer +0x444/8 + gates +0x44c/d/e.
Game side: level_mode at +0x40 (NOT +0x150), level_mode_arg +0x44,
runtime_flags +0x4c, first_block_row_count +0x50, runtime_row_count
+0x54, completion_row_start +0x58, row event defs +0xa670 stride 16928
(text +0, dismiss +0x200, voice +0x204), level_segment_count +0xa874,
row records +0x5ccac8 stride 244 (flags +0x00: 0x40/0x80 owner bits +
0x100 no-drag; attachment cells +0xa4/+0xa8; event id +0xf0), ghost
blocks +0x944150 stride 129728, frame counter +0xfd2b7c, replay buffer
+0xfd2b80 stride 6, replay state +0xff25d0/d1/d4/dc, parcels +0x125e480,
display +0x12727d8 (state +0x14, gate +0x18; the "2" flag dword sits at
game+0x1270fc8), times-up +0x1272828. App: fade +0x24, hud rows
+0x15c→+0x2cc (0x40 bytes, scroll float at +0x300 inside), states
+0x1b8/+0x1bc, skip byte +0x30c, backdrop +0x4ec10, startup counter
+0x1066bf4, level count +0x12d4644, tip manager +0x12e6f58.

## Source-shape idioms that mattered

- Doubled quantum is `quantum + quantum` via a named local (fadd st0,st0),
  never two products (VC6 folds those into one const).
- Gravity sites need `float gravity = rate*rate*-0.0099999998f;` as a
  named local or VC6 rewrites `+ x*-c` into `- x*c` (fsubr).
- Clamp ladders are written negative-arm-first
  (`if (x < lo) ... else if (x > hi) ...`).
- The pending/floor and floor/gravity branches are polarity-flipped
  (`if (!pending) {floor} else {trampoline}`, `if (floor > y) {snap}
  else {gravity}`) so the trampoline/gravity blocks land last and fall
  into the continuation.
- The follow switch is source-ordered case 1/3 first, case 0 falling
  through into case 2.
- The position stash around the camera block is a Vector3 struct copy
  (dead y/z stores survive), and the camera writes go through a
  `Vector3*` local (lea-reused base).
- The steering lerp needs `pull` and `steer_delta` locals to force the
  fxch evaluation order.
- 2026-06-15 type-consolidation probe: replacing the local `Vector3`
  with shared `vector3.h` preserved the headline score but introduced a
  masked operand mismatch, so this scratch keeps its local view for now.
- 2026-06-15 attachment-layout probe: expanding the local
  `AttachmentSample`/`AttachmentPathTemplate`/`TrackRowCell` views to the
  shared-header field names also preserved the headline score but shrank the
  stack frame and introduced the same jump-table masked mismatch. Keep the
  compact local attachment view until a source-shape fix explains the frame.
- 2026-06-16 tip-manager probe: replacing the local `TipDefinition`/`TipManager`
  view with shared `tip_manager.h` preserved the headline score and instruction
  count but changed the masked audit from 291 ok / 0 mismatch to 290 ok / 1
  jump-table mismatch. Keep this scratch's compact local tip view for now.
- 2026-06-16 timer-counter probe: replacing the local compact
  `TimerCounters` call view with shared `timer_counters.h` and offset-preserving
  padding produced the same masked-audit regression. Keep the compact local
  timer view until the follow-switch layout issue is fixed.
- 2026-06-16 voice-manager probe: replacing the local compact
  `VoiceManager` call view with shared `voice_manager.h` preserved the headline
  score but produced the same 290 ok / 1 jump-table masked-audit regression.
  Keep the compact local voice view until the follow-switch layout issue is
  fixed.

## Named residuals (all register-allocation / micro-shape class)

1. esi/edi zero-register swap born at the wall-14 block (`xor esi,esi`
   native vs `xor edi,edi` here) — cascades through the whole tail.
2. eax/ecx/edx scratch rotation shifted by one from the z-record site:
   native splits the game load (`mov edx,[0x408]; mov esi,edx`), ours
   loads esi directly; the missing split shifts every later scratch pick.
3. The three replay-flag ORs: native `or byte [sib+disp], imm` followed
   by a DEAD `lea eax,[sib+disp]`; no source shape found yet that emits
   the dead lea (likely the same idiom in all three).
4. Frame 0x24 vs 0x40: native keeps more spilled temps (the wall-probe
   y/z temps, v136/v137 camera sums, the x-quantize temp survive as
   distinct slots).
5. `(320 - offset)`: native `fld var; fsubr const`, ours
   `fld const; fsub var`.
6. The two window clamps compare via `fld vz; fcomp st(1)` (vz loaded)
   vs our `fcom [vz]`.
7. Free-lane z / case-2 x integrate operand commutation (velocity-first
   vs position-first) — VC6 commutes one site each way regardless of
   source order so far.

## Zig port residuals (carried from the pre-scratch dossier, still open)

1. native resets the live-matrix rotation to identity in the grounded
   snap; the port only clears the airborne flag (presentation-level).
2. the trampoline envelope uses a shipped-tile floor-height proxy for the
   cell anchor y (the checklist correction stands).
3. +0x41c boost lane is DEAD CODE in the shipped binary (only ever
   written 0) — the port correctly omits it.
4. NEW (this scratch): the per-tick 16-bit lateral quantization and the
   replay z-delta accumulator are not modeled in the port — audit
   `stepActivePhase`/the oracle harness for codec parity on x.
