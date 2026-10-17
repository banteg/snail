// Pro-Challenge galaxy, New Game menu entry, mobile CalcRate rules,
// and ScorePro.dat / SnailMailPro.cfg persistence.

#include <stdio.h>
#include <string.h>

#include "archive_index.h"
#include "backdrop.h"
#include "border_manager.h"
#include "extras.h"
#include "frontend_widget.h"
#include "galaxy_route_types.h"
#include "game_root.h"
#include "high_score.h"
#include "input_state.h"
#include "landscape_manager.h"
#include "new_game_menu.h"
#include "rshell.h"
#include "rstring.h"
#include "rtext.h"
#include "runtime_config.h"
#include "segment_catalog_types.h"
#include "sprite.h"
#include "sub_high_score.h"
#include "sub_tracks.h"
#include "subgame_runtime.h"
#include "texture_registry.h"
#include "thanks_screen.h"

extern char* g_current_level_definition_name;
extern char g_back_text[];

float Sin(float angle);
char* load_file_bytes_from_archive_or_fs(char* path, char* out_buffer, int* out_size);
void* allocate_tracked_memory(int size, char* name);
void free_tracked_memory(void* memory);
void xor_decode_buffer_with_index(void* buffer, int byte_count);
int write_file_bytes(char* file_name, void* bytes, int byte_count);

void intro_init_recovered(cRIntro* self)
    __asm__("_ZN7cRIntro14Init_recoveredEv");
void intro_ai_recovered(cRIntro* self)
    __asm__("_ZN7cRIntro12AI_recoveredEv");
void galaxy_init_recovered(cRGalaxy* self)
    __asm__("_ZN8cRGalaxy14Init_recoveredEv");
void load_frontend_level_recovered(cRSubTracks* self, int mode, int level_index)
    __asm__("_ZN11cRSubTracks47load_frontend_level_by_mode_and_index_recoveredEii");
void calc_rate_recovered(cRSubGame* self)
    __asm__("_ZN9cRSubGame18CalcRate_recoveredEv");
void splash_init_recovered(cRSplash* self)
    __asm__("_ZN8cRSplash14Init_recoveredEv");
void high_score_init_recovered(cRHighScore* self, int mode, int rank)
    __asm__("_ZN11cRHighScore14Init_recoveredEii");
void high_score_ai_recovered(cRHighScore* self)
    __asm__("_ZN11cRHighScore12AI_recoveredEv");
void mini_save_recovered(cRSubHighScore* self, unsigned char save_mask)
    __asm__("_ZN14cRSubHighScore18MiniSave_recoveredEh");
char* save_config_file_recovered(char* file_name, void* bytes, int byte_count)
    __asm__("_Z26save_config_file_recoveredPcPvi");

