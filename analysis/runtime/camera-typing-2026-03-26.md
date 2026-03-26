# Camera Typing Pass (2026-03-26)

This pass promoted a minimal camera/controller slice into the checked-in type header so the decompile can use stable object names instead of raw matrix and float-array indexing.

## Safe Typed Slice

The current conservative `CameramanState` prefix is:

- `+0x00`: `live_matrix`
- `+0x40`: `desired_matrix`
- `+0x80`: `previous_desired_matrix`
- `+0xc0`: `player`
- `+0xc4`: `game`
- `+0xc8`: `fov_degrees`
- `+0xcc`: unresolved byte flag
- `+0xd0`: `attachment_lift_envelope`
- `+0xd4`: `smoothed_attachment_lift_envelope`

The current conservative `Player` camera slice is:

- `+0x38`: `live_matrix`
  - `+0x68`: `live_matrix.position`
- `+0x350`: `lane_lean_state`
- `+0x354`: `lane_lean_amplitude`
- `+0x358`: `lane_lean_progress`
- `+0x35c`: `lane_lean_progress_step`
- `+0x370`: `heading_roll`
- `+0x384`: `follow_state`
- `+0x41d`: `attachment_exit_pending`
- `+0x42c`: `post_follow_value_a`
- `+0x2964`: `cached_camera_target_world`

The current conservative `PlayerPresentationController` camera-adjacent slice is:

- `+0x15bc`: `wobble`
  - `roll_phase`
  - `roll_phase_step`
  - `lift_phase`
  - `lift_phase_step`
- `+0x1894`: `invincible_shell`
  - `state`
  - `spin_phase`
  - `spin_phase_step`
  - `fade_progress`
  - `fade_step`

These are the player-side camera inputs that `update_cameraman` now reads directly in the typed decompile:

- `live_matrix.position.z`
- `lane_lean_amplitude`
- `lane_lean_progress`
- `heading_roll`
- `follow_state.active`
- `follow_state.template_record`
- `follow_state.source_cell`
- `follow_state.orientation_a`
- `follow_state.orientation_b`
- `attachment_exit_pending`
- `post_follow_value_a`
- `cached_camera_target_world`

And these presentation-side controller slices now read back with stable names in `initialize_cutscene`, `initialize_invincible_shell`, and `update_invincible_shell` instead of anonymous `+0x15bc` / `+0x1894` float blocks.

## Helper Typing

The shared matrix helper family is now typed around `TransformMatrix`:

- `initialize_matrix_from_values`
- `rotate_matrix_world_x`
- `rotate_matrix_world_y`
- `rotate_matrix_world_z`
- `look_at_point`
- `invert_matrix_from_source`
- `multiply_matrix_in_place`
- `premultiply_matrix_in_place`
- `interpolate_matrix_rotation`
- `linear_interpolate_matrix`

The camera/cutscene helper returns are also now constrained to the safe in-place model:

- `set_matrix_identity` is `void`
- `set_matrix_rotation_identity` is `void`
- `rotate_matrix_world_x` is `void`
- `rotate_matrix_world_y` is `void`
- `rotate_matrix_world_z` is `void`
- `set_matrix_z_direction` is `void`
- `look_at_point` is `void`
- `linear_interpolate_matrix` is `void`

Those helpers mutate the output matrix directly; treating them as value-returning helpers polluted both BN and IDA callers with fake temporary results.

## Readback Wins

The tracked IDA exports are materially clearer after the sync:

- `initialize_cameraman` now reads as explicit `live_matrix` / `desired_matrix` / `previous_desired_matrix` initialization rather than three anonymous `0x40` matrix blocks.
- `update_cameraman` now uses `player->cached_camera_target_world.{x,y,z}` for the core camera anchor math instead of `*((float *)player + 2649..2651)`.
- `update_cameraman` now shows the follow-attachment gates as `player->follow_state.active`, `player->follow_state.template_record`, `player->follow_state.source_cell`, and the two typed follow orientation floats instead of raw `player + 0x384..0x3a0` byte arithmetic.
- `update_cameraman` now shows the post-follow carryover branch as `player->attachment_exit_pending` plus `player->post_follow_value_a` instead of `player + 0x41d` / `player + 0x42c`.
- `update_cameraman` now reads the tile-family lean pulse and live heading lane as `player->lane_lean_amplitude`, `player->lane_lean_progress`, and `player->heading_roll` instead of `player + 0x354/+0x358/+0x370`.
- `update_subgoldy` and `update_track_attachment_follow_state` now expose the same player-side `lane_lean_*` / `heading_roll` lanes that the Zig port already mirrors.
- the live BN lane now also reads `game->first_block_row_count` and `game->track_center_x` directly in `update_cameraman` and nearby ring or hazard helpers instead of raw `game->__offset(0x50)` / `game->__offset(0x38)`.
- `look_at_point` now reads directly against `TransformMatrix.position`.
- the world-axis rotation helpers now mutate `basis_right`, `basis_up`, and `basis_forward` explicitly.

## Current Limits

- the byte at `cameraman + 0xcc` is still unresolved and intentionally unnamed beyond `unresolved_cc`
- most player-side attachment and presentation fields that `update_cameraman` touches are still only partially typed
- the checked-in header now drives both the IDA sync lane and the live BN camera-mutator pass, but large whole-header imports still time out on the BN bridge; the stable workflow is to use `uv run python tools/binja/sync_path_template_types.py` for the narrow presentation slice, including the verified matrix/presentation helper prototypes plus the small dependent `SnailVisual` / `PathTemplate` field overlays, and to apply other camera-facing mutations in smaller verified steps
- the remaining BN caller residue in `update_cameraman` is now localized to presentation noise around `rotate_matrix_world_z` rather than the broader helper signature set; `linear_interpolate_matrix`, `initialize_cutscene`, and `dispatch_cutscene_animation` are safe to replay through the narrow BN sync lane
