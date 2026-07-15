/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_player_presentation_controller @ 0x4086d0 */

004086d6        initialize_renderable_bod(snail)
004086db        struct PresentationAnimationSlot (* edi)[0xa] = &snail->cutscene_animation_slots
004086e1        int32_t i_2 = 0xa
004086f4        int32_t i
004086e8        initialize_renderable_bod(edi)
004086ed        edi = &(*edi)[1]
004086f3        i = i_2
004086f3        i_2 -= 1
004086f4        do while (i != 1)
004086fe        initialize_renderable_bod(&snail->weapon_channels)
00408721        initialize_array_with_constructor(&snail->weapon_channels[0].animation_slots, 0x80, 5, initialize_renderable_bod)
00408726        snail->weapon_channels[0].body.bod.bod.vtable = &g_weapon_noop_vtable
00408734        initialize_renderable_bod(&snail->weapon_channels[1])
00408757        initialize_array_with_constructor(&snail->weapon_channels[1].animation_slots, 0x80, 5, initialize_renderable_bod)
0040875c        snail->weapon_channels[1].body.bod.bod.vtable = &g_weapon_noop_vtable
0040876a        initialize_renderable_bod(&snail->weapon_channels[2])
0040878d        initialize_array_with_constructor(&snail->weapon_channels[2].animation_slots, 0x80, 5, initialize_renderable_bod)
00408792        snail->weapon_channels[2].body.bod.bod.vtable = &g_weapon_noop_vtable
004087a0        initialize_renderable_bod(&snail->jetpack_channel)
004087bb        struct PresentationAnimationSlot (* ebx)[0x5] = &snail->jetpack_channel.animation_slots
004087c1        int32_t i_3 = 5
004087d4        int32_t i_1
004087c8        initialize_renderable_bod(ebx)
004087cd        ebx = &(*ebx)[1]
004087d3        i_1 = i_3
004087d3        i_3 -= 1
004087d4        do while (i_1 != 1)
004087dc        snail->jetpack_channel.body.bod.bod.vtable = &g_weapon_noop_vtable
004087e2        initialize_renderable_bod(&snail->snail_hotspot_source_body)
004087ed        initialize_renderable_bod(&snail->snail_hotspot_body)
004087fa        initialize_renderable_bod(&snail->invincible_shell)
004087ff        snail->invincible_shell.body.bod.bod.vtable = &g_invincible_shell_update_vtable
00408805        snail->body.bod.bod.vtable = &g_player_presentation_noop_vtable
00408811        return snail
