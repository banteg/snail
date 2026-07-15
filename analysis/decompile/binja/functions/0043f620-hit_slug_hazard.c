/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: hit_slug_hazard @ 0x43f620 */

0043f627        int32_t hit_points = slug->hit_points
0043f62f        slug->hit_points = hit_points - damage
0043f635        if (hit_points - damage s>= 0)
0043f64c        slug->hit_flash_pending = 1
0043f675        int16_t x87control
0043f675        play_slug_voice(slug, 0x24 - ftol(x87control, float.t(next_math_random_value()) * fconvert.t(-9.15527344e-05f)))
0043f67b        return
0043f639        slug->hit_points = 0
0043f643        kill_slug_hazard(slug)
0043f649        return
