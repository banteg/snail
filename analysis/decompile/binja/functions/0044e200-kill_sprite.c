/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: kill_sprite @ 0x44e200 */

0044e207        if ((sprite->flags.b & 1) == 0)
0044e215        report_errorf("Sprite kill error, already dead (%s)", &sprite->texture_ref->name)
0044e223        if (sprite == &g_sprite_sentinel)
0044e223        return
0044e22b        sprite->flags &= ~SPRITE_FLAG_ACTIVE
0044e238        if (sprite == g_sprite_active_heads[sprite->owner])
0044e23a        struct Sprite* next = sprite->next
0044e23f        if (next != 0)
0044e241        next->prev = nullptr
0044e24e        g_sprite_active_heads[sprite->owner] = sprite->next
0044e25b        sprite->next = g_sprite_free_head
0044e25e        g_sprite_free_head = sprite
0044e265        return
0044e266        struct Sprite* prev = sprite->prev
0044e26b        if (prev != 0)
0044e270        prev->next = sprite->next
0044e273        struct Sprite* next_1 = sprite->next
0044e278        if (next_1 != 0)
0044e27d        next_1->prev = sprite->prev
0044e286        sprite->next = g_sprite_free_head
0044e289        g_sprite_free_head = sprite
0044e290        return
