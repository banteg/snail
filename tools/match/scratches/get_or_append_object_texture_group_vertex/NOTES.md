# get_or_append_object_texture_group_vertex

Current result: **100.00%**, 127/127 instructions, all 18 references clean.
This supersedes the historical residual assessments below.

Relationship-first scratch for the private grouped-vertex append helper at
`0x413bb0`.

Current Wibo result: 83.14%, 128/127 candidate/target instruction shape,
prefix 25/127, masked operands 18 ok, 0 unresolved, 0 mismatch.

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
- `OBJECT_FLAG_USE_VERTEX_COLOURS` enables per-vertex colour packing from
  `Object +0x48`; otherwise diffuse is `0xffffffff`.

Corrected assumptions:

- The de-duplication key is flag-dependent. With
  `OBJECT_FLAG_DYNAMIC_VERTICES`, native matches
  on source vertex index plus UV only; without that flag, it matches on full
  position plus UV.
- The native source-position local is better represented as a semantic
  `Vector3` stack copy than as an integer bit array. This preserves the native
  address-then-load sequence for `object->vertices[vertex_index]` and moves the
  first mismatch from the source copy to the loop-entry branch.
- The de-duplication loop uses a byte cursor starting at
  `g_object_grouped_vertex_scratch + 4`, so the static comparisons are
  naturally `cursor - 4`, `cursor`, and `cursor + 4` for x/y/z, while the
  dynamic source-vertex comparison is `cursor + 0x14`.

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

2026-07-10 shared-scratch ownership: native reloads
`g_object_grouped_vertex_scratch` for every appended field rather than keeping
an owned pointer to the new record. Writing x/y/z, u/v, diffuse, and the source
index directly through `g_object_grouped_vertex_scratch[i]` reproduces those
global reloads and the native x87 stores, raising focused Wibo from 65.34% to
83.14% (128/127 insns, 25/127 prefix, 18 clean masks). This confirms the array
is reusable global build workspace owned by the texture-group build pipeline,
not a record returned or retained by this helper. An explicit found-label form
is codegen-neutral, a `break` plus post-loop result check regresses to 82.49%,
and `for`/`while` loop spellings regress to 79.69% with a four-instruction
prefix. The source therefore retains the semantic `do`/`while` search and
direct returns. The honest residual is one loop-exit block-placement choice
(`jl` in native versus `jge` plus `jmp` here); no goto or volatile nudge is
justified.

2026-07-14 scratch-record ownership: the narrow loop cursor now starts from
`ObjectGroupedVertex::y` and advances by `sizeof(ObjectGroupedVertex)` instead
of raw `+4`/`+0x1c` constants. It preserves the same 83.14%, 128/127
instruction frontier, prefix 25, and all 18 clean operands; the honest
loop-exit block-placement residual is unchanged.

## 2026-07-15 shared-workspace ABI replay

The helper declaration and both workspace globals now live in the shared
Object header. Repeatable Binary Ninja sync types the first argument as the
borrowed `Object*`, names the vertex/UV arguments, and preserves
`g_object_grouped_vertex_scratch` plus its append cursor as builder-owned global
workspace. Focused matching remains 83.14% with all 18 operands clean; the
honest loop-exit block-placement residual is unchanged.

## 2026-07-18 paired replay closure

IDA now receives the same `Object*` ABI, `ObjectGroupedVertex*` scratch owner,
and `int32_t` cursor as Binary Ninja. Both shared globals remain temporary
workspace owned by `build_object_texture_group_buffers`; neither is retained
by an object. Replay health checks reject raw `_DWORD*` object arguments and
anonymous absolute globals. Matcher source and the honest 83.14% frontier are
unchanged.

## 2026-07-23 source borrow and append-offset replay

The existing texture-group builder replay now covers this private helper rather
than adding a second overlapping script. It distinguishes the retained
`Object::vertices` bank from the one borrowed `Vec3* source_vertex`, and names
the x/y/z component lifetimes that native copies into its stack position
record. The search cursor remains an intentional `float*` interior borrow
starting at `ObjectGroupedVertex::y`.

The ESI strength-reduction chain for `index * 0x1c` is explicitly kept as
integer arithmetic, ending in `int32_t append_byte_offset`; the former
`float*` inference was false ownership. Optimized HLIL folds that verified
offset back into `g_object_grouped_vertex_scratch[grouped_vertex_index]`, so
all appended x/y/z, UV, diffuse, and source-index stores now visibly target the
same builder-owned record.

