# release_snail_weapons @ 0x442e40

Death-cutscene helper that arms the snail weapon and jetpack channel release
steps once, then marks `InvincibleShellController::channel_release_steps_active`.

Recovered relationships:

- The one-shot gate is the existing
  `PlayerPresentationController::invincible_shell.channel_release_steps_active`
  byte at `presentation +0x1934`.
- Release step writes target:
  - `jetpack_channel.release_step` at `+0x15b0`;
  - `weapon_channels[0].release_step` at `+0x0a1c`;
  - `weapon_channels[2].release_step` at `+0x11d4`;
  - `weapon_channels[1].release_step` at `+0x0df8`.
- The Z release component is `owner_player->velocity.z * 0.30000001f`.
- The helper ends live jetpack hover through `owner_player->jetpack_gauge`.

Focused match:

- 2026-06-18: 49.55%, 125 target instructions versus 97 candidate
  instructions.
- 2026-06-21: 88.80%, 125 target instructions versus 125 candidate
  instructions, 32 ok masks. Staging the release vector through a stack
  `Vector3`, making the `random_y + 0.5f` adjustment explicit, and reusing the
  staged `z` slot for the raw forward velocity recovers the native component
  spill/store shape.
- This callsite needs the two-argument `random_float_below(1.0f, 0)` view.
- This callsite also behaves better with a float return view for
  `random_float_below`; the native instruction stream uses `fadd/fmul dword`
  constants for the returned value.
- Remaining shape gap is local-frame layout: native reserves `0x1c` bytes and
  uses larger stack offsets for the raw random/forward components, while the
  current candidate uses a `0x10` frame. Splitting raw forward-Z into a separate
  scalar looked plausible but regressed to 74.38%, because the compiler delayed
  the owner-velocity load again.
- 2026-06-21 follow-up release-vector audit: spelling
  `random_float_below(...) + 0.5f` inline and giving each forward-z load a
  distinct source local are both codegen-neutral at 88.80%; they do not move the
  frame to native's 0x1c layout. Direct scalar stores for the release vectors
  shrink the frame and regress to the low-50% range. Keep the staged `Vector3`
  source.

2026-07-09 frame campaign: dead pad floats are optimized away (still 0x10).
Persistent raw `slot_x/y/z` locals before the 0.3 scale regress to 72.73%. Keep
the staged `Vector3` form at 88.80%.
