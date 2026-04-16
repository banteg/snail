/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_joystick_input @ 0x44b570 */

0044b57d        int32_t ebx = 0
0044b583        if (data_777b2c s> 0)
0044b589        int32_t* esi_1 = &data_777b34
0044b58e        int32_t* var_114_1 = &data_777b34
0044b598        while (true)
0044b598        int32_t* eax = *esi_1
0044b59c        if (eax == 0)
0044b59c        break
0044b5aa        if ((*(*eax + 0x64))(eax) s< 0)
0044b730        int32_t* eax_5 = (&data_777b34)[ebx]
0044b742        if ((*(*eax_5 + 0x1c))(eax_5) == 0x8007001e)
0044b756        int32_t i
0044b744        int32_t* eax_7 = (&data_777b34)[ebx]
0044b74e        i = (*(*eax_7 + 0x1c))(eax_7)
0044b756        do while (i == 0x8007001e)
0044b742        break
0044b5b0        int32_t* eax_2 = *esi_1
0044b5bf        int32_t var_110
0044b5bf        int32_t result = (*(*eax_2 + 0x24))(eax_2, 0x110, &var_110)
0044b5c4        if (result s< 0)
0044b764        return result
0044b5ce        long double x87_r7_2 = float.t(var_110) * fconvert.t(0.00100000005f)
0044b5d4        float var_11c_1 = fconvert.s(x87_r7_2)
0044b5d8        long double temp0_1 = fconvert.t(1000f)
0044b5d8        x87_r7_2 - temp0_1
0044b5de        result.w = (x87_r7_2 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp0_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp0_1 ? 1 : 0) << 0xe
0044b5e3        if ((result:1.b & 0x41) != 0)
0044b5ef        long double x87_r7_3 = fconvert.t(var_11c_1)
0044b5f3        long double temp1_1 = fconvert.t(-1000f)
0044b5f3        x87_r7_3 - temp1_1
0044b5f9        result.w = (x87_r7_3 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_3, temp1_1) ? 1 : 0) << 0xa | (x87_r7_3 == temp1_1 ? 1 : 0) << 0xe
0044b5fe        if ((result:1.b & 0x41) != 0)
0044b600        var_11c_1 = -1000f
0044b5e5        var_11c_1 = 1000f
0044b60c        int32_t var_10c
0044b60c        long double x87_r7_5 = float.t(var_10c) * fconvert.t(0.00100000005f)
0044b612        float var_118_1 = fconvert.s(x87_r7_5)
0044b616        long double temp2_1 = fconvert.t(1000f)
0044b616        x87_r7_5 - temp2_1
0044b61c        result.w = (x87_r7_5 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_5, temp2_1) ? 1 : 0) << 0xa | (x87_r7_5 == temp2_1 ? 1 : 0) << 0xe
0044b621        if ((result:1.b & 0x41) != 0)
0044b62d        long double x87_r7_6 = fconvert.t(var_118_1)
0044b631        long double temp3_1 = fconvert.t(-1000f)
0044b631        x87_r7_6 - temp3_1
0044b637        result.w = (x87_r7_6 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_6, temp3_1) ? 1 : 0) << 0xa | (x87_r7_6 == temp3_1 ? 1 : 0) << 0xe
0044b63c        if ((result:1.b & 0x41) != 0)
0044b63e        var_118_1 = -1000f
0044b623        var_118_1 = 1000f
0044b646        char var_d4
0044b646        result.b = var_d4
0044b64a        int32_t esi_2 = 0
0044b64e        if ((result.b & 0x80) != 0)
0044b650        esi_2 = 1
0044b65a        char var_d2
0044b65a        if ((var_d2 & 0x80) != 0)
0044b65c        esi_2 |= 2
0044b664        char var_d1
0044b664        if ((var_d1 & 0x80) != 0)
0044b666        esi_2 |= 4
0044b66e        char var_d3
0044b66e        if ((var_d3 & 0x80) != 0)
0044b670        esi_2 |= 8
0044b678        char var_de
0044b678        if ((var_de & 0x80) != 0)
0044b67a        esi_2 |= 0x10
0044b682        char var_dd
0044b682        if ((var_dd & 0x80) != 0)
0044b684        esi_2 |= 0x20
0044b68c        char var_df
0044b68c        if ((var_df & 0x80) != 0)
0044b68e        esi_2 |= 0x40
0044b696        char var_e0
0044b696        if ((var_e0 & 0x80) != 0)
0044b698        esi_2 |= 0x80
0044b6a3        char var_da
0044b6a3        if ((var_da & 0x80) != 0)
0044b6a5        esi_2 |= 0x100
0044b6b0        char var_d9
0044b6b0        if ((var_d9 & 0x80) != 0)
0044b6b2        esi_2 |= 0x200
0044b6bd        char var_dc
0044b6bd        if ((var_dc & 0x80) != 0)
0044b6bf        esi_2 |= 0x1000
0044b6ca        char var_db
0044b6ca        if ((var_db & 0x80) != 0)
0044b6cc        esi_2 |= 0x2000
0044b6d7        char var_d5
0044b6d7        if ((var_d5 & 0x80) != 0)
0044b6d9        esi_2 |= 0x400
0044b6e4        char var_d8
0044b6e4        if ((var_d8 & 0x80) != 0)
0044b6e6        esi_2 |= 0x800
0044b6f8        update_input_controller_slot_button_axes(ebx, esi_2, var_11c_1, var_118_1)
0044b702        update_input_controller_slot_button_axes(1, esi_2, var_11c_1, var_118_1)
0044b713        ebx += 1
0044b719        var_114_1 = &var_114_1[1]
0044b71d        if (ebx s>= data_777b2c)
0044b72f        return 0
0044b594        esi_1 = var_114_1
0044b758        return 0
