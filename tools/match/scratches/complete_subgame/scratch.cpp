// complete_subgame @ 0x438700 (thiscall, ret 0x4)
// cRSubGame::Complete(bool): snapshot the finished run and route high-score writes.

#include "score_stats.h"

struct RunRecord {
    unsigned char flags;
    char pad[5];
};

struct SixDwords {
    int values[6];
};

struct ResultRecord {
    int active;              // +0x00
    int score;               // +0x04
    SixDwords stats;         // +0x08
    int score_tail;          // +0x20
    int source_tail;         // +0x24
    int unknown_28;          // +0x28
    int level_mode;          // +0x2c
    int unknown_30;          // +0x30
    int difficulty_tail;     // +0x34
    char unknown_38[0x48 - 0x38];
    int level_arg_tail;      // +0x48
    int source_arg_tail;     // +0x4c
    int level_index_tail;    // +0x50
};

struct HighScoreBank {
    void add_arcade_high_score(ResultRecord* record, int level_arg); // @ 0x4176a0
    void add_survival_high_score(ResultRecord* record);              // @ 0x417780
    void add_time_trial_high_score(ResultRecord* record, int level_arg, unsigned char route_active); // @ 0x4178b0
};

extern unsigned char g_completion_snapshot_flags; // byte_4b2f40

class Game {
public:
    void complete_subgame(unsigned char completed);

    char unknown_000000[0x28];
    int source_arg_tail; // +0x28
    int level_index_tail; // +0x2c
    int level_arg_tail; // +0x30
    int difficulty_tail; // +0x34
    char unknown_000038[0x40 - 0x38];
    int level_mode; // +0x40
    int level_arg; // +0x44
    char unknown_000048[0x3bb764 - 0x48];
    char score_stats_block[0x2e4]; // +0x3bb764, RunScoreStats pointer view
    int source_score; // +0x3bba48
    SixDwords source_stats; // +0x3bba4c
    int source_score_tail; // +0x3bba64
    int source_tail; // +0x3bba68
    char unknown_3bba6c[0x3bbba4 - 0x3bba6c];
    unsigned char time_trial_route_active; // +0x3bbba4
    char unknown_3bbba5[0x68b4c8 - 0x3bbba5];
    HighScoreBank high_score_bank; // +0x68b4c8
    char unknown_68b4c9[0xfd2b10 - 0x68b4c9];
    ResultRecord result_record; // +0xfd2b10
    char unknown_fd2b64[0xfd2b7c - 0xfd2b64];
    int completion_count; // +0xfd2b7c
    char unknown_fd2b80[0xfd2b84 - 0xfd2b80];
    RunRecord run_records[0x1fa3c / 6]; // +0xfd2b84, 6-byte stride
    int timer_snapshot_a; // +0xff25c0
    int timer_snapshot_b; // +0xff25c4
    char unknown_ff25c8[0xff25d0 - 0xff25c8];
    unsigned char selected_level_record_active; // +0xff25d0
    char unknown_ff25d1[0xff25dc - 0xff25d1];
    int replay_update_cursor; // +0xff25dc
    char unknown_ff25e0[0x125ffd8 - 0xff25e0];
    int source_timer_a; // +0x125ffd8
    int source_timer_b; // +0x125ffdc
};

void Game::complete_subgame(unsigned char completed)
{
    ((RunScoreStats*)score_stats_block)->display_score_stats();

    run_records[replay_update_cursor].flags |= 0x08;
    ++completion_count;
    ++replay_update_cursor;

    if ((g_completion_snapshot_flags & 1) == 0) {
        ResultRecord* record = &result_record;

        result_record.score = source_score;
        result_record.stats = source_stats;
        result_record.difficulty_tail = difficulty_tail;
        result_record.source_arg_tail = source_arg_tail;
        result_record.score_tail = source_score_tail;
        result_record.level_index_tail = level_index_tail;
        result_record.level_arg_tail = level_arg_tail;
        timer_snapshot_a = source_timer_a;
        timer_snapshot_b = source_timer_b;
        result_record.active = 1;
        result_record.source_tail = source_tail;
        result_record.level_mode = level_mode;

        if ((level_mode != 1 || source_tail != 0)
            && !selected_level_record_active
            && completed == 1) {
            switch (level_mode) {
            case 0:
                high_score_bank.add_arcade_high_score(record, level_arg);
                break;
            case 1:
                high_score_bank.add_survival_high_score(record);
                break;
            case 4:
                high_score_bank.add_time_trial_high_score(
                    record,
                    level_arg,
                    time_trial_route_active);
                break;
            }
        }
    }
}
