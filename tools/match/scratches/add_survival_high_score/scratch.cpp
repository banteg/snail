// add_survival_high_score @ 0x417780 (thiscall, ret 0x4)

#include "high_score_bank.h"
#include "high_score_screen.h"

extern char* g_game_base; // data_4df904

int HighScoreBank::add_survival_high_score(HighScoreRecord* record)
{
    HighScoreBank* bank = this;
    int rank = 0;

    record->high_score_mode_tag = 1;
    record->route_or_rank_index = 0;
    record->replay_cursor = 0;
    bank->current_result_record = *record;
    bank->survival_pending_record = *record;

    int score = record->score;
    HighScoreRecord* cursor = bank->survival_records;
    for (;;) {
        if (score > cursor->score)
            break;
        ++rank;
        ++cursor;
        if (rank >= HIGH_SCORE_TOP_TEN_COUNT)
            return rank;
    }

    int shift_rank = HIGH_SCORE_TOP_TEN_COUNT;
    do {
        bank->survival_records[shift_rank] = bank->survival_records[shift_rank - 1];
        bank->survival_records[shift_rank].route_or_rank_index = shift_rank;
        --shift_rank;
    } while (shift_rank > rank);

    bank->survival_records[rank] = *record;
    bank->survival_records[rank].high_score_mode_tag = 1;
    bank->survival_records[rank].route_or_rank_index = rank;

    ((HighScoreGameView*)g_game_base)->frontend_next_state = 20;
    ((HighScoreGameView*)g_game_base)->high_score_entry_pending = 1;

    if (rank != -1) {
        record->high_score_mode_tag = 1;
        bank->survival_records[rank].high_score_mode_tag = 1;
        ((HighScoreGameView*)g_game_base)->high_score_records.active_record_bank =
            bank->survival_records;
        ((HighScoreGameView*)g_game_base)->high_score_entry_rank = rank;
        ((HighScoreGameView*)g_game_base)->high_score_entry_bank = 1;
    }

    return (int)(HighScoreGameView*)g_game_base;
}
