# cRSnail::SetAnimation @ 0x444600

Current recovery: semantic-complete (`compiler` residual). Windows exposes a
void `thiscall` with `int`, one-byte immediate, and `int` arguments. Android
names it `cRSnail::SetAnimation(int, bool, int)`, while iOS independently
preserves the class/name provenance in `SubGame.o`. Authoring the Windows byte
as `bool`, matching the paired `cRWeapon` method, is byte-identical.

The immediate path selects one of ten owned renderable slots, installs its
borrowed animation and object, normalizes forward/reverse progress, clears the
queue, and publishes the active-body flag. The queued path appends the three
arguments to the exact `cRAnimManager` arrays.

Focused VC6 result: **94.55%**, exact 55/55 instruction parity, prefix 48/55,
with all three relocation operands audited and clean. Only the final queued
slot publication rotates equivalent registers.

The matcher source now uses authored `SetAnimation` and exact VC6 symbol
`?SetAnimation@cRSnail@@QAEXH_NH@Z`; `dispatch_cutscene_animation` remains only
the stable scratch and Windows-address identity.
