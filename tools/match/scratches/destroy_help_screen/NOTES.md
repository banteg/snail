# destroy_help_screen

Small Help-screen teardown helper at 0x4168c0. Both BN and IDA decompiles show
it forwarding to `kill_all_borders` on `GameRoot::border_manager`.

The helper is source-shaped as a `Help` member. The body ignores `this`
and still compiles to the same tailcall, while the member spelling is required
by `update_help_screen` so VC6 keeps the owner in `ecx` across the call.

Exact match: 100.00%, 3/3 instructions, with the root owner and
`kill_all_borders` operand resolved. The 2026-07-14 root-client pass removes
the raw root-offset reconstruction without changing codegen.

2026-07-11 cRHelp ownership: Android names this lifecycle edge
`cRHelp::UnInit()`. The exact 3/3 Windows body now lives on the shared
four-byte `Help` owner.
