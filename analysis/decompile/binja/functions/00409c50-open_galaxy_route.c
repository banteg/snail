/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: open_galaxy_route @ 0x409c50 */

00409c50        int32_t selected_level_index_1 = selected_level_index
00409c5a        struct FrontendWidget* selected_title_widget_2 = galaxy->selected_title_widget
00409c60        galaxy->route_state = 1
00409c67        galaxy->selected_index = selected_level_index_1
00409c6d        unhide_border_init(selected_title_widget_2)
00409ca6        rstrcpy_checked_ascii(&galaxy->selected_title_widget->text_buffer, &galaxy->route_names[galaxy->route_slots[galaxy->selected_index].record.route_name_index])
00409cd3        galaxy->selected_title_widget->layout_anchor_x = fconvert.s(fconvert.t((&galaxy->route_slots[0].record.map_x)[galaxy->selected_index * 0xa8]) + fconvert.t(60f))
00409cfe        galaxy->selected_title_widget->layout_anchor_y = fconvert.s(fconvert.t((&galaxy->route_slots[0].record.map_y)[galaxy->selected_index * 0xa8]) - fconvert.t(130f))
00409d0a        float max_y
00409d0a        float min_x
00409d0a        float min_y
00409d0a        while (true)
00409d0a        layout_frontend_widget(galaxy->selected_title_widget)
00409d15        unhide_border_init(galaxy->selected_detail_widget)
00409d41        rstrcpy_checked_ascii(&galaxy->selected_detail_widget->text_buffer, &galaxy->route_slots[0].record.detail_text[galaxy->selected_index * 0x2a0])
00409d56        stack_widget_below(galaxy->selected_detail_widget, galaxy->selected_title_widget)
00409d61        unhide_border_init(galaxy->selected_description_widget)
00409d8f        rstrcpy_checked_ascii(&galaxy->selected_description_widget->text_buffer, &galaxy->route_slots[0].record.description_text[galaxy->selected_index * 0x2a0])
00409da4        stack_widget_below(galaxy->selected_description_widget, galaxy->selected_detail_widget)
00409daf        unhide_border_init(galaxy->play_or_deliver_widget)
00409db4        struct FrontendWidget* selected_title_widget = galaxy->selected_title_widget
00409dd8        galaxy->play_or_deliver_widget->anchor_x = fconvert.s(fconvert.t(selected_title_widget->layout_width) * fconvert.t(0.5f) + fconvert.t(selected_title_widget->layout_left) - fconvert.t(320f))
00409deb        stack_widget_below(galaxy->play_or_deliver_widget, galaxy->selected_description_widget)
00409e1d        if (galaxy->level_progress_base->sub_high_score.time_trial_route_records[galaxy->selected_index].active != 1 || galaxy->route_mode != 2)
00409e80        hide_border_init(galaxy->replay_widget)
00409e25        unhide_border_init(galaxy->replay_widget)
00409e2a        struct FrontendWidget* selected_title_widget_1 = galaxy->selected_title_widget
00409e4e        galaxy->replay_widget->anchor_x = fconvert.s(fconvert.t(selected_title_widget_1->layout_width) * fconvert.t(0.5f) + fconvert.t(selected_title_widget_1->layout_left) - fconvert.t(320f))
00409e61        stack_widget_below(galaxy->replay_widget, galaxy->selected_description_widget)
00409e73        stack_widget_below(galaxy->play_or_deliver_widget, galaxy->replay_widget)
00409e8b        unhide_border_init(galaxy->bounds_frame_widget)
00409e90        struct FrontendWidget* selected_title_widget_3 = galaxy->selected_title_widget
00409ead        min_x = 1000f
00409eb5        selected_level_index = 0xc47a0000
00409ebd        min_y = 1000f
00409ec5        max_y = -1000f
00409ecd        galaxy_border_bound(galaxy, &min_x, &selected_level_index, &min_y, &max_y, selected_title_widget_3)
00409eef        galaxy_border_bound(galaxy, &min_x, &selected_level_index, &min_y, &max_y, galaxy->selected_detail_widget)
00409f11        galaxy_border_bound(galaxy, &min_x, &selected_level_index, &min_y, &max_y, galaxy->selected_description_widget)
00409f33        galaxy_border_bound(galaxy, &min_x, &selected_level_index, &min_y, &max_y, galaxy->play_or_deliver_widget)
00409f42        max_y = fconvert.s(fconvert.t(max_y) + fconvert.t(8f))
00409f50        min_x = fconvert.s(fconvert.t(min_x) - fconvert.t(8f))
00409f58        long double x87_r7_17 = fconvert.t(selected_level_index) + fconvert.t(8f)
00409f5e        selected_level_index = fconvert.s(x87_r7_17)
00409f62        long double temp1_1 = fconvert.t(630f)
00409f62        x87_r7_17 - temp1_1
00409f6d        if ((((x87_r7_17 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_17, temp1_1) ? 1 : 0) << 0xa | (x87_r7_17 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00409f9c        galaxy->selected_title_widget->layout_anchor_x = fconvert.s(fconvert.t((&galaxy->route_slots[0].record.map_x)[galaxy->selected_index * 0xa8]) - (fconvert.t(selected_level_index) - fconvert.t(min_x)) - fconvert.t(40f))
00409fa2        long double x87_r7_22 = fconvert.t(min_y)
00409fa6        long double temp2_1 = fconvert.t(50f)
00409fa6        x87_r7_22 - temp2_1
00409fb1        if ((((x87_r7_22 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_22, temp2_1) ? 1 : 0) << 0xa | (x87_r7_22 == temp2_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00409fb9        galaxy->selected_title_widget->layout_anchor_y = 50f
00409fc3        long double x87_r7_23 = fconvert.t(max_y)
00409fc7        long double temp3_1 = fconvert.t(450f)
00409fc7        x87_r7_23 - temp3_1
00409fd2        if ((((x87_r7_23 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_23, temp3_1) ? 1 : 0) << 0xa | (x87_r7_23 == temp3_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00409fe8        galaxy->selected_title_widget->layout_anchor_y = fconvert.s(fconvert.t(450f) - (fconvert.t(max_y) - fconvert.t(min_y)))
00409fee        long double x87_r7_27 = fconvert.t(selected_level_index)
00409ff2        long double temp4_1 = fconvert.t(631f)
00409ff2        x87_r7_27 - temp4_1
00409ffd        if ((((x87_r7_27 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_27, temp4_1) ? 1 : 0) << 0xa | (x87_r7_27 == temp4_1 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
0040a003        long double x87_r7_28 = fconvert.t(min_y)
0040a007        long double temp5_1 = fconvert.t(49f)
0040a007        x87_r7_28 - temp5_1
0040a012        if ((((x87_r7_28 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_28, temp5_1) ? 1 : 0) << 0xa | (x87_r7_28 == temp5_1 ? 1 : 0) << 0xe):1.b & 1) == 0)
0040a018        long double x87_r7_29 = fconvert.t(max_y)
0040a01c        long double temp6_1 = fconvert.t(451f)
0040a01c        x87_r7_29 - temp6_1
0040a027        if ((((x87_r7_29 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_29, temp6_1) ? 1 : 0) << 0xa | (x87_r7_29 == temp6_1 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
0040a027        break
0040a03b        galaxy->bounds_frame_widget->authored_width = fconvert.s(fconvert.t(selected_level_index) - fconvert.t(min_x))
0040a04c        galaxy->bounds_frame_widget->authored_height = fconvert.s(fconvert.t(max_y) - fconvert.t(min_y))
0040a059        galaxy->bounds_frame_widget->authored_left = min_x
0040a066        galaxy->bounds_frame_widget->authored_top = min_y
0040a069        struct FrontendWidget* bounds_frame_widget = galaxy->bounds_frame_widget
0040a087        galaxy->play_or_deliver_widget->anchor_x = fconvert.s(fconvert.t(bounds_frame_widget->authored_width) * fconvert.t(0.5f) + fconvert.t(bounds_frame_widget->authored_left) - fconvert.t(320f))
0040a08d        struct FrontendWidget* bounds_frame_widget_1 = galaxy->bounds_frame_widget
0040a0ac        galaxy->replay_widget->anchor_x = fconvert.s(fconvert.t(bounds_frame_widget_1->authored_width) * fconvert.t(0.5f) + fconvert.t(bounds_frame_widget_1->authored_left) - fconvert.t(320f))
0040a0b5        return
