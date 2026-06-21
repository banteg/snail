// Root subgame runtime view, partial. iOS symbols name this embedded owner
// cRSubGame; the surrounding Windows root object remains the larger Game view.
// This intentionally stays sparse: fields are added only when an exact helper
// or cross-function caller proves them.
#ifndef SUBGAME_RUNTIME_H
#define SUBGAME_RUNTIME_H

#include "frontend_widget.h"
#include "garbage_hazard_slot.h"
#include "high_score_bank.h"
#include "high_score_record.h"
#include "cameraman_state.h"
#include "contact_target.h"
#include "score_stats.h"
#include "track_health_pickup.h"
#include "track_jetpack_pickup.h"
#include "track_parcel_runtime.h"
#include "track_row_cell_tile_views.h"
#include "track_speedup.h"

class Player;
struct TrackAttachmentRuntimeRow;
struct TrackRowCell;

class SubgameRuntime {
public:
    int set_subgame_features(); // @ 0x435df0
    bool switch_track_mirror(); // @ 0x435e60
    void populate_runtime_track_cells_from_segments(); // @ 0x435eb0
    void reset_subgame(); // @ 0x437b10
    int rebuild_track_runtime_from_segments(int level_index); // @ 0x437de0
    void destroy_subgame(); // @ 0x438850
    unsigned int* spawn_track_health_pickup(
        TrackRowCell* cell, Player* player); // @ 0x43d6c0
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

    char unknown_000000[0x01];
    unsigned char camera_snap_requested; // +0x01, transient camera source switch flag
    bool track_mirror_enabled; // +0x02
    char unknown_000003;
    int track_mirror_repeat_count; // +0x04
    char unknown_000008;
    unsigned char subgame_pause_gate; // +0x09
    char unknown_00000a[0x28 - 0x0a];
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
    char unknown_1b014c[0x355bd4 - 0x1b014c];
    char sub_lazer_list_head[0x10]; // +0x355bd4, node-shaped live-list anchor
    char unknown_355be4[0x355db0 - 0x355be4];
    TrackSpeedupRuntime speedup_pickup; // +0x355db0
    TrackJetpackPickup jetpack_pickup; // +0x355e64
    TrackHealthPickup health_pickups[8]; // +0x356000
    char unknown_3563a0[0x359140 - 0x3563a0];
    GarbageHazardPool garbage_hazards; // +0x359140
    char unknown_35b78c[0x35bb88 - 0x35b78c];
    FrontendWidget* score_widget_a; // +0x35bb88
    FrontendWidget* score_widget_b; // +0x35bb8c
    FrontendWidget* lives_icon_widget; // +0x35bb90
    FrontendWidget* lives_text_widget; // +0x35bb94
    FrontendWidget* life_stock_widgets[9]; // +0x35bb98
    char unknown_35bbbc[0x3bb764 - 0x35bbbc];
    char score_stats; // +0x3bb764, owner anchor used by parcels
    char unknown_3bb765[0x3bb7d4 - 0x3bb765];
    union {
        float completion_progress_z; // +0x3bb7d4
        float salt_fade_start_z; // +0x3bb7d4
    };
    char unknown_3bb7d8[0x3bb964 - 0x3bb7d8];
    CameramanState cameraman; // +0x3bb964
    char unknown_3bba3c[0x3bba48 - 0x3bba3c];
    int source_score; // +0x3bba48
    ScoreBucketBlock source_stats; // +0x3bba4c
    int source_score_tail; // +0x3bba64
    int source_tail; // +0x3bba68
    char unknown_3bba6c[0x3bbae4 - 0x3bba6c];
    int parcel_sprite_owner; // +0x3bbae4
    char unknown_3bbae8[0x3bbb28 - 0x3bbae8];
    int bonus_rate_state; // +0x3bbb28
    char unknown_3bbb2c[0x3bbb48 - 0x3bbb2c];
    float bonus_rate_phase; // +0x3bbb48
    char unknown_3bbb4c[0x3bbb7c - 0x3bbb4c];
    float slug_explosion_base_z; // +0x3bbb7c
    char unknown_3bbb80[0x3bbba4 - 0x3bbb80];
    unsigned char time_trial_route_active; // +0x3bbba4
    char unknown_3bbba5[0x3bdec0 - 0x3bbba5];
    int nuke_rate_state; // +0x3bdec0
    char unknown_3bdec4[0x3be0c0 - 0x3bdec4];
    float nuke_rate_progress; // +0x3be0c0
    char unknown_3be0c4[0x3be0e4 - 0x3be0c4];
    float subgame_kill_plane_z; // +0x3be0e4, shared cull/live-window boundary
    char unknown_3be0e8[0x3bfa4c - 0x3be0e8];
    int override_camera_active; // +0x3bfa4c
    TransformMatrix override_camera_matrix; // +0x3bfa50
    char unknown_3bfa90[0x3bfa98 - 0x3bfa90];
    unsigned char override_camera_snap; // +0x3bfa98
    char unknown_3bfa99[0x3bfb04 - 0x3bfa99];
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
    char unknown_125ffe0[0x1270fc8 - 0x125ffe0];
    int subgame_rebuild_selector; // +0x1270fc8
    char unknown_1270fcc[0x1270fd4 - 0x1270fcc];
    ContactTargetRegistry contact_targets; // +0x1270fd4, per-frame target append window
};

#endif
