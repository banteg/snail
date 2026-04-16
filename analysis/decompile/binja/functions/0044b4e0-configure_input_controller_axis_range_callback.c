/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: configure_input_controller_axis_range_callback @ 0x44b4e0 */

0044b4e7        int32_t eax = *(arg1 + 0x18)
0044b4ee        if ((eax.b & 3) != 0)
0044b4f0        int32_t var_10_1 = eax
0044b4f4        int32_t eax_1 = data_777b2c
0044b4f9        int32_t i = 0
0044b4fb        int32_t var_18 = 0x18
0044b505        int32_t var_14_1 = 0x10
0044b50d        int32_t var_c_1 = 2
0044b515        int32_t var_8_1 = 0xfffffc18
0044b51d        int32_t var_4_1 = 0x3e8
0044b525        if (eax_1 s> 0)
0044b527        int32_t* esi_1 = &data_777b34
0044b52c        int32_t* eax_2 = *esi_1
0044b53d        if ((*(*eax_2 + 0x18))(eax_2, 4, &var_18) s< 0)
0044b560        return 0
0044b544        i += 1
0044b545        esi_1 = &esi_1[1]
0044b54a        do while (i s< data_777b2c)
0044b556        return 1
