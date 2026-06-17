/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_click_start @ 0x442290 */

004422a0        if (*(data_4df904 + 0x74621) != 0)
004422a0        return
004422ac        struct FrontendWidget* prompt = controller->prompt
004422b4        if (controller->hide_prompt == 0)
004422bd        unhide_border_init(prompt)
004422b6        hide_border_init(prompt)
004422d1        switch (controller->state)
004422de        case 2
004422de        *(data_4df904 + 0x4f270) = 1
004422e5        void* eax_2 = data_4df904
004422f1        if (*(eax_2 + 0x1066bf4) s> 8)
004422f3        *(eax_2 + 0x1066bf4) = 8
004422fd        eax_2 = data_4df904
00442302        char edx = *(eax_2 + 0x1066be8)
0044230a        if (edx == 0)
00442332        label_442332:
00442346        if (controller->hide_prompt == 0 && ((*(*(eax_2 + 0x28c) + 0x3c)).w:1.b & 0x40) != 0)
00442346        goto label_442358
00442322        if ((*(*(eax_2 + 0x1066bec) + *(eax_2 + 0x1066bf4) * 6 + 0x74) & 0x20) != 0)
00442358        label_442358:
00442358        controller->player->startup_track_index = *(eax_2 + 0x1066bf4)
0044235e        controller->state = 3
00442368        void* ecx_6 = data_4df904
00442376        if (*(ecx_6 + 0x1066be8) == 0)
0044237e        int32_t eax_5 = *(ecx_6 + 0x1066bf4) * 3
00442381        *(ecx_6 + (eax_5 << 1) + 0x104719c) |= 0x20
00442390        void* ecx_7 = data_4df904
0044239c        int32_t edx_3 = *(ecx_7 + 0x1066bf4) * 3
0044239f        *(ecx_7 + (edx_3 << 1) + 0x104719c) &= 0xfffe
004423b0        void* eax_7 = data_4df904
004423bb        *(eax_7 + 0x104714c) = *(eax_7 + 0x1066bf4)
004423cd        set_input_controller_pointer_authored_xy(0, 320f, 240f)
004423de        set_input_controller_pointer_authored_xy(1, 320f, 240f)
004423ed        play_sound_effect(8)
004423f3        return
00442326        if (edx == 0)
00442326        goto label_442332
00442401        case 3
00442401        set_math_random_seed(*(data_4df904 + 0x1047190))
00442406        struct FrontendWidget* prompt_1 = controller->prompt
0044240f        controller->state = 4
00442419        controller->teardown_progress = 0f
00442423        controller->teardown_progress_step = 0.0166666675f
0044242d        data_4df904
0044243a        kill_border(prompt_1)
0044244e        label_44244e:
0044244e        controller->transform.position.y = fconvert.s(fconvert.t(controller->teardown_progress) * fconvert.t(16f) + fconvert.t(controller->transform.position.y))
0044245d        controller->teardown_progress = fconvert.s(fconvert.t(controller->teardown_progress_step) + fconvert.t(controller->teardown_progress))
00442468        void* ecx_11 = data_4df904 + 0x5a8
0044246e        int16_t list_flags = (controller->list_flags).w
00442474        if ((list_flags:1.b & 2) == 0)
0044247b        report_errorf("List remove")
00442483        controller->state = 0
0044248e        return
00442491        if ((list_flags.b & 0x40) != 0)
00442498        report_errorf("List remove NEXTBOD")
004424a0        controller->state = 0
004424ab        return
004424ac        struct ClickStartController* list_next = controller->list_next
004424b1        if (list_next != 0)
004424b6        list_next->list_prev = controller->list_prev
004424b9        struct ClickStartController* list_prev = controller->list_prev
004424be        if (list_prev == 0)
004424cb        *(ecx_11 + 4) = controller->list_next
004424c3        list_prev->list_next = controller->list_next
004424d1        controller->list_next = *(ecx_11 + 8)
004424d4        *(ecx_11 + 8) = controller
004424d7        int32_t list_flags_1 = controller->list_flags
004424da        controller->state = 0
004424e4        list_flags_1:1.b &= 0xfd
004424e7        controller->list_flags = list_flags_1
004422d1        case 4
004422d1        goto label_44244e
004424eb        return
