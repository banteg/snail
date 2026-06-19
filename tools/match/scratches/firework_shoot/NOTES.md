# firework_shoot @ 0x441dd0

Spawns a burst of small firework sprites at a supplied world position. The only
known callsite is `handle_subgoldy_collisions`, which passes a burst position,
player slot, texture id, and particle count.

Recovered behavior:

- gates on `byte_4df934 & 0x10`;
- allocates `count` sprites through `g_sprite_manager`;
- uses owner and texture id from the caller, with both alternate textures set
  to `-1`;
- arms draw mode 10, render flags `0x802`, progress/lifetime fields, and a
  large corner scale;
- randomizes duration, red/yellow tint, and velocity;
- copies the supplied position into each spawned sprite.

This also identifies `0x44dbd0` as `Color4f::set_color_rgb(float,float,float)`,
a three-channel setter used here after randomizing the red component.

Source-shape notes:

- keeping a real `Vector3 velocity` local recovers the native 0x10-byte stack
  frame (`velocity` plus remaining particle count);
- scalar `random_x/y/z` locals compiled smaller and lost the native prologue;
- the remaining body mismatch is mostly stack-slot reuse: the target reuses the
  now-dead owner/texture/count argument slots as float temporaries after the
  `allocate_sprite` call, while the clean source keeps the staged velocity in
  its local `Vector3`.
