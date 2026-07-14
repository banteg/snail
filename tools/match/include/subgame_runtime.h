// Root subgame runtime view, partial. iOS symbols name this embedded owner
// cRSubGame; the surrounding Windows root object remains the larger Game view.
// This intentionally stays sparse: fields are added only when an exact helper
// or cross-function caller proves them.
#ifndef SUBGAME_RUNTIME_H
#define SUBGAME_RUNTIME_H

#include "landscape_manager.h"
#include "banner.h"
#include "barrier_actor.h"
#include "gui.h"
#include "completion.h"
#include "frontend_widget.h"
#include "fringe_object.h"
#include "garbage_hazard_slot.h"
#include "galaxy_route_types.h"
#include "sub_high_score.h"
#include "sub_solution.h"
#include "help.h"
#include "sub_tracks.h"
#include "contact_target.h"
#include "new_game_menu.h"
#include "path_manager.h"
#include "pause_menu.h"
#include "player.h"
#include "ring_special_effect_types.h"
#include "salt_hazard_types.h"
#include "slug_hazard_types.h"
#include "slug_voice_manager.h"
#include "smtracks.h"
#include "sub_lazer_types.h"
#include "time_trial.h"
#include "times_up.h"
#include "thanks_screen.h"
#include "track_health_pickup.h"
#include "track_jetpack_pickup.h"
#include "track_attachment_types.h"
#include "track_parcel_runtime.h"
#include "segment_cache.h"
#include "track_row_cell_tile_views.h"
#include "track_speedup.h"
#include "tutorial.h"

