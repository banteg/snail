# `initialize_kind42_path_template_pair` reconstruction notes

## Recovered behavior

This is an honest starter reconstruction for the kind-42 nonlinear attachment
initializer at `0x429b20`. It models the observed source behavior:

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
initialize_kind42_path_template_pair(this + ..., 1086324736, 8, 1,
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

The scratch now uses the shared `AttachmentPathTemplate`, `AttachmentSample`,
and `ObjectFaceQuad` declarations. The local facequad overlay mapped directly to
`ObjectFaceQuad`; the zero store is spelled through `header_word` to preserve
the former 16-bit `flags` store.

The matcher stayed at the current baseline:

```text
match: 35.95%
target: 707 insns, candidate: 667 insns
masked operands: 45 ok, 0 unresolved, 1 mismatch
```

This removes the initializer from the `AttachmentPathTemplate` scratch-local
type row while keeping the documented six-argument call shape.
