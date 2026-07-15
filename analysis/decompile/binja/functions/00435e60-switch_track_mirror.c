/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: switch_track_mirror @ 0x435e60 */

00435e61        char* var_8 = "Mirror"
00435e6d        long double st0 = random_float_below(1f)
00435e72        long double temp0 = fconvert.t(0.5f)
00435e72        st0 - temp0
00435e7d        int16_t eax_1 = (st0 < temp0 ? 1 : 0) << 8 | (is_unordered.t(st0, temp0) ? 1 : 0) << 0xa | (st0 == temp0 ? 1 : 0) << 0xe
00435e82        if ((eax_1:1.b & 0x41) != 0)
00435e88        eax_1.b = 0
00435e84        eax_1.b = 1
00435e8d        if (eax_1.b != runtime->track_mirror_enabled)
00435e94        runtime->track_mirror_repeat_count = 0
00435e8f        runtime->track_mirror_repeat_count += 1
00435e9b        if (runtime->track_mirror_repeat_count s< 4)
00435e9d        runtime->track_mirror_enabled = eax_1.b
00435ea1        return eax_1.b
00435ea4        runtime->track_mirror_repeat_count = 0
00435ea7        eax_1.b = eax_1.b == 0
00435eaa        runtime->track_mirror_enabled = eax_1.b
00435eae        return eax_1.b
