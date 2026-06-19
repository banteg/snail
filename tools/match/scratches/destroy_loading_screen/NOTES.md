# destroy_loading_screen

Tears down the loading-screen textures and preserves the measured loading
budget at `+0x08` in `data_4df9c4`.

The texture releases are COM-style calls: the texture pointer is pushed before
calling vtable slot `+0x08`, so the scratch keeps a narrow stdcall vtable view
instead of treating the release as a C++ thiscall.

Focused Wibo matches 100.00%, 15/15 instructions. The masked audit is clean
after curating `g_last_loading_budget`, `g_loading_background_texture`, and
`g_loading_bar_on_texture`. `initialize_loading_screen` proves that
`data_503288` is the `Sprites/Loading.tga` background texture and `data_503280`
is the `LoadingBarOn` progress-fill texture.
