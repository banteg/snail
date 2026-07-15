/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: explode_slug_hazard @ 0x43f680 */

0043f689        int32_t var_38 = 0x46
0043f89e        bool cond:0_1
0043f6ac        float var_3c_2 = fconvert.s(float.t(next_math_random_value()) * fconvert.t(6.10351572e-06f) + fconvert.t(0.200000003f))
0043f6df        float var_40_2 = fconvert.s(float.t(next_math_random_value()) * fconvert.t(3.05175781e-05f) * fconvert.t(0.75f) + fconvert.t(0.25f))
0043f6e3        struct Sprite* eax_3 = allocate_sprite(&g_sprite_manager, 1, 0x81, 0xffffffff, 0xffffffff)
0043f6e8        long double x87_r7_8 = fconvert.t(var_40_2)
0043f6f0        enum SpriteFlag flags = eax_3->flags
0043f6f3        eax_3->progress = 0f
0043f6fc        eax_3->flags = flags | SPRITE_FLAG_ORIENT_TO_MOTION | SPRITE_FLAG_GAMEPLAY_OWNED
0043f6ff        eax_3->corner_scale = fconvert.s(x87_r7_8 + x87_r7_8)
0043f730        long double x87_r7_15 = fconvert.t(1f) / ((float.t(next_math_random_value()) * fconvert.t(1.52587891e-05f) + fconvert.t(0.600000024f)) * fconvert.t(60f)) * fconvert.t(slug->owner_game->subgame_rate)
0043f733        eax_3->lifetime = 0f
0043f736        eax_3->lifetime_step = 0f
0043f739        eax_3->progress_step = fconvert.s(x87_r7_15)
0043f745        int32_t var_54_1 = 0x1fff
0043f75c        set_color_grayscale(&eax_3->color, fconvert.s(float.t(next_math_random_value()) * fconvert.t(9.1552738e-06f) + fconvert.t(0.699999988f)))
0043f76b        eax_3->size_start = fconvert.s(fconvert.t(var_40_2) * fconvert.t(0.300000012f))
0043f778        eax_3->size_end = fconvert.s(fconvert.t(var_40_2) * fconvert.t(1.20000005f))
0043f781        long double x87_r7_23 = fconvert.t(slug->owner_game->subgame_rate)
0043f794        eax_3->gravity_step = fconvert.s(x87_r7_23 * x87_r7_23 * fconvert.t(-0.00999999978f) * fconvert.t(2.20000005f))
0043f7b6        float var_18_1 = fconvert.s((float.t(next_math_random_value()) - fconvert.t(16384f)) * fconvert.t(var_3c_2) * fconvert.t(6.10351562e-05f))
0043f7ba        int32_t eax_8 = next_math_random_value()
0043f7c3        struct SubgameRuntime* owner_game = slug->owner_game
0043f7fa        long double x87_r7_35 = float.t(next_math_random_value()) * fconvert.t(var_3c_2) * fconvert.t(3.05175781e-05f) + fconvert.t(owner_game->player.velocity.z)
0043f800        long double x87_r6_7 = fconvert.t(owner_game->subgame_rate)
0043f81c        eax_3->velocity.x = fconvert.s(x87_r6_7 * fconvert.t(var_18_1))
0043f82a        eax_3->velocity.y = fconvert.s(fconvert.t(fconvert.s(float.t(eax_8) * (fconvert.t(var_3c_2) + fconvert.t(0.300000012f)) * fconvert.t(3.05175781e-05f))) * x87_r6_7)
0043f837        eax_3->velocity.z = fconvert.s(x87_r7_35 * x87_r6_7)
0043f84a        long double x87_r7_39 = float.t(next_math_random_value()) * fconvert.t(0.000305175781f)
0043f885        eax_3->position.x = fconvert.s(fconvert.t(fconvert.s(x87_r7_39 * fconvert.t(eax_3->velocity.x))) + fconvert.t(slug->body.transform.position.x))
0043f887        eax_3->position.y = fconvert.s(fconvert.t(fconvert.s(x87_r7_39 * fconvert.t(eax_3->velocity.y))) + fconvert.t(slug->body.transform.position.y))
0043f892        eax_3->position.z = fconvert.s(x87_r7_39 * fconvert.t(eax_3->velocity.z) + fconvert.t(slug->body.transform.position.z))
0043f899        cond:0_1 = var_38 != 1
0043f89a        var_38 -= 1
0043f89e        do while (cond:0_1)
0043f8ab        return
