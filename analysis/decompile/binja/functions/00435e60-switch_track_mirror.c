/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: switch_track_mirror @ 0x435e60 */

00435e61        char* tag = "Mirror"
00435e6d        long double random_value = random_float_below(1f)
00435e72        long double threshold = fconvert.t(0.5f)
00435e72        random_value - threshold
00435e82        bool mirror_enabled
00435e82        if ((((random_value < threshold ? 1 : 0) << 8 | (is_unordered.t(random_value, threshold) ? 1 : 0) << 0xa | (random_value == threshold ? 1 : 0) << 0xe):1.b & 0x41) != 0)
00435e88        mirror_enabled = false
00435e84        mirror_enabled = true
00435e8d        if (mirror_enabled != game->track_mirror_enabled)
00435e94        game->track_mirror_repeat_count = 0
00435e8f        game->track_mirror_repeat_count += 1
00435e9b        if (game->track_mirror_repeat_count s< 4)
00435e9d        game->track_mirror_enabled = mirror_enabled
00435ea1        return mirror_enabled
00435ea4        game->track_mirror_repeat_count = 0
00435ea7        mirror_enabled = mirror_enabled == false
00435eaa        game->track_mirror_enabled = mirror_enabled
00435eae        return mirror_enabled
