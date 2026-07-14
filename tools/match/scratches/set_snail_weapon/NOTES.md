# set_snail_weapon @ 0x445920

First source-shaped scratch for authored `cRSnail::SetWeapon(int)`.
This sits between `update_player_movement_flags` and
`PresentationAnimationChannel::set_weapon_animation`.

Recovered mapping:

- movement flag `1`: channel states `0, 0, 1`;
- `2`: `1, 1, 0`;
- `4`: `1, 1, 1`;
- `8`: `0, 2, 0`;
- `16`/`144`: `2, 2, 0`;
- `32`/`64`/`192`: `0, 0, 3`.

The default arm only assigns the first two target states from
`movement_flags`; the third target state is intentionally left as the
source-shaped local seen in both decompilers. In normal gameplay the producer
(`update_player_movement_flags`) only emits the handled values above.

Focused Wibo result: 68.29%, 244/248 candidate/target instructions, with 23
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
stack, and uses `ebx` as a channel pointer in the first transition block. VC6
currently keeps state1 in `ebx`, saves `ebp` only around the first block, and
therefore shifts later stack offsets. An explicit channel pointer scores higher
but materializes `weapon_channels[0]` before the movement dispatcher, unlike
native, so it is rejected. Do not add dummy aliasing or a volatile parameter
reload to force the remaining register ownership.

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
