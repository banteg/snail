# update_banner

`update_banner` drives a small banner/start-line actor:

- `+0x04` flags, with bit `0x20` toggled by the visibility gate
- `+0x14` y bob output
- `+0x18` state-1 reference z
- `+0x38` visibility mode
- `+0x54` row source pointer, read at source `+0x70`
- `+0x58` phase
- `+0x5c` phase step

Visibility mode `0` sets bit `0x20` while `row_source->row_position < 40`.
Visibility mode `1` sets it while `reference_z - row_source->row_position <
46`. Other modes skip the visibility gate and only advance the bob phase.

The bob output is `sine(phase * 6.2831855) * 0.25999999`.

## Scratch status

Added on 2026-06-18. Focused Wibo verifies a clean 100% match: 44/44
instructions, prefix 44/44, 7 masked operands OK, no unresolved or mismatched
operands.

Source-shape note: do not stage the sine argument in an `angle` local. Native
keeps no stack local in the prologue and uses `push ecx; fstp [esp]` directly
before calling `sine`.
