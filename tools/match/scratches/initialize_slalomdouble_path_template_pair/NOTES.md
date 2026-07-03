# initialize_slalomdouble_path_template_pair

Honest starter scratch for `initialize_slalomdouble_path_template_pair @ 0x425050`.

The constructor callsite uses the same six-argument stack shape as the slalom
family and the native epilogue is `ret 0x18`. The runtime kind written by this
public constructor is `0x20`, matching the current decompile. The scratch builds
the fixed 70-sample double-slalom body with four straight samples at each end,
sinusoidal lateral motion, raised Y motion, orientation, deltas, strip mesh, and
`finalize_path_template`.

Residuals are expected. This is a semantic starter, not a tuned byte match.

2026-06-21 helper-inline sweep: native flattens the scratch-local helper layer.
Forcing those helpers inline moves focused Wibo from 10.59% (129/683
candidate/target instructions) to 22.28% (574/683), with masked operands
improving from 12 ok, 0 unresolved, 5 mismatch to 31 ok, 0 unresolved, 1
mismatch.

2026-07-03 falloff shape: split the double-slalom center falloff into the two
native absolute-distance temporaries before the sine/scale multiply. Focused
Wibo moves from 22.28% (574/683) to 22.66% (588/683), with masked operands
improving from 31 ok, 0 unresolved, 1 mismatch to 32 ok, 0 unresolved, 1
mismatch.
