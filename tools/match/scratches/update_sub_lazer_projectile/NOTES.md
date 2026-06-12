# WIP - 72.44% score, 127/127 insns on standard flags

Semantics recovered from IDA/BN plus the matched pickup-list precedent:

- live object uses the shared bod/list layout, not the pool-slot offsets used
  by `spawn_sub_lazer_projectile`
- `+0x14` is the sprite bob base y, `+0x18` is the live world z used for the
  interaction-window cleanup, `+0x44` is the hidden/source object checked at
  byte `+9`, and `+0x64` is the sprite killed on cleanup
- states `1` and `2` both remove the object from the intrusive list and return
  it to the free list at `game_base + 0x5a8`
- the live bob update is `phase += step`, wrap only when `phase > 1.0`, then
  `sprite.local_y = sine(phase * tau) * 0.3 + base_y`

Current residuals:

- the state-1 non-cleanup branch in the scratch places the bob-update block
  inline; native branches to the shared tail bob block after both cleanup
  copies
- the two list-removal copies are semantically aligned, but label placement
  around their shared tail differs

Keep this as a source-shape problem. Do not collapse the duplicate cleanup
blocks into a helper; that regressed the target layout.
