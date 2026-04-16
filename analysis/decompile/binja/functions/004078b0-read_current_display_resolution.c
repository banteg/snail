/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: read_current_display_resolution @ 0x4078b0 */

004078c7        DEVMODEA devMode
004078c7        if (EnumDisplaySettingsA(nullptr, ENUM_CURRENT_SETTINGS, &devMode) != 0)
004078db        *arg1 = devMode.dmPelsWidth
004078e1        *arg2 = devMode.dmPelsHeight
004078e9        return arg2
004078f1        int32_t* eax_2 = arg2
004078f8        *arg1 = 0x280
004078fe        *eax_2 = 0x1e0
0040790a        return eax_2
