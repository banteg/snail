# refresh_object_vertex_buffer

Relationship-first scratch for the private object vertex-buffer refresher at
`0x412250`.

Current Wibo result: 59.85%, 135/139 instructions, prefix 7/139, masked
operands 4 ok, 0 unresolved, 0 mismatch.

Recovered relationships:

- Called only by `render_object`.
- `Object +0x10` is the render/object flags word.
- `flags & 0x200000` selects the animated/distorted vertex source path.
- `Object +0xbc` points at an animation/frame source with an integer lane at
  `+0x04`, a frame pointer table at `+0x08`, and a float scale at `+0x0c`.
- Animated refresh writes `Object +0x38` from frame `+0x00` vertices and
  `Object +0x60` from frame `+0x04` normals.
- `flags & 0x800000` dispatches `apply_distort_to_object` on the embedded
  distort state at `Object +0x80`.
- `Object +0xc0` owns grouped-render buffers; its `+0x08` member is the D3D
  vertex buffer locked with `Object +0xc4 * 0x18` bytes.
- Both refresh paths rewrite vertex positions in the locked 0x18-byte render
  vertex stream.
- The non-animated `flags & 4` path also copies UVs from `Object +0x5c`
  facequad data, using `quad = i / 4` and `corner = i & 3`.

Corrected assumptions:

- `Object +0x80` is only treated as a subobject call base for
  `apply_distort_to_object`; modeling it as a sized scratch-local field shifted
  the later `+0xbc/+0xc0/+0xc4` renderer fields and was wrong.

Expected residuals:

- Native uses offset-driven copy loops with specific register owners
  (`eax/ecx/edx` for count/source/destination in the animated path, and
  `ecx/edi/ebx` in the UV path). The scratch now uses the same byte-offset
  semantics, but VC6 still chooses different loop registers and label distances.

This is intentionally not a promoted `Object` layout yet. The local view is
only the renderer-side field set proven by this helper and its `render_object`
caller.
