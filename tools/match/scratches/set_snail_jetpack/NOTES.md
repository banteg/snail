# cRSnail::SetJetPack @ 0x445860

Current recovery: semantic-complete (`compiler` residual). Live Windows
analysis establishes a void `cRSnail` member with one integer argument;
Android and iOS both retain `cRSnail::SetJetPack(int)` in `SubGame.o`.

The method maps the requested state onto the embedded jetpack `cRWeapon`,
transitions out of the previous active state, dispatches the authored reverse,
show, queued-idle, or hide animations, publishes `selected_state`, and emits
the independently corroborated sound cues.

Focused VC6 result: **86.18%**, 61/62 candidate/target instructions, prefix
0/62, with all eight relocation operands audited and clean. Remaining drift is
the switch/prologue register schedule and one instruction of transition shape;
no behavior or owner is missing.

The matcher source now uses authored `SetJetPack` and exact VC6 symbol
`?SetJetPack@cRSnail@@QAEXH@Z`; `set_snail_jetpack` remains only the stable
scratch and Windows-address identity.
