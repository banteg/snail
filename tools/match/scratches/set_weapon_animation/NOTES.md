# cRWeapon::SetAnimation @ 0x4446e0

Current recovery: semantic-complete (`compiler` residual). Live Windows
analysis establishes the same void `int, byte, int` member ABI as the Snail
counterpart; Android retains the authored
`cRWeapon::SetAnimation(int, bool, int)` symbol in `SubGame.o`.

The method queues an animation request or immediately selects one of five
owned renderable slots, follows its `Object::animation` link, normalizes
forward/reverse progress, clears the queue, installs the borrowed object, and
publishes the active-body flag on the exact 0x3dc-byte `cRWeapon` owner.

Focused VC6 result: **94.55%**, exact 55/55 instruction parity, prefix 48/55,
with all three relocation operands audited and clean. Only the final queued
slot publication rotates equivalent registers.

The matcher source now uses authored `SetAnimation` and exact VC6 symbol
`?SetAnimation@cRWeapon@@QAEXH_NH@Z`; `set_weapon_animation` remains only the
stable scratch and Windows-address identity.

## 2026-09-04 queue-publication diagnostics

The eight forms in `queue-publication-mutations.json` retest publication with
postincrement, preincrement/subtraction, local index/value, a slot reference,
commuted indexing, a pointer, and an unsigned index. Seven reproduce 94.55%
and the same register difference. Preincrement/subtraction reaches 95.41% but
has 54/55 instructions and changes the update schedule; it is not promoted.
All three references stay clean. The canonical source is unchanged; this finite
queue-only product does not close helper or whole-method source hypotheses.
