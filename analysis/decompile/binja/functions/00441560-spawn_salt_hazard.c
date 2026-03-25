/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: spawn_salt_hazard @ 0x441560 */

00441561        int32_t eax = 0
00441563        int32_t* edx = arg1 + 0x80
0044156c        while (*edx != 0)
0044156e        eax += 1
0044156f        edx = &edx[0x26]
00441578        if (eax s>= 0x28)
0044157b        return eax
00441585        void* esi = arg1 + eax * 0x98
00441588        int32_t* eax_2 = arg2
0044158c        *(esi + 0x80) = 1
00441596        *(esi + 0x8c) = 0
004415b8        *(esi + 0x90) = fconvert.s(fconvert.t(*(data_4df904 + 0x74650)) * fconvert.t(0.0333333351f))
004415c0        *(esi + 0x68) = *eax_2
004415c5        *(esi + 0x6c) = eax_2[1]
004415cd        *(esi + 0x70) = eax_2[2]
004415d0        set_matrix_rotation_identity(esi + 0x38)
004415de        int32_t var_c = 0x1fff
004415f4        rotate_matrix_world_y(esi + 0x38, fconvert.s((float.t(next_math_random_value()) - fconvert.t(16384f)) * fconvert.t(0.000191747604f)))
004415f9        *(esi + 0x94) = 1
0044160a        void* eax_5 = data_4df904 + 0x3ca224
00441617        if ((0x200 & *(esi + 4)) != 0)
0044161e        report_errorf("List ADDafter")
00441627        return 0
0044162a        *(esi + 8) = eax_5
00441630        *(esi + 0xc) = *(eax_5 + 0xc)
00441633        *(eax_5 + 0xc) = esi
00441636        void* eax_6 = *(esi + 0xc)
0044163b        if (eax_6 != 0)
0044163d        *(eax_6 + 8) = esi
00441643        int32_t eax_8 = *(esi + 4) | 0x200
00441645        *(esi + 4) = eax_8
00441649        return eax_8
