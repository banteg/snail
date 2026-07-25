/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: read_current_display_resolution @ 0x4078b0 */

004078c7        DEVMODEA devMode
004078c7        if (EnumDisplaySettingsA(nullptr, ENUM_CURRENT_SETTINGS, &devMode) == 0)
004078f8        *out_width = 0x280
004078fe        *out_height = 0x1e0
0040790a        return out_height
004078db        *out_width = devMode.dmPelsWidth
004078e1        *out_height = devMode.dmPelsHeight
004078e9        return out_height
