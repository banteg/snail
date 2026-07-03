# Path-Template Pair Campaign

Phase B focuses on the path-template constructors that share the same broad
source shape but are still parked in the 12-40% band.

Current board checkpoint from `tools/match/STATUS.md`:

| target | score | notes |
|---|---:|---|
| `initialize_kind42_path_template_pair` | 37.34% | Best non-cage anchor; exact transform helper, exact sample allocation, and native mesh request order now clear the focused masked audit. |
| `initialize_loopout_path_template_pair` | 37.52% | Same large strip-mesh skeleton; recovered six-argument ABI and native `ret 0x18`. |
| `initialize_looptheloop_path_template_pair` | 35.74% | Loop-family macro scratch; recovered six-argument ABI and native `ret 0x18`. |
| `initialize_looptheloopw_path_template_pair` | 28.11% | Loop-family sibling with roll term; recovered six-argument ABI and native `ret 0x18`. |
| `initialize_dip_path_template_pair` | 30.19% | Shared ABI cleanup; recovered six-argument callsite and native `ret 0x18`; prologue now preserves native curve-count conversion order. |
| `initialize_dump_path_template_pair` | 29.78% | Hump twin, inverted vertical lane; middle loop now uses native byte-offset ownership and keeps the focused masked audit clean. |
| `initialize_hump_path_template_pair` | 30.38% | Worst front-half family target; middle loop now uses native byte-offset ownership and keeps the focused masked audit clean. |
| `initialize_screw_path_template_pair` | 30.95% | Screw-specific seed/middle loops now follow native sample setup lifetime and clear the masked audit. |
| `initialize_slalom_path_template_pair` | 27.36% | Curved-body orientation now builds both fixed-up frames before either roll call; lead-out bound spelling matches the native header; fixed lead-in/lead-out sample loops are expanded; mesh request-order probe was neutral. |
| `initialize_slalombig_path_template_pair` | 21.76% | Same two-temporary falloff split as slalom, with native lead-out bound spelling, the wider `4.4444447f` scale, the retained two-iteration facequad loop, and lead-in fixed samples expanded; mesh request-order and slalom orientation-split transfers regressed. |
| `initialize_slalomdouble_path_template_pair` | 26.92% | Orientation helper now always dispatches `rotate_matrix_world_z`; fixed-sample initializer reloads X, delays Z conversion, and now uses the retained two-iteration facequad loop with a masked-audit caveat; slalom orientation-split transfer regressed. |
| `initialize_twister_path_template_pair` | 21.67% | Interior primary sample order now avoids scratch-only zero Y/Z writes; constant-reference residuals remain explicit; mesh request-order probe regressed. |
| `initialize_twister2_path_template_pair` | 21.67% | Twister twin; same retained interior primary sample order and masked-audit caveat as twister; mesh request-order probe regressed. |
| `initialize_start_path_template_pair` | 21.65% | Low tail target; direct sample loops, retained face loop, staged mesh vertices, facequads-first mesh allocation, and the retested count-of-11 flat-tail loop improve fuzzy score, with the lost prefix/frame debt called out. |
| `initialize_supertramp_path_template_pair` | 18.66% | Arc sample schedule now initializes both lanes before either orientation pass; flat lead-in keeps Z conversion inside the helper; allocation count now uses the native last-index local; mesh vertices stage through a local `Vector3`; mesh allocation is facequads-first. |
| `initialize_p_path_template_pair` | 19.40% | Low tail target; endpoint index/count spelling, radius lifetime, in-helper Z conversion, and curved-body orientation expansion now match the native setup better; endpoint expansion, mesh-vertex staging, and zero-based loop-counter spelling are rejected for now. |
| `initialize_turnunder_path_template_pair` | 27.22% | Low tail target; delayed turn conversion, straight primary/secondary seed loops, retained two-iteration facequad loop, and native-style interior angle/trig/orientation scheduling improve the focused matcher. The prologue-radius lifetime retest cleared the masked audit but lowered focused Wibo, so the retained scratch keeps one constant-lifetime mismatch. |
| `initialize_wibble_path_template_pair` | 29.95% | Interior roll schedule and the retained two-iteration facequad loop now both clear the focused masked audit. |
| `initialize_invert_path_template_pair` | 29.37% | Invert sibling; interior-X cleanup and the retained two-iteration facequad loop now clear the focused masked audit. |
| `initialize_turnover_path_template_pair` | 26.85% | Seed helper now reloads secondary X from the written primary center field, and the retained two-iteration facequad loop improves the focused matcher. |
| `initialize_turnoverdouble_path_template_pair` | 27.60% | Turnover sibling; the retained two-iteration facequad loop improves the focused matcher while the seed-X reload remains rejected. |
| `initialize_toad_path_template_pair` | 25.97% | Selector ABI and sample-scalar cleanup now pair with the retained two-iteration facequad loop. |
| `initialize_hill_valley_path_template_pair` | 21.53% | Native phase counter plus the two-iteration facequad loop lift the fuzzy score; mesh request-order remains vertices-first after a neutral rejected probe. |
| `initialize_sbend_path_template_pair` | 23.33% | Mesh setup now requests facequads before vertices, clearing the focused masked audit. |
| `initialize_snake_path_template_pair` | 22.15% | Same retained facequad inner-loop skeleton as sweep; neutral half-angle cleanup is retained; curved-body orientation scheduling now leaves only the mesh allocation call pairing; mesh-vertex staging is rejected; mesh request-order retest stayed neutral after orientation expansion. |
| `initialize_sweep_path_template_pair` | 25.04% | Facequad emission now uses the native two-iteration inner-loop skeleton; the snake orientation-scheduling expansion regressed. |

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

