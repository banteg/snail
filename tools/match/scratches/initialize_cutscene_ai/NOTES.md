# initialize_cutscene_ai

Exact `cRCutScene::Init` helper at `0x446130`. The Windows function name stays
stable for the match harness.

The receiver is the exact 0x5c-byte `CutScene` embedded at
`Snail +0x1958` (`Player +0x42dc`). The helper writes
the parent presentation and Player backlinks at `+0/+4` and clears state at
`+0x0c`.

Android exports `cRCutScene::Init`, is called from `cRSubGoldy::Init`, and
performs the same four stores at identical offsets. iOS v1.9 exposes
`cRCutScene::Init(cRSubGoldy*)`; the later build passes the Player explicitly
where Windows and Android recover it from the runtime singleton.

The source return is `void`. Windows happens to leave the presentation pointer
in `eax`, while Android leaves the CutScene receiver in `r0`; callers ignore
both. Those incompatible incidental register values rule out the old integer
return interpretation.

Focused Wibo remains exact: 100.00%, 8/8 instructions, with four clean masked
operands.

2026-07-14 parent-owner closure: the initializer now borrows
`cRSubGame::player` and its owned `Player::presentation` directly instead
of rebuilding root `+0x42fd7c/+0x432700`. It stays exact at 8/8 with all four
operands clean.

## 2026-07-25 IDA nested presentation replay

The Player backlink at `0x446142` adds root `+0x42fd7c`; the adjacent
presentation store uses root `+0x432700`, which closes as
`Player + offsetof(Player, presentation) +0x2984`. Removing only the false
`g_player_block` operand is sufficient for a fresh Hex-Rays pass to recover
both `&g_game_base->subgame.player` and its owned `presentation`. This agrees
with the cross-port constructor evidence and leaves the exact 8/8 source
untouched.

## 2026-07-25 paired owner canary

Fresh Binary Ninja analysis now closes the same two constants through the
imported `GameRoot -> cRSubGame -> Player` graph without a local-variable
override: the first store borrows `Player::presentation`, and the final store
borrows the enclosing `Player`. The tracked BN artifact had simply preceded
that analysis state.

The refreshed artifact and a paired health canary now reject the old
`g_game_base[0x432700]` / `g_game_base[0x42fd7c]` byte-array rendering. No
matcher source or database annotation changed; the exact 8/8 match remains the
evidence boundary.
