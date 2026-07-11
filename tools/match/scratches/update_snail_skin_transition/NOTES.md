# update_snail_skin_transition @ 0x445f80

Exact 100.00% match, 25/25 instructions, with one clean masked operand.

This is the Windows `SnailSkin::update_snail_skin_transition`, authored as
`cRSnailSkin::AI`. The exact owner follows its borrowed `Snail*` backlink to
the snail visual, raises visual flag `0x8`, and writes the material index from
`slot_ids[selected_slot]`. If a timed change is active, it advances
`progress` by `progress_step` and restores slot zero after progress exceeds
one.

Android independently exports `cRSnailSkin::AI()` and has the same visual
flag/material writes and timer state machine. That cross-port body disproves
the old synthetic `PlayerRenderOwner`/`PlayerRenderModel` partial views.
