/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_registered_sound_sample_from_path @ 0x449920 */

00449936        int32_t result = data_7537cc(0, arg1, 0, 0, arg3, 0x20010)
00449942        *((arg2 << 2) + &data_7537e0) = result
00449949        if (result != 0)
0044995a        return result
0044994b        int32_t var_8_1 = arg1
0044994c        char* var_c_1 = "Bass Sample Load Fail %s\n"
00449951        return sub_449c00()
