/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: hide_border_init @ 0x4010e0 */

004010e0        int32_t result = *(arg1 + 0x1a0)
004010e9        if ((result:1.b & 0x10) != 0)
00401106        return result
004010eb        result:1.b |= 0x10
004010ee        *(arg1 + 0x44) = 0
004010f5        *(arg1 + 0x1a0) = result
00401101        return reset_tooltip(arg1 + 0x28c) __tailcall
