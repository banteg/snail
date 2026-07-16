# copy_active_input_controller_state @ 0x4320f0

Copies slot 0 or slot 1 from the global input-controller state into the
caller-owned runtime buffer. The copied lanes are button mask, analog axes,
authored pointer coordinates, the pointer-region value, and raw pointer x/y.

2026-07-16 owner correction: both branches now read separate 0x20-byte
`g_input_controller_slot0` and `g_input_controller_slot1` payloads. Their
0x38-byte spacing proves a shared selection stride, but not a contiguous
`InputControllerSlot[2]` owner: the second stride crosses an independently
authored RShell key-repeat global. The source remains exact at 52/52
instructions with all 16 global field operands resolved, proving every copied
payload field independently of the startup reset loop.

The button output now carries the shared `InputButtonFlag` type. This closes
the producer/copy/consumer path from the controller and pointer adapters into
`InputState::current_buttons` without changing code generation.
