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

## 2026-07-26 mobile RShell owner, boundary, and void ABI

Android and iOS retain this API as `RShellInputRetrieve(...)` in `RShell.o`.
All three ports select one slot and copy the same eight lanes in the same
order: buttons, axes, authored coordinates, pointer value, and raw pointer
coordinates. Mobile then exposes two additional mouse-extra floats and uses a
`0x40` slot stride. Windows has neither those two output parameters nor any
xrefs in the corresponding gap after its proved `0x20` payload, so the mobile
tail must not be projected into the Windows layout.

The sole Windows caller at `0x40aae6` adjusts the stack and calls
`update_input` without consuming EAX. Both mobile ports declare the routine
void. Removing the synthetic `out_pointer_value` return keeps the Windows
scratch exact at 52/52 instructions with all 16 operands resolved.

## 2026-08-09 slot-0 fire-word transfer

For Goldy's literal controller slot `0`, the first branch reads
`g_input_controller_slot0.buttons` at `0x4320fc` and writes it directly to
`GameInput::input.current_buttons`. The source word's full-image xrefs include
the exact keyboard and controller adapters plus the pointer adapter; among
those Windows producers, the pointer adapter is the one that ORs
`INPUT_BUTTON_PRIMARY` (`0x4000`) into slot 0. This exact 52/52 copy therefore
connects the desktop mouse producer to the cRInput edge fields consumed by
Goldy's firing gates without inventing an intermediate control state.
