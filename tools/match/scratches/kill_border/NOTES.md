# kill_border

`kill_border` marks one frontend widget for teardown unless it is already dead
or protected by flag `0x400`. Widgets with flag `0x100000` own three child
widgets at `+0x718..+0x720`, which are killed recursively.

The shared `BorderManager` declaration now models the helper as returning
`int`, matching callers such as `reset_tooltip` that preserve the result. The
scratch returns an intentionally unspecified local because the native helper
falls through with whatever `eax` contains, but VC6 under the match harness
cannot compile a non-void fallthrough without entering a missing-import warning
path. Current result: 88.52%. The remaining residual is the three recursive
calls normalizing as `call ADDR` instead of target-local `call L0`, plus the
compiler's final load for the placeholder return value.
