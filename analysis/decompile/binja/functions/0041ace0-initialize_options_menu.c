/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_options_menu @ 0x41ace0 */

0041acf1        hide_all_borders(&g_game_base->border_manager)
0041acfc        g_game_base->frontend_link_latch = 1
0041ad30        options->fullscreen_widget = allocate_border(&g_game_base->border_manager)
0041ad33        struct tColour color
0041ad33        struct tColour* color_1 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
0041ad4f        initialize_frontend_widget(options->fullscreen_widget, 0x14, &g_blank_text, 0x14, 90f, 75f, color_1, 2, 0f)
0041ad54        struct FrontendWidget* fullscreen_widget = options->fullscreen_widget
0041ad63        fullscreen_widget->layout_anchor_y = fconvert.s(fconvert.t(fullscreen_widget->layout_anchor_y) + fconvert.t(8f))
0041ad95        options->sound_volume_widget = allocate_border(&g_game_base->border_manager)
0041ad98        struct tColour* color_2 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
0041adb7        initialize_frontend_widget(options->sound_volume_widget, 0x900004, "     Sounds Volume     >", 0x14, 90f, 400f, color_2, 2, 0f)
0041adc3        stack_widget_below(options->sound_volume_widget, options->fullscreen_widget)
0041add0        options->sound_volume_widget->slider_position_target = g_runtime_config.sample_volume
0041addf        options->sound_volume_widget->slider_position_current = g_runtime_config.sample_volume
0041adea        (*options->sound_volume_widget->list_kind)()
0041ae19        options->music_volume_widget = allocate_border(&g_game_base->border_manager)
0041ae1c        struct tColour* color_3 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
0041ae3b        initialize_frontend_widget(options->music_volume_widget, 0x100004, "      Music Volume      >", 0x14, 90f, 400f, color_3, 2, 0f)
0041ae47        stack_widget_below(options->music_volume_widget, options->sound_volume_widget)
0041ae55        options->music_volume_widget->slider_position_target = g_runtime_config.stream_volume
0041ae63        options->music_volume_widget->slider_position_current = g_runtime_config.stream_volume
0041ae6e        (*options->music_volume_widget->list_kind)()
0041ae9c        options->back_widget = allocate_border(&g_game_base->border_manager)
0041ae9f        struct tColour* color_4 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
0041aebb        initialize_frontend_widget(options->back_widget, 0x14, "Back", 0x14, 90f, 400f, color_4, 2, 0f)
0041aec7        stack_widget_below(options->back_widget, options->music_volume_widget)
0041aed2        options->previous_sample_volume = g_runtime_config.sample_volume
0041aed9        return
