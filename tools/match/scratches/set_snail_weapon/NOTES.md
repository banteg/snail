# cRSnail::SetWeapon @ 0x445920

Current recovery: semantic-complete (`analysis` residual). Live Windows
analysis establishes a void `cRSnail` member with one integer argument;
Android and iOS both retain `cRSnail::SetWeapon(int)` in `SubGame.o`.

The method maps the Goldy shooting flags onto target states for all three
embedded weapon channels, performs reverse/show/queued-idle/hide transitions
through `cRWeapon::SetAnimation`, publishes each selected state, and emits the
appropriate activation/deactivation sound feedback. The sparse movement lookup
and jump tables remain explicit curated references.

Focused VC6 result under scoring policy 5: **83.5386%**, 246/249 candidate/native
code instructions, prefix 1/249, with all 24 reference operands audited and
clean. The guarded remap is literal data, not code. Remaining state lifetimes,
register allocation, and transition scheduling require further analysis.

## 2026-09-11 lookup-aware lifetime replay

The current recipe records 38 initialization, channel-borrow, and chained
target-assignment controls. Two chains score 83.7626%, but merely reorder
assignments across the still-wrong state register allocation: native channel
targets use EDI/EBP, while those candidates retain EBP/EBX. They preserve the
same three missing instructions and do not recover the early input load or
the channel-zero address lifetime. No source is promoted from that score gain.

The other controls are neutral or regress; eager initialization also changes
the audited jump-table structure. The default path and uninitialized third
target remain as observed in the Windows body. These bounded results do not
close the mapping or transition work. The recipe and
[receipt](../../initializer-boundaries-20260911.json) preserve every current
result and the relevant native/candidate assembly differences. The September 5
measurements below used older source dependencies and scoring.

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

## 2026-09-05 shared transition owner and feedback joins

Six whole-channel forms reuse a transition-channel pointer across the first,
first two, or all three channels, either at target-switch entry or inside its
two-call cases. All regress from 73.02%. Six additional forms join the third
channel's duplicated state/sound exits, with the original, direct, or later
channel-zero borrow and either a shared change gate or existing sound branch.
All regress as well. Every variant compiles with all 24 references clean; no
source change is retained. The native mapping/transition lifetimes remain open.
