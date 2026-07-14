# initialize_bod_base @ 0x42f5f0

Exact match: 100.00%, 27/27 instructions.

Initializes the shared BOD base vtable, default flags, color lane, constructor
counter, and zeroed render/list fields. The first call targets the no-op `this`
constructor thunk at `0x44db50` (`mov eax, ecx; ret`) before the same storage is
written as a `tColour`.

`BodBase` now inherits the already-proven `BodNode`/`ContactTargetObject`
prefix, so the default flag store writes inherited `list_flags +0x04` rather
than a duplicate local field.

The exact store order now names the shared prefix also consumed by
`render_game_frame`: `position.z`, `position.y`, `position.x`, render-object
argument `+0x1c`, and render-object argument `+0x20`. The `+0x08/+0x0c`
intrusive links are not explicitly cleared here but are shared with the BOD list
views.

## 2026-07-14 shared BOD flag ownership

The default `0x02000020` store is now the named combination
`BOD_FLAG_VIEWPORT_1 | BOD_FLAG_RENDER_ENABLED`. The render traversal proves
the high byte is intersected with `render_camera_slots[1].flags`, while banner,
landscape, animation, and subgame lifecycles independently toggle the low
visibility bit. `RenderableBod` adds `BOD_FLAG_USE_TRANSFORM`, matching the
renderer branch that selects its embedded matrix instead of the position-only
base path. Both constructors remain exact.

2026-07-14 folded-constructor ownership: the opening identity call now targets
the embedded `tColour` directly. The previous `NoopAiCallback` cast represented
no object, field, or vtable boundary; it existed only to give the folded helper
a local constructor-shaped symbol. The shared color call preserves the exact
27/27 instruction stream and all five audited operands, so the synthetic
callback alias has been removed from the reference manifest.
