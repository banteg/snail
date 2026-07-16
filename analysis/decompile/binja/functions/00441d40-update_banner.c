/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_banner @ 0x441d40 */

00441d41        struct Banner* banner_2 = banner
00441d43        int32_t visibility_mode = banner_2->visibility_mode
00441d49        bool c0_1
00441d49        bool c2_1
00441d49        bool c3_1
00441d49        if (visibility_mode == 0)
00441d5f        banner = banner_2->owner_player
00441d62        long double x87_r7_3 = fconvert.t(banner->__offset(0x70).d)
00441d65        long double temp1_1 = fconvert.t(40f)
00441d65        x87_r7_3 - temp1_1
00441d65        c0_1 = x87_r7_3 < temp1_1
00441d65        c2_1 = is_unordered.t(x87_r7_3, temp1_1)
00441d65        c3_1 = x87_r7_3 == temp1_1
00441d70        label_441d70:
00441d70        uint32_t list_flags = banner_2->bod.bod.list_flags
00441d73        if ((((c0_1 ? 1 : 0) << 8 | (c2_1 ? 1 : 0) << 0xa | (c3_1 ? 1 : 0) << 0xe):1.b & 1) == 0)
00441d79        list_flags.b &= 0xdf
00441d75        list_flags.b |= 0x20
00441d7b        banner_2->bod.bod.list_flags = list_flags
00441d4c        if (visibility_mode == 1)
00441d54        long double x87_r7_2 = fconvert.t(banner_2->bod.position.z) - fconvert.t(banner_2->owner_player->body.transform.position.z)
00441d57        long double temp4_1 = fconvert.t(46f)
00441d57        x87_r7_2 - temp4_1
00441d57        c0_1 = x87_r7_2 < temp4_1
00441d57        c2_1 = is_unordered.t(x87_r7_2, temp4_1)
00441d57        c3_1 = x87_r7_2 == temp4_1
00441d5d        goto label_441d70
00441d81        long double x87_r7_5 = fconvert.t(banner_2->phase_step) + fconvert.t(banner_2->phase)
00441d84        long double temp3 = fconvert.t(1f)
00441d84        x87_r7_5 - temp3
00441d8a        banner_2->phase = fconvert.s(x87_r7_5)
00441d8a        bool c1 = unknown  {fst dword [esi+0x58], st0}
00441d92        if ((((x87_r7_5 < temp3 ? 1 : 0) << 8 | (c1 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_5, temp3) ? 1 : 0) << 0xa | (x87_r7_5 == temp3 ? 1 : 0) << 0xe | 0x3800):1.b & 0x41) == 0)
00441d9a        banner_2->phase = fconvert.s(x87_r7_5 - fconvert.t(1f))
00441daa        struct Banner* banner_1 = banner
00441dbc        banner_2->bod.position.y = fconvert.s(sine(fconvert.s(fconvert.t(banner_2->phase) * fconvert.t(6.28318548f))) * fconvert.t(0.25999999f))
00441dc0        return
