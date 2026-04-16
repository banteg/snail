/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: kill_game_sprites @ 0x44e3d0 */

0044e3d3        int32_t* i = &data_814c94
0044e401        while (i s< &data_814ca8)
0044e3dd        void* j_1 = *i
0044e3e1        if (j_1 != 0)
0044e3f6        void* j
0044e3e6        j = *(j_1 + 0xc)
0044e3eb        if ((0x800 & *(j_1 + 4)) != 0)
0044e3ed        kill_sprite(j_1)
0044e3f4        j_1 = j
0044e3f6        do while (j != 0)
0044e3f8        i = &i[1]
0044e406        return
