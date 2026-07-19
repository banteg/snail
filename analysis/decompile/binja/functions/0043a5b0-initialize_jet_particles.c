/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_jet_particles @ 0x43a5b0 */

0043a5b7        struct JetParticleSlot* particle_slot_cursor = &sub_hover->particle_slots
0043a5ba        int32_t rows_remaining = 0xf
0043a678        bool cond:1_1
0043a5c9        int32_t columns_remaining = 2
0043a669        int32_t i
0043a5de        struct Sprite* particle_sprite = allocate_sprite(&g_sprite_manager, 1, 0x9e, 0xffffffff, 0xffffffff)
0043a5e3        particle_slot_cursor->sprite = particle_sprite
0043a5e5        enum SpriteFlag flags = particle_sprite->flags
0043a5e8        flags:1.b |= 8
0043a5f0        particle_sprite->flags = flags
0043a5f3        particle_slot_cursor->sprite
0043a602        particle_slot_cursor->sprite
0043a60c        particle_slot_cursor->sprite
0043a611        particle_slot_cursor->sprite
0043a616        particle_slot_cursor->sprite
0043a621        __builtin_memset(&particle_slot_cursor->sprite->size_start, 0, 0x1c)
0043a62f        __builtin_memset(&particle_slot_cursor->sprite->velocity, 0, 0xc)
0043a631        particle_slot_cursor->sprite
0043a636        struct tColour color
0043a636        struct tColour* initial_color = set_color_rgba(&color, 1f, 1f, 1f, 0.999000013f)
0043a63f        struct tColour* particle_color = &particle_slot_cursor->sprite->color
0043a642        particle_slot_cursor = &particle_slot_cursor[1]
0043a645        i = columns_remaining
0043a645        columns_remaining -= 1
0043a646        particle_color->r = initial_color->r
0043a64b        particle_color->g = initial_color->g
0043a64e        float b = initial_color->b
0043a651        particle_color->b.b = b.b
0043a651        particle_color->b:1.b = b:1.b
0043a651        particle_color->b:2.b = b:2.b
0043a651        particle_color->b:3.b = b:3.b
0043a657        particle_color->a = initial_color->a
0043a65a        particle_slot_cursor->__offset(0xfffffffffffffff4).d = 0
0043a660        particle_slot_cursor->__offset(0xfffffffffffffff0).d->draw_mode = 0
0043a663        particle_slot_cursor->__offset(0xfffffffffffffff8).d = 0
0043a666        particle_slot_cursor->sprite:-4.d = 0x3e2aaaab
0043a669        do while (i != 1)
0043a673        cond:1_1 = rows_remaining != 1
0043a674        rows_remaining -= 1
0043a678        do while (cond:1_1)
0043a685        return
