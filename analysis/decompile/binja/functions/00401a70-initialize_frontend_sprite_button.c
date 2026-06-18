/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_frontend_sprite_button @ 0x401a70 */

00401a78        struct FrontendWidget* eax = data_4df904 + 0xb4c
00401a8b        if ((arg1->list_flags & 0x200) == 0)
00401a9c        arg1->list_prev = eax
00401aa2        arg1->list_next = eax->list_next
00401aa5        eax->list_next = arg1
00401aa8        struct FrontendWidget* list_next = arg1->list_next
00401aad        if (list_next != 0)
00401aaf        list_next->list_prev = arg1
00401ab2        arg1->list_flags |= 0x200
00401a92        report_errorf("List ADDafter")
00401ab5        arg1->_pad_10[0x38] = 5
00401ab5        arg1->_pad_10[0x39] = 0
00401ab5        arg1->_pad_10[0x3a] = 0
00401ab5        arg1->_pad_10[0x3b] = 0
00401abc        arg1->state_5c = 0
00401abf        arg1->tooltip.state = 0
00401ac5        arg1->tooltip.owner_widget = arg1
00401acb        arg1->tooltip.tooltip_widget = nullptr
00401ad1        arg1->tooltip.owner_widget_38 = arg1
00401adc        arg1->render_inset_delta = 0f
00401ae2        arg1->render_inset_base = 20f
00401ae8        arg1->render_inset_dynamic = 0
00401aee        arg1->_pad_80[0xf8] = 0
00401aee        arg1->_pad_80[0xf9] = 0
00401aee        arg1->_pad_80[0xfa] = 0x80
00401aee        arg1->_pad_80[0xfb] = 0x40
00401af8        arg1->font_id = 0
00401aff        arg1->font_scale = 1f
00401b0b        arg1->idle_padding = 10f
00401b15        arg1->hot_padding = 15f
00401b1f        arg1->stack_gap = 20f
00401b25        arg1->border_edge = 0f
00401b2b        arg1->_pad_10[0x28] = 1
00401b2b        arg1->_pad_10[0x29] = 0
00401b2b        arg1->_pad_10[0x2a] = 0
00401b2b        arg1->_pad_10[0x2b] = 0
00401b32        unhide_border_init(arg1)
00401b3f        uint32_t eax_2 = arg2 | 0x40801
00401b44        arg1->layout_anchor_y = arg5
00401b4a        arg1->widget_flags = eax_2
00401b50        arg1->previous_widget_flags = eax_2
00401b5a        arg1->text_buffer.raw[0] = 0
00401b60        arg1->layout_anchor_x = arg4
00401b7c        int32_t ebp
00401b7c        ebp.b = *arg6
00401b7c        ebp:1.b = arg6[1]
00401b7c        ebp:2.b = arg6[2]
00401b7c        ebp:3.b = arg6[3]
00401b83        arg1->idle_fill_color.r = ebp
00401b8d        arg1->idle_fill_color.g = *(arg6 + 4)
00401b93        arg1->idle_fill_color.b = *(arg6 + 8)
00401b99        arg1->idle_fill_color.a = *(arg6 + 0xc)
00401ba4        arg1->hot_fill_color.r = *arg6
00401bad        arg1->hot_fill_color.g = *(arg6 + 4)
00401bb3        arg1->hot_fill_color.b = *(arg6 + 8)
00401bbd        arg1->hot_fill_color.a = *(arg6 + 0xc)
00401bc0        struct Color4f color
00401bc0        struct Color4f* eax_6 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00401bc5        float r = eax_6->r
00401bd7        arg1->idle_text_color.r.b = r.b
00401bd7        arg1->idle_text_color.r:1.b = r:1.b
00401bd7        arg1->idle_text_color.r:2.b = r:2.b
00401bd7        arg1->idle_text_color.r:3.b = r:3.b
00401be6        arg1->idle_text_color.g = eax_6->g
00401bec        arg1->idle_text_color.b = eax_6->b
00401bf2        arg1->idle_text_color.a = eax_6->a
00401bf9        struct Color4f* eax_8 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00401c06        arg1->hot_text_color.r = eax_8->r
00401c0f        arg1->hot_text_color.g = eax_8->g
00401c15        arg1->hot_text_color.b = eax_8->b
00401c1b        arg1->hot_text_color.a = eax_8->a
00401c1e        float eax_9
00401c1e        eax_9.b = arg1->widget_flags.b
00401c27        if ((eax_9.b & 2) == 0)
00401c41        float idle_padding = arg1->idle_padding
00401c47        arg1->hover_blend_target = 0f
00401c4d        arg1->target_padding = idle_padding
00401c29        float hot_padding = arg1->hot_padding
00401c2f        arg1->hover_blend_target = 1f
00401c39        arg1->target_padding = hot_padding
00401c59        float target_padding = arg1->target_padding
00401c63        arg1->hover_blend_current = arg1->hover_blend_target
00401c6d        arg1->current_padding = target_padding
00401c77        arg1->text_effect_target = 0f
00401c7d        arg1->text_effect_current = 0f
00401c83        arg1->text_alignment = 0
00401c89        arg1->anchor_x = arg7
00401c98        long double x87_r7_1 = fconvert.t(arg7) + fconvert.t(*(data_4df904 + 0x440fc))
00401ca2        arg1->layout_left = arg4
00401ca8        arg1->layout_top = arg5
00401cae        arg1->anchor_x = fconvert.s(x87_r7_1)
00401cbe        arg1->layout_width = fconvert.s(float.t(*(*((arg3 << 2) + &g_sprite_texture_table) + 4)))
00401ccb        float layout_width = arg1->layout_width
00401cd1        long double x87_r7_3 = float.t(*(*((arg3 << 2) + &g_sprite_texture_table) + 8))
00401cd4        arg1->_pad_250[0] = layout_width.b
00401cd4        arg1->_pad_250[1] = layout_width:1.b
00401cd4        arg1->_pad_250[2] = layout_width:2.b
00401cd4        arg1->_pad_250[3] = layout_width:3.b
00401cde        arg1->texture_id_270 = arg3
00401ce8        arg1->layout_height = fconvert.s(x87_r7_3)
00401cee        float layout_height = arg1->layout_height
00401cf4        arg1->layout_anchor_x = arg4
00401cfa        arg1->_pad_250[4] = layout_height.b
00401cfa        arg1->_pad_250[5] = layout_height:1.b
00401cfa        arg1->_pad_250[6] = layout_height:2.b
00401cfa        arg1->_pad_250[7] = layout_height:3.b
00401d06        arg1->layout_anchor_y = arg5
00401d0c        arg1->_pad_274[0] = arg8[0]
00401d0c        arg1->_pad_274[1] = arg8[1]
00401d0c        arg1->_pad_274[2] = arg8[2]
00401d0c        arg1->_pad_274[3] = arg8[3]
00401d12        arg1->aux_progress = 0f
00401d18        arg1->aux_step = 0f
00401d28        return layout_frontend_widget(arg1)
