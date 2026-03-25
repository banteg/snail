/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: set_bod_object @ 0x42f5d0 */

0042f5d4        *(arg1 + 0x24) = arg2
0042f5da        int32_t result
0042f5da        result.b = (*(arg1 + 4)).b | 2
0042f5dc        *(arg1 + 4) = result
0042f5df        return result
