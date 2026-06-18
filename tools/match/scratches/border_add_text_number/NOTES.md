# border_add_text_number

First scratch for the frontend decimal text appender at `0x401030`.

The helper scans to the current end of `FrontendWidget::text_buffer`, appends a
positive decimal value with comma separators at millions/thousands boundaries,
and terminates the buffer. The zero input is a special two-byte append of
`"0\0"`.

Focused Wibo result: 100.00%, 68/68 instructions, full prefix, with no masked
operands.
