/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: save_config_file @ 0x42f540 */

0042f551        int32_t* eax = fopen(path, "wb")
0042f55d        if (eax == 0)
0042f578        void var_200
0042f578        return sub_496946(&var_200, 0x200)
0042f58c        sub_48b7a1(bytes, 1, byte_count, eax)
0042f5a1        return fclose(eax)
