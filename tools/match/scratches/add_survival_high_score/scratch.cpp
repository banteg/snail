// add_survival_high_score @ 0x417780 (thiscall, ret 0x4)

#include "game_root.h"
#include "sub_high_score.h"


void SubHighScore::add_survival_high_score(SubSolution* record)
{
    int shift_rank;
    SubHighScore* bank = this;
    int rank = 0;

    record->high_score_mode_tag = 1;
    record->route_or_rank_index = 0;
    record->replay_cursor = 0;
    bank->current_result_record = *record;
    bank->survival_pending_record = *record;

    int score = record->score;
    int* score_cursor = &bank->survival_records[0].score;
    while (rank < SUB_HIGH_SCORE_TOP_TEN_COUNT) {
        if (score > *score_cursor)
            goto insert_record;
        ++rank;
        score_cursor += SUB_SOLUTION_STRIDE / sizeof(int);
    }
    return;

insert_record:
    shift_rank = SUB_HIGH_SCORE_TOP_TEN_COUNT;
    if (rank >= shift_rank)
        return;

    SubSolution* shift_cursor = &bank->survival_records[shift_rank];
    do {
        SubSolution* destination = shift_cursor;
        SubSolution* source = --shift_cursor;
        *destination = *source;
        destination->route_or_rank_index = shift_rank;
        --shift_rank;
    } while (shift_rank > rank);

    bank->survival_records[rank] = *record;
    bank->survival_records[rank].high_score_mode_tag = 1;
    bank->survival_records[rank].route_or_rank_index = rank;

    g_game->players[0].frontend_state = 20;
    g_game->players[0].high_score_entry_pending = 1;

    if (rank != -1) {
        record->high_score_mode_tag = 1;
        bank->survival_records[rank].high_score_mode_tag = 1;
        ((GameRoot*)g_game)->subgame.sub_high_score.active_record_bank =
            bank->survival_records;
        g_game->players[0].high_score_entry_rank = rank;
        GameRoot* game = g_game;
        game->players[0].high_score_entry_bank = 1;
    }
}
