# Path-Template Pair Campaign

Phase B focuses on the path-template constructors that share the same broad
source shape but are still parked in the 12-40% band.

Current board checkpoint from `tools/match/STATUS.md`:

| target | score | notes |
|---|---:|---|
| `initialize_kind42_path_template_pair` | 36.22% | Best non-cage anchor; uses exact `allocate_path_template_samples` and exact `compute_kind42_attachment_transform`. |
| `initialize_loopout_path_template_pair` | 37.37% | Same large strip-mesh skeleton, one masked mismatch. |
| `initialize_looptheloop_path_template_pair` | 35.59% | Loop-family macro scratch, still no prefix. |
| `initialize_looptheloopw_path_template_pair` | 27.96% | Loop-family sibling with roll term. |
| `initialize_hump_path_template_pair` | 14.72% | Worst front-half family target; shares the macro skeleton with dump and other curve families. |
| `initialize_dump_path_template_pair` | 14.67% | Hump twin, inverted vertical lane. |
| `initialize_twister_path_template_pair` | 14.36% | Worst twin target; compact 34-sample nonlinear constructor. |
| `initialize_twister2_path_template_pair` | 14.36% | Twister twin; same source shape with 52 samples. |

`initialize_loopbow_path_template_pair` and `initialize_worm_path_template_pair`
are intentionally excluded from this campaign slice because they are claimed by
other work.

## Shared Skeleton

The established constructor outline is:

1. Write template header fields: `kind`, `is_mirrored_x`, `side_exit_mode`,
   `width_cells`, `width_or_scale`, `segment_count`, and `segment_count_f`.
2. Call `allocate_path_template_samples()` and seed `special_runtime_flag_9c`.
3. Fill primary and secondary `AttachmentSample` arrays using stride `0xa8`.
4. Compute per-sample orientation vectors, usually by orienting the previous
   sample after the next sample is known.
5. Compute primary and secondary `delta_dir_to_next` and `delta_length`, then
   seed the terminal `(0, 0, 1)` direction.
6. Request strip-mesh vertices and facequads from `strip_mesh`.
7. Emit the `(segment_count + 1) * (width_cells + 1)` vertex grid from primary
   samples.
8. Emit two `ObjectFaceQuad` records per mesh cell with the shared 1/8 tiled UV
   pattern and alternating `texture_a` / `texture_b` ownership.
9. Call `finalize_path_template(this)`.

The checked-in shared views for this shape are `AttachmentPathTemplate`,
`AttachmentSample`, and `ObjectFaceQuad`. Keep new scratch changes on those
views unless a target proves a narrower local overlay is necessary.

## First Code Slice

Use `initialize_kind42_path_template_pair` as the breakthrough target. Its
semantics are already close enough to expose source-shape debt:

- native stack frame is `0x9c`; current candidate is `0x7c`;
- entry/exit/middle sample loops are semantically modeled but use different
  local ownership and induction variables;
- the vertex loop is the special kind-42 lane that calls
  `compute_kind42_attachment_transform` and only applies transformed coordinates
  to non-terminal curved rows; and
- facequad emission still uses the shared strip-mesh checkerboard skeleton.

The first retained source probe should improve the focused matcher for
`initialize_kind42_path_template_pair` without changing flags, inventing dummy
symbols, or moving `loopbow`/`worm`.

First retained probe: spelling the vertex grid through a stable `vertex_index`
instead of a pinned `Vector3*` cursor moved `kind42` from 35.95% to 36.22% and
raised audited masked operands from 45 to 46. The native strip-mesh loop still
keeps different row/column/sample-offset register ownership, so leave the next
probe focused on that local lifetime problem.

## Expansion Order

After `kind42` moves, apply the proven spelling mechanically to the four lowest
family scores first:

1. `initialize_twister_path_template_pair`
2. `initialize_twister2_path_template_pair`
3. `initialize_dump_path_template_pair`
4. `initialize_hump_path_template_pair`

For each target, update its `NOTES.md` with the tried spelling, focused matcher
result, and any rejected source-shape probes.
