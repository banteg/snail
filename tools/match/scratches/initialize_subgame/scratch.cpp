// initialize_subgame @ 0x4374b0 (thiscall)

#include "backdrop.h"
#include "border_manager.h"
#include "challenge_setup_screen.h"
#include "frontend_widget.h"
#include "landscape_script_bank.h"
#include "timer_counters.h"
#include "transform_matrix.h"

extern "C" void* memcpy(void* destination, const void* source, unsigned int count);
#pragma intrinsic(memcpy)

struct BuiltinSegmentDefinition;

class RuntimeCallback {
public:
    void noop_runtime_ai();
};

class TimeTrialStringFormatter {
public:
    char* format_time_trial_string(TimerCounters* timer);
};

class LevelSegmentSlotStore {
public:
    void load_builtin_segment_definitions(BuiltinSegmentDefinition** builtins);
};

class WarningRuntime {
public:
    void initialize_warning();
};

class GalaxyRoute {
public:
    void initialize_galaxy();
};

class SubgameBorderManager {
public:
    FrontendWidget* allocate_border();
    int set_border_justify_centre(int justify_centre);
};

class Game {
public:
    void initialize_subgame();
    void reset_subgame();
};

extern char* g_game_base; // data_4df904
extern char g_main_menu_music_path[]; // 0x4a2128
extern char g_menu_background_script_path[]; // 0x4a347c
extern char g_blank_text[]; // 0x4dfb08
extern char g_zero_text[]; // 0x4a493c
extern char g_snailmail_cfg_path[]; // 0x4a170c
extern char g_unknown_game_mode_text[]; // 0x4a4d10
extern char g_config_blob; // 0x4df918
extern int data_4df9b8; // 0x4df9b8
extern int g_landscape_backdrop_variant_selector; // 0x4df9bc
extern BuiltinSegmentDefinition* g_builtin_segment_definitions[]; // 0x4a63d0

char cache_music_file(char* path, int unused, char* unused_default_path); // @ 0x432d50
void rstrcpy_checked_ascii(char* destination, char* source); // @ 0x44e5b0
char* save_config_file(char* file_name, void* bytes, int byte_count); // @ 0x42f540
int report_errorf(char* format, ...); // @ 0x431cc0

