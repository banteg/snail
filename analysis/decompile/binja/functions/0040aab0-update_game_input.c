/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_game_input @ 0x40aab0 */

0040aab0        void* result = data_4df904
0040aabd        if (*(result + 0x520) == 0)
0040aaf6        return result
0040aae6        copy_active_input_controller_state(*(arg1 + 0x38), arg1 + 0x6c, arg1 + 0x4c, arg1 + 0x50, arg1 + 0x60, arg1 + 0x64, arg1 + 0x68, arg1 + 0x58, arg1 + 0x5c)
0040aaf0        return update_input(arg1 + 0x38)
