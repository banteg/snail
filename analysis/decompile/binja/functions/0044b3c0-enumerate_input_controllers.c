/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: enumerate_input_controllers @ 0x44b3c0 */

0044b3d8        data_777b2c = 0
0044b3e4        *arg2 = 0
0044b3f1        HRESULT result = DirectInput8Create(GetModuleHandleA(nullptr), 0x800, 0x49b0c0, &data_777b30, 0)
0044b3f8        if (result s>= 0)
0044b3fe        int32_t* eax_1 = data_777b30
0044b411        result = (*(*eax_1 + 0x10))(eax_1, 4, append_enumerated_input_controller_callback, 0, 1)
0044b416        if (result s>= 0)
0044b41e        *arg2 = data_777b2c
0044b427        if (data_777b34 != 0)
0044b42e        int32_t ebx_1 = 0
0044b432        if (data_777b2c s> 0)
0044b438        int32_t* esi_1 = &data_777b34
0044b43d        while (true)
0044b43d        int32_t* eax_4 = *esi_1
0044b447        result = (*(*eax_4 + 0x2c))(eax_4, 0x49b2fc)
0044b44c        if (result s< 0)
0044b483        return result
0044b44e        int32_t* eax_5 = *esi_1
0044b456        result = (*(*eax_5 + 0x34))(eax_5, arg1, 5)
0044b45b        if (result s< 0)
0044b483        return result
0044b45d        int32_t* eax_6 = *esi_1
0044b46a        result = (*(*eax_6 + 0x10))(eax_6, configure_input_controller_axis_range_callback, arg1, 0)
0044b46f        if (result s< 0)
0044b483        return result
0044b476        ebx_1 += 1
0044b477        esi_1 = &esi_1[1]
0044b47c        if (ebx_1 s>= data_777b2c)
0044b47e        return 0
0044b47e        return 0
0044b483        return result
