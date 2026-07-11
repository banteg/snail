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
four-byte owner lives at `SubgameRuntime +0x1260008`; the shared type is now
`Help`, and this initializer remains exact at 47/47.
