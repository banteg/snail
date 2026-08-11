# set_snail_weapon @ 0x445920

First source-shaped scratch for authored `cRSnail::SetWeapon(int)`.
This sits between `set_subgoldy_shoot_flags` and
`Weapon::set_weapon_animation`.

Recovered mapping:

- movement flag `1`: channel states `0, 0, 1`;
- `2`: `1, 1, 0`;
- `4`: `1, 1, 1`;
- `8`: `0, 2, 0`;
- `16`/`144`: `2, 2, 0`;
- `32`/`64`/`192`: `0, 0, 3`.

The default arm only assigns the first two target states from
`shoot_flags`; the third target state is intentionally left as the
source-shaped local seen in both decompilers. In normal gameplay the producer
(`set_subgoldy_shoot_flags`) only emits the handled values above.

Focused Wibo result: 73.02%, 245/248 candidate/target instructions, with 23
clean masked operands. The calls hit channel bases `+0x64c`, `+0xa28`, and
`+0xe04`, and selected states at channel `+0x104` (`+0x750`, `+0xb2c`,
`+0xf08` in the presentation owner).

iOS and Android retain the same authored method on cRSnail. Android's complete
`cRSnail::SetWeapon(int)` body independently preserves all three state maps,
the selected-state tests, the same channel order, and the shared sound-25 tail.
Together with the three embedded channel bases, this makes the receiver the
exact shared `Snail` at `Player +0x2984`, not a freestanding weapon controller.

The selected-state and target-state branches are ordinary sparse `switch`es.
That source shape recovers the native decrement ladders throughout all three
channels and raises the focused score from 39.43%. The final channel is a
structured changed/unchanged branch rather than an early return: native places
the already-selected sound check after the update paths, and Android preserves
the same relationship.

Main residual: native keeps state0 in `edi`, state1 in `ebp`, state2 on the
stack, and uses `ebx` as a channel pointer in the first transition block. The
retained channel-0 reference makes VC6 reserve the same four saved-register
lanes but rotates their assignments: state0 moves to `ebp`, state1 stays in
`ebx`, and the channel receiver uses `edi`. Do not add dummy aliasing or a
volatile parameter reload to force the remaining register ownership.

The sparse movement dispatch names
`set_snail_weapon_movement_jump_table` at `0x445bf0` and
`set_snail_weapon_movement_lookup_table` at `0x445c0c`. The remaining masked
mismatch is the candidate's compiler-local jump-table symbol; all runtime
function/global operands are clean.

2026-07-14 animation-mode closure: each outgoing transition uses reverse-once,
each incoming transition uses once, and its queued base/draw followup preserves
the clip's current mode flags. Animation id `-1` is separately named as the
manager's hide-channel queue sentinel. Focused code remains byte-identical at
68.29%, 244/248, with the same 23 clean operands and one jump-table-only mask.

## 2026-07-19 channel-state lifetime closure

The live Windows stack/register ownership now matches the three-channel model
instead of leaking compiler reuse into the decompile. VC6 first spills the
`Snail*` receiver and then reuses that dead stack slot for channel 2's target
state. A guarded split keeps the prologue pointer separate and leaves the
default movement arm's channel-2 state honestly uninitialized, exactly as the
native body and Android control flow imply; it does not invent a fallback.

The overwritten low byte of `shoot_flags` is likewise three disjoint
per-channel `immediate` lifetimes, each with its own initial write, optional
clear, and SSA join. Binja now exposes all three target states, all three
selected states, the prior-channel change latch, and those transition flags
without pointer casts or parameter-byte aliases. The matcher source only gains
the same ownership names: focused code remains at the honest 68.29%, 244/248,
with 23 clean masks and the lone compiler-local jump-table mismatch.

## 2026-07-27 Android-authored channel guard

