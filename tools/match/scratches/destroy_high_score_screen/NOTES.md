# destroy_high_score_screen

Small high-score screen teardown helper at 0x417220. BN shows it storing
`this+0x08` into the global selected-bank slot, killing all borders through
`game+0xb4c`, clearing the high-score entry pending byte at `game+0x30d`, and
zeroing the entry rank at `game+0x310`.

Focused match: 100.00%, 11/11 instructions, with five clean masked operands.

2026-06-20 header promotion: the scratch now includes the shared high-score
owner header and uses `HighScore::selected_bank` directly. This is
codegen neutral at the exact baseline and removes the last local
high-score owner type-consolidation candidate.

2026-07-10 root-owner promotion: border teardown now uses the owned
`GameRoot::border_manager`, and the pending/rank clears use
`GamePlayer[0]`. The typed ownership stays exact at 11/11.

2026-07-11 cRHighScore ownership: Android preserves this exact lifecycle role
as `cRHighScore::UnInit()`. The 0xd0-byte root-owned controller is now named
`HighScore`; this exact 11/11 teardown remains distinct from `SubHighScore`.

2026-07-14 return-contract audit: Android's direct AI tail branch and all six
Windows callers establish a side-effect-only `void` member. Removing the
synthetic `return 0` preserves the exact 11/11 body and five clean operands;
Binary Ninja records the authored prototype as explicitly deferred because
live analysis restores its stale scalar inference.
