/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_frontend_widget_interaction @ 0x402820 */

0040282e        widget->previous_widget_flags = widget->widget_flags
0040283a        enum FrontendWidgetFlag edx_1 = widget->widget_flags & ~FRONTEND_WIDGET_FLAG_POINTER_INSIDE
00402842        widget->widget_flags = edx_1
0040284d        if ((edx_1 & FRONTEND_WIDGET_FLAG_SLIDER) != 0)
00402871        widget->slider_hit_left = fconvert.s(fconvert.t(widget->layout_width) * fconvert.t(0.100000001f) + fconvert.t(widget->layout_left) + fconvert.t(4f) - fconvert.t(12f))
0040288f        widget->slider_hit_right = fconvert.s(fconvert.t(widget->layout_width) * fconvert.t(0.800000012f) + fconvert.t(widget->layout_left) - fconvert.t(4f))
004028ad        widget->slider_hit_top = fconvert.s(fconvert.t(widget->layout_height) * fconvert.t(0.5f) + fconvert.t(widget->layout_top) - fconvert.t(6f))
004028d1        widget->slider_hit_bottom = fconvert.s(fconvert.t(widget->layout_height) * fconvert.t(0.5f) + fconvert.t(widget->layout_top) + fconvert.t(32f) - fconvert.t(6f))
004028ef        widget->slider_position_current = fconvert.s((fconvert.t(widget->slider_position_target) - fconvert.t(widget->slider_position_current)) * fconvert.t(0.800000012f) + fconvert.t(widget->slider_position_current))
004028f5        enum FrontendWidgetFlag widget_flags = widget->widget_flags
004028fd        if (widget_flags == 0)
00402909        uint16_t list_flags = (widget->list_flags).w
0040290c        struct FrameBodList* ecx_1 = &g_game_base->active_bod_list
00402915        if ((list_flags:1.b & 2) != 0)
00402938        if ((list_flags.b & 0x40) != 0)
0040293f        report_errorf("List remove NEXTBOD")
0040294d        reset_tooltip(&widget->tooltip)
00402958        return
00402959        struct FrontendWidget* list_next = widget->list_next
0040295e        if (list_next != 0)
00402963        list_next->list_prev = widget->list_prev
00402966        struct FrontendWidget* list_prev = widget->list_prev
0040296b        if (list_prev == 0)
00402978        ecx_1->first = widget->list_next
00402970        list_prev->list_next = widget->list_next
0040297e        widget->list_next = ecx_1->free_top
00402981        ecx_1->free_top = widget
00402984        uint32_t list_flags_1 = widget->list_flags
0040298d        list_flags_1:1.b &= 0xfd
00402990        widget->list_flags = list_flags_1
00402993        reset_tooltip(&widget->tooltip)
0040299e        return
0040291c        report_errorf("List remove")
0040292a        reset_tooltip(&widget->tooltip)
00402935        return
004029a2        struct FrameBodList* ecx_5
004029a2        if ((widget_flags:1.b & 2) == 0)
00402a18        if ((widget_flags:1.b & 4) == 0)
00402ac9        if ((widget_flags:1.b & 0x10) != 0)
00403294        return
00402ad2        enum FrontendWidgetFlag widget_flags_1
00402ad2        if ((widget_flags:1.b & 0x80) == 0)
00402aeb        if ((widget_flags.b & 2) != 0)
00402aed        widget->hover_blend_target = 1f
00402af3        enum FrontendWidgetFlag widget_flags_12 = widget->widget_flags
00402b09        if ((widget_flags_12 & 0x2000000) != 0 && widget->mouse_history_warmup_frames == 0)
00402b0b        struct GameRoot* game_base_2 = g_game_base
00402b11        long double x87_r7_25 = fconvert.t(game_base_2->players[0].mouse_cursor.saved_x)
00402b17        long double temp4_1 = fconvert.t(widget->previous_mouse_x)
00402b17        x87_r7_25 - temp4_1
00402b22        long double x87_r7_26
00402b22        long double temp5_1
00402b22        if ((((x87_r7_25 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_25, temp4_1) ? 1 : 0) << 0xa | (x87_r7_25 == temp4_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
00402b24        x87_r7_26 = fconvert.t(game_base_2->players[0].mouse_cursor.saved_y)
00402b2a        temp5_1 = fconvert.t(widget->previous_mouse_y)
00402b2a        x87_r7_26 - temp5_1
00402b35        if ((((x87_r7_25 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_25, temp4_1) ? 1 : 0) << 0xa | (x87_r7_25 == temp4_1 ? 1 : 0) << 0xe):1.b & 0x40) == 0 || (((x87_r7_26 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_26, temp5_1) ? 1 : 0) << 0xa | (x87_r7_26 == temp5_1 ? 1 : 0) << 0xe):1.b & 0x40) == 0)
00402b3d        widget->widget_flags = widget_flags_12 | 0x4000000
00402b4d        if ((widget->widget_flags & FRONTEND_WIDGET_FLAG_SHORTCUT_KEY_ENABLED) != 0 && is_mouse_captured(&g_game_base->players[0].mouse_cursor) != 0 && sx.d(read_pressed_text_input_key_code()) == widget->shortcut_key_code)
00402b79        reset_tooltip(&widget->tooltip)
00402b7e        enum FrontendWidgetFlag widget_flags_2 = widget->widget_flags
00402b89        if ((widget_flags_2 & FRONTEND_WIDGET_FLAG_IMMEDIATE_ACTION) == 0)
00402ba4        queue_frontend_widget_flag_after_delay(&g_game_base->border_manager, widget, 0x20)
00402b8b        widget_flags_2.b |= 0x20
00402b8d        widget->widget_flags = widget_flags_2
00402bb4        uint8_t eax_13 = is_mouse_captured(&g_game_base->players[0].mouse_cursor)
00402bbb        uint8_t eax_14
00402bbb        if (eax_13 != 0)
00402bc3        eax_14 = border_mouse_test(widget)
00402bca        if (eax_13 == 0 || eax_14 == 0)
00402d0a        enum FrontendWidgetFlag edx_19 = widget->widget_flags & FRONTEND_WIDGET_FLAG_HIGHLIGHTED | FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED | FRONTEND_WIDGET_FLAG_HOVER_TEXT_EFFECT_ENABLED | FRONTEND_WIDGET_FLAG_PRIMARY_INPUT_ENABLED | FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED | FRONTEND_WIDGET_FLAG_SECONDARY_INPUT_ENABLED | FRONTEND_WIDGET_FLAG_SECONDARY_ACTION_TRIGGERED | FRONTEND_WIDGET_FLAG_KILL_PENDING | FRONTEND_WIDGET_FLAG_TEARDOWN_ACTIVE | FRONTEND_WIDGET_FLAG_SPRITE_MODE | FRONTEND_WIDGET_FLAG_HIDDEN | FRONTEND_WIDGET_FLAG_TEXT_INPUT_ACTIVE | FRONTEND_WIDGET_FLAG_TEXT_INPUT_COMPLETE | FRONTEND_WIDGET_FLAG_DISABLED | FRONTEND_WIDGET_FLAG_USE_AUTHORED_RECT | FRONTEND_WIDGET_FLAG_POINTER_INSIDE | FRONTEND_WIDGET_FLAG_SNAP_VISUAL_STATE | FRONTEND_WIDGET_FLAG_SHORTCUT_KEY_ENABLED | FRONTEND_WIDGET_FLAG_SLIDER | FRONTEND_WIDGET_FLAG_FRAMELESS | FRONTEND_WIDGET_FLAG_SUPPRESS_ACTION_SOUND | FRONTEND_WIDGET_FLAG_IMMEDIATE_ACTION | FRONTEND_WIDGET_FLAG_TEXT_INPUT_SUBMIT_REQUESTED | FRONTEND_WIDGET_FLAG_ALLOW_OFFSCREEN | FRONTEND_WIDGET_FLAG_FADE_BEFORE_ACTION | FRONTEND_WIDGET_FLAG_DISABLED_BEFORE_DEACTIVATION | 0x16000101
00402d12        widget->widget_flags = edx_19
00402d1e        if ((0x2000 & edx_19) == 0 && (edx_19.b & 4) != 0)
00402d22        unhighlight_border(widget)
00402d27        widget->text_effect_target = 0f
00402d31        widget_flags_1 = widget->widget_flags
00402d39        if ((widget_flags_1.b & 4) != 0)
00402d3b        widget_flags_1.b &= 0xfd
00402d3d        widget->widget_flags = widget_flags_1
00402bd6        enum FrontendWidgetFlag edx_12 = widget->widget_flags | FRONTEND_WIDGET_FLAG_POINTER_INSIDE
00402bde        widget->widget_flags = edx_12
00402be6        if ((edx_12.b & 4) != 0)
00402be8        widget->hover_blend_target = 1f
00402bf4        widget->target_padding = widget->hot_padding
00402c01        if ((widget->widget_flags.b & 8) != 0)
00402c03        widget->text_effect_target = 1f
00402c09        enum FrontendWidgetFlag widget_flags_3 = widget->widget_flags
00402c15        if ((widget_flags_3.b & 2) == 0 && (widget_flags_3.b & 4) != 0)
00402c1c        if ((widget_flags_3 & FRONTEND_WIDGET_FLAG_SNAP_VISUAL_STATE) == 0)
00402c25        play_sound_effect(9)
00402c2a        enum FrontendWidgetFlag widget_flags_4 = widget->widget_flags
00402c30        widget_flags_4.b |= 2
00402c32        widget->widget_flags = widget_flags_4
00402c38        enum FrontendWidgetFlag widget_flags_5 = widget->widget_flags
00402c40        struct GameRoot* game_base_1
00402c40        if ((widget_flags_5.b & 0x10) == 0)
00402ca9        game_base_1 = g_game_base
00402c42        game_base_1 = g_game_base
00402c50        if (game_base_1->border_manager.delayed_widget_active == 0)
00402c52        void* edx_14
00402c52        edx_14.b = game_base_1->players[0].game_input.b
00402c52        edx_14:1.b = game_base_1->players[0].game_input:1.b
00402c52        edx_14:2.b = game_base_1->players[0].game_input:2.b
00402c52        edx_14:3.b = game_base_1->players[0].game_input:3.b
00402c5c        if ((*(edx_14 + 0x3d) & 0x40) != 0)
00402c63        if ((widget_flags_5 & FRONTEND_WIDGET_FLAG_IMMEDIATE_ACTION) == 0)
00402c78        queue_frontend_widget_flag_after_delay(&game_base_1->border_manager, widget, 0x20)
00402c65        widget_flags_5.b |= 0x20
00402c67        widget->widget_flags = widget_flags_5
00402c87        if ((widget->widget_flags & &data_800000) == 0)
00402c90        play_sound_effect(8)
00402c9c        if ((widget->tooltip.mode_flags.b & 0x20) == 0)
00402ca4        reset_tooltip(&widget->tooltip)
00402ca9        game_base_1 = g_game_base
00402caf        enum FrontendWidgetFlag widget_flags_6 = widget->widget_flags
00402cb7        if ((widget_flags_6.b & 0x40) != 0)
00402cbd        void* edx_17
00402cbd        edx_17.b = game_base_1->players[0].game_input.b
00402cbd        edx_17:1.b = game_base_1->players[0].game_input:1.b
00402cbd        edx_17:2.b = game_base_1->players[0].game_input:2.b
00402cbd        edx_17:3.b = game_base_1->players[0].game_input:3.b
00402cc7        if ((*(edx_17 + 0x3d) & 0x80) != 0)
00402cce        if ((widget_flags_6 & FRONTEND_WIDGET_FLAG_IMMEDIATE_ACTION) == 0)
00402ce6        queue_frontend_widget_flag_after_delay(&game_base_1->border_manager, widget, 0x80)
00402cd0        widget_flags_6.b |= 0x80
00402cd2        widget->widget_flags = widget_flags_6
00402cf2        play_sound_effect(8)
00402cfd        reset_tooltip(&widget->tooltip)
00402ad4        widget->text_effect_target = 0f
00402ade        widget_flags_1 = widget->widget_flags
00402d3b        widget_flags_1.b &= 0xfd
00402d3d        widget->widget_flags = widget_flags_1
00402ad2        goto label_402d43
00402a24        long double x87_r7_24 = fconvert.t(widget->teardown_progress_step) + fconvert.t(widget->teardown_progress)
00402a2a        widget->teardown_progress = fconvert.s(x87_r7_24)
00402a30        long double temp1_1 = fconvert.t(1f)
00402a30        x87_r7_24 - temp1_1
00402a3b        if ((((x87_r7_24 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_24, temp1_1) ? 1 : 0) << 0xa | (x87_r7_24 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
00402d43        label_402d43:
00402d43        enum FrontendWidgetFlag widget_flags_7 = widget->widget_flags
00402d4c        if ((widget_flags_7:1.b & 0x80) != 0)
00402d55        widget->widget_flags = widget_flags_7 & FRONTEND_WIDGET_FLAG_HIGHLIGHTED | FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED | FRONTEND_WIDGET_FLAG_HOVER_TEXT_EFFECT_ENABLED | FRONTEND_WIDGET_FLAG_PRIMARY_INPUT_ENABLED | FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED | FRONTEND_WIDGET_FLAG_SECONDARY_INPUT_ENABLED | FRONTEND_WIDGET_FLAG_SECONDARY_ACTION_TRIGGERED | FRONTEND_WIDGET_FLAG_KILL_PENDING | FRONTEND_WIDGET_FLAG_TEARDOWN_ACTIVE | FRONTEND_WIDGET_FLAG_SPRITE_MODE | FRONTEND_WIDGET_FLAG_HIDDEN | FRONTEND_WIDGET_FLAG_TEXT_INPUT_ACTIVE | FRONTEND_WIDGET_FLAG_TEXT_INPUT_COMPLETE | FRONTEND_WIDGET_FLAG_DISABLED | FRONTEND_WIDGET_FLAG_USE_AUTHORED_RECT | FRONTEND_WIDGET_FLAG_POINTER_INSIDE | FRONTEND_WIDGET_FLAG_SNAP_VISUAL_STATE | FRONTEND_WIDGET_FLAG_SHORTCUT_KEY_ENABLED | FRONTEND_WIDGET_FLAG_SLIDER | FRONTEND_WIDGET_FLAG_FRAMELESS | FRONTEND_WIDGET_FLAG_SUPPRESS_ACTION_SOUND | FRONTEND_WIDGET_FLAG_IMMEDIATE_ACTION | FRONTEND_WIDGET_FLAG_TEXT_INPUT_SUBMIT_REQUESTED | FRONTEND_WIDGET_FLAG_ALLOW_OFFSCREEN | FRONTEND_WIDGET_FLAG_FADE_BEFORE_ACTION | FRONTEND_WIDGET_FLAG_DISABLED_BEFORE_DEACTIVATION | 0x16000101
00402d5b        unhighlight_border(widget)
00402d60        enum FrontendWidgetFlag widget_flags_8 = widget->widget_flags
00402d6b        if ((widget_flags_8 & FRONTEND_WIDGET_FLAG_SNAP_VISUAL_STATE) == 0)
00402db9        widget->hover_blend_current = fconvert.s((fconvert.t(widget->hover_blend_target) - fconvert.t(widget->hover_blend_current)) * fconvert.t(0.100000001f) + fconvert.t(widget->hover_blend_current))
00402dd7        widget->current_padding = fconvert.s((fconvert.t(widget->target_padding) - fconvert.t(widget->current_padding)) * fconvert.t(0.100000001f) + fconvert.t(widget->current_padding))
00402def        long double x87_r7_38 = (fconvert.t(widget->text_effect_target) - fconvert.t(widget->text_effect_current)) * fconvert.t(0.100000001f) + fconvert.t(widget->text_effect_current)
00402df5        widget->text_effect_current = fconvert.s(x87_r7_38)
00402dfb        long double x87_r7_39 = fconvert.t(widget->text_effect_target) - x87_r7_38
00402e01        long double temp2_1 = fconvert.t(0f)
00402e01        x87_r7_39 - temp2_1
00402e0c        if ((((x87_r7_39 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_39, temp2_1) ? 1 : 0) << 0xa | (x87_r7_39 == temp2_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) != 0)
00402e0e        x87_r7_39 = fneg(x87_r7_39)
00402e10        long double temp3_1 = fconvert.t(0.100000001f)
00402e10        x87_r7_39 - temp3_1
00402e1b        if ((((x87_r7_39 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_39, temp3_1) ? 1 : 0) << 0xa | (x87_r7_39 == temp3_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00402e23        widget->text_effect_current = widget->text_effect_target
00402d72        widget->widget_flags = widget_flags_8 & ~FRONTEND_WIDGET_FLAG_SNAP_VISUAL_STATE
00402d7e        widget->hover_blend_current = widget->hover_blend_target
00402d8a        widget->current_padding = widget->target_padding
00402d96        widget->text_effect_current = widget->text_effect_target
00402e2f        if ((widget->widget_flags & FRONTEND_WIDGET_FLAG_TEXT_INPUT_ACTIVE) != 0 && is_mouse_captured(&g_game_base->players[0].mouse_cursor) != 0)
00402e48        border_input_text(widget)
00402e53        if ((widget->widget_flags & FRONTEND_WIDGET_FLAG_TEXT_INPUT_ACTIVE) == 0)
00402e61        activate_all_borders(&g_game_base->border_manager)
00402e6c        update_twinkle_manager(&widget->twinkle_manager)
00402e77        update_tooltip(&widget->tooltip)
00402e87        uint8_t pulse_alpha = (widget->widget_flags u>> 8).b & 1
00402e8d        int32_t ecx_32
00402e8d        int16_t x87control_1
00402e8d        ecx_32, x87control_1 = layout_frontend_widget(widget)
00402e9b        if (((widget->widget_flags).w:1.b & 0x10) == 0)
00402ea7        long double x87_r7_41 = fconvert.t(1f) - fconvert.t(widget->hover_blend_current)
00402ec1        int32_t var_18_1 = ecx_32
00402ee1        int32_t var_1c_4 = ecx_32
00402efb        int32_t var_20_1 = ecx_32
00402f15        int32_t var_24_1 = ecx_32
00402f1d        store_color4f(&widget->current_fill_color, fconvert.s(fconvert.t(widget->hover_blend_current) * fconvert.t(widget->hot_fill_color.r) + x87_r7_41 * fconvert.t(widget->idle_fill_color.r)), fconvert.s(fconvert.t(widget->hover_blend_current) * fconvert.t(widget->hot_fill_color.g) + x87_r7_41 * fconvert.t(widget->idle_fill_color.g)), fconvert.s(fconvert.t(widget->hover_blend_current) * fconvert.t(widget->hot_fill_color.b) + x87_r7_41 * fconvert.t(widget->idle_fill_color.b)), fconvert.s(fconvert.t(widget->hover_blend_current) * fconvert.t(widget->hot_fill_color.a) + x87_r7_41 * fconvert.t(widget->idle_fill_color.a)))
00402f28        long double x87_r7_45 = fconvert.t(1f) - fconvert.t(widget->hover_blend_current)
00402f42        struct tColour* var_18_3 = &widget->current_fill_color
00402f62        struct tColour* var_1c_6 = &widget->current_fill_color
00402f7c        struct tColour* var_20_3 = &widget->current_fill_color
00402f96        struct tColour* var_24_3 = &widget->current_fill_color
00402f9e        store_color4f(&widget->current_text_color, fconvert.s(fconvert.t(widget->hover_blend_current) * fconvert.t(widget->hot_text_color.r) + x87_r7_45 * fconvert.t(widget->idle_text_color.r)), fconvert.s(fconvert.t(widget->hover_blend_current) * fconvert.t(widget->hot_text_color.g) + x87_r7_45 * fconvert.t(widget->idle_text_color.g)), fconvert.s(fconvert.t(widget->hover_blend_current) * fconvert.t(widget->hot_text_color.b) + x87_r7_45 * fconvert.t(widget->idle_text_color.b)), fconvert.s(fconvert.t(widget->hover_blend_current) * fconvert.t(widget->hot_text_color.a) + x87_r7_45 * fconvert.t(widget->idle_text_color.a)))
00402fa3        enum FrontendWidgetFlag widget_flags_9 = widget->widget_flags
00402fac        if ((widget_flags_9:1.b & 0x80) != 0)
00402fba        widget->current_text_color.r = fconvert.s(fconvert.t(widget->current_text_color.r) * fconvert.t(0.5f))
00402fc8        widget->current_text_color.g = fconvert.s(fconvert.t(widget->current_text_color.g) * fconvert.t(0.5f))
00402fda        widget->current_text_color.b = fconvert.s(fconvert.t(widget->current_text_color.b) * fconvert.t(0.5f))
00402fec        widget->current_text_color.a = fconvert.s(fconvert.t(widget->current_text_color.a) * fconvert.t(0.5f))
00402ffb        widget->current_fill_color.r = fconvert.s(fconvert.t(widget->current_fill_color.r) * fconvert.t(0.5f))
0040300a        widget->current_fill_color.g = fconvert.s(fconvert.t(widget->current_fill_color.g) * fconvert.t(0.5f))
0040301c        widget->current_fill_color.b = fconvert.s(fconvert.t(widget->current_fill_color.b) * fconvert.t(0.5f))
0040302e        widget->current_fill_color.a = fconvert.s(fconvert.t(widget->current_fill_color.a) * fconvert.t(0.5f))
00403037        if ((widget_flags_9:1.b & 8) == 0)
00403052        if ((widget_flags_9 & 0x10000) == 0)
004030e0        layout_and_queue_wrapped_font_text(&widget->text_buffer.raw, widget->font_id, widget->font_scale, widget->layout_anchor_x, widget->layout_anchor_y, &widget->layout_left, &widget->layout_top, &widget->layout_width, &widget->layout_height, widget->text_effect_current, (g_runtime_config.render_flags u>> 8).b & 1, widget->text_alignment, widget->anchor_x, 0x1000000, &widget->current_text_color, 0, pulse_alpha)
00403057        float authored_top = widget->authored_top
0040305a        float authored_width = widget->authored_width
0040305d        widget->layout_left = widget->authored_left
00403063        float authored_height = widget->authored_height
00403066        widget->layout_top = authored_top
0040306c        widget->layout_width = authored_width
00403072        widget->layout_height = authored_height
004030ea        x87control_1 = draw_frontend_widget(widget)
004030f4        int32_t mouse_history_warmup_frames = widget->mouse_history_warmup_frames
004030fc        if (mouse_history_warmup_frames != 0)
004030ff        widget->mouse_history_warmup_frames = mouse_history_warmup_frames - 1
00403111        widget->previous_mouse_x = g_game_base->players[0].mouse_cursor.saved_x
00403123        widget->previous_mouse_y = g_game_base->players[0].mouse_cursor.saved_y
00403134        if ((widget->widget_flags & FRONTEND_WIDGET_FLAG_SLIDER) != 0)
0040313a        struct FrontendWidget* slider_more_widget_1 = widget->slider_more_widget
00403140        enum FrontendWidgetFlag widget_flags_10 = slider_more_widget_1->widget_flags
00403148        if ((widget_flags_10.b & 0x20) != 0)
0040314a        widget_flags_10.b &= 0xdf
0040314c        slider_more_widget_1->widget_flags = widget_flags_10
00403158        long double x87_r7_65 = fconvert.t(widget->slider_position_target) + fconvert.t(0.200000003f)
0040315e        widget->slider_position_target = fconvert.s(x87_r7_65)
00403164        long double temp6_1 = fconvert.t(0.899999976f)
00403164        x87_r7_65 - temp6_1
0040316f        if ((((x87_r7_65 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_65, temp6_1) ? 1 : 0) << 0xa | (x87_r7_65 == temp6_1 ? 1 : 0) << 0xe):1.b & 1) == 0)
00403171        widget->slider_position_target = 1f
00403177        struct FrontendWidget* slider_less_widget_1 = widget->slider_less_widget
0040317d        enum FrontendWidgetFlag widget_flags_11 = slider_less_widget_1->widget_flags
00403185        if ((widget_flags_11.b & 0x20) != 0)
00403187        widget_flags_11.b &= 0xdf
00403189        slider_less_widget_1->widget_flags = widget_flags_11
00403195        long double x87_r7_67 = fconvert.t(widget->slider_position_target) - fconvert.t(0.200000003f)
0040319b        widget->slider_position_target = fconvert.s(x87_r7_67)
004031a1        long double temp8_1 = fconvert.t(0.100000001f)
004031a1        x87_r7_67 - temp8_1
004031ac        if ((((x87_r7_67 < temp8_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_67, temp8_1) ? 1 : 0) << 0xa | (x87_r7_67 == temp8_1 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
004031ae        widget->slider_position_target = 0f
004031b8        long double x87_r7_68 = fconvert.t(widget->slider_position_target)
004031be        long double temp7_1 = fconvert.t(0f)
004031be        x87_r7_68 - temp7_1
004031ce        struct FrontendWidget* slider_less_widget = widget->slider_less_widget
004031d4        enum FrontendWidgetFlag widget_flags_14 = slider_less_widget->widget_flags
004031da        if ((((x87_r7_68 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_68, temp7_1) ? 1 : 0) << 0xa | (x87_r7_68 == temp7_1 ? 1 : 0) << 0xe):1.b & 0x40) == 0)
004031e1        widget_flags_14 &= ~FRONTEND_WIDGET_FLAG_DISABLED
004031dc        widget_flags_14:1.b |= 0x80
004031e3        slider_less_widget->widget_flags = widget_flags_14
004031f1        struct FrontendWidget* slider_more_widget = widget->slider_more_widget
004031f7        if (widget->slider_position_target != 0x3f800000)
0040320a        slider_more_widget->widget_flags &= ~FRONTEND_WIDGET_FLAG_DISABLED
004031f9        enum FrontendWidgetFlag widget_flags_13 = slider_more_widget->widget_flags
004031ff        widget_flags_13:1.b |= 0x80
00403202        slider_more_widget->widget_flags = widget_flags_13
0040321c        struct tColour* ecx_46 = &widget->slider_value_widget->current_text_color
00403224        ecx_46->r = widget->current_text_color.r
00403229        ecx_46->g = widget->current_text_color.g
0040322f        ecx_46->b = widget->current_text_color.b
00403235        ecx_46->a = widget->current_text_color.a
00403244        widget->slider_value_widget->hover_blend_target = widget->hover_blend_target
00403256        widget->slider_value_widget->hover_blend_current = widget->hover_blend_current
00403279        int32_t var_18_6 = ftol(x87control_1, fconvert.t(widget->slider_position_target) * fconvert.t(100f) + fconvert.t(0.100000001f))
00403286        sprintf(&widget->slider_value_widget->text_buffer, "%02i%%")
00403294        return
00402a46        ecx_5 = &g_game_base->active_bod_list
00402a4c        uint16_t list_flags_3 = (widget->list_flags).w
00402a52        if ((list_flags_3:1.b & 2) != 0)
00402a65        if ((list_flags_3.b & 0x40) == 0)
00402a76        struct FrontendWidget* list_next_2 = widget->list_next
00402a7b        if (list_next_2 != 0)
00402a80        list_next_2->list_prev = widget->list_prev
00402a83        struct FrontendWidget* list_prev_2 = widget->list_prev
00402a88        if (list_prev_2 == 0)
00402a88        goto label_402a95
00402a8d        list_prev_2->list_next = widget->list_next
00402a90        goto label_402a9b
00402a6c        report_errorf("List remove NEXTBOD")
00402a59        report_errorf("List remove")
004029a4        widget_flags:1.b &= 0xfd
004029a7        widget->widget_flags = widget_flags
004029b2        ecx_5 = &g_game_base->active_bod_list
004029b8        uint16_t list_flags_2 = (widget->list_flags).w
004029be        if ((list_flags_2:1.b & 2) == 0)
004029c5        report_errorf("List remove")
004029d4        if ((list_flags_2.b & 0x40) == 0)
004029e8        struct FrontendWidget* list_next_1 = widget->list_next
004029ed        if (list_next_1 != 0)
004029f2        list_next_1->list_prev = widget->list_prev
004029f5        struct FrontendWidget* list_prev_1 = widget->list_prev
004029fa        if (list_prev_1 == 0)
00402a95        label_402a95:
00402a95        ecx_5->first = widget->list_next
00402a95        goto label_402a9b
00402a03        list_prev_1->list_next = widget->list_next
00402a9b        label_402a9b:
00402a9b        widget->list_next = ecx_5->free_top
00402a9e        ecx_5->free_top = widget
00402aa1        uint32_t list_flags_4 = widget->list_flags
00402aa4        list_flags_4:1.b &= 0xfd
00402aa7        widget->list_flags = list_flags_4
004029db        report_errorf("List remove NEXTBOD")
00402ab0        reset_tooltip(&widget->tooltip)
00402ab5        widget->widget_flags = 0
00402ac5        return
