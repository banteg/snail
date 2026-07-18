/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_frontend_sprite_button @ 0x401a70 */

00401a78        struct BorderManager* eax = &g_game_base->border_manager
00401a8b        if ((widget->list_flags & 0x200) == 0)
00401a9c        widget->list_prev = eax
00401aa2        widget->list_next = eax->list_next
00401aa5        eax->list_next = widget
00401aa8        struct FrontendWidget* list_next = widget->list_next
00401aad        if (list_next != 0)
00401aaf        list_next->list_prev = widget
00401ab2        widget->list_flags |= 0x200
00401a92        report_errorf("List ADDafter")
00401ab5        widget->border_texture_id = 5
00401abc        widget->texture_hit_test_enabled = 0
00401abf        widget->tooltip.state = 0
00401ac5        widget->tooltip.owner_widget = widget
00401acb        widget->tooltip.tooltip_widget = nullptr
00401ad1        widget->tooltip.input_ok_state.source_widget = widget
00401adc        widget->render_inset_delta = 0f
00401ae2        widget->render_inset_base = 20f
00401ae8        widget->render_inset_dynamic = 0
00401aee        widget->sprite_shadow_offset = 4f
00401af8        widget->font_id = 0
00401aff        widget->font_scale = 1f
00401b0b        widget->idle_padding = 10f
00401b15        widget->hot_padding = 15f
00401b1f        widget->stack_gap = 20f
00401b25        widget->border_edge = 0f
00401b2b        widget->_pad_10[0x28] = 1
00401b2b        widget->_pad_10[0x29] = 0
00401b2b        widget->_pad_10[0x2a] = 0
00401b2b        widget->_pad_10[0x2b] = 0
00401b32        unhide_border_init(widget)
00401b3f        enum FrontendWidgetFlag eax_2 = widget_flags | 0x40801
00401b44        widget->layout_anchor_y = y
00401b4a        widget->widget_flags = eax_2
00401b50        widget->previous_widget_flags = eax_2
00401b5a        widget->text_buffer.raw[0] = 0
00401b60        widget->layout_anchor_x = x
00401b83        widget->idle_fill_color.r = color->r
00401b8d        widget->idle_fill_color.g = color->g
00401b93        widget->idle_fill_color.b = color->b
00401b99        widget->idle_fill_color.a = color->a
00401ba4        widget->hot_fill_color.r = color->r
00401bad        widget->hot_fill_color.g = color->g
00401bb3        widget->hot_fill_color.b = color->b
00401bbd        widget->hot_fill_color.a = color->a
00401bc0        struct tColour color_1
00401bc0        struct tColour* eax_6 = set_color_rgba(&color_1, 1f, 1f, 1f, 1f)
00401bd7        widget->idle_text_color.r = eax_6->r
00401be6        widget->idle_text_color.g = eax_6->g
00401bec        widget->idle_text_color.b = eax_6->b
00401bf2        widget->idle_text_color.a = eax_6->a
00401bf9        struct tColour* eax_8 = set_color_rgba(&color_1, 1f, 1f, 1f, 1f)
00401c06        widget->hot_text_color.r = eax_8->r
00401c0f        widget->hot_text_color.g = eax_8->g
00401c15        widget->hot_text_color.b = eax_8->b
00401c1b        widget->hot_text_color.a = eax_8->a
00401c27        if ((widget->widget_flags.b & 2) == 0)
00401c41        float idle_padding = widget->idle_padding
00401c47        widget->hover_blend_target = 0f
00401c4d        widget->target_padding = idle_padding
00401c29        float hot_padding = widget->hot_padding
00401c2f        widget->hover_blend_target = 1f
00401c39        widget->target_padding = hot_padding
00401c59        float target_padding = widget->target_padding
00401c63        widget->hover_blend_current = widget->hover_blend_target
00401c6d        widget->current_padding = target_padding
00401c77        widget->text_effect_target = 0f
00401c7d        widget->text_effect_current = 0f
00401c83        widget->text_alignment = 0
00401c89        widget->anchor_x = anchor_x
00401c98        long double x87_r7_1 = fconvert.t(anchor_x) + fconvert.t(g_game_base->border_manager.justify_centre)
00401ca2        widget->layout_left = x
00401ca8        widget->layout_top = y
00401cae        widget->anchor_x = fconvert.s(x87_r7_1)
00401cbe        widget->layout_width = fconvert.s(float.t(g_sprite_texture_table[sprite]->loaded_width))
00401cd1        long double x87_r7_3 = float.t(g_sprite_texture_table[sprite]->loaded_height)
00401cd4        widget->texture_hit_width = widget->layout_width
00401cde        widget->texture_id = sprite
00401ce8        widget->layout_height = fconvert.s(x87_r7_3)
00401cee        float layout_height = widget->layout_height
00401cf4        widget->layout_anchor_x = x
00401cfa        widget->texture_hit_height = layout_height
00401d06        widget->layout_anchor_y = y
00401d0c        widget->texture_layer = layer
00401d12        widget->teardown_progress = 0f
00401d18        widget->teardown_progress_step = 0f
00401d1e        layout_frontend_widget(widget)
00401d28        return
