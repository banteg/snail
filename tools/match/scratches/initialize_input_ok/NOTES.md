# cRInputOK::Init @ 0x403560

Exact match: 100.00%, 23/23 instructions, with all five masked operands clean.

This lifecycle method allocates one BorderManager-owned OK border, binds it
beside the borrowed source border, initializes its presentation, and delegates
final placement to `cRInputOK::AI()`.

Android `Border.o` independently exports `cRInputOK::Init()` and preserves the
same lifecycle; no iOS export survives. Live Windows analysis confirms a void
thiscall whose sole caller is `cRBorder::InputTextInit`.

The stable matcher identity remains `initialize_input_ok`; source and
relocations now use the authored member name.
