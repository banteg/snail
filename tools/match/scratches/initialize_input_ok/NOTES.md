# initialize_input_ok @ 0x403560

Exact 23/23-instruction initializer for the reused 0x24-byte `cRInputOK`
overlay. Android retains the authored `cRInputOK::Init()` vocabulary. The
member allocates one BorderManager-owned OK widget, stores that handle beside
the borrowed source widget, initializes its presentation, and delegates final
placement to `update_input_ok`.

2026-07-16 void ABI recovery: the only native caller at
`border_input_text_init +0xae` enters its epilogue immediately after the call.
The natural `void` source remains exact with all five masked operands clean;
the former result was only residue from the nested void layout call.
