// add_arcade_high_score @ 0x4176a0 (thiscall, ret 0x8)

#include "high_score_bank.h"
#include "high_score_screen.h"

extern char* g_game_base; // data_4df904

int HighScoreBank::add_arcade_high_score(HighScoreRecord* record, int level_arg)
{
    HighScoreBank* bank = this;
    int rank = 0;

    record->route_or_rank_index = level_arg;
    record->high_score_mode_tag = 0;
    bank->current_result_record = *record;

    int score = record->score;
    int* score_cursor = &bank->postal_records[0].score;
    for (;;) {
        if (score > *score_cursor)
            break;
        ++rank;
        score_cursor += HIGH_SCORE_RECORD_STRIDE / sizeof(int);
        if (rank >= HIGH_SCORE_TOP_TEN_COUNT)
            return rank;
    }

    int shift_rank = HIGH_SCORE_TOP_TEN_COUNT;
    while (shift_rank > rank) {
        bank->postal_records[shift_rank] = bank->postal_records[shift_rank - 1];
        bank->postal_records[shift_rank].route_or_rank_index = shift_rank;
        --shift_rank;
    }

    bank->postal_records[rank] = *record;
    bank->postal_records[rank].route_or_rank_index = rank;

    ((HighScoreGameView*)g_game_base)->frontend_next_state = 20;
    ((HighScoreGameView*)g_game_base)->high_score_entry_pending = 1;
    ((HighScoreGameView*)g_game_base)->high_score_entry_rank = rank;
    ((HighScoreGameView*)g_game_base)->high_score_entry_bank = 0;
    return (int)(HighScoreGameView*)g_game_base;
}
