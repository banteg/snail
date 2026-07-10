# initialize_noop_renderable_bod @ 0x408040

Constructs a normal `RenderableBod`, then replaces its callback slot with the
shared `noop_runtime_ai` owner at 0x4972b0. `construct_game_runtime` uses this
helper for the passive child bodies at `Game +0x6fc/+0x848/+0x994`.

Focused Wibo is exact at 100.00%, 7/7 instructions, full prefix, and two clean
masked operands.
