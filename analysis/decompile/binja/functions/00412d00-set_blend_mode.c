/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: set_blend_mode @ 0x412d00 */

00412d07        if (arg1 u<= 0x14)
00412d0f        int32_t ecx_1
00412d0f        ecx_1.b = lookup_table_412e30[arg1]
00412d15        int32_t var_4_1
00412d15        int32_t* eax_5
00412d15        int32_t edx_3
00412d15        switch (ecx_1)
00412d1c        case 0
00412d1c        int32_t* eax = data_502fec
00412d28        (*(*eax + 0xc8))(eax, 0x1b, 1)
00412d2e        int32_t* eax_1 = data_502fec
00412d3a        (*(*eax_1 + 0xc8))(eax_1, 0x13, 5)
00412d40        int32_t* eax_2 = data_502fec
00412d52        return (*(*eax_2 + 0xc8))(eax_2, 0x14, 6)
00412d53        case 1
00412d53        int32_t* eax_4 = data_502fec
00412d5f        (*(*eax_4 + 0xc8))(eax_4, 0x1b, 1)
00412d65        eax_5 = data_502fec
00412d6a        var_4_1 = 5
00412d6c        edx_3 = *eax_5
00412dff        label_412dff:
00412dff        (*(edx_3 + 0xc8))(eax_5, 0x13, var_4_1)
00412e05        int32_t* eax_15 = data_502fec
00412e11        return (*(*eax_15 + 0xc8))(eax_15, 0x14, 6)
00412d73        case 2
00412d73        int32_t* eax_6 = data_502fec
00412d7f        (*(*eax_6 + 0xc8))(eax_6, 0x1b, 1)
00412d85        int32_t* eax_7 = data_502fec
00412d91        (*(*eax_7 + 0xc8))(eax_7, 0x13, 5)
00412d97        int32_t* eax_8 = data_502fec
00412da9        return (*(*eax_8 + 0xc8))(eax_8, 0x14, 2)
00412daa        case 3
00412daa        int32_t* eax_10 = data_502fec
00412db6        (*(*eax_10 + 0xc8))(eax_10, 0x1b, 1)
00412dbc        int32_t* eax_11 = data_502fec
00412dc8        (*(*eax_11 + 0xc8))(eax_11, 0x13, 2)
00412dce        int32_t* eax_12 = data_502fec
00412de0        return (*(*eax_12 + 0xc8))(eax_12, 0x14, 2)
00412de1        case 4
00412de1        int32_t* eax_14 = data_502fec
00412ded        (*(*eax_14 + 0xc8))(eax_14, 0x1b, 1)
00412df3        eax_5 = data_502fec
00412df8        var_4_1 = 2
00412dfa        edx_3 = *eax_5
00412dfa        goto label_412dff
00412e17        return arg1
