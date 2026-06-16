# initialize_bod_base @ 0x42f5f0

Exact match: 100.00%, 27/27 instructions.

Initializes the shared BOD base vtable, default flags, color lane, constructor
counter, and zeroed render/list fields. The first call targets the no-op `this`
constructor thunk at `0x44db50` (`mov eax, ecx; ret`) before the same storage is
written as a `Color4f`.

The exact store order now names the shared prefix also consumed by
`render_game_frame`: `position.z`, `position.y`, `position.x`, render-object
argument `+0x1c`, and render-object argument `+0x20`. The `+0x08/+0x0c`
intrusive links are not explicitly cleared here but are shared with the BOD list
views.
