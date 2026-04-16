/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: stack_widget_below @ 0x4027b0 */

004027ba        arg1->__offset(0x6f4).d = *(arg2 + 0x6f4)
004027d2        arg1->__offset(0x6f8).d = fconvert.s(fconvert.t(*(arg2 + 0x6f8)) + fconvert.t(arg1->__offset(0x26c).d) + fconvert.t(*(arg2 + 0x24c)))
004027dd        return layout_frontend_widget(arg1)
