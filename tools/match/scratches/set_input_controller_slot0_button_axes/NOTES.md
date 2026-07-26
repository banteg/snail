# set_input_controller_slot0_button_axes

The exact seven-instruction helper writes the first proved 0x20-byte payload in
the recovered two-slot, 0x38-stride input-controller bank at `0x50333c`.

2026-07-16 owner correction: the scratch now writes
`g_input_controller_slot0` through the proved `InputControllerSlot` payload
rather than treating its three fields as lane arrays. The trailing stride gap
is deliberately not part of that owner. Codegen remains exact at 7/7 with
three clean operands.

## 2026-07-26 mobile RShell owner and void ABI

Android and iOS retain this exact leaf as
`RShellInputRegisterKeyboard(int, float, float)` in `RShell.o`. Both bodies
store the button word and two axes into slot 0, in the same source-level
operation as Windows. The only Windows caller at `0x44baf2` immediately
executes `xor eax, eax`, overwriting the copied button residue. Removing the
synthetic return therefore recovers the authored void contract without
changing code generation: the natural source remains exact at 7/7
instructions with three clean operands.
