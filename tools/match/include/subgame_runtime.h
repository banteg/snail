// Root subgame runtime view, partial. iOS symbols name this embedded owner
// cRSubGame; the surrounding Windows root object remains the larger Game view.
// This intentionally stays sparse: fields are added only when an exact helper
// or cross-function caller proves them.
#ifndef SUBGAME_RUNTIME_H
#define SUBGAME_RUNTIME_H

#include "challenge_setup_screen.h"
#include "completion_screen.h"
#include "frontend_widget.h"
#include "garbage_hazard_slot.h"
#include "galaxy_route_types.h"
#include "high_score_bank.h"
#include "high_score_record.h"
#include "cameraman_state.h"
#include "contact_target.h"
#include "player.h"
#include "ring_special_effect_types.h"
#include "score_stats.h"
#include "track_health_pickup.h"
#include "track_jetpack_pickup.h"
#include "track_parcel_runtime.h"
#include "track_row_cell_tile_views.h"
#include "track_speedup.h"

struct TrackAttachmentRuntimeRow;
struct TrackRowCell;
class TimeTrialStringFormatter;

class SubgameRuntime {
public:
    int set_subgame_features(); // @ 0x435df0
    bool switch_track_mirror(); // @ 0x435e60
    void populate_runtime_track_cells_from_segments(); // @ 0x435eb0
    void initialize_subgame(); // @ 0x4374b0
    void reset_subgame(); // @ 0x437b10
    int rebuild_track_runtime_from_segments(int level_index); // @ 0x437de0
    float calc_slider_to_rate(float slider); // @ 0x437e80, receiver unused by body
    void build_subgame_level(int level_index); // @ 0x437eb0
    Player* embedded_player(); // typed view of owned player_storage at +0x3bb764
    TrackRowCellFringeLinkView* runtime_cell_fringe_links(); // +0x3bfb0c field-first view
    TimeTrialStringFormatter* time_trial_formatter(); // embedded service view at +0xff25e0
    void update_subgame(); // @ 0x438b90
    void destroy_subgame(); // @ 0x438850
    unsigned int* spawn_track_health_pickup(
        TrackRowCell* cell, Player* player); // @ 0x43d6c0
    int spawn_track_speedup(TrackRowCell* cell, Player* player); // @ 0x43d880, receiver unused by body
    int spawn_track_jetpack_pickup(TrackRowCell* cell, Player* player); // @ 0x43d890
    unsigned int* spawn_track_garbage_hazard(TrackRowCell* cell, Player* player); // @ 0x43da80
    int spawn_slug_hazard(TrackRowCell* cell, Player* player); // @ 0x43dc80
    TrackRowCell* spawn_track_ring_or_special_effect(
        TrackRowCell* cell, int requested_kind, Player* player, float ring_speed); // @ 0x43df10
    void set_subgame_rate(float rate); // @ 0x4404c0
    void calc_subgame_rate(); // @ 0x4404d0
    void remove_subgame_bods(); // @ 0x440910
    void hide_gameplay_scores(); // @ 0x445f10
    void unhide_gameplay_scores(); // @ 0x445f40
    void update_subgame_camera(); // @ 0x446020
    Color4f* get_track_skirt_color(Color4f* out); // @ 0x442120
    TrackParcelRuntime* spawn_track_parcel(
        Vector3* world_position,
        void* owner_hint); // @ 0x443730
    TrackRowCell* get_track_grid_cell_at_world_position(Vector3* position);
    TrackAttachmentRuntimeRow* get_track_runtime_cell_at_world_z(Vector3* position);
    double sample_track_floor_height_at_position(Vector3* position);
    char* project_position_onto_track_attachment(Vector3* position, float* out_angle);
    void complete_subgame(unsigned char completed);
    void build_track_colours();
    int place_parcels_on_track();
    int place_challenge_parcels_on_track();
    void select_track_tile_edge_variants();
    void promote_track_tiles_to_fringe_variants();
    void harmonize_center_lane_floor_slide_variants();
    void merge_track_tile_runs();
    void mark_track_warning_zones();
    int build_track_fringe_objects();
    bool is_neighbor_cell_solid(TrackRowCell* cell, int dx, int dz);
    char normalize_segment_glyph_for_track_flags(char glyph, int row, char edge_row);

