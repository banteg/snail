/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: click_mouse_screen @ 0x44c060 */

0044c076        if (data_4dfaf4 == 0 && is_mouse_captured(data_4df904 + 0x290) == 1 && arg1 == 0 && data_4b7654 == 0 && GetActiveWindow() == data_4dfaf0)
0044c0a9        SetCursorPos(arg2, arg3)
0044c0af        long double x87_r7 = float.t(arg2)
0044c0b3        void* ecx_2 = data_4df904
0044c0b9        *((arg1 << 2) + &data_777d7c) = arg2
0044c0c0        *((arg1 << 2) + &data_777d74) = arg3
0044c0c8        (&data_777d58)[arg1] = fconvert.s(x87_r7)
0044c0cf        long double x87_r6 = float.t(arg3)
0044c0d7        (&data_777d60)[arg1] = fconvert.s(x87_r6)
0044c0e6        *(*(ecx_2 + 0x28c) + 0x60) = fconvert.s(x87_r7)
0044c0e9        void* result = data_4df904
0044c0f8        *(*(result + 0x28c) + 0x64) = fconvert.s(x87_r6)
0044c0fb        return result
