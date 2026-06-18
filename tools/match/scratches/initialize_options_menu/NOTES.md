# initialize_options_menu @ 0x41ace0

First scratch for the options screen constructor.

- Builds the fullscreen, sounds-volume, music-volume, and Back widgets.
- Confirms `OptionsMenu` slots: previous frontend state at `+0x00`, active byte
  at `+0x04`, widget pointers at `+0x10..+0x1c`, and the sample-volume
  snapshot at `+0x20`.
- The fullscreen widget is initialized with shared blank text `g_blank_text`;
  `update_options_menu` writes the live On/Off label every frame.
- The slider widgets use the first virtual widget callback after seeding
  `slider_value` and `slider_target_value`; spelling this as the named layout
  helper emits the wrong direct call.
- Focused Wibo result: 2026-06-18, 100.00%, 127/127 instructions, masked
  operands 32 ok.