Third retained probe: `kind42` requests strip-mesh facequads before vertices,
unlike the current shared helper default. Focused Wibo moved from 37.04% to
37.34% (`659/707` unchanged) and cleared the focused masked audit from
`45 ok / 1 mismatch` to `46 ok / 0 mismatch`. This order is not automatically
portable: `p` and `hill_valley` rejected or neutralized adjacent allocation
order probes, so only back-propagate it where focused evidence agrees.

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
Retesting the same prologue ordering after the later direct-loop and vertical
cleanup slices still regressed (`hump` 20.49% to 20.02%, `dump` 19.94% to
19.31%) and reintroduced the mesh allocation call pairing, so this campaign
keeps the early conversion despite the decompiler's native-looking schedule.

The next retained dump/hump slice expands the fixed seed loops and curved middle
loop instead of routing through the generic sample-pair helper. This keeps Z
conversion after primary identity and spells the curved center/height cosine
order from the decompilers, reducing the masked audit to a single half-angle
constant mismatch. Focused Wibo moved `hump` from 18.99% to 19.53%
(`600/685` to `605/685`, masked operands `22 ok / 4 mismatch` to
`28 ok / 1 mismatch`) and `dump` from 19.05% to 19.43% (`601/690` to
`607/690`, masked operands `23 ok / 4 mismatch` to `28 ok / 1 mismatch`).
The later inline half-angle cleanup spells the same center expression as
`cosine(angle * 0.5f)` instead of a `half_angle` local. It is score-neutral for
both twins and leaves the single masked mismatch unchanged, so it is recorded as
source-shape cleanup only.
A hump/dump mesh request-order probe was rejected: swapping the local
strip-mesh calls to facequads-before-vertices regressed `hump` from 19.53% to
18.60% and `dump` from 19.43% to 18.50%, with both masked audits dropping from
`28 ok / 1 mismatch` to `27 ok / 1 mismatch`. The remaining mismatch stayed the
half-angle constant pairing, so the twins keep the shared vertices-first order.

The next retained dump/hump slice narrows only the departure seed loop to direct
indexed `primary_samples[sample_index]` / `secondary_samples[sample_index]`
writes. Focused Wibo moved `hump` from 19.53% to 20.49% (`605/685` to
`613/685`, masked operands `28 ok / 1 mismatch` to `33 ok / 0 mismatch`) and
`dump` from 19.43% to 19.77% (`607/690` to `615/690`, masked operands
`28 ok / 1 mismatch` to `29 ok / 0 mismatch`). Applying the indexed spelling to
both fixed seed loops regressed `hump` to 18.02%, and the first fixed seed loop
alone regressed to 19.38%, so the approach loop remains pointer-local.

The follow-up vertical-sign cleanup specializes the curved Y expressions to the
decompiler spelling instead of carrying a shared `vertical_sign` local. This is
score-neutral for `hump` at 20.49% (`613/685`, `33 ok / 0 mismatch`) and moves
`dump` from 19.77% to 19.94% (`615/690` to `614/690`, `29 ok / 0 mismatch`).
The remaining dump/hump front-line residual is still the native `0x4c` frame
against the candidate `0x44` frame, not an operand-audit mismatch.

A local `Vector3 generated_position` mesh-vertex staging probe was rejected for
both twins: `hump` regressed from 20.49% to 20.31% (`613/685` to `625/685`) and
`dump` regressed from 19.94% to 19.76% (`614/690` to `626/690`). Both masked
audits stayed clean, so this is frame/local-shape debt and the vertex loop keeps
direct component writes.

The retained dump/hump middle-loop byte-offset slice applies the kind42-style
local-ownership lesson inside the curved sample loop, but not the rejected mesh
vertex loop. Spelling the curved primary/secondary sample pointers and the
orientation guard through `sample_offset` moves `hump` from 20.49% to 30.38%
(`613/685` to `612/685`, masked `33 ok / 0 mismatch` to `38 ok / 0 mismatch`)
and `dump` from 19.94% to 29.78% (`614/690` to `613/690`, masked
`29 ok / 0 mismatch` to `34 ok / 0 mismatch`).

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

The next twister-family slice keeps the final endpoint's width-derived center
recompute inline instead of reusing the first endpoint local or extracting the
rejected handedness helper. Focused Wibo moved both twins from 15.27% to 15.66%
(`554/677` to `562/677`), with masked operands unchanged at
`30 ok / 0 mismatch`.

The retained twister mesh-face slice applies the same native two-iteration
`face_index` facequad loop proven by `sweep`/`snake`. Focused Wibo moved both
twins from 15.66% to 21.58% (`562/677` to `574/677`). This is a source-shape
and fuzzy-score win, not a masked-audit cleanup: masked operands move from
`30 ok / 0 mismatch` to `33 ok / 3 mismatch`, with the new pairings all in
constant references exposed by the shifted alignment.

