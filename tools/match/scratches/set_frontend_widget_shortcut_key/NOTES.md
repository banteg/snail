# set_frontend_widget_shortcut_key

Small front-end widget mutator at 0x402790. Both BN and IDA decompiles show it
storing the shortcut key at +0x194, setting
`FRONTEND_WIDGET_FLAG_SHORTCUT_KEY_ENABLED` at +0x1a0, and leaving the updated
flags word in EAX incidentally. The interaction update independently consumes
that bit before comparing `shortcut_key_code`.

Exact match: 100.00%, 6/6 instructions, no masked operands.

Android preserves the authored member as `cRBorder::SetKeyLeft(int)`. Its body
has the same stores and no semantic return, while all five Windows callers
discard EAX. The shared member is therefore `void`; the exact 6/6 body is
unchanged.

2026-06-16 type consolidation: `FrontendWidget` now lives in
`frontend_widget.h` with the shortcut field, shared flags word, hide/unhide,
highlight, stack-layout, warning, tip, and row-event fields recovered from the
small exact widget helpers. This scratch remains exact.

## 2026-07-15 persisted member ABI

The rollback-safe Binary Ninja replay now applies and independently verifies
the authored `void cRBorder::SetKeyLeft(int)` contract directly. IDA carries
the same void `FrontendWidget*` receiver. The exact 6/6 scratch is unchanged;
the flags word left in EAX remains incidental rather than a synthetic result.
