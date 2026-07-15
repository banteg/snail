/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: show_subgoldy_lives @ 0x43af10 */

0043af15        int32_t edi = 0
0043af17        int32_t i = 0x35bb98
0043af4c        while (i s< 0x35bbbc)
0043af22        if (edi s>= player->visible_life_stock)
0043af3d        hide_border_init(*(player->game + i))
0043af2d        unhide_border_init(*(player->game + i))
0043af42        i += 4
0043af45        edi += 1
0043af51        return
