# initialize_border_stack @ 0x404350

Windows emits the exact two-store `cRBorderStack::Init()` body retained by the
iOS symbol corpus. The method resets only the current generation and borrowed
entry count; its `BorderManager* owner` link is assigned by the owning manager
initialization flow immediately afterward.

The same 14-byte Windows body is folded with
`FrontendFade::initialize_frontend_fade`; the receiver callsites distinguish
the two authored methods without inventing separate machine-code ranges.

Promoting both hidden routines also replaces the old coarse `update_twinkle`
extent with three exact ranges. The generated status therefore stops charging
the 11-byte and 2-byte alignment gaps around this folded initializer as native
function bytes.
