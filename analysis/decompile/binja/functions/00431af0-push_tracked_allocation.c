/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: push_tracked_allocation @ 0x431af0 */

00431af9        stack->records[stack->depth].guarded_size = guarded_size
00431b07        *(stack + (stack->depth + 1) * 0xc) = pointer
00431b0c        int32_t edx_3 = stack->depth + 1
00431b0f        stack->depth = edx_3
00431b16        if (edx_3 s> 0x3a98)
00431b1d        report_errorf("Memory Stack Full")
00431b23        return
