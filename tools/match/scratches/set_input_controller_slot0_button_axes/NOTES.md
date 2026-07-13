# set_input_controller_slot0_button_axes

The exact seven-instruction helper writes the first record in the recovered
two-slot, 0x38-stride input-controller bank at `0x50333c`.

2026-07-13 owner closure: the scratch now writes
`g_input_controller_slots[0]` through the complete shared
`InputControllerSlot` record rather than treating its three fields as lane
arrays. Codegen remains exact at 7/7 with three clean operands.
