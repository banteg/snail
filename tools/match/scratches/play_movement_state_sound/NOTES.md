Best current result: 89.13%.

The native stack has two `Vector3` locals: the camera-minus-player delta is
stored at `esp+0xc..0x14`, copied to `esp+0x18..0x20`, and the copy is passed to
`normalize_vector`. Modeling that as `normalized_vector = vector` matches the
full stack/vector-copy region and raises the scratch from 80.90%.

Remaining miss: after clamping the attachment-exit volume below zero, the target
stores `0.0f` and jumps to the shared `play_sound_effect_scaled` tail. VC6.5
continues to duplicate that call tail in source-equivalent forms tried so far:
structured `else if`, two independent `if`s, explicit `goto play_scaled`,
nested `else`, ternary clamp, do/break clamp, sentinel-initialized `sound_id`,
and a raw-double lower-bound spelling. Avoid using volatile, fake symbols, or
asm to force this tail merge.
