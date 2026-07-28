# initialize_renderable_bod @ 0x42f650

Exact VC6 match: 100.00% (10/10 instructions, full prefix, three clean masked
operands).

## 2026-07-17 positioned-body constructor ownership

iOS `RObject.o` names the same owner `cRBodPos::cRBodPos()`, immediately above
the independently recovered `cRBod::cRBod()` base constructor. The Windows
body preserves ECX in ESI, invokes `initialize_bod_base`, installs the positioned
body vtable and render flags, initializes the matrix at `+0x38`, moves ESI back
to EAX, and returns through a plain `ret`.

That proves the complete native contract:

```cpp
RenderableBod* __thiscall initialize_renderable_bod(RenderableBod* body);
```

The canonical replay now preserves that ABI in both analysis backends. Binary
Ninja consequently renders the inherited `BodNode` members and owned
`TransformMatrix` directly instead of a `void***` result and word-indexed
stores. No matching source or operand mask changed.

## 2026-07-28 cRBodPos tail-lane ownership

Android and iOS `cRDirectX::LoadAnim` independently allocate their transient
animation keyframe banks as raw `cRBodPos` records with a `0x74` stride, retain
the inherited `Object*` at `+0x24`, and store the parsed frame number in the
final word at `+0x70`. Their exact
`cRObject::RequestAnim(int, cRBodPos*, float, int)` symbols consume that same
lane.

The Windows owner has the already-proven `0x80` extent: its larger
`BodBase + TransformMatrix + AnimManager*` prefix places the homologous final
word at `+0x7c`. That lane is now `RenderableBod::frame_number`, and the former
synthetic `XAnimationKeyframe : BodBase` record is only a role alias for the
authored `cRBodPos`. The constructor still leaves both trailing words alone,
exactly as both mobile constructors do. Focused Windows matching remains exact
at 10/10 instructions with all three operands clean.
