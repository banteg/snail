# Reconstruction notes

## Scope

Target: `initialize_loopbow_path_template_pair` at `0x42ba80`, compiled with
MSVC 6.5 using `/O2 /G5 /W3`.

The starter was only a two-instruction stub.  This scratch reconstructs the
complete path-template initializer: constructor fields, two sample arrays, the
loop-bow curve, normalized sample deltas, terminal directions, strip vertices,
face quads, UVs, texture selection, and the finalizer call.

## ABI and layout findings

The native function is a `thiscall` with six stack arguments and `ret 0x18`:

```cpp
float curve_scale,
unsigned int width_cells_arg,
char unused_mode,
char* texture_a,
char* texture_b,
char* unused_texture
```

The two apparently unused arguments are retained because surrounding native
call sites push six arguments.  The earlier four-argument skeleton could not
reproduce the native epilogue or texture argument slots.

Scratch-local overlays were kept intentionally narrow:

- `AttachmentSample` has stride `0xa8`.
- Its transform is at `+0x00`, delta vector at `+0x80`, delta length at
  `+0x8c`, center value at `+0x90`, and loop-bow scalar fields through `+0xa4`.
- `LoopbowFaceQuad` has stride `0x30`, five 16-bit vertex/header fields,
  a texture pointer at `+0x0c`, and eight UV floats through `+0x2c`.
- Only the `AttachmentPathTemplate` fields used by this function are overlaid.

Compile-time size checks guard both reconstructed element strides.

## Reconstructed behavior

The accepted body follows the native phases in order:

1. Initialize path-template flags and dimensions, derive
   `curve_segment_count = int(curve_scale * 2*pi)`, add fourteen straight
   samples, and allocate both sample arrays.
2. Build seven incoming straight samples and seven outgoing straight samples.
3. Build the circular middle section, including center interpolation, the
   primary and secondary radii, basis-vector construction, the world-Y
   rotation, and the secondary `0.49f` normal offset.
4. Compute and normalize primary and secondary deltas, then construct separate
   `{0, 0, 1}` terminal direction values.
5. Allocate the strip mesh, generate the `(segments + 1) * (width + 1)` vertex
   grid, and synthesize the extra terminal row from the final sample.
6. Emit two `0x30` face quads per cell with the native winding split, UV scale
   of `0.125f`, parity branch, and the two texture arguments.
7. Call `finalize_path_template(this)`.

The two `multiply_matrix_in_place` calls compile at the exact native relative
addresses `+0x56c` and `+0x57d`.  Their symbol identity remains unresolved by
the matcher, but their masked operands do not mismatch.

## Source-shape decisions

The most productive source-shape changes were:

- correcting the six-argument ABI;
- using direct indexed sample accesses for the two straight sections;
- preserving the native floating-point literal spellings and expression order;
- materializing value `Vector3` objects for arc/delta/mesh calculations;
- constructing distinct primary and secondary terminal direction temporaries;
- retaining a meaningful endpoint vector for the synthetic final mesh row;
- declaring the sample pointer separately inside each vertex-loop branch;
- duplicating face construction in the two side branches instead of merging a
  common face pointer and common tail.

The endpoint and branch-local pointer lifetimes recover the native `0x9c`
local frame without dummy locals or stack padding.  The candidate also ends in
`ret 0x18`, as required by the recovered ABI.

## Remaining differences

The first mismatch is now local-slot allocation rather than control flow:

```text
target[10]    mov [esp+0x2c], esi
candidate[10] mov [esp+0x24], esi
```

The overall frame size is nevertheless exact.  Remaining structural drift is
concentrated in:

- local lifetime/slot ordering in the constructor and arc setup;
- the basis-copy and secondary-offset sequence after the two matrix calls;
- x87 evaluation order and pointer induction in the vertex-grid loop;
- register allocation and duplicated texture/UV stores in the face loop.

No inline assembly, fake globals, volatile clutter, or artificial frame padding
was used.

## Next region to attack

The highest-value next pass is the vertex-grid block beginning near target
offset `+0x7d3` (roughly target instructions 515 onward).  Moving the sample
pointer into the two branches produced the final large score gain, which shows
that this region is still highly sensitive to plausible source-level lifetime
and evaluation-order changes.  The next experiments should focus on the row
sample-offset induction, the terminal-row endpoint expression, and preserving
`lateral` on the x87 stack, while leaving the already exact frame and matrix
call positions intact.

## Validation command

```sh
tools/match/match.sh \
  tools/match/scratches/initialize_loopbow_path_template_pair \
  --regions --max-regions 20 --region-context 6
```
