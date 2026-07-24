/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_frontend_overlay_color_lerp @ 0x40ab00 */

0040ab05        int32_t* overlay_1 = overlay
0040ab1b        *overlay_1 = state
0040ab1d        store_color4f(&overlay_1[1], 1f, 1f, 1f, 0f)
0040ab36        store_color4f(&overlay_1[5], 1f, 1f, 1f, 0f)
0040ab3c        return
