# border_input_text_init

First typed scratch for the frontend text-input initializer at `0x403410`.

The native function copies the initial text to the secondary buffer at
`FrontendWidget +0x6cc`, counts the existing `text_buffer` length while
incrementing the paired input counters at `+0x710` and `+0x6fc`, appends the
visible cursor marker, initializes the input flags/timing fields, lays the
widget out, and conditionally initializes the embedded OK-button state at
`this +0x2a8`.

Focused Wibo result: 100.00%, 46/46 instructions, full prefix, with three
clean masked operands.
