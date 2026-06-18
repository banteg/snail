// commit_high_score_entry_into_top_ten @ 0x417af0 (thiscall, ret 0x4)

#include "high_score_screen.h"

void HighScoreRecordView::commit_high_score_entry_into_top_ten(int rank)
{
    if (rank < HIGH_SCORE_TOP_TEN_COUNT) {
        int row = rank;
        int offset = row * HIGH_SCORE_RECORD_STRIDE;
        char* source_cursor = (char*)name_submit_records + offset;
        do {
            HighScoreRecord* destination =
                (HighScoreRecord*)((char*)active_record_bank + offset);
            HighScoreRecord* source = (HighScoreRecord*)source_cursor;
            offset += HIGH_SCORE_RECORD_STRIDE;
            source_cursor += HIGH_SCORE_RECORD_STRIDE;
            *destination = *source;
            ((HighScoreRecord*)((char*)active_record_bank + offset
                - HIGH_SCORE_RECORD_STRIDE))
                ->route_or_rank_index = row;
            ++row;
        } while (offset < HIGH_SCORE_RECORD_STRIDE * HIGH_SCORE_TOP_TEN_COUNT);
    }
}
