# Path-Template Pair Campaign

Phase B focuses on the path-template constructors that share the same broad
source shape but are still parked in the 12-40% band.

Current board checkpoint from `tools/match/STATUS.md`:

| target | score | notes |
|---|---:|---|
| `initialize_kind42_path_template_pair` | 37.04% | Best non-cage anchor; uses exact `allocate_path_template_samples` and exact `compute_kind42_attachment_transform`. |
| `initialize_loopout_path_template_pair` | 37.52% | Same large strip-mesh skeleton; recovered six-argument ABI and native `ret 0x18`. |
| `initialize_looptheloop_path_template_pair` | 35.74% | Loop-family macro scratch; recovered six-argument ABI and native `ret 0x18`. |
| `initialize_looptheloopw_path_template_pair` | 28.11% | Loop-family sibling with roll term; recovered six-argument ABI and native `ret 0x18`. |
| `initialize_dip_path_template_pair` | 30.19% | Shared ABI cleanup; recovered six-argument callsite and native `ret 0x18`. |
| `initialize_dump_path_template_pair` | 19.05% | Hump twin, inverted vertical lane; recovered seven-argument ABI and native `ret 0x1c`. |
| `initialize_hump_path_template_pair` | 18.99% | Worst front-half family target; recovered seven-argument ABI and native `ret 0x1c`. |
| `initialize_screw_path_template_pair` | 18.95% | Low tail target; recovered six-argument ABI and native `ret 0x18` cleanup. |
| `initialize_slalom_path_template_pair` | 20.97% | Orientation helper now always dispatches `rotate_matrix_world_z`; lead-out bound spelling matches the native header. |
| `initialize_slalombig_path_template_pair` | 20.44% | Same two-temporary falloff split as slalom, with native lead-out bound spelling and the wider `4.4444447f` scale. |
| `initialize_slalomdouble_path_template_pair` | 23.14% | Orientation helper now always dispatches `rotate_matrix_world_z`; fixed-sample initializer reloads X and delays Z conversion. |
| `initialize_twister_path_template_pair` | 15.27% | Primary sample setup now omits the unused `lateral_source` store and follows native scalar store order. |
| `initialize_twister2_path_template_pair` | 15.27% | Twister twin; same retained sample-scalar cleanup as twister. |
| `initialize_start_path_template_pair` | 16.96% | Low tail target; allocation count, sample X reloads, and in-helper Z conversion now expose a real prefix. |
| `initialize_supertramp_path_template_pair` | 16.59% | Arc sample schedule now initializes both lanes before either orientation pass; flat lead-in keeps Z conversion inside the helper. |
| `initialize_p_path_template_pair` | 19.26% | Low tail target; endpoint index/count spelling, radius lifetime, and in-helper Z conversion now match the native setup better. |
| `initialize_turnunder_path_template_pair` | 20.96% | Low tail target; delayed turn conversion and straight primary/secondary seed loops now match the native setup better. |
| `initialize_wibble_path_template_pair` | 22.72% | Fixed-sample helper/copy cleanup removes scratch-only `lateral_source` traffic; interior samples now keep transform X at zero. |
| `initialize_invert_path_template_pair` | 23.82% | Invert sibling; interior samples now keep transform X at zero and clear the focused masked audit. |
| `initialize_turnover_path_template_pair` | 23.36% | Seed helper now reloads secondary X from the written primary center field. |
| `initialize_toad_path_template_pair` | 19.40% | Split turn-angle arithmetic to preserve native `0.5f` multiply before turn sign/quarter-turn scaling. |
| `initialize_hill_valley_path_template_pair` | 14.65% | Primary sample setup now omits the unused `lateral_source` store and follows native scalar store order. |
| `initialize_sbend_path_template_pair` | 22.59% | Helper/copy cleanup removes scratch-only `lateral_source` traffic and follows native scalar store order. |
| `initialize_snake_path_template_pair` | 14.53% | Delayed the width-derived `right` local and moved Z conversion into the seed helper. |
| `initialize_sweep_path_template_pair` | 14.30% | Delayed the width-derived `right` local until after the left lead-in seed loop. |

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

Second retained probe: spelling the exit-sample loop with a separate byte
offset and logical exit counter moved `kind42` from 36.22% to 37.04%
(`668` candidate insns to `659`). The masked audit keeps the same single
relocation mismatch but drops from `46 ok` to `45 ok`, so the remaining
call-audit debt is still explicit.

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

The same callsite/tail audit used on the loop-family constructors also applies
to `hump` and `dump`: focused tail dumps show native `ret 0x1c`, while the
scratches still compiled as five-argument `ret 0x14` members. Making the unused
`side_exit` and `cap_texture` arguments explicit moved `hump` from 18.83% to
18.99% (`600/685`, `22 ok / 4 mismatch`) and `dump` from 18.90% to 19.05%
(`601/690`, `23 ok / 4 mismatch`).

