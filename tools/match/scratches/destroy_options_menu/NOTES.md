# destroy_options_menu @ 0x41aee0

First scratch for options teardown.

- Unhides the shared border batch, kills Back, Music, Sounds, and Fullscreen in
  that order, then saves the 0xc4-byte `SnailMail.cfg` blob.
- Confirms the widget slot order recovered by `initialize_options_menu`.
- Focused Wibo result: 2026-06-18, 100.00%, 32/32 instructions, masked operands
  13 ok.
