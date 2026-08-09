# initialize_invincible_shell

Exact `cRInvincible::Init` helper at `0x444ac0`.

The receiver is the 0x98-byte `Invincible` visual embedded at
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

## 2026-07-18 durable lifecycle replay

The focused Snail-presentation replay now owns this initializer together with
`Start()` and `AI()` instead of merely size-checking the embedded `Invincible`
type. Binary Ninja and IDA both retain the exact `Invincible*` receiver, the
typed inactive state, and the adjacent root-owned `SnailSkin` handoff. The
matcher remains exact at 7/7 instructions with all three operands clean.

2026-07-28 mobile extent correction: both mobile ports end the corresponding
`cRInvincible` state/fade/spin owner before the cRSnail roll/release lanes at
`+0x1764`. Applying the same boundary to Windows yields the exact 0x98-byte
owner ending at `Snail +0x192c`; the adjacent roll pair and release gate are
now correctly direct `Snail` fields.

## 2026-08-09 primary cRInvincible ownership

The matcher now emits this initializer as `cRInvincible::Init()` and binds the
exact VC6 decorated symbol `?Init@cRInvincible@@QAEXXZ`; `Invincible` remains
a compatibility typedef for existing analysis replays. The live Windows view
confirms the void `thiscall` receiver and its sole direct call at `0x43aaaf`.
Android independently exports `cRInvincible::Init()` with the same state reset
and adjacent skin handoff, while iOS retains the authored owner and method.
The promotion is codegen-neutral: focused matching remains exact at 7/7
instructions with all three masked operands clean.