A dump/hump curve-count scheduling probe was rejected: delaying the
`curve_source * 4.0f` integer conversion until after header writes, even with
`kind` before the conversion and `width_or_scale` after it, regressed `hump` to
16.65% and `dump` to 16.58% while reducing masked operand matches to 18.

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

For `hill_valley` and the twister twins, the retained sample-scalar cleanup
removes the scratch-only `lateral_source` zero store and orders scalar setup as
`rotation_scalar_98`, `rotation_scalar_94`, `special_scalar`, `lateral_scale`.
Focused Wibo moved `hill_valley` from 14.62% to 14.65% (`563/668` to
`561/668`, masked operands unchanged at `27 ok / 2 mismatch`) and each twister
twin from 15.25% to 15.27% (`556/677` to `554/677`, masked operands unchanged
at `30 ok / 0 mismatch`). A twister endpoint-handedness helper was rejected
because it regressed to 15.00% and reintroduced two masked call mismatches.
The `wibble`/`invert` interior-X spelling was also rejected for both twister
twins: forcing transform `position.x` to `0.0f` regressed each focused Wibo
score from 15.27% to 14.16% (`554/677` to `552/677`) and reintroduced four
masked operand mismatches.

For `start`, the retained slice spells the allocation count as
`curve_segments + 15`, writes `segment_count` from that local plus one, and
reloads both primary and secondary sample X from the primary `center_x` field.
Focused Wibo moved from 14.56% to 15.86% (`530/610` to `525/610`) and exposed a
7-instruction prefix. An explicit count-of-11 tail loop was rejected because it
reduced the score to 15.63% and worsened the masked operand audit.

The next `start` slice keeps the pair helper's Z input as an integer sample
index and performs the int-to-float conversion inside the inlined helper after
primary identity. Focused Wibo moved from 15.86% to 16.96% (`525/610` to
`522/610`), with the same 7-instruction prefix and masked operands improving
from `19 ok / 2 mismatch` to `21 ok / 2 mismatch`.

For `sweep` and `snake`, the retained slice applies the same primary-center X
reload to both sample arrays. Focused Wibo moved `sweep` from 13.71% to 13.88%
and `snake` from 13.74% to 13.98%. The earlier `sweep` loop-split probe was
left out because it worsened the masked audit despite a tiny score increase.

The next retained sweep/snake slice delays the width-derived `right` local until
after the lead-in seed samples that do not need it. Focused Wibo moved `sweep`
from 13.88% to 14.30% (`544/652` to `537/652`, masked operands `24 ok / 1
mismatch` to `26 ok / 1 mismatch`) and `snake` from 13.98% to 14.49%
(`535/652` unchanged, masked operands `23 ok / 4 mismatch` to `25 ok / 4
mismatch`).

For `snake`, retaining the sample helper's Z input as an integer index and
performing the int-to-float conversion inside the inlined helper after primary
identity moved focused Wibo from 14.49% to 14.53% (`535/652` to `532/652`,
masked operands unchanged at `25 ok / 4 mismatch`). The same spelling was
rejected for `sweep` because it regressed to 14.17% and worsened the masked
audit to `22 ok / 4 mismatch`.

For `turnunder`, the retained slice delays the `turns * 2pi` to integer
conversion until after the first header stores, splits the straight lead-in and
exit seed samples into separate primary/secondary identity initializers, sets
their `delta_length`, and reloads the nonlinear interpolation endpoints from the
seeded primary centers. Focused Wibo moved from 14.79% to 20.96% (`598/687` to
`582/687`, masked operands `13 ok / 7 mismatch` to `22 ok / 5 mismatch`).
Swapping the start/end center expressions and precomputing an explicit
`interior_count_f` radius were both rejected because they reduced the focused
score.

For `turnover`, the retained slice narrows the straight seed helper by reloading
secondary X from the primary center field after it has been written. Focused Wibo
moved from 22.85% to 23.36% (`563/671` to `562/671`, masked operands
`28 ok / 1 mismatch` to `29 ok / 1 mismatch`). The same spelling was rejected
for `turnoverdouble` because it reduced that sibling from 23.98% to 23.68%.

For `sbend`, the retained slice keeps the native early `height * pi` x87 load but
delays the integer step conversion until after the first header stores, then
initializes each interior primary sample before writing the computed Y and Z
positions in native arithmetic order. Focused Wibo moved from 20.52% to 22.51%
(`503/579` to `505/579`, masked operands `23 ok / 4 mismatch` to
`24 ok / 1 mismatch`).

For `sbend`, `wibble`, and `invert`, the retained helper/copy scalar cleanup
removes scratch-only `lateral_source` traffic and orders scalar stores/copies as
`rotation_scalar_98`, `rotation_scalar_94`, `special_scalar`, `lateral_scale`.
Focused Wibo moved `sbend` from 22.51% to 22.59% (`505/579` to `501/579`,
masked operands unchanged at `24 ok / 1 mismatch`), `wibble` from 22.54% to
22.70% (`510/608` to `502/608`, masked operands unchanged at `20 ok / 4
mismatch`), and `invert` from 20.20% to 22.89% (`509/600` to `501/600`, masked
operands `14 ok / 2 mismatch` to `18 ok / 2 mismatch`).

