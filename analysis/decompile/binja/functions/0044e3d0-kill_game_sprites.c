/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: kill_game_sprites @ 0x44e3d0 */

0044e3d3        struct Sprite** i = &g_sprite_active_heads
0044e401        while (i s< &g_sprite_free_head)
0044e3dd        struct Sprite* sprite = *i
0044e3e1        if (sprite != 0)
0044e3f6        struct Sprite* next
0044e3e6        next = sprite->next
0044e3eb        if ((0x800 & sprite->flags) != 0)
0044e3ed        kill_sprite(sprite)
0044e3f4        sprite = next
0044e3f6        do while (next != 0)
0044e3f8        i = &i[1]
0044e406        return
