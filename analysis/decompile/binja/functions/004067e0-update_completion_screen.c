/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_completion_screen @ 0x4067e0 */

004067f4        switch (*arg1 - 2)
0040690d        case 0
0040690d        void* ecx_15 = arg1[5]
00406910        int32_t eax_10 = *(ecx_15 + 0x1a0)
00406918        if ((eax_10.b & 0x20) != 0)
0040691e        eax_10.b &= 0xdf
00406922        *(ecx_15 + 0x1a0) = eax_10
00406934        complete_subgame(data_4df904 + 0x74618, 1)
00406939        void* eax_11 = data_4df904
00406945        if (*(eax_11 + 0x30d) != 1)
00406996        destroy_completion_screen(arg1)
004069a6        uninit_pause_menu(data_4df904 + 0x7462c)
004069b2        *(data_4df904 + 0x74621) = 0
004069bd        sub_44e540(&data_790f30, 0)
004069ce        destroy_subgame(data_4df904 + 0x74618)
004069d3        void* ecx_26 = data_4df904
004069d9        int32_t eax_14 = *(ecx_26 + 0x74658)
004069e7        if (eax_14 == 4 || eax_14 == 1)
004069fe        initialize_subgame(ecx_26 + 0x74618)
004069e9        *(ecx_26 + 0x1b8) = 2
0040694f        arg1[2] = *(eax_11 + 0x1b8)
00406952        destroy_completion_screen(arg1)
00406962        uninit_pause_menu(data_4df904 + 0x7462c)
0040696e        *(data_4df904 + 0x74621) = 0
00406979        sub_44e540(&data_790f30, 0)
0040698a        destroy_subgame(data_4df904 + 0x74618)
00406a54        case 1
00406a54        void* ecx_32 = arg1[5]
00406a57        int32_t eax_17 = *(ecx_32 + 0x1a0)
00406a5f        if ((eax_17.b & 0x20) != 0)
00406a65        eax_17.b &= 0xdf
00406a67        *(ecx_32 + 0x1a0) = eax_17
00406a6f        destroy_completion_screen(arg1)
00406a80        uninit_pause_menu(data_4df904 + 0x7462c)
00406a91        *(data_4df904 + 0x74621) = 0
00406a97        sub_44e540(&data_790f30, 0)
00406aa7        destroy_subgame(data_4df904 + 0x74618)
00406aac        void* eax_19 = data_4df904
00406ab7        *(eax_19 + 0x1b8) = *(eax_19 + 0x1066bf0)
00406ac2        case 2
00406ac2        void* ecx_38 = arg1[5]
00406ac5        int32_t eax_20 = *(ecx_38 + 0x1a0)
00406acd        if ((eax_20.b & 0x20) != 0)
00406ad3        eax_20.b &= 0xdf
00406ad5        *(ecx_38 + 0x1a0) = eax_20
00406add        label_406add:
00406add        destroy_completion_screen(arg1)
00406aee        destroy_subgame(data_4df904 + 0x74618)
00406af8        *(data_4df904 + 0x1b8) = 2
00406a08        case 5
00406a08        void* ecx_28 = arg1[5]
00406a0b        int32_t eax_15 = *(ecx_28 + 0x1a0)
00406a13        if ((eax_15.b & 0x20) != 0)
00406a19        eax_15.b &= 0xdf
00406a1b        *(ecx_28 + 0x1a0) = eax_15
00406a23        destroy_completion_screen(arg1)
00406a33        uninit_pause_menu(data_4df904 + 0x7462c)
00406a3f        *(data_4df904 + 0x74621) = 0
00406a4a        sub_44e540(&data_790f30, 0)
00406aee        destroy_subgame(data_4df904 + 0x74618)
00406af8        *(data_4df904 + 0x1b8) = 2
00406b10        case 6
00406b10        update_new_game_menu(data_4df904 + 0x4f2dc)
00406b15        void* ecx_43 = arg1[5]
00406b18        int32_t eax_22 = *(ecx_43 + 0x1a0)
00406b20        if ((eax_22.b & 0x20) != 0)
00406b22        eax_22.b &= 0xdf
00406b24        char* var_c_1 = "Alpha72.url"
00406b29        *(ecx_43 + 0x1a0) = eax_22
00406b2f        sub_433050()
00406b3f        *(data_4df904 + 0x1b8) = 0
00406b4a        *(data_4df904 + 0x568) = 0
00406b50        destroy_completion_screen(arg1)
004067fb        case 7
004067fb        void* ecx = arg1[5]
004067fe        int32_t eax_2 = *(ecx + 0x1a0)
00406806        if ((eax_2.b & 0x20) != 0)
0040680c        eax_2.b &= 0xdf
0040680e        *(ecx + 0x1a0) = eax_2
00406816        destroy_completion_screen(arg1)
00406820        *(data_4df904 + 0x38) = 3
00406838        case 8
00406838        update_main_menu(data_4df904 + 0x4f324)
0040683d        void* ecx_4 = arg1[5]
00406840        int32_t eax_4 = *(ecx_4 + 0x1a0)
00406848        if ((eax_4.b & 0x20) != 0)
0040684e        eax_4.b &= 0xdf
00406850        *(ecx_4 + 0x1a0) = eax_4
00406858        destroy_completion_screen(arg1)
0040685d        data_4df904
00406869        destroy_main_menu()
0040686e        void* eax_5 = data_4df904
00406876        if (*(eax_5 + 0x38) == 0)
0040687c        *(eax_5 + 0x38) = 1
00406893        case 9
00406893        update_galaxy(data_4df904 + 0x12d4638)
00406898        void* ecx_8 = arg1[5]
0040689b        int32_t eax_7 = *(ecx_8 + 0x1a0)
004068a3        if ((eax_7.b & 0x20) != 0)
004068a9        eax_7.b &= 0xdf
004068ab        *(ecx_8 + 0x1a0) = eax_7
004068bd        destroy_galaxy(data_4df904 + 0x12d4638)
004068d0        complete_subgame(data_4df904 + 0x74618, 1)
004068d5        void* eax_8 = data_4df904
004068e1        if (*(eax_8 + 0x30d) != 1)
004068e1        goto label_406add
004068ef        arg1[2] = *(eax_8 + 0x1b8)
004068f2        destroy_completion_screen(arg1)
00406903        destroy_subgame(data_4df904 + 0x74618)
00406b55        void* ecx_45 = arg1[6]
00406b58        int32_t result = *(ecx_45 + 0x1a0)
00406b60        if ((result.b & 0x20) == 0)
00406b8d        return result
00406b62        result.b &= 0xdf
00406b64        *(ecx_45 + 0x1a0) = result
00406b73        *(data_4df904 + 0x1b8) = arg1[2]
00406b80        *(data_4df904 + 0x568) = 0
00406b86        return destroy_completion_screen(arg1)
