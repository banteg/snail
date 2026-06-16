# set_frontend_widget_shortcut_key

Small front-end widget mutator at 0x402790. Both BN and IDA decompiles show it
storing the shortcut key at +0x194, setting widget flag 0x80000 at +0x1a0, and
returning the updated flags word.

Exact match: 100.00%, 6/6 instructions, no masked operands.

2026-06-16 type consolidation: `FrontendWidget` now lives in
`frontend_widget.h` with the shortcut field, shared flags word, hide/unhide,
highlight, stack-layout, warning, tip, and row-event fields recovered from the
small exact widget helpers. This scratch remains exact.