The shared replay guards the `Vec3`, `ObjectGroupedVertex`, and `Object`
layouts before previewing any mutation, and a second run is fully idempotent.
Focused Wibo remains 83.14%, 128/127 candidate/target instructions, prefix 25,
and all 18 masked operands clean. No matcher source changed; the loop-exit
block-placement residual remains visible.

## 2026-07-27 mobile AddVertexUV ownership

Android retains the factored authored helper
`AddVertexUV(cGLVertexUV*, int&, tVector*, float, float)` immediately before
`cRObject::BuildGLVertexArray()`. Its complete body borrows the builder's
scratch vertex bank, compares position plus UV, appends on a miss, advances
the caller-owned count by reference, and returns the existing or appended
index. iOS inlines the same five-float search/append loop into
`BuildGLVertexArray()`, independently confirming the helper boundary even
though that build exports no separate symbol.

This is a semantic and ownership mapping, not a layout transfer. Mobile
`cGLVertexUV` is a 0x14-byte position/UV record. Windows deliberately owns a
0x1c-byte `ObjectGroupedVertex`, adding packed diffuse colour and the source
vertex index used by dynamic objects. Windows also keeps its scratch pointer
and count in builder-scoped globals rather than passing both into the helper.
The shared lifecycle is builder-borrowed dedup workspace; the platform record
layouts and ABIs remain distinct.

The matcher source remains unchanged at the honest 83.14%, 128/127
candidate/target instructions, prefix 25, and 18 clean operands. The remaining
loop-exit block placement is a VC6 control-flow choice, so no mobile-shaped ABI
or goto is introduced to force it.

## 2026-07-29 one-instruction CFG audit

The focused frontier remains **83.14%**, `128/127` instructions, prefix
`25/127`, with all 18 operands clean. Three recorded sweeps cover 19 bounded
variants around the sole extra loop-exit jump:

- five signed, reversed, equality, last-index, and difference spellings of the
  `do`/`while` condition were neutral or regressed to 82.35%/82.03%;
- IDA's natural `return g_object_grouped_vertex_cursor++` spelling and two
  explicit result lifetimes regressed to 80.00% or 81.10%, confirming the
  retained increment/store/decrement epilogue;
- all count/index declaration orders and ordinary nonempty guards were
  byte-neutral except `count >= 1`, which regressed to 82.35% and shortened the
  prefix.

Both native decompilers independently retain the direct-return `do`/`while`
search and fallthrough append semantics already in the scratch. The remaining
native `jl` versus candidate `jge` plus `jmp` is therefore bounded to VC6 cold
return-block placement. Previously rejected found-label, break, `for`, `while`,
raw-offset, and shared-flipped-V forms were not repeated, and no control-flow
or lifetime nudge is retained.

## 2026-08-12 recovery classification

Fresh Windows matching and live Binary Ninja readback retain the borrowed
`Object`, source vertex, dynamic/static de-duplication keys, vertex-colour
policy, builder-owned grouped-vertex workspace, append cursor, and complete
seven-dword output record. All 18 references are clean. Android's authored
`AddVertexUV` independently confirms the helper boundary and borrowed
search-or-append lifecycle; the wider Windows record fields remain directly
proved by its native stores and sole builder caller.

The 128/127-instruction difference is the one cold found-return block jump
visible in both Windows decompilers. It does not hide another owner or behavior
path. Recovery is `semantic-complete` with compiler residue; the prior sweep
count is not part of this decision.

## 2026-09-05 bounded source-expression probes

Three search-exit forms (shared label, loop break with append-on-miss, and post-loop found return) do not improve the 83.14% baseline. The shared label is byte-neutral; the other two alter more control flow.

The recorded specifications and experiment receipts preserve these negative
results. They do not establish source exhaustion or compiler provenance.

## 2026-09-05 exact indexed search and loop recovery

A normal for loop over the grouped-vertex bank, testing the object's dynamic
flag directly, reproduces every native instruction and all 18 references.
The scratch no longer invents an interior y-field cursor or retains the flag
snapshot. Typed indexing alone was neutral at 83.14%; pairing it with the
structured loop changes VC6's return-block placement and removes the extra
back-edge instruction, reaching 100%. Retaining the flag snapshot in the same
for loop regresses, showing why isolated return-placement probes missed this
source interaction. Either a direct or cached global count remains exact;
the direct form is retained.

The global bank and its existing field layout remain correct. This is source
control and borrow recovery, with no compiler or reference-audit changes.