namespace {

enum {
    kProGalaxyCount = 2,
    kProRouteSlotCount = 11,
    kProMaxRouteIndex = 10,
};

struct ProPoint {
    float x;
    float y;
};

const ProPoint kProRoutePoints[kProRouteSlotCount] = {
    {120.0f, 500.0f},
    {139.0f, 258.0f},
    {164.0f, 161.0f},
    {278.0f, 149.0f},
    {273.0f, 276.0f},
    {343.0f, 237.0f},
    {553.0f, 257.0f},
    {646.0f, 302.0f},
    {665.0f, 441.0f},
    {591.0f, 418.0f},
    {530.0f, 364.0f},
};

cRGalaxy g_postal_galaxy_layout;
cRGalaxy g_pro_galaxy_layout;

SubSolution g_postal_records_backup[SUB_HIGH_SCORE_TOP_TEN_STORAGE_COUNT];
SubSolution g_pro_records[SUB_HIGH_SCORE_TOP_TEN_STORAGE_COUNT];

cRTexture* g_normal_level_select_tex = 0;
cRTexture* g_normal_border_tex = 0;
cRTexture* g_normal_line_tex = 0;
cRTexture* g_pro_level_select_tex = 0;
cRTexture* g_pro_border_tex = 0;
cRTexture* g_pro_line_tex = 0;

cRBorder* g_pro_challenge_button = 0;

bool g_pro_initialized = false;
bool g_pro_mode_active = false;
bool g_high_score_pro_view = false;
bool g_pro_state_swapped = false;

int g_saved_postal_highest_route = 1;
int g_saved_postal_selected_route = 1;
int g_pro_highest_route_index = 1;
int g_pro_selected_route_index = 1;

float scale_galaxy_x(float x)
{
    return x * 0.80000001f;
}

float scale_galaxy_y(float y)
{
    return (y * 0.80000001f - 240.0f) * 0.93000001f + 250.0f;
}

void save_pro_progress_file()
{
    int progress[2] = {g_pro_highest_route_index, g_pro_selected_route_index};
    save_config_file_recovered((char*)"SnailMailPro.cfg", progress, sizeof(progress));
}

void load_pro_progress_file()
{
    g_pro_highest_route_index = 1;
    g_pro_selected_route_index = 1;
    FILE* f = fopen("SnailMailPro.cfg", "rb");
    if (!f)
        return;
    int progress[2] = {1, 1};
    if (fread(progress, sizeof(int), 2, f) == 2) {
        if (progress[0] >= 1 && progress[0] <= kProMaxRouteIndex)
            g_pro_highest_route_index = progress[0];
        if (progress[1] >= 1 && progress[1] <= g_pro_highest_route_index)
            g_pro_selected_route_index = progress[1];
    }
    fclose(f);
}

void save_pro_high_scores_file()
{
    const int kBufferSize = 0x4c4b40;
    char* bytes = (char*)allocate_tracked_memory(kBufferSize, (char*)"High Score Table");
    char* out = bytes;
    int bytes_used = 0;
    for (int i = 0; i < SUB_HIGH_SCORE_TOP_TEN_STORAGE_COUNT; ++i) {
        if (g_pro_records[i].active == 1) {
            bytes_used += g_pro_records[i].Save((SubSolutionHeader*)out);
            out = bytes + bytes_used;
        }
    }
    xor_decode_buffer_with_index(bytes, bytes_used);
    write_file_bytes((char*)"ScorePro.dat", bytes, bytes_used);
    free_tracked_memory(bytes);
}

void swap_in_pro_state()
{
    if (g_pro_state_swapped || !g_pro_initialized || !g_game)
        return;
    g_saved_postal_highest_route = g_runtime_config.highest_galaxy_route_index;
    g_saved_postal_selected_route = g_runtime_config.landscape_backdrop_variant_selector;
    g_runtime_config.highest_galaxy_route_index = g_pro_highest_route_index;
    g_runtime_config.landscape_backdrop_variant_selector = g_pro_selected_route_index;

    memcpy(
        g_postal_records_backup,
        g_game->subgame.sub_high_score.postal_records,
        sizeof(g_postal_records_backup));
    memcpy(
        g_game->subgame.sub_high_score.postal_records,
        g_pro_records,
        sizeof(g_pro_records));

    g_postal_galaxy_layout = g_game->subgame.galaxy;
    g_game->subgame.galaxy = g_pro_galaxy_layout;

    g_sprite_texture_table[150] = g_pro_level_select_tex;
    g_sprite_texture_table[152] = g_pro_border_tex;
    g_sprite_texture_table[153] = g_pro_line_tex;

    g_pro_state_swapped = true;
}

void swap_out_pro_state()
{
    if (!g_pro_state_swapped || !g_pro_initialized || !g_game)
        return;
    if (g_runtime_config.highest_galaxy_route_index >= 1
        && g_runtime_config.highest_galaxy_route_index <= kProMaxRouteIndex) {
        g_pro_highest_route_index = g_runtime_config.highest_galaxy_route_index;
    }
    if (g_runtime_config.landscape_backdrop_variant_selector >= 1
        && g_runtime_config.landscape_backdrop_variant_selector <= g_pro_highest_route_index) {
        g_pro_selected_route_index = g_runtime_config.landscape_backdrop_variant_selector;
    }

    memcpy(
        g_pro_records,
        g_game->subgame.sub_high_score.postal_records,
        sizeof(g_pro_records));
    memcpy(
        g_game->subgame.sub_high_score.postal_records,
        g_postal_records_backup,
        sizeof(g_postal_records_backup));

    g_runtime_config.highest_galaxy_route_index = g_saved_postal_highest_route;
    g_runtime_config.landscape_backdrop_variant_selector = g_saved_postal_selected_route;

    g_game->subgame.galaxy = g_postal_galaxy_layout;

    g_sprite_texture_table[150] = g_normal_level_select_tex;
    g_sprite_texture_table[152] = g_normal_border_tex;
    g_sprite_texture_table[153] = g_normal_line_tex;

    g_pro_state_swapped = false;
}

void import_pro_landscape(char* name, int target_sprite_id)
{
    cRLandscapeManager& lm = g_game->subgame.landscape_manager;
    int old_count = lm.script_count;
    int default_id = old_count * 2 + 6;
    cRTexture* saved_a = g_sprite_texture_table[default_id];
    cRTexture* saved_b = g_sprite_texture_table[default_id + 1];
    int idx = lm.Import(name);
    if (idx == old_count) {
        g_sprite_texture_table[target_sprite_id] = g_sprite_texture_table[default_id];
        g_sprite_texture_table[target_sprite_id + 1] = g_sprite_texture_table[default_id + 1];
        g_sprite_texture_table[default_id] = saved_a;
        g_sprite_texture_table[default_id + 1] = saved_b;
        lm.scripts[idx].backdrop_texture_id = target_sprite_id;
    }
}

void build_pro_galaxy_layout()
{
    memset(&g_pro_galaxy_layout, 0, sizeof(g_pro_galaxy_layout));
    g_pro_galaxy_layout.active = 0;
    g_pro_galaxy_layout.record_count = 1;
    g_pro_galaxy_layout.level_progress_base = &g_game->subgame;

    char* file_text = load_file_bytes_from_archive_or_fs(
        (char*)"Galaxy/_GalaxyPro.txt", (char*)get_archive_data_base(), 0);
    if (!file_text)
        return;

    // StarmapProbg has both Pro galaxies painted in, and Android's cRGalaxy::Render
    // (000593e0) draws no galaxy sprites, so the PC Galaxy000-009 sprites stay off screen.
    for (int g = 0; g < 10; ++g) {
        g_pro_galaxy_layout.route_names[g].map_x = -1000.0f;
        g_pro_galaxy_layout.route_names[g].map_y = -1000.0f;
        g_pro_galaxy_layout.route_names[g].map_z_bits = 0;
    }

    for (int galaxy_index = 0; galaxy_index < kProGalaxyCount; ++galaxy_index) {
        char marker[64];
        sprintf(marker, "Galaxy%i:", galaxy_index);
        char* cursor = Rstrfind(marker, file_text);
        if (!cursor)
            break;
        cursor = Rstrfind((char*)":", cursor) + 1;
        while (*cursor == ' ' || *cursor == '\t')
            ++cursor;
        if (*cursor != '"')
            break;
        ++cursor;
        char* name_out = g_pro_galaxy_layout.route_names[galaxy_index].name;
        while (*cursor && *cursor != '"')
            *name_out++ = *cursor++;
        *name_out = 0;

        cursor = Rstrfind((char*)"StarNumber=", cursor);
        if (!cursor)
            break;
        cursor = Rstrfind((char*)"=", cursor) + 1;
        int star_count = Rstrint(&cursor);
        g_pro_galaxy_layout.route_names[galaxy_index].star_count = star_count;
        g_pro_galaxy_layout.route_names[galaxy_index].color.store_color4f(1.0f, 1.0f, 1.0f, 0.800000012f);

        for (int s = 0; s < star_count && g_pro_galaxy_layout.record_count < kProRouteSlotCount; ++s) {
            int slot = g_pro_galaxy_layout.record_count;
            g_pro_galaxy_layout.route_slots[slot].record.route_name_index = galaxy_index;
            g_pro_galaxy_layout.route_slots[slot].record.map_x =
                scale_galaxy_x(kProRoutePoints[slot].x);
            g_pro_galaxy_layout.route_slots[slot].record.map_y =
                scale_galaxy_y(kProRoutePoints[slot].y);
            g_pro_galaxy_layout.route_slots[slot].record.map_z_bits = 0;
            ++g_pro_galaxy_layout.record_count;
        }
    }

    g_pro_galaxy_layout.route_slots[0].record.route_name_index = 0;
    g_pro_galaxy_layout.route_slots[0].record.map_x = scale_galaxy_x(kProRoutePoints[0].x);
    g_pro_galaxy_layout.route_slots[0].record.map_y = scale_galaxy_y(kProRoutePoints[0].y);
    g_pro_galaxy_layout.route_slots[0].record.map_z_bits = 0;
    g_pro_galaxy_layout.route_slots[0].record.detail_text[0] = 0;
    g_pro_galaxy_layout.route_slots[0].record.description_text[0] = 0;

    // Populate detail_text and description_text for ArcadePro000..010.txt.
    g_game->subgame.galaxy = g_pro_galaxy_layout;
    for (int i = 0; i < kProRouteSlotCount; ++i) {
        char level_name[64];
        sprintf(level_name, "ArcadePro%03i.txt", i);
        g_game->subgame.level_definition_scratch.Init(level_name);
    }
    g_pro_galaxy_layout = g_game->subgame.galaxy;
    g_pro_galaxy_layout.active = 1;
    g_game->subgame.galaxy = g_postal_galaxy_layout;
}

}  // namespace

