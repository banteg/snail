# update_thanks_for_playing_screen

## 2026-09-11 inline-table certification

The unchanged source now compares at **100%**, 88/88 code
instructions plus 32 bytes of explicitly compared jump-table data. All
19 reference audits are clean and positional. Encoded-body proof is
**exact**.
This is corrected table-data accounting, not newly reconstructed source code.

The [proof report](../../inline-jump-table-proof-20260911.md) and
[receipt](../../inline-jump-table-proof-20260911.json) preserve the full source,
compiled-object identity, data entries, reference audits, comparison ranges, and
encoded-body evidence. Earlier measurements below are historical.

- Void thiscall state-machine updater for the thanks-for-playing screen.
- `message_progress` at `+0x0c` is an x87 float accumulator; the stale `eax`
  return is just compare/call residue.
- The click/key path only starts fade-out once message state is at least `2`
  and `GameRoot::fade.state` is idle.

2026-07-14 root graph closure: the controller skip bit is
`GameRoot::players[0].game_input->input.pressed_buttons`; fade reads and the
fade-out call use `GameRoot::fade`. Focused Wibo remains exact at 88/88
instructions with 19 clean operands.

2026-07-18 live-analysis lifecycle pass: both databases now apply the void
screen-controller receiver and recover `message_state`, `message_progress`,
`message_progress_step`, `message_widget`, and its embedded `text_buffer`
through the exact 0x14-byte controller. The updater calls the typed teardown
and widget visibility methods without raw receiver arithmetic; cross-tool
health checks preserve the complete state-machine owner graph.

2026-08-12 cRSplash ownership recovery: Android `cRSplash::AI()` at `0x6a900`
and iOS `cRSplash::AI()` at `0x63dac` preserve the Windows state machine's
primary-action/key-11 gate after state 2, fade-out handoff, and exact semantic
sequence of Challenge Mode, Time Trial, and continue prompts through alternating
hide/unhide states. The full-version mobile wording and leading exit flag are
platform/version differences; they identify the authored `cRSplash` owner but
do not transfer mobile offsets into the Windows layout.

The exact Windows object symbol `?AI@cRSplash@@QAEXXZ` now anchors the authored
`cRSplash::AI()` method spelling throughout the exact source; its fade-complete
edge calls the independently anchored `cRSplash::UnInit()` member.
