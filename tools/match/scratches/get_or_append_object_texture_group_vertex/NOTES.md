# get_or_append_object_texture_group_vertex

Relationship-first scratch for the private grouped-vertex append helper at
`0x413bb0`.

Current Wibo result: 65.34%, 124/127 candidate/target instruction shape,
prefix 25/127, masked operands 9 ok, 0 unresolved, 0 mismatch.

Recovered relationships:

- Called only by `build_object_texture_group_buffers`.
- Reads `Object +0x2c` vertex count, `+0x38` vertices, `+0x48` vertex colours,
  and `+0x10` flags.
- `g_object_grouped_vertex_cursor` (`data_5031bc`) is the append cursor and
  return index for the 0x1c-byte temporary grouped-vertex stream.
- `g_object_grouped_vertex_scratch` (`data_5031c4`) points at temporary records:
  position `+0x00..+0x08`, packed diffuse `+0x0c`, UV `+0x10/+0x14`, and source
  vertex index `+0x18`.
- Source V is stored flipped as `1.0f - v`.
- `flags & 0x10000` enables per-vertex colour packing from `Object +0x48`;
  otherwise diffuse is `0xffffffff`.

Corrected assumptions:

- The de-duplication key is flag-dependent. With `flags & 4`, native matches
  on source vertex index plus UV only; without that flag, it matches on full
  position plus UV.
- The native source-position local is better represented as a semantic
  `Vector3` stack copy than as an integer bit array. This preserves the native
  address-then-load sequence for `object->vertices[vertex_index]` and moves the
  first mismatch from the source copy to the loop-entry branch.
- The de-duplication loop uses a byte cursor starting at
  `g_object_grouped_vertex_scratch + 4`, so the no-`flags & 4` comparisons are
  naturally `cursor - 4`, `cursor`, and `cursor + 4` for x/y/z, while the
  `flags & 4` source-vertex comparison is `cursor + 0x14`.

Rejected probes:

- Plain `float` locals for x/y/z regressed to 31.45% by removing the native
  0x0c stack-local copy shape.
- Union/int-source spellings and a common-result/goto return block were neutral
  at the then-current score, so they were left out.
- A raw byte-offset append tail produced x87 stores but dropped to 62.99% and
  introduced a masked global mismatch (`g_object_grouped_vertex_cursor` versus
  `g_object_grouped_vertex_scratch`), so the typed append pointer is retained.

Expected residuals:

- Native still lays out the fall-through append block and found-return block
  differently, using `jl` back to the loop where the scratch emits `jge` plus a
  jump. The append tail also differs in x87 scheduling versus integer copies
  for unchanged float words. Further work needs a real source idiom for that
  layout, not return-goto reshuffling or raw-offset append nudging.

2026-06-21 found-label follow-up: an explicit found label after the append block
is codegen-neutral at 63.20% once the skipped `appended`/`result` declarations
are hoisted for C++ legality. A guarded found label before the append block
regresses to 62.70%. The retained direct returns remain the clearest source;
the loop-tail `jge`/`jmp` residual is not fixed by legal label spelling alone.

2026-07-09 append-return shape: spelling the cursor update as
`++g_object_grouped_vertex_cursor; return g_object_grouped_vertex_cursor - 1;`
recovers native's `inc` / store / `dec` epilogue and raises focused Wibo from
63.20% to 65.34% (124/127 insns, 25/127 prefix, 9 clean masks). The older
`result = cursor; cursor = result + 1; return result` form left a non-native
`lea` return path. Typed `appended->` for the default diffuse store and a
shared `flipped_v` local both regress, so only the cursor return change is
retained. Remaining debt is still loop-exit branch layout and append float
store scheduling.