void extras_init_pro()
{
    if (!g_port_ultimate || g_pro_initialized || !g_game)
        return;

    g_pro_initialized = true;

    g_normal_level_select_tex = g_sprite_texture_table[150];
    g_normal_border_tex = g_sprite_texture_table[152];
    g_normal_line_tex = g_sprite_texture_table[153];
    g_pro_level_select_tex = g_texture_refs.Add((char*)"Galaxy/LevelSelectPro.tga", 0, 0x400);
    g_pro_border_tex = g_texture_refs.Add((char*)"Galaxy/BorderSpacemapPro.tga", 0, 0x400);
    g_pro_line_tex = g_texture_refs.Add((char*)"Galaxy/LinePro.tga", 0, 0x400);

    import_pro_landscape((char*)"StarMapPro.txt", 500);
    import_pro_landscape((char*)"SplashPro.txt", 502);
    import_pro_landscape((char*)"SpacePro.txt", 504);
    import_pro_landscape((char*)"SpacePro2.txt", 506);
    g_postal_galaxy_layout = g_game->subgame.galaxy;
    build_pro_galaxy_layout();

    // Initialize default Pro high score table and load ScorePro.dat if present.
    memcpy(
        g_postal_records_backup,
        g_game->subgame.sub_high_score.postal_records,
        sizeof(g_postal_records_backup));
    for (int i = 0; i < SUB_HIGH_SCORE_TOP_TEN_STORAGE_COUNT; ++i)
        g_game->subgame.sub_high_score.postal_records[i].ReSet(0, 0, 0x3f800000, 0, 0, i);
    g_game->subgame.sub_high_score.load_high_scores_from_file((char*)"ScorePro.dat");
    memcpy(
        g_pro_records,
        g_game->subgame.sub_high_score.postal_records,
        sizeof(g_pro_records));
    memcpy(
        g_game->subgame.sub_high_score.postal_records,
        g_postal_records_backup,
        sizeof(g_postal_records_backup));

    load_pro_progress_file();
}

