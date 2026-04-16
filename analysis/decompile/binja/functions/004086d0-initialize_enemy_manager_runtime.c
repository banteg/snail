/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_enemy_manager_runtime @ 0x4086d0 */

004086d6        initialize_renderable_bod(arg1)
004086d6        int16_t top = 0xffff
004086db        char** edi = &arg1[0x53]
004086e1        int32_t i_2 = 0xa
004086f4        int32_t i
004086e8        initialize_renderable_bod(edi)
004086e8        top -= 1
004086ed        edi = &edi[0x20]
004086f3        i = i_2
004086f3        i_2 -= 1
004086f4        do while (i != 1)
004086fe        initialize_renderable_bod(&arg1[0x193])
00408721        initialize_array_with_constructor(&arg1[0x1e7], 0x80, 5, initialize_renderable_bod)
00408726        arg1[0x193] = &data_49735c
00408734        initialize_renderable_bod(&arg1[0x28a])
00408757        initialize_array_with_constructor(&arg1[0x2de], 0x80, 5, initialize_renderable_bod)
0040875c        arg1[0x28a] = &data_49735c
0040876a        initialize_renderable_bod(&arg1[0x381])
0040878d        initialize_array_with_constructor(&arg1[0x3d5], 0x80, 5, initialize_renderable_bod)
00408792        arg1[0x381] = &data_49735c
004087a0        initialize_renderable_bod(&arg1[0x478])
004087a0        int16_t top_4 = top - 4
004087bb        char** ebx = &arg1[0x4cc]
004087c1        int32_t i_3 = 5
004087d4        int32_t i_1
004087c8        initialize_renderable_bod(ebx)
004087c8        top_4 -= 1
004087cd        ebx = &ebx[0x20]
004087d3        i_1 = i_3
004087d3        i_3 -= 1
004087d4        do while (i_1 != 1)
004087dc        arg1[0x478] = &data_49735c
004087e2        initialize_renderable_bod(&arg1[0x573])
004087ed        initialize_renderable_bod(&arg1[0x593])
004087fa        initialize_renderable_bod(&arg1[0x625])
004087ff        arg1[0x625] = &data_497358
00408805        *arg1 = &data_497354
00408811        return arg1
