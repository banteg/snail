# bind_subgame_owner @ 0x433fc0

Stores the root-owned `cRSubGame` pointer (`GameRoot +0x74618`) in the
receiver's first word and returns it.

The two native callsites in `initialize_game_assets_and_world` pass
`GUI` at subgame `+0x125ffe0` and `cRSplash` at subgame
`+0x126000c`. The old `open_thanks_screen` name was therefore too specific:
this is a folded field-first owner-binding helper, not proof that the two
controllers share a C++ base or that either screen opens here.

Focused match: 100%, 4/4 instructions, with one clean masked operand.

For the GUI callsite, iOS and Android identify this one-store operation as
`cRGUI::Open()`. The generic Windows name remains intentional because the
linker folded the byte-identical cRSplash owner bind into the same address.

2026-07-14 root-owner closure: the folded helper now borrows
`&g_game->subgame` directly. It remains exact at 4/4 with its one operand clean.

2026-07-25 paired replay: Binary Ninja and IDA now explicitly reanalyze this
folded helper after their narrow owner/type syncs. Both tracked decompiles
retain the canonical `&g_game_base->subgame` borrow; paired health checks reject
the old raw `+0x74618`/`476696` forms. Matching source remains unchanged.

2026-08-12 folded cRSplash proof: Android and iOS independently export both
`cRGUI::Open()` and `cRSplash::Open()`. Windows has two callsites to the same
four-instruction body, passing the embedded GUI and cRSplash owners
respectively, so the linker folded the byte-identical authored Open methods.
The stable generic Windows symbol stays in place; `cRSplash_Open` is recorded
as an alias rather than inventing inheritance between the controllers.
