/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: free_tracked_memory @ 0x431bf0 */

00431bfe        int32_t eax = get_tracked_allocation_size(&data_5108c0, arg1 - 4)
00431c0b        data_5108b4 -= eax
00431c16        if (*(arg1 - 4) != 0xde)
00431c51        report_errorf("Memory corruption")
00431c18        int32_t edx_1
00431c18        edx_1.b = *(arg1 - 3)
00431c1f        if (edx_1.b != 0xad)
00431c51        report_errorf("Memory corruption")
00431c22        int32_t ebx
00431c22        ebx.b = *(arg1 - 2)
00431c4a        if (ebx.b != 0xba || *(arg1 - 1) != 0xbe || (arg1 - 4)[eax - 4] != 0xde || (arg1 - 4)[eax - 3] != 0xad || (arg1 - 4)[eax - 2] != 0xba || (arg1 - 4)[eax - 1] != 0xbe)
00431c51        report_errorf("Memory corruption")
00431c5a        sub_48b8d5(arg1 - 4)
00431c6e        return pop_tracked_allocation(&data_5108c0, arg1 - 4)
