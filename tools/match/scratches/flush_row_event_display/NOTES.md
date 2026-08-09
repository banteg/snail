# Scratch status

`flush_row_event_display` @ 0x404830 is the Windows
`cRCompletion::UnInit` (stable matcher key `flush_row_event_display`).
It forces the parcel-display phase
to its completed state: it pays out any remaining parcel deliveries, applies
the optional bonus, kills all five row-event widgets, restores the display
token, and clears the controller state.

Current result: 100.00%, 67/67 instructions, full prefix.

The match became exact after correcting the source shape for the
post-payout delivery-count bump: the optional bonus branch only pays the bonus
score, then `delivered_parcel_count` increments once unconditionally before the
widget teardown. The controller state clear also belongs at the shared tail,
outside the active-state branch.

The primary shared owner is now `cRCompletion`, not a separate
`RowEventDisplayController`. Its 0x50-byte extent is the native
`Size of cRCompletion` ledger, and its fields overlay exactly with the result
screen initialized by `cRCompletion::Init`. The owner consolidation preserves
the exact 67/67 match with all 19 operands clean.

Rejected variants: duplicating the first widget kill across bonus/non-bonus
paths regressed to 79.17% by splitting the teardown flow; local-count and
pointer-to-field spellings for the bonus increment were neutral and still
lowered to `inc dword [mem]`.

2026-07-14 root-client consolidation: score awards and restoration now follow
`GameRoot::subgame.player`, proving root +0x430060 is
`Player::total_score`; all five widget releases use the root-owned
`BorderManager`. The complete graph remains exact at 67/67 instructions with
19 clean operands.

## 2026-07-14 five-widget role closure

Teardown now releases the same five semantic fields proven by Init: the title,
delivered count, bonus icon, bonus summary, and continue prompt. This removes
the last generic widget aliases from the lifecycle while remaining exact at
67/67 instructions with all 19 operands clean.

## 2026-07-14 completion lifecycle ownership

Teardown now tests and restores `COMPLETION_STATE_INACTIVE` explicitly. This
closes the lifecycle against Init and every AI terminal path while preserving
the exact 67/67 instruction body and all 19 clean operands.

## 2026-07-25 IDA Player-root replay

The two score calls at `0x404853` and `0x404881` add the same root displacement
`0x42fd7c`, exactly
`GameRoot::subgame +0x74618 + cRSubGame::player +0x3bb764`. IDA had
mistaken that displacement for the standalone `g_player_block` evidence
symbol. Exact operand normalization now agrees with Binary Ninja and the
matcher source on `&g_game_base->subgame.player`; the exact 67/67 result is
unchanged.

## 2026-08-09 primary cRCompletion ownership

The matcher now emits this exact 67/67 teardown as
`cRCompletion::UnInit()` and binds the VC6 decorated symbol
`?UnInit@cRCompletion@@QAEXXZ`. `Completion` remains a compatibility typedef
for analysis and caller migration. Android and iOS independently retain
`_ZN12cRCompletion6UnInitEv` on the same authored lifecycle owner; the Windows
five-widget teardown and 0x50-byte layout remain the local ABI boundary.
