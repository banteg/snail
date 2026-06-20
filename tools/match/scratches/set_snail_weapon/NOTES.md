# set_snail_weapon @ 0x445920

First source-shaped scratch for the player presentation weapon dispatcher.
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

Focused Wibo result: 39.43%, 244/248 candidate/target instructions. This is a
semantic/relationship scratch, not a near-final match. The layout is useful:
the calls hit channel bases `+0x64c`, `+0xa28`, and `+0xe04`, and selected
states at channel `+0x104` (`+0x750`, `+0xb2c`, `+0xf08` in the presentation
owner).

Main residual: native keeps state0 in `edi`, state1 in `ebp`, state2 on the
stack, and uses `ebx` as a channel pointer in the first transition block. VC6
currently keeps state1 in `ebx`, saves `ebp` only around the first block, and
therefore shifts most later blocks. The source has been reshaped to the native
decrement/goto ladders; do not add dummy aliasing or asm to force the remaining
register ownership.

2026-06-20 lookup-table audit: the sparse movement dispatch now names
`set_snail_weapon_movement_jump_table` at `0x445bf0` and
`set_snail_weapon_movement_lookup_table` at `0x445c0c`. Focused Wibo remains
`39.43%`; masked audit is now `15 ok / 0 unresolved / 2 mismatch`, so the
former lookup-table relocation is clean and the remaining debt is the existing
register/layout mismatch.
