/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: pop_tracked_allocation @ 0x431b30 */

00431b37        int32_t result = *arg1 - 1
00431b38        *arg1 = result
00431b41        if (arg1[result * 3 + 3] != arg2)
00431b43        int32_t edx_1 = 0
00431b47        if (result s> 0)
00431b49        int32_t* ecx = &arg1[3]
00431b4e        while (*ecx != arg2)
00431b50        edx_1 += 1
00431b51        ecx = &ecx[3]
00431b56        if (edx_1 s>= result)
00431b56        break
00431b59        return result
