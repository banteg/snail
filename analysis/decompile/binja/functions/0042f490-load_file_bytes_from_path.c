/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_file_bytes_from_path @ 0x42f490 */

0042f4a5        int32_t* eax = sub_48b41d(arg1, "rb")
0042f4b1        if (eax == 0)
0042f4bd        char var_200[0x200]
0042f4bd        sub_496946(&var_200, 0x200)
0042f4c6        char (* var_214)[0x200] = &var_200
0042f4c7        PSTR var_218 = arg1
0042f4cd        sub_48b614("WARNING:Cannot find file : %s (from %s)\n")
0042f4df        return 0
0042f4e0        int32_t* edi_1 = arg4
0042f4e9        if (edi_1 == 0)
0042f4f4        edi_1 = get_stream_length_preserve_position(eax)
0042f4f7        char* result = arg2
0042f500        if (result == 0)
0042f50b        result = sub_48b72d(edi_1)
0042f512        sub_48b645(result, 1, edi_1, eax)
0042f518        sub_48b3a7(eax)
0042f529        if (arg3 != 0)
0042f52b        *arg3 = edi_1
0042f538        return result
