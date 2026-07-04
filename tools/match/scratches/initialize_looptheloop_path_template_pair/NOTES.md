# `initialize_looptheloop_path_template_pair` starter

This is an honest semantic starter for the path-template initializer at
`0x41b0f0`.

The scratch reconstructs the recovered loop-the-loop family setup from the IDA
and Binary Ninja decompiles: template metadata, primary/secondary samples,
straight approach/departure runs, the circular loop section, delta vectors,
strip-mesh vertices/faces, and the final `finalize_path_template` call.

It deliberately keeps the implementation source-level and plausible rather than
trying to force register allocation. Residuals are expected around helper
inlining, x87 scheduling, and the large mesh/face loops.

2026-07-03 ABI cleanup: focused diff shows the native tail is `ret 0x18`, so
the constructor uses the same six-argument stack cleanup as the surrounding path
template callsites. Updating the scratch and shared declaration from the stale
four-argument prototype moves focused Wibo from 35.59% (639/721) to 35.74%
(639/721), with masked operands unchanged at 39 ok, 0 unresolved, 0 mismatch.

2026-07-04 prologue order cleanup: the native entry compares `width_cells_`
against 4 and selects the loop wiggle before starting the `curve_source *
6.2831855f` integer conversion; it also writes `width_or_scale` after that
conversion. Delaying `PATH_CURVE_COUNT` and `width_or_scale` to match that
order keeps focused Wibo at 35.74% (639/721) but improves the masked audit from
39 ok to 40 ok, with 0 unresolved and 0 mismatch.
