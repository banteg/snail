# border_input_text_init

First typed scratch for the frontend text-input initializer at `0x403410`.

The native function copies the initial text to the secondary buffer at
`FrontendWidget +0x6cc`, counts the existing `text_buffer` length while
incrementing the typed `input_length` and `input_cursor` fields, appends the
visible cursor marker, initializes the input flags/timing fields, lays the
widget out, and conditionally initializes the embedded OK-button state at
`this +0x2a8`. The owned editor state spans `+0x6fc..+0x714`; the secondary
copy is expressed as `text_buffer + 0x400`, preserving its relationship to the
primary text buffer instead of inventing another owner.

Focused Wibo result: 100.00%, 46/46 instructions, full prefix, with three
clean masked operands. The typed ownership rewrite remains byte-identical.
