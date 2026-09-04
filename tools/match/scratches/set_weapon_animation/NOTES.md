# cRWeapon::SetAnimation @ 0x4446e0

Current result: **100.00%**, 55/55 instructions, all three references clean.
The exact recovery below supersedes historical queue-register residuals.

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

## 2026-09-05 exact selected-object publication lifetime

The same source change closes both snail and weapon SetAnimation: read the
selected slot directly and assign `object` before clearing `queue_count`.
This removes the unnecessary root-object local. Although the immediate branch
still emits the same native instructions, VC6 now also chooses the native
registers in the queued branch. Both functions rise from 94.55% to 100%, with
all three references clean. Direct active-animation lookup removes the
pointer-to-pointer slot borrow and remains exact.

A first 11-shape sweep isolated a 98.18% intermediate with an earlier mismatch;
it was not retained. Four follow-up root/publication forms identify the exact
ordering, without changing the absolute-step expressions or callee ABI. Local
queue-expression probes had missed this whole-function lifetime interaction.
