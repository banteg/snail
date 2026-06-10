/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_tip @ 0x448c40 */

00448c46        struct TipSlot* slot_1 = slot
00448c48        slot.b = *(data_4df904 + 0x74621)
00448c50        void* widget_main = slot_1->widget_main
00448c53        if (slot.b != 0)
00448c5b        return hide_border_init(widget_main)
00448c5c        void* eax_1 = unhide_border_init(widget_main)
00448c61        void* ecx = slot_1->widget_ok
00448c66        if (ecx != 0)
00448c68        eax_1 = *(ecx + 0x1a0)
00448c70        if (ecx == 0 || (eax_1.b & 0x20) == 0)
00448c72        ecx = slot_1->widget_disable
00448c77        if (ecx != 0)
00448c79        eax_1 = *(ecx + 0x1a0)
00448c81        if (ecx == 0 || (eax_1.b & 0x20) == 0)
00448cbf        if ((slot_1->definition->flags.b & 2) != 0)
00448cc4        long double x87_r7_2 = fconvert.t(slot_1->dismiss_step) + fconvert.t(slot_1->dismiss_progress)
00448cc7        slot_1->dismiss_progress = fconvert.s(x87_r7_2)
00448cca        long double temp0_1 = fconvert.t(1f)
00448cca        x87_r7_2 - temp0_1
00448cd0        eax_1.w = (x87_r7_2 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp0_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp0_1 ? 1 : 0) << 0xe
00448cd5        if ((eax_1:1.b & 0x41) == 0)
00448cd9        eax_1 = kill_tip_widgets(slot_1)
00448cde        slot_1->active = 0
00448ce5        return eax_1
00448c83        eax_1.b &= 0xdf
00448c85        *(ecx + 0x1a0) = eax_1
00448c94        *(data_4df904 + 0x1b8) = slot_1->previous_outer_owner
00448c9c        kill_tip_widgets(slot_1)
00448cac        int32_t eax_3 = unhide_all_borders(data_4df904 + 0xb4c)
00448cb1        slot_1->active = 0
00448cb8        return eax_3
