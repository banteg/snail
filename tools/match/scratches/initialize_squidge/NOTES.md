# initialize_squidge

Exact `cRSquidge::Init` helper at `0x444960`. The Windows function name is
ownership-canonical. The historical `initialize_score_stats` alias has been
retired from this function because it does not own or initialize score storage;
that compatibility name now belongs to the proven
`clear_subgoldy_score_buckets` / `cRSubGoldy::ScoreStatsInit()` mapping.

Ownership proof:

- the sole Windows callsite is `initialize_subgoldy`, with receiver
  `Player + 0x4344`;
- score buckets are a separate six-int array at `Player + 0x310`;
- the surrounding Windows helpers use that same `+0x4344` owner as two
  three-float spring lanes (`y_output/y_velocity/y_phase` and
  `z_output/z_velocity/z_phase`);
- Android exports `cRSquidge::Init`, `StartY`, `StartZ`, and `AI`; their bodies
  consume the same exact 0x18-byte six-float layout, and Android
  `cRSubGoldy::Init` calls `cRSquidge::Init`;
- iOS independently exports the same four authored `cRSquidge` symbols.

The helper clears the six floats in native Windows store order: `+0x04`,
`+0x08`, `+0x00`, `+0x10`, `+0x14`, then `+0x0c`. Its source return type is
`void`; the zero left in `eax` is only the register used for the stores.

Focused Wibo remains exact: 100.00%, 8/8 instructions, no masked operands.

2026-07-26 ownership correction: Android supplies the exact method body and
iOS independently supplies the authored symbol. Together with the sole Windows
receiver at `Player + 0x4344`, this makes `initialize_squidge` canonical.
The newly imported mobile ScoreStatsInit bodies also prove that the distinct
authored score initializer maps to exact Windows helper 0x4403a0, so the old
compatibility alias can move to its real owner.

## 2026-08-12 authored method surface

The scratch now spells the exact member as `cRSquidge::Init()` and exports the
MSVC6 relocation name `?Init@cRSquidge@@QAEXXZ`. Live Windows callsite recovery
confirms its sole receiver is `cRSubGoldy + 0x4344`; Android and iOS independently
retain `cRSquidge::Init()`. The source-only promotion preserves the exact 8/8
instruction match and gives callers the authored API without compatibility glue.
