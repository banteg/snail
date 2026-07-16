# set_input_controller_slot0_button_axes

The exact seven-instruction helper writes the first proved 0x20-byte payload in
the recovered two-slot, 0x38-stride input-controller bank at `0x50333c`.

2026-07-16 owner correction: the scratch now writes
`g_input_controller_slot0` through the proved `InputControllerSlot` payload
rather than treating its three fields as lane arrays. The trailing stride gap
is deliberately not part of that owner. Codegen remains exact at 7/7 with
three clean operands.
