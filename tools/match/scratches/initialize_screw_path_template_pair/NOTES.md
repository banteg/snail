# `initialize_screw_path_template_pair` starter

This is an honest semantic starter for the path-template initializer at
`0x41eda0`.

It reconstructs the screw template setup, three-sample entrance, five-sample
exit, helical middle section, recovered `rotation_scalar_94` angle, rotated
secondary lane, adjacent-sample orientation, deltas, strip mesh, and final
template pass.

The scratch is partial and keeps the source plausible. Any future tightening
should focus on real lifetime/control-flow shape.

2026-07-03 ABI cleanup: the constructor callsite passes six stack arguments
(`curve_count`, `width_cells`, an unused mode, two textures, and a cap texture)
and the native tail is `ret 0x18`. Updating the scratch and shared declaration
from the stale four-argument prototype moves focused Wibo from 18.80% (613/685)
to 18.95% (613/685), with masked operands unchanged at 19 ok, 0 unresolved, 4
mismatch.
