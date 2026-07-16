/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: free_tracked_memory @ 0x431bf0 */

00431bfe        int32_t eax = get_tracked_allocation_size(&g_tracked_allocation_stack, pointer - 4)
00431c0b        g_tracked_allocation_total_bytes -= eax
00431c4a        if (*(pointer - 4) != 0xde || *(pointer - 3) != 0xad || *(pointer - 2) != 0xba || *(pointer - 1) != 0xbe || (pointer - 4)[eax - 4] != 0xde || (pointer - 4)[eax - 3] != 0xad || (pointer - 4)[eax - 2] != 0xba || (pointer - 4)[eax - 1] != 0xbe)
00431c51        report_errorf("Memory corruption")
00431c5a        sub_48b8d5(pointer - 4)
00431c68        pop_tracked_allocation(&g_tracked_allocation_stack, pointer - 4)
00431c6e        return
