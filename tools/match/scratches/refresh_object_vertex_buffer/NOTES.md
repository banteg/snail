# refresh_object_vertex_buffer

Relationship-first scratch for the private object vertex-buffer refresher at
`0x412250`.

Current Wibo result: 59.85%, 135/139 instructions, prefix 7/139, masked
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

- Native uses offset-driven copy loops with specific register owners
  (`eax/ecx/edx` for count/source/destination in the animated path, and
  `ecx/edi/ebx` in the UV path). The scratch now uses the same byte-offset
  semantics, but VC6 still chooses different loop registers and label distances.

The refresh parameter now aliases the shared `Object` layout; its old local
field set is covered by shared `flags`, `vertices`, `facequad_normals`,
`animation`, render buffers, and grouped vertex count. `Object +0xbc` is the
shared `ObjectAnimation*` owner pointer, and generated frame facequad normals
are typed as `Vector3*` buffers containing two normals per facequad. Focused
Wibo remains `59.85%`, `135/139`, with `4 ok` masked operands.
