/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: free_tracked_allocations_to_mark @ 0x431c70 */

00431c70        int32_t depth = g_tracked_allocation_stack.depth
00431c7d        while (depth s> g_tracked_allocation_stack.bookmark_depth)
00431c8d        free_tracked_memory(*(depth * 0xc + &g_tracked_allocation_stack) + 4)
00431c92        depth = g_tracked_allocation_stack.depth
00431ca4        return
