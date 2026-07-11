# `initialize_cage2_path_template_pair` reconstruction notes

## Recovered behavior

The scratch now reconstructs the complete cage-2 path-template initializer rather
than returning a placeholder value. The implementation:

- initializes kind `0x0f`, mirror/exit flags, width, scale, and the fixed
  22-sample count;
- calls `allocate_path_template_samples`;
- builds the primary and secondary endpoints, including the `0.49f` secondary
  Y offset and Z endpoints `0.0f` / `21.0f`;
- generates the 20 interior samples with the two cage-curve angles,
  identity/derived rotation branches, normalized forward vectors, cross-product
  right vectors, and world-Z rotation;
- computes primary and secondary delta directions and lengths;
- installs terminal `{0, 0, 1}` directions and unit lengths;
- allocates and fills the strip-mesh vertex grid and both facequads per cell;
- assigns the two supplied textures and the `1/8`-tile UVs; and
- calls `finalize_path_template`.

No shared headers were changed. Conservative scratch-local overlays are used for
fields whose promoted repository types are still incomplete.

## Prototype correction

The decompiler prototype exposes three explicit parameters, but the native
function ends in `ret 0x10`, and the surrounding constructor callsite passes four
stack arguments after `this`. The recovered member prototype is therefore:

```cpp
void initialize_cage2_path_template_pair(
    int width_cells,
    char* texture_a,
    char* texture_b,
    char* vertical_texture);
```

The fourth texture argument is unused by this initializer. Keeping it is
necessary to reproduce the native calling convention and epilogue.

## Local layout overlays

`CageAttachmentSample` is fixed at `0xa8` bytes and preserves the offsets used by
the target:

- transform `+0x00`;
- delta direction `+0x80`;
- delta length `+0x8c`;
- center X `+0x90`;
- scalar fields `+0x94` through `+0xa4`.

`CageFaceQuad` is fixed at `0x30` bytes, with five leading 16-bit fields, texture
reference at `+0x0c`, and four UV pairs beginning at `+0x10`.

The path-template overlay preserves the observed fields at `+0x24`, `+0x38`
through `+0x5c`, and the runtime flag at `+0x9c`.

## Source-shape decisions that improved code generation

- Aggregate `Vector3(...)` assignments are retained for basis-forward and delta
  construction. In particular, replacing scalar delta stores with a real vector
  temporary raised the matcher from about `35.8%` to `40.57%` and recovered the
  target's copy/spill sequence.
- The vertex loop also uses real generated-position vectors. A separate
  `lateral_offset` vector in the terminal row is the final accepted refinement;
  it raised the score from `43.49%` to `43.55%`.
- The face loop deliberately reloads `(unsigned short)width_cells + 1` rather
  than caching a stride. The target repeatedly performs those word loads.
- The parity-controlled duplicate texture calls are retained. Although the two
  arms use the same texture for a given face orientation, the target preserves
  the redundant branch and out-of-line call path.
- The world-Z angle keeps an explicit float cast around
  `(1.0f - cosine(curve_angle)) * 0.5f`. Without that source boundary, VC6 folds
  constants and creates masked-constant mismatches.
- A single semantic mesh cursor is reused for the zero initialization, sample
  byte offset, and face-row traversal. It gives a slightly better global layout
  than independent cursors, even though VC6 spills it instead of retaining the
  target's `ebx` allocation.

Measured milestones during reconstruction were approximately:

| Shape | Match | Candidate instructions |
|---|---:|---:|
| Starter return | 0.19% | 2 |
| Complete scalar reconstruction | 27.76% | 549 |
| Vector-shaped basis work | 35.79% | — |
| Aggregate delta loop | 40.57% | 593 |
| Aggregate vertex grid | 42.23% | 605 |
| Face-loop reload/control-flow work | 43.22% | 623 |
| Float-boundary cleanup | 43.49% | 622 |
| Terminal-row lateral vector | **43.55%** | **629** |

## Target-range anomaly

The saved target range is larger than the native initializer. In the target
dump:

- the initializer's `ret 0x10` is target instruction 644 (645 instructions
  through the return);
- padding continues through target instruction 657; and
- a different frame-pointer function begins at `0x42f0a0`, target instruction
  658, then continues through the reported target instruction 1028.

Thus the official 1029-instruction score includes 371 instructions belonging to
the following function, plus the post-return padding. The official matcher
number remains the result of record, but the concatenated tail explains the
large final unmatched region and should be corrected before expecting a normal
whole-function percentage.

## Rejected trials

- Inverting the `i <= 1` branch produced a clean masked audit but collapsed
  global alignment to `27.74%`.
- Naming the rotation factor removed constant folding in isolation but changed
  register allocation throughout the curve body and fell to about `28.73%`.
- Direct-cast and double-valued loop-index forms reached only `43.20%` and
  `43.26%`; the latter also introduced qword constants unlike the target.
- Moving the destination vertex calculation later made the terminal-row block
  locally closer but changed global register allocation and fell to about
  `28.82%`.
- Shared or terminal vector locals, two-vector vertex rewrites, and explicit
  scalar arrays did not recover the native `0x54` frame; tested scores ranged
  from roughly `37.96%` to `43.12%`.
- Three-vector and copy/add terminal-row spellings increased instruction count
  but scored below the accepted lateral-offset form.
- Caching the mesh stride removed the target's repeated 16-bit width reloads and
  reduced the face-loop match.
- `register` hints and named secondary-Y constants were code-generation neutral.

## Remaining work

The next high-value region is the interior-sample loop preheader and induction
shape. The target keeps an integer counter in the reused argument slot and emits
`fild` each iteration; the current candidate strength-reduces that conversion
into a floating induction value. Recovering that source shape should also help
align the identity/derived-rotation call sites and remove the one masked call
mismatch.

After that, the terminal vertex row is the best stack-frame target. The native
branch keeps additional scalar spills at post-save stack offsets `+0x5c` and
`+0x60`, while the candidate still compiles with a `0x48` frame instead of
`0x54`. This should be pursued through real vector/scalar lifetimes, not padding.

## 2026-06-20 shared type pass

The scratch now uses the shared `Path`, `AttachmentSample`,
and `ObjectFaceQuad` declarations. The local facequad overlay mapped directly to
`ObjectFaceQuad`; the zero store is spelled through `header_word` to preserve
the former 16-bit `flags` store.

The matcher stayed at the accepted baseline:

```text
match: 43.55%
target: 1029 insns, candidate: 629 insns
masked operands: 39 ok, 0 unresolved, 1 mismatch
```

The shared type report now removes this initializer from the
`Path` scratch-local list. The target-range anomaly above
still applies.
