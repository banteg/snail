/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: probe_display_mode_count @ 0x407880 */

0040788e        enum ENUM_DISPLAY_SETTINGS_MODE iModeNum = 0
0040789d        BOOL i
00407898        DEVMODEA devMode
00407898        i = EnumDisplaySettingsA(nullptr, iModeNum, &devMode)
0040789a        iModeNum += 1
0040789d        do while (i != 0)
004078a7        return i
