/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: allocate_tracked_memory @ 0x431b60 */

00431b6b        void* pointer = malloc(size + 8)
00431b77        if (pointer == 0)
00431b7e        report_errorf("Not enough memory\n\n")
00431b92        push_tracked_allocation(&g_tracked_allocation_stack, name, pointer, size + 8)
00431bab        __builtin_memset(__builtin_memset(pointer, 0, (size + 8) & 0xfffffffc), 0, (size + 8) & 3)
00431bb1        *pointer = 0xde
00431bb4        *(pointer + 1) = 0xad
00431bb7        *(pointer + 2) = 0xba
00431bba        *(pointer + 3) = 0xbe
00431bbd        *(pointer + size + 8 - 4) = 0xde
00431bc2        *(pointer + size + 8 - 3) = 0xad
00431bc6        *(pointer + size + 8 - 2) = 0xba
00431bca        *(pointer + size + 8 - 1) = 0xbe
00431bd6        g_tracked_allocation_total_bytes += size + 8
00431be0        return pointer + 4