    unsigned char scan_reset; // +0x00, row scanner start-window reset
    unsigned char camera_snap_requested; // +0x01, transient camera source switch flag
    bool track_mirror_enabled; // +0x02
    char unknown_000003;
    int track_mirror_repeat_count; // +0x04
    unsigned char resume_requested; // +0x08, pause-menu resume handoff
    unsigned char subgame_pause_gate; // +0x09
    char unknown_00000a[0x0c - 0x0a];
    float pause_fade; // +0x0c
    float pause_fade_step; // +0x10
    PauseMenu pause_menu; // +0x14
    char unknown_000020[0x28 - 0x20];
    int completion_bonus_x_source; // +0x28, raw result snapshot lane
    int completion_bonus_y_source; // +0x2c, raw result snapshot lane
    union {
        float base_rate; // +0x30, set by set_subgame_rate and used by calc_subgame_rate
        int level_arg_tail; // +0x30, raw result snapshot lane
    };
    union {
        float challenge_difficulty_scalar; // +0x34
        int difficulty_scalar_bits; // +0x34, raw result snapshot lane
    };
    float subgame_rate; // +0x38
    int subgame_state; // +0x3c
    int level_mode; // +0x40
    int level_mode_arg; // +0x44
    float base_subgame_rate; // +0x48, segment/ring speed scale
    unsigned int runtime_flags; // +0x4c
    int first_block_row_count; // +0x50
    int runtime_row_count; // +0x54
    int completion_row_start; // +0x58
    char unknown_00005c[0xa874 - 0x5c];
    int level_segment_count; // +0xa874
    char unknown_00a878[0x1b0140 - 0xa878];
    float track_skirt_r; // +0x1b0140
    float track_skirt_g; // +0x1b0144
    float track_skirt_b; // +0x1b0148
    char unknown_1b014c[0x1b01e0 - 0x1b014c];
    int parcel_total; // +0x1b01e0
    char unknown_1b01e4[0x355bd4 - 0x1b01e4];
    char sub_lazer_list_head[0x10]; // +0x355bd4, node-shaped live-list anchor
    char unknown_355be4[0x355d94 - 0x355be4];
    int active_level_score; // +0x355d94, copied from the selected bank record
    TimerCounters active_level_timer; // +0x355d98, embedded display snapshot
    TrackSpeedupRuntime speedup_pickup; // +0x355db0
    TrackJetpackPickup jetpack_pickup; // +0x355e64
    TrackHealthPickup health_pickups[8]; // +0x356000
    char unknown_3563a0[0x359140 - 0x3563a0];
    GarbageHazardPool garbage_hazards; // +0x359140
    RingOrSpecialEffectPool ring_effects; // +0x35b78c, two embedded parent slots
    char unknown_35bb7c[0x35bb88 - 0x35bb7c];
    // BorderManager pool handles. SubgameRuntime retains them for gameplay,
    // then destroy_subgame returns each handle through kill_border().
    FrontendWidget* top_score_widget; // +0x35bb88
    FrontendWidget* bottom_score_widget; // +0x35bb8c
    FrontendWidget* lives_icon_widget; // +0x35bb90
    FrontendWidget* lives_text_widget; // +0x35bb94
    FrontendWidget* life_stock_widgets[9]; // +0x35bb98
    char unknown_35bbbc[0x3bb764 - 0x35bbbc];
    union {
        // VC6 rejects non-trivial class members in a union, so preserve the
        // exact Player extent as storage and cast it at typed callsites.
        char player_storage[sizeof(Player)]; // +0x3bb764, ends at +0x3bfac8
        struct {
            char score_stats; // Player +0x000, owner anchor used by parcels
            char unknown_player_001[0x070 - 0x001];
            union {
                float completion_progress_z; // Player.position.z +0x070
                float salt_fade_start_z;      // Player.position.z +0x070
            };
            char unknown_player_074[0x200 - 0x074];
            CameramanState cameraman; // Player.cameraman +0x200
            char unknown_player_2d8[0x2e4 - 0x2d8];
            int source_score; // Player.total_score +0x2e4
            union {
                ScoreBucketBlock source_stats; // Player timer/stat overlay +0x2e8
                TimerCounters source_timer;
            };
            int source_score_tail; // Player +0x300
            int source_tail; // Player.startup_track_index +0x304
            char unknown_player_308[0x380 - 0x308];
            int parcel_sprite_owner; // Player.player_slot +0x380
            char unknown_player_384[0x3c4 - 0x384];
            int bonus_rate_state; // Player.damage_gauge +0x00
            char unknown_player_3c8[0x3e4 - 0x3c8];
            float bonus_rate_phase; // Player.damage_gauge +0x20
            char unknown_player_3e8[0x418 - 0x3e8];
            float slug_explosion_base_z; // Player.velocity.z +0x418
            char unknown_player_41c[0x440 - 0x41c];
            unsigned char time_trial_route_active; // Player.completion_handoff_active +0x440
            char unknown_player_441[0x275c - 0x441];
            int nuke_rate_state; // Player.jetpack_gauge +0x0c
            char unknown_player_2760[0x295c - 0x2760];
            float nuke_rate_progress; // Player +0x295c
            char unknown_player_2960[0x2980 - 0x2960];
            float subgame_kill_plane_z; // Player.interaction_max_z +0x2980
            char unknown_player_2984[0x42e8 - 0x2984];
            int override_camera_active; // Player.presentation +0x1964
            TransformMatrix override_camera_matrix; // Player.presentation +0x1968
            char unknown_player_432c[0x4334 - 0x432c];
            unsigned char override_camera_snap; // Player.presentation +0x19b0
            char unknown_player_4335[0x4364 - 0x4335];
        };
    };
    char unknown_3bfac8[0x3bfb04 - 0x3bfac8];
    TrackRowCellTileByteView runtime_cell_tiles[1]; // +0x3bfb04, row-major tile-byte view
    char unknown_3bfb58[0x68b4c8 - 0x3bfb58];
    HighScoreBank high_score_bank; // +0x68b4c8
    HighScoreRecord current_high_score_record; // +0xfd2b10
    unsigned char selected_level_record_active; // +0xff25d0
    unsigned char selected_level_record_persistent; // +0xff25d1
    char unknown_ff25d2[0xff25d4 - 0xff25d2];
    HighScoreRecord* selected_level_record; // +0xff25d4
    int selected_level_record_cursor; // +0xff25d8, replay/update cursor window
    int replay_update_cursor; // +0xff25dc
    char unknown_ff25e0[0x125e480 - 0xff25e0];
    TrackParcelPool parcel_pool; // +0x125e480
    int source_timer_a; // +0x125ffd8
    int source_timer_b; // +0x125ffdc
    ChallengeSetupScreen challenge_setup; // +0x125ffe0
    char unknown_1260008[0x1260020 - (0x125ffe0 + sizeof(ChallengeSetupScreen))];
    GalaxyRoute galaxy; // +0x1260020, embedded route controller
    char unknown_1270fc4[0x1270fc8 - 0x1270fc4];
    int subgame_rebuild_selector; // +0x1270fc8
    char unknown_1270fcc[0x1270fd4 - 0x1270fcc];
    ContactTargetRegistry contact_targets; // +0x1270fd4, per-frame target append window
};

inline Player* SubgameRuntime::embedded_player()
{
    return (Player*)player_storage;
}

inline TrackRowCellFringeLinkView* SubgameRuntime::runtime_cell_fringe_links()
{
    return (TrackRowCellFringeLinkView*)((char*)this + 0x3bfb0c);
}

inline TimeTrialStringFormatter* SubgameRuntime::time_trial_formatter()
{
    return (TimeTrialStringFormatter*)((char*)this + 0xff25e0);
}

#endif
