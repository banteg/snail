// Run score/stat pointer view, reached through the subgame score block at
// game+0x3bb764. This is separate from Player's score producer fields even
// though the bucket offsets match within each object. Do not embed this full
// view as a Game member when subsequent Game fields overlap its inner fields.
#ifndef SCORE_STATS_H
#define SCORE_STATS_H

enum {
    SUBGOLDY_SCORE_GARBAGE = 0,
    SUBGOLDY_SCORE_SLUG = 1,
    SUBGOLDY_SCORE_RING = 2,
    SUBGOLDY_SCORE_PARCEL_COLLECT = 3,
    SUBGOLDY_SCORE_PARCEL_DELIVER = 4,
    SUBGOLDY_SCORE_BONUS = 5,
    SUBGOLDY_SCORE_BUCKET_COUNT = 6,
};

class RunScoreStats {
public:
    int clear_subgoldy_score_buckets(); // @ 0x4403a0
    int display_score_stats();          // @ 0x4403c0

    char unknown_000[0x2e4];
    int total_score;                    // +0x2e4
    char unknown_2e8[0x310 - 0x2e8];
    int score_buckets[SUBGOLDY_SCORE_BUCKET_COUNT]; // +0x310
};

#endif
