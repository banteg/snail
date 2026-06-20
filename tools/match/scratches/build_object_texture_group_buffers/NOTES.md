# build_object_texture_group_buffers

Structure-first scratch for the object texture-group buffer builder at
`0x413d50`.

Current Wibo result: 42.20%, 319/373 candidate/target instruction shape,
prefix 0/373, masked operands 24 ok, 0 unresolved, 0 mismatch.

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
- The vertex-buffer factory is the existing `g_direct3d_renderer` object at
  `0x4f7458` under a scratch-local factory view. The index-buffer factory is
  the neighboring object at `0x5000fc`.
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

Rejected probes:

- Rewriting the texture-group expansion around six long-lived output-pointer
  locals grew the frame toward native size but regressed to 38.48% and moved
  object ownership from `ebx` to `ebp`, so the clearer indexed loop is retained
  for now.
- Retesting the non-void return shape after the intrinsic/local-lifetime edits
  dropped slightly to 42.14% and reintroduced an explicit zero-return block.

Expected residuals:

- The main remaining residual is native's larger `0x28` frame and saved-register
  schedule. The group loop still differs in pointer-local ownership and branch
  layout; direct pointer-local source spelling currently loses the better object
  register, so continue only with a stronger source-idiom lead.
