# cRSnail::ReleaseWeapons @ 0x442e40

## 2026-09-21 ordinary component and direction ownership controls

The canonical source remains **94.40%, 125/125 instructions**, prefix 15 and
33 clean references. Complete vector, component-array, scalar-pair and in-place
scaling controls, followed by first/third-channel isolation, add no retained
improvement. No authored purpose for the previous diagnostic's redundant
conversions was recovered. The [four-target receipt](../../mesh-owner-frontier-20260921.md)
preserves these source recipes and measurements alongside three path-builder
gains; these finite controls do not establish exhaustion.

## 2026-09-14 unpromoted vertical-precision diagnostic

Canonical source remains at **94.40%, 125/125 instructions**, prefix 15 and
33 clean references. A separate source reproduces the complete 554-byte native
body, all 33 strict positional references and its literal branch, but requires
two redundant numeric conversions with no recovered authored purpose. It is
not promoted under the no-fakematching requirement. Preserving C2 observations,
removal controls and named-value/array alternatives are retained as evidence
for further source recovery, without changing the public exactness claim.

See the [diagnostic source, proof, controls and compiler observations](../../halfpipe-live-bank-and-release-diagnostic-20260914.md).

## 2026-09-14 first vector component ownership

The retained source improves **92.80% to 94.40%**, with 125/125 instructions,
prefix 15 and 33 clean references. Constructing the first input vector directly
recovers native's shared storage for its random-X spill and reload. Exactly two
ordinary bytes change, at offsets 55 and 92; both complete changed instructions
now equal native bytes. The RNG call order, all other candidate bytes and the
reference audit are unchanged. This remains a partial body match.

See the [controls, raw byte proof and reversal evidence](../../release-component-and-bank-controls-20260914.md).
The measurements below describe the previous source.

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

## 2026-09-25 scheduler trace of the two open blocks

Unchanged at **94.40%**. `tools/match/c2/schedtrace.py release_snail_weapons
--line 14` shows two different mechanisms.

- **First block (jetpack): priority.** After the `RAND` call, the ready list
  holds `mov eax, [esi+0x100]` (height 131: owner load → AGI 2 →
  `fld [eax+0x418]`) and the `fadd 0.5` (height 129). Our rule picks the owner
  load. Native picks the `fadd`, so native's `fadd` is at least as high
  (a 131 tie goes to the `fadd`, which comes first in IL). In our graph
  the `IL_FROUND` after that `fadd` (tuple 13) has no successors, so it adds
  nothing to the `fadd`'s height. If it lay on the x87 chain, the `fadd` would
  reach 133. The IL shape that native implies is not yet identified.
- **Third block (`weapon_channels[2]`): the 81-tuple cut.** Window 1 ends
  inside this block, at the second `fmul` (the Y product). Its launch-vector
  stores and the `lea ecx, [esi+0x11d4]` fall into window 2, so they cannot
  interleave with the products. In the same block, the owner load (height 19)
  also wins over the `fadd` (height 18) for the same reason as the first
  block. Native interleaves the `lea` and the X store between the multiplies,
  so native's window 1 reaches further: it has fewer tuples than ours before
  this block. Window 1 holds eight `IL_FROUND` tuples: one after each random-X
  subtraction and each owner-Z load, plus the jetpack's X product and Y
  `fadd`.

The second and fourth blocks already match, because there the owner load's
larger height is also native's order. No source change is retained.

## 2026-09-25 codeless-tuple sweep

`schedtrace.py --census`: window 1 is cut at 81 tuples after the third
block's Y product, and holds 8 `IL_FROUND`s. Native's third block
interleaves the `lea ecx` and the X store between the products, so its
window 1 would have to reach past our tuple ~89. That needs about eight fewer
tuples before the cut, and window 1 only has eight FROUNDs.

Grids:

| Variant | Tuple effect | Result |
| --- | --- | --- |
| 256 combinations of named/inline X, Y, Z per block, with the owner and destination placement kept | 1–2 fewer | best 94.40% (unchanged) |
| any named form of the jetpack block | 1–2 fewer | loses the native `[esp+0x1c]` X slot (92.80%) |
| third block alone as single-use `laser_x/laser_y` names or inline | none: the tuple count and code are identical | unchanged |

Block 1's `fadd`/owner-load order also needs the `fadd` to gain two height
levels. That needs two FROUNDs **on** its chain, whereas the jetpack Y
FROUND is dangling (no successors). No change retained.

## 2026-09-26: Codex consult (no gain)

A bounded Codex consult (gpt-6-astra, about 40-60 probes) found no defensible improvement. Its evidence and probe ledger are in `/private/tmp/claude-501/sm/codex/release_snail_weapons/RESULTS.md`.
