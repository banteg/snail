# pack_color_rgba_u8 @ 0x44dbf0

Exact thiscall match. Converts a `Color4f` record to the packed BGRA byte
record used by sprite and mesh draw paths: float `r/g/b/a` are multiplied by
`255.0f`, converted through the native `__ftol` path, and stored as
`ColorBGRA8::{r,g,b,a}` at byte offsets `+2/+1/+0/+3`.

This promotes the packed color view from the old `draw_sprite_quad` local shell
into `sprite.h`; `draw_sprite_quad` remains a 100% match with the shared type.
