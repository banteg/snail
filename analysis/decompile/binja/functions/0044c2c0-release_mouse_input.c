/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: release_mouse_input @ 0x44c2c0 */

0044c2c0        int32_t* eax_1 = data_777d9c
0044c2c7        if (eax_1 != 0)
0044c2cc        (*(*eax_1 + 0x20))(eax_1)
0044c2cf        int32_t* eax = data_777d9c
0044c2d6        if (eax != 0)
0044c2db        (*(*eax + 8))(eax)
0044c2de        data_777d9c = 0
0044c2e8        int32_t* result = data_777d98
0044c2ef        if (result != 0)
0044c2f4        result = (*(*result + 8))(result)
0044c2f7        data_777d98 = 0
0044c301        return result
