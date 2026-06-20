# destroy_high_score_screen

Small high-score screen teardown helper at 0x417220. BN shows it storing
`this+0x08` into the global selected-bank slot, killing all borders through
`game+0xb4c`, clearing the high-score entry pending byte at `game+0x30d`, and
zeroing the entry rank at `game+0x310`.

Focused match: 100.00%, 11/11 instructions, with five clean masked operands.

2026-06-20 header promotion: the scratch now includes `high_score_screen.h`
and uses the shared `HighScoreScreen::selected_bank` layout directly. This is
codegen neutral at the exact baseline and removes the last local
`HighScoreScreen` type-consolidation candidate.
