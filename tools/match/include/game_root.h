// Shared root-level game owner view.
#ifndef GAME_ROOT_H
#define GAME_ROOT_H

#include "backdrop.h"
#include "bod_list.h"
#include "border_manager.h"
#include "exit.h"
#include "directx_loader.h"
#include "frontend_fade.h"
#include "frontend_overlay_color_lerp.h"
#include "high_score.h"
#include "input_state.h"
#include "intro_screen_runtime.h"
#include "main_menu.h"
#include "mouse_cursor_state.h"
#include "new_game_menu.h"
#include "overlay.h"
#include "options.h"
#include "render_camera_slot.h"
#include "root_bod_catalog.h"
#include "sprite.h"
#include "star_manager.h"
#include "subgame_runtime.h"
#include "texture_set_selector.h"
#include "tip_manager.h"
#include "vector3.h"

enum {
    GAME_ROOT_BOD_COUNT = ROOT_BOD_CATALOG_ENTRY_COUNT,
    GAME_ROOT_PLAYER_SLOT_COUNT = 2,
};

// Windows cRPlayer owns the front-end state machine and an embedded cRCamera.
// GameRoot constructs two consecutive 0x1f8-byte players at +0x124; viewport
// slots only borrow their camera subobjects at player +0xa0.
class GamePlayer : public RenderableBod {
public:
    GamePlayer* initialize_game_player(); // @ 0x408000, cRPlayer constructor helper
    void update_frontend_state_machine(); // @ 0x4107d0, cRPlayer::AI()

    char player_name[SUB_SOLUTION_PLAYER_NAME_SIZE]; // +0x80
    int frontend_state; // +0x94
    int saved_frontend_state; // +0x98
    char unknown_09c[0xa0 - 0x9c];
    RenderCamera camera; // +0xa0, owned cRCamera subobject
    GameInput* game_input; // +0x168, borrows the matching root input owner
    MouseCursorState mouse_cursor; // +0x16c, root player 0 cursor state
    FrontendOverlayColorLerp frontend_overlay; // +0x184, root player 0 overlay
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
    FrontendFade fade; // +0x24, root-owned transition controller
    union {
        int frontend_quit_requested; // +0x38, nonzero run-loop exit request
        int frontend_quit_mode; // exit prompt writes modes 1 and 3
    };
    int fixed_update_count;      // +0x3c
    int player_count; // +0x40, controls the two-player initialization loop
    GameInput game_inputs[GAME_ROOT_PLAYER_SLOT_COUNT]; // +0x44, paired input owners
    GamePlayer players[GAME_ROOT_PLAYER_SLOT_COUNT]; // +0x124, owned cRPlayer array
    int unknown_000514; // +0x514, startup-only dword storage
    float fixed_update_accumulator; // +0x518, consumed in unit fixed steps
    int frame_counter; // +0x51c, creation timestamp for front-end borders
    unsigned char input_sampling_gate; // +0x520, live input sampled on first step
    char unknown_000521[0x568 - 0x521];
    unsigned char frontend_link_latch; // +0x568, cleared when a linked screen exits
    char unknown_000569[0x56c - 0x569];
    union {
        int render_skip_count; // +0x56c, decremented before an otherwise skipped frame
        int render_skip_countdown; // front-end initialization spelling
    };
    BodBase inactive_bod_sentinel; // +0x570, constructed root free-list sentinel
    BodList active_bod_list; // +0x5a8, root-owned active/free intrusive BOD anchor
    RenderCameraSlot render_camera_slots[5]; // +0x5b4, owned fixed viewport array
    Overlay overlay_0; // +0x67c, lends camera at +0x6fc to viewport slot 0
    Overlay overlay_1; // +0x7c8, lends camera at +0x848 to viewport slot 2
    Overlay overlay_2; // +0x914, lends camera at +0x994 to viewport slot 3
    char unknown_000a60[0xb24 - 0xa60];
    TextureSetSelector texture_set_selector; // +0xb24, four track/slide pairs
    int unknown_000b48; // +0xb48, startup-only dword storage
    // Exact cRBorder manager: the 150-record pool is followed by its delayed
    // transition lane and center-justify scalar, ending at the root BOD bank.
    BorderManager border_manager; // +0xb4c, ends exactly at +0x44100
    RootBodCatalog root_bod_catalog; // +0x44100, fixed 352-entry cRBod bank
    DirectXLoader directx_loader; // +0x48e00, owns 128 cached X-mesh slots
    Backdrop backdrop; // +0x4ec10, owned cRBackdrop-compatible renderer
    // Contiguous front-end owner block. The exact component extents prove
    // every boundary through the exit prompt without padding.
    Intro intro; // +0x4f2dc, exact Windows cRIntro owner
    MainMenu main_menu; // +0x4f324
    StarManager star_manager; // +0x4f33c, exact authored cRStarManager owner
    Options options; // +0x4f388, exact authored cROptions owner
    Exit exit_controller; // +0x4f3ac, exact authored cRExit owner
    BodBase root_bod_4f3c8; // +0x4f3c8, concrete role not yet established
    Logo logo; // +0x4f400, exact cRLogo owner with both 0x90-byte banks
    SubgameRuntime subgame; // +0x74618, owned cRSubGame runtime
    HighScore high_score; // +0x12e6e50, known cRHighScore storage through +0x12e6f44
    char unknown_12e6f44[0x12e6f58 - 0x12e6f44];
    TipManager tip_manager; // +0x12e6f58, owned root tutorial-message manager
    char unknown_12e6ff0[0x12e6ff4 - 0x12e6ff0];

    int run_frame_update();          // @ 0x40a2a0
    char initialize_game_assets_and_world(); // @ 0x40acf0
    void initialize_game_last();     // @ 0x410720
    void render_game_frame();        // @ 0x40a490, iOS cRGame::Render()
    TrackFringeBodCatalog* track_fringe_bod_catalog();
};

typedef char GameRoot_must_be_0x12e6ff4[
    (sizeof(GameRoot) == 0x12e6ff4) ? 1 : -1];

inline TrackFringeBodCatalog* GameRoot::track_fringe_bod_catalog()
{
    // The asset constructor proves entries 58..345 of the root BOD bank are
    // the complete 8x4x3x3 track-fringe catalog.
    return &root_bod_catalog.fringe_catalog;
}

#endif
