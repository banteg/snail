/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: add_subgoldy_score @ 0x4402c0 */

004402cb        int32_t points
004402cb        if (score_kind u> SUBGOLDY_SCORE_BONUS)
004402f4        report_errorf("Unknown Score Type")
004402fc        points = 0
004402cb        switch (score_kind)
004402d4        case SUBGOLDY_SCORE_GARBAGE
004402d4        points = 0xa
004402db        case SUBGOLDY_SCORE_SLUG
004402db        points = 0x1f4
004402e2        case SUBGOLDY_SCORE_RING, SUBGOLDY_SCORE_PARCEL_COLLECT, SUBGOLDY_SCORE_PARCEL_DELIVER
004402e2        points = 0x64
004402e9        case SUBGOLDY_SCORE_BONUS
004402e9        points = bonus_score
00440307        player->score_buckets[score_kind] += points
0044030e        int32_t old_total = player->total_score
00440314        int32_t new_total = old_total + points
0044031e        player->total_score = new_total
00440335        int32_t eax_4
00440335        int32_t edx_1
00440335        edx_1:eax_4 = muls.dp.d(0x14f8b589, old_total)
0044033c        uint32_t result = edx_1 s>> 0xc u>> 0x1f
00440343        if (old_total s/ 0xc350 != new_total s/ 0xc350)
00440345        result = player->visible_life_stock
0044034e        if (result s< 9)
00440351        player->visible_life_stock = result + 1
00440357        result = data_4df904
0044036b        if (*(result + 0x74658) == 0 && *(result + 0x24) == 0)
00440374        return play_sound_effect(0x2c)
0044037b        return result
