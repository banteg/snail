/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: destroy_options_menu @ 0x41aee0 */

0041aeee        unhide_all_borders(data_4df904 + 0xb4c)
0041aef6        data_4df904
0041af03        kill_border(*(arg1 + 0x10))
0041af0b        data_4df904
0041af18        kill_border(*(arg1 + 0x1c))
0041af1d        data_4df904
0041af2c        kill_border(*(arg1 + 0x18))
0041af34        data_4df904
0041af41        kill_border(*(arg1 + 0x14))
0041af5e        return save_config_file("SnailMail.cfg", &data_4df918, 0xc4)
