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
