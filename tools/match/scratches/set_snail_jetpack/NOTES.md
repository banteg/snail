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

## Direct state mapping cleanup (2026-08-13)

The retained source no longer uses the old `register target_state` hint or a
redundant `input_state` copy. A recorded 14-form mapping sweep already proves
that the ordinary `switch (state)` form is byte-identical at **86.18%**,
61/62 instructions, prefix 0, and eight clean references. The coercive spelling
therefore carried no matching evidence and obscured the authored state map.

The experiment ledger preserves the complete mapping, local-lifetime, and
transition results. Their three mutation recipes depended on the removed
source text and are pruned rather than left as stale runnable inputs.

## 2026-09-05 bounded animation-family probes

Six mapping/transition lifetime variants move the immediate flag and replace the selected-state snapshot with direct reads. None improves 86.18%. The switch/prologue difference remains visible; these results bound only the tested source lifetimes.

## 2026-09-05 additional source-shape checks

Three inline state-mapping operations and three parameter-remapping lifetimes do not improve 86.18%. No helper is retained; the default-arm source lifetime remains unresolved.

## 2026-09-05 state mapping borrows

Six ordinary inline state-mapping forms cover a value, const reference, or
const pointer input with either a returned state or a reference output. All
are byte-neutral at 86.18%. No helper is retained. The native default-arm
parameter reload remains unrecovered.

## 2026-09-07 version-verified VC6 controls

Unchanged-source probes under the coherent `msvc6.0` and `msvc6.3` component
sets preserve this function's current normalized instructions and reference
state. The seven-function batch pairs the selector/search residuals with four
exact neighboring controls. No compiler override or source change follows
from this comparison. Component versions, hashes, measured results and the
separate mislabeled VC7-archive check are recorded in
[the compiler-control report](../../compiler-profile-controls-20260907.md).
