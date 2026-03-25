/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_cameraman @ 0x446160 */

0044616d        arg1->__offset(0xc0).d = data_4df904 + 0x42fd7c
00446179        int32_t ecx_1 = data_4df904 + 0x74618
0044617f        arg1->__offset(0xcc).b = 0
00446186        arg1->__offset(0xc4).d = ecx_1
00446192        set_matrix_identity(&arg1[2])
0044619a        set_matrix_identity(&arg1[1])
004461a1        set_matrix_identity(arg1)
004461a6        arg1->__offset(0xd0).d = 0
004461b0        arg1->__offset(0xd4).d = 0
004461ba        arg1->__offset(0xc8).d = 0x42dc0000
004461c5        return 0
