# open_logo @ 0x419110

Initializes the 32 intro logo renderable slots and preloads every texture
matching `Intro/*.tga`.

Recovered layout:

- `this + 0x24018`: first image-donor `LogoLetter`;
- logo renderable stride: `0x90`;
- each slot is a 0x80-byte `RenderableBod` followed by 0x10 bytes of intro-logo
  runtime state, matching the existing intro logo update scratch;
- the local archive enumeration buffer stores names in 0x80-byte entries.

The function uses the shared object and texture lists: each renderable receives
an object from `g_object_list`, loads `Objects/Font3D`, marks
`OBJECT_FLAG_DYNAMIC_VERTICES`, then sets texture flag `0x400` on every loaded
`Intro/%s` texture.

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

## 2026-07-11 owner closure

The constructor, exact intro update/teardown helpers, and corrected initializer
now close the reusable owner that the earlier method-only view could not:
The owner begins at root `+0x4f400`, owns 1024 crawl renderables at
`+0x18`, then the 32 logo renderables used here at `+0x24018`, and ends exactly
at root `+0x74618`. `open_logo` is therefore a method on that shared owner and
the standalone `logo_runtime.h` view is retired. Focused Wibo remains 90.00%,
`60/60`, with all 13 masked operands clean; only the object-field cursor versus
BOD-base cursor register shape remains.

## 2026-07-12 typed donor-bank cleanup

The retained cursor is now a `LogoLetter*`, advances with `++slot`,
and reads `slot->object` directly. The old `BodBase*` plus raw `+0x24` and
`+0x90` arithmetic is no longer needed once the full donor-bank owner is
available. Texture registration likewise uses `TEXTURE_REF_REGISTERED`.
These ownership cleanups are codegen-neutral at 90.00%, 60/60, prefix 4/60,
with all 13 masked operands clean. Native still biases its cursor to the
`object` member lane; the typed source keeps the record base and leaves that
honest four-instruction representation residual visible.

## 2026-07-12 cRLogo ownership

Symbol-preserving iOS builds name this lifecycle edge `cRLogo::Open()`. The
mobile port initializes 100 cRLogoRows, while Windows initializes 32 fixed
0x90-byte image donors, so only the owner and role are shared across ports; the
Windows bank size and layout remain target-local facts. Focused Wibo remains
90.00%, 60/60, with all 13 operands clean.

## 2026-07-12 indexed donor-bank closure

The native object-member cursor is not evidence for a raw `Object**` owner.
Spelling the fixed bank as ordinary indexed `image_donors[logo_index]` access
lets VC6 perform the native strength reduction itself: it seeds `esi` at the
first donor's `object` member (`this + 0x2403c`), forms each `LogoLetter`
receiver as `esi - 0x24`, advances the member cursor by the exact `0x90` record
stride, and retains the two-register frame. This supersedes the explicit
record-base cursor while preserving the typed `Logo`/`LogoLetter` ownership.

Focused Wibo is now **100.00%**, `60/60`, prefix `60/60`, with all 13 masked
operands clean. Together with the exact constructor, updater, teardown, and
letter updater, `cRLogo::Open` now closes the complete shared Logo lifecycle.
