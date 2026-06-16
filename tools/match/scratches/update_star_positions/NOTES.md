# update_star_positions

`update_star_positions @ 0x434800` advances star entry phases, respawns expired
sprites from the camera-facing game slice, mirrors entry velocity into the
sprite, offsets the respawned sprite by ten frames of travel, and writes
twinkle alpha from `(phase - 2) * twinkle_scale * fade / 87.5`.

Layout evidence shared with `initialize_star_field`:

- `StarFieldEntry` size is `0x2c`, proved by `open_star_field`.
- `active +0x00` is initialized and cleared by lifecycle functions.
- `position +0x04` and `velocity +0x10` are seeded by
  `initialize_star_field`; update copies velocity to the sprite.
- `sprite +0x1c`, `speed +0x20`, `phase +0x24`, and
  `twinkle_scale +0x28` are all read by this updater.

The game camera/origin view at `g_game_base +0x6d4/+0x6e4` stays
scratch-local until more callers agree on names.

Current Wibo result: 32.85%, 101/106 candidate/target instructions, prefix
1/106, masked operands 11 ok.

Rejected/source-shape probes:

- Direct per-component sprite writes compiled to 26.46% by eliminating native
  stack staging entirely.
- A local `Vector3 staged_position` plus `scaled_y/scaled_z` recovered some
  stack traffic but only reached 31.84%; VC6 still kept the entry pointer live
  and introduced an `ebx` zero register.
- The current array-index spelling with `direction_scaled`, `staged_position`,
  and `velocity_scaled` is semantically closest to the native stack model, but
  VC6 allocates a `0x28` frame instead of native `0x24` and still does not keep
  the loop as native's `edx` byte-offset form.
