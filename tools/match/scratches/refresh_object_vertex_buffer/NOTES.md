# refresh_object_vertex_buffer

Relationship-first scratch for the private object vertex-buffer refresher at
`0x412250`.

Current Wibo result: 90.58%, 137/139 instructions, prefix 7/139, masked
operands 4 ok, 0 unresolved, 0 mismatch.

Recovered relationships:

- Called only by `render_object`.
- `Object +0x10` is the render/object flags word.
- `OBJECT_FLAG_HAS_ANIMATION` selects the generated animation-frame vertex
  source path.
- `Object +0xbc` points at the 0x14-byte `ObjectAnimation` produced by
  `request_object_animation`: generated frame count at `+0x04`, frame pointer
  table at `+0x08`, playback progress at `+0x0c`, and progress step at `+0x10`.
- Animated refresh writes `Object +0x38` from frame `+0x00` vertices and
  `Object +0x60` from frame `+0x04` facequad normals.
- `OBJECT_FLAG_DISTORT_ENABLED` dispatches `apply_distort_to_object` on the
  embedded distort state at `Object +0x80`.
- `Object +0xc0` owns grouped-render buffers; its `+0x08` member is the D3D
  vertex buffer locked with `Object +0xc4 * 0x18` bytes.
- Both refresh paths rewrite vertex positions in the locked 0x18-byte render
  vertex stream.
- The non-animated `OBJECT_FLAG_DYNAMIC_VERTICES` path also copies UVs from `Object +0x5c`
  facequad data, using `quad = i / 4` and `corner = i & 3`.

Corrected assumptions:

- `Object +0x80` is a real five-float, 0x14-byte `ObjectDistort` subobject.
  Three controls are understood and two trailing floats remain unknown. The
  shared complete `Object` layout owns that member directly; the older
  explicit cast was a temporary renderer-local view.
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

## 2026-07-14 distort and render-stream ownership

The dynamic path now calls the embedded `object->distort` owner directly, and
both lock sizes derive from the shared 24-byte `ObjectRenderVertex` type.
These replace the last `Object +0x80` cast and duplicated `0x18` stream stride
without changing code generation: focused output remains 90.58%, 137/139
instructions, prefix 7, with all four operands clean. The two missing
instructions remain the documented address-formation scheduling differences.

## 2026-07-15 retained-buffer replay

Binary Ninja now sees `apply_distort_to_object(&object->distort, object)` and
the full Object-owned animation/copy/render-buffer chain. A local retained
`source_vertices` pointer regressed focused matching to 82.48%; per-iteration
typed source/destination pointer locals were codegen-neutral at 90.58%. The
direct aggregate copy remains the clearest source-plausible form, with the two
documented address-formation instructions left honest.

## 2026-07-18 locked render-stream ownership

The IDA decompiler had merged each D3D lock output with the reused incoming
`Object*` stack slot. The repeatable object replay now splits the two native
definitions into scoped `ObjectRenderVertex*` locals at `0x4122d0` and
`0x412350`. The tracked artifact consequently renders typed position and UV
writes instead of false `Object::_pad_00` accesses, while preserving the real
Object receiver in both branches. The replay is read-back verified and
idempotent, and a health check rejects the old argument alias.

No matcher source changed. Focused Wibo remains `90.58%`, `137/139`, prefix
`7`, with four clean masks; the two residual instructions remain ordinary
source/destination address-formation scheduling differences.

## 2026-07-19 Binary Ninja locked-stream lifetimes

- Direct3D `Lock` writes the mapped `ObjectRenderVertex*` into the incoming
  `Object*` argument's caller-owned stack slot. Binary Ninja does not expose
  that external memory write as an MLIL variable definition, so the parameter
  itself cannot be split honestly in this database.
- Six exact post-lock register lifetimes now preserve the two borrowed stream
  bases plus the current `Vec3*` source and `ObjectRenderVertex*` destination
  elements. Both upload loops consequently render explicit `x/y/z` ownership
  instead of `Object::_pad_00` and untyped `int32_t*` copies.
- Two attempted UV-only base reload annotations had no decompile or ownership
  effect and were removed. The UV stores remain raw stack-slot expressions;
  claiming a split output variable there would exceed the analysis evidence.
- The bounded replay verifies the canonical 0x0c-byte `Vec3`, 0x18-byte render
  vertex, render-buffer chain, and 0xdc-byte `Object` before applying any
  annotations. A second run reports all six lifetimes already current in
  0.74 seconds.

No matcher source changed. Focused Wibo remains `90.58%`, `137/139`, prefix
`7`, with four clean masks and the same two honest scheduling residuals.
