# update_input_ok @ 0x4034d0

Exact 32/32-instruction layout helper for the 0x24-byte `InputOkState` overlay
reused at `FrontendWidget::tooltip +0x1c`. The overlay borrows its source widget
at `+0x1c` and the BorderManager-owned OK widget at `+0x20`; it owns neither.

2026-07-16 void ABI recovery: the calls at `initialize_input_ok +0x3c` and
`border_input_text +0x1c` immediately enter epilogue or load the OK widget and
never consume EAX. A natural `void` transcription remains byte-identical with
no masked operands. The apparent source-widget result is final-load residue,
not an authored return value.

2026-07-27 mobile ownership: Android names the method `cRInputOK::AI()` and
retains the complete 0x24-byte owner, including the borrowed source and
BorderManager-owned OK widget pointers at `+0x1c/+0x20`. Its flag-4 branch
places the OK widget to the right using OK padding, source width/left/padding;
its flag-8 branch places it to the left using source left, OK width, source
padding, and twice the OK padding. Both branches copy top and the two layout
anchors exactly as Windows does. Android `cRInputOK::Init()` directly calls
`AI(this)`, independently proving the lifecycle pairing.

The manifest and matcher header now record the authored owner/method. No iOS
export survives, and no mobile `cRBorder` member offset was transferred.
