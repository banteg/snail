# initialize_help_screen @ 0x416800

Help-screen initializer, reusing the main-menu music/backdrop setup with the
`Help.txt` landscape script and a single Back widget.

- Focused Wibo result: 100.00%, 47/47 instructions, 15 masked operands ok.
- Confirms the help controller is just one `FrontendWidget* back_button` at
  `+0x00`; `update_help_screen` shares the same layout.
- This is a second proof point that front-end music callsites push
  `(path, 0, g_blank_text)` even though `cache_music_file` only consumes
  `path`.

2026-07-11 cRHelp ownership: Android and iOS preserve this method as
`cRHelp::Init()`, paired with `AI()` and Android `UnInit()`. The exact
four-byte owner lives at `cRSubGame +0x1260008`; the shared type is now
`Help`, and this initializer remains exact at 47/47.

2026-07-13 root-owner cleanup: the landscape, backdrop, border pool, and Back
widget allocation now use canonical `GameRoot` members, removing the
screen-local `HelpBorderManager` pseudo-type. Output remains exact at 47/47
with all 15 operands clean.

2026-07-25 lifecycle replay closure: both decompiler lanes now persist the
authored `void cRHelp::Init()` ABI and exact four-byte `Help` owner. The
tracked output reaches `help->back_button` directly instead of treating the
owner as a loose `FrontendWidget**`; the replay rejects any `Help` size other
than `0x04`.

## 2026-08-12 authored method surface

The scratch now spells the exact member as `cRHelp::Init()` and exports
`?Init@cRHelp@@QAEXXZ`. Its sole live Windows caller passes the four-byte Help
owner at `cRSubGame + 0x1260008`; Android and iOS independently retain the same
symbol and body. Matching stays exact at 47/47 with all 15 operands clean.
