/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: reset_vapour @ 0x442540 */

00442544        trail->point_count = 0
0044254e        int32_t arg_4
0044254e        trail->z_floor = arg_4
00442554        int32_t flags = trail->flags
00442557        flags.b &= 0xdf
00442559        trail->flags = flags
0044255c        return flags
