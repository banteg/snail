/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_cutscene_ai @ 0x446130 */

00446135        int32_t result = data_4df904 + 0x432700
0044613a        cutscene_ai->presentation = result
00446142        struct Player* edx_1 = data_4df904 + 0x42fd7c
00446148        cutscene_ai->state = 0
0044614f        cutscene_ai->player = edx_1
00446152        return result
