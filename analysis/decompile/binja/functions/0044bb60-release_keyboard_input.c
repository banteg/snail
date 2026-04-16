/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: release_keyboard_input @ 0x44bb60 */

0044bb60        int32_t* eax_1 = data_777d50
0044bb67        if (eax_1 != 0)
0044bb6c        (*(*eax_1 + 0x20))(eax_1)
0044bb6f        int32_t* eax = data_777d50
0044bb76        if (eax != 0)
0044bb7b        (*(*eax + 8))(eax)
0044bb7e        data_777d50 = 0
0044bb88        int32_t* result = data_777d4c
0044bb8f        if (result != 0)
0044bb94        result = (*(*result + 8))(result)
0044bb97        data_777d4c = 0
0044bba1        return result
