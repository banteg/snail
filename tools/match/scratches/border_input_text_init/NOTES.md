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

## 2026-07-14 authored API and editor-tail closure

Android preserves this member as
`cRBorder::InputTextInit(int, char*, int)` and performs the same complete
editor initialization before calling `RePosition()` and, conditionally,
`cRInputOK::Init()`. Both Windows callers discard EAX; Android likewise
returns with whichever nested void helper last ran. The authored contract is
therefore `void`, not a widget pointer synthesized from incidental return
register contents. Correcting the contract remains exact at 46/46
instructions with all three operands clean.

The exact body also closes the formerly padded tail as cursor index,
visibility, blink progress/step, input flags, current length, and capacity at
`+0x6fc..+0x714`. `border_input_text` independently consumes the same seven
fields.
