# destroy_loading_screen

Tears down the loading-screen textures and preserves the measured loading
budget at `+0x08` in `data_4df9c4`.

The texture releases are COM-style calls: the texture pointer is pushed before
calling vtable slot `+0x08`. The shared `Direct3DTexture8` view now exposes that
stdcall COM `Release` slot directly instead of duplicating a scratch-local
interface and vtable.

Focused Wibo matches 100.00%, 15/15 instructions. The masked audit is clean
after curating `RuntimeConfig::last_loading_budget`, `g_loading_background_texture`, and
`g_loading_bar_on_texture`. `initialize_loading_screen` proves that
`data_503288` is the `Sprites/Loading.tga` background texture and `data_503280`
is the `LoadingBarOn` progress-fill texture.

2026-07-11 cRLoadingBar ownership: Android preserves the resource teardown as
`cRLoadingBar::UnInit()`. The exact 15/15 Windows member now lives on the
shared `LoadingBar g_loading_bar` owner.

2026-07-14 resource ownership: the two texture globals and two render-buffer
globals created and consumed by the loading lifecycle are declared alongside
`LoadingBar`. Initializer, updater, and teardown retain their existing focused
instruction streams and operand audits.

2026-07-15 return-ownership closure: startup invokes teardown at `0x406f8a`
and immediately reloads the root; it never consumes the final COM `Release`
value. The authored `cRLoadingBar::UnInit()` member is void, and dropping the
synthetic return preserves the exact 15/15 instructions and three operands.
