/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_click_start @ 0x442170 */

004421a4        *(arg1 + 0x84) = allocate_border(data_4df904 + 0xb4c)
004421aa        struct Color4f color
004421aa        struct Color4f* color_1 = set_color_rgba(&color, 1f, 1f, 1f, 0.0299999993f)
004421c8        initialize_frontend_widget(*(arg1 + 0x84), &__dos_header.e_cblp, "Click to Start", 0x14, 0f, 200f, color_1, 2, 0f)
004421d3        hide_border_init(*(arg1 + 0x84))
004421d8        int32_t eax_1 = *(arg1 + 4)
004421e4        *(arg1 + 0xa8) = 1
004421ed        *(arg1 + 0x98) = arg2
004421f3        void* ecx_5
004421f3        if ((0x200 & eax_1) == 0)
00442209        void** eax_3 = data_4df904 + 0x5ac
0044220e        void* ecx_6 = *eax_3
00442212        if (ecx_6 != 0)
00442220        *(ecx_6 + 8) = arg1
00442223        void* ecx_7 = *eax_3
00442229        *(*(ecx_7 + 8) + 0xc) = ecx_7
0044222f        ecx_5 = *(*eax_3 + 8)
00442232        *eax_3 = ecx_5
00442234        *(ecx_5 + 8) = 0
00442214        *eax_3 = arg1
00442216        *(arg1 + 8) = 0
0044221b        *(*eax_3 + 0xc) = 0
00442237        *(arg1 + 4) |= 0x200
004421fa        report_errorf("List ADD")
0044223a        void* edx = *(arg1 + 0x98)
00442240        *(arg1 + 0x80) = 2
0044224a        *(edx + 0x304) = 0
00442250        *(arg1 + 0x1c) = 0
00442253        *(arg1 + 0x20) = 0
0044225b        ecx_5.b = *(data_4df904 + 0x1066be8)
00442263        void* ecx_9 = *(arg1 + 0x84)
00442269        if (ecx_5.b == 0)
00442282        return unhide_border_init(ecx_9)
00442275        return hide_border_init(ecx_9)
