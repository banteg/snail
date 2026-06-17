# activate_landscape_entry @ 0x418870

Exact match: 123/123 instructions, clean masks.

Selects one cached landscape script and activates the ten repeated landscape
slices backed by `ActiveLandscapeEntry`.

Recovered layout evidence:

- the selected landscape script stride is `0x124`.
- script record data is reached through a `+0x5a4` window from the entries
  base.
- `record +0x10c` is the landscape object index, or `-1` for no object.
- `record +0x110..+0x11c` is the 16-byte `fog_color` block copied to
  `Game+0x14` after backdrop activation. `load_landscape_script_by_name` writes
  RGB from `Fog:` and the missing-Fog fallback writes the full `Color4f`.
- active slots are inserted after the landscape active-list head at
  `Game+0x3ca25c`.
- `data_4df9bc` is a landscape backdrop variant selector fed from
  `Game::level_mode_arg`; activator consumes its low bit outside tutorial and
  random challenge modes.
- `record +0x120` is the script `Distort:` scalar consumed by
  `change_backdrop`.
- object slots at `Game+0x48e2c` have a `0xbc` stride and provide the
  `LandscapeObjectBounds*` used for each repeated slice.
- each live slice records `repeat_z_span = max_z - min_z`, resets its inherited
  transform to identity, places its local z at `(index - 0.5) * repeat_z_span`,
  and uses the shared reference BOD at `Game+0x42fd7c` for later wrapping.

Source-shape note: the state store uses a single volatile typed store so VC6
keeps the native `state = 1` write before reloading `list_flags` for the
visibility bit. A plain member store lets the compiler hoist the flag load
ahead of the state write; no extra fake symbol or dummy call is involved.
