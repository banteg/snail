/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: write_file_bytes @ 0x431650 */

00431665        char var_200[0x200]
00431665        sub_496946(&var_200, 0x200)
0043166a        char* esi = arg1
004316b1        char var_500[0x100]
004316b1        int32_t edi_1
00431674        char i = *esi
00431676        edi_1 = 0
0043167a        if (i != 0)
0043167e        while (i != 0x2f)
00431682        if (i == 0x5c)
00431682        break
00431684        var_500[edi_1] = i
00431688        i = esi[1]
0043168b        edi_1 += 1
0043168c        esi = &esi[1]
0043168f        if (i == 0)
0043168f        break
00431691        i = *esi
00431699        if (i == 0x2f || i == 0x5c)
0043169f        var_500[edi_1] = 0
004316a5        set_current_directory_with_drive_fallback(&var_500)
004316ad        esi = &esi[1]
004316b1        do while (*esi != 0)
004316bd        var_500[edi_1] = 0
004316c2        int32_t* eax_1 = sub_48b41d(&var_500, "wb")
004316ce        if (eax_1 != 0)
0043170e        sub_48b7a1(arg2, 1, arg3, eax_1)
00431714        sub_48b3a7(eax_1)
004316dd        char var_400[0x200]
004316dd        sub_496946(&var_400, 0x200)
004316f4        report_messagef("ERROR:Cannot save file : %s (from %s)\n", &var_500, &var_400)
00431734        return sub_48c18b(&var_200)
