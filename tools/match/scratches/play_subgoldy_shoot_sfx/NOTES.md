# play_subgoldy_shoot_sfx / cRSubGoldy::PlayShootSfx @ 0x43afd0

Best current result: 89.13%.

The native stack has two `Vector3` locals: the camera-minus-player delta is
stored at `esp+0xc..0x14`, copied to `esp+0x18..0x20`, and the copy is passed to
`normalize_vector`. Modeling that as `normalized_vector = vector` matches the
full stack/vector-copy region and raises the scratch from 80.90%.

Remaining miss: after clamping the attachment-exit volume below zero, the target
stores `0.0f` and jumps to the shared `play_sound_effect_scaled` tail. VC6.5
continues to duplicate that call tail in source-equivalent forms tried so far:
structured `else if`, two independent `if`s, explicit `goto play_scaled`,
nested `else`, ternary clamp, do/break clamp, sentinel-initialized `sound_id`,
and a raw-double lower-bound spelling. Avoid using volatile, fake symbols, or
asm to force this tail merge.

2026-06-13 pin audit: focused matcher still verifies 89.13%, 96/88 insns.
Semantics are pinned: movement flag buckets, RNG variant draws,
camera-minus-player vector staging, normalized distance volume, and both audio
call paths match the recovered behavior. Leave the remaining residual as
clamp-tail control-flow duplication unless a new source-shaped VC6 tail form
appears.

2026-06-20 larger motion-audio retry: focused Wibo still reports 89.13%,
96/88 candidate/target instructions, 26/88 prefix, and 19 clean masked
operands. The addressed dump confirms native stores zero for the lower clamp
then jumps to the shared `play_sound_effect_scaled` tail. Inverting the source
guard to `if (volume >= 0.0f) ... else ...` regresses to 88.04% by duplicating
the upper clamp tail instead. Two independent clamp guards are codegen-neutral
and still duplicate the lower tail. The exact `play_sound_effect_scaled`
scratch and shared audio header keep the callee `void`, so changing the ABI
would be source-false. No canned `snail match idioms` clamp case exists; keep
the clearer `if/else if` clamp until a real VC6 tail-merge source idiom is
identified.

2026-07-14 camera owner closure: root `+0x18c..+0x194` is
`GameRoot::players[0].transform.position`, the inherited renderable transform
of the front-end `GamePlayer`. The attachment-exit volume therefore measures
from that camera/player presentation position to the gameplay Goldy position.
Naming the aggregate owner is codegen-neutral at the retained 89.13% baseline.

## 2026-07-16 void helper ABI

Both direct `update_subgoldy` callsites discard EAX. The two native returns
either follow `play_sound_effect_scaled` or `play_sound_effect`, so the observed
register value is merely the callee's incidental residue; the early no-sound
path likewise promises no result. BN and IDA now preserve the source-authored
`void __thiscall(Player*)` contract. The matching source already used that ABI
and remains unchanged at 89.13%, 96/88 instructions, prefix 26/88, with all 19
masked operands clean.

## 2026-07-18 Player lifecycle ownership guard

The focused replay now makes the void `Player*` ABI and its transitive owner
graph durable in both tools: movement flags and the cached variant sample live
on `Player`, attachment-exit attenuation reads the Player body transform, and
the reference position comes from the root-owned presentation player. This is
an analysis-only improvement. The honest matcher baseline remains 89.13%,
96/88 instructions, prefix 26/88, with all 19 masks clean; the unresolved
lower-clamp tail is not fakematched.

## 2026-07-25 authored PlayShootSfx ownership

Android and iOS preserve this exact member as
`cRSubGoldy::PlayShootSfx()`. The Android body repeats the Windows three
shoot-flag buckets, random SFX ranges 17..18 / 19..21 / 22..24, cached
variant, Goldy-to-presentation-player distance attenuation, and direct versus
scaled sound calls. This closes the stable Windows helper as shoot-SFX
ownership rather than a generic movement-state sound.

IDA 9.4 shows every Android path joining one
`POP {R4-R8,R10,PC}` epilogue. The no-SFX path leaves the original receiver in
R0; direct and attenuated playback leave unrelated `cRSound::Play` or
`PlayVolume` residue. Ghidra 12.1.2 independently demangles the same body as
`void cRSubGoldy::PlayShootSfx()`. The shared Windows ABI remains the proven
void mutator.

