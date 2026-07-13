# copy_active_input_controller_state @ 0x4320f0

Copies slot 0 or slot 1 from the global input-controller state into the
caller-owned runtime buffer. The copied lanes are button mask, analog axes,
authored pointer coordinates, the pointer-region value, and raw pointer x/y.

2026-07-13 owner closure: both branches now read the fixed
`g_input_controller_slots[2]` array through complete `InputControllerSlot`
records. The source remains exact at 52/52 instructions with all 16 global
field operands resolved, proving the array layout independently of the startup
reset loop.
