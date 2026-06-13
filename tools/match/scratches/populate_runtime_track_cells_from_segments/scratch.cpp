// populate_runtime_track_cells_from_segments @ 0x435eb0 (thiscall, ret)
// Structure-first scratch for the runtime grid builder setup and clear pass.

struct Color4f {
    void set_color_white();
};

struct HighScoreEntry {
    void initialize_high_score_entry(
        int runtime_build_seed,
        int level_mode_arg,
        int level_record_word,
        unsigned int runtime_flags,
        int archive_kind,
        int replay_level_arg);
};

struct ScoreStats {
    void clear_subgoldy_score_buckets();
};

struct TimerCounters {
    int zero_timer_counters();
};

struct TextureSetSelector {
    int select_level_track_texture_set(int texture_set);
};

struct SelectedLevelRecord {
    char unknown_00[0x68];
    int runtime_build_seed;
};

extern char* g_game_base; // data_4df904

double random_float_below(float upper_bound, const char* tag);
void set_math_random_seed(int seed);
int report_errorf(const char* format, ...);

class Game {
public:
    void populate_runtime_track_cells_from_segments();
    bool switch_track_mirror();

    char unknown_00[0x34];
    float challenge_difficulty_scalar; // +0x34
    float subgame_rate; // +0x38
    int subgame_state; // +0x3c
    int level_mode; // +0x40
    int level_mode_arg; // +0x44
    float base_subgame_rate; // +0x48
    unsigned int runtime_flags; // +0x4c
    int first_block_row_count; // +0x50
    int runtime_row_count; // +0x54
    int completion_row_start; // +0x58
    char unknown_5c[0xa874 - 0x5c];
    int level_segment_count; // +0xa874
};

void Game::populate_runtime_track_cells_from_segments()
{
    char* base = (char*)this;
    int runtime_build_seed;

    if (*(unsigned char*)(base + 0xff25d0) != 0) {
        SelectedLevelRecord* record = *(SelectedLevelRecord**)(base + 0xff25d4);
        runtime_build_seed = record->runtime_build_seed;
    } else {
        int mode = level_mode;
        if (mode == 4 || mode == 7) {
            runtime_build_seed = 0;
        } else {
            runtime_build_seed = (int)random_float_below(32768.0f, "Seed");
        }
    }

    int archive_kind;
    int mode = level_mode;
    if (mode == 0) {
        archive_kind = 0;
    } else if (mode == 1) {
        archive_kind = 1;
    } else if (mode == 4) {
        archive_kind = 2;
    } else {
        archive_kind = -1;
    }
    if (archive_kind != -1) {
        ((HighScoreEntry*)(base + 0xfd2b10))->initialize_high_score_entry(
            runtime_build_seed,
            level_mode_arg,
            *(int*)(base + 0x30),
            runtime_flags,
            archive_kind,
            level_mode_arg);
    }

    *(int*)(base + 0xff25dc) = 0;
    if (*(int*)(base + 0x1270fc8) == 3) {
        *(int*)(base + 0x1270fc8) = 1;
        *(int*)(base + 0x3bba48) = 0;
        ((ScoreStats*)(base + 0x3bb764))->clear_subgoldy_score_buckets();
        *(int*)(base + 0x3bfaa4) = 3;
    }

    ((TimerCounters*)(base + 0x3bba4c))->zero_timer_counters();
    *(int*)(base + 0x3bba64) = 0;
    *(int*)(base + 0x3bba6c) = 0;
    set_math_random_seed(runtime_build_seed);
    ((TextureSetSelector*)(g_game_base + 0xb24))->select_level_track_texture_set(
        *(int*)(base + 0x1b01e4));

    int segment_cursor = 0;
    mode = level_mode;
    if (mode == 0 || mode == 7 || mode == 4 || mode == 1) {
        first_block_row_count = *(int*)(base + 0x1a7cfc);
        int authored_length = *(int*)(base + 0x1b0138);
        runtime_row_count = authored_length;
        if (mode == 1) {
            runtime_row_count =
                (int)((challenge_difficulty_scalar * 0.64999998f + 0.34999999f)
                    * (float)authored_length);
        }
        if (*(unsigned char*)(base + 0x1b013c) == 0) {
            runtime_row_count = *(int*)(base + 0x1a7cfc) + *(int*)(base + 0x1abf1c);
            for (int i = 0; i < level_segment_count; ++i)
                runtime_row_count += *(int*)(base + 0xa87c + 0x4220 * i);
            segment_cursor = 0;
        }
        completion_row_start = runtime_row_count - *(int*)(base + 0x1abf1c);
        if (runtime_row_count >= 3100) {
            report_errorf(
                "Track (%s) too long, Maximum Length %i",
                base + 0x1b0150,
                3100);
        }
    } else if (mode == 3) {
        first_block_row_count = *(int*)(base + 0x1a7cfc);
        runtime_row_count = *(int*)(base + 0x1a7cfc) + *(int*)(base + 0x1abf1c);
        for (int i = 0; i < 16; ++i)
            runtime_row_count += *(int*)(base + 0xa87c);
        segment_cursor = 0;
        completion_row_start = runtime_row_count - *(int*)(base + 0x1abf1c);
        completion_row_start = runtime_row_count - *(int*)(base + 0x1abf1c);
    }

    base[2] = 0;
    *(int*)(base + 4) = 0;
    int trampoline_counter = 0;
    char first_or_last_row = 0;
    int row_event_owner = 0;
    *(unsigned char*)(base + 0x3bbb24) = 0;

    char* cell_payload_cursor = base + 0x3bfb0c;
    int* row_cursor = (int*)(base + 0x5ccb5c);
    for (int row = 0; row < 3200; ++row) {
        row_cursor[-37] = 0;
        row_cursor[6] = 0;
        row_cursor[3] = 0;
        row_cursor[21] = 0;
        row_cursor[4] = 0;
        row_cursor[1] = 0;
        row_cursor[0] = 0;
        row_cursor[-1] = 0;
        row_cursor[2] = 0;
        row_cursor[22] = 0;
        row_cursor[23] = 0;

        char* cell_flags = cell_payload_cursor - 4;
        for (int lane = 0; lane < 8; ++lane) {
            int flags = *(int*)cell_flags;
            ((unsigned char*)&flags)[1] &= 0x5f;
            *(int*)cell_flags = flags;
            *(cell_flags - 3) = 0;
            *(short*)cell_flags = 0;
            *(int*)cell_flags &= 0xffffafa7;
            *(short*)cell_flags = 0;
            *(int*)(cell_flags - 60) &= 0xffffff7f;
            ((Color4f*)(cell_flags - 24))->set_color_white();
            cell_flags += 84;
        }

        char* cell_payload = cell_payload_cursor;
        for (int lane_payload = 0; lane_payload < 8; ++lane_payload) {
            *(int*)cell_payload = 0;
            *(int*)(cell_payload + 4) = 0;
            *(int*)(cell_payload + 8) = 0;
            *(int*)(cell_payload + 12) = 0;
            cell_payload += 84;
        }
        cell_payload_cursor = cell_payload;
        row_cursor += 61;
    }

    if (*(unsigned char*)(base + 0x1b013c) == 1) {
        for (int i = 0; i < level_segment_count; ++i)
            *(unsigned char*)(base + 0xa880 + 0x4220 * i) = 0;
    }

    (void)segment_cursor;
    (void)trampoline_counter;
    (void)first_or_last_row;
    (void)row_event_owner;
}
