// populate_runtime_track_cells_from_segments @ 0x435eb0 (thiscall, ret)
// Structure-first scratch for the runtime grid builder setup and clear pass.

#include "score_stats.h"
#include "sprite.h"
#include "timer_counters.h"

void __fastcall set_matrix_identity(void* transform);

class TrackRowBodSlot {
public:
    int set_bod_object(void* object);
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
int debug_report_stub(const char* format, ...);

class Game {
public:
    void populate_runtime_track_cells_from_segments();
    bool switch_track_mirror();
    char normalize_segment_glyph_for_track_flags(char glyph, int row, char edge_row);

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
        ((RunScoreStats*)(base + 0x3bb764))->clear_subgoldy_score_buckets();
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

    if (runtime_row_count <= 0)
        return;

    int segment_row = 0;
    char* active_segment = 0;
    for (int build_row = 0; build_row < runtime_row_count; ++build_row) {
        if (build_row == 0) {
            active_segment = base + 0x1a7cf8;
            first_or_last_row = 1;
            segment_row = 0;
            *(int*)active_segment = build_row;
        } else if (build_row == completion_row_start && *(unsigned char*)(base + 0x1b013c) == 0) {
            active_segment = base + 0x1abf18;
            first_or_last_row = 1;
            segment_row = 0;
            *(int*)active_segment = build_row;
        } else if (segment_row >= *(int*)(active_segment + 4)) {
            first_or_last_row = 0;
            if (*(unsigned char*)(base + 0x1b013c) == 1) {
                float segment_pick_range;
                if (level_mode == 1) {
                    segment_pick_range =
                        (challenge_difficulty_scalar * 0.89999998f + 0.100000001f)
                        * (float)level_segment_count;
                    int picked = (int)random_float_below(segment_pick_range, "Segdif");
                    picked = (int)((float)picked * base_subgame_rate);
                    active_segment = base + 0xa878 + 0x4220 * picked;
                } else {
                    segment_pick_range = (float)level_segment_count;
                    int picked = (int)random_float_below(segment_pick_range, "Segtra");
                    picked = (int)((float)picked * base_subgame_rate);
                    active_segment = base + 0xa878 + 0x4220 * picked;
                }
                *(unsigned char*)(active_segment + 8) = 1;
            } else {
                int picked = segment_cursor;
                ++segment_cursor;
                active_segment = base + 0xa878 + 0x4220 * picked;
                switch_track_mirror();
            }
            segment_row = 0;
            *(int*)active_segment = build_row;
            if (*(int*)(active_segment + 4) < 0)
                report_errorf("Negative Segment Length");
        }

        if (level_mode != 2 && build_row >= completion_row_start) {
            if (level_mode == 0 || level_mode == 4 || level_mode == 1 || level_mode == 7) {
                active_segment = base + 0x1abf18;
                if (build_row == completion_row_start)
                    segment_row = 0;
            } else if (level_mode == 3) {
                active_segment = base + 0x1b4410;
            }

            int segment_end = *(int*)(active_segment + 4) - segment_row + build_row;
            if (segment_end > completion_row_start
                && active_segment != base + 0x1b4410
                && active_segment != base + 0x1bc850
                && active_segment != base + 0x1c0a70
                && (level_mode == 0
                    || level_mode == 4
                    || level_mode == 1
                    || level_mode == 7
                    || (level_mode == 3 && active_segment != base + 0x1abf18))) {
                int extra_rows = *(int*)(active_segment + 4) - completion_row_start - segment_row + build_row;
                completion_row_start += extra_rows;
                runtime_row_count += extra_rows;
            }
        }

        char* row_record = base + 0xf4 * build_row + 0x5ccac8;
        if (base[2])
            *(int*)row_record |= 0x20;

        int authored_flags = *(int*)(active_segment + 0x814 + 0x38 * segment_row);
        if ((authored_flags & 0x100) != 0)
            *(int*)row_record |= 0x100;
        if ((authored_flags & 0x8000) != 0)
            *(int*)row_record |= 0x8000;

        *(char**)(row_record + 0xec) = active_segment;
        *(int*)(row_record + 0xf0) = row_event_owner;

        char* authored_row = active_segment + 0x814 + 0x38 * segment_row;
        if ((authored_flags & 0x2) != 0) {
            *(int*)row_record |= 0x2;
            int object_id = *(int*)(authored_row + 0x14);
            void* object = *(void**)(g_game_base + 0x48e2c + 0xbc * object_id);
            ((TrackRowBodSlot*)(row_record + 4))->set_bod_object(object);
            set_matrix_identity(row_record + 0x3c);
            *(int*)(row_record + 0x6c) = *(int*)(authored_row + 0x18);
            *(int*)(row_record + 0x70) = *(int*)(authored_row + 0x1c);
            *(int*)(row_record + 0x74) = *(int*)(authored_row + 0x20);
            *(float*)(row_record + 0x74) += (float)build_row;

            if ((authored_flags & 0x8) != 0) {
                *(int*)row_record |= 0x8;
                *(int*)(row_record + 0x84) = *(int*)(authored_row + 0x24);
                *(int*)(row_record + 0x88) = *(int*)(authored_row + 0x28);
                *(int*)(row_record + 0x8c) = *(int*)(authored_row + 0x2c);
            } else {
                *(int*)(row_record + 0x84) = 0;
                *(int*)(row_record + 0x88) = 0;
                *(int*)(row_record + 0x8c) = 0;
            }
        }

        if ((authored_flags & 0x1) != 0) {
            *(int*)row_record |= 0x4001;
            *(int*)(row_record + 0x9c) = *(int*)(authored_row + 4);
            *(int*)(row_record + 0x90) = *(int*)(authored_row + 8);
            *(int*)(row_record + 0x94) = *(int*)(authored_row + 12);
            *(int*)(row_record + 0x98) = *(int*)(authored_row + 16);
        }
        if ((authored_flags & 0x8) != 0) {
            *(int*)row_record |= 0x8;
            *(int*)(row_record + 0xa0) = *(int*)(authored_row + 0x30);
        }
        if ((authored_flags & 0x4) != 0)
            *(int*)row_record |= 0x4;
        if ((authored_flags & 0x200) != 0)
            *(int*)row_record |= 0x200;
        if ((authored_flags & 0x400) != 0)
            *(int*)row_record |= 0x400;
        if ((authored_flags & 0x2000) != 0)
            *(int*)row_record |= 0x2000;
        if ((authored_flags & 0x800) != 0)
            *(int*)row_record |= 0x800;
        if ((authored_flags & 0x1000) != 0)
            *(int*)row_record |= 0x1000;
        *(int*)(row_record + 0xe8) = *(int*)(authored_row + 0x34);

        first_or_last_row = 0;
        for (int lane = 0; lane < 8; ++lane) {
            int authored_lane;
            if (base[2])
                authored_lane = 7 - lane;
            else
                authored_lane = lane;

            char* cell = base + 0x54 * (lane + build_row * 8);
            int cell_word = *(int*)(cell + 0x3bfb08);
            ((unsigned char*)&cell_word)[0] &= 0xe0;
            cell_word ^= lane & 7;
            *(int*)(cell + 0x3bfb08) = cell_word;

            *(int*)(cell + 0x3bfb0c) = 0;
            *(int*)(cell + 0x3bfb10) = 0;
            *(int*)(cell + 0x3bfb14) = 0;
            *(int*)(cell + 0x3bfb18) = 0;

            char edge_row;
            if (build_row >= first_block_row_count) {
                edge_row = 0;
                if (build_row >= completion_row_start)
                    edge_row = 1;
            } else {
                edge_row = 1;
            }

            ((TrackRowBodSlot*)(cell + 0x3bfac8))->set_bod_object(0);

            char* glyph_ptr = active_segment + (authored_lane << 8) + lane + 0x14;
            char glyph = *glyph_ptr;
            char normalized =
                normalize_segment_glyph_for_track_flags(glyph, build_row, edge_row);
            switch (normalized) {
            case ' ':
                *(unsigned char*)(cell + 0x3bfb04) = 0;
                *(int*)(cell + 0x3bfacc) &= 0xffffffdf;
                break;
            case '#':
                *(unsigned char*)(cell + 0x3bfb04) = 0x20;
                *(int*)(cell + 0x3bfacc) &= 0xffffffdf;
                break;
            case '$':
                ((TrackRowBodSlot*)(cell + 0x3bfac8))->set_bod_object(*(void**)(g_game_base + 0x44b34));
                *(unsigned char*)(cell + 0x3bfb04) = 0x17;
                *(int*)(cell + 0x3bfacc) |= 0x20;
                break;
            case '&':
                ((TrackRowBodSlot*)(cell + 0x3bfac8))->set_bod_object(*(void**)(g_game_base + 0x447b4));
                *(unsigned char*)(cell + 0x3bfb04) = 0x22;
                *(int*)(cell + 0x3bfacc) |= 0x20;
                break;
            case '(':
                ++trampoline_counter;
                *(int*)(cell + 0x3bfacc) &= 0xffffffdf;
                if (trampoline_counter == 15)
                    trampoline_counter = 0;
                if (trampoline_counter == 8) {
                    ((TrackRowBodSlot*)(cell + 0x3bfac8))->set_bod_object(*(void**)(g_game_base + 0x444dc));
                    *(int*)(cell + 0x3bfacc) |= 0x20;
                    ((Color4f*)(base + 0x54 * (lane + build_row * 8 + 0xb6cc)))
                        ->store_color4f(1.0f, 1.0f, 1.0f, 0.99900001f);
                }
                *(unsigned char*)(cell + 0x3bfb04) = 0x16;
                break;
            case '+':
                ((TrackRowBodSlot*)(cell + 0x3bfac8))->set_bod_object(*(void**)(g_game_base + 0x44b34));
                *(unsigned char*)(cell + 0x3bfb04) = 0x18;
                *(int*)(cell + 0x3bfacc) |= 0x20;
                break;
            case ',':
                ((TrackRowBodSlot*)(cell + 0x3bfac8))->set_bod_object(*(void**)(g_game_base + 0x44124));
                *(unsigned char*)(cell + 0x3bfb04) = 0x1c;
                *(int*)(cell + 0x3bfacc) |= 0x20;
                break;
            case '-':
                ((TrackRowBodSlot*)(cell + 0x3bfac8))->set_bod_object(*(void**)(g_game_base + 0x447b4));
                *(unsigned char*)(cell + 0x3bfb04) = 0x15;
                *(int*)(cell + 0x3bfacc) |= 0x20;
                break;
            case '.':
                ((TrackRowBodSlot*)(cell + 0x3bfac8))->set_bod_object(*(void**)(g_game_base + 0x447b4));
                *(unsigned char*)(cell + 0x3bfb04) = 1;
                *(int*)(cell + 0x3bfacc) |= 0x20;
                break;
            case '0':
                if (level_mode == 1) {
                    *(int*)row_record = (*(int*)row_record & 0xffffbfff) | 1;
                    *(int*)(row_record + 0x9c) = 0;
                    *(float*)(row_record + 0x90) = (float)lane - 3.5f;
                    *(int*)(row_record + 0x94) = *(int*)(cell + 0x3bfadc);
                    *(float*)(row_record + 0x98) = (float)build_row + 0.5f;
                    if (base[2])
                        *(float*)(row_record + 0x90) *= -1.0f;
                }
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                if ((*(int*)row_record & 0xc0) == 0) {
                    ((TrackRowBodSlot*)(cell + 0x3bfac8))->set_bod_object(*(void**)(g_game_base + 0x44b34));
                    *(unsigned char*)(cell + 0x3bfb04) = 0xf;
                    *(int*)(cell + 0x3bfacc) |= 0x20;
                } else {
                    *(int*)(cell + 0x3bfacc) &= 0xffffffdf;
                    *(unsigned char*)(cell + 0x3bfb04) = 0;
                }
                break;
            case '<':
                ((TrackRowBodSlot*)(cell + 0x3bfac8))->set_bod_object(*(void**)(g_game_base + 0x44d2c));
                *(int*)(cell + 0x3bfae4) = 0;
                *(int*)(cell + 0x3bfae8) = 0;
                *(unsigned char*)(cell + 0x3bfb04) = 6;
                *(int*)(cell + 0x3bfacc) |= 0x20;
                break;
            case '=':
            case '|':
                ((TrackRowBodSlot*)(cell + 0x3bfac8))->set_bod_object(*(void**)(g_game_base + 0x445f4));
                *(unsigned char*)(cell + 0x3bfb04) = 0xe;
                *(int*)(cell + 0x3bfacc) |= 0x20;
                break;
            case '>':
                ((TrackRowBodSlot*)(cell + 0x3bfac8))->set_bod_object(*(void**)(g_game_base + 0x44d2c));
                *(int*)(cell + 0x3bfae4) = 0;
                *(int*)(cell + 0x3bfae8) = 0;
                if (build_row > 0 && *(unsigned char*)(cell + 0x3bf864) == 3) {
                    *(unsigned char*)(cell + 0x3bfb04) = 9;
                    *(unsigned char*)(cell + 0x3bf864) = 0xc;
                } else {
                    *(unsigned char*)(cell + 0x3bfb04) = 3;
                }
                *(int*)(cell + 0x3bfacc) |= 0x20;
                break;
            case '@':
                *(unsigned char*)(cell + 0x3bfb04) = 0;
                *(int*)(cell + 0x3bfacc) &= 0xffffffdf;
                switch_track_mirror();
                break;
            case 'F':
                ((TrackRowBodSlot*)(cell + 0x3bfac8))->set_bod_object(*(void**)(g_game_base + 0x44b34));
                *(unsigned char*)(cell + 0x3bfb04) = 0x13;
                *(int*)(cell + 0x3bfacc) |= 0x20;
                break;
            case 'G':
                ((TrackRowBodSlot*)(cell + 0x3bfac8))->set_bod_object(*(void**)(g_game_base + 0x44b34));
                *(unsigned char*)(cell + 0x3bfb04) = 0x11;
                *(int*)(cell + 0x3bfacc) |= 0x20;
                break;
            case 'J':
                ((TrackRowBodSlot*)(cell + 0x3bfac8))->set_bod_object(*(void**)(g_game_base + 0x44b34));
                *(unsigned char*)(cell + 0x3bfb04) = 0x19;
                *(int*)(cell + 0x3bfacc) |= 0x20;
                break;
            case 'M':
                ((TrackRowBodSlot*)(cell + 0x3bfac8))->set_bod_object(*(void**)(g_game_base + 0x44b34));
                *(unsigned char*)(cell + 0x3bfb04) = 0x12;
                *(int*)(cell + 0x3bfacc) |= 0x20;
                break;
            case 'R':
                *(unsigned char*)(cell + 0x3bfb04) = 0x23;
                *(int*)(cell + 0x3bfacc) &= 0xffffffdf;
                break;
            case '[':
                ((TrackRowBodSlot*)(cell + 0x3bfac8))->set_bod_object(*(void**)(g_game_base + 0x44cf4));
                *(int*)(cell + 0x3bfae4) = 0;
                *(int*)(cell + 0x3bfae8) = 0;
                *(unsigned char*)(cell + 0x3bfb04) = 5;
                *(int*)(cell + 0x3bfacc) |= 0x20;
                break;
            case '_':
                ((TrackRowBodSlot*)(cell + 0x3bfac8))->set_bod_object(*(void**)(g_game_base + 0x44b34));
                *(unsigned char*)(cell + 0x3bfb04) = 0xf;
                *(int*)(cell + 0x3bfacc) |= 0x20;
                break;
            case 'o':
                ((TrackRowBodSlot*)(cell + 0x3bfac8))->set_bod_object(*(void**)(g_game_base + 0x44b34));
                *(unsigned char*)(cell + 0x3bfb04) = 0x10;
                *(int*)(cell + 0x3bfacc) |= 0x20;
                break;
            case '{':
                ((TrackRowBodSlot*)(cell + 0x3bfac8))->set_bod_object(*(void**)(g_game_base + 0x44cf4));
                *(int*)(cell + 0x3bfae4) = 0;
                *(int*)(cell + 0x3bfae8) = 0;
                if (build_row > 0 && *(unsigned char*)(cell + 0x3bf864) == 3) {
                    *(unsigned char*)(cell + 0x3bfb04) = 8;
                    *(unsigned char*)(cell + 0x3bf864) = 0xb;
                } else {
                    *(unsigned char*)(cell + 0x3bfb04) = 2;
                }
                *(int*)(cell + 0x3bfacc) |= 0x20;
                break;
            case '}':
                ((TrackRowBodSlot*)(cell + 0x3bfac8))->set_bod_object(*(void**)(g_game_base + 0x44d64));
                *(int*)(cell + 0x3bfae4) = 0;
                *(int*)(cell + 0x3bfae8) = 0;
                if (build_row > 0 && *(unsigned char*)(cell + 0x3bf864) == 3) {
                    *(unsigned char*)(cell + 0x3bfb04) = 0xa;
                    *(unsigned char*)(cell + 0x3bf864) = 0xd;
                } else {
                    *(unsigned char*)(cell + 0x3bfb04) = 4;
                }
                *(int*)(cell + 0x3bfacc) |= 0x20;
                break;
            case 's':
                ((TrackRowBodSlot*)(cell + 0x3bfac8))->set_bod_object(*(void**)(g_game_base + 0x447b4));
                *(unsigned char*)(cell + 0x3bfb04) = 0x21;
                *(int*)(cell + 0x3bfacc) |= 0x20;
                break;
            default:
                debug_report_stub(
                    "TrackError:%c in Segment %s\n",
                    normalize_segment_glyph_for_track_flags(glyph, build_row, 1),
                    *(char**)(active_segment + 0x10));
                break;
            }
        }
        ++segment_row;
    }

    (void)trampoline_counter;
}
