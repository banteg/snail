/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: release_input_controllers @ 0x44b770 */

0044b776        int32_t i = 0
0044b77a        if (data_777b2c s> 0)
0044b77d        int32_t* esi_1 = &data_777b34
0044b782        int32_t* eax = *esi_1
0044b786        if (eax != 0)
0044b78b        (*(*eax + 0x20))(eax)
0044b78e        int32_t* eax_1 = *esi_1
0044b792        if (eax_1 != 0)
0044b797        (*(*eax_1 + 8))(eax_1)
0044b79a        *esi_1 = 0
0044b7a5        i += 1
0044b7a6        esi_1 = &esi_1[1]
0044b7ab        do while (i s< data_777b2c)
0044b7ae        int32_t* result = data_777b30
0044b7b6        if (result != 0)
0044b7bb        result = (*(*result + 8))(result)
0044b7be        data_777b30 = 0
0044b7c8        return result
