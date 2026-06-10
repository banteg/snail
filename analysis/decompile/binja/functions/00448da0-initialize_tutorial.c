/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_tutorial @ 0x448da0 */

00448da0        controller->state = 0
00448dab        void* eax_1 = data_4df904 + 0x74618
00448db0        controller->game = eax_1
00448dbc        *(eax_1 + 0x4c) |= 0x600000
00448dbf        void* game = controller->game
00448dc5        int32_t eax_2
00448dc5        eax_2.b = (*(game + 0x4c)).b & 0xfd
00448dc7        *(game + 0x4c) = eax_2
00448dca        return
