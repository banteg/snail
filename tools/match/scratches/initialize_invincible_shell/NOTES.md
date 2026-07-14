# initialize_invincible_shell

Exact `cRInvincible::Init` helper at `0x444ac0`.

The receiver is the 0xa4-byte `Invincible` visual embedded at
`Snail +0x1894` (`Player +0x4218`). It clears the
owner's state and restores snail skin slot zero through the adjacent
exact `cRSnailSkin` owner.

Android independently exports `cRInvincible::Init`, calls it from
`cRSubGoldy::Init`, and performs the same state reset and skin change. iOS v1.9
exports the same authored method. Android's member offsets are twelve bytes
earlier because its renderable base is smaller; the state-machine member order
and behavior agree.

Focused Wibo: exact 100.00%, 7/7 instructions, with three clean masked
operands.

2026-07-14 sibling-owner closure: the skin reset now follows the owned
`Player::presentation.snail_skin` path instead of root `+0x434038`. The helper
remains exact at 7/7 with all three operands clean.

2026-07-14 renderable inheritance closure: `Invincible` now inherits its
complete `RenderableBod` prefix, including the live shell transform at `+0x38`,
instead of repeating that matrix after a `BodBase`. Focused Wibo remains exact
at 7/7 with all three operands clean.

## 2026-07-14 lifecycle state ownership

Initialization now names state zero as `INVINCIBLE_STATE_INACTIVE`. Live
Binary Ninja field xrefs show that only `cRInvincible::{Init,Start,AI}` access
the exact four-byte state at owner `+0x80`, and Android confirms the same
four-state graph. Focused output remains exact at 7/7 instructions with all
three operands clean.
