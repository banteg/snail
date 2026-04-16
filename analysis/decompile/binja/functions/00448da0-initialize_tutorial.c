/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_tutorial @ 0x448da0 */

00448da0        *arg1 = 0
00448dab        void* eax_1 = data_4df904 + 0x74618
00448db0        arg1[3] = eax_1
00448dbc        *(eax_1 + 0x4c) |= 0x600000
00448dbf        void* ecx = arg1[3]
00448dc5        int32_t result
00448dc5        result.b = (*(ecx + 0x4c)).b & 0xfd
00448dc7        *(ecx + 0x4c) = result
00448dca        return result
