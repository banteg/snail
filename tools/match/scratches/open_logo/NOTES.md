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

2026-06-20 type cleanup: `LogoRuntime` moved to a method-only shared header.
Binary Ninja shows the caller uses the receiver at `game + 0x4f400`, but this
function only proves the logo slot cursor, not a reusable full object layout.
`open_logo` stayed at 69.35%, and the broad `initialize_game_assets_and_world`
caller stayed at its previous semantic-partial score after including the header.

2026-06-21 cursor-owner retry: focused Wibo improves from 69.35% to 90.00%,
with 60/60 candidate/target instructions, 4/60 prefix, and 13 clean masked
operands. The accepted BOD-slot cursor removes the non-native `ebx` save and
restores native stack offsets. Retested object-field cursor forms, including a
typed `Object**` cursor and a named allocated-object temporary before
`set_bod_object`, both fell back to the old 69.35% three-register shape. Keep
the BOD-slot source until an object-field spelling preserves the two-register
loop.
