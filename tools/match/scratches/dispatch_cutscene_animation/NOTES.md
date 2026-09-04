# cRSnail::SetAnimation @ 0x444600

Current result: **100.00%**, 55/55 instructions, all three references clean.
The exact recovery below supersedes historical queue-register residuals.

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

## 2026-09-05 bounded source-expression probes

Seventeen combinations of absolute-step expressions and post-incremented queue insertion do not improve the 94.55% baseline. The queue-store register pair remains unresolved.

The recorded specifications and experiment receipts preserve these negative
results. They do not establish source exhaustion or compiler provenance.

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
