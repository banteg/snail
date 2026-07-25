/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: firework_shoot @ 0x441dd0 */

00441de9        if ((g_runtime_config.render_flags.b & 0x10) == 0 || count s<= 0)
00441de9        return
00441dfa        int32_t remaining = count
00441f46        bool cond:1_1
00441e09        struct Sprite* sprite = allocate_sprite(&g_sprite_manager, owner, texture_id, 0xffffffff, 0xffffffff)
00441e10        int32_t var_24_1 = 0
00441e16        enum SpriteFlag flags = sprite->flags
00441e19        sprite->draw_mode = 0xa
00441e26        sprite->corner_scale = 4f
00441e30        sprite->flags = flags | SPRITE_FLAG_ORIENT_TO_MOTION | SPRITE_FLAG_GAMEPLAY_OWNED
00441e33        sprite->progress = 0f
00441e3b        long double x87_r7_2 = random_float_below(0.5f) + fconvert.t(0.800000012f)
00441e41        int32_t var_2c_2 = 0
00441e47        sprite->lifetime = 0f
00441e4a        sprite->lifetime_step = 0.277777791f
00441e5d        sprite->progress_step = fconvert.s(fconvert.t(1f) / (x87_r7_2 * fconvert.t(60f)))
00441e60        int32_t ecx_1
00441e60        long double st0_2
00441e60        st0_2, ecx_1 = random_float_below(0.300000012f)
00441e6f        int32_t var_28_1 = ecx_1
00441e70        float red = fconvert.s(st0_2 + fconvert.t(0.699999988f))
00441e89        set_color_rgb(&sprite->color, red, fconvert.s(fconvert.t(red) * fconvert.t(0.5f)), 0f)
00441e8e        sprite->size_start = 0.5f
00441e95        sprite->size_end = 0.100000001f
00441eb5        float velocity_z = fconvert.s((float.t(next_math_random_value()) - fconvert.t(16384f)) * fconvert.t(1.22070314e-05f))
00441ed8        float velocity_y = fconvert.s((float.t(next_math_random_value()) - fconvert.t(16384f)) * fconvert.t(1.83105476e-05f) + fconvert.t(0.100000001f))
00441efc        long double x87_r7_17 = float.t(next_math_random_value()) - fconvert.t(16384f)
00441f06        sprite->depth_offset = 0f
00441f23        sprite->velocity.x.12 = struct Vec3 {
    .x = fconvert.s(x87_r7_17 * fconvert.t(1.22070314e-05f))
    .y = velocity_y
    .z = velocity_z
}
00441f2f        sprite->position.x = position->x
00441f38        cond:1_1 = remaining != 1
00441f39        sprite->position.y = position->y
00441f3c        remaining -= 1
00441f43        sprite->position.z = position->z
00441f46        do while (cond:1_1)
00441f53        return
