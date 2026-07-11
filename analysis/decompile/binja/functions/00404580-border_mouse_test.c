/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: border_mouse_test @ 0x404580 */

00404580        int16_t eax
00404580        eax.b = widget->texture_hit_test_enabled
00404583        char* game_base_1 = g_game_base
0040458e        if (eax.b == 0)
004046af        long double x87_r7_17 = fconvert.t(widget->layout_left) - fconvert.t(widget->target_padding)
004046b5        long double temp0_1 = fconvert.t(*(game_base_1 + 0x29c))
004046b5        x87_r7_17 - temp0_1
004046bb        eax = (x87_r7_17 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_17, temp0_1) ? 1 : 0) << 0xa | (x87_r7_17 == temp0_1 ? 1 : 0) << 0xe
004046c0        if ((eax:1.b & 1) != 0)
004046ce        long double x87_r7_20 = fconvert.t(widget->layout_width) + fconvert.t(widget->target_padding) + fconvert.t(widget->layout_left)
004046d4        long double temp2_1 = fconvert.t(*(game_base_1 + 0x29c))
004046d4        x87_r7_20 - temp2_1
004046da        eax = (x87_r7_20 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_20, temp2_1) ? 1 : 0) << 0xa | (x87_r7_20 == temp2_1 ? 1 : 0) << 0xe
004046df        if ((eax:1.b & 0x41) == 0)
004046e7        long double x87_r7_22 = fconvert.t(widget->layout_top) - fconvert.t(widget->target_padding)
004046ed        long double temp4_1 = fconvert.t(*(game_base_1 + 0x2a0))
004046ed        x87_r7_22 - temp4_1
004046f3        eax = (x87_r7_22 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_22, temp4_1) ? 1 : 0) << 0xa | (x87_r7_22 == temp4_1 ? 1 : 0) << 0xe
004046f8        if ((eax:1.b & 1) != 0)
00404706        long double x87_r7_25 = fconvert.t(widget->layout_height) + fconvert.t(widget->layout_top) + fconvert.t(widget->target_padding)
0040470c        long double temp6_1 = fconvert.t(*(game_base_1 + 0x2a0))
0040470c        x87_r7_25 - temp6_1
00404712        eax = (x87_r7_25 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_25, temp6_1) ? 1 : 0) << 0xa | (x87_r7_25 == temp6_1 ? 1 : 0) << 0xe
00404717        if ((eax:1.b & 0x41) == 0)
00404719        eax.b = 1
0040471e        return 1
00404594        long double x87_r7 = fconvert.t(*(game_base_1 + 0x29c))
0040459a        long double temp1_1 = fconvert.t(widget->texture_hit_x)
0040459a        x87_r7 - temp1_1
004045a0        eax = (x87_r7 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7, temp1_1) ? 1 : 0) << 0xa | (x87_r7 == temp1_1 ? 1 : 0) << 0xe
004045a5        if ((eax:1.b & 1) == 0)
004045b1        long double x87_r7_2 = fconvert.t(widget->texture_hit_width) + fconvert.t(widget->texture_hit_x)
004045b7        long double temp3_1 = fconvert.t(*(game_base_1 + 0x29c))
004045b7        x87_r7_2 - temp3_1
004045bd        eax = (x87_r7_2 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp3_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp3_1 ? 1 : 0) << 0xe
004045c2        if ((eax:1.b & 0x41) == 0)
004045c8        long double x87_r7_3 = fconvert.t(*(game_base_1 + 0x2a0))
004045ce        long double temp5_1 = fconvert.t(widget->texture_hit_y)
004045ce        x87_r7_3 - temp5_1
004045d4        eax = (x87_r7_3 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_3, temp5_1) ? 1 : 0) << 0xa | (x87_r7_3 == temp5_1 ? 1 : 0) << 0xe
004045d9        if ((eax:1.b & 1) == 0)
004045e5        long double x87_r7_5 = fconvert.t(widget->texture_hit_height) + fconvert.t(widget->texture_hit_y)
004045eb        long double temp7_1 = fconvert.t(*(game_base_1 + 0x2a0))
004045eb        x87_r7_5 - temp7_1
004045f1        eax = (x87_r7_5 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_5, temp7_1) ? 1 : 0) << 0xa | (x87_r7_5 == temp7_1 ? 1 : 0) << 0xe
004045f6        if ((eax:1.b & 0x41) == 0)
00404616        float var_8_1 = fconvert.s((fconvert.t(*(game_base_1 + 0x29c)) - fconvert.t(widget->texture_hit_x)) / fconvert.t(widget->texture_hit_width))
00404631        float var_4_1 = fconvert.s((fconvert.t(*(game_base_1 + 0x2a0)) - fconvert.t(widget->texture_hit_y)) / fconvert.t(widget->texture_hit_height))
00404635        void* eax_2 = get_sprite_texture_ref(widget->texture_hit_test_sprite)
0040463c        int32_t esi_1 = 0
0040463e        esi_1.w = *(eax_2 + 0xc)
0040464e        int32_t eax_3
0040464e        int16_t x87control
0040464e        int16_t x87control_1
0040464e        eax_3, x87control_1 = ftol(x87control, float.t(esi_1) * fconvert.t(var_8_1))
00404653        int32_t ebx_1 = 0
00404655        int32_t edi_1 = eax_3
00404657        ebx_1.w = *(eax_2 + 0xe)
00404667        int32_t eax_4 = ftol(x87control_1, float.t(ebx_1) * fconvert.t(var_4_1))
0040466e        if (edi_1 s< 0)
00404670        edi_1 = 0
00404679        if (edi_1 s> esi_1 - 1)
0040467b        edi_1 = esi_1 - 1
0040467f        if (eax_4 s< 0)
00404681        eax_4 = 0
0040468a        if (eax_4 s> ebx_1 - 1)
0040468c        eax_4 = ebx_1 - 1
004046a1        if (*((esi_1 * eax_4 + edi_1 + 6) * 3 + eax_2) == 0)
004046a3        char* eax_6
004046a3        eax_6.b = 1
004046a8        return 1
0040471f        eax.b = 0
00404724        return 0
