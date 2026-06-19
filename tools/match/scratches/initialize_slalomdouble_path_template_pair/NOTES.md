# initialize_slalomdouble_path_template_pair

Honest starter scratch for `initialize_slalomdouble_path_template_pair @ 0x425050`.

The constructor callsite uses the same six-argument stack shape as the slalom
family and the native epilogue is `ret 0x18`. The runtime kind written by this
public constructor is `0x20`, matching the current decompile. The scratch builds
the fixed 70-sample double-slalom body with four straight samples at each end,
sinusoidal lateral motion, raised Y motion, orientation, deltas, strip mesh, and
`finalize_path_template`.

Residuals are expected. This is a semantic starter, not a tuned byte match.
