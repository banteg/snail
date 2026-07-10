// add_arcade_high_score @ 0x4176a0 (thiscall, ret 0x8)

#include "game_root.h"
#include "high_score_bank.h"
#include "high_score_screen.h"

extern GameRoot* g_game; // data_4df904

int HighScoreBank::add_arcade_high_score(HighScoreRecord* record, int level_arg)
{
    HighScoreBank* bank = this;
    int rank = 0;

    record->route_or_rank_index = level_arg;
    record->high_score_mode_tag = 0;
    bank->current_result_record = *record;

    int score = record->score;
    int* score_cursor = &bank->postal_records[0].score;
    while (rank < HIGH_SCORE_TOP_TEN_COUNT) {
        if (score > *score_cursor)
            goto insert_record;
        ++rank;
        score_cursor += HIGH_SCORE_RECORD_STRIDE / sizeof(int);
    }
    return rank;

insert_record:
    int shift_rank = HIGH_SCORE_TOP_TEN_COUNT;
    while (shift_rank > rank) {
        bank->postal_records[shift_rank] = bank->postal_records[shift_rank - 1];
        bank->postal_records[shift_rank].route_or_rank_index = shift_rank;
        --shift_rank;
    }

    bank->postal_records[rank] = *record;
    bank->postal_records[rank].route_or_rank_index = rank;

    g_game->players[0].frontend_state = 20;
    g_game->players[0].high_score_entry_pending = 1;
    g_game->players[0].high_score_entry_rank = rank;
    GameRoot* result_view = g_game;
    result_view->players[0].high_score_entry_bank = 0;
    return (int)result_view;
}
