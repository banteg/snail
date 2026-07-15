/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: draw_frontend_widget @ 0x401130 */

00401158        void var_20
00401158        struct GameRoot* result = noop_this_constructor(&var_20)
0040115d        result.b = g_render_queue_active
00401164        if (result.b != 0)
0040116a        result = widget->widget_flags
00401173        if ((result:1.b & 0x10) == 0)
00401180        int32_t blend_mode
00401180        struct tColour color_2
00401180        int32_t blend_mode_1
00401180        if ((g_runtime_config.render_flags.b & 0x80) != 0)
0040119a        blend_mode = 3
004011a2        blend_mode_1 = 3
00401182        blend_mode_1 = 0
00401184        color_2.a = 0x3f800000
0040118c        int32_t var_14_1 = 0x3f800000
00401194        blend_mode = 0
004011a6        float width_3 = widget->layout_width
004011ac        float layout_height = widget->layout_height
004011b7        float width_2 = width_3
004011bf        if ((result & 0x100000) != 0)
004011c5        long double x87_r7_1 = fconvert.t(widget->slider_position_current)
004011d7        long double temp1_1 = fconvert.t(0f)
004011d7        x87_r7_1 - temp1_1
004011e0        struct tColour color_1
004011e0        color_1.r = widget->current_text_color.r
004011e4        color_1.g = widget->current_text_color.g
004011e8        width_3 = widget->current_text_color.b
004011eb        color_1.b = width_3
004011f4        color_1.a = widget->current_text_color.a
004011fb        if ((((x87_r7_1 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp1_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00401229        struct tColour* var_b0_1 = &color_1
00401239        struct tColour* var_b4_1 = &color_1
00401247        struct tColour* var_b8_1 = &color_1
00401259        width_3 = queue_axis_aligned_textured_quad_uv(0x25, fconvert.s(fconvert.t(width_2) * fconvert.t(0.5f) + fconvert.t(widget->texture_hit_x) - fconvert.t(128f)), fconvert.s(fconvert.t(widget->texture_hit_y) + fconvert.t(50f)), fconvert.s(fconvert.t(widget->slider_position_current) * fconvert.t(256f)), 32f, 0x1000000, &color_1, 0f, 0f, fconvert.s(x87_r7_1), 1f, blend_mode_1, 0f)
00401261        long double x87_r7_10 = fconvert.t(widget->slider_position_current)
0040126b        long double temp2_1 = fconvert.t(1f)
0040126b        x87_r7_10 - temp2_1
00401276        if ((((x87_r7_10 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_10, temp2_1) ? 1 : 0) << 0xa | (x87_r7_10 == temp2_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
004012ad        float width_6 = width_3
004012bd        float width_5 = width_3
004012cb        float width_4 = width_3
004012eb        width_3 = queue_axis_aligned_textured_quad_uv(0x24, fconvert.s(fconvert.t(width_2) * fconvert.t(0.5f) + fconvert.t(widget->texture_hit_x) - fconvert.t(128f) + fconvert.t(widget->slider_position_current) * fconvert.t(256f)), fconvert.s(fconvert.t(widget->texture_hit_y) + fconvert.t(50f)), fconvert.s((fconvert.t(1f) - fconvert.t(widget->slider_position_current)) * fconvert.t(256f)), 32f, 0x1000000, &color_1, fconvert.s(x87_r7_10), 0f, 1f, 1f, blend_mode_1, 0f)
004012f8        if (widget->texture_hit_test_enabled != 0)
004012fe        struct GameRoot* game_base_1 = g_game_base
00401303        long double x87_r7_21 = fconvert.t(0f)
00401309        width_3.b = game_base_1->border_manager.delayed_widget_active
00401319        if (width_3.b != 0 && widget == game_base_1->border_manager.delayed_widget)
00401329        float width_7 = width_3
00401338        x87_r7_21 = sine(fconvert.s(fconvert.t(game_base_1->border_manager.delayed_widget_progress) * fconvert.t(3.14159274f))) * fconvert.t(3f)
00401340        if (widget->sprite_wobble_positive == 0)
00401342        x87_r7_21 = x87_r7_21 * fconvert.t(-1f)
00401348        int32_t texture_layer = widget->texture_layer
00401356        long double x87_r6_4 = fconvert.t(widget->border_edge) * fconvert.t(0.5f)
00401383        int32_t texture_layer_8 = texture_layer
0040138c        float height = fconvert.s(fconvert.t(widget->texture_hit_height) + fconvert.t(widget->border_edge))
0040139b        int32_t texture_layer_6 = texture_layer
0040139c        float width = fconvert.s(fconvert.t(widget->texture_hit_width) + fconvert.t(widget->border_edge))
004013a7        int32_t texture_layer_4 = texture_layer
004013a8        float y = fconvert.s(fconvert.t(widget->texture_hit_y) - x87_r6_4)
004013b3        int32_t texture_layer_2 = texture_layer
004013b6        float x = fconvert.s(x87_r7_21 + fconvert.t(widget->texture_hit_x) - x87_r6_4)
004013bb        if ((widget->widget_flags.b & 2) == 0)
004013e7        return queue_axis_aligned_textured_quad_uv(widget->texture_id, x, y, width, height, 0x1000000, &widget->current_text_color, 0f, 0f, 1f, 1f, texture_layer, 0f)
004013d0        return queue_axis_aligned_textured_quad_uv(widget->background_texture_id, x, y, width, height, 0x1000000, &widget->current_text_color, 0f, 0f, 1f, 1f, texture_layer, 0f)
004013e8        result = widget->widget_flags
004013f1        struct tColour color
004013f1        if ((result:1.b & 8) != 0)
004013f7        int32_t texture_layer_1 = widget->texture_layer
00401405        long double x87_r7_29 = fconvert.t(widget->border_edge) * fconvert.t(0.5f)
00401432        int32_t texture_layer_9 = texture_layer_1
00401448        int32_t texture_layer_7 = texture_layer_1
00401454        int32_t texture_layer_5 = texture_layer_1
00401460        int32_t texture_layer_3 = texture_layer_1
00401467        result = queue_axis_aligned_textured_quad_uv(widget->texture_id, fconvert.s(fconvert.t(widget->texture_hit_x) - x87_r7_29), fconvert.s(fconvert.t(widget->texture_hit_y) - x87_r7_29), fconvert.s(fconvert.t(widget->border_edge) + fconvert.t(widget->texture_hit_width)), fconvert.s(fconvert.t(widget->texture_hit_height) + fconvert.t(widget->border_edge)), 0x1000000, &widget->current_text_color, 0f, 0f, 1f, 1f, texture_layer_1, 0f)
0040146c        long double x87_r7_31 = fconvert.t(widget->sprite_shadow_offset)
00401472        long double temp3_1 = fconvert.t(0f)
00401472        x87_r7_31 - temp3_1
0040147b        result.w = (x87_r7_31 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_31, temp3_1) ? 1 : 0) << 0xa | (x87_r7_31 == temp3_1 ? 1 : 0) << 0xe
00401480        if ((result:1.b & 0x41) == 0)
004014a4        float var_54_1 = fconvert.s(fconvert.t(widget->border_edge) * fconvert.t(0.5f))
004014b7        struct tColour* color_3
004014b7        int32_t ecx_6
004014b7        color_3, ecx_6 = set_color_rgba(&color, 0f, 0f, 0f, 0.899999976f)
004014ce        int32_t var_ac_2 = ecx_6
004014de        int32_t var_b0_5 = ecx_6
004014ee        int32_t var_b4_5 = ecx_6
00401502        int32_t var_b8_5 = ecx_6
00401511        result = queue_axis_aligned_textured_quad_uv(widget->texture_id, fconvert.s(fconvert.t(widget->sprite_shadow_offset) + fconvert.t(widget->texture_hit_x) - fconvert.t(var_54_1)), fconvert.s(fconvert.t(widget->sprite_shadow_offset) + fconvert.t(widget->texture_hit_y) - fconvert.t(var_54_1)), fconvert.s(fconvert.t(widget->border_edge) + fconvert.t(widget->texture_hit_width)), fconvert.s(fconvert.t(widget->texture_hit_height) + fconvert.t(widget->border_edge)), 0x1000000, color_3, 0f, 0f, 1f, 1f, 2, 0f)
00401523        if ((widget->widget_flags & &__dos_header) == 0)
00401529        int16_t eax_12
00401529        eax_12.b = widget->render_inset_dynamic
00401531        float texture_hit_y
00401531        float texture_hit_x
00401531        float height_1
00401531        float width_1
00401531        float var_64_1
00401531        float var_60_3
00401531        float var_5c_1
00401531        if (eax_12.b == 0)
0040158c        long double x87_r7_52 = fconvert.t(widget->current_padding)
00401592        long double temp4_1 = fconvert.t(widget->render_inset_base)
00401592        x87_r7_52 - temp4_1
0040159d        if ((((x87_r7_52 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_52, temp4_1) ? 1 : 0) << 0xa | (x87_r7_52 == temp4_1 ? 1 : 0) << 0xe):1.b & 1) == 0)
00401619        texture_hit_x = widget->texture_hit_x
00401621        texture_hit_y = widget->texture_hit_y
0040162b        width_1 = width_2
0040162f        height_1 = layout_height
00401633        var_64_1 = widget->current_padding
00401637        var_60_3 = 0.200000003f
0040163f        var_5c_1 = 0.800000012f
004015a5        long double x87_r7_54 = fconvert.t(widget->render_inset_base) - fconvert.t(widget->current_padding)
004015b1        var_64_1 = widget->render_inset_base
004015b5        widget->render_inset_delta = fconvert.s(x87_r7_54)
004015c3        texture_hit_x = fconvert.s(x87_r7_54 + fconvert.t(widget->texture_hit_x))
004015cf        texture_hit_y = fconvert.s(x87_r7_54 + fconvert.t(widget->texture_hit_y))
004015d3        long double x87_r7_55 = x87_r7_54 + x87_r7_54
004015db        width_1 = fconvert.s(fconvert.t(width_2) - x87_r7_55)
004015e5        height_1 = fconvert.s(fconvert.t(layout_height) - x87_r7_55)
004015f5        var_60_3 = fconvert.s(fconvert.t(var_64_1) * fconvert.t(0.0078125f))
00401603        var_5c_1 = fconvert.s(fconvert.t(1f) - fconvert.t(var_60_3))
00401539        long double x87_r7_45 = fconvert.t(widget->texture_hit_x) + fconvert.t(4f)
0040153f        var_64_1 = 4f
00401547        var_60_3 = 0.100000001f
0040154f        __builtin_strncpy(&var_5c_1, "fff?", 4)
00401557        texture_hit_x = fconvert.s(x87_r7_45)
00401567        texture_hit_y = fconvert.s(fconvert.t(widget->texture_hit_y) + fconvert.t(3f))
00401575        width_1 = fconvert.s(fconvert.t(width_2) - fconvert.t(8f))
00401583        height_1 = fconvert.s(fconvert.t(layout_height) - fconvert.t(6f))
0040165e        float y_2 = fconvert.s(fconvert.t(texture_hit_y) - fconvert.t(var_64_1))
0040167a        float x_3 = fconvert.s(fconvert.t(texture_hit_x) - fconvert.t(var_64_1))
0040168c        queue_axis_aligned_textured_quad_uv(widget->border_texture_id, x_3, y_2, var_64_1, var_64_1, 0x1000000, &widget->current_fill_color, 0f, 0f, var_60_3, var_60_3, blend_mode_1, 0f)
00401698        float ebx_1 = var_5c_1
004016a1        float u1
004016a1        __builtin_strncpy(&u1, "fff?", 4)
004016c0        queue_axis_aligned_textured_quad_uv(widget->border_texture_id, texture_hit_x, y_2, width_1, var_64_1, 0x1000000, &widget->current_fill_color, var_60_3, 0f, u1, var_60_3, blend_mode_1, 0f)
004016e6        float x_1 = fconvert.s(fconvert.t(width_1) + fconvert.t(texture_hit_x))
004016f4        float u0
004016f4        __builtin_strncpy(&u0, "fff?", 4)
00401703        queue_axis_aligned_textured_quad_uv(widget->border_texture_id, x_1, y_2, var_64_1, var_64_1, 0x1000000, &widget->current_fill_color, u0, 0f, 1f, var_60_3, blend_mode, 0f)
00401737        queue_axis_aligned_textured_quad_uv(widget->border_texture_id, x_3, texture_hit_y, var_64_1, height_1, 0x1000000, &widget->current_fill_color, 0f, var_60_3, var_60_3, ebx_1, blend_mode, 0f)
00401771        queue_axis_aligned_textured_quad_uv(widget->border_texture_id, texture_hit_x, texture_hit_y, width_1, height_1, 0x1000000, &widget->current_fill_color, var_60_3, var_60_3, ebx_1, ebx_1, blend_mode, 0f)
004017a5        queue_axis_aligned_textured_quad_uv(widget->border_texture_id, x_1, texture_hit_y, var_64_1, height_1, 0x1000000, &widget->current_fill_color, ebx_1, var_60_3, 1f, ebx_1, blend_mode, 0f)
004017cf        float y_1 = fconvert.s(fconvert.t(height_1) + fconvert.t(texture_hit_y))
004017eb        queue_axis_aligned_textured_quad_uv(widget->border_texture_id, x_3, y_1, var_64_1, var_64_1, 0x1000000, &widget->current_fill_color, 0f, ebx_1, var_60_3, 1f, blend_mode, 0f)
0040181f        queue_axis_aligned_textured_quad_uv(widget->border_texture_id, texture_hit_x, y_1, width_1, var_64_1, 0x1000000, &widget->current_fill_color, var_60_3, ebx_1, ebx_1, 1f, blend_mode, 0f)
00401859        queue_axis_aligned_textured_quad_uv(widget->border_texture_id, x_1, y_1, var_64_1, var_64_1, 0x1000000, &widget->current_fill_color, ebx_1, ebx_1, 1f, 1f, blend_mode, 0f)
0040185e        result = g_game_base
0040187a        if (result->border_manager.delayed_widget_active != 0 && widget == result->border_manager.delayed_widget)
0040188d        set_color_white(&color_2)
004018ac        struct tColour* var_8c_2 = &color_2
004018bb        store_color4f(&color, color_2.r, color_2.g, color_2.b, fconvert.s(fconvert.t(1f) - fconvert.t(g_game_base->border_manager.delayed_widget_progress)))
004018ef        float var_54_2 = fconvert.s((fconvert.t(g_game_base->border_manager.delayed_widget_progress) * fconvert.t(0.699999988f) + fconvert.t(1f)) * fconvert.t(var_64_1))
00401901        float y_3 = fconvert.s(fconvert.t(texture_hit_y) - fconvert.t(var_54_2))
00401912        float x_2 = fconvert.s(fconvert.t(texture_hit_x) - fconvert.t(var_54_2))
0040191d        queue_axis_aligned_textured_quad_uv(0x63, x_2, y_3, var_54_2, var_54_2, 0x1000000, &color, 0f, 0f, var_60_3, var_60_3, 3, 0f)
0040194a        queue_axis_aligned_textured_quad_uv(0x63, texture_hit_x, y_3, width_1, var_54_2, 0x1000000, &color, var_60_3, 0f, ebx_1, var_60_3, 3, 0f)
00401973        queue_axis_aligned_textured_quad_uv(0x63, x_1, y_3, var_54_2, var_54_2, 0x1000000, &color, ebx_1, 0f, 1f, var_60_3, 3, 0f)
004019a0        queue_axis_aligned_textured_quad_uv(0x63, x_2, texture_hit_y, var_54_2, height_1, 0x1000000, &color, 0f, var_60_3, var_60_3, ebx_1, 3, 0f)
004019cc        queue_axis_aligned_textured_quad_uv(0x63, x_1, texture_hit_y, var_54_2, height_1, 0x1000000, &color, ebx_1, var_60_3, 1f, ebx_1, 3, 0f)
004019f9        queue_axis_aligned_textured_quad_uv(0x63, x_2, y_1, var_54_2, var_54_2, 0x1000000, &color, 0f, ebx_1, var_60_3, 1f, 3, 0f)
00401a29        queue_axis_aligned_textured_quad_uv(0x63, texture_hit_x, y_1, width_1, var_54_2, 0x1000000, &color, var_60_3, ebx_1, ebx_1, 1f, 3, 0f)
00401a51        return queue_axis_aligned_textured_quad_uv(0x63, x_1, y_1, var_54_2, var_54_2, 0x1000000, &color, ebx_1, ebx_1, 1f, 1f, 3, 0f)
00401a60        return result
