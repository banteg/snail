// mini_delete_high_score_entry @ 0x417af0 (thiscall, ret 0x4)

#include "high_score_bank.h"

void HighScoreBank::mini_delete_high_score_entry(int rank)
{
    if (rank < HIGH_SCORE_TOP_TEN_COUNT) {
        int row = rank;
        int offset = row * SUB_SOLUTION_STRIDE;
        char* source_cursor = (char*)mini_delete_source_records + offset;
        do {
            SubSolution* destination =
                (SubSolution*)((char*)active_record_bank + offset);
            source_cursor += SUB_SOLUTION_STRIDE;
            SubSolution* source =
                (SubSolution*)(source_cursor - SUB_SOLUTION_STRIDE);
            offset += SUB_SOLUTION_STRIDE;
            *destination = *source;
            ((SubSolution*)((char*)active_record_bank + offset
                - SUB_SOLUTION_STRIDE))
                ->route_or_rank_index = row;
            ++row;
        } while (offset < SUB_SOLUTION_STRIDE * HIGH_SCORE_TOP_TEN_COUNT);
    }
}
