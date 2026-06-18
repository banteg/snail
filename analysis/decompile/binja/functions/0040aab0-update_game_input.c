/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_game_input @ 0x40aab0 */

0040aab0        int32_t game_base_1 = g_game_base
0040aabd        if (*(game_base_1 + 0x520) == 0)
0040aaf6        return game_base_1
0040aae6        copy_active_input_controller_state(owner->input.controller_slot, &owner->input.current_buttons, &owner->input.axis_x, &owner->input.axis_y, &owner->input.authored_x, &owner->input.authored_y, &owner->input.pointer_value, &owner->input.pointer_x, &owner->input.pointer_y)
0040aaf0        return update_input(&owner->input)
