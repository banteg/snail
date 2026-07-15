/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_options_menu @ 0x41af60 */

0041af6c        g_runtime_config.stream_volume = options->music_volume_widget->slider_position_target
0041af7b        g_runtime_config.sample_volume = options->sound_volume_widget->slider_position_target
0041af87        char* var_c
0041af87        char* var_8
0041af87        if (g_runtime_config.fullscreen_enabled == 0)
0041af9d        var_8 = "Full-screen Off"
0041afa8        var_c = &options->fullscreen_widget->text_buffer.raw
0041af8c        var_8 = "Full-screen On"
0041af97        var_c = &options->fullscreen_widget->text_buffer
0041afa9        rstrcpy_checked_ascii(var_c, var_8)
0041afae        struct FrontendWidget* fullscreen_widget = options->fullscreen_widget
0041afb4        enum FrontendWidgetFlag widget_flags = fullscreen_widget->widget_flags
0041afbc        if ((widget_flags.b & 0x20) != 0)
0041afbe        widget_flags.b &= 0xdf
0041afc0        fullscreen_widget->widget_flags = widget_flags
0041afcd        if (g_runtime_config.fullscreen_enabled == 0)
0041afe4        set_fullscreen_mode(1)
0041afec        g_runtime_config.fullscreen_enabled = 1
0041afd1        set_fullscreen_mode(0)
0041afd9        g_runtime_config.fullscreen_enabled = 0
0041aff3        struct FrontendWidget* sound_volume_widget = options->sound_volume_widget
0041aff6        enum FrontendWidgetFlag widget_flags_1 = sound_volume_widget->widget_flags
0041affe        if ((widget_flags_1.b & 0x20) != 0)
0041b000        widget_flags_1.b &= 0xdf
0041b002        sound_volume_widget->widget_flags = widget_flags_1
0041b008        struct FrontendWidget* back_widget = options->back_widget
0041b00b        enum FrontendWidgetFlag widget_flags_2 = back_widget->widget_flags
0041b013        if ((widget_flags_2.b & 0x20) != 0)
0041b015        widget_flags_2.b &= 0xdf
0041b017        back_widget->widget_flags = widget_flags_2
0041b01f        destroy_options_menu(options)
0041b029        g_game_base->frontend_link_latch = 0
0041b038        g_game_base->players[0].frontend_state = options->previous_frontend_state
0041b040        apply_audio_config_volumes(options)
0041b045        long double x87_r7 = fconvert.t(options->previous_sample_volume)
0041b048        long double temp0 = fconvert.t(g_runtime_config.sample_volume)
0041b048        x87_r7 - temp0
0041b053        if ((((x87_r7 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7, temp0) ? 1 : 0) << 0xa | (x87_r7 == temp0 ? 1 : 0) << 0xe):1.b & 0x40) == 0)
0041b05c        play_sound_effect(8)
0041b066        options->previous_sample_volume = g_runtime_config.sample_volume
0041b06a        return
