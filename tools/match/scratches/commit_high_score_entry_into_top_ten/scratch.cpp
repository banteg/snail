// commit_high_score_entry_into_top_ten @ 0x417af0 (thiscall, ret 0x4)

#include "high_score_screen.h"

void HighScoreRecordView::commit_high_score_entry_into_top_ten(int rank)
{
    if (rank < HIGH_SCORE_TOP_TEN_COUNT) {
        int row = rank;
        do {
            active_record_bank[row] = name_submit_records[row];
            active_record_bank[row].route_or_rank_index = row;
            ++row;
        } while (row < HIGH_SCORE_TOP_TEN_COUNT);
    }
}
