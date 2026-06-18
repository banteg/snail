/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: firework_shoot @ 0x441dd0 */

00441de9        if ((data_4df934 & 0x10) == 0 || world_z s<= 0)
00441de9        return 
00441df0        float texture_id = world_y
00441df5        float owner = world_x
00441dfa        float world_z_1 = world_z
00441f46        bool cond:1_1
00441e09        struct Sprite* eax_1 = allocate_sprite(&g_sprite_manager, owner, texture_id, 0xffffffff, 0xffffffff)
00441e10        int32_t var_24_1 = 0
00441e16        uint32_t flags = eax_1->flags
00441e19        eax_1->draw_mode = 0xa
00441e26        eax_1->corner_scale = 4f
00441e30        eax_1->flags = flags | 0x802
00441e33        eax_1->progress = 0f
00441e3b        long double x87_r7_2 = random_float_below(0.5f) + fconvert.t(0.800000012f)
00441e41        int32_t var_2c_2 = 0
00441e47        eax_1->lifetime = 0f
00441e4a        eax_1->lifetime_step = 0.277777791f
00441e5d        eax_1->progress_step = fconvert.s(fconvert.t(1f) / (x87_r7_2 * fconvert.t(60f)))
00441e60        int32_t ecx_2
00441e60        long double st0_2
00441e60        st0_2, ecx_2 = random_float_below(0.300000012f)
00441e6f        int32_t var_28_1 = ecx_2
00441e70        world_z = fconvert.s(st0_2 + fconvert.t(0.699999988f))
00441e89        sub_44dbd0(&eax_1->color, world_z, fconvert.s(fconvert.t(world_z) * fconvert.t(0.5f)), 0)
00441e8e        eax_1->size_start = 0.5f
00441e95        eax_1->size_end = 0.100000001f
00441eb5        world_x = fconvert.s((float.t(next_math_random_value()) - fconvert.t(16384f)) * fconvert.t(1.22070314e-05f))
00441ed8        world_y = fconvert.s((float.t(next_math_random_value()) - fconvert.t(16384f)) * fconvert.t(1.83105476e-05f) + fconvert.t(0.100000001f))
00441efc        long double x87_r7_17 = float.t(next_math_random_value()) - fconvert.t(16384f)
00441f06        eax_1->depth_offset = 0f
00441f1a        eax_1->velocity.x = fconvert.s(x87_r7_17 * fconvert.t(1.22070314e-05f))
00441f20        eax_1->velocity.y = world_y
00441f23        eax_1->velocity.z = world_x
00441f26        int32_t* game_1 = game
00441f2f        eax_1->position.x = *game_1
00441f38        cond:1_1 = world_z_1 != 1
00441f39        eax_1->position.y = game_1[1]
00441f3c        world_z_1 -= 1
00441f43        eax_1->position.z = game_1[2]
00441f46        do while (cond:1_1)
00441f53        return