The next retained `wibble`/`invert` slice follows the decompiler-backed interior
sample shape: the interpolated lateral value belongs in `center_x`, while
transform `position.x` remains `0.0f`. Focused Wibo moved `wibble` from 22.70%
to 22.72% (`502/608` to `501/608`, masked operands unchanged at
`20 ok / 4 mismatch`) and `invert` from 22.89% to 23.82% (`501/600` to
`500/600`), clearing the invert masked audit from `18 ok / 2 mismatch` to
`21 ok / 0 mismatch`.

For `supertramp`, the retained arc schedule cleanup matches the native order
that initializes both primary and secondary arc sample positions before
orienting either sample. Focused Wibo moved from 15.61% to 16.20% (`473/552`
unchanged), shrank the candidate stack frame from `0x48` to `0x44`, and improved
masked operands from `23 ok / 4 mismatch` to `25 ok / 2 mismatch`.

The next `supertramp` slice keeps the flat lead-in helper's Z input as an
integer sample index and performs the int-to-float conversion inside the inlined
helper after primary identity. Focused Wibo moved from 16.20% to 16.59%
(`473/552` unchanged), with masked operands unchanged at `25 ok / 2 mismatch`.

For `toad`, the retained slice splits the turn-angle expression so the native
`0.5f` multiply remains separate from the turn sign and quarter-turn scale.
Focused Wibo moved from 19.25% to 19.40% (`594/663` to `595/663`, masked
operands `16 ok / 3 mismatch` to `18 ok / 2 mismatch`). A neutral-sample
writeback probe was rejected because it reduced the focused score to 19.26%.

For `p`, the retained slice materializes the endpoint `last_index` and
`sample_count` locals before allocation and keeps the radius sign check on a
temporary before storing the float radius. Focused Wibo moved from 18.55% to
19.22% (`561/679` to `559/679`, masked operands unchanged at `19 ok / 6
mismatch`). Reloading sample X from `primary->center_x`, reloading secondary Y
from the primary transform, and branching through `kind - 0x21` were rejected
because they reduced the focused score.

The next `p` slice keeps the pair helper's Z input as an integer sample index
and performs the int-to-float conversion inside the inlined helper after primary
identity. Focused Wibo moved from 19.22% to 19.26% (`559/679` to `557/679`),
with masked operands unchanged at `19 ok / 6 mismatch`.

For `screw`, the retained slice fixes the stale four-argument scratch prototype.
The recovered constructor callsite passes six stack arguments and the target tail
cleans up `0x18` bytes; the unused mode/cap arguments are now explicit in both
the scratch and shared declaration. Focused Wibo moved from 18.80% to 18.95%
(`613/685` unchanged, masked operands unchanged at `19 ok / 4 mismatch`).

The same callsite/tail audit applies to `dip` and `slalom`, which were still on
stale four-argument prototypes despite native six-argument calls. Making the
unused mode/cap arguments explicit moved `dip` from 30.02% to 30.19% (`564/655`
unchanged, `30 ok / 1 mismatch`) and `slalom` from 19.22% to 19.37% (`615/696`
unchanged, `19 ok / 3 mismatch`).

For `slalom`, the retained lead-out bound spelling follows the same native
header idiom as `slalombig`: keep `lead_out_start = curve_count + 4`, then
derive `total_segments` from that local. Focused Wibo moved from 20.84% to
20.97% (`619/696` to `620/696`, masked operands unchanged at
`24 ok / 1 mismatch`).

For `slalombig`, the retained lead-out bound spelling materializes
`lead_out_start = curve_segments + 4` and derives `total_segments` from that
local, matching the native header calculation. Focused Wibo moved from 20.39%
to 20.44% (`589/696` to `586/696`, masked operands unchanged at
`23 ok / 2 mismatch`).

For `slalomdouble`, the retained fixed-sample initializer spelling reloads
primary and secondary X from the stored primary `center_x`, then delays the
integer-to-float Z conversion until inside the inlined initializer after primary
identity. Focused Wibo moved from 22.84% to 23.14% (`578/683` to `570/683`);
the masked audit keeps one call mismatch but drops from `32 ok` to `31 ok`.
The analogous fixed lead-out local (`66`, then `+ 4`) was rejected because it
regressed to 22.61% and added a second masked mismatch.

The loop-family callsite/tail audit applies to `loopout`, `looptheloop`, and
`looptheloopw` as well: focused diffs showed native `ret 0x18` tails while the
scratches still compiled as four-argument `ret 0x10` members. The retained ABI
cleanup moved `loopout` from 37.37% to 37.52% (`636/718`, `41 ok / 1 mismatch`),
`looptheloop` from 35.59% to 35.74% (`639/721`, `39 ok / 0 mismatch`), and
`looptheloopw` from 27.96% to 28.11% (`664/745`, `21 ok / 1 mismatch`).
