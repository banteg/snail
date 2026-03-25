/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_tip @ 0x448c40 */

00448c46        int32_t* esi = arg1
00448c48        arg1.b = *(data_4df904 + 0x74621)
00448c50        void* ecx = esi[3]
00448c53        if (arg1.b != 0)
00448c5b        return hide_border_init(ecx)
00448c5c        void* eax_1 = unhide_border_init(ecx)
00448c61        void* ecx_1 = esi[4]
00448c66        if (ecx_1 != 0)
00448c68        eax_1 = *(ecx_1 + 0x1a0)
00448c70        if (ecx_1 == 0 || (eax_1.b & 0x20) == 0)
00448c72        ecx_1 = esi[5]
00448c77        if (ecx_1 != 0)
00448c79        eax_1 = *(ecx_1 + 0x1a0)
00448c81        if (ecx_1 == 0 || (eax_1.b & 0x20) == 0)
00448cbf        if ((*esi[2] & 2) != 0)
00448cc4        long double x87_r7_2 = fconvert.t(esi[7]) + fconvert.t(esi[6])
00448cc7        esi[6] = fconvert.s(x87_r7_2)
00448cca        long double temp0_1 = fconvert.t(1f)
00448cca        x87_r7_2 - temp0_1
00448cd0        eax_1.w = (x87_r7_2 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp0_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp0_1 ? 1 : 0) << 0xe
00448cd5        if ((eax_1:1.b & 0x41) == 0)
00448cd9        eax_1 = kill_tip_widgets(esi)
00448cde        *esi = 0
00448ce5        return eax_1
00448c83        eax_1.b &= 0xdf
00448c85        *(ecx_1 + 0x1a0) = eax_1
00448c94        *(data_4df904 + 0x1b8) = esi[1]
00448c9c        kill_tip_widgets(esi)
00448cac        int32_t eax_3 = unhide_all_borders(data_4df904 + 0xb4c)
00448cb1        *esi = 0
00448cb8        return eax_3
