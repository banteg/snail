# update_game_input

Partial owner-side bridge at `0x40aab0`.

When `g_game_base + 0x520` is nonzero, the function samples the active
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
