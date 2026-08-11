# set_snail_jetpack @ 0x445860

First tracked scratch for the jetpack presentation dispatcher. The important
struct correction is that this is authored `cRSnail::SetJetPack(int)`:
the known callers pass `g_game_base + 0x432700`, which is `Player +0x2984`, not
a separate global presentation controller.

The scratch now uses the shared exact `Snail` layout directly; the
older local `+0x11e0` controller view has been removed.

Recovered behavior:

- input state `0` maps to channel state `0`;
- input state `1` maps to channel state `4`;
- any other input is passed through as the target state;
- leaving selected state `4` queues animation `1` in reverse-once mode and
  plays sound `26`;
- entering target state `4` plays animation `1`, queues animation `0`, plays
  sound `16`, and stores selected state `4`;
- entering target state `0` clears the channel with animation `-1`.

Focused Wibo result after the shared selected-state tail: 86.18%, 61/62
candidate/target instructions. The switch spelling for the input-state mapping
is still better than the direct `if` ladder, while sharing the final
`selected_state = target_state` store across the enter-state-4 and clear paths
removes the old constant-folded state-4 return tail.

The remaining drift is register ownership. Native loads `state` before saving
registers, keeps `this` in `edi`, keeps `target_state` in `ebx`, and only saves
`esi` around the enter-state-4 block. The retained source still saves `ebx`
before loading `state`, but now preserves the native shared tail shape. Tested
variants: initializing `target_state = state` recovers the first argument load
but regresses to 66.67% by losing the better switch/register split; flattening
the tail as `if target == 4 else if target == 0` reaches 82.93%; checking the
clear path first regresses to 71.54%. Keep the nested shared-store tail unless
a real VC6 source idiom explains the remaining prologue split.

2026-06-21 mapping follow-up: removing the `register` hint and switching
directly on `state` are both codegen-neutral at 86.18% and keep the first
mismatch at the pre-save argument load. Rewriting the mapping as an `if` ladder
recovers only a three-instruction prefix and regresses to 81.30%. The current
switch remains the best mapping shape even though it saves `ebx` before loading
the argument.

2026-07-14 authored-call contract: Android names the shared callee
`void cRWeapon::SetAnimation(int, bool, int)`. Modeling `immediate` as `bool`
preserves the existing 86.18% result while removing the obsolete integer-return
and byte-flag contract from this caller.

2026-07-14 animation-mode closure: the third argument is now tied to the
parser/updater-owned mode bits. State `4` selects the once mode, leaving it uses
reverse-once, and queued followups preserve the clip's existing flags. The
equal-valued animation-id `-1` remains a separate hide-channel sentinel.

2026-07-15 cRWeapon owner closure: the embedded `+0x11e0` jetpack channel is
now the exact `Weapon` (`cRWeapon`) owner shared with the three weapon channels.
Android preserves `cRWeapon::SetAnimation`, `cRWeapon::AI`, RTTI, and the same
Snail-to-Weapon call relationship; Windows independently constructs four
0x3dc-byte children and installs one callback slot on all four. This retires the
synthetic presentation-channel type without changing focused codegen.

## 2026-07-26 analyzer replay closure

The verified Android and iOS `cRSnail::SetJetPack(int)` bodies now drive the
focused Binary Ninja and IDA 9.4 replay lanes. Both retain the exact `Snail*`
receiver and embedded `Weapon jetpack_channel`; Binary Ninja additionally
guards the `target_state` and `selected_state` register lifetimes, while IDA
guards those plus the stack-reused `transition_immediate` byte.

Tracked decompile health checks reject a return to the old `mode_flags`,
`v3`, or `statea` views. Focused Windows matching is intentionally unchanged at
86.18%, 61/62 instructions, with eight clean masked operands: the remaining
gap is still the native prologue/register schedule, not missing ownership.

## 2026-07-29 bounded state-lifetime audit

Three recorded mutation sweeps evaluated 51 source variants around the last
native-only instruction gap:

- mapping forms varied switch, if, ternary, scalar type, and source expression;
- declaration and scope forms varied the `state` and `target_state` lifetimes;
- a cross-product varied the mapping together with transition-control spelling.

None improved the canonical 86.18% result: 21 variants were neutral and 30
regressed. The native load-before-save prologue and default-path reload remain
unexplained by ordinary source spelling. That history records the tested source
shapes without limiting future evidence about the source type, translation-unit
context, or compiler relationship.

## 2026-08-12 recovery classification

The recovery is semantic-complete. The live Windows decompile and verified
Android/iOS `cRSnail::SetJetPack(int)` bodies establish the Snail owner,
embedded jetpack Weapon, input-to-channel state map, outgoing and incoming
animations, transition immediacy, both sound effects, hide path, and shared
selected-state publication. All eight references are clean.

The single missing candidate instruction is the native load of `state` before
saved-register setup; the candidate reloads the same default value after the
switch. The wider 86.18% delta is the resulting register allocation, not a
missing branch, field, or owner.
