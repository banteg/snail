# destroy_options_menu @ 0x41aee0

First scratch for options teardown.

- Unhides the shared border batch, kills Back, Music, Sounds, and Fullscreen in
  that order, then saves the 0xc4-byte `SnailMail.cfg` blob.
- Confirms the widget slot order recovered by `initialize_options_menu`.
- Focused Wibo result: 2026-06-18, 100.00%, 32/32 instructions, masked operands
  13 ok.

2026-07-11 cROptions ownership: Android and iOS name this lifecycle edge
`cROptions::UnInit()`. The exact Windows body now lives on the shared
0x24-byte `Options` owner.

2026-07-15 return-ownership closure: the sole call at `0x41b01f` immediately
reloads the game root. The `save_config_file` pointer previously forwarded in
EAX is therefore incidental, while the cross-port `cROptions::UnInit()` role
supplies the authored void contract. The corrected member remains exact at
32/32 instructions with all 13 operands clean.
