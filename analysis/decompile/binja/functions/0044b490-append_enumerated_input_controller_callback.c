/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: append_enumerated_input_controller_callback @ 0x44b490 */

0044b490        int32_t eax_4 = data_777b2c
0044b4a4        data_777b2c = eax_4 + 1
0044b4a9        int32_t* eax_1 = data_777b30
0044b4ba        if ((*(*eax_1 + 0xc))(eax_1, arg1 + 4, &(&data_777b34)[eax_4], 0) s< 0)
0044b4c1        return 1
0044b4cf        int32_t result
0044b4cf        result.b = data_777b2c s< 4
0044b4d2        return result
