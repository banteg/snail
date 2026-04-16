/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: destroy_loading_screen @ 0x418e50 */

00418e56        data_4df9c4 = arg1[2]
00418e5b        int32_t* eax_1 = data_503288
00418e63        (*(*eax_1 + 8))(eax_1)
00418e66        int32_t* eax_2 = data_503280
00418e6e        int32_t result = (*(*eax_2 + 8))(eax_2)
00418e71        *arg1 = 0
00418e78        return result
