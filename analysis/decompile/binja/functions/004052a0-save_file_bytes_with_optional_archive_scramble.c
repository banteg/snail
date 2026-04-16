/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: save_file_bytes_with_optional_archive_scramble @ 0x4052a0 */

004052be        if (arg4 != 0)
004052c2        scramble_archive_bytes_in_place(arg2, arg3)
004052d7        int32_t* eax_1 = sub_48b41d(arg1, "wb")
004052e3        if (eax_1 == 0)
004052ef        char var_200[0x200]
004052ef        sub_496946(&var_200, 0x200)
004052f8        char (* var_21c)[0x200] = &var_200
004052f9        PSTR var_220 = arg1
00405311        return sub_48b614("ERROR:Cannot save file : %s (from %s)\n")
00405312        uint32_t var_214_2 = arg3
00405313        PSTR var_218_4 = arg1
00405319        sub_48b614("Saving file :%s %i bytes\n")
00405323        sub_48b7a1(arg2, 1, arg3, eax_1)
0040533b        return sub_48b3a7(eax_1)
