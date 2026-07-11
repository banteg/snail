# set_input_controller_slot0_button_axes

The exact seven-instruction helper writes the first record in the recovered
two-slot, 0x38-stride input-controller bank at `0x50333c`.

2026-07-11 ownership consolidation: the scratch now consumes the shared lane
declarations from `input_controller_state.h` and indexes slot zero explicitly,
instead of redeclaring the same three lane bases as unrelated scalars. Codegen
remains 7/7 with three clean operands. Together with the shared Win32 state
header, this removes five stale extern-type conflicts from the repository lint
inventory (16 down to 11) without changing an instruction.
