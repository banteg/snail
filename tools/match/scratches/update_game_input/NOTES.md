# update_game_input @ 0x40aab0

Exact Windows `cRGameInput::AI()` at 30/30 instructions with all three masked
references clean. Android and iOS independently preserve the owner and method
in `Game.o`.

`construct_game_runtime` creates two consecutive 0x70-byte owners at
`GameRoot +0x44` and installs the callback entry at `0x4972f0` on each. When
the root sampling gate is live, AI copies the selected controller's buttons,
axes, pointer values, and authored coordinates into its embedded `cRInput`,
then invokes the void edge updater. Each matching player borrows one of these
root-owned records; no separate gameplay input buffer exists.
