/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_main_menu @ 0x419e00 */

00419e00        void* edx_9 = *arg1
00419e02        int32_t eax = *(edx_9 + 0x1a0)
00419e0a        if ((eax.b & 0x20) != 0)
00419e0c        eax.b &= 0xdf
00419e0e        *(edx_9 + 0x1a0) = eax
00419e14        destroy_main_menu()
00419e19        void* eax_1 = data_4df904
00419e1e        *(eax_1 + 0x1b8) = 2
00419e2e        *(data_4df904 + 0x30c) = 1
00419e35        return eax_1
00419e36        void* edx = arg1[3]
00419e39        int32_t eax_2 = *(edx + 0x1a0)
00419e41        if ((eax_2.b & 0x20) != 0)
00419e43        eax_2.b &= 0xdf
00419e45        *(edx + 0x1a0) = eax_2
00419e4b        destroy_main_menu()
00419e56        *(data_4df904 + 0x1b8) = 0xe
00419e60        void* eax_3 = data_4df904
00419e65        *(eax_3 + 0x30c) = 1
00419e6c        return eax_3
00419e6d        void* edx_2 = arg1[5]
00419e70        int32_t eax_4 = *(edx_2 + 0x1a0)
00419e78        if ((eax_4.b & 0x20) != 0)
00419e7a        eax_4.b &= 0xdf
00419e7c        *(edx_2 + 0x1a0) = eax_4
00419e82        void* eax_5 = data_4df904
00419e8d        *(eax_5 + 0x4f3b4) = *(eax_5 + 0x1b8)
00419ea2        *(data_4df904 + 0x4f3b8) = *(arg1[5] + 0x23c)
00419ea8        void* eax_7 = data_4df904
00419ead        *(eax_7 + 0x4f3ac) = 0xa
00419ebd        *(data_4df904 + 0x1b8) = 8
00419ec7        return eax_7
00419ec8        void* edx_5 = arg1[2]
00419ecb        int32_t eax_8 = *(edx_5 + 0x1a0)
00419ed3        if ((eax_8.b & 0x20) != 0)
00419ed5        eax_8.b &= 0xdf
00419ed7        *(edx_5 + 0x1a0) = eax_8
00419ee3        *(data_4df904 + 0x4f38c) = 1
00419eea        void* eax_9 = data_4df904
00419ef5        *(eax_9 + 0x4f388) = *(eax_9 + 0x1b8)
00419f01        *(data_4df904 + 0x1b8) = 6
00419f0b        return eax_9
00419f0c        void* edx_8 = arg1[1]
00419f0f        void* eax_10 = *(edx_8 + 0x1a0)
00419f17        if ((eax_10.b & 0x20) != 0)
00419f19        eax_10.b &= 0xdf
00419f1b        *(edx_8 + 0x1a0) = eax_10
00419f21        destroy_main_menu()
00419f26        eax_10 = data_4df904
00419f2b        *(eax_10 + 0x1b8) = 0x12
00419f3b        *(data_4df904 + 0x12e6e54) = 0
00419f45        return eax_10
