# cRSnail::SetWeapon @ 0x445920

Current recovery: semantic-complete (`compiler` residual). Live Windows
analysis establishes a void `cRSnail` member with one integer argument;
Android and iOS both retain `cRSnail::SetWeapon(int)` in `SubGame.o`.

The method maps the Goldy shooting flags onto target states for all three
embedded weapon channels, performs reverse/show/queued-idle/hide transitions
through `cRWeapon::SetAnimation`, publishes each selected state, and emits the
appropriate activation/deactivation sound feedback. The sparse movement lookup
and jump tables remain explicit curated references.

Focused VC6 result: **73.02%**, 245/248 candidate/target instructions, prefix
1/248, with all 24 relocation operands audited and clean. Remaining drift is
compiler register allocation and repeated transition scheduling, not missing
state cases.

The matcher source now uses authored `SetWeapon` and exact VC6 symbol
`?SetWeapon@cRSnail@@QAEXH@Z`; `set_snail_weapon` remains only the stable scratch
and Windows-address identity.

## 2026-09-05 bounded animation-family probes

Three complete channel-lifetime variants remove the channel-0 borrow and/or separate selected-state and immediate locals for each channel. All regress from 73.02% with references still clean. The original state-dispatch and channel interactions remain open; local simplification alone is insufficient.

## 2026-09-05 continued source-shape investigation

Eleven change-gate lifetime forms regress from 73.02%. The undefined default-arm value remains as in the native body; no fabricated initialization is added.

## 2026-09-05 channel operation and target-array checks

Twelve `whole-channel-transition-operation-20260905-mutations.json` forms
factor the first two identical animation transitions, borrowing the channel
or indexing it through the Snail and returning/borrowing the changed flag.
All regress to 63.27%, with the 24 references still clean.

Fourteen `whole-case-channel-borrows-20260905-mutations.json` forms place the
channel borrow only inside the two-call target-state branches. Changing only
channels one/two is neutral at 73.02%; moving channel zero's borrow regresses
to 68.29%. Eight coupled target-state array forms in
`whole-target-channel-array-20260905-mutations.json` regress further to
58.42–59.02% and expose six unaudited operands. The undefined default-arm
third state is left uninitialized in every probe. No source is retained;
these results do not close the branch-lifetime or state-mapping source work.