void Game::initialize_subgame()
{
    char* game = (char*)this;
    int scratch[6];

    int outer_count = 3200;
    int* cell = (int*)(game + 0x3bfb0c);
    do {
        int inner_count = 8;
        do {
            int* active_cell = cell;
            cell = (int*)((char*)cell + 0x54);
            --inner_count;
            active_cell[0] = 0;
            active_cell[1] = 0;
            active_cell[2] = 0;
            active_cell[3] = 0;
        } while (inner_count);
        --outer_count;
    } while (outer_count);

    int zero = 0;
    int selector = *(int*)(game + 0x1270fc8);
    if (selector == 2 || selector == 1) {
        cache_music_file(g_main_menu_music_path, zero, g_blank_text);
        int script_index =
            ((LandscapeScriptBank*)(g_game_base + 0x106c218))
                ->load_landscape_script_by_name(g_menu_background_script_path);
        ((Backdrop*)(g_game_base + 0x4ec10))
            ->change_backdrop(
                (LandscapeScriptRecord*)(g_game_base + 0x106c7bc
                    + script_index * sizeof(LandscapeScriptRecord)),
                (char)zero);
        ((SubgameBorderManager*)(g_game_base + 0xb4c))
            ->set_border_justify_centre(0x41c80000);
    }

    int level_mode = *(int*)(game + 0x40);
    char* level_record = 0;
    if (level_mode == 0) {
        level_record = game + 0x68b4d0;
    } else if (level_mode == 1) {
        level_record = game + 0x7e7b10;
        *(char**)(game + 0x68b4c8) = level_record;
        *(int*)(game + 0x355d94) = *(int*)(level_record + 4);
        memcpy(game + 0x355d98, level_record + 8, 0x18);
    } else if (level_mode == 4) {
        level_record = game + 0x944150;
    }

    if (level_record != 0 && level_mode != 1) {
        *(char**)(game + 0x68b4c8) = level_record;
        *(int*)(game + 0x355d94) = *(int*)(level_record + 4);
        memcpy(game + 0x355d98, level_record + 8, 0x18);
    }

    if (*(unsigned char*)(game + 0xff25d1) != 0)
        *(int*)(game + 0x30) = *(int*)(*(char**)(game + 0xff25d4) + 0x48);

    *(unsigned char*)(game + 9) = (unsigned char)zero;
    *(unsigned char*)(game + 8) = (unsigned char)zero;
    *(int*)(game + 0x0c) = zero;
    *(int*)(game + 0x10) = 0x3d088889;
    ((RuntimeCallback*)(game + 0x68b4c8))->noop_runtime_ai();
    *(int*)(game + 0x3c) = zero;
    *(int*)(game + 0x1272828) = zero;

    FrontendWidget* top_score =
        ((SubgameBorderManager*)(g_game_base + 0xb4c))->allocate_border();
    *(FrontendWidget**)(game + 0x35bb88) = top_score;
    top_score->initialize_frontend_widget(
        0x400002,
        g_zero_text,
        0x14,
        400.0f,
        14.0f,
        ((Color4f*)scratch)->set_color_rgba(1.0f, 1.0f, 1.0f, 0.0299999993f),
        3,
        300.0f);
    *(int*)((char*)top_score + 0x6f0) = 0x3fc00000;
    *(int*)((char*)top_score + 0x274) = 7;
    *((unsigned char*)top_score + 0x2cc) = (unsigned char)zero;

    if (*(int*)(game + 0x40) == 0) {
        FrontendWidget* life_icon =
            ((SubgameBorderManager*)(g_game_base + 0xb4c))->allocate_border();
        *(FrontendWidget**)(game + 0x35bb90) = life_icon;
        life_icon->initialize_frontend_sprite_button(
            0x400800,
            122,
            0.0f,
            58.0f,
            ((Color4f*)scratch)->set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            0.0f,
            4);
        life_icon->hide_border_init();
        *(int*)((char*)life_icon + 0x178) = zero;

        FrontendWidget* life_score =
            ((SubgameBorderManager*)(g_game_base + 0xb4c))->allocate_border();
        *(FrontendWidget**)(game + 0x35bb94) = life_score;
        life_score->initialize_frontend_widget(
            0x400002,
            g_zero_text,
            0x14,
            47.0f,
            80.0f,
            ((Color4f*)scratch)->set_color_rgba(1.0f, 1.0f, 1.0f, 0.0299999993f),
            0,
            0.0f);
        life_score->hide_border_init();
        *(int*)((char*)life_score + 0x6f0) = 0x3f333333;

        int icon_index = 0;
        FrontendWidget** icon_slot = (FrontendWidget**)(game + 0x35bb98);
        do {
            *icon_slot =
                ((SubgameBorderManager*)(g_game_base + 0xb4c))->allocate_border();
            (*icon_slot)->initialize_frontend_sprite_button(
                0x400800,
                123,
                (float)icon_index * 24.0f + 13.0f,
                430.0f,
                ((Color4f*)scratch)->set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
                0.0f,
                4);
            *(int*)((char*)*icon_slot + 0x178) = zero;
            (*icon_slot)->hide_border_init();
            ++icon_index;
            ++icon_slot;
        } while (icon_index < 9);
    }

    level_mode = *(int*)(game + 0x40);
    if (*(int*)(game + 0xf935bc) == level_mode) {
        if (level_mode == 4) {
            char* text =
                ((TimeTrialStringFormatter*)(game + 0xff25e0))
                    ->format_time_trial_string((TimerCounters*)(game + 0xf93598));
            rstrcpy_checked_ascii((char*)top_score + 0x2cc, text);
        } else {
            top_score->border_add_text_number(*(int*)(game + 0xf93594));
        }
    } else {
        if (level_mode == 4) {
            ((TimerCounters*)scratch)->zero_timer_counters();
            char* text =
                ((TimeTrialStringFormatter*)(game + 0xff25e0))
                    ->format_time_trial_string((TimerCounters*)scratch);
            rstrcpy_checked_ascii((char*)top_score + 0x2cc, text);
        } else {
            top_score->border_add_text_number(zero);
        }
    }

    FrontendWidget* bottom_score =
        ((SubgameBorderManager*)(g_game_base + 0xb4c))->allocate_border();
    *(FrontendWidget**)(game + 0x35bb8c) = bottom_score;
    bottom_score->initialize_frontend_widget(
        0x400002,
        g_zero_text,
        0x14,
        40.0f,
        14.0f,
        ((Color4f*)scratch)->set_color_rgba(1.0f, 1.0f, 1.0f, 0.0299999993f),
        3,
        -71.0f);
    *(int*)((char*)bottom_score + 0x6f0) = 0x3fc00000;
    *(int*)((char*)bottom_score + 0x274) = 7;
    *((unsigned char*)bottom_score + 0x2cc) = (unsigned char)zero;

    switch (*(int*)(game + 0x40)) {
    case 0:
    case 1:
        bottom_score->border_add_text_number(*(int*)(game + 0x355d94));
        break;
    case 2:
    case 3:
        bottom_score->hide_border_init();
        top_score->hide_border_init();
        break;
    case 4: {
        char* text =
            ((TimeTrialStringFormatter*)(game + 0xff25e0))
                ->format_time_trial_string((TimerCounters*)(game + 0x355d98));
        rstrcpy_checked_ascii((char*)bottom_score + 0x2cc, text);
        break;
    }
    default:
        break;
    }

    if (*(unsigned char*)(g_game_base + 0x4f2e0) != 0 || *(int*)(game + 0x40) == 7) {
        bottom_score->hide_border_init();
        top_score->hide_border_init();
    }

    if (*(unsigned char*)(g_game_base + 0x30d) != 0)
        return;

    *(unsigned char*)(g_game_base + 0x30d) = (unsigned char)zero;
    *(int*)(g_game_base + 0x310) = zero;
    ((LevelSegmentSlotStore*)(game + 0x1b01ec))
        ->load_builtin_segment_definitions(g_builtin_segment_definitions);
    set_matrix_identity((TransformMatrix*)(game + 0x3bb79c));
    *(int*)(game + 0x3bbb70) = zero;
    *(int*)(game + 0x3bbb6c) = (int)this;
    *(int*)(game + 0x3be0c8) = *(int*)(game + 0x3bb7cc);
    *(unsigned char*)(game + 0x3bbb81) = (unsigned char)zero;
    *(int*)(game + 0x3be0cc) = *(int*)(game + 0x3bb7d0);
    *(unsigned char*)(game + 0x3bbb80) = (unsigned char)zero;
    *(int*)(game + 0x3bbb68) = zero;
    *(int*)(game + 0x3be0d0) = *(int*)(game + 0x3bb7d4);
    *(int*)(game + 0x3bb768) &= ~0x20;
    ((WarningRuntime*)(game + 0x3bbb58))->initialize_warning();

    selector = *(int*)(game + 0x1270fc8);
    if (selector != 0 && selector != 3) {
        if (*(unsigned char*)(game + 0xff25d1) == 0) {
            switch (*(int*)(game + 0x40)) {
            case 0:
                if (selector == 1) {
                    int next_level = *(int*)(game + 0x44) + 1;
                    *(int*)(game + 0x44) = next_level;
                    if (next_level > data_4df9b8) {
                        data_4df9b8 = next_level;
                        save_config_file(g_snailmail_cfg_path, &g_config_blob, 0xc4);
                    }
                    g_landscape_backdrop_variant_selector = *(int*)(game + 0x44);
                }
                // Native mode 0 continues into the galaxy setup path.
            case 4:
                ((GalaxyRoute*)(game + 0x1260020))->initialize_galaxy();
                reset_subgame();
                return;
            case 1:
                ((ChallengeSetupScreen*)(game + 0x125ffe0))->initialize_challenge_setup_screen();
                reset_subgame();
                return;
            case 7:
                *(int*)(game + 0x3c) = zero;
                reset_subgame();
                return;
            default:
                report_errorf(g_unknown_game_mode_text);
                reset_subgame();
                return;
            }
        }
        *(int*)(game + 0x30) = *(int*)(*(char**)(game + 0xff25d4) + 0x48);
    }

    reset_subgame();
}
