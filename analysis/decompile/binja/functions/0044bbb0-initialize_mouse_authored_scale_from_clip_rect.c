/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_mouse_authored_scale_from_clip_rect @ 0x44bbb0 */

0044bbb5        GetClipCursor(&g_mouse_clip_rect)
0044bbcd        return update_mouse_authored_scale(640f, 480f)
