/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: layout_frontend_widget @ 0x4024a0 */

004024a6        struct FrontendWidget* slider_value_widget = widget
004024b6        while (true)
004024b6        uint32_t result = slider_value_widget->widget_flags
004024bf        float* ebx_1
004024bf        float* edi_1
004024bf        if ((result:1.b & 8) != 0)
004024c7        float layout_top = slider_value_widget->layout_top
004024cd        ebx_1 = &slider_value_widget->layout_left
004024d3        edi_1 = &slider_value_widget->layout_top
004024d9        slider_value_widget->layout_anchor_x = slider_value_widget->layout_left
004024df        slider_value_widget->layout_anchor_y = layout_top
004024ef        if ((result & 0x10000) == 0)
00402557        edi_1 = &slider_value_widget->layout_top
00402564        ebx_1 = &slider_value_widget->layout_left
00402584        result = layout_and_queue_wrapped_font_text(&slider_value_widget->text_buffer.raw, slider_value_widget->font_id, slider_value_widget->font_scale, slider_value_widget->layout_anchor_x, slider_value_widget->layout_anchor_y, ebx_1, edi_1, &slider_value_widget->layout_width, &slider_value_widget->layout_height, slider_value_widget->text_effect_current, (data_4df934.d u>> 8).b & 1, slider_value_widget->text_alignment, slider_value_widget->anchor_x, 0x1000000, &slider_value_widget->idle_text_color.r, 1, 0)
004024f1        float authored_left = slider_value_widget->authored_left
004024f4        float authored_top = slider_value_widget->authored_top
004024fa        ebx_1 = &slider_value_widget->layout_left
00402500        edi_1 = &slider_value_widget->layout_top
00402506        slider_value_widget->layout_width = slider_value_widget->authored_width
0040250c        (ebx_1 - 0x238)->layout_left = authored_left
0040250e        result = slider_value_widget->authored_height
00402511        (edi_1 - 0x23c)->layout_top = authored_top
00402513        slider_value_widget->layout_height = result
0040258e        float layout_top_1 = (edi_1 - 0x23c)->layout_top
00402590        slider_value_widget->clamped_left = (ebx_1 - 0x238)->layout_left
00402596        uint32_t widget_flags = slider_value_widget->widget_flags
004025a2        slider_value_widget->clamped_top = layout_top_1
004025a8        if ((widget_flags & 0x20000000) == 0)
004025b6        long double x87_r7_3 = fconvert.t((ebx_1 - 0x238)->layout_left) + fconvert.t(slider_value_widget->hot_padding) + fconvert.t(slider_value_widget->layout_width)
004025bc        long double temp0_1 = fconvert.t(640f)
004025bc        x87_r7_3 - temp0_1
004025c2        result.w = (x87_r7_3 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_3, temp0_1) ? 1 : 0) << 0xa | (x87_r7_3 == temp0_1 ? 1 : 0) << 0xe
004025c7        if ((result:1.b & 0x41) != 0)
004025e5        long double x87_r7_8 = fconvert.t((ebx_1 - 0x238)->layout_left) - fconvert.t(slider_value_widget->hot_padding)
004025eb        long double temp1_1 = fconvert.t(0f)
004025eb        x87_r7_8 - temp1_1
004025f1        result.w = (x87_r7_8 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp1_1) ? 1 : 0) << 0xa | (x87_r7_8 == temp1_1 ? 1 : 0) << 0xe
004025f6        if ((result:1.b & 1) != 0)
004025fe        slider_value_widget->clamped_left = slider_value_widget->hot_padding
004025db        slider_value_widget->clamped_left = fconvert.s(fconvert.t(640f) - fconvert.t(slider_value_widget->hot_padding) - fconvert.t(slider_value_widget->layout_width))
0040260a        long double x87_r7_10 = fconvert.t(slider_value_widget->hot_padding) + fconvert.t((edi_1 - 0x23c)->layout_top)
0040260c        long double temp2_1 = fconvert.t(480f)
0040260c        x87_r7_10 - temp2_1
00402612        result.w = (x87_r7_10 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_10, temp2_1) ? 1 : 0) << 0xa | (x87_r7_10 == temp2_1 ? 1 : 0) << 0xe
00402617        if ((result:1.b & 0x41) != 0)
0040262f        long double x87_r7_14 = fconvert.t((edi_1 - 0x23c)->layout_top) - fconvert.t(slider_value_widget->hot_padding)
00402635        long double temp3_1 = fconvert.t(0f)
00402635        x87_r7_14 - temp3_1
0040263b        result.w = (x87_r7_14 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_14, temp3_1) ? 1 : 0) << 0xa | (x87_r7_14 == temp3_1 ? 1 : 0) << 0xe
00402640        if ((result:1.b & 1) != 0)
00402648        slider_value_widget->clamped_top = slider_value_widget->hot_padding
00402625        slider_value_widget->clamped_top = fconvert.s(fconvert.t(480f) - fconvert.t(slider_value_widget->hot_padding))
00402654        long double x87_r7_16 = fconvert.t(slider_value_widget->clamped_left) - fconvert.t((ebx_1 - 0x238)->layout_left)
00402658        result = widget_flags & 0x100000
00402665        slider_value_widget->anchor_x = fconvert.s(x87_r7_16 + fconvert.t(slider_value_widget->anchor_x))
00402671        slider_value_widget->layout_anchor_x = fconvert.s(x87_r7_16 + fconvert.t(slider_value_widget->layout_anchor_x))
00402685        slider_value_widget->layout_anchor_y = fconvert.s(fconvert.t(slider_value_widget->clamped_top) - fconvert.t((edi_1 - 0x23c)->layout_top) + fconvert.t(slider_value_widget->layout_anchor_y))
0040268b        long double x87_r7_21 = fconvert.t(slider_value_widget->clamped_left)
00402691        (ebx_1 - 0x238)->layout_left = fconvert.s(x87_r7_21)
00402693        long double x87_r6_3 = fconvert.t(slider_value_widget->clamped_top)
0040269d        (edi_1 - 0x23c)->layout_top = fconvert.s(x87_r6_3)
0040269f        if (result != 0)
004026bb        slider_value_widget->slider_hit_left = fconvert.s(fconvert.t(slider_value_widget->layout_width) * fconvert.t(0.100000001f) + x87_r7_21 + fconvert.t(4f) - fconvert.t(12f))
004026d5        slider_value_widget->slider_hit_right = fconvert.s(fconvert.t(slider_value_widget->layout_width) * fconvert.t(0.800000012f) + x87_r7_21 - fconvert.t(4f))
004026e9        long double x87_r7_25 = fconvert.t(slider_value_widget->layout_height) * fconvert.t(0.5f) + fconvert.t(fconvert.s(x87_r6_3))
004026f5        slider_value_widget->slider_hit_top = fconvert.s(x87_r7_25 - fconvert.t(6f))
00402707        slider_value_widget->slider_hit_bottom = fconvert.s(x87_r7_25 + fconvert.t(32f) - fconvert.t(6f))
00402713        if ((widget_flags & 0x20000000) != 0 || result == 0)
00402784        return result
00402727        slider_value_widget->slider_more_widget->layout_top = fconvert.s(fconvert.t(slider_value_widget->clamped_top) + fconvert.t(33f))
00402733        layout_frontend_widget(slider_value_widget->slider_more_widget)
0040274a        slider_value_widget->slider_less_widget->layout_top = fconvert.s(fconvert.t(slider_value_widget->clamped_top) + fconvert.t(33f))
00402756        layout_frontend_widget(slider_value_widget->slider_less_widget)
0040276d        slider_value_widget->slider_value_widget->layout_anchor_y = fconvert.s(fconvert.t(slider_value_widget->clamped_top) + fconvert.t(49f))
00402773        slider_value_widget = slider_value_widget->slider_value_widget
