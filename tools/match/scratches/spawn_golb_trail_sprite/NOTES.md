# cRSubGolb::Jet

Exact at 47/47 instructions with two clean relocation masks. The Windows
method allocates sprite `0x21`, seeds its gameplay-owned trail lanes, copies the
supplied position, forwards the shot-bank index into `object_ref`, and returns
the allocated `cRSprite*`.

Android preserves the authored `cRSubGolb::Jet(tVector)` symbol and the same
three `cRSubGolb::AI()` call positions: current projectile position and 0.3
and 0.6 units behind it. Its standalone Jet body is deliberately empty, while
iOS inlines a different trail effect. Windows therefore keeps its observed
`tVector*` argument and `cRSprite*` result rather than importing the mobile
ABI. The typed velocity pointer is retained because it naturally produces the
native zero-store schedule.
