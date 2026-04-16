/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: reset_subgame @ 0x437b10 */

00437b16        int32_t i_4 = 8
00437b1b        int32_t* eax = &arg1[0x356044]
00437b2a        int32_t i
00437b21        eax[-3] = 0
00437b24        *eax = arg1
00437b26        eax = &eax[0x1d]
00437b29        i = i_4
00437b29        i_4 -= 1
00437b2a        do while (i != 1)
00437b2c        *(arg1 + 0x355e30) = 0
00437b32        *(arg1 + 0x355e3c) = arg1
00437b38        *(arg1 + 0x355e9c) = 0
00437b3e        *(arg1 + 0x355ea8) = arg1
00437b44        void** eax_1 = &arg1[0x3591d0]
00437b4a        int32_t i_5 = 0x32
00437b5d        int32_t i_1
00437b4f        eax_1[-2] = 0
00437b52        *eax_1 = arg1
00437b54        eax_1[-3] = 0
00437b57        eax_1 = &eax_1[0x31]
00437b5c        i_1 = i_5
00437b5c        i_5 -= 1
00437b5d        do while (i_1 != 1)
00437b5f        void** eax_2 = &arg1[0x356428]
00437b65        int32_t i_6 = 8
00437b75        int32_t i_2
00437b6a        eax_2[-2] = 0
00437b6d        *eax_2 = arg1
00437b6f        eax_2 = &eax_2[0x3b]
00437b74        i_2 = i_6
00437b74        i_6 -= 1
00437b75        do while (i_2 != 1)
00437b77        void** eax_3 = &arg1[0x35b95c]
00437b7d        int32_t i_7 = 2
00437b90        int32_t i_3
00437b82        eax_3[-0x54] = 0
00437b88        *eax_3 = arg1
00437b8a        eax_3 = &eax_3[0x7e]
00437b8f        i_3 = i_7
00437b8f        i_7 -= 1
00437b90        do while (i_3 != 1)
00437ba6        int32_t result
00437ba6        if (arg1[0xff25d0] != 1 || *(arg1 + 0x40) != *(arg1 + 0xfd2b3c))
00437bec        if (*(arg1 + 0x1270fc8) == 2)
00437bf4        *(arg1 + 0x3bba48) = 0
00437bfa        clear_subgoldy_score_buckets(&arg1[0x3bb764])
00437c05        result = zero_timer_counters()
00437c0a        *(arg1 + 0x3bba64) = 0
00437c10        *(arg1 + 0x3bba68) = 0
00437bae        int32_t edx_1 = *(arg1 + 0xfd2b30)
00437bb4        result = *(arg1 + 0xfd2b34)
00437bbc        *(arg1 + 0x3bba48) = *(arg1 + 0xfd2b14)
00437bd3        *(arg1 + 0x3bba64) = edx_1
00437bd9        __builtin_memcpy(&arg1[0x3bba4c], &arg1[0xfd2b18], 0x18)
00437bdc        *(arg1 + 0x3bba68) = result
00437c16        *(arg1 + 0x3bbae0) = 0
00437c1c        *arg1 = 1
00437c20        arg1[1] = 1
00437c24        arg1[0xff25d0] = 0
00437c2a        *(arg1 + 0x359140) = 0
00437c32        return result
