# update_game_input

Partial owner-side bridge at `0x40aab0`.

When `GameRoot::input_sampling_gate +0x520` is nonzero, the function samples the active
controller slot into `InputState` axes, authored pointer coordinates, pointer
value, and button mask, then calls `InputState::update_input`.

Current Wibo result is 63.33%. The remaining mismatch is register choice for the
`lea` chain that prepares `copy_active_input_controller_state` arguments; the
argument offsets and masked call operands are correct.

2026-06-20 owner-bridge probe: spelling the decompiler's `InputState* p_input`
local and returning `p_input->update_input()` directly regresses to 53.33%,
because VC6 materializes `esi` before the first pointer-argument `lea`. Keep the
direct `input.*` call spelling; native only takes `esi = &input` midway through
the push chain.

2026-06-21 argument-owner retry: declaring pointer aliases in native
right-to-left push order (`pointer_y`, `pointer_x`, `pointer_value`,
`authored_y`, `authored_x`, `axis_y`, `axis_x`, buttons, slot) is codegen-neutral
at 63.33%. Naming only the first three pointer arguments is also neutral, while
the explicit `InputState*` local still regresses to 53.33%. The residual remains
the equivalent `eax`/`edx` LEA scheduling for the copy helper arguments.

2026-06-21 void bridge pass: `InputState::update_input()` is side-effect-only at
this callsite; native does not consume a declared return after the call. Changing
both the shared updater and `GameInputOwner::update_game_input()` signatures to
`void`, and dropping the scratch return-value carrier, recovers the native
right-to-left argument LEA schedule and exact-matches the bridge at 100.00%,
30/30 instructions, with 3 clean masked operands.

2026-07-11 root-owner pass: the gate is now reached through the typed
`GameRoot` field toggled by `run_frame_update`. Focused Wibo remains exact at
30/30 with 3 clean operands.
