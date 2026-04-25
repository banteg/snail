/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_galaxy_layout @ 0x4088e0 */

004088e6        int32_t* i = &data_4a1d18
004088f1        *arg1 = 0
004088f4        *(arg1 + 0xc) = 1
004088fe        long double x87_r7_2 = fconvert.t(i[-1]) * fconvert.t(0.800000012f)
00408904        i = &i[2]
0040890c        i[-3] = fconvert.s(x87_r7_2)
0040892a        i[-2] = fconvert.s((fconvert.t(i[-2]) * fconvert.t(0.800000012f) - fconvert.t(240f)) * fconvert.t(0.930000007f) + fconvert.t(250f))
0040892d        do while (i s< "ing " in _Galaxy.txt")
0040892f        void* i_1 = &data_4a1c50
00408966        while (i_1 s< 0x4a1ca0)
00408937        long double x87_r7_9 = fconvert.t(*(i_1 - 4)) * fconvert.t(0.800000012f)
0040893d        i_1 += 8
00408945        *(i_1 - 0xc) = fconvert.s(x87_r7_9)
00408963        *(i_1 - 8) = fconvert.s((fconvert.t(*(i_1 - 8)) * fconvert.t(0.800000012f) - fconvert.t(240f)) * fconvert.t(0.930000007f) + fconvert.t(250f))
0040896d        int32_t j_1 = 0
00408975        *(arg1 + 0x10f70) = data_4df904 + 0x74618
00408986        char* eax_3 = load_file_bytes_from_archive_or_fs("Galaxy/_Galaxy.txt", get_archive_data_base(), nullptr)
0040898b        int32_t* i_2 = &data_4a1c50
00408997        int32_t var_d0 = 0
0040899b        int32_t var_cc = 0
0040899f        int32_t* i_3 = &data_4a1c50
004089a3        int32_t* edi = &arg1[0x109b4]
004089b1        int32_t var_e8_1 = var_d0
004089b8        void var_c0
004089b8        sub_48b32c(&var_c0, "Galaxy%i:")
004089c7        char* eax_5 = find_case_insensitive_substring(&var_c0, eax_3)
004089d1        char* var_d4 = eax_5
004089d5        if (eax_5 == 0)
00408bd8        report_errorf("Cannot find Galaxy %i in _Galaxy.txt")
00408bea        return 0
004089e9        char* eax_7 = &find_case_insensitive_substring(":", eax_5)[1]
004089ea        var_d4 = eax_7
004089f1        if (*eax_7 != 0x22)
00408bf0        report_errorf("missing " in _Galaxy.txt")
00408c02        return 0
004089f7        char* eax_8 = &eax_7[1]
004089f8        char* edx_1 = &edi[-0x21]
004089fe        var_d4 = eax_8
00408a02        char j = *eax_8
00408a07        while (j != 0x22)
00408a09        *edx_1 = j
00408a0b        edx_1 = &edx_1[1]
00408a0c        eax_8 = &eax_8[1]
00408a0d        var_d4 = eax_8
00408a11        j = *eax_8
00408a1e        *edx_1 = 0
00408a21        char* eax_9 = find_case_insensitive_substring("StarNumber=", eax_8)
00408a2c        var_d4 = eax_9
00408a3b        var_d4 = &find_case_insensitive_substring("=", eax_9)[1]
00408a44        edi[-1] = parse_next_signed_int(&var_d4)
00408a4c        *edi = 0x3f800000
00408a4e        edi[1] = 0x3f800000
00408a51        edi[2] = 0x3f800000
00408a54        edi[3] = 0x3f4ccccd
00408a61        edi[4] = i_2[-1]
00408a67        edi[5] = *i_2
00408a6a        edi[6] = 0
00408a70        if (edi[-1] s> 0)
00408a76        int32_t ebp = 0
00408a8e        *(*(arg1 + 0xc) * 0x2a0 + arg1 + 0x14) = var_d0
00408ab9        *(*(arg1 + 0xc) * 0x2a0 + arg1 + 0x1c) = *(((divs.dp.d(sx.q(ebp), edi[-1]) + var_cc) << 3) + &data_4a1d1c)
00408ae4        *(*(arg1 + 0xc) * 0x2a0 + arg1 + 0x20) = *(((divs.dp.d(sx.q(ebp), edi[-1]) + var_cc) << 3) + &data_4a1d20)
00408afe        *(*(arg1 + 0xc) * 0x2a0 + arg1 + 0x24) = 0
00408b09        int32_t var_e8_4 = *(arg1 + 0xc)
00408b10        void var_80
00408b10        sub_48b32c(&var_80, "LEVEL %i MISSING")
00408b31        rstrcpy_checked_ascii(&arg1[*(arg1 + 0xc) * 0x2a0 + 0x30], &var_80)
00408b55        rstrcpy_checked_ascii(&arg1[*(arg1 + 0xc) * 0x2a0 + 0xb0], &var_80)
00408b61        j_1 += 1
00408b62        *(arg1 + 0xc) += 1
00408b68        ebp += 0xa
00408b6d        do while (j_1 s< edi[-1])
00408b73        i_2 = i_3
00408b77        j_1 = 0
00408b81        i_2 = &i_2[2]
00408b88        edi = &edi[0x28]
00408b94        var_d0 += 1
00408b98        i_3 = i_2
00408b9c        var_cc += 0xa
00408ba0        do while (i_2 s< 0x4a1ca0)
00408ba6        *(arg1 + 0x14) = 0
00408baf        *(arg1 + 0x1c) = data_4a1d14
00408bb2        int32_t result = data_4a1d18
00408bb7        *(arg1 + 0x20) = result
00408bba        *(arg1 + 0x24) = 0
00408bbd        arg1[0x30] = 0
00408bc1        arg1[0xb0] = 0
00408bd2        return result
