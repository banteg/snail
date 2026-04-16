/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: delete_file_path_with_directory_walk @ 0x431540 */

00431555        char var_200[0x200]
00431555        sub_496946(&var_200, 0x200)
0043155a        char* esi = arg1
004315a1        char var_500[0x100]
004315a1        int32_t edi_1
00431564        char i = *esi
00431566        edi_1 = 0
0043156a        if (i != 0)
0043156e        while (i != 0x2f)
00431572        if (i == 0x5c)
00431572        break
00431574        var_500[edi_1] = i
00431578        i = esi[1]
0043157b        edi_1 += 1
0043157c        esi = &esi[1]
0043157f        if (i == 0)
0043157f        break
00431581        i = *esi
00431589        if (i == 0x2f || i == 0x5c)
0043158f        var_500[edi_1] = 0
00431595        set_current_directory_with_drive_fallback(&var_500)
0043159d        esi = &esi[1]
004315a1        do while (*esi != 0)
004315ad        var_500[edi_1] = 0
004315b2        int32_t* eax_1 = sub_48b41d(&var_500, "wb")
004315be        char var_400[0x200]
004315be        if (eax_1 != 0)
004315f2        char (* var_50c_2)[0x100] = &var_500
004315f8        report_messagef("*Deleting file* :%s\n")
004315fe        sub_48b3a7(eax_1)
00431613        if (sub_48b8ab(&var_500) == 0xffffffff)
00431620        char (* var_50c_3)[0x200] = &var_400
00431621        char (* var_510_3)[0x100] = &var_500
00431627        report_messagef("ERROR:Cannot delete file : %s (from %s)\n")
004315cd        sub_496946(&var_400, 0x200)
004315dd        char (* var_514)[0x200] = &var_400
004315de        char (* var_518)[0x100] = &var_500
004315e4        report_messagef("ERROR:Cannot delete file : %s (from %s)\n")
00431647        return sub_48c18b(&var_200)
