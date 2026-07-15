# update_input_ok @ 0x4034d0

Exact 32/32-instruction layout helper for the 0x24-byte `InputOkState` overlay
reused at `FrontendWidget::tooltip +0x1c`. The overlay borrows its source widget
at `+0x1c` and the BorderManager-owned OK widget at `+0x20`; it owns neither.

2026-07-16 void ABI recovery: the calls at `initialize_input_ok +0x3c` and
`border_input_text +0x1c` immediately enter epilogue or load the OK widget and
never consume EAX. A natural `void` transcription remains byte-identical with
no masked operands. The apparent source-widget result is final-load residue,
not an authored return value.
