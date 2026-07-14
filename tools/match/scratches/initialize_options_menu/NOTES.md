# initialize_options_menu @ 0x41ace0

First scratch for the options screen constructor.

- Builds the fullscreen, sounds-volume, music-volume, and Back widgets.
- Confirms `Options` slots: previous frontend state at `+0x00`, active byte
  at `+0x04`, widget pointers at `+0x10..+0x1c`, and the sample-volume
  snapshot at `+0x20`.
- The fullscreen widget is initialized with shared blank text `g_blank_text`;
  `update_options_menu` writes the live On/Off label every frame.
- The slider widgets use the first virtual widget callback after seeding
  `slider_value` and `slider_target_value`; spelling this as the named layout
  helper emits the wrong direct call.
- Focused Wibo result: 2026-06-18, 100.00%, 127/127 instructions, masked
  operands 32 ok.

2026-07-11 cROptions ownership: Android and iOS preserve this exact lifecycle
method as `cROptions::Init()`. The shared root owner is now `Options`; its
fields close the exact 0x24-byte interval from `GameRoot +0x4f388` to the
adjacent `Exit`, and the initializer remains exact at 127/127.

2026-07-14 root-client consolidation: the initializer now names both
`GameRoot::border_manager` and `GameRoot::frontend_link_latch`; the latter is
the byte formerly reached as root +0x568. The complete owner graph remains
exact at 127/127 instructions with 32 clean operands.
