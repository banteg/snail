/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: kill_slug_hazard @ 0x43f8b0 */

0043f8b0        struct Slug* slug_1 = slug
0043f8bb        if (slug->state != SUB_SLUG_STATE_ACTIVE)
0043f8bb        return
0043f8df        int16_t x87control
0043f8df        play_slug_voice(slug, 0x1c - ftol(x87control, float.t(next_math_random_value()) * fconvert.t(-6.10351562e-05f)))
0043f8e4        long double x87_r7_3 = fconvert.t(slug->body.transform.position.x)
0043f8e7        long double temp0_1 = fconvert.t(0f)
0043f8e7        x87_r7_3 - temp0_1
0043f8f2        slug->state = SUB_SLUG_STATE_DEATH_TOSS_PENDING
0043f8fd        if ((((x87_r7_3 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_3, temp0_1) ? 1 : 0) << 0xa | (x87_r7_3 == temp0_1 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
0043f90b        slug->death_toss_direction = SUB_SLUG_DEATH_TOSS_LEFT
0043f8ff        slug->death_toss_direction = SUB_SLUG_DEATH_TOSS_RIGHT
0043f921        add_subgoldy_score(&slug->owner_game->player, 1, 0)
0043f928        explode_slug_hazard(slug)
0043f92f        return