The next retained twister slice expands the interior primary sample setup so it
does not zero-write Y/Z before the final sine-derived values. It also follows
the native order of X write, `sine(angle)`, local counter increment, then final
Y/Z stores. Focused Wibo moved both twins from 21.58% to 21.67% (`574/677` to
`569/677`), with the same `33 ok / 3 mismatch` constant-reference audit.
The `snake`/dump/hump half-angle cleanup does not transfer here yet: removing
the `half_angle` local regressed both twister twins to 21.40% (`566/677`) while
leaving the masked audit unchanged, so the current twister loop shape keeps the
local.
A follow-up middle-loop byte-offset probe also stays rejected for both twister
twins: it cleared the focused masked audit (`33 ok / 3 mismatch` to
`36 ok / 0 mismatch`) but regressed focused Wibo to 21.42% (`574/677`). The
stronger direct primary/secondary pointer helper variant regressed further to
20.10% (`567/677`) and reintroduced a `cross_vectors` / `normalize_vector`
masked call mismatch, so the twister twins keep the indexed loop while the
score ratchet is the campaign gate.

A twister-family mesh request-order probe was rejected for both twins: swapping
strip-mesh requests to facequads-before-vertices regressed each focused Wibo
from 21.67% to 20.87% (`569/677` unchanged) and worsened the masked audit from
`33 ok / 3 mismatch` to `31 ok / 5 mismatch`, adding explicit allocation call
pairings. The twister helper keeps vertices-before-facequads order.

The next `hill_valley` slice keeps the length-to-steps conversion ahead of
`width_or_scale`, materializes `last = steps + 1` before allocation, and reloads
primary transform X from `center_x` inside the sample helper. Focused Wibo moved
from 14.65% to 14.67% (`561/668` to `559/668`), with masked operands unchanged
at `27 ok / 2 mismatch`. A direct sample-0 centered/non-centered branch rewrite
was rejected because it regressed to 14.63% (`562/668`).

The retained `hill_valley` loop-counter slice spells the hill loop with the
native zero-based phase counter and pre-incremented Z counter, then retries the
last-endpoint center recompute in that improved loop shape. Focused Wibo moved
from 14.67% to 18.00% (`559/668` to `565/668`). This is a fuzzy-score and
source-shape improvement, not a masked-audit cleanup: masked operands move from
`27 ok / 2 mismatch` to `26 ok / 4 mismatch`, with two added orientation
identity-vs-normalize pairings still called out as residual alignment drift.

The next retained `hill_valley` mesh-face slice applies the same native
two-iteration `face_index` loop proven by `sweep`/`snake`/`twister`. Focused
Wibo moved from 18.00% to 21.53% (`565/668` to `577/668`) and improved the
masked audit from `26 ok / 4 mismatch` to `28 ok / 4 mismatch`. The same
orientation and mesh-allocation residuals remain explicit.

Two tempting `hill_valley` loop-body cleanups are rejected for now. Fully
expanding the interior hill loop in decompiler order clears the phase/orientation
call residuals but regresses focused Wibo to 19.22% (`560/668`), and narrowing
only the loop center source to `primary_samples[0].center_x` regresses to
19.94% (`576/668`) despite reducing the masked audit to two mismatches. The
helper-routed loop remains the better Phase B fuzzy-alignment baseline.

A `hill_valley` mesh request-order probe was also rejected: swapping to
facequads-before-vertices stayed neutral at 21.53% (`577/668`) and only flipped
the remaining allocation mismatch from target vertices vs candidate facequads to
target facequads vs candidate vertices. Masked operands stayed at
`28 ok / 4 mismatch`, so this target keeps vertices-before-facequads order.

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
An explicit `raised_y = radius + radius` lead-in local was rejected because it
regressed focused Wibo to 16.95% (`523/610`) by forcing a store/reload before
the secondary offset add.

The next `start` slice expands all three sample loops instead of routing through
the generic pair helper. The retained source follows the native direct setup:
the lead-in keeps the doubled radius expression live, the flat tail copies
secondary Z from the written primary transform, and the curved body stores Z
before computing cosine-derived Y while deriving secondary Y from the written
primary Y. Focused Wibo moved from 16.96% to 17.31% (`522/610` to `511/610`),
with the 7-instruction prefix preserved and masked operands improving from
`21 ok / 2 mismatch` to `22 ok / 2 mismatch`.
Retesting the `start` raised-Y local after direct sample-loop expansion was
rejected again: it regressed focused Wibo from 17.31% to 17.02% (`511/610` to
`518/610`) while leaving the prefix and masked audit unchanged.

