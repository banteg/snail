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