bool extras_is_pro_mode()
{
    return g_port_ultimate && g_pro_mode_active;
}

void extras_set_pro_mode(bool active)
{
    if (!g_port_ultimate || !g_pro_initialized)
        return;
    g_pro_mode_active = active;
    if (active) {
        g_high_score_pro_view = false;
        swap_in_pro_state();
    } else if (!g_high_score_pro_view) {
        swap_out_pro_state();
    }
}

// Android cRIntro::Init (000674f8): adds "Pro-Challenge" between Postal
// Adventure and Time Trial.
void cRIntro::Init()
{
    if (g_port_ultimate && g_pro_initialized) {
        g_high_score_pro_view = false;
        extras_set_pro_mode(false);
    }
    intro_init_recovered(this);
    g_pro_challenge_button = 0;
    if (!g_port_ultimate || !g_pro_initialized)
        return;

    tColour color;
    g_pro_challenge_button = g_game->border_manager.GetBorder();
    g_pro_challenge_button->Init(
        FRONTEND_WIDGET_FLAG_FADE_BEFORE_ACTION
            | FRONTEND_WIDGET_FLAG_HOVER_HIGHLIGHT_ENABLED
            | FRONTEND_WIDGET_FLAG_PRIMARY_INPUT_ENABLED,
        (char*)"Pro-Challenge",
        0x14,
        20.0f,
        20.0f,
        color.Set(1.0f, 1.0f, 1.0f, 1.0f),
        2,
        0.0f);
    g_pro_challenge_button->SetBelow(postal_button);
    time_trial_button->SetBelow(g_pro_challenge_button);
    challenge_button->SetBelow(time_trial_button);

    // Keep navigation separate from the five game modes. The PC Help anchor
    // puts this stack inside the lower-left frame, clear of Challenge Mode.
    help_button->layout_anchor_y = 300.0f;
    help_button->RePosition();
    back_button->layout_center_x = help_button->layout_center_x;
    back_button->stack_gap = 16.0f;
    back_button->SetBelow(help_button);

    if (g_runtime_config.new_game_tutorial_started == 0)
        g_pro_challenge_button->widget_flags |= FRONTEND_WIDGET_FLAG_DISABLED;
}

