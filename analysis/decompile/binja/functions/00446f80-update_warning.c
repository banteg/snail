/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_warning @ 0x446f80 */

00446f88        int32_t ebx
00446f88        ebx.b = *(data_4df904 + 0x74621)
00446f91        if (ebx.b != 0)
00446f91        return 
00446f97        int32_t state = actor->state
00446f9b        if (state == 0)
00446f9b        return 
00446fa2        if (state == 1)
00447009        actor->border->__offset(0x208).d = 0x3f7fbe77
00447016        long double x87_r7_8 = fconvert.t(actor->progress_step) + fconvert.t(actor->progress)
00447019        actor->progress = fconvert.s(x87_r7_8)
0044701c        long double temp2_1 = fconvert.t(1f)
0044701c        x87_r7_8 - temp2_1
00447022        struct FrontendWidget* eax_4
00447022        eax_4.w = (x87_r7_8 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp2_1) ? 1 : 0) << 0xa | (x87_r7_8 == temp2_1 ? 1 : 0) << 0xe
00447027        if ((eax_4:1.b & 0x41) == 0)
00447029        actor->progress = 0f
0044702c        actor->state = 2
00446fa5        if (state == 2)
00446fab        long double x87_r7_1 = fconvert.t(actor->progress)
00446fae        long double temp4_1 = fconvert.t(0.5f)
00446fae        x87_r7_1 - temp4_1
00446fb9        if ((((x87_r7_1 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp4_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp4_1 ? 1 : 0) << 0xe):1.b & 1) == 0)
00446fd4        actor->border->__offset(0x208).d = 0
00446fbb        long double x87_r7_2 = fconvert.t(actor->progress)
00446fc9        actor->border->__offset(0x208).d = fconvert.s(fconvert.t(1f) - (x87_r7_2 + x87_r7_2))
00446fdd        long double x87_r7_6 = fconvert.t(actor->progress_step) + fconvert.t(actor->progress)
00446fe0        actor->progress = fconvert.s(x87_r7_6)
00446fe3        long double temp5_1 = fconvert.t(1f)
00446fe3        x87_r7_6 - temp5_1
00446fe9        struct FrontendWidget* eax_3
00446fe9        eax_3.w = (x87_r7_6 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_6, temp5_1) ? 1 : 0) << 0xa | (x87_r7_6 == temp5_1 ? 1 : 0) << 0xe
00446fee        if ((eax_3:1.b & 0x41) == 0)
00446ff0        actor->progress = 0f
00446ff3        actor->state = 1
00447000        play_sound_effect(0x32)
00447032        return
