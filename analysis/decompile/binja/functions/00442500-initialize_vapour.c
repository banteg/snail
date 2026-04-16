/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_vapour @ 0x442500 */

0044250c        void* ecx = *(arg1 + 0x24)
0044250f        *(arg1 + 0x88) = arg2
00442518        int32_t eax_1 = *(ecx + 0x54) + 1
00442519        *(arg1 + 0x84) = eax_1
0044252d        *(arg1 + 0x90) = allocate_tracked_memory(eax_1 << 6, "Vapour Trail")
0044253b        return reset_vapour(arg1, 0)
