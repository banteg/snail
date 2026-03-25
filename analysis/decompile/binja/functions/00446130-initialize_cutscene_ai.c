/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_cutscene_ai @ 0x446130 */

00446135        int32_t result = data_4df904 + 0x432700
0044613a        *arg1 = result
00446142        int32_t edx_1 = data_4df904 + 0x42fd7c
00446148        arg1[3] = 0
0044614f        arg1[1] = edx_1
00446152        return result
