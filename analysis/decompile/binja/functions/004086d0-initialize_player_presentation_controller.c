/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_player_presentation_controller @ 0x4086d0 */

004086d6        initialize_renderable_bod(presentation)
004086d6        int16_t top = 0xffff
004086db        uint8_t (* edi)[0x500] = &presentation->_pad_14c
004086e1        int32_t i_2 = 0xa
004086f4        int32_t i
004086e8        initialize_renderable_bod(edi)
004086e8        top -= 1
004086ed        edi = &(*edi)[0x80]
004086f3        i = i_2
004086f3        i_2 -= 1
004086f4        do while (i != 1)
004086fe        initialize_renderable_bod(&presentation->weapon_channels)
00408721        initialize_array_with_constructor(&presentation->weapon_channels[0]._pad_150, 0x80, 5, initialize_renderable_bod)
00408726        presentation->weapon_channels[0].vtable = &g_presentation_animation_channel_noop_vtable
00408734        initialize_renderable_bod(&presentation->weapon_channels[1])
00408757        initialize_array_with_constructor(&presentation->weapon_channels[1]._pad_150, 0x80, 5, initialize_renderable_bod)
0040875c        presentation->weapon_channels[1].vtable = &g_presentation_animation_channel_noop_vtable
0040876a        initialize_renderable_bod(&presentation->weapon_channels[2])
0040878d        initialize_array_with_constructor(&presentation->weapon_channels[2]._pad_150, 0x80, 5, initialize_renderable_bod)
00408792        presentation->weapon_channels[2].vtable = &g_presentation_animation_channel_noop_vtable
004087a0        initialize_renderable_bod(&presentation->jetpack_channel)
004087a0        int16_t top_4 = top - 4
004087bb        uint8_t (* ebx)[0x24] = &presentation->jetpack_channel._pad_150
004087c1        int32_t i_3 = 5
004087d4        int32_t i_1
004087c8        initialize_renderable_bod(ebx)
004087c8        top_4 -= 1
004087cd        ebx = &(*ebx)[0x80]
004087d3        i_1 = i_3
004087d3        i_3 -= 1
004087d4        do while (i_1 != 1)
004087dc        presentation->jetpack_channel.vtable = &g_presentation_animation_channel_noop_vtable
004087e2        initialize_renderable_bod(&presentation->wobble._pad_10)
004087ed        initialize_renderable_bod(&presentation->_pad_1644[8])
004087fa        initialize_renderable_bod(&presentation->invincible_shell)
004087ff        presentation->invincible_shell.vtable = &g_invincible_shell_update_vtable
00408805        presentation->vtable = &g_player_presentation_noop_vtable
00408811        return presentation