The retained `start` mesh-face slice uses a target-specific two-iteration
`face_index` loop: both faces keep the same texture, while the second face keeps
the native `flags = 4` spelling. Focused Wibo moved from 17.31% to 18.04%
(`511/610` to `521/610`) and improved the masked audit from `22 ok / 2
mismatch` to `24 ok / 2 mismatch`. This is not a clean prefix/prologue win:
the 7-instruction prefix disappears and the candidate stack frame grows from
the native `0x44` to `0x48`, so those debts remain explicit.
A `start` flat-tail bound probe was rejected: using `last_segment_index` as the
upper bound instead of spelling `curve_segments + 15` regressed focused Wibo
from 18.04% to 17.88% (`521/610` to `520/610`) with the masked audit unchanged
at `24 ok / 2 mismatch`, so the direct bound stays retained.
Retesting direct array-index writes in the `start` lead-in loop was rejected:
removing the primary/secondary sample pointer locals regressed focused Wibo from
18.04% to 17.79% (`521/610` to `537/610`) with the same `24 ok / 2 mismatch`
masked audit.
The next retained `start` mesh-vertex slice stages each generated vertex
through a local `Vector3` before assigning it to the vertex array, matching the
native stack-spill shape in the vertex row loop. Focused Wibo moved from 18.04%
to 20.56% (`521/610` to `528/610`) and improved the masked audit from
`24 ok / 2 mismatch` to `26 ok / 2 mismatch`. The prefix/frame debt remains:
the candidate still starts at a `0x48` frame against native `0x44`.
A curved-loop byte-offset probe was rejected for `start`: replacing the curved
body's indexed sample pointers with explicit byte-offset ownership regressed
focused Wibo to 18.72% (`533/610`) and reduced the masked audit to
`22 ok / 2 mismatch`, so the current `start` body keeps indexed pointers.
Retesting the explicit count-of-11 flat-tail loop after mesh-vertex staging and
the extra-row request-order cleanup is now retained: focused Wibo moves from
21.27% to 21.65% (`528/610` to `526/610`), with masked operands unchanged at
`27 ok / 1 mismatch`. The candidate frame is still `0x48` versus native `0x44`,
so this is a loop-shape win, not a prefix/prologue fix.

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

For `sweep`, the retained direct sample-loop expansion follows the decompiler
shape for the three lead-in samples, three lead-out samples, and curved body.
The lead-in/tail loops keep the index float conversion after primary identity,
the curved body reloads the seeded primary `center_x`, and secondary Y derives
from the written primary Y. Focused Wibo moved from 14.30% to 14.85%
(`537/652` to `533/652`), with masked operands improving from `26 ok / 1
mismatch` to `27 ok / 1 mismatch`.
The later `start`/`supertramp` mesh-vertex staging pattern was rejected here:
it cleared sweep's masked audit but regressed focused Wibo from 25.04% to
17.26% (`546/652` to `553/652`), so the sweep vertex loop keeps direct
component stores.

A sweep/snake curved-counter spelling was rejected: using a separate zero-based
logical counter for angle/Z, like the decompiler, regressed `sweep` from 14.85%
to 14.81% (`533/652` to `536/652`) and `snake` from 15.50% to 15.46%
(`535/652` to `538/652`), with masked audits unchanged.

For `snake`, retaining the sample helper's Z input as an integer index and
performing the int-to-float conversion inside the inlined helper after primary
identity moved focused Wibo from 14.49% to 14.53% (`535/652` to `532/652`,
masked operands unchanged at `25 ok / 4 mismatch`). The same spelling was
rejected for `sweep` because it regressed to 14.17% and worsened the masked
audit to `22 ok / 4 mismatch`.

A `snake` orientation-bound probe was rejected: extending the identity branch
from `current_index <= first_index` to `current_index <= first_index + 1` left
focused Wibo and the masked audit unchanged at 14.53% (`532/652`) and
`25 ok / 4 mismatch`, so the apparent identity-vs-normalize pairings remain
documented alignment drift.

For `snake`, the retained curved-body expansion follows the same decompiler
shape as the direct sample-setup slices: center reloads the seeded right-side
sample, primary Y is computed after primary identity, and secondary Y recomputes
the cosine-derived height after secondary identity. Focused Wibo moved from
14.53% to 15.50% (`532/652` to `535/652`), with masked operands improving from
`25 ok / 4 mismatch` to `29 ok / 3 mismatch`. Retesting the orientation-bound
probe after this expansion stayed neutral, so that branch remains unchanged.
Expanding the remaining snake lead-in and lead-out helper calls was rejected
because it regressed focused Wibo to 15.41% (`542/652`) without improving the
masked audit.
A `snake` mesh request-order probe matched the earlier `sweep` rejection:
swapping to facequads-before-vertices stayed neutral at 15.50% (`535/652`) with
`29 ok / 3 mismatch`, only flipping the remaining mesh call mismatch.

For `sweep` and `snake`, the retained mesh-face slice replaces the straight
`a`/`b` facequad writes with the native two-iteration `face_index` loop and a
single `face->uv[3].v` tail store. Focused Wibo moved `sweep` from 14.85% to
25.04% (`533/652` to `546/652`, masked operands `27 ok / 1 mismatch` to
`32 ok / 1 mismatch`) and `snake` from 15.50% to 21.33% (`535/652` to
`548/652`, masked operands `29 ok / 3 mismatch` to `33 ok / 3 mismatch`).
The remaining mesh call mismatch is still an alignment pairing, so the retained
request order stays vertices-before-facequads.
The `p`/`snake` orientation scheduling expansion does not transfer back to
`sweep`: expanding both lane orientations inline regressed focused Wibo from
25.04% to 20.02% (`546/652` to `547/652`) and reduced masked operands from
`32 ok / 1 mismatch` to `29 ok / 1 mismatch`, so the compact helper calls stay.
For `snake`, the follow-up half-angle cleanup removes the scratch-only
`half_angle` local and spells the curved-body center as `cosine(angle * 0.5f)`.
This is neutral at 21.33% (`548/652`) with the masked audit still at
`33 ok / 3 mismatch`, so it is retained as source-shape cleanup only.
The retained `snake` orientation scheduling expansion follows the successful
`p` shape: keep the first curved sample identity branch paired across both lanes,
then build both right-vector orientation frames inline. Focused Wibo moved from
21.33% to 22.15% (`548/652` to `549/652`), and masked operands improved from
`33 ok / 3 mismatch` to `35 ok / 1 mismatch`; the remaining mismatch is only
the mesh allocation call pairing.
A post-orientation `snake` mesh request-order retest was rejected: swapping to
facequads-before-vertices stayed neutral at 22.15% (`549/652`) with masked
operands unchanged at `35 ok / 1 mismatch`, only flipping the single allocation
pairing from target vertices vs candidate facequads to target facequads vs
candidate vertices.
A `snake` mesh-vertex staging probe was rejected: routing each row vertex
through a local `Vector3 generated_position`, as retained by `start` and
`supertramp`, regressed focused Wibo from 21.33% to 20.55% (`548/652` to
`555/652`) and reduced the masked audit from `33 ok / 3 mismatch` to
`31 ok / 3 mismatch`. This target keeps direct component stores like `sweep`.

