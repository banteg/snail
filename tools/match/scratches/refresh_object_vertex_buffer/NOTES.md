# refresh_object_vertex_buffer

Relationship-first scratch for the private object vertex-buffer refresher at
`0x412250`.

Current Wibo result: 90.58%, 137/139 instructions, prefix 7/139, masked
operands 4 ok, 0 unresolved, 0 mismatch.

Recovered relationships:

- Called only by `render_object`.
- `Object +0x10` is the render/object flags word.
- `flags & 0x200000` selects the animated/distorted vertex source path.
- `Object +0xbc` points at the 0x14-byte `ObjectAnimation` produced by
  `request_object_animation`: generated frame count at `+0x04`, frame pointer
  table at `+0x08`, playback progress at `+0x0c`, and progress step at `+0x10`.
- Animated refresh writes `Object +0x38` from frame `+0x00` vertices and
  `Object +0x60` from frame `+0x04` facequad normals.
- `flags & 0x800000` dispatches `apply_distort_to_object` on the embedded
  distort state at `Object +0x80`.
- `Object +0xc0` owns grouped-render buffers; its `+0x08` member is the D3D
  vertex buffer locked with `Object +0xc4 * 0x18` bytes.
- Both refresh paths rewrite vertex positions in the locked 0x18-byte render
  vertex stream.
- The non-animated `flags & 4` path also copies UVs from `Object +0x5c`
  facequad data, using `quad = i / 4` and `corner = i & 3`.

Corrected assumptions:

- `Object +0x80` is a real three-float `ObjectDistort` subobject, but this
  narrow renderer-local view should keep the explicit cast-call shape. Modeling
  it as a local member perturbs unrelated vertex-copy loop codegen without
  improving this scratch.
- `ObjectAnimation +0x04/+0x0c` are not a raw frame-index/scale pair. The
  animation builder proves they are generated frame count and playback
  progress; their product selects the generated frame.

Expected residuals:

- Native and candidate now have the same two indexed copy loops and the same
  aggregate position/UV payload. VC6 schedules the source/destination address
  formation differently and emits two fewer candidate instructions, which also
  shifts the surrounding branch labels.

The refresh parameter now aliases the shared `Object` layout; its old local
field set is covered by shared `flags`, `vertices`, `facequad_normals`,
`animation`, render buffers, and grouped vertex count. `Object +0xbc` is the
shared `ObjectAnimation*` owner pointer, and generated frame facequad normals
are typed as `Vector3*` buffers containing two normals per facequad. Focused
Wibo remains `59.85%`, `135/139`, with `4 ok` masked operands.

2026-07-10 borrower closure: the scratch now accepts `Object*` directly rather
than a renderer-local typedef. The shared lifecycle records that `vertices`
and `facequad_normals` are active views which may point into the retained
animation graph, while this helper only borrows those views and the built
vertex-buffer wrapper. Hoisting the active `vertices` view once in the animated
copy path recovers the native 41-instruction prefix without extending that
alias into the unrelated static UV path. Focused Wibo is 60.81%, 134/139, with
four clean masked operands.

The animated upload copies each borrowed generated position as a typed
`Vector3` value into the position prefix of `ObjectRenderVertex`.

2026-07-13 authored loop-shape recovery: both uploads are ordinary indexed
loops over the object-owned `grouped_vertex_count`. The animated path copies
the active generated `Vector3` view into each locked render vertex; the static
path performs the same aggregate position copy and then preserves the authored
facequad-corner UV lanes. This removes the manual byte offsets and scalar
type-punning from the scratch. The natural typed spelling raises focused Wibo
from 60.81% (`134/139`, prefix 41) to 90.58% (`137/139`, prefix 7), with all
four references still clean. The two residual instructions are scheduling
differences in source/destination address formation; no compiler-control
scaffolding was added.
