# cRSubGolb::Smoke

Exact at 72/72 instructions with eight clean relocation masks. The method
allocates sprite `128`, derives progress and lifetime steps from the owning
subgame rate, copies white RGBA, seeds the size lanes, scales the projectile
velocity by `0.4`, clears gravity, and copies the supplied position.

Android preserves the authored by-value `cRSubGolb::Smoke(tVector)` symbol and
the same Sprite initialization lanes. Live Windows evidence establishes a
void method taking `tVector*`; both `cRSubGolb::AI()` callsites discard EAX.
The scoped aggregate velocity assignment reproduces Windows' stack-staged
three-lane store schedule without padding or register coercion.
