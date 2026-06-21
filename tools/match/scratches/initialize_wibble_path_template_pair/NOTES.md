# initialize_wibble_path_template_pair

Starter reconstruction for `initialize_wibble_path_template_pair @ 0x4289a0`.

Captures the fixed 32-sample wibble template: endpoint samples, sinusoidal
interior up-vector wobble, secondary sample offset, delta recomputation,
generated strip mesh, and finalization.

The remaining mismatch is source-shape/codegen debt, especially the decompiler's
pointer-shaped loop counters and the shared mesh tail. No dummy symbols, inline
assembly, flag changes, or volatile/register games were introduced.

2026-06-21 helper-inline sweep: native flattens the scratch-local helper layer.
Forcing those helpers inline moves focused Wibo from 9.41% (115/608
candidate/target instructions) to 22.54% (510/608), with masked operands
improving from 7 ok, 0 unresolved, 8 mismatch to 20 ok, 0 unresolved, 4
mismatch.
