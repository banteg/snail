# initialize_score_stats

Exact `ScoreStats` helper at `0x444960`.

The helper clears the six score/stat bucket dwords in native order:
`+0x04`, `+0x08`, `+0x00`, `+0x10`, `+0x14`, then `+0x0c`, returning zero.

2026-06-20 helper-type consolidation:

- Promoted the shared `ScoreStats` view into `tools/match/include/score_stats.h`
  and removed the scratch-local duplicate declaration.
- Focused Wibo remains exact: 100.00%, 8/8 instructions, no masked operands.
- `initialize_subgoldy` now consumes the same header for its callsite and
  remains stable at 95.14%.
