# initialize_score_stats

Exact `cRSquidge::Init` helper at `0x444960`. The Windows function name is
retained as a stable match-harness identifier, but it was a historical
misidentification: this function does not own or initialize score storage.

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
