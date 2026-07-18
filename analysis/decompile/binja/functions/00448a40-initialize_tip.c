/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_tip @ 0x448a40 */

00448a4f        tip->active = 1
00448a55        if (definition == 0)
00448a5c        tip->definition = &g_default_tip_message
00448a57        tip->definition = definition
00448a74        tip->widget_main = allocate_border(&g_game_base->border_manager)
00448a7a        struct TipData* definition_4 = tip->definition
00448a7f        float layout_y_1 = definition_4->layout_y
00448a8b        uint32_t text_alignment = (sx.d(not.b((tip->definition->flags).b)) & 4) u>> 1
00448aa6        struct tColour color
00448aa6        struct tColour* color_1 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00448abf        initialize_frontend_widget(tip->widget_main, 2, definition_4->text, 0x14, definition_4->layout_y, definition_4->text_scale, color_1, text_alignment, layout_y_1)
00448ac4        struct TipData* definition_1 = tip->definition
00448acb        if ((definition_1->flags.b & 2) != 0)
00448acd        tip->dismiss_progress = 0f
00448adf        tip->dismiss_step = fconvert.s(fconvert.t(1f) / (fconvert.t(definition_1->dismiss_seconds) * fconvert.t(60f)))
00448ae5        if ((definition_1->flags.b & 1) == 0)
00448c09        tip->widget_ok = nullptr
00448c0c        tip->widget_disable = nullptr
00448afb        tip->widget_ok = allocate_border(&g_game_base->border_manager)
00448b04        if (hide_disable_button != 0)
00448bc5        float layout_y = tip->definition->layout_y
00448bdf        struct tColour* color_4 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00448bf3        initialize_frontend_widget(tip->widget_ok, 0x14, "OK", 0x14, 0f, 0f, color_4, 2, layout_y)
00448bf8        struct FrontendWidget* widget_main = tip->widget_main
00448bfb        tip->widget_disable = nullptr
00448c02        stack_widget_below(tip->widget_ok, widget_main)
00448b0a        struct TipData* definition_2 = tip->definition
00448b0d        struct TipData* __saved_edi_1 = definition_2
00448b1b        float __saved_edi_2 = fconvert.s(fconvert.t(definition_2->layout_y) + fconvert.t(40f))
00448b34        struct tColour* color_2 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00448b48        initialize_frontend_widget(tip->widget_ok, 0x14, "OK", 0x14, 0f, 0f, color_2, 2, __saved_edi_2)
00448b59        struct FrontendWidget* eax_9
00448b59        int32_t __saved_edi_9
00448b59        eax_9, __saved_edi_9 = allocate_border(&g_game_base->border_manager)
00448b5e        tip->widget_disable = eax_9
00448b64        int32_t __saved_edi_3 = __saved_edi_9
00448b72        float __saved_edi_4 = fconvert.s(fconvert.t(tip->definition->layout_y) - fconvert.t(60f))
00448b8b        struct tColour* color_3 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00448b9f        initialize_frontend_widget(tip->widget_disable, 0x14, "Disable", 0x14, 0f, 0f, color_3, 2, __saved_edi_4)
00448bab        stack_widget_below(tip->widget_disable, tip->widget_main)
00448bb7        stack_widget_below(tip->widget_ok, tip->widget_main)
00448c15        struct TipData* definition_3 = tip->definition
00448c1e        tip->previous_outer_owner = g_game_base->players[0].frontend_state
00448c27        if ((definition_3->flags.b & 1) != 0)
00448c2f        g_game_base->players[0].frontend_state = 0x16
00448c3c        return
