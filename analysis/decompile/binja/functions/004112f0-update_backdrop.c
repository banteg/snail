/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_backdrop @ 0x4112f0 */

004112f6        int16_t eax
004112f6        eax.b = backdrop->backdrop_change_queued
004112fb        if (eax.b != 0)
004112fd        change_backdrop_real(backdrop)
00411302        backdrop->backdrop_change_queued = 0
00411309        struct BackdropDistortCell (* ebx)[0x8][0x8] = &backdrop->distort_grid
0041130c        int32_t var_4 = 8
0041137a        bool cond:1_1
00411314        struct BackdropDistortCell (* esi_1)[0x8][0x8] = ebx
00411316        int32_t i_1 = 8
0041136c        int32_t i
0041131e        long double x87_r7_2 = fconvert.t((esi_1 - 0x58)->distort_grid[0][0].phase_step) + fconvert.t((esi_1 - 0x58)->distort_grid[0][0].phase)
00411320        float var_8_1 = fconvert.s(x87_r7_2)
00411324        (esi_1 - 0x58)->distort_grid[0][0].phase = fconvert.s(x87_r7_2)
00411326        long double x87_r7_3 = fconvert.t(var_8_1)
0041132a        long double temp0_1 = fconvert.t(6.28318548f)
0041132a        x87_r7_3 - temp0_1
00411335        if ((((x87_r7_3 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_3, temp0_1) ? 1 : 0) << 0xa | (x87_r7_3 == temp0_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00411341        (esi_1 - 0x58)->distort_grid[0][0].phase = fconvert.s(fconvert.t(var_8_1) - fconvert.t(6.28318548f))
0041134e        (esi_1 - 0x58)->distort_grid[0][0].current_x_offset = fconvert.s(sine((esi_1 - 0x58)->distort_grid[0][0].phase) * fconvert.t((esi_1 - 0x58)->distort_grid[0][0].x_offset))
00411359        long double x87_r7_9 = cosine((esi_1 - 0x58)->distort_grid[0][0].phase) * fconvert.t((esi_1 - 0x58)->distort_grid[0][0].y_offset)
0041135f        esi_1 = &(*esi_1)[1]
00411365        i = i_1
00411365        i_1 -= 1
00411366        (esi_1 - 0x58)->__offset(0xffffffffffffffac).d = fconvert.s(x87_r7_9)
0041136c        do while (i != 1)
00411372        ebx = &(*ebx)[0][1]
00411375        cond:1_1 = var_4 != 1
00411376        var_4 -= 1
0041137a        do while (cond:1_1)
0041137c        int32_t active_primary_texture_id = backdrop->active_primary_texture_id
00411385        if (active_primary_texture_id != 0xffffffff)
00411387        int32_t backdrop_render_enabled = backdrop->backdrop_render_enabled
0041138d        active_primary_texture_id = backdrop_render_enabled - 1
0041138e        if (backdrop_render_enabled == 1)
00411397        if (backdrop->active_split_backdrop_pair == 0)
004113a3        return render_backdrop(backdrop)
004113a2        return draw_split_backdrop(backdrop)
004113ac        return active_primary_texture_id
