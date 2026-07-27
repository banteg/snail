/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_math_random_table @ 0x44c8d0 */

0044c8d1        int32_t* i = &data_787f8c
0044c8e6        while (i s< &g_sound_effect_manager)
0044c8db        *i = rand()
0044c8dd        i = &i[1]
0044c8e8        data_77ff3c = 0
0044c8f3        return
