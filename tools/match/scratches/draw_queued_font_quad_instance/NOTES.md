# draw_queued_font_quad_instance

Initial scratch for the explicit queued-quad draw forwarder at `0x44a6d0`.

Wibo result: exact 100%, 41/41 instructions, masked operands 2 ok.

Recovered relationships:

- Reads the texture id at `cFontPrintBuffer +0x50` through the shared sprite
  texture table (`g_sprite_texture_table`, data `0x78ff90`).
- Forwards all four corner coordinate pairs (`+0x04..+0x2c`), size
  (`+0x54/+0x58`), UV bounds (`+0x5c..+0x68`), `tColour` pointer
  (`+0x6c`), integer blend mode (`+0x7c`), and float rotation (`+0x80`) into
  `draw_textured_quad_immediate`.

The Android export `OSDPrintReal(cFontPrintBuffer*)` independently proves the
authored record name and pointer contract. Its result is incidental: the only
Windows caller discards EAX, so the recovered source contract is `void` while
remaining byte-identical.

## 2026-07-14 font queue ownership closure

The Binary Ninja and IDA owners now agree on the full `cFontPrintBuffer`
forwarder, including the previously ambiguous tail: `+0x7c` is the integer
`blend_mode` consumed by the immediate renderer and `+0x80` is its float
`rotation`. This correction removes the old integer bit-cast interpretation
from IDA and preserves the exact `41/41` matcher result.

## 2026-07-25 cross-port corner-vector cadence

The symbol-rich iOS 1.5 and 1.9 binaries and the unstripped Android binary all
preserve `OSDPrintReal(cFontPrintBuffer*)`, the `0x84` record stride, and the
same coordinate loads at `+0x04/+0x08`, `+0x10/+0x14`, `+0x1c/+0x20`, and
`+0x28/+0x2c`. Android additionally exports `FontPrintBuffer` with exact size
`0x10800`, proving 512 mobile records.

Each x/y pair occupies the first two lanes of a 12-byte engine-vector cadence.
The dormant third lanes at `+0x0c/+0x18/+0x24/+0x30` are therefore recorded as
float `z0..z3`, not integer unknowns. No 2D producer or renderer reads or writes
those z lanes, so the matcher body remains unchanged and the exact `41/41`
forwarder is not shaped around them.