Android preserves channel 1 as the same ordinary
`selected_state != target_state` update guard used by the other channels.
The former Windows scratch expressed its unchanged path with a source-level
`goto`; replacing that decompiler-shaped jump with the cross-port structured
guard recovers the more plausible authored control flow.

This cleanup is byte-neutral at 68.29%, 244/248 instructions, with the same 23
clean masks and compiler-local jump-table mismatch. An explicit reusable
`Weapon*` was also tested because it could have explained native register
allocation, but it moved the receiver and target-state lifetimes away from the
binary and regressed to 64.91%; no synthetic pointer lifetime is retained.

## 2026-07-27 channel-0 receiver lifetime

Both mobile bodies keep every outgoing and incoming transition for the first
weapon lane on the same authored `cRWeapon` subobject. Windows independently
uses the one `Snail +0x64c` receiver throughout that changed-channel block.
Naming that borrowed subobject as a branch-scoped `Weapon&` therefore records
real ownership without changing the ABI, state map, calls, or exits.

The narrower lifetime improves focused Wibo from 68.29% (`244/248`) to 73.02%
(`245/248`) with all 23 runtime references still clean. It is distinct from
the rejected reusable pointer above: the reference cannot escape channel 0
and is not shared across the three channel blocks. Applying the same source
shape to channel 1 regresses to 67.35% by displacing the long-lived `Snail*`
receiver, so that probe is reverted. The remaining mask mismatch is still only
VC6's compiler-local sparse-switch table symbol.

## 2026-07-29 dispatch and owner residual boundary

Three recorded mutation sweeps cover 26 source-shaped variants around the
remaining Windows allocation gap. Parameter qualifiers, every target-state
declaration order, grouped declarations, selector copies and casts, default-arm
publication order, chained publication, and boolean initializer spelling all
compile byte-identically to the retained 73.02% source. Those 25 neutral
results show that the early `shoot_flags` ownership and state0/state1 register
rotation are not controlled by declaration order or an equivalent spelling of
the sparse movement switch.

The final probe moved the proved channel-0 borrow below the outgoing-state
switch, matching the point where native first keeps a receiver base live.
VC6 instead chose a substantially different family and regressed to 67.89%.
Together with the earlier 64.91% reusable-pointer and 67.35% channel-1 borrow
probes, this closes the plausible receiver-lifetime variants without retaining
synthetic aliasing.

The Android and iOS bodies still independently confirm the state map, all three
ordinary changed-state guards, channel order, and shared sound tail. Focused
Windows remains 73.02% (`245/248`) with all 23 runtime references clean. The
sole masked mismatch is still the candidate's compiler-local jump-table label;
the native/candidate comparison identifies it as a bounded VC6
register-allocation and private-label residual, not a semantic mismatch.

## 2026-07-30 translated jump-table proof

The matcher now verifies compiler-local jump tables by their ordered
destinations even when one uniform prologue-size difference shifts every case
block. It requires at least two distinct entries, proves every entry is an
instruction boundary on its own side, and still rejects permuted or
independently shifted tables.

The seven movement-dispatch entries are exactly such a table: native offsets
`36, 50, 67, 80, 107, 93, 124` correspond to candidate offsets
`38, 52, 69, 82, 109, 95, 126`, uniformly translated by two bytes. The retained
source stays at 73.02% (`245/248`), but the former private-label mismatch is now
content-proved. All 24 masked operands are audited and clean.

## 2026-08-12 recovery classification

The recovery is semantic-complete. The live Windows decompile and both mobile
bodies agree on the authored `cRSnail::SetWeapon(int)` owner, the complete
shoot-flag map, three embedded `Weapon` channels, outgoing and incoming
animation modes, selected-state publication, and sound-25 policy. The
deliberately undefined channel-2 default is also preserved rather than filled
with an invented value.

All 24 references are clean. The 73.02% residual is the compiler's rotation of
three target states, receiver, and transition-flag lifetimes across equivalent
channel blocks; it does not represent missing behavior or ownership. Probe
counts play no role in this classification.
