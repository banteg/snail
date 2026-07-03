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
| `initialize_dump_path_template_pair` | 18.90% | Hump twin, inverted vertical lane; fixed-center seed calls now use native-style width/member-derived expressions. |
| `initialize_hump_path_template_pair` | 18.83% | Worst front-half family target; fixed-center seed calls now use native-style width/member-derived expressions. |
| `initialize_screw_path_template_pair` | 18.95% | Low tail target; recovered six-argument ABI and native `ret 0x18` cleanup. |
| `initialize_twister_path_template_pair` | 15.25% | Worst twin target; secondary sample writes and sine/store order now match the native call order. |
| `initialize_twister2_path_template_pair` | 15.25% | Twister twin; same source-shape cleanup as twister. |
| `initialize_start_path_template_pair` | 15.86% | Low tail target; allocation count spelling and sample X reloads now expose a real prefix. |
| `initialize_p_path_template_pair` | 19.22% | Low tail target; endpoint index/count spelling and radius lifetime now match the native setup better. |
| `initialize_turnunder_path_template_pair` | 20.96% | Low tail target; delayed turn conversion and straight primary/secondary seed loops now match the native setup better. |
| `initialize_hill_valley_path_template_pair` | 14.62% | Low tail target; loop secondary samples now recompute the cosine-derived height in native order. |
| `initialize_snake_path_template_pair` | 13.98% | Low tail target; sample X reloads now use primary center fields. |
| `initialize_sweep_path_template_pair` | 13.88% | Low tail target; same sample X reload as snake, with loop split rejected. |

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

The kind42 `vertex_index` spelling was rejected for `twister`, `twister2`,
`dump`, and `hump`: it was neutral for the twister twins and regressed the
dump/hump twins. The retained second code slice instead removes precomputed
`start_center` / `end_center` lifetime pressure from `dump` and `hump` by
spelling the fixed seed centers directly from `width_cells` and the middle
cosine center from `primary_samples[0].center_x`.

For the twister twins, the retained slice narrows secondary sample
initialization to transform-only writes, preserves the native `0.5f * 5.0f`
center scale spelling, and delays primary `y` / `z` stores until after the
identity call. That clears the focused masked operand audit for both twins
without pretending the larger loop/register residual is solved.

For `hill_valley`, the retained slice delays the length-to-steps conversion
until after the first header writes, applies the same transform-only secondary
sample rule, copies secondary X from the primary center field, delays primary
loop `y` / `z` stores until after identity, and uses a loop-specific secondary
initializer that recomputes the cosine-derived height after secondary identity.
Focused Wibo moved from 12.31% to 14.62% (`583/668` to `563/668`, masked
operands `19 ok / 3 mismatch` to `27 ok / 2 mismatch`). A last-endpoint center
recompute probe improved the mask audit to one mismatch but reduced fuzzy score
to 13.56%, so it was left out.

For `start`, the retained slice spells the allocation count as
`curve_segments + 15`, writes `segment_count` from that local plus one, and
reloads both primary and secondary sample X from the primary `center_x` field.
Focused Wibo moved from 14.56% to 15.86% (`530/610` to `525/610`) and exposed a
7-instruction prefix. An explicit count-of-11 tail loop was rejected because it
reduced the score to 15.63% and worsened the masked operand audit.

For `sweep` and `snake`, the retained slice applies the same primary-center X
reload to both sample arrays. Focused Wibo moved `sweep` from 13.71% to 13.88%
and `snake` from 13.74% to 13.98%. The earlier `sweep` loop-split probe was
left out because it worsened the masked audit despite a tiny score increase.

For `turnunder`, the retained slice delays the `turns * 2pi` to integer
conversion until after the first header stores, splits the straight lead-in and
exit seed samples into separate primary/secondary identity initializers, sets
their `delta_length`, and reloads the nonlinear interpolation endpoints from the
seeded primary centers. Focused Wibo moved from 14.79% to 20.96% (`598/687` to
`582/687`, masked operands `13 ok / 7 mismatch` to `22 ok / 5 mismatch`).
Swapping the start/end center expressions and precomputing an explicit
`interior_count_f` radius were both rejected because they reduced the focused
score.

For `p`, the retained slice materializes the endpoint `last_index` and
`sample_count` locals before allocation and keeps the radius sign check on a
temporary before storing the float radius. Focused Wibo moved from 18.55% to
19.22% (`561/679` to `559/679`, masked operands unchanged at `19 ok / 6
mismatch`). Reloading sample X from `primary->center_x`, reloading secondary Y
from the primary transform, and branching through `kind - 0x21` were rejected
because they reduced the focused score.

For `screw`, the retained slice fixes the stale four-argument scratch prototype.
The recovered constructor callsite passes six stack arguments and the target tail
cleans up `0x18` bytes; the unused mode/cap arguments are now explicit in both
the scratch and shared declaration. Focused Wibo moved from 18.80% to 18.95%
(`613/685` unchanged, masked operands unchanged at `19 ok / 4 mismatch`).
