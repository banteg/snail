/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_barrier_ai @ 0x440f80 */

00440f80        void* result = *(arg1 + 0x38)
00440f83        int32_t edx = *(result + 0x70)
00440f86        *(arg1 + 0x14) = 0x3ecccccd
00440f8d        *(arg1 + 0x18) = edx
00440f90        return result
