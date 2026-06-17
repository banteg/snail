/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: destroy_completion_screen @ 0x406060 */

00406063        data_4df904
00406073        kill_border(prompt->prompt_title)
00406078        data_4df904
00406087        kill_border(prompt->yes_button)
0040608f        data_4df904
0040609c        kill_border(prompt->no_button)
004060ac        int32_t result = unhide_all_borders(data_4df904 + 0xb4c)
004060bb        *(data_4df904 + 0x1b8) = prompt->previous_frontend_state
004060c1        return result
