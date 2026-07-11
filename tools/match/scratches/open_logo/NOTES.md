# open_logo @ 0x419110

Initializes the 32 intro logo renderable slots and preloads every texture
matching `Intro/*.tga`.

Recovered layout:

- `this + 0x24018`: first `IntroLogoRenderable`;
- logo renderable stride: `0x90`;
- each slot is a `RenderableBod` followed by 0x18 bytes of intro-logo runtime
  state, matching the existing intro logo update scratch;
- the local archive enumeration buffer stores names in 0x80-byte entries.

The function uses the shared object and texture lists: each renderable receives
an object from `g_object_list`, loads `Objects/Font3D`, marks object flag `0x4`,
then sets texture flag `0x400` on every loaded `Intro/%s` texture.

The retained source uses the renderable/BOD slot cursor at `this + 0x24018`
and reads the object field at `slot + 0x24`. That removes VC6's earlier
strength-reduced second cursor, so the first loop now keeps the same two saved
registers as native. The remaining difference is representational: native
keeps the object-field cursor at `this + 0x2403c` and forms the BOD receiver as
`cursor - 0x24`, while this source keeps the BOD receiver directly and reads the
object through `+0x24`.

2026-06-20 type cleanup: the first pass used a method-only `LogoRuntime` view.
Binary Ninja showed the caller receiver at `game + 0x4f400`, while this helper
proved the second slot-bank cursor at receiver `+0x24018`.

2026-06-21 cursor-owner retry: focused Wibo improves from 69.35% to 90.00%,
with 60/60 candidate/target instructions, 4/60 prefix, and 13 clean masked
operands. The accepted BOD-slot cursor removes the non-native `ebx` save and
restores native stack offsets. Retested object-field cursor forms, including a
typed `Object**` cursor and a named allocated-object temporary before
`set_bod_object`, both fell back to the old 69.35% three-register shape. Keep
the BOD-slot source until an object-field spelling preserves the two-register
loop.

2026-06-21 raw object-cursor retry: spelling the loop around a `char*`
`this+0x2403c` object-field cursor does recover the native `lea esi,
[ecx+0x2403c]` and `lea ecx, [esi-0x24]` arithmetic, but VC6 keeps a second
persistent receiver cursor in `edi`, saves `ebx`, shifts the stack frame, and
regresses back to 69.35%. The retained BOD-slot cursor is still the better
two-register source shape.

2026-07-09 object-cursor transfer from the promote campaign: retested
`void**` / `char*` / dual BOD+object-slot / named allocated-object temps.
Every object-field primary cursor still falls to 69.35% with the three-register
frame. Keep the BOD-slot source at 90.00%.

## 2026-07-11 intro owner closure

The constructor, exact intro update/teardown helpers, and corrected initializer
now close the reusable owner that the earlier method-only view could not:
`IntroScreenRuntime` begins at root `+0x4f400`, owns 1024 crawl renderables at
`+0x18`, then the 32 logo renderables used here at `+0x24018`, and ends exactly
at root `+0x74618`. `open_logo` is therefore a method on that shared owner and
the standalone `logo_runtime.h` view is retired. Focused Wibo remains 90.00%,
`60/60`, with all 13 masked operands clean; only the object-field cursor versus
BOD-base cursor register shape remains.
