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

## 2026-09-05 bounded animation-family probes

Eight complete release-vector variants compare shared versus scoped vectors, direct channel stores versus borrowed destinations, and final owner reuse. All regress from 92.80%; the RNG call order is preserved. No variant is retained. The first random-x spill and later vector publication lifetimes remain open.

## 2026-09-05 goal-600 source ownership campaign

Eleven whole-channel forms test direct channel fields, live owner velocity access, separate scopes and the final owner borrow. None improves 92.80%; canonical source is unchanged.

The recorded probes describe the tested source forms only; they do not establish exhaustion.

## 2026-09-05 additional source-shape checks

Five diagnostic vector copy/assignment definitions regress from 92.80%; seven combinations of const vector value returns are neutral. No header change is retained.

## 2026-09-05 release operation boundaries

Six complete ordinary inline release operations test vector returns, vector
outputs, and channel outputs, with either explicit inputs or the original
ordered RNG calls inside the operation. Five are byte-neutral at 92.80%;
channel ownership across the RNG calls regresses to 89.24%. No helper is
retained. The first X spill and third channel's store schedule remain open.


## 2026-09-05 independent release-scalar scopes

Separating the four channels' scalar and destination locals, or separating
only the first or final channel, is byte-neutral at 92.80%, 125/125
instructions, prefix 13, and 33 clean references. The first unique-name
variant accidentally renamed real `release_step` members as well as locals;
record 10 has a digest-bound invalid-plan audit. Its corrected recipe compiles
successfully and is also neutral. No source or shared type changes are kept.

## 2026-09-08 pre-RAND component ownership control

The complete native/candidate comparison isolates two nonmatching blocks. The
first `gRMathRand2` result is converted and spilled before `RAND`: native uses
`[esp+0x1c]`, whereas the candidate uses the dedicated scalar slot
`[esp+0xc]`. The proven-equivalent compiler listing identifies that candidate
slot as `random_x`, while the native slot is also used by the constructed input
vector later in the block. This identifies storage reuse, not a recovered
native local name. Native also performs the first and third block's post-RAND
`fadd` before loading `owner_player`; the third block interleaves three vector
stores with the remaining multiplies. The second and fourth blocks already
match.

`component-input-ownership-20260908.json` tests whether staging the RNG values
directly in their input-vector component owner recovers this relationship,
for the first block, first and third blocks, or all four (with two scalar
scope controls). All four keep 125/125 instructions and 33 clean references,
but regress from 92.80% to 45.60-76.80%. None is retained. This bounds the
specific component-staging hypothesis; it does not establish source or compiler
exhaustion. The canonical scalar source and shared vector contracts are unchanged.