For `turnunder`, the retained slice delays the `turns * 2pi` to integer
conversion until after the first header stores, splits the straight lead-in and
exit seed samples into separate primary/secondary identity initializers, sets
their `delta_length`, and reloads the nonlinear interpolation endpoints from the
seeded primary centers. Focused Wibo moved from 14.79% to 20.96% (`598/687` to
`582/687`, masked operands `13 ok / 7 mismatch` to `22 ok / 5 mismatch`).
Swapping the start/end center expressions and precomputing an explicit
`interior_count_f` radius were both rejected because they reduced the focused
score.

The retained `turnunder` mesh-face slice applies the same two-texture
`face_index` loop. Focused Wibo moved from 20.96% to 23.92% (`582/687` to
`592/687`) and improved the masked audit from `22 ok / 5 mismatch` to
`24 ok / 5 mismatch`. The remaining residuals are still in the turn
angle/interior orientation schedule.

The retained `turnunder` interior-loop slice switches the body to the recovered
negative one-turn angle, computes the count-derived radius, orders the
half-angle/full-angle/Y/roll trig calls like the native loop, and builds
`basis_forward`/`basis_right` before copying the secondary sample. Focused Wibo
improves from 23.92% to 27.22% (`592/687` to `628/687`), with masked operands
moving from `24 ok / 5 mismatch` to `38 ok / 1 mismatch`. Retesting the
prologue-radius lifetime cleared the masked audit (`37 ok / 0 mismatch`) but
reduced focused Wibo to 26.62%, so it remains rejected for now.

For `turnover`, the retained slice narrows the straight seed helper by reloading
secondary X from the primary center field after it has been written. Focused Wibo
moved from 22.85% to 23.36% (`563/671` to `562/671`, masked operands
`28 ok / 1 mismatch` to `29 ok / 1 mismatch`). The same spelling was rejected
for `turnoverdouble` because it reduced that sibling from 23.98% to 23.68%.
Reordering the curved `turnover` position writes to compute Y/cosine before
X/sine was also rejected: it raised fuzzy score to 23.52% but worsened the
masked audit from `29 ok / 1 mismatch` to `28 ok / 2 mismatch`.

The retained `turnover` mesh-face slice applies the same two-texture
`face_index` loop as the other strip-mesh wins. Focused Wibo moved from 23.36%
to 26.85% (`562/671` to `573/671`), and the masked audit improved from
`29 ok / 1 mismatch` to `31 ok / 1 mismatch`. The remaining mismatch is still
the sine/cosine pairing in the curved interior.

A `turnover` curved-call materialization probe was rejected. Materializing
`sine(angle)`, `cosine(angle)`, and `sine(half)` in straight order regressed to
24.88% (`567/671`) and kept one masked mismatch; interleaving the calls as
`sine(angle)`, `cosine(angle)`, `sine(half)` cleared the masked audit to
`30 ok / 0 mismatch` but regressed fuzzy score further to 24.54% (`568/671`).

The retained `turnoverdouble` mesh-face slice follows the same helper rewrite.
Focused Wibo moved from 23.98% to 27.60% (`571/680` to `581/680`), and the
masked audit improved from `32 ok / 1 mismatch` to `34 ok / 1 mismatch`. The
same sine/cosine pairing remains as the sole masked mismatch.

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

The next retained `sbend` slice follows the focused masked audit and swaps the
two local strip-mesh allocation calls so facequads are requested before
vertices. Focused Wibo moved from 22.59% to 23.33% (`501/579` unchanged), and
the masked audit cleared from `24 ok / 1 mismatch` to `25 ok / 0 mismatch`.
Trying the same mesh-request swap for `sweep` was rejected because it stayed at
14.30% (`537/652`) and only flipped the single masked mismatch to the opposite
request call alignment.

The next retained `wibble`/`invert` slice follows the decompiler-backed interior
sample shape: the interpolated lateral value belongs in `center_x`, while
transform `position.x` remains `0.0f`. Focused Wibo moved `wibble` from 22.70%
to 22.72% (`502/608` to `501/608`, masked operands unchanged at
`20 ok / 4 mismatch`) and `invert` from 22.89% to 23.82% (`501/600` to
`500/600`), clearing the invert masked audit from `18 ok / 2 mismatch` to
`21 ok / 0 mismatch`.

