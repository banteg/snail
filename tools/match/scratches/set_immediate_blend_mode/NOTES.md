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

Current focused result: `85.50%`, `126/136` candidate/target instructions,
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
