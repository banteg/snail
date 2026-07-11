# Scratch status

`flush_row_event_display` @ 0x404830 is the Windows
`Completion::flush_row_event_display` / cross-port `cRCompletion::UnInit`.
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

The primary shared owner is now `Completion`, not a separate
`RowEventDisplayController`. Its 0x50-byte extent is the native
`Size of cRCompletion` ledger, and its fields overlay exactly with the result
screen initialized by `cRCompletion::Init`. The owner consolidation preserves
the exact 67/67 match with all 19 operands clean.

Rejected variants: duplicating the first widget kill across bonus/non-bonus
paths regressed to 79.17% by splitting the teardown flow; local-count and
pointer-to-field spellings for the bonus increment were neutral and still
lowered to `inc dword [mem]`.
