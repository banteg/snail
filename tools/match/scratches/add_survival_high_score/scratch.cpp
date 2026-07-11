// add_survival_high_score @ 0x417780 (thiscall, ret 0x4)

#include "game_root.h"
#include "high_score_bank.h"

extern GameRoot* g_game; // data_4df904

int HighScoreBank::add_survival_high_score(SubSolution* record)
{
    int rank = 0;

    record->high_score_mode_tag = 1;
    record->route_or_rank_index = 0;
    record->replay_cursor = 0;
    current_result_record = *record;
    survival_pending_record = *record;

    int score = record->score;
    int* score_cursor = &survival_records[0].score;
    while (rank < HIGH_SCORE_TOP_TEN_COUNT) {
        if (score > *score_cursor)
            goto insert_record;
        ++rank;
        score_cursor += SUB_SOLUTION_STRIDE / sizeof(int);
    }
    return rank;

insert_record:
    int shift_rank = HIGH_SCORE_TOP_TEN_COUNT;
    if (rank >= shift_rank)
        return rank;

    do {
        survival_records[shift_rank] = survival_records[shift_rank - 1];
        survival_records[shift_rank].route_or_rank_index = shift_rank;
        --shift_rank;
    } while (shift_rank > rank);

    survival_records[rank] = *record;
    survival_records[rank].high_score_mode_tag = 1;
    survival_records[rank].route_or_rank_index = rank;

    g_game->players[0].frontend_state = 20;
    g_game->players[0].high_score_entry_pending = 1;

    int result = rank;
    if (rank != -1) {
        record->high_score_mode_tag = 1;
        survival_records[rank].high_score_mode_tag = 1;
        ((GameRoot*)g_game)->subgame.high_score_bank.active_record_bank =
            survival_records;
        g_game->players[0].high_score_entry_rank = rank;
        GameRoot* game = g_game;
        game->players[0].high_score_entry_bank = 1;
        result = (int)game;
    }

    return result;
}
