# activate_landscape_entry @ 0x418870

Near-exact source: 123/123 instructions with all masks clean; the sole residual
is the ordinary state-store/load schedule documented below.

Selects one cached landscape script and activates the ten repeated landscape
slices owned by the same `LandscapeManager` receiver.

Recovered layout evidence:

- the selected landscape script stride is `0x124`.
- script record data begins at manager `+0x5a4`; the ten active entries occupy
  the exact preceding `10 * 0x90 = 0x5a0` bytes and the count is at `+0x5a0`.
- `record +0x10c` is the landscape object index, or `-1` for no object.
- `record +0x110..+0x11c` is the 16-byte `fog_color` block copied to
  `Game+0x14` after backdrop activation. `load_landscape_script_by_name` writes
  RGB from `Fog:` and the missing-Fog fallback writes the full `tColour`.
- active slots are inserted after
  `SubgameRuntime::landscape_slice_list_head +0x355c44`
  (`GameRoot +0x3ca25c`).
- `data_4df9bc` is a landscape backdrop variant selector fed from
  `Game::level_mode_arg`; activator consumes its low bit outside tutorial and
  random challenge modes.
- `record +0x120` is the script `Distort:` scalar consumed by
  `change_backdrop`.
- object slots at `Game+0x48e2c` are
  `DirectXLoader::cached_x_mesh_slots[0].object`; their `0xbc` stride provides
  the retained `Object*` used for each repeated slice.
- each live slice records `repeat_z_span = max_z - min_z`, resets its inherited
  transform to identity, places its local z at `(index - 0.5) * repeat_z_span`,
  and uses the shared reference BOD at `Game+0x42fd7c` for later wrapping.

Source-shape note: the state store uses a single volatile typed store so VC6
keeps the native `state = 1` write before reloading `list_flags` for the
visibility bit. A plain member store lets the compiler hoist the flag load
ahead of the state write; no extra fake symbol or dummy call is involved.

2026-07-11 ownership closure: moving this method from the false first-entry
receiver to `LandscapeManager` remains exact at 123/123. Direct
`scripts[script_index]` expressions let VC6 retain the native manager-relative
`+0x5a4` field displacements without an overlapping window type.

2026-07-13 no-fakematch audit: the volatile state write was only pinning the
store ahead of a list-flag reload. It is now the ordinary typed
`ActiveLandscapeEntry::state` assignment. Ownership and instruction parity are
unchanged; focused matching is honestly 99.19%, 123/123, prefix 65, with all
20 operands clean and only the independent load/store schedule swapped.

## 2026-07-14 canonical landscape owner graph

The method now follows the root-owned level mode, landscape slice list,
DirectX cached-mesh bank, embedded player reference BOD, backdrop, border
manager, and fog color directly. The cached slot's `Object*` already exposes
`bounds_min.z/+0xac` and `bounds_max.z/+0xb8`, so the two synthetic
`LandscapeObjectSlotRef` and `LandscapeObjectBounds` views are retired.

Focused output remains at the honest 99.19%, 123/123 frontier with all 20
operands clean. The sole residual is still the ordinary `state`/flag-load
scheduling swap documented above.

## 2026-07-14 fixed landscape bank extents

The exact manager layout proves ten `0x90` active entries through `+0x5a0`,
followed by `script_count` and 128 `0x124` parsed script records through the
`0x97a4` manager end. The active-entry sweep now shares
`LANDSCAPE_ACTIVE_ENTRY_COUNT` with the owned array, while the parsed bank is
bounded by `LANDSCAPE_SCRIPT_CAPACITY`; no synthetic load-time capacity check
was added where the native has none.

All five owner/consumer listings remain byte-identical:

- reset: `f447a0d71bb0043dea4d8ad6c6f702fff401d5d70ccce08c1959c02af273243f`
- script loader: `189bde097668c3e56a2767b90c9b333a518f6641f19ec9451abc50d7f4a1f950`
- activator: `613ba51711ebb72a5edce6f185f9bb72c835a3fd95c02686784fa704efd04be2`
- active-entry clear: `a663ed2ee953e6f01b4857d201b800bc443ea2d205c28751ee62c5fecbe956f0`
- runtime constructor: `755c2d4b3862bccde9a1fae74b792b0500699dda1c378c9f673ef0c27b829bba`
