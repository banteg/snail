/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: free_tracked_allocations_to_mark @ 0x431c70 */

00431c7d        int32_t i
00431c70        i = data_5108c0
00431c7d        while (i s> data_5108c4)
00431c8d        free_tracked_memory((&data_5108c0)[i * 3] + 4)
00431c92        i = data_5108c0
00431ca4        return i
