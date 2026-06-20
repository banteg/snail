// build_subgame_level @ 0x437eb0 (thiscall, ret 0x4)

#include "high_score_record.h"
#include "slug_voice_manager.h"

class StarField {
public:
    int unhide_star_field();
};

class GolbPathBank {
public:
    void initialize_enemy_manager();
};

class DamageGaugeController {
public:
    void initialize_damage_gauge();
};

class RuntimeCallback {
public:
    void noop_runtime_ai();
};

class SubLazerPool {
public:
    int* initialize_sub_lazer_pool();
};

class SaltHazardPool {
public:
    int* initialize_salt_hazard_pool();
};

class VoiceManager {
public:
    void reset_voice_manager();
};

class LevelDefinitionLoader {
public:
    int* load_frontend_level_by_mode_and_index(int mode, int level_index);
};

class TrackParcelPool {
public:
    void initialize_track_parcel_slots();
};

class FrontendWidget {
public:
    int hide_border_init();
    int unhide_border_init();
};

class LandscapeScriptBank {
public:
    int load_landscape_script_by_name(char* script_name);
};

class ActiveLandscapeEntry {
public:
    void activate_landscape_entry(int script_index);
};

struct BodNode {
    int callback;
    unsigned int list_flags;
    BodNode* list_prev;
    BodNode* list_next;
};

struct BodList {
    int unknown_00;
    BodNode* first;
    BodNode* free_top;
};

class MouseCursorState {
public:
    void release_mouse_cursor();
};

class Player {
public:
    int initialize_subgoldy(int player_slot);
};

class Game {
public:
    void build_subgame_level(int level_index);
    void hide_gameplay_scores();
    void unhide_gameplay_scores();
    float calc_slider_to_rate(float slider);
    int rebuild_track_runtime_from_segments(int level_index);
    void calc_subgame_rate();
};

extern char* g_game_base;
extern VoiceManager g_voice_manager;
extern char g_blank_text[];
extern int g_completion_bonus_x_source[2];
extern int g_completion_bonus_y_source;

int next_math_random_value();
float random_float_below(float upper_bound, const char* tag);
char cache_music_file(char* path, int unused, char* unused_default_path);
int report_errorf(char* format, ...);
int sprintf(char* buffer, char* format, ...);
void set_input_controller_pointer_authored_xy(int controller, float x, float y);

