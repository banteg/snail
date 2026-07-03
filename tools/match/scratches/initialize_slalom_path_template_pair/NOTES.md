# `initialize_slalom_path_template_pair` starter

This is an honest semantic starter for the path-template initializer at
`0x41f760`.

It models the slalom setup with four flat entrance samples, four flat exit
samples, the recovered sine lateral displacement with squared center falloff,
roll from previous center-X, delta vectors, strip mesh construction, and
finalization.

The source is intentionally a low/partial starting point. Residuals are expected
around VC6 register allocation and mesh-loop scheduling.

2026-07-03 ABI cleanup: the constructor callsite passes six stack arguments and
the native tail is `ret 0x18`. Updating the scratch and shared declaration from
the stale four-argument prototype moves focused Wibo from 19.22% (615/696) to
19.37% (615/696), with masked operands unchanged at 19 ok, 0 unresolved, 3
mismatch.
