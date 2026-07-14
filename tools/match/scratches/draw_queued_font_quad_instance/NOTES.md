# draw_queued_font_quad_instance

Initial scratch for the explicit queued-quad draw forwarder at `0x44a6d0`.

Wibo result: exact 100%, 41/41 instructions, masked operands 2 ok.

Recovered relationships:

- Reads the texture id at `cFontPrintBuffer +0x50` through the shared sprite
  texture table (`g_sprite_texture_table`, data `0x78ff90`).
- Forwards all four corner coordinate pairs (`+0x04..+0x2c`), size
  (`+0x54/+0x58`), UV bounds (`+0x5c..+0x68`), `tColour` pointer
  (`+0x6c`), layer (`+0x7c`), and blend (`+0x80`) into
  `draw_textured_quad_immediate`.

The Android export `OSDPrintReal(cFontPrintBuffer*)` independently proves the
authored record name and pointer contract. Its result is incidental: the only
Windows caller discards EAX, so the recovered source contract is `void` while
remaining byte-identical.
