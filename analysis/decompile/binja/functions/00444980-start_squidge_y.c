/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: start_squidge_y @ 0x444980 */

0044498a        squidge->y_phase = 0f
00444991        squidge->y_velocity = fconvert.s(fconvert.t(value) * fconvert.t(0.5f))
00444994        return
