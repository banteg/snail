# update_font_wave_state

Initial scratch for the per-frame font queue reset and wave-phase updater at
`0x449ca0`.

Wibo result: exact 100%, 25/25 instructions, masked operands 17 ok.

Recovered relationships:

- Resets the shared text-buffer cursor (`data_7772f0`) to `data_753ce8`.
- Clears the registered-font counter (`data_777b20`) and font queue count
  (`data_777b24`) every frame before queued text/quads are appended.
- Advances the two wave phases initialized by exact `initialize_font_wave_state`
  and wraps each phase by one `2*pi` interval.

## 2026-07-14 shared global declarations

The reset and initializer now share the font runtime declarations instead of
redeclaring the four wave scalars, text cursor, and counters independently.
Their addresses also close the tail around the fixed sheet bank: the scale
cache ends at `g_font_wave_phase_a` (`0x7772e8`), followed by phase B, the text
cursor, step B, the one-sheet array, registered/queue counts, and step A.

Both exact routines remain byte-identical: `update_font_wave_state` retains
hash `5585d19e0efdb2d1ee1b0fa481c8dae4e5928fa1d6183b6a1b2c387939065365`
(`25/25`, 17 clean operands), and `initialize_font_wave_state` retains hash
`3a31a5797a1d96d8af76b1af64c46364afee7e5de4c6f690a3502cc17f5215e4`
(`5/5`, four clean operands).
