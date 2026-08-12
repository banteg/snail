# cRSnail::ReleaseWeapons @ 0x442e40

Current recovery: semantic-complete (`compiler` residual). Live Windows
analysis establishes a void no-argument `cRSnail` member, and Android/iOS both
retain `cRSnail::ReleaseWeapons()` in `SubGame.o`.

On the first release it constructs randomized, forward-biased release steps
for the jetpack and all three weapon channels, ends the owning Goldy hover, and
publishes the one-shot release gate. The exact embedded `cRWeapon` layout and
the non-owning `owner_player` backlink corroborate every destination.

Focused VC6 result: **92.80%**, exact 125/125 instruction parity, prefix
13/125, with all 33 relocation operands audited and clean. Remaining drift is
anonymous vector/scalar stack-slot allocation across the four repeated blocks.

The matcher source now uses authored `ReleaseWeapons` and exact VC6 symbol
`?ReleaseWeapons@cRSnail@@QAEXXZ`; `release_snail_weapons` remains only the
stable scratch and Windows-address identity.