void Game::build_subgame_level(int level_index)
{
    char* game = (char*)this;

    ((StarField*)(g_game_base + 0x4f33c))->unhide_star_field();
    if (*(int*)(game + 0x40) == 7)
        hide_gameplay_scores();
    else
        unhide_gameplay_scores();

    int zero = 0;
    switch ((unsigned int)(next_math_random_value() * 0.000122070312f)) {
    case 0:
        cache_music_file("music/1.ogg", zero, g_blank_text);
        break;
    case 1:
        cache_music_file("music/2.ogg", zero, g_blank_text);
        break;
    case 3:
        cache_music_file("music/4.ogg", zero, g_blank_text);
        break;
    case 2:
    case 4:
        cache_music_file("music/3.ogg", zero, g_blank_text);
        break;
    }

    *(float*)(game + 0x1270fcc) = 50.0f;
    *(float*)(game + 0x1270fd0) = 100.0f;
    ((GolbPathBank*)(game + 0x1270fd4))->initialize_enemy_manager();
    ((DamageGaugeController*)(game + 0x3bbb28))->initialize_damage_gauge();
    ((RuntimeCallback*)(game + 0x3bbb54))->noop_runtime_ai();
    ((SubLazerPool*)(game + 0x356b00))->initialize_sub_lazer_pool();
    ((SaltHazardPool*)(game + 0x3578c0))->initialize_salt_hazard_pool();
    g_voice_manager.reset_voice_manager();

    ((LevelDefinitionLoader*)(game + 0xa874))->load_frontend_level_by_mode_and_index(
        *(int*)(game + 0x40), level_index);

    if (*(unsigned char*)(game + 0xff25d0) != zero
        || *(unsigned char*)(game + 0xff25d1) != zero) {
        *(float*)(game + 0x30) =
            (*(HighScoreRecord**)(game + 0xff25d4))->replay_speed_scalar;
        *(int*)(game + 0x40) =
            (*(HighScoreRecord**)(game + 0xff25d4))->replay_mode_id;
        *(int*)(game + 0x2c) =
            (*(HighScoreRecord**)(game + 0xff25d4))->challenge_difficulty_value;
        *(int*)(game + 0x28) =
            (*(HighScoreRecord**)(game + 0xff25d4))->challenge_speed_value;
        *(float*)(game + 0x34) =
            (float)(*(HighScoreRecord**)(game + 0xff25d4))->challenge_difficulty_value
            * 0.00999999978f;
    } else {
        int level_mode = *(int*)(game + 0x40);
        if (level_mode == 3) {
            *(float*)(game + 0x30) = *(float*)&g_completion_bonus_x_source[1];
        } else if (level_mode == 0 || level_mode == 4 || level_mode == 7) {
            if (*(int*)(game + 0x1b01d0) == (int)0xbf800000) {
                *(float*)(game + 0x30) = calc_slider_to_rate(0.0f);
            } else {
                float normalized_speed =
                    *(float*)(game + 0x1b01d0) * 0.00999999978f;
                *(float*)(game + 0x30) =
                    normalized_speed * 0.900000036f + 0.200000003f;
            }
        } else if (level_mode == 1) {
            *(float*)(game + 0x30) = calc_slider_to_rate(
                (float)g_completion_bonus_x_source[0] * 0.00999999978f);
            *(float*)(game + 0x34) =
                (float)g_completion_bonus_y_source * 0.00999999978f;
        } else if (level_mode == 2) {
            *(float*)(game + 0x30) = calc_slider_to_rate(
                *(float*)&g_completion_bonus_x_source[1]);
        }
    }

    if (*(unsigned char*)(game + 0xff25d0) != zero
        || *(unsigned char*)(game + 0xff25d1) != zero) {
        *(float*)(game + 0x125ffd8) =
            (*(HighScoreRecord**)(game + 0xff25d4))->garbage_scalar;
        *(float*)(game + 0x125ffdc) =
            (*(HighScoreRecord**)(game + 0xff25d4))->salt_scalar;
    } else {
        int level_mode = *(int*)(game + 0x40);
        if (level_mode == 2 || level_mode == 3 || level_mode == 0
            || level_mode == 4 || level_mode == 7) {
            *(float*)(game + 0x125ffd8) =
                *(float*)(game + 0x1b01d4) * 0.00999999978f;
            *(float*)(game + 0x125ffdc) =
                *(float*)(game + 0x1b01d8) * 0.00999999978f;
        } else if (level_mode == 1) {
            float normalized_garbage_difficulty =
                (float)g_completion_bonus_y_source * 0.00999999978f;
            *(float*)(game + 0x125ffd8) =
                normalized_garbage_difficulty * 0.800000012f;
            float normalized_salt_difficulty =
                (float)g_completion_bonus_y_source * 0.00999999978f;
            *(float*)(game + 0x125ffdc) =
                normalized_salt_difficulty * 0.800000012f;
        }
    }

    ((TrackParcelPool*)(game + 0x125e480))->initialize_track_parcel_slots();
    if (*(unsigned char*)(g_game_base + 0x4f2e0) == 1) {
        (*(FrontendWidget**)(game + 0x35bb88))->hide_border_init();
        (*(FrontendWidget**)(game + 0x35bb8c))->hide_border_init();
    }

    rebuild_track_runtime_from_segments(level_index);

    if (*(int*)(game + 0x1b01e4) == 5) {
        int* fallback_level_index = &level_index;
        int landscape_index;
        switch ((unsigned int)random_float_below(4.0f, 0)) {
        case 0:
            landscape_index =
                ((LandscapeScriptBank*)(g_game_base + 0x106c218))
                    ->load_landscape_script_by_name("SpaceBluesWhorl.txt");
            break;
        case 1:
            landscape_index =
                ((LandscapeScriptBank*)(g_game_base + 0x106c218))
                    ->load_landscape_script_by_name("SpaceGreenWarp.txt");
            break;
        case 2:
            landscape_index =
                ((LandscapeScriptBank*)(g_game_base + 0x106c218))
                    ->load_landscape_script_by_name("SpacePurple.txt");
            break;
        case 3:
            landscape_index =
                ((LandscapeScriptBank*)(g_game_base + 0x106c218))
                    ->load_landscape_script_by_name("SpaceRed.txt");
            break;
        default:
            landscape_index = *fallback_level_index;
            break;
        }

        ((ActiveLandscapeEntry*)(game + 0xff7c00))
            ->activate_landscape_entry(landscape_index);
        if (random_float_below(1.0f, 0) > 0.5f)
            *(unsigned char*)(g_game_base + 0x4ec64) = 1;
        else
            *(unsigned char*)(g_game_base + 0x4ec64) = (unsigned char)zero;
    } else {
        ((ActiveLandscapeEntry*)(game + 0xff7c00))
            ->activate_landscape_entry(*(int*)(game + 0x1b01dc));
    }

    BodNode* track_bod_list = (BodNode*)(game + 0x355b9c);
    {
        BodNode* start_row = (BodNode*)(game + 0x359080);
        if ((start_row->list_flags & 0x200) != zero) {
            report_errorf("List ADDafter");
        } else {
            start_row->list_prev = track_bod_list;
            start_row->list_next = track_bod_list->list_next;
            track_bod_list->list_next = start_row;
            if (start_row->list_next != 0)
                start_row->list_next->list_prev = start_row;
            start_row->list_flags |= 0x200;
        }
    }

    *(int*)(game + 0x359098) = zero;
    *(int*)(game + 0x359094) = zero;
    *(int*)(game + 0x359090) = zero;
    unsigned int start_flags = *(unsigned int*)(game + 0x359084);
    *(void**)(game + 0x3590d4) = game + 0x3bb764;
    *(float*)(game + 0x359098) = (float)*(int*)(game + 0x50);
    int row_alpha = 0x3f7fbe77;
    *(int*)(game + 0x3590b4) = row_alpha;
    *(unsigned int*)(game + 0x359084) = start_flags & ~0x20;

    {
        BodNode* completion_row = (BodNode*)(game + 0x3590e0);
        if ((completion_row->list_flags & 0x200) != zero) {
            report_errorf("List ADDafter");
        } else {
            completion_row->list_prev = track_bod_list;
            completion_row->list_next = track_bod_list->list_next;
            track_bod_list->list_next = completion_row;
            if (completion_row->list_next != 0)
                completion_row->list_next->list_prev = completion_row;
            completion_row->list_flags |= 0x200;
        }
    }

    *(int*)(game + 0x3590f8) = zero;
    *(int*)(game + 0x3590f4) = zero;
    *(int*)(game + 0x3590f0) = zero;
    unsigned int completion_flags = *(unsigned int*)(game + 0x3590e4);
    *(void**)(game + 0x359134) = game + 0x3bb764;
    *(unsigned int*)(game + 0x3590e4) = completion_flags & ~0x20;
    *(float*)(game + 0x3590f8) = (float)*(int*)(game + 0x58);
    *(int*)(game + 0x359114) = row_alpha;

    *(unsigned char*)(game + 0xa854) = (unsigned char)zero;
    *(int*)(game + 0xff25dc) = zero;
    *(int*)(game + 0x1272828) = zero;
    *(int*)(game + 0x3c) = 2;

    int one = 1;
    *(int*)(g_game_base + 0x56c) = one;
    ((MouseCursorState*)(g_game_base + 0x290))->release_mouse_cursor();
    *(int*)(game + 0x3bbb70) = one;
    *(int*)(game + 0x3be0d4) = zero;
    ((Player*)(game + 0x3bb764))->initialize_subgoldy(one);

    BodNode* node = (BodNode*)(game + 0x3bf2c8);
    if ((node->list_flags & 0x200) != zero) {
        report_errorf("List ADD");
    } else {
        BodNode** first_ref = &((BodList*)(g_game_base + 0x5a8))->first;
        BodNode* first = *first_ref;
        if (first == 0) {
            *first_ref = node;
            node->list_prev = 0;
            (*first_ref)->list_next = 0;
        } else {
            first->list_prev = node;
            (*first_ref)->list_prev->list_next = *first_ref;
            BodNode* new_first = (*first_ref)->list_prev;
            *first_ref = new_first;
            new_first->list_prev = 0;
        }
        node->list_flags |= 0x200;
    }

    node = (BodNode*)(game + 0x3be734);
    if ((node->list_flags & 0x200) != zero) {
        report_errorf("List ADD");
    } else {
        BodNode** first_ref = &((BodList*)(g_game_base + 0x5a8))->first;
        BodNode* first = *first_ref;
        if (first == 0) {
            *first_ref = node;
            node->list_prev = 0;
            (*first_ref)->list_next = 0;
        } else {
            first->list_prev = node;
            (*first_ref)->list_prev->list_next = *first_ref;
            BodNode* new_first = (*first_ref)->list_prev;
            *first_ref = new_first;
            new_first->list_prev = 0;
        }
        node->list_flags |= 0x200;
    }

    node = (BodNode*)(game + 0x3beb10);
    if ((node->list_flags & 0x200) != zero) {
        report_errorf("List ADD");
    } else {
        BodNode** first_ref = &((BodList*)(g_game_base + 0x5a8))->first;
        BodNode* first = *first_ref;
        if (first == 0) {
            *first_ref = node;
            node->list_prev = 0;
            (*first_ref)->list_next = 0;
        } else {
            first->list_prev = node;
            (*first_ref)->list_prev->list_next = *first_ref;
            BodNode* new_first = (*first_ref)->list_prev;
            *first_ref = new_first;
            new_first->list_prev = 0;
        }
        node->list_flags |= 0x200;
    }

    node = (BodNode*)(game + 0x3beeec);
    if ((node->list_flags & 0x200) != zero) {
        report_errorf("List ADD");
    } else {
        BodNode** first_ref = &((BodList*)(g_game_base + 0x5a8))->first;
        BodNode* first = *first_ref;
        if (first == 0) {
            *first_ref = node;
            node->list_prev = 0;
            (*first_ref)->list_next = 0;
        } else {
            first->list_prev = node;
            (*first_ref)->list_prev->list_next = *first_ref;
            BodNode* new_first = (*first_ref)->list_prev;
            *first_ref = new_first;
            new_first->list_prev = 0;
        }
        node->list_flags |= 0x200;
    }

    node = (BodNode*)(game + 0x3bf97c);
    if ((node->list_flags & 0x200) != zero) {
        report_errorf("List ADD");
    } else {
        BodNode** first_ref = &((BodList*)(g_game_base + 0x5a8))->first;
        BodNode* first = *first_ref;
        if (first == 0) {
            *first_ref = node;
            node->list_prev = 0;
            (*first_ref)->list_next = 0;
        } else {
            first->list_prev = node;
            (*first_ref)->list_prev->list_next = *first_ref;
            BodNode* new_first = (*first_ref)->list_prev;
            *first_ref = new_first;
            new_first->list_prev = 0;
        }
        node->list_flags |= 0x200;
    }
    unsigned int visible_flags = node->list_flags;
    ((unsigned char*)&visible_flags)[0] |= 0x80;
    node->list_flags = visible_flags;

    node = (BodNode*)(game + 0x3be0e8);
    if ((node->list_flags & 0x200) != zero) {
        report_errorf("List ADD");
    } else {
        BodNode** first_ref = &((BodList*)(g_game_base + 0x5a8))->first;
        BodNode* first = *first_ref;
        if (first == 0) {
            *first_ref = node;
            node->list_prev = 0;
            (*first_ref)->list_next = 0;
        } else {
            first->list_prev = node;
            (*first_ref)->list_prev->list_next = *first_ref;
            BodNode* new_first = (*first_ref)->list_prev;
            *first_ref = new_first;
            new_first->list_prev = 0;
        }
        node->list_flags |= 0x200;
    }

    BodNode* player_node = (BodNode*)(game + 0x3bb764);
    if ((player_node->list_flags & 0x200) != zero) {
        report_errorf("List ADD");
    } else {
        BodNode** first_ref = &((BodList*)(g_game_base + 0x5a8))->first;
        BodNode* first = *first_ref;
        if (first == 0) {
            *first_ref = player_node;
            player_node->list_prev = 0;
            (*first_ref)->list_next = 0;
        } else {
            first->list_prev = player_node;
            (*first_ref)->list_prev->list_next = *first_ref;
            BodNode* new_first = (*first_ref)->list_prev;
            *first_ref = new_first;
            new_first->list_prev = 0;
        }
        player_node->list_flags |= 0x200;
    }

    ((SlugVoiceManager*)(game + 0x35bb7c))->initialize_slug_voice_manager();

    BodNode* voice_node = (BodNode*)(game + 0xff7bc4);
    BodNode* voice_list = (BodNode*)(game + 0x355bd4);
    if ((voice_node->list_flags & 0x200) != zero) {
        report_errorf("List ADDafter");
    } else {
        voice_node->list_prev = voice_list;
        voice_node->list_next = voice_list->list_next;
        voice_list->list_next = voice_node;
        if (voice_node->list_next != 0)
            voice_node->list_next->list_prev = voice_node;
        voice_node->list_flags |= 0x200;
    }
    *(BodNode**)(game + 0xff7bfc) = player_node;

    if (*(int*)(game + 0x40) == zero) {
        sprintf((char*)(*(FrontendWidget**)(game + 0x35bb94)) + 0x2cc,
            "0/%i", *(int*)(game + 0x1b01e0));
        (*(FrontendWidget**)(game + 0x35bb90))->unhide_border_init();
        (*(FrontendWidget**)(game + 0x35bb94))->unhide_border_init();
    }

    set_input_controller_pointer_authored_xy(0, 320.0f, 240.0f);
    set_input_controller_pointer_authored_xy(1, 320.0f, 240.0f);
    *(float*)(game + 0x3bdea0) = 320.0f;
    *(float*)(game + 0x3bdea4) = 320.0f;
    *(unsigned char*)game = 1;
    calc_subgame_rate();
}