class SubgameRuntime {
public:
    SubgameRuntime* initialize_runtime_pools_and_path_template_bank(); // @ 0x408060
    int set_subgame_features(); // @ 0x435df0
    bool switch_track_mirror(); // @ 0x435e60
    void populate_runtime_track_cells_from_segments(); // @ 0x435eb0
    void initialize_subgame(); // @ 0x4374b0
    void reset_subgame(); // @ 0x437b10
    int rebuild_track_runtime_from_segments(int level_index); // @ 0x437de0
    float calc_slider_to_rate(float slider); // @ 0x437e80, receiver unused by body
    void build_subgame_level(int level_index); // @ 0x437eb0
    Player* embedded_player(); // borrowed pointer to owned player at +0x3bb764
    Vector3* parcel_delivery_arc_basis(); // Player.presentation.transform.basis_up
    Vector3* parcel_home_anchor(); // Player.presentation.snail_hotspots_world[11]
    TrackRowCellTileByteView* runtime_cell_tile_views(); // +0x3bfb04 field-first view
    TrackRowCellFringeLinkView* runtime_cell_fringe_links(); // +0x3bfb0c field-first view
    void update_subgame(); // @ 0x438b90
    void destroy_subgame(); // @ 0x438850
    void spawn_track_health_pickup(
        SubLoc* cell, Player* player); // @ 0x43d6c0
    void spawn_track_speedup(SubLoc* cell, Player* player); // @ 0x43d880, no-op in Windows/Android
    void spawn_track_jetpack_pickup(SubLoc* cell, Player* player); // @ 0x43d890
    void spawn_track_garbage_hazard(SubLoc* cell, Player* player); // @ 0x43da80
    int spawn_slug_hazard(SubLoc* cell, Player* player); // @ 0x43dc80
    void spawn_track_ring_or_special_effect(
        SubLoc* cell, int requested_kind, Player* player, float ring_speed); // @ 0x43df10
    void set_subgame_rate(float rate); // @ 0x4404c0
    void calc_subgame_rate(); // @ 0x4404d0
    double advance_blink_random(); // @ 0x4408a0
    int initialize_blink_random(); // @ 0x4408c0
    void remove_subgame_bods(); // @ 0x440910
    void hide_gameplay_scores(); // @ 0x445f10
    void unhide_gameplay_scores(); // @ 0x445f40
    void update_subgame_camera(); // @ 0x446020
    Color4f* get_track_skirt_color(Color4f* out); // @ 0x442120
    Parcel* spawn_track_parcel(
        Vector3* world_position,
        Player* ignored_player); // @ 0x443730, native binds embedded_player()
    SubLoc* get_track_grid_cell_at_world_position(Vector3* position);
    SubRow* get_track_runtime_cell_at_world_z(Vector3* position);
    double sample_track_floor_height_at_position(Vector3* position);
    void project_position_onto_track_attachment(Vector3* position, float* out_angle);
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
    bool is_neighbor_cell_solid(SubLoc* cell, int dx, int dz); // cRSubGame::TestLoc
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
    int runtime_row_scan_begin; int runtime_row_scan_end; // +0x20/+0x24, rolling row-window [begin, end)
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
    // Owns 143 rows x five render-family BOD slots and their shared staging
    // buffers. Its owner_subgame field is a borrowed backlink to this object.
    SegmentCache segment_cache; // +0x5c, ends at +0xa854
    unsigned char track_state_latch; // +0xa854, row-event / movement-emitter handoff
    char unknown_00a855[0xa858 - 0xa855];
    Tutorial tutorial; // +0xa858, authored cRTutorial owner through +0xa874
    // Embedded level-definition owner. Its exact extent accounts for the
    // authored segment slots and all parsed level metadata through parcel_quota.
    SubTracks level_definition; // +0xa874, ends at +0x1b01ec
    // A second complete cRSubTracks-shaped owner. Startup reuses it while
    // enumerating every Levels/*.txt file, then reseeds its slot storage from
    // the built-in segment table; it is storage, not a borrowed loader view.
    SubTracks level_definition_scratch; // +0x1b01ec, ends at +0x355b64
    // Ten consecutive constructed BodBase records close this entire 0x230-byte
    // interval. Startup links nine into the root active list; +0x355d5c stays
    // unlinked there. Roles without a direct native consumer stay offset-named
    // rather than borrowing names from ports with a different group ordering.
    BodBase fringe_attachment_list_head; // +0x355b64
    BodBase track_body_list_head; // +0x355b9c, cells plus start/end banners
    BodBase barrier_sub_lazer_list_head; // +0x355bd4
    BodBase salt_hazard_list_head; // +0x355c0c
    BodBase landscape_slice_list_head; // +0x355c44, ten active landscape repeats
    BodBase unknown_bod_355c7c; // +0x355c7c
    BodBase special_track_cell_list_head; // +0x355cb4, tile 29/30 bodies
    BodBase unknown_bod_355cec; // +0x355cec
    BodBase golb_vapour_list_head; // +0x355d24, Golb embedded vapour bodies
    BodBase unknown_bod_355d5c; // +0x355d5c
    int active_level_score; // +0x355d94, copied from the selected bank record
    Time active_level_timer; // +0x355d98, embedded cRTime display snapshot
    SubSpeedUp speedup_pickup; // +0x355db0, owned cRSubSpeedUp singleton
    JetPack jetpack_pickup; // +0x355e64, owned cRJetPack singleton
    SubHealth health_pickups[8]; // +0x356000, eight owned cRSubHealth slots
    SlugPool slug_hazards; // +0x3563a0, eight owned cRSlug slots
    SubLazerManager sub_lazers; // +0x356b00, 20 owned cRSubLazer slots
    SaltManager salt_hazards; // +0x3578c0, 40 owned cRSalt slots
    BannerPool banners; // +0x359080, embedded start/completion actors
    SubGarbagePool garbage_hazards; // +0x359140, borrowed head + 50 owned slots
    SubRingPool ring_effects; // +0x35b78c, two embedded cRSubRing slots
    SlugVoiceManager slug_voice_manager; // +0x35bb7c, authored cRSlugVoiceManager
    // BorderManager pool handles. SubgameRuntime retains them for gameplay,
    // then destroy_subgame returns each handle through kill_border().
    FrontendWidget* top_score_widget; // +0x35bb88
    FrontendWidget* bottom_score_widget; // +0x35bb8c
    FrontendWidget* lives_icon_widget; // +0x35bb90
    FrontendWidget* lives_text_widget; // +0x35bb94
    FrontendWidget* life_stock_widgets[9]; // +0x35bb98
    // Fixed visual pool owned by SubgameRuntime. TrackRowCell fringe fields
    // only borrow handles into this storage while a built track is live.
    FringeManager fringe_manager; // +0x35bbbc, count at +0x3bb6fc
    // Shared cadence source used by the embedded slug pool. Startup fills the
    // samples once; each blink advances the single wrapping cursor.
    int blink_random_index; // +0x3bb700
    float blink_random_samples[24]; // +0x3bb704, ends at +0x3bb764
    // The complete cRSubGoldy actor is embedded here. Its score/timer block,
    // gauges, cameraman, and presentation controller all share this owner;
    // the former sparse SubgameRuntime aliases merely reached into this field.
    Player player; // +0x3bb764, ends at +0x3bfac8
    // Fixed row-major runtime grid owned by SubgameRuntime. Gameplay actors
    // retain pointers into this slab only for the lifetime of the built track.
    SubLoc runtime_cells[SUBGAME_RUNTIME_ROW_CAPACITY][SUBGAME_TRACK_LANE_COUNT];
    // +0x3bfac8, ends at +0x5ccac8
    // Fixed row records owned by SubgameRuntime. Their body objects are
    // embedded; source_segment and attachment-cell fields are borrowed links.
    SubRow runtime_rows[SUBGAME_RUNTIME_ROW_CAPACITY]; // +0x5ccac8, ends at +0x68b4c8
    // Both objects are embedded in SubgameRuntime. complete_subgame snapshots
    // into current_high_score_record, then lends that record to sub_high_score
    // for in-place normalization and value-copy persistence.
    SubHighScore sub_high_score; // +0x68b4c8, owns persistent record arrays
    SubSolution current_high_score_record; // +0xfd2b10, working run snapshot
    union {
        unsigned char selected_level_record_active; // +0xff25d0
        unsigned char replay_launch_active; // front-end replay handoff alias
    };
    union {
        unsigned char selected_level_record_persistent; // +0xff25d1
        unsigned char replay_launch_from_frontend; // front-end replay handoff alias
    };
    char unknown_ff25d2[0xff25d4 - 0xff25d2];
    union {
        SubSolution* selected_level_record; // +0xff25d4
        SubSolution* replay_launch_record; // front-end replay handoff alias
    };
    union {
        int selected_level_record_cursor; // +0xff25d8, replay/update cursor window
        int replay_launch_return_state; // front-end state restored after replay
    };
    int replay_update_cursor; // +0xff25dc
    TimeTrial time_trial; // +0xff25e0, exact authored cRTimeTrial owner
    PathManager path_manager; // +0xff2910, empty authored cRPathManager owner
    char unknown_ff2911[0xff2914 - 0xff2911];
    // Startup constructs 126 authored cRPath records here as 63 adjacent
    // primary/secondary pairs; public `Path=` indices occupy 0..50 and
    // transition-only auxiliary pairs occupy 51..62.
    PathPair path_pairs[PATH_PAIR_COUNT]; // +0xff2914, ends +0xff7bc4
    BarrierActor barrier; // +0xff7bc4, embedded tutorial barrier actor
    // Exact cRLandscapeManager owner: ten active render entries followed by
    // the script count and 128 parsed 0x124-byte records.
    LandscapeManager landscape_manager; // +0xff7c00, ends at +0x10013a4
    SmtrackHeightfieldAnimator smtrack_heightfield; // +0x10013a4, ends at +0x10014cc
    // The count precedes 150 constructor-built 0x4088-byte records. Their
    // exact aggregate extent reaches the following parcel pool.
    SMTracks sm_tracks; // +0x10014cc, ends at +0x125e480
    ParcelManager parcel_manager; // +0x125e480, 50 owned cRParcel slots
    union {
        float garbage_frequency; // +0x125ffd8, normalized Garbage: spawn control
        int garbage_frequency_bits;
    };
    union {
        float salt_frequency; // +0x125ffdc, normalized Salt: spawn control
        int salt_frequency_bits;
    };
    GUI gui; // +0x125ffe0
    Help help; // +0x1260008, exact authored cRHelp owner
    ThanksScreen thanks_screen; // +0x126000c, embedded front-end controller
    Galaxy galaxy; // +0x1260020, authored cRGalaxy owner through +0x1270fc8
    int subgame_rebuild_selector; // +0x1270fc8
    float next_slug_voice_trigger_z; // +0x1270fcc, advances when a spawned slug is marked to speak
    float slug_voice_trigger_spacing_z; // +0x1270fd0
    EnemyManager enemy_manager; // +0x1270fd4, authored cREnemyManager owner
    Completion completion; // +0x12727d8, embedded cRCompletion owner
    TimesUp times_up; // +0x1272828, authored cRTimesUp owner
};

// GameRoot embeds cRSubGame at +0x74618. Its exact extent reaches the root
// high-score screen at +0x12e6e50, proving that the replay, help, thanks, and
// high-score-bank fields above all share this single owner.
typedef char SubgameRuntime_must_be_0x1272838[
    (sizeof(SubgameRuntime) == 0x1272838) ? 1 : -1];

inline Player* SubgameRuntime::embedded_player()
{
    return &player;
}

inline Vector3* SubgameRuntime::parcel_delivery_arc_basis()
{
    return &embedded_player()->presentation.transform.basis_up;
}

inline Vector3* SubgameRuntime::parcel_home_anchor()
{
    return &embedded_player()->presentation.snail_hotspots_world[
        SNAIL_HOTSPOT_PARCEL_POINT];
}

inline TrackRowCellTileByteView* SubgameRuntime::runtime_cell_tile_views()
{
    return (TrackRowCellTileByteView*)&runtime_cells[0][0].tile_id;
}

inline TrackRowCellFringeLinkView* SubgameRuntime::runtime_cell_fringe_links()
{
    return (TrackRowCellFringeLinkView*)&runtime_cells[0][0].fringes[0];
}

#endif
