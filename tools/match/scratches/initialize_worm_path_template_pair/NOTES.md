# initialize_worm_path_template_pair @ 0x420170

This scratch reconstructs the worm attachment-path constructor and its generated
strip mesh using the shared native `AttachmentSample`, `Path`, and
`ObjectFaceQuad` owners.

Current focused result:

- match: **72.28%**;
- target/candidate instructions: **736 / 725**;
- common prefix: **0 / 736**;
- masked operands: **37 clean, 0 unresolved, 0 mismatched**;
- native/candidate local frames: **0x80 / 0x68**.

The zero common prefix is solely the honest frame-size mismatch in the first
instruction (`sub esp, 0x80` versus `sub esp, 0x68`), not a missing constructor
prefix. The following constructor stores and allocation call are strongly
aligned.

## Recovered behavior

The implementation covers the complete high-level body visible in the native
function:

- assigns kind `24`, clears mirror/exit state, selects 16 radial cells, a
  4-unit segment width/radius scale, 24 samples, and the 96-unit total span;
- allocates primary and secondary sample arrays and clears the runtime flag;
- initializes all 24 samples at y `0.49`, with z advancing by four units,
  identity transforms, unit lateral scale, and zeroed rotation/special fields;
- rebuilds forward/right/up basis rows for the middle sample range, preserving
  the distinct first-iteration identity path seen in the target;
- computes and normalizes primary and secondary deltas, then supplies the
  terminal `(0, 0, 1)` direction and four-unit length;
- allocates a 25-by-16 vertex grid, 768 double-sided facequads, and per-vertex
  colours on the strip mesh;
- generates each tube row from the sample position and basis using sine/cosine,
  a radius of `4 * lateral_scale`, and an alpha wave of
  `0.5 - 0.5 * cos(2 * row_angle)`;
- extrapolates the terminal row from the previous row, scales vertices below
  y zero by `0.3`, and emits two opposite windings for every row/column cell;
- wraps the final radial column, assigns U coordinates from the 16-column
  fraction, advances V by `0.125` per path row, resolves the supplied texture,
  and calls `finalize_path_template`.

The constructor and finalizer are intentionally declared `void`. The related
matched finalizer shows that the apparent non-void decompiler result is stale
EAX state rather than a source-level return value.

## Source-shape findings

The useful gains came from ordinary source spelling rather than stack padding
or compiler tricks:

- Direct sample-array expressions and repeated natural indices recover the
  native SIB/register plan better than long-lived sample aliases.
- A zero-based `middle_index` with `if (middle_index != 0)` recovers the native
  first-iteration branch and induction register.
- Direct primary/secondary delta loops preserve the native normalize-call
  layout.
- Scalar-left vector operators, plus real `up_radius`, `up_component`,
  `base_plus_right`, and `vertex` temporaries, substantially improve the x87
  tube-generation block.
- Keeping the ordinary vertex row as the fallthrough and the extrapolated row
  in the `else` branch gives the target's branch polarity.
- Converting the column once, writing colours inside each row branch, and using
  a real `lowered_y` temporary preserve native temporary lifetimes.
- The face loop works best with a two-iteration `side` loop and a direct
  `if (side == 0)` winding/UV branch.

Measured milestones from the focused pass were:

| Source-shape stage | Match |
|---|---:|
| Starter skeleton | 0.27% |
| Complete semantic first pass | 22.59% |
| Direct array/index and vector-temporary pass | 34.11% |
| Native-shaped middle branch | 36.63% |
| Direct delta and face-side loops | 46.06% |
| Zero-based middle induction | 51.82% |
| Direct vertex-grid indexing | 59.78% |
| Scalar-left vector expression shape | 67.17% |
| Named radius/y temporaries and direct texture call | 67.90% |
| Native vertex-row branch polarity | 72.28% |

## Residuals

The remaining mismatch is compiler shape rather than a known missing semantic
lane:

- The target reserves `0x80` bytes while this source naturally reserves
  `0x68`. The target keeps additional vector/x87 staging copies around the
  trigonometric expression.
- The candidate is 11 instructions shorter. The broad vertex-expression region
  is `target[461:525]` versus `candidate[460:518]` at 57.38%.
- The largest remaining tail is the face/UV loop,
  `target[556:736]` versus `candidate[549:725]` at 45.51%. It differs in
  temporary stack slots, register lifetimes, and a native parity-looking branch
  before the texture lookup.
- Both sides of that native texture branch ultimately pass the sole
  `texture_path` argument. Reproducing it with a redundant source branch is not
  justified and measured worse, so the clean direct call is retained.
- Some early sample loops still differ only in equivalent base/index operand
  ordering and spill-slot placement.

A by-value vector-operator experiment did recover the exact `0x80` frame, but
it lowered the full-function result to 66.85%, grew the candidate to 739
instructions, and introduced a masked sine/cosine alignment mismatch. It is
rejected rather than using frame size as a metric-only goal. Likewise, an
explicit duplicated texture-parity branch fell to 62.27%; face aliases,
alternate `for` spellings, and several operator-return variants were neutral or
regressive.

## 2026-06-20 shared type pass

The sample and owner overlays now use the shared `AttachmentSample` and
`Path` declarations from `track_attachment_types.h`. The
matcher stayed at the accepted baseline:

```text
match: 72.28%
target: 736 insns, candidate: 725 insns
masked operands: 37 ok, 0 unresolved, 0 mismatch
```

## 2026-07-14 facequad ownership pass

The scratch now uses the `Object::facequads` element type directly instead of a
duplicate `WormFaceQuad`. The shared `ObjectFaceQuad` exposes both its canonical
`uv[4]` array and the native constructor's flat `u0/v0` through `u3/v3` view.
That preserves the source shape identified by the earlier rejected indexed-UV
experiment while recovering the real allocation owner. The 16-bit constructor
store uses `header_word`, rather than the byte-sized runtime `flags` view.

The focused result is byte-for-byte unchanged from the accepted baseline:

```text
match: 72.28%
target: 736 insns, candidate: 725 insns
masked operands: 37 ok, 0 unresolved, 0 mismatch
```
