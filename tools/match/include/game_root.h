// Shared root-level game owner view.
#ifndef GAME_ROOT_H
#define GAME_ROOT_H

#include "bod_list.h"
#include "border_manager.h"
#include "completion_screen.h"
#include "main_menu.h"
#include "new_game_menu.h"
#include "options_menu.h"
#include "render_camera_slot.h"
#include "sprite.h"
#include "star_field.h"
#include "subgame_runtime.h"
#include "tip_manager.h"
#include "vector3.h"

class GameRootIntroScreen {
public:
    void initialize_intro_screen(char* script_path);
    void update_intro_screen();
};

// Windows cRPlayer owns the front-end state machine and an embedded cRCamera.
// GameRoot constructs two consecutive 0x1f8-byte players at +0x124; viewport
// slots only borrow their camera subobjects at player +0xa0.
class GamePlayer : public RenderableBod {
public:
    GamePlayer* initialize_game_player(); // @ 0x408000, cRPlayer constructor helper
    int update_frontend_state_machine(); // @ 0x4107d0, cRPlayer::AI()

    char unknown_078[0x80 - 0x78];
    char player_name[HIGH_SCORE_RECORD_PLAYER_NAME_SIZE]; // +0x80
    int frontend_state; // +0x94
    int saved_frontend_state; // +0x98
    char unknown_09c[0xa0 - 0x9c];
    RenderCamera camera; // +0xa0, owned cRCamera subobject
    void* camera_anchor; // +0x168, borrowed current menu/gameplay anchor
    char unknown_16c[0x178 - 0x16c];
    float camera_anchor_x; // +0x178
    float camera_anchor_y; // +0x17c
    char unknown_180[0x188 - 0x180];
    Color4f color_188; // +0x188, constructed owned color
    Color4f color_198; // +0x198, constructed owned color
    char unknown_1a8[0x1e8 - 0x1a8];
    unsigned char redispatch_requested; // +0x1e8
    unsigned char high_score_entry_pending; // +0x1e9
    char unknown_1ea[0x1ec - 0x1ea];
    union {
        int selected_high_score_rank; // +0x1ec, frontend selection read
        int high_score_entry_rank; // +0x1ec, pending-entry write
    };
    union {
        int selected_high_score_mode; // +0x1f0, frontend selection read
        int high_score_entry_bank; // +0x1f0, pending-entry write
    };
    char unknown_1f4[0x1f8 - 0x1f4];
};

typedef char GamePlayer_must_be_0x1f8[
    (sizeof(GamePlayer) == 0x1f8) ? 1 : -1];

class GameRoot {
public:
    char unknown_000000[0x04];
    unsigned char fog_enabled; // +0x04
    char unknown_000005[0x08 - 0x05];
    float fog_start; // +0x08, D3DRS_FOGSTART
    float fog_end; // +0x0c, D3DRS_FOGEND
    float fog_density; // +0x10, D3DRS_FOGDENSITY
    Color4f fog_color; // +0x14, packed for D3DRS_FOGCOLOR
    char unknown_000024[0x38 - 0x24];
    union {
        int frontend_quit_requested; // +0x38, nonzero run-loop exit request
        int frontend_quit_mode; // completion prompt writes modes 1 and 3
    };
    int fixed_update_count;      // +0x3c
    char unknown_000040[0x124 - 0x40];
    GamePlayer players[2]; // +0x124, owned cRPlayer array
    char unknown_000514[0x568 - 0x514];
    unsigned char frontend_link_latch; // +0x568, cleared when a linked screen exits
    char unknown_000569[0x56c - 0x569];
    union {
        int render_skip_count; // +0x56c, decremented before an otherwise skipped frame
        int render_skip_countdown; // front-end initialization spelling
    };
    char unknown_000570[0x5a8 - 0x570];
    BodList active_bod_list; // +0x5a8, root-owned active/free intrusive BOD anchor
    RenderCameraSlot render_camera_slots[5]; // +0x5b4, owned fixed viewport array
    char unknown_00067c[0x6d4 - 0x67c];
    Vector3 star_spawn_direction; // +0x6d4
    char unknown_0006e0[0x6e4 - 0x6e0];
    Vector3 star_spawn_origin; // +0x6e4
    char unknown_0006f0[0xb4c - 0x6f0];
    BorderManager border_manager; // +0xb4c, owned frontend border pool
    char unknown_0440e8[0x4f2dc - 0x440e8];
    // Contiguous front-end owner block. The exact component extents prove
    // every boundary through the completion prompt without padding.
    NewGameMenu new_game_menu; // +0x4f2dc
    MainMenu main_menu; // +0x4f324
    StarField star_field; // +0x4f33c
    OptionsMenu options_menu; // +0x4f388
    CompletionPrompt completion_screen; // +0x4f3ac
    char unknown_04f3c8[0x4f400 - 0x4f3c8];
    GameRootIntroScreen intro_screen; // +0x4f400
    char unknown_04f401[0x74618 - 0x4f401];
    SubgameRuntime subgame; // +0x74618, owned cRSubGame runtime
    HighScoreScreen high_score_screen; // +0x12e6e50
    char unknown_12e6f20[0x12e6f58 - 0x12e6f20];
    TipManager tip_manager; // +0x12e6f58, owned root tutorial-message manager
    char unknown_12e6ff0[0x12e6ff4 - 0x12e6ff0];

    int run_frame_update();          // @ 0x40a2a0
    char initialize_game_assets_and_world(); // @ 0x40acf0
    void initialize_game_last();     // @ 0x410720
    int render_game_frame();         // @ 0x40a490
};

typedef char GameRoot_must_be_0x12e6ff4[
    (sizeof(GameRoot) == 0x12e6ff4) ? 1 : -1];

#endif
