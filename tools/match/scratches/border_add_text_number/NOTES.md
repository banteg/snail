# border_add_text_number

First scratch for the frontend decimal text appender at `0x401030`.

The helper scans to the current end of `FrontendWidget::text_buffer`, appends a
positive decimal value with comma separators at millions/thousands boundaries,
and terminates the buffer. The zero input is a special two-byte append of
`"0\0"`.

Focused Wibo result: 100.00%, 68/68 instructions, full prefix, with no masked
operands.

## 2026-07-26 cross-port owner

Android and iOS both retain the exact-demangled
`cRBorder::AddTextNumber(int)` method. Their bodies preserve the Windows
algorithm: find the end of the owned text buffer, special-case zero, consume
decimal divisors from 10,000,000 through 1, insert commas at the million and
thousand boundaries, and terminate the append.

The mobile text buffer begins at `cRBorder +0x2c4`; Windows uses the recovered
`FrontendWidget::text_buffer` at `+0x2cc`. Only the authored owner and algorithm
transfer. The exact Windows member remains 68/68 with no masked operands.