The next retained `wibble` slice recomputes the native roll basis separately for
the cosine and sine up-vector components. Focused Wibo moved from 22.72% to
24.46% (`501/608` to `504/608`), clearing the masked audit from
`20 ok / 4 mismatch` to `27 ok / 0 mismatch`. Three nearby schedules were
rejected as lesser fits: folded roll after initialization at 23.86%, split turn
phase before initialization at 23.84%, and roll calls after initialization at
23.92%, each still leaving one masked mismatch.

The retained `wibble`/`invert` mesh-face slice applies the same two-texture
`face_index` loop proven by `sweep`/`snake`/twister/toad. Focused Wibo moved
`wibble` from 24.46% to 29.95% (`504/608` to `514/608`, masked operands
`27 ok / 0 mismatch` to `29 ok / 0 mismatch`) and `invert` from 23.82% to
29.37% (`500/600` to `510/600`, masked operands `21 ok / 0 mismatch` to
`23 ok / 0 mismatch`). The remaining residual is still the larger frame and
interior loop/codegen shape, not an operand-audit mismatch.

For `supertramp`, the retained arc schedule cleanup matches the native order
that initializes both primary and secondary arc sample positions before
orienting either sample. Focused Wibo moved from 15.61% to 16.20% (`473/552`
unchanged), shrank the candidate stack frame from `0x48` to `0x44`, and improved
masked operands from `23 ok / 4 mismatch` to `25 ok / 2 mismatch`.

The next `supertramp` slice keeps the flat lead-in helper's Z input as an
integer sample index and performs the int-to-float conversion inside the inlined
helper after primary identity. Focused Wibo moved from 16.20% to 16.59%
(`473/552` unchanged), with masked operands unchanged at `25 ok / 2 mismatch`.

The next `supertramp` slice materializes `last_segment_index = curve_segments +
7` before deriving `segment_count`. Focused Wibo moved from 16.59% to 16.96%
(`473/552` to `474/552`), with masked operands improving from `25 ok / 2
mismatch` to `26 ok / 1 mismatch`. Reloading flat lead-in X from the written
primary `center_x` was rejected because it regressed to 16.75% and restored the
two masked mismatches.

The next retained `supertramp` mesh-vertex slice mirrors the `start` finding:
staging each row vertex through a local `Vector3` improves the focused matcher
from 16.96% to 17.10% (`474/552` to `477/552`) while keeping the masked audit at
`26 ok / 1 mismatch`. The cap-texture facequad loop remains direct because the
earlier two-iteration `face_index` probe regressed sharply.

The retained extra-row mesh request-order slice applies to both `start` and
`supertramp`: request facequads before vertices, matching the call alignment
that survived after mesh-vertex staging. Focused Wibo moved `start` from 20.56%
to 21.27% (`528/610` unchanged), improving the masked audit from
`26 ok / 2 mismatch` to `27 ok / 1 mismatch`, and moved `supertramp` from
17.10% to 18.66% (`477/552` unchanged), improving masked operands from
`26 ok / 1 mismatch` to `27 ok / 1 mismatch`. The remaining mismatch is still a
mesh allocation call aligned against native orientation work, so this does not
claim the prologue/interior residual is solved.

Retesting the native count-of-11 flat-tail loop on top of that retained
`start` shape moves it again from 21.27% to 21.65% (`528/610` to `526/610`);
the masked audit remains `27 ok / 1 mismatch`, so the source keeps the explicit
tail counter while leaving the allocation/orientation mismatch documented.

A `supertramp` float-count lifetime probe was rejected: materializing a separate
`curve_segments_f` local for radius and angle division was exactly neutral at
16.96% (`474/552`), with masked operands unchanged at `26 ok / 1 mismatch`.
A facequad inner-loop probe was also rejected for `supertramp`: applying the
`sweep`/`snake`/twister two-iteration `face_index` skeleton to the cap-texture
mesh regressed focused Wibo from 16.96% to 10.19% (`474/552` to `488/552`) and
reduced the masked audit from `26 ok / 1 mismatch` to `7 ok / 3 mismatch`, so
that mesh keeps the direct `a`/`b` facequad writes.
A flat lead-in expansion was also neutral at 16.96% (`474/552`) with
`26 ok / 1 mismatch`, so the seven fixed lead-in samples stay helper-routed
until another source-shape lead appears.
Retesting after the retained mesh-vertex staging kept that flat lead-in
expansion neutral at 17.10% (`477/552`), and the arc-loop byte-offset ownership
probe was also neutral at 17.10% with the same `26 ok / 1 mismatch` audit.
Two arc-loop scalar probes were rejected: dropping secondary scalar-field writes
regressed to 16.49% (`467/552`, `22 ok / 2 mismatch`), and reloading arc primary
X from `center_x` regressed to 16.76% (`474/552`, `25 ok / 2 mismatch`).
After the request-order cleanup, expanding the arc orientation helper into direct
`basis_right` / `basis_up` stores was rejected: it regressed focused Wibo from
18.66% to 17.98% (`477/552` to `449/552`) and worsened the masked audit from
`27 ok / 1 mismatch` to `20 ok / 3 mismatch`.

