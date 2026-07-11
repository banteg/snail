/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_game_input @ 0x40aab0 */

0040aabd        if (g_game_base[0x520] != 0)
0040aae6        copy_active_input_controller_state(game_input->input.controller_slot, &game_input->input.current_buttons, &game_input->input.axis_x, &game_input->input.axis_y, &game_input->input.authored_x, &game_input->input.authored_y, &game_input->input.pointer_value, &game_input->input.pointer_x, &game_input->input.pointer_y)
0040aaf0        update_input(&game_input->input)
0040aaf6        return