// Android cRIntro::AI (00067ab8): dispatches Pro-Challenge into Pro galaxy mode.
void cRIntro::AI()
{
    if (g_port_ultimate && g_pro_challenge_button) {
        if (hide_for_replay_latch == 1
            && (read_pressed_text_input_key_code() != 0
                || (g_game->players[0].game_input->input.pressed_buttons & INPUT_BUTTON_PRIMARY) != 0)) {
            g_pro_challenge_button->UnHideInit();
        }
        unsigned int flags = g_pro_challenge_button->widget_flags;
        if ((flags & FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED) != 0) {
            g_pro_challenge_button->widget_flags =
                flags & ~FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED;
            UnInit();
            extras_set_pro_mode(true);
            g_game->players[0].frontend_state = 10;
            g_game->players[0].redispatch_requested = 1;
            g_game->subgame.level_mode = 0;
            g_game->subgame.subgame_rebuild_selector = 2;
            return;
        }
    }
    intro_ai_recovered(this);
}

// Android cRGalaxy::Init (0005a21c) and Init2 (00059830).
void cRGalaxy::Init()
{
    galaxy_init_recovered(this);
    if (!g_port_ultimate || !g_pro_mode_active)
        return;
    if (g_runtime_config.highest_galaxy_route_index >= 1
        && g_runtime_config.highest_galaxy_route_index <= kProMaxRouteIndex) {
        g_pro_highest_route_index = g_runtime_config.highest_galaxy_route_index;
    }
    if (selected_index >= 1 && selected_index <= g_pro_highest_route_index) {
        g_pro_selected_route_index = selected_index;
        g_runtime_config.landscape_backdrop_variant_selector = selected_index;
    }
    save_pro_progress_file();

    int landscape_index = g_game->subgame.landscape_manager.Import((char*)"StarMapPro.txt");
    g_game->backdrop.Change(&g_game->subgame.landscape_manager.scripts[landscape_index], 0);
}