For `toad`, the retained slice splits the turn-angle expression so the native
`0.5f` multiply remains separate from the turn sign and quarter-turn scale.
Focused Wibo moved from 19.25% to 19.40% (`594/663` to `595/663`, masked
operands `16 ok / 3 mismatch` to `18 ok / 2 mismatch`). A neutral-sample
writeback probe was rejected because it reduced the focused score to 19.26%.

The next `toad` slice narrows the branch selector from `int` to `char` in the
shared path-template declaration and scratch signature after focused head diff
showed the native byte load. Focused Wibo moved from 19.40% to 19.71%
(`595/663` unchanged), exposing a 1-instruction prefix while leaving the masked
audit unchanged at `18 ok / 2 mismatch`.

Retrying only the `toad` sample-scalar cleanup after the byte-width ABI fix is
now retained: removing scratch-only `lateral_source` traffic moves focused Wibo
from 19.71% to 19.79% (`595/663` to `590/663`), while the prefix and
`18 ok / 2 mismatch` audit remain unchanged.

Removing the remaining flat-secondary `lateral_source` copy was rejected: it
improved the masked audit to `18 ok / 1 mismatch` but regressed focused Wibo to
19.70% (`586/663`), so the retained source keeps that copy for now.

The retained `toad` mesh-face slice applies the same two-texture `face_index`
loop as `hill_valley`. Focused Wibo moved from 19.79% to 25.97% (`590/663` to
`600/663`), preserved the 1-instruction prefix, and improved the masked audit
from `18 ok / 2 mismatch` to `22 ok / 2 mismatch`. The remaining masked
pairings are still in the interior orientation/copy schedule.

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

A follow-up `p` radius compare probe was rejected: collapsing the sign check
from the double temporary to a float local made the visible compare use a dword
operand, but the focused score regressed to 19.19% (`561/679`) while masked
operands stayed at `19 ok / 6 mismatch`.
A `p` mesh request-order probe was also rejected: swapping to
facequads-before-vertices stayed neutral at 19.26% (`557/679`) and only flipped
the mesh call mismatch, leaving masked operands at `19 ok / 6 mismatch`.
Retesting after the retained orientation expansion stayed neutral at 19.40%
(`558/679`) with `19 ok / 9 mismatch`, so vertices-first order still stays
retained.
Replacing the direct `a`/`b` face writer with the shared two-iteration
`face_index` loop was rejected too: focused Wibo regressed to 18.14%
(`567/679`) and masked operands dropped to `16 ok / 6 mismatch`.
Unlike `start` and `supertramp`, staging the strip-mesh vertex calculation
through a local `Vector3` was rejected for `p`: focused Wibo regressed from
19.26% to 13.01% (`557/679` to `566/679`) and masked operands dropped from
`19 ok / 6 mismatch` to `14 ok / 5 mismatch`, so direct component writes remain
retained.

A zero-based `p` curved-body loop-counter probe was rejected: spelling the loop
with `sample_index = i + 1` regressed focused Wibo from 19.26% to 18.74%
(`557/679` to `559/679`) and reduced the masked audit from
`19 ok / 6 mismatch` to `16 ok / 6 mismatch`. The one-based loop with `(i - 1)`
angle ownership remains the better current alignment.
The retained `p` orientation scheduling expansion follows the decompiler's
inline curved-body orientation shape and keeps the first-sample identity branch
paired across both lanes. Focused Wibo moved from 19.26% to 19.40% (`557/679`
to `558/679`), but masked operands worsened from `19 ok / 6 mismatch` to
`19 ok / 9 mismatch`, so this is retained only as a source-shape/fuzzy-score
win with explicit call-pairing debt.
Retesting the decompiler-looking independent `kind == 0x21` / `0x22` / `0x23`
branches after that orientation expansion regressed focused Wibo to 19.31%
(`564/679`) with masked operands unchanged at `19 ok / 9 mismatch`, so the
current `else if` branch spelling remains retained.

For `screw`, the retained slice fixes the stale four-argument scratch prototype.
The recovered constructor callsite passes six stack arguments and the target tail
cleans up `0x18` bytes; the unused mode/cap arguments are now explicit in both
the scratch and shared declaration. Focused Wibo moved from 18.80% to 18.95%
(`613/685` unchanged, masked operands unchanged at `19 ok / 4 mismatch`).

The next retained `screw` slice expands the screw-specific three-sample entrance,
five-sample exit, and helical middle loops instead of routing them through the
generic sample-pair helper. This delays each Z conversion until after primary
identity, removes the extra helical secondary-X store, and spells the previous
sample up-vector cosine/sine temporaries in native order. Focused Wibo moved
from 18.95% to 30.95% (`613/685` to `601/685`) and the masked audit improved
from `19 ok / 4 mismatch` to `33 ok / 0 mismatch`.

The same callsite/tail audit applies to `dip` and `slalom`, which were still on
stale four-argument prototypes despite native six-argument calls. Making the
unused mode/cap arguments explicit moved `dip` from 30.02% to 30.19% (`564/655`
unchanged, `30 ok / 1 mismatch`) and `slalom` from 19.22% to 19.37% (`615/696`
unchanged, `19 ok / 3 mismatch`).

For `dip`, the retained prologue cleanup keeps the native early
`curve_source * 5.0f` x87 multiply but delays the integer curve-count conversion
until after the header kind/flag/width stores. Focused Wibo remains 30.19%
(`564/655`, masked operands unchanged at `30 ok / 1 mismatch`), so this is
recorded as source-shape alignment rather than a score win.

