# set_immediate_blend_mode

Immediate 2D quad blend-state helper at `0x412e50`, called by
`draw_textured_quad_immediate` for its authored `blend_mode` argument.

Recovered behavior:

- mode `0` disables alpha blending through render state `0x1b = 0`.
- modes `1, 3, 4, 7, 15` enable alpha blending with source `5`, destination `6`.
- mode `2` uses source `1`, destination `6`.
- modes `5, 8, 9, 11, 12, 13` use destination `2`, with source `5`.
- mode `6` uses source `2`, destination `2`.
- mode `14` uses source `10`, destination `6`.
- mode `10` and out-of-range modes return the input unchanged.

The native switch table lives at `0x412fe8` and has 16 entries.

Initial focused result: `85.50%`, `126/136` candidate/target instructions,
`19 ok`, `0 unresolved`, `1 mismatch`.

Source-shape notes:

- Ordering the source cases by native block layout improved the initial
  semantic scratch from `76.54%` to `85.50%`.
- The remaining mismatch is the jump table and tail-sharing ownership. Native
  keeps separate full blocks for mode `1` and mode `4`, shares the `dest=6`
  suffix for modes `2`, `14`, and `3/7/15`, and shares the `dest=2` suffix for
  modes `6` and `5/8/11/13`; the current source still lets VC6 merge mode `1`
  into the later mode `4` block and inline the mode `6` destination tail.
- Local `Direct3DDevice8* device` spellings for modes `1` and `4` compiled
  identically and did not split the merged blocks.
- An explicit `goto` from mode `6` into the destination-2 tail regressed the
  helper to `50.20%`, so the semantic return spelling stays.
- 2026-06-20 render-state family audit: a mode-1-only `source_blend = 5` local
  also compiled identically at `85.50%` and did not split the native mode 1/mode
  4 duplicate full blocks. The source stays in the simpler semantic switch form.
- 2026-06-20 larger render-state audit: a mode-1 result-overwriting local also
  compiles identically at 85.50%, so return-value lifetime is not what keeps
  native's mode-1 block distinct. Reordering the two `dest=2` case groups is
  codegen-neutral. A broader `source_blend` shared-suffix rewrite for the
  `dest=6` and `dest=2` families regresses to 70.00%, confirming that this
  helper wants duplicated full blocks rather than the `set_blend_mode` suffix
  idiom. Replacing the shared Direct3D view with a local narrow view is also
  neutral and leaves the same jump-table masked mismatch.
- 2026-06-20 render-state helper retry: focused Wibo still reports `85.50%`,
  `126/136` candidate/target instructions, `2/136` prefix, nineteen clean
  masked operands, and the expected jump-table masked mismatch. Swapping the
  source order of the duplicate `source=5,dest=6` `case 1` and `case 4` blocks
  is codegen-neutral: VC6 still emits the `source=1` shared suffix first and
  keeps only one full `source=5,dest=6` block. The exact
  `configure_sprite_render_state` helper confirms the semantic switch idiom,
  but it does not provide a transferable way to force native's duplicated
  mode-1 block without fakematching. Keep the current simple switch and leave
  the remaining debt as block-order/tail-sharing codegen.

2026-07-09 switch-shape campaign: device-local reloads on case 1, shared
`source_blend` dest=6 suffix (as in `set_blend_mode`), and if-ladder mode
dispatch all fail to recover native's fully expanded mode-1 block. Best remains
85.50% with the jump-table content mismatch.

2026-07-14 cross-port contract closure: iOS and Android export the shared
responsibility as `G0SetBlend(int)`, whose authored contract is void. Windows
splits it into this immediate-quad helper and the object-rendering variant at
`0x412d00`. The sole Windows caller is the recovered `G0RenderFont` counterpart
and discards EAX. Replacing synthetic Direct3D return forwarding with ordinary
calls plus `return;` is byte-identical: 85.50%, 126/136 instructions, nineteen
clean operands, and the existing honest jump-table mismatch.

