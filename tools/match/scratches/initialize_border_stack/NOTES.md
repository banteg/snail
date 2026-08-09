# initialize_border_stack @ 0x404350

Windows emits the exact two-store `cRBorderStack::Init()` body retained by the
iOS symbol corpus. The method resets only the current generation and borrowed
entry count; its `BorderManager* owner` link is assigned by the owning manager
initialization flow immediately afterward.

The same 14-byte Windows body is folded with
`cRFade::Init()`; the receiver callsites distinguish
the two authored methods without inventing separate machine-code ranges.

Promoting both hidden routines also replaces the old coarse `update_twinkle`
extent with three exact ranges. The generated status therefore stops charging
the 11-byte and 2-byte alignment gaps around this folded initializer as native
function bytes.

## 2026-08-09 primary cRFade folded alias

The stable `initialize_border_stack` matcher row now selects the authored
`cRFade::Init()` candidate and exports `?Init@cRFade@@QAEXXZ`. Native calls at
`0x40ad35` and `0x410277` pass `GameRoot +0x24` and the distinct border-stack
receiver respectively, proving that `cRFade::Init()` and
`cRBorderStack::Init()` intentionally share this address. The body remains
exact at 3/3 instructions and full prefix; both semantic aliases must remain
attached to the one Windows function.
