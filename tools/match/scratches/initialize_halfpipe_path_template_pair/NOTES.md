# `initialize_halfpipe_path_template_pair` reconstruction notes

## Recovered behavior

This is an honest starter reconstruction for the public `HALFPIPE` attachment
initializer at `0x429b20`. The direct world-init call places it in authored
slot `42`; its output also carries runtime kind `42`.

- keeps the six stack-argument call shape from the game asset initializer
  (`ret 0x18`), using the `8` argument as the real width-cell count;
- initializes kind `0x2a`, mirror/exit flags, width, scale, and the fixed
  66-sample count;
- calls `allocate_path_template_samples` and clears the runtime flag at `+0x9c`;
- builds the 16 entry samples and 16 exit samples with the sinusoidal depth
  envelope and stores the resulting kind-42 radius in the sample `+0xa0` field;
- builds samples 16 through 49 as the straight center section with radius `4.0`,
  normalized forward vectors, a right vector from up x forward, and secondary
  transforms offset by `0.49` along the up axis;
- computes primary and secondary delta vectors and unit terminal deltas;
- allocates the generated strip-mesh vertex and facequad grids;
- calls `compute_kind42_attachment_transform` while emitting vertices, and
  applies the transformed x/y coordinates for the non-terminal curved rows; and
- assigns the two supplied textures with the target's 1/8 tiled UV pattern.

## Source-shape choices

The callsite in `initialize_game_assets_and_world` passes six explicit
arguments after `this`:

```cpp
initialize_halfpipe_path_template_pair(this + ..., 1086324736, 8, 1,
    texture_a, texture_b, (int)aObjectsPathVer);
```

The decompiler signature is stale and treats the width as `texture_a`. This
scratch keeps the larger stack shape and uses the second explicit argument as
`width_cells`.

The local sample and facequad overlays mirror the established path-template
scratch layout: sample stride `0xa8`, strip mesh pointer at `+0x24`, kind and
count fields at `+0x38` through `+0x5c`, and facequads at `0x30` bytes.

## Remaining work

This is intentionally a starter. The high-value follow-up areas are source
spelling and lifetime work around:

- the entry/exit loops, where the target uses byte-offset induction variables;
- the middle-sample loop, especially its reuse of a local `out_angle` stack
  slot and the transform copy into the secondary sample;
- the vertex loop, where native code keeps a reused sample byte offset and
  stack-resident kind-42 transform; and
- the exact face-loop branch shape.

Current matcher result:

```text
match: 35.95%
target: 707 insns, candidate: 667 insns
prefix: 0/707 target insns
masked operands: 45 ok, 0 unresolved, 1 mismatch
```

No fake matching tricks were used.

## 2026-06-20 shared type pass

The scratch now uses the shared `Path`, `AttachmentSample`,
and `ObjectFaceQuad` declarations. The local facequad overlay mapped directly to
`ObjectFaceQuad`; the zero store is spelled through `header_word` to preserve
the former 16-bit `flags` store.

The matcher stayed at the current baseline:

```text
match: 35.95%
target: 707 insns, candidate: 667 insns
masked operands: 45 ok, 0 unresolved, 1 mismatch
```

This removes the initializer from the `Path` scratch-local
type row while keeping the documented six-argument call shape.

## 2026-07-03 vertex-grid source-shape pass

Focused matcher after the retained vertex-index spelling:

```text
match: 36.22%
target: 707 insns, candidate: 668 insns
masked operands: 46 ok, 0 unresolved, 1 mismatch
```

Two source-shape probes were tried in the strip-mesh vertex loop:

- spelling the non-terminal row first matches the native branch order but is
  score-neutral by itself; and
- replacing the pinned `Vector3* vertex` cursor with a stable `vertex_index`
  is retained because it improves the vertex-loop region and adds one more
  masked operand to the audited set.

Remaining local debt: native still keeps the vertex base in `edi`, the row in
`esi`, the column in `ebx`, and the sample byte offset on the stack. The current
candidate still differs in that register/lifetime split, and the stack frame is
still `0x7c` instead of native `0x9c`.

