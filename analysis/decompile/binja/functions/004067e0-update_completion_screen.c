/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_completion_screen @ 0x4067e0 */

004067f4        switch (prompt->state - 2)
0040690d        case 0
0040690d        struct FrontendWidget* yes_button_3 = prompt->yes_button
00406910        uint32_t widget_flags_3 = yes_button_3->widget_flags
00406918        if ((widget_flags_3.b & 0x20) != 0)
0040691e        widget_flags_3.b &= 0xdf
00406922        yes_button_3->widget_flags = widget_flags_3
00406934        complete_subgame(data_4df904 + 0x74618, 1)
00406939        void* eax_7 = data_4df904
00406945        if (*(eax_7 + 0x30d) != 1)
00406996        destroy_completion_screen(prompt)
004069a6        uninit_pause_menu(data_4df904 + 0x7462c)
004069b2        *(data_4df904 + 0x74621) = 0
004069bd        set_sprite_manager_paused(&g_sprite_manager, 0)
004069ce        destroy_subgame(data_4df904 + 0x74618)
004069d3        void* ecx_22 = data_4df904
004069d9        int32_t eax_10 = *(ecx_22 + 0x74658)
004069e7        if (eax_10 == 4 || eax_10 == 1)
004069fe        initialize_subgame(ecx_22 + 0x74618)
004069e9        *(ecx_22 + 0x1b8) = 2
0040694f        prompt->previous_frontend_state = *(eax_7 + 0x1b8)
00406952        destroy_completion_screen(prompt)
00406962        uninit_pause_menu(data_4df904 + 0x7462c)
0040696e        *(data_4df904 + 0x74621) = 0
00406979        set_sprite_manager_paused(&g_sprite_manager, 0)
0040698a        destroy_subgame(data_4df904 + 0x74618)
00406a54        case 1
00406a54        struct FrontendWidget* yes_button_5 = prompt->yes_button
00406a57        uint32_t widget_flags_5 = yes_button_5->widget_flags
00406a5f        if ((widget_flags_5.b & 0x20) != 0)
00406a65        widget_flags_5.b &= 0xdf
00406a67        yes_button_5->widget_flags = widget_flags_5
00406a6f        destroy_completion_screen(prompt)
00406a80        uninit_pause_menu(data_4df904 + 0x7462c)
00406a91        *(data_4df904 + 0x74621) = 0
00406a97        set_sprite_manager_paused(&g_sprite_manager, 0)
00406aa7        destroy_subgame(data_4df904 + 0x74618)
00406aac        void* eax_13 = data_4df904
00406ab7        *(eax_13 + 0x1b8) = *(eax_13 + 0x1066bf0)
00406ac2        case 2
00406ac2        struct FrontendWidget* yes_button_6 = prompt->yes_button
00406ac5        uint32_t widget_flags_6 = yes_button_6->widget_flags
00406acd        if ((widget_flags_6.b & 0x20) != 0)
00406ad3        widget_flags_6.b &= 0xdf
00406ad5        yes_button_6->widget_flags = widget_flags_6
00406add        label_406add:
00406add        destroy_completion_screen(prompt)
00406aee        destroy_subgame(data_4df904 + 0x74618)
00406af8        *(data_4df904 + 0x1b8) = 2
00406a08        case 5
00406a08        struct FrontendWidget* yes_button_4 = prompt->yes_button
00406a0b        uint32_t widget_flags_4 = yes_button_4->widget_flags
00406a13        if ((widget_flags_4.b & 0x20) != 0)
00406a19        widget_flags_4.b &= 0xdf
00406a1b        yes_button_4->widget_flags = widget_flags_4
00406a23        destroy_completion_screen(prompt)
00406a33        uninit_pause_menu(data_4df904 + 0x7462c)
00406a3f        *(data_4df904 + 0x74621) = 0
00406a4a        set_sprite_manager_paused(&g_sprite_manager, 0)
00406aee        destroy_subgame(data_4df904 + 0x74618)
00406af8        *(data_4df904 + 0x1b8) = 2
00406b10        case 6
00406b10        update_new_game_menu(data_4df904 + 0x4f2dc)
00406b15        struct FrontendWidget* yes_button_7 = prompt->yes_button
00406b18        uint32_t widget_flags_7 = yes_button_7->widget_flags
00406b20        if ((widget_flags_7.b & 0x20) != 0)
00406b22        widget_flags_7.b &= 0xdf
00406b24        char* var_c_1 = "Alpha72.url"
00406b29        yes_button_7->widget_flags = widget_flags_7
00406b2f        sub_433050()
00406b3f        *(data_4df904 + 0x1b8) = 0
00406b4a        *(data_4df904 + 0x568) = 0
00406b50        destroy_completion_screen(prompt)
004067fb        case 7
004067fb        struct FrontendWidget* yes_button = prompt->yes_button
004067fe        uint32_t widget_flags = yes_button->widget_flags
00406806        if ((widget_flags.b & 0x20) != 0)
0040680c        widget_flags.b &= 0xdf
0040680e        yes_button->widget_flags = widget_flags
00406816        destroy_completion_screen(prompt)
00406820        *(data_4df904 + 0x38) = 3
00406838        case 8
00406838        update_main_menu(data_4df904 + 0x4f324)
0040683d        struct FrontendWidget* yes_button_1 = prompt->yes_button
00406840        uint32_t widget_flags_1 = yes_button_1->widget_flags
00406848        if ((widget_flags_1.b & 0x20) != 0)
0040684e        widget_flags_1.b &= 0xdf
00406850        yes_button_1->widget_flags = widget_flags_1
00406858        destroy_completion_screen(prompt)
0040685d        data_4df904
00406869        destroy_main_menu()
0040686e        void* eax_3 = data_4df904
00406876        if (*(eax_3 + 0x38) == 0)
0040687c        *(eax_3 + 0x38) = 1
00406893        case 9
00406893        update_galaxy(data_4df904 + 0x12d4638)
00406898        struct FrontendWidget* yes_button_2 = prompt->yes_button
0040689b        uint32_t widget_flags_2 = yes_button_2->widget_flags
004068a3        if ((widget_flags_2.b & 0x20) != 0)
004068a9        widget_flags_2.b &= 0xdf
004068ab        yes_button_2->widget_flags = widget_flags_2
004068bd        destroy_galaxy(data_4df904 + 0x12d4638)
004068d0        complete_subgame(data_4df904 + 0x74618, 1)
004068d5        void* eax_5 = data_4df904
004068e1        if (*(eax_5 + 0x30d) != 1)
004068e1        goto label_406add
004068ef        prompt->previous_frontend_state = *(eax_5 + 0x1b8)
004068f2        destroy_completion_screen(prompt)
00406903        destroy_subgame(data_4df904 + 0x74618)
00406b55        struct FrontendWidget* no_button = prompt->no_button
00406b58        uint32_t widget_flags_8 = no_button->widget_flags
00406b60        if ((widget_flags_8.b & 0x20) == 0)
00406b8d        return widget_flags_8
00406b62        widget_flags_8.b &= 0xdf
00406b64        no_button->widget_flags = widget_flags_8
00406b73        *(data_4df904 + 0x1b8) = prompt->previous_frontend_state
00406b80        *(data_4df904 + 0x568) = 0
00406b86        return destroy_completion_screen(prompt)
