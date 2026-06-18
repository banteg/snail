// clear_subgoldy_score_buckets @ 0x4403a0 (thiscall, ret)

#include "score_stats.h"

int RunScoreStats::clear_subgoldy_score_buckets()
{
    for (int i = 0; i < SUBGOLDY_SCORE_BUCKET_COUNT; ++i) {
        score_buckets[i] = 0;
    }
    return 0;
}