void cRSubTracks::load_frontend_level_by_mode_and_index(int mode, int level_index)
{
    if (g_port_ultimate && g_pro_mode_active && mode == 0) {
        if (level_index >= 1 && level_index <= g_pro_highest_route_index) {
            g_pro_selected_route_index = level_index;
            save_pro_progress_file();
        }
        char path[128];
        sprintf(path, "ArcadePro%03i.txt", level_index);
        Init(path);
        return;
    }
    load_frontend_level_recovered(this, mode, level_index);
}

// Android cRSubGame::CalcRate (0006daf0): all modes use mobile pacing
// while extras is enabled; classic mode delegates without adjustment.
void cRSubGame::CalcRate()
{
    if (!g_port_ultimate) {
        calc_rate_recovered(this);
        return;
    }
    if (subgame_state != 2) {
        subgame_rate = base_rate;
        return;
    }
    float fraction = player.transform.position.z / (float)completion_row_start;
    if (fraction < 0.0f) fraction = 0.0f;
    else if (fraction > 1.0f) fraction = 1.0f;
    subgame_rate = base_rate + fraction * ((level_mode == 1 || level_mode == 3) ? 0.3f : 0.2f);
    if (player.damage_gauge.state == DAMAGE_GUAGE_STATE_DRAINING) {
        float bonus = (level_mode == 1 || level_mode == 4) ? 0.3f : 0.4f;
        float fill = player.damage_gauge.display_fill;
        if (fill < 0.25f || fill > 0.75f)
            bonus *= (1.0f - Sin(fill * 12.566371f + 1.57079637f)) * 0.5f;
        subgame_rate += bonus;
    }
    if (player.sub_hover.state == SUB_HOVER_STATE_ACTIVE)
        subgame_rate += player.sub_hover.warning_intensity_latch * 0.5f;
}

void cRSplash::Init()
{
    splash_init_recovered(this);
    if (!g_port_ultimate || !g_pro_mode_active)
        return;
    int script_index = g_game->subgame.landscape_manager.Import((char*)"SplashPro.txt");
    g_game->backdrop.Change(&g_game->subgame.landscape_manager.scripts[script_index], 0);
}

void cRHighScore::Init(int mode_, int rank)
{
    if (!g_port_ultimate || !g_pro_initialized) {
        high_score_init_recovered(this, mode_, rank);
        return;
    }

    if (rank != -1) {
        // Entering a new high score name after a run: if g_pro_mode_active is true,
        // swap_in_pro_state() is already active so bank 0 is Pro High Scores.
        g_high_score_pro_view = false;
        high_score_init_recovered(this, mode_, rank);
        return;
    }

    if (g_high_score_pro_view) {
        swap_in_pro_state();
        high_score_init_recovered(this, 0, -1);
        if (title_widget) {
            Rstrcpy(title_widget->text_buffer, (char*)"Pro High Scores");
            title_widget->RePosition();
        }
        if (bank_toggle_button) {
            Rstrcpy(bank_toggle_button->text_buffer, (char*)"Postal Scores");
            bank_toggle_button->RePosition();
        }
        return;
    }

    if (!g_pro_mode_active)
        swap_out_pro_state();
    high_score_init_recovered(this, mode_, rank);
    if (mode_ == 1 && bank_toggle_button) {
        Rstrcpy(bank_toggle_button->text_buffer, (char*)"Pro Scores");
        bank_toggle_button->RePosition();
    }
}

void cRHighScore::AI()
{
    if (!g_port_ultimate || !g_pro_initialized || entering_name != 0) {
        high_score_ai_recovered(this);
        return;
    }

    if (bank_toggle_button
        && (bank_toggle_button->widget_flags & FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED) != 0) {
        bank_toggle_button->widget_flags &= ~FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED;
        UnInit();
        if (!g_high_score_pro_view && selected_bank == 0) {
            selected_bank = 1;
            g_runtime_config.high_score_selected_bank = 1;
            Init(1, -1);
        } else if (!g_high_score_pro_view && selected_bank == 1) {
            g_high_score_pro_view = true;
            selected_bank = 0;
            g_runtime_config.high_score_selected_bank = 0;
            Init(0, -1);
        } else {
            g_high_score_pro_view = false;
            swap_out_pro_state();
            selected_bank = 0;
            g_runtime_config.high_score_selected_bank = 0;
            Init(0, -1);
        }
        return;
    }

    if (back_button
        && (back_button->widget_flags & FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED) != 0) {
        g_high_score_pro_view = false;
        if (!g_pro_mode_active)
            swap_out_pro_state();
    }

    // If launching a replay from the Pro High Scores view, enable g_pro_mode_active
    // so load_frontend_level_by_mode_and_index loads ArcadePro%03i.txt.
    bool was_pro_view = g_high_score_pro_view;
    high_score_ai_recovered(this);
    if (was_pro_view && g_game->subgame.replay_launch_active == 1)
        g_pro_mode_active = true;
}

