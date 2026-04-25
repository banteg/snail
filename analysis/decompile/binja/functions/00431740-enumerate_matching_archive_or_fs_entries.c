/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: enumerate_matching_archive_or_fs_entries @ 0x431740 */

00431740        int32_t* eax = data_53c7f8
00431751        data_503320 = 0
00431757        if (eax == 0)
00431896        char var_200[0x200]
00431896        sub_496946(&var_200, 0x200)
004318ae        if (set_current_directory_with_drive_fallback(arg1) == 1)
004318b7        int32_t eax_9 = data_503320
004318be        *arg3 = eax_9
004318c6        return eax_9
004318d4        int32_t var_318[0x5]
004318d4        HANDLE eax_10 = sub_48c211(arg2, &var_318)
004318e1        if (eax_10 != 0xffffffff)
004318fb        void var_304
004318fb        rstrcpy_checked_ascii((data_503320 << 7) + arg4, &var_304)
0043190c        data_503320 += 1
0043191c        if (sub_48c2db(eax_10, &var_318) != 0xffffffff)
00431950        int32_t i
0043192f        rstrcpy_checked_ascii((data_503320 << 7) + arg4, &var_304)
00431940        data_503320 += 1
00431945        i = sub_48c2db(eax_10, &var_318)
00431950        do while (i != 0xffffffff)
00431967        *arg3 = data_503320
00431979        return sub_48c18b(&var_200)
0043175f        int32_t var_31c = 0
00431765        if (*eax s> 0)
0043176b        int32_t ebx
0043176b        int32_t var_330_1 = ebx
0043176d        int32_t var_320_1 = 0
00431869        bool cond:1_1
00431775        char* esi_1 = arg1
0043177c        char* ecx_2 = *(var_320_1 + eax + 4)
00431780        int32_t edx
00431780        edx.b = *ecx_2
00431784        while (edx.b != 0)
00431786        eax.b = *esi_1
0043178a        if (eax.b == 0)
0043178a        break
00431792        if (eax.b s>= 0x61 && eax.b s<= 0x7a)
00431794        eax.b -= 0x20
00431798        if (edx.b != eax.b)
00431798        break
0043179a        edx.b = ecx_2[1]
0043179d        esi_1 = &esi_1[1]
0043179e        ecx_2 = &ecx_2[1]
004317af        if (*ecx_2 == 0x2f && *esi_1 == 0)
004317b5        eax.b = ecx_2[1]
004317b8        char* ebp_1 = &ecx_2[1]
004317bb        char* edi_1 = nullptr
004317bd        char* esi_2 = nullptr
004317c1        if (eax.b != 0)
004317ca        ebx.b = *(esi_2 + arg2)
004317cf        if (ebx.b == 0)
004317cf        break
004317d1        eax.b = *(edi_1 + ebp_1)
004317da        int32_t* edx_1
004317da        edx_1.b = ascii_upper_if_lowercase(eax.b)
004317e6        ecx_2.b = edx_1.b
004317fc        if (ecx_2.b != ascii_upper_if_lowercase(ebx.b) && *(esi_2 + arg2) != 0x2a)
004317fc        break
00431802        if (*(esi_2 + arg2) == 0x2a)
00431804        edx_1.b = *(edi_1 + ebp_1)
00431807        ecx_2.b = *(esi_2 + arg2 + 1)
0043180d        if (edx_1.b == ecx_2.b)
0043180f        esi_2 = &esi_2[1]
00431810        ecx_2.b = *(esi_2 + arg2)
00431813        edi_1 = &edi_1[1]
00431817        if (ecx_2.b != 0x2a)
00431819        esi_2 = &esi_2[1]
0043181e        do while (*(edi_1 + ebp_1) != 0)
00431824        if (*(edi_1 + ebp_1) == 0)
00431839        rstrcpy_checked_ascii((data_503320 << 7) + arg4, ebp_1)
00431847        data_503320 += 1
0043184c        eax = data_53c7f8
0043185f        cond:1_1 = var_31c + 1 s< *eax
00431861        var_31c += 1
00431865        var_320_1 += 0xc
00431869        do while (cond:1_1)
00431880        *arg3 = data_503320
00431888        return eax
