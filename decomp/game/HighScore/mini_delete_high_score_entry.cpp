// mini_delete_high_score_entry @ 0x417af0 (thiscall, ret 0x4)

#include "sub_high_score.h"

void cRSubHighScore::MiniDelete(int rank)
{
    for (int row = rank; row < SUB_HIGH_SCORE_TOP_TEN_COUNT; ++row) {
        active_record_bank[row] = survival_records[row + 1];
        active_record_bank[row].route_or_rank_index = row;
    }
}
