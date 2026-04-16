/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_help_screen @ 0x4168d0 */

004168d0        void* edx = *arg1
004168d2        void* result = *(edx + 0x1a0)
004168da        if ((result.b & 0x20) != 0)
004168dc        result.b &= 0xdf
004168de        *(edx + 0x1a0) = result
004168e4        destroy_help_screen()
004168e9        result = data_4df904
004168ee        *(result + 0x1b8) = 2
004168fe        *(data_4df904 + 0x30c) = 1
00416905        return result
