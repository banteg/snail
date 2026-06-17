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
- This callsite needs the two-argument `random_float_below(1.0f, 0)` view.
- This callsite also behaves better with a float return view for
  `random_float_below`; the native instruction stream uses `fadd/fmul dword`
  constants for the returned value.
- Main remaining shape gap is temporary placement: native keeps each random
  component and scaled vector component in the stack frame before storing x/y/z,
  while the current source still optimizes most stores directly into the channel
  fields.
