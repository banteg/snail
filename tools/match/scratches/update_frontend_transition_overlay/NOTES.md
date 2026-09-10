# update_frontend_transition_overlay

## 2026-09-11 inline-table certification

The unchanged source now compares at **100%**, 63/63 code
instructions plus 20 bytes of explicitly compared jump-table data. All
9 reference audits are clean and positional. Encoded-body proof is
**exact**.
This is corrected table-data accounting, not newly reconstructed source code.

The [proof report](../../inline-jump-table-proof-20260911.md) and
[receipt](../../inline-jump-table-proof-20260911.json) preserve the full source,
compiled-object identity, data entries, reference audits, comparison ranges, and
encoded-body evidence. Earlier measurements below are historical.

Frontend fade overlay state machine on `g_game_base + 0x24`, independently
identified by Android as the authored `cRFade::AI()` owner.

- `state == 0`: idle, returns before queueing the overlay quad.
- `state == 1`: fade out to transparent, then idle.
- `state == 2`: fade in to opaque, then hold.
- `state == 3`: advance the hold timer.
- `state == 4`: hand back to fade-out.

The final draw guard is `alpha > 0.01f`, matching the same overlay-quad
threshold used by `draw_frontend_overlay_color_lerp`.

Exact match: 100.00%, 62/62 instructions, with 9 masked operands OK and no
unresolved or mismatched operands. The jump-table displacement is audited
through `update_frontend_transition_overlay_jump_table` at `0x40acd4`.

Android preserves the same float alpha at `+0x04`, state-1/state-2 `1/18`
step, and full-screen black draw while using port-specific handoff gates.
iOS and Android also retain `cRFade::Start(void (*)())`; its store proves the
Windows `+0x10` word is a completion callback, not a hold-state integer. All
six Windows Start callsites pass null, and Windows externally polls state 4.

## 2026-08-09 primary cRFade::AI promotion

The exact callback is now defined as `cRFade::AI()` and exports
`?AI@cRFade@@QAEXXZ`. Its Windows state machine still never reads or invokes
the stored completion callback; that dead lane is preserved as layout evidence
rather than assigned invented behavior. The existing jump-table reference and
all nine masked operands remain clean at 62/62 instructions and full prefix.
