# pack_color_rgba_u8 @ 0x44dbf0

Exact thiscall match. Converts a `tColour` record to the packed BGRA byte
record used by sprite and mesh draw paths: float `r/g/b/a` are multiplied by
`255.0f`, converted through the native `__ftol` path, and stored as
`tColourSmall::{r,g,b,a}` at byte offsets `+2/+1/+0/+3`.

Android's symbol-preserving build names the owner `tColourSmall` and exposes
this exact operation as `tColourSmall::operator=(tColour const&)`: its four
stores use the same `+2/+1/+0/+3` layout. `G0SetColour` reads those bytes back
as red, green, blue, and alpha, independently closing the four-byte class
layout. The stable Windows harness name remains `pack_color_rgba_u8`.

The shared class replaces the temporary descriptive `ColorBGRA8` shell.
`draw_sprite_quad`, `set_object_color`, and the track cache builder retain their
measured code generation with the authored owner.

The checked-in headers and IDA database carry the recovered prototype. Binary
Ninja accepts the `tColourSmall*` prototype in preview, but the live database
restores its pinned `ColorBGRA8*` user type during application. The repeatable
BN sync therefore leaves this one function prototype deferred instead of
forcing a failed mutation; its body, exact matcher source, Android provenance,
and IDA readback still agree on the authored owner.
