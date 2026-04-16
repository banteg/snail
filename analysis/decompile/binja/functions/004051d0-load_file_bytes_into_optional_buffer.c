/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_file_bytes_into_optional_buffer @ 0x4051d0 */

004051e5        int32_t* eax = sub_48b41d(arg1, "rb")
004051f1        if (eax == 0)
004051fd        char var_200[0x200]
004051fd        sub_496946(&var_200, 0x200)
00405206        char (* var_214)[0x200] = &var_200
00405207        PSTR var_218 = arg1
0040520d        sub_48b614("WARNING:Cannot find file : %s (from %s)\n")
0040521f        return 0
00405222        int32_t* eax_2 = get_stream_length_preserve_position(eax)
00405227        char* result = arg2
00405235        if (result == 0)
00405240        result = sub_48b72d(eax_2)
00405247        sub_48b645(result, 1, eax_2, eax)
0040524d        sub_48b3a7(eax)
0040525e        if (arg3 != 0)
00405260        *arg3 = eax_2
0040526d        return result
