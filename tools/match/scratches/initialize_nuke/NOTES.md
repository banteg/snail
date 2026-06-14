# initialize_nuke

- Near-exact/source-shaped match: 93.75%, 64/64 instructions.
- Uses typed `NukeController`, `Player`, `Game`, `SpriteManager`, and `Sprite`
  layouts. This pins the owner player pointer, `subgame_rate` read at
  `game+0x74650`, orbit axis/phase fields, and the 25 sprite slots at
  controller `+0x18`.
- Semantics: inactive state allocates 25 sprite id `0x83` entries for the
  owner's player slot, sets sprite flag `0x800`, clears orbit position/velocity
  lanes, seeds `3.0f` scale, sets phase step `0.104719758f`, and tail-calls
  `update_nuke()`. Already-active state skips allocation and still tail-calls
  `update_nuke()`.
- Residual: four instructions differ after each `allocate_sprite` call. Native
  uses `edx` for the sprite flag OR and reloads the just-stored slot into `ecx`
  before materializing the `3.0f` bit pattern in `eax`; VC6 emits the equivalent
  flag OR through `ecx` and loads the `3.0f` constant before the slot reload.
- Rejected no-op/source variants: a `register` flag temporary and a named
  first-store `current` sprite plus `sprite_scale` local did not improve the
  match. Keep the direct flag OR and vector-pointer zeroing unless stronger
  original-source evidence appears.
