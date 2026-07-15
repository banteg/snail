# reset_tooltip @ 0x403be0

The exact embedded tooltip reset releases its borrowed widget through the
root-owned `GameRoot::border_manager`, clears the handle, and returns to state
1. The root-owner spelling remains exact at 16/16 instructions with two clean
operands.

## 2026-07-15 authored void switch and persisted ABI

Android preserves this owner as `cRToolTip::ReSet()` with the same state-2
idle reset and state-3 manager release. All Windows continuations discard EAX.
Expressing those two states as the natural authored switch recovers the real
void contract while remaining exact at 16/16 instructions with both operands
clean. The rollback-safe Binary Ninja replay and IDA now carry the typed
`FrontendWidgetTooltip*` member ABI directly.
