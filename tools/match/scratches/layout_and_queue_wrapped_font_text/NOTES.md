# FontType

`FontType(...)` owns the Windows routine at `0x44abe0`. The focused match is
exact: 155/155 instructions and 12 clean references.

It splits text on `>`, measures each line, optionally queues it through
`FontPrint`, and publishes the resulting bounds. Android and iOS both retain
the complete authored `Font.o` signature. Windows locally proves borrowed
output/color pointers and byte-sized boolean flags where mobile uses value
types. Live Windows analysis finds two frontend callers.

The directory and manifest retain `layout_and_queue_wrapped_font_text` as the
stable matcher identifier.
