/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_tip @ 0x448a40 */

00448a4f        slot->active = 1
00448a55        if (definition == 0)
00448a5c        slot->definition = &data_4ac5c8
00448a57        slot->definition = definition
00448a74        slot->widget_main = allocate_border(data_4df904 + 0xb4c)
00448a7a        struct TipMessageDefinition* definition_4 = slot->definition
00448a7f        float layout_y_1 = definition_4->layout_y
00448a8b        uint32_t text_alignment = (sx.d(not.b((slot->definition->flags).b)) & 4) u>> 1
00448aa6        struct Color4f color
00448aa6        struct Color4f* color_1 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00448abf        initialize_frontend_widget(slot->widget_main, 2, definition_4->text, 0x14, definition_4->layout_y, definition_4->text_scale, color_1, text_alignment, layout_y_1)
00448ac4        struct TipMessageDefinition* definition_1 = slot->definition
00448acb        if ((definition_1->flags.b & 2) != 0)
00448acd        slot->dismiss_progress = 0f
00448adf        slot->dismiss_step = fconvert.s(fconvert.t(1f) / (fconvert.t(definition_1->dismiss_seconds) * fconvert.t(60f)))
00448ae5        if ((definition_1->flags.b & 1) == 0)
00448c09        slot->widget_ok = nullptr
00448c0c        slot->widget_disable = nullptr
00448afb        slot->widget_ok = allocate_border(data_4df904 + 0xb4c)
00448b04        if (show_disable_button != 0)
00448bc5        float layout_y = slot->definition->layout_y
00448bdf        struct Color4f* color_4 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00448bf3        initialize_frontend_widget(slot->widget_ok, 0x14, "OK", 0x14, 0f, 0f, color_4, 2, layout_y)
00448bf8        void* widget_main = slot->widget_main
00448bfb        slot->widget_disable = nullptr
00448c02        stack_widget_below(slot->widget_ok, widget_main)
00448b0a        struct TipMessageDefinition* definition_2 = slot->definition
00448b0d        struct TipMessageDefinition* __saved_edi_1 = definition_2
00448b1b        float __saved_edi_2 = fconvert.s(fconvert.t(definition_2->layout_y) + fconvert.t(40f))
00448b34        struct Color4f* color_2 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00448b48        initialize_frontend_widget(slot->widget_ok, 0x14, "OK", 0x14, 0f, 0f, color_2, 2, __saved_edi_2)
00448b59        void* eax_9
00448b59        int32_t __saved_edi_9
00448b59        eax_9, __saved_edi_9 = allocate_border(data_4df904 + 0xb4c)
00448b5e        slot->widget_disable = eax_9
00448b64        int32_t __saved_edi_3 = __saved_edi_9
00448b72        float __saved_edi_4 = fconvert.s(fconvert.t(slot->definition->layout_y) - fconvert.t(60f))
00448b8b        struct Color4f* color_3 = set_color_rgba(&color, 1f, 1f, 1f, 1f)
00448b9f        initialize_frontend_widget(slot->widget_disable, 0x14, "Disable", 0x14, 0f, 0f, color_3, 2, __saved_edi_4)
00448bab        stack_widget_below(slot->widget_disable, slot->widget_main)
00448bb7        stack_widget_below(slot->widget_ok, slot->widget_main)
00448c15        struct TipMessageDefinition* definition_3 = slot->definition
00448c1e        slot->previous_outer_owner = *(data_4df904 + 0x1b8)
00448c21        int32_t eax_11
00448c21        eax_11.b = definition_3->flags.b
00448c27        if ((eax_11.b & 1) != 0)
00448c2f        *(data_4df904 + 0x1b8) = 0x16
00448c3c        return