2026-07-15 replay closure: the void ABI now replays repeatably and the refreshed
artifact resolves every state write through `g_direct3d_renderer.device`.
Case-local `break`/`return` variants and a full switch-wide return variant were
byte-neutral; the retained semantic switch stays at 85.50% with its honest
tail-sharing/jump-table residual.

## 2026-07-30 bounded mode-1 block ownership

Three recorded sweeps cover the remaining distinct native mode-1 block.
Spelling its `1/5/6` values from the known case selector, with or without
locals, compiles byte-identically. Scoped, `break`, one-iteration, and
redundant-selector-guard control forms are also neutral.

Under the current recovered Direct3D header, case-local device owners are no
longer neutral: applying them to both duplicate blocks falls to 75.25%, while
applying one side falls to 46.26-47.97% and can increase reference debt. This
current recorded evidence supersedes the older manual device-local note.

Across 12 unique variants, none improve, nine are byte-identical, and three
regress. The experiment ledger records the lane at 85.50%, 126/136
candidate/target instructions, prefix 2/136, with 20 clean references, two
target-only device loads, and the explicit nonuniform jump-table mismatch. No
selector dependency, duplicate receiver lifetime, or goto is retained solely
to defeat VC6's identical-block merge.

## 2026-09-07 complete preset grouping and ordering

The now-exact object blend helper motivated two bounded source-switch checks.
The 150-form partition recipe splits the existing equal-effect preset groups
into complete case bodies. It produces no improvement over 85.50%.

The 38-form order recipe compares numeric/reversed preset order and individual
case-body swaps. Several forms reach 89.30%, 135/136 instructions, prefix 2,
with 21 clean references, one unaudited load, and a mismatched jump table.
These are useful diagnostic seeds: native physical block order need not be the
authored case order. No alternative is exact, and no case reordering is retained
in the canonical source in this batch. Both recipes and their complete receipts
remain available; neither establishes a compiler-provenance requirement.


## 2026-09-07 five-function campaign evidence

A C++ COM-interface view and an inline device-call operation are both
byte-neutral at 85.50%. The complete preset-block sharing remains unresolved;
no interface header or call wrapper is retained.

The committed recipes and hash-bound receipts describe the tested forms; they
do not establish source exhaustion.


## 2026-09-07 platform continuation

The 150-form `preset-order-and-partition-interaction-20260907.json` pairs the
better case order with every previously tested equal-effect group partition.
It reproduces, but does not improve, the 89.30% ordering seed. The canonical
source now retains the smallest form: place mode 14 immediately after mode 2,
with every case body and state value unchanged. This keeps the improvement
visible as a partial: 135/136 instructions instead of 126/136, prefix 2/136,
21 clean references instead of 20, one target-only load instead of two, and
the existing mismatched switch table. Duplicate blocks and shared suffixes
still differ; this is not an exact match.

The executable's independently verified VC6 8168 C++ contribution motivated
six unchanged adjacent render controls under both standard C++ profiles.
`initialize_direct3d_renderer`, `set_blend_mode`, `render_game_frame_scene`,
`present_backbuffer`, `configure_sprite_render_state`, and `bind_texture_ref`
all remain exact under both msvc6.5 and msvc6.0: 308 native instructions in
aggregate, full prefixes, and clean references. The immediate blend helper
and textured quad are also byte-neutral between those profiles. These controls
do not distinguish the render compiler profile, so no profile override is
retained. Each comparison has a receipt in the corresponding scratch ledger.

## 2026-09-07 continuation: numeric preset grouping

All 300 numeric-order/reverse-order partitions of the equivalent preset groups
were evaluated in two receipts: the first budget covered 256 forms, and the
remaining recipe covers the other 44 without repeating candidates. None
improves the current 89.30%, 135/136-instruction source or resolves its jump-table reference mismatch. The unchanged-source 8447 comparison is neutral;
see the [profile controls](../rebuild_game_archive_if_needed/profile-controls-20260907.md).

The recipes bound these case-grouping hypotheses; they do not establish source
exhaustion. No source or compiler setting changes.