For `slalom`, the retained lead-out bound spelling follows the same native
header idiom as `slalombig`: keep `lead_out_start = curve_count + 4`, then
derive `total_segments` from that local. Focused Wibo moved from 20.84% to
20.97% (`619/696` to `620/696`, masked operands unchanged at
`24 ok / 1 mismatch`).

The next retained `slalom` slice expands only the four fixed lead-in and four
fixed lead-out sample loops from the generic helper. Focused Wibo moved from
20.97% to 21.46% (`620/696` to `618/696`), with the masked audit unchanged at
`24 ok / 1 mismatch`. The curved body stays helper-routed: curved-only
regressed to 20.84% with `23 ok / 1 mismatch`, and expanding all three loops
reached only 21.33% while also reducing the masked audit to `23 ok / 1
mismatch`.

A `slalom` mesh request-order probe was rejected: swapping strip-mesh requests
to facequads-before-vertices stayed neutral at 21.46% (`618/696`), with masked
operands unchanged at `24 ok / 1 mismatch` on the same `cross_vectors` vs
`rotate_matrix_world_z` orientation call pairing. The target keeps
vertices-before-facequads order.
The retained `slalom` orientation scheduling split expands just the curved-body
orientation block so the primary and secondary fixed-up frames are both built
before either frame is rolled. Focused Wibo moves from 21.46% to 27.36%
(`618/696` to `620/696`), and the masked audit improves from
`24 ok / 1 mismatch` to `28 ok / 1 mismatch`. The remaining mismatch is still
orientation call alignment, now native `normalize_vector` against candidate
`rotate_matrix_world_z`.

For `slalombig`, the retained lead-out bound spelling materializes
`lead_out_start = curve_segments + 4` and derives `total_segments` from that
local, matching the native header calculation. Focused Wibo moved from 20.39%
to 20.44% (`589/696` to `586/696`, masked operands unchanged at
`23 ok / 2 mismatch`).

The next retained `slalombig` mesh-face slice follows `slalom` and replaces the
direct `a`/`b` facequad writes with the two-iteration `face_index` loop. Focused
Wibo moved from 20.44% to 21.71% (`586/696` to `594/696`), with the masked audit
improving from `23 ok / 2 mismatch` to `25 ok / 1 mismatch`. The remaining
masked mismatch is still the interior orientation call pairing.

The follow-up `slalombig` fixed-sample slice expands only the four lead-in
samples from the generic helper. Focused Wibo moved from 21.71% to 21.76%
(`594/696` to `600/696`), with the masked audit unchanged at `25 ok / 1
mismatch`. The sibling full fixed-loop spelling does not transfer wholesale:
expanding both fixed loops regressed to 21.62%, and lead-out-only regressed to
21.22% while reducing the masked audit to `23 ok / 1 mismatch`, so the trailing
fixed samples stay helper-routed.

A `slalombig` mesh request-order probe was rejected: swapping strip-mesh
requests to facequads-before-vertices regressed focused Wibo from 21.76% to
20.99% (`600/696` unchanged) and worsened the masked audit from
`25 ok / 1 mismatch` to `23 ok / 3 mismatch`, adding explicit allocation call
pairings. This sibling also keeps vertices-before-facequads order.
The new `slalom` orientation scheduling split does not transfer to
`slalombig`: expanding both lane orientations before either roll call clears
the masked audit to `26 ok / 0 mismatch`, but regresses focused Wibo from
21.76% to 18.68% (`600/696` to `589/696`). The compact helper calls remain the
better current fuzzy baseline.

For `slalomdouble`, the retained fixed-sample initializer spelling reloads
primary and secondary X from the stored primary `center_x`, then delays the
integer-to-float Z conversion until inside the inlined initializer after primary
identity. Focused Wibo moved from 22.84% to 23.14% (`578/683` to `570/683`);
the masked audit keeps one call mismatch but drops from `32 ok` to `31 ok`.
The analogous fixed lead-out local (`66`, then `+ 4`) was rejected because it
regressed to 22.61% and added a second masked mismatch.

The retained `slalomdouble` mesh-face slice follows the same `face_index` loop
as `slalom` and `slalombig`. Focused Wibo moved from 23.14% to 26.92%
(`570/683` to `580/683`), but the masked audit changed from
`31 ok / 1 mismatch` to `32 ok / 3 mismatch`. The remaining mismatches are in
the interior orientation call pairings, so this is kept as a score/candidate
gain with explicit residual debt.
A `slalomdouble` orientation scheduling split was rejected for the same reason
as `slalombig`: expanding both lane orientations before either roll call reduced
the masked residuals to `30 ok / 1 mismatch`, but regressed focused Wibo from
26.92% to 25.08% (`580/683` to `577/683`). The helper calls stay as the current
score baseline.

The loop-family callsite/tail audit applies to `loopout`, `looptheloop`, and
`looptheloopw` as well: focused diffs showed native `ret 0x18` tails while the
scratches still compiled as four-argument `ret 0x10` members. The retained ABI
cleanup moved `loopout` from 37.37% to 37.52% (`636/718`, `41 ok / 1 mismatch`),
`looptheloop` from 35.59% to 35.74% (`639/721`, `39 ok / 0 mismatch`), and
`looptheloopw` from 27.96% to 28.11% (`664/745`, `21 ok / 1 mismatch`).
