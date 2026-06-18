/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: allocate_sprite @ 0x44e2a0 */

0044e2a2        struct Sprite* free_head = manager->free_head
0044e2ac        if (free_head == 0)
0044e2b5        return &g_sprite_sentinel
0044e2c0        manager->free_head = free_head->next
0044e2c6        free_head->owner = owner
0044e2c9        void* eax_2 = manager->active_heads[owner]
0044e2d2        if (eax_2 != 0)
0044e2d4        *(eax_2 + 0x10) = free_head
0044e2d7        free_head->prev = nullptr
0044e2e1        free_head->next = manager->active_heads[owner]
0044e2e4        manager->active_heads[owner] = free_head
0044e2ed        initialize_sprite(free_head)
0044e2ff        int32_t ecx_3 = free_head->flags | 1 << (owner.b + 0x18)
0044e305        free_head->flags = ecx_3
0044e30f        free_head->texture_ref = g_sprite_texture_table[texture_id]
0044e319        if (texture_b != 0xffffffff)
0044e31e        free_head->flags = ecx_3 | 0x20
0044e32c        free_head->texture_ref_a = g_sprite_texture_table[texture_a]
0044e336        free_head->texture_ref_b = g_sprite_texture_table[texture_b]
0044e342        if (texture_a != 0xffffffff)
0044e347        free_head->flags = ecx_3 | 0x10
0044e351        free_head->texture_ref_a = g_sprite_texture_table[texture_a]
0044e354        free_head->size_end = 0f
0044e357        free_head->texture_id = texture_id
0044e35d        free_head->frame_progress = 0f
0044e363        free_head->frame_progress_step = 0f
0044e376        free_head->frame_count = g_sprite_texture_table[texture_id]->frame_count
0044e388        if (((g_sprite_texture_table[texture_id]->flags).w:1.b & 0x20) != 0)
0044e38d        uint32_t edi_2 = free_head->flags | 0x2000
0044e393        free_head->flags = edi_2
0044e39d        uint32_t ecx_11 = edi_2
0044e3a5        free_head->frame_progress_step = g_sprite_texture_table[texture_id]->frame_progress_step
0044e3b7        if (((g_sprite_texture_table[texture_id]->flags).w:1.b & 0x40) != 0)
0044e3b9        ecx_11:1.b |= 0x40
0044e3bc        free_head->flags = ecx_11
0044e3c4        return free_head