`Player +0x1cc` is consequently narrowed from a generic movement-sound sample
to `shoot_sfx_variant_sample`, the cached 0..1 or 0..2 family variant. The
stable manifest name remains `play_movement_state_sound`, with
`PlayShootSfx` as its authored matcher alias. This is ownership-only: the
honest 89.13%, 96/88 result and the unresolved VC6 lower-clamp tail remain
unchanged.

## 2026-07-26 canonical owner and attenuation spelling

Android and iOS now supply the canonical Windows identity
`play_subgoldy_shoot_sfx`; `play_movement_state_sound` remains an alias. The
source also adopts the mobile-preserved `distance / -60.0f + 1.0f`
attenuation spelling. VC6 emits the same 96-instruction candidate, so the
honest 89.13% result, 26/88 prefix, and unresolved lower-clamp tail remain
unchanged.

## 2026-07-28 dual-mobile vector expression

Android and iOS both build one local vector from the presentation-player
position minus Goldy's inherited transform position before normalizing a copy.
The Windows source now expresses that subtraction through the shared
`Vector3::operator-` instead of three hand-written component assignments.
VC6 emits the same 96-instruction candidate, preserving the honest 89.13%
result and the same 19 clean audited references; the two candidate-only
duplicated-tail references remain explicitly unaudited.

The iOS negative-volume branch also motivated a direct portable control-flow
probe: call scaled playback with literal zero in the negative branch, otherwise
clamp the upper bound and call with the local volume. VC6 duplicated that call
and epilogue and regressed to 89.01%, 94/88 instructions. It was removed; the
Windows target's shared lower-clamp tail is still an optimizer residual rather
than evidence for platform control flow.

## 2026-07-28 dual-mobile SFX ranges

Android and iOS both retain the three authored random buckets as a unit-random
draw scaled to two, three, and three choices, producing SFX ranges 17..18,
19..21, and 22..24. The first mobile bucket appears as two additions of the
unit factor while the latter buckets retain explicit `* 3.0f`; the Windows
scratch now names the equivalent range factors rather than their folded
decimals. VC6 emits the same 96-instruction candidate, preserving the honest
89.13% result, prefix 26/88, 19 clean references, and two candidate-only
unaudited duplicated-tail references.

## 2026-07-29 bounded playback-tail audit

Two recorded sweeps make the previously manual tail-merge boundary
reproducible. `playback-return-mutations.json` evaluates all eight one- and
two-site combinations of explicit returns after the scaled and direct playback
calls. Ordinary `return;` statements are byte-neutral; VC6 rejects returning a
void expression, so no hidden return contract changes the tail.

`volume-clamp-tail-mutations.json` evaluates nine clamp-and-call control
shapes. Nested and independent clamps, a named clamped value, a conditional
expression, and an explicit shared label are all byte-identical to the 89.13%,
96/88 baseline. The direct literal-zero playback branch reaches 89.01%;
inverting or breaking out of the clamp reaches 88.04%; commuting the x87
comparisons falls to 81.08% and increases reference debt.

The remaining eight candidate-only instructions are therefore a VC6 terminal
call-duplication choice, not a missing clamp, playback, or ABI relationship.
Native stores lower-bound zero and jumps to one shared scaled-playback tail;
every ordinary source form under the recovered build profile duplicates that
tail. The clear clamp remains canonical, with 19 clean references and the two
candidate-only duplicated call references explicitly unaudited.

## 2026-07-29 outer playback branch closure

A third recorded sweep moves direct playback ahead of attenuation so the
scaled call is structurally outside the attachment guard. Both an early-return
guard and an inverted `if/else` eliminate the duplicated candidate-only
references, but disturb the recovered native branch order and regress the
fuzzy result from 89.13% to 85.23%. A labeled direct tail is not valid C++ in
this function because its jump bypasses the initialized `Vector3` locals; VC6
correctly rejects it, so it supplies no missing source form.

The complete ledger now covers 20 unique variants: none improve, eight are
byte-identical, and twelve regress or fail to compile. Three consecutive
non-improving sweeps formally stall the scratch. The retained attachment-first
control flow preserves the stronger 299/335 fuzzy-byte result, 26-instruction
prefix, and all 19 aligned references. The lower-clamp call duplication remains
visible rather than being forced with an invalid jump or artificial side
effect.
