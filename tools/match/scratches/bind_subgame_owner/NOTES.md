# bind_subgame_owner @ 0x433fc0

Stores the root-owned `SubgameRuntime` pointer (`GameRoot +0x74618`) in the
receiver's first word and returns it.

The two native callsites in `initialize_game_assets_and_world` pass
`ChallengeSetupScreen` at subgame `+0x125ffe0` and `ThanksScreen` at subgame
`+0x126000c`. The old `open_thanks_screen` name was therefore too specific:
this is a folded field-first owner-binding helper, not proof that the two
controllers share a C++ base or that either screen opens here.

Focused match: 100%, 4/4 instructions, with one clean masked operand.