## 2026-07-03 exit-loop byte-offset pass

Focused matcher after separating the exit sample byte offset from the logical
exit counter:

```text
match: 37.04%
target: 707 insns, candidate: 659 insns
masked operands: 45 ok, 0 unresolved, 1 mismatch
```

The retained spelling mirrors the native exit loop's separate sample-offset and
small counter ownership better than the old indexed `for (i = 50; i < 66; ++i)`
shape. It drops one audited masked operand compared with the vertex-grid pass,
but keeps the same single relocation mismatch and materially improves the
focused fuzzy score.

## 2026-07-03 mesh request-order pass (superseded)

Focused matcher after requesting facequads before vertices:

```text
match: 37.34%
target: 707 insns, candidate: 659 insns
masked operands: 46 ok, 0 unresolved, 0 mismatch
```

This source order was retained because it cleared the old audit mismatch and
moved focused Wibo from 37.04% to 37.34%. It was later rejected: both target
exports show vertices requested before facequads, so the higher score came from
ambiguous alignment of two normalized `call ADDR` instructions rather than
recovered behavior.

## 2026-07-04 middle-loop byte-offset retest

A direct byte-offset rewrite of the middle sample loop was rejected. It mirrored
the native decompiler's `0xa80`-to-`0x20d0` sample-offset counter and explicit
primary/secondary pointers, but it lowered the focused matcher:

```text
match: 32.21%
target: 707 insns, candidate: 634 insns
masked operands: 44 ok, 0 unresolved, 0 mismatch
```

Restoring the indexed `for (i = 16; i < 50; ++i)` loop brings the scratch back
to the current baseline:

```text
match: 37.34%
target: 707 insns, candidate: 659 insns
masked operands: 46 ok, 0 unresolved, 0 mismatch
```

The native-looking byte-offset ownership is therefore not portable to this loop
without also solving the surrounding stack-frame and transform-copy lifetime.

## 2026-07-15 honest mesh request-order correction

The target calls `request_object_vertices` at `0x42a10b`, followed by
`request_object_facequads` at `0x42a11d`. The scratch now preserves that order
and the target's multiplication ownership:

```text
match: 37.04%
target: 707 insns, candidate: 659 insns
masked operands: 46 ok, 0 unresolved, 0 mismatch
```

The 37.34% facequads-first version is intentionally rejected despite its higher
fuzzy score. The reference-aware masked-operand aligner now associates these
repeated `call ADDR` sites with their actual callees, so the evidence-backed
order remains audit-clean without a metric-driven source reordering.

## 2026-07-17 live constructor ABI closure

Native world-init disassembly pushes `6.0f`, width `8`, mode `1`, two surface
textures, and the vertical texture before the slot-`0x2a` call; the tail at
`0x42a530` is `retn 0x18`. The iOS Path.o symbol
`cRPath::BuildHalfPipe(float, int, bool, char*, char*)` independently confirms
the portable prefix. This also proves the first scratch parameter is a float,
not an integer bit bucket; the shared declaration, callee, and caller now spell
that real type while generating identical code.

Guarded recreation and post-write readback expose the complete seven-parameter
`Path*` prototype with no pending operation. The refreshed caller passes all
six stack operands through `path_pairs[0x2a].primary`, and the callee ends in
void finalizer flow. Focused matching remains 37.04% (659/707) with 46 clean
masked operands, and the world initializer remains byte-for-byte unchanged at
80.50% (5392/5411).

## 2026-07-20 live lifetime ownership

A guarded transaction proves eleven complete live owners across the lead-in,
curve orientation, secondary offset, terminal deltas, mesh vertex generation,
and both face records. The single existing fixed-index sample `__offset`
remains unchanged. Typing the pre-biased curved-sample cursor was rejected
because it added three backward `__offset` accesses; the retained replay keeps
that cursor automatic. Focused matching remains 37.04% (659/707) with 46 clean
masked operands.
