# build_object_texture_group_buffers

Structure-first scratch for the object texture-group buffer builder at
`0x413d50`.

Current Wibo result: 100.00%, 373/373 candidate/target instructions,
prefix 373/373, masked operands 29 ok, 0 unresolved, 0 mismatch.

Recovered relationships:

- Called only by `build_all_objects`.
- If `Object +0x2c` vertex count is zero, native clears `+0xcc/+0xd0/+0xd4`,
  `+0xc0`, and `+0xc8`, then returns.
- Non-empty objects set `flags |= 0x80000`, which is the same tint-rewrite gate
  consumed by exact `set_object_color`.
- Allocates three per-texture-group arrays:
  - `Object +0xcc`: index-buffer start offset per texture group.
  - `Object +0xd0`: texture reference per texture group.
  - `Object +0xd4`: primitive count per texture group.
- `Object +0x6c` entries are cumulative facequad end indices, confirmed by
  `calc_object_texture_groups`; they are not per-group counts.
- `g_object_grouped_vertex_scratch` (`data_5031c4`) points at 0x1c-byte
  temporary vertices filled by `get_or_append_object_texture_group_vertex`.
- `g_object_grouped_vertex_cursor` (`data_5031bc`) is reset here, incremented
  by the append helper, then copied into `Object +0xc4`.
- `Object +0xc0` receives the D3D vertex-buffer wrapper and `Object +0xc8`
  receives the D3D index-buffer wrapper.
- Facequad flag `0x80` selects the three-index form; otherwise native emits six
  indices by reusing indices 0 and 2 plus the fourth corner.
- Toon/secondary index buffer allocation is gated by `flags & 0x4000`
  (`test ah, 0x40`), not by `flags & 0x40`.
- The vertex-buffer pool is the first `0x8ca4` bytes of
  `g_direct3d_renderer` at `0x4f7458`: one count followed by 3000 0xc-byte
  wrappers. Its 3000-entry index-buffer factory is the embedded subobject at
  renderer `+0x8ca4` (`0x5000fc`), not an unrelated neighboring global.
- The `flags & 4` warm-up scan is an `else if` chain. For each source
  vertex/face pair, native appends only the first matching corner, matching the
  IDA control flow rather than four independent corner tests.
- The known caller ignores this helper's return value. Modeling the scratch as
  `void` better matches the native incidental return state than manufacturing
  `return 0` / `return result`.
- Native's final index upload is an inline MSVC `memcpy` intrinsic
  (`rep movsd`/`rep movsb`), not an out-of-line CRT call. Promoting the scratch
  to `#pragma intrinsic(memcpy)` also recovers the native `ebx` ownership for
  the object pointer through most of the function.
- Each grouped face owns six advancing `unsigned short*` index lanes. They are
  initialized from the shared index scratch plus the current index count,
  advanced by three slots for a triangle or six for a quad, and preserve the
  reused `0/2` lanes explicitly. The face itself remains Object-owned and is
  reloaded through the running 0x30-byte face offset for every corner.
- The 0x1c-byte `ObjectGroupedVertex` scratch begins with the same 0x18-byte
  render payload written to `ObjectRenderVertex`: `diffuse` is copied as a
  scalar, UV as one `ObjectUv`, and XYZ as one `Vector3`; the trailing dword is
  the source-object vertex index used only by the append/dedup helper.

Rejected probes:

- An earlier six-pointer probe paired the cursors with a cached face pointer and
  scalar vertex upload. It regressed to 38.48% and moved object ownership from
  `ebx` to `ebp`; the cursor hypothesis was only accepted after Binary Ninja
  proved the owner-relative face reloads and aggregate upload that complete the
  native source shape.
- Retesting the non-void return shape after the intrinsic/local-lifetime edits
  dropped slightly to 42.14% and reintroduced an explicit zero-return block.
- Replacing the aggregate UV/position copies with manually advanced byte
  offsets slightly regressed the focused result and lost one clean relocation;
  no synthetic frame or padding local is retained.

Exact closure:

- Direct Object-owned warm-up accesses, the six lane cursors, authored
  triangle/quad branch order, index-count-first cursor advancement, and the
  aggregate render upload reproduce the native 0x28-byte frame and full
  instruction stream without padding, volatile tricks, or dead work.

2026-07-10 retained-resource closure: the builder now has one shared
`void(Object*)` declaration across its exact `ObjectList::build_all_objects`
caller, scratch, Binary Ninja, and IDA. This corrects the live Binary Ninja
prototype from a synthetic `ObjectIndexBuffer*(int32_t)` return and makes the
five retained products at `+0xc0/+0xc8/+0xcc/+0xd0/+0xd4` visible as fields.
The exact caller/callee contract remains unchanged by the later source-shape
recovery.

2026-07-11 renderer-owner closure: the builder now reaches both buffer pools
through `Direct3DRenderer`. The index receiver compiles as
`g_direct3d_renderer+0x8ca4`; giving the manifest the proven `0xbcc0` renderer
extent resolves that interior relocation against the existing `0x5000fc`
reference without an alias or operand waiver. Focused matching remains exact at
373/373 with all 29 operands clean.
