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

- `+0x2964`: `cached_camera_target_world`

This is the world-space point consumed by `update_cameraman` when it seeds the desired follow camera and applies the later pitch and lift offsets.

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

## Readback Wins

The tracked IDA exports are materially clearer after the sync:

- `initialize_cameraman` now reads as explicit `live_matrix` / `desired_matrix` / `previous_desired_matrix` initialization rather than three anonymous `0x40` matrix blocks.
- `update_cameraman` now uses `player->cached_camera_target_world.{x,y,z}` for the core camera anchor math instead of `*((float *)player + 2649..2651)`.
- `look_at_point` now reads directly against `TransformMatrix.position`.
- the world-axis rotation helpers now mutate `basis_right`, `basis_up`, and `basis_forward` explicitly.

## Current Limits

- the byte at `cameraman + 0xcc` is still unresolved and intentionally unnamed beyond `unresolved_cc`
- most player-side attachment and presentation fields that `update_cameraman` touches are still only partially typed
- the checked-in header is now ready for both BN and IDA, but this pass only refreshed the tracked IDA lane because the live BN bridge timed out on the mutation/decompile calls
