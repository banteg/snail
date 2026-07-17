/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: reset_vapour @ 0x442540 */

00442544        vapour->point_count = 0
0044254e        vapour->z_floor = z_floor
00442554        uint32_t list_flags = vapour->body.bod.bod.list_flags
00442557        list_flags.b &= 0xdf
00442559        vapour->body.bod.bod.list_flags = list_flags
0044255c        return