void cRSubHighScore::MiniSave(unsigned char save_mask)
{
    if (!g_port_ultimate || !g_pro_initialized) {
        mini_save_recovered(this, save_mask);
        return;
    }

    bool was_swapped = g_pro_state_swapped;
    if (was_swapped)
        swap_out_pro_state();

    mini_save_recovered(this, save_mask);

    if ((save_mask & 1) != 0 || (save_mask & 16) != 0) {
        save_pro_high_scores_file();
        save_pro_progress_file();
    }

    if (was_swapped)
        swap_in_pro_state();
}

char* __cdecl save_config_file(char* file_name, void* bytes, int byte_count)
{
    file_name = (char*)extras_save_path(file_name);
    if (g_port_ultimate && g_pro_initialized && g_pro_state_swapped && bytes == &g_runtime_config) {
        if (g_runtime_config.highest_galaxy_route_index >= 1
            && g_runtime_config.highest_galaxy_route_index <= kProMaxRouteIndex) {
            g_pro_highest_route_index = g_runtime_config.highest_galaxy_route_index;
        }
        if (g_runtime_config.landscape_backdrop_variant_selector >= 1
            && g_runtime_config.landscape_backdrop_variant_selector <= g_pro_highest_route_index) {
            g_pro_selected_route_index = g_runtime_config.landscape_backdrop_variant_selector;
        }
        save_pro_progress_file();

        int pro_high = g_runtime_config.highest_galaxy_route_index;
        int pro_sel = g_runtime_config.landscape_backdrop_variant_selector;
        g_runtime_config.highest_galaxy_route_index = g_saved_postal_highest_route;
        g_runtime_config.landscape_backdrop_variant_selector = g_saved_postal_selected_route;
        char* res = save_config_file_recovered(file_name, bytes, byte_count);
        g_runtime_config.highest_galaxy_route_index = pro_high;
        g_runtime_config.landscape_backdrop_variant_selector = pro_sel;
        return res;
    }
    return save_config_file_recovered(file_name, bytes, byte_count);
}

extern "C" void border_init_text_recovered(
    cRBorder* self, int flags, char* text, int font, float x, float y, tColour* color, int mode, float offset)
    __asm__("_ZN8cRBorder14Init_recoveredEiPciffP7tColourif");
extern "C" void border_init_text_recovered(
    cRBorder* self, int flags, char* text, int font, float x, float y, tColour* color, int mode, float offset)
{
    self->Init(flags, text, font, x, y, color, mode, offset);
}

extern "C" void border_init_sprite_recovered(
    cRBorder* self, int flags, int sprite_id, float x, float y, tColour* color, float scale, int mode)
    __asm__("_ZN8cRBorder14Init_recoveredEiiffP7tColourfi");
extern "C" void border_init_sprite_recovered(
    cRBorder* self, int flags, int sprite_id, float x, float y, tColour* color, float scale, int mode)
{
    self->Init(flags, sprite_id, x, y, color, scale, mode);
}

__attribute__((export_name("snail_sprite_texture_name")))
const char* extras_sprite_texture_name(int slot)
{
    if (slot < 0 || slot >= SPRITE_TEXTURE_CAPACITY || !g_sprite_texture_table[slot])
        return "";
    return g_sprite_texture_table[slot]->name;
}
