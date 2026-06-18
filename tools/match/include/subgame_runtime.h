// Root subgame runtime view, partial. This intentionally stays sparse: fields
// are added only when an exact helper or cross-function caller proves them.
#ifndef SUBGAME_RUNTIME_H
#define SUBGAME_RUNTIME_H

#include "track_parcel_runtime.h"

class Player;
struct SelectedLevelRecord;
struct TrackRowCell;

class SubgameRuntime {
public:
    int set_subgame_features(); // @ 0x435df0
    bool switch_track_mirror(); // @ 0x435e60
    void populate_runtime_track_cells_from_segments(); // @ 0x435eb0
    int rebuild_track_runtime_from_segments(int level_index); // @ 0x437de0
    TrackRowCell* spawn_track_ring_or_special_effect(
        TrackRowCell* cell, int requested_kind, Player* player, float ring_speed); // @ 0x43df10
    void set_subgame_rate(float rate); // @ 0x4404c0
    void calc_subgame_rate(); // @ 0x4404d0
    Color4f* get_track_skirt_color(Color4f* out); // @ 0x442120
    TrackParcelRuntime* spawn_track_parcel(
        Vector3* world_position,
        void* owner_hint); // @ 0x443730
    TrackRowCell* get_track_grid_cell_at_world_position(Vector3* position);
    float sample_track_floor_height_at_position(Vector3* position);
    void complete_subgame(int completed);
    void build_track_colours();
    void place_parcels_on_track();
    void select_track_tile_edge_variants();
    void promote_track_tiles_to_fringe_variants();
    void harmonize_center_lane_floor_slide_variants();
    void merge_track_tile_runs();
    void mark_track_warning_zones();
    void build_track_fringe_objects();

    char unknown_000000[0x02];
    bool track_mirror_enabled; // +0x02
    char unknown_000003;
    int track_mirror_repeat_count; // +0x04
    char unknown_000008;
    unsigned char subgame_pause_gate; // +0x09
    char unknown_00000a[0x30 - 0x0a];
    float base_rate; // +0x30, set by set_subgame_rate and used by calc_subgame_rate
    float challenge_difficulty_scalar; // +0x34
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
    char unknown_1b014c[0x3bb764 - 0x1b014c];
    char score_stats; // +0x3bb764, owner anchor used by parcels
    char unknown_3bb765[0x3bb7d4 - 0x3bb765];
    float completion_progress_z; // +0x3bb7d4
    char unknown_3bb7d8[0x3bbae4 - 0x3bb7d8];
    int parcel_sprite_owner; // +0x3bbae4
    char unknown_3bbae8[0x3bbb28 - 0x3bbae8];
    int bonus_rate_state; // +0x3bbb28
    char unknown_3bbb2c[0x3bbb48 - 0x3bbb2c];
    float bonus_rate_phase; // +0x3bbb48
    char unknown_3bbb4c[0x3bdec0 - 0x3bbb4c];
    int nuke_rate_state; // +0x3bdec0
    char unknown_3bdec4[0x3be0c0 - 0x3bdec4];
    float nuke_rate_progress; // +0x3be0c0
    char unknown_3be0c4[0xff25d0 - 0x3be0c4];
    unsigned char selected_level_record_active; // +0xff25d0
    unsigned char selected_level_record_persistent; // +0xff25d1
    char unknown_ff25d2[0xff25d4 - 0xff25d2];
    SelectedLevelRecord* selected_level_record; // +0xff25d4
    int selected_level_record_cursor; // +0xff25d8, replay/update cursor window
    int replay_update_cursor; // +0xff25dc
    char unknown_ff25e0[0x125e480 - 0xff25e0];
    TrackParcelPool parcel_pool; // +0x125e480
};

#endif
