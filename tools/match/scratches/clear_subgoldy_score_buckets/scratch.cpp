// clear_subgoldy_score_buckets @ 0x4403a0 (thiscall, ret)

#include "player.h"

int Player::clear_subgoldy_score_buckets()
{
    for (int i = 0; i < 6; ++i) {
        score_buckets[i] = 0;
    }
    return 0;
}
