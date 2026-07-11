// Root subgame runtime view, partial. iOS symbols name this embedded owner
// cRSubGame; the surrounding Windows root object remains the larger Game view.
// This intentionally stays sparse: fields are added only when an exact helper
// or cross-function caller proves them.
#ifndef SUBGAME_RUNTIME_H
#define SUBGAME_RUNTIME_H

#include "active_landscape_entry.h"
#include "banner.h"
#include "barrier_actor.h"
#include "challenge_setup_screen.h"
#include "completion_screen.h"
#include "frontend_widget.h"
#include "fringe_object.h"
#include "garbage_hazard_slot.h"
#include "galaxy_route_types.h"
#include "high_score_bank.h"
#include "high_score_record.h"
#include "help_screen.h"
#include "level_definition_loader.h"
#include "cameraman_state.h"
#include "contact_target.h"
#include "new_game_menu.h"
#include "player.h"
#include "ring_special_effect_types.h"
#include "row_event_display.h"
#include "salt_hazard_types.h"
#include "score_stats.h"
#include "slug_hazard_types.h"
#include "sub_lazer_types.h"
#include "times_up_controller.h"
#include "thanks_screen.h"
#include "track_health_pickup.h"
#include "track_jetpack_pickup.h"
#include "track_attachment_types.h"
#include "track_parcel_runtime.h"
#include "track_render_cache.h"
#include "track_row_cell_tile_views.h"
#include "track_speedup.h"

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
    Vector3* parcel_delivery_arc_basis(); // Player.presentation.live_matrix.basis_up
    Vector3* parcel_home_anchor(); // Player.presentation.snail_hotspots_world[11]
    TrackRowCellTileByteView* runtime_cell_tile_views(); // +0x3bfb04 field-first view
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
        Player* ignored_player); // @ 0x443730, native binds embedded_player()
    TrackRowCell* get_track_grid_cell_at_world_position(Vector3* position);
    TrackAttachmentRuntimeRow* get_track_runtime_cell_at_world_z(Vector3* position);
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
    // Owns 143 rows x five render-family BOD slots and their shared staging
    // buffers. Its owner_subgame field is a borrowed backlink to this object.
    TrackRenderCacheManager track_render_cache; // +0x5c, ends at +0xa854
    char unknown_00a854[0xa858 - 0xa854];
    TutorialController tutorial; // +0xa858, embedded tutorial-mode controller
    char unknown_00a868[0xa874 - 0xa868];
    // Embedded level-definition owner. Its exact extent accounts for the
    // authored segment slots and all parsed level metadata through parcel_quota.
    LevelDefinitionLoader level_definition; // +0xa874, ends at +0x1b01ec
    char unknown_1b01ec[0x355bd4 - 0x1b01ec];
    // Constructed BodBase sentinels own the live intrusive lists used by the
    // corresponding fixed pools below. Spawn paths only consume the inherited
    // BodNode links, but startup proves the complete 0x38-byte objects.
    BodBase sub_lazer_list_head; // +0x355bd4
    BodBase salt_hazard_list_head; // +0x355c0c
    char unknown_355c44[0x355d94 - 0x355c44];
    int active_level_score; // +0x355d94, copied from the selected bank record
    TimerCounters active_level_timer; // +0x355d98, embedded display snapshot
    TrackSpeedupRuntime speedup_pickup; // +0x355db0
    TrackJetpackPickup jetpack_pickup; // +0x355e64
    TrackHealthPickup health_pickups[8]; // +0x356000
    SlugHazardPool slug_hazards; // +0x3563a0, fixed eight-slot owner
    SubLazerPool sub_lazers; // +0x356b00, fixed 20-slot owner
    SaltHazardPool salt_hazards; // +0x3578c0, fixed 40-slot owner
    BannerPool banners; // +0x359080, embedded start/completion actors
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
    // Fixed visual pool owned by SubgameRuntime. TrackRowCell fringe fields
    // only borrow handles into this storage while a built track is live.
    FringeManager fringe_manager; // +0x35bbbc, count at +0x3bb6fc
    char unknown_3bb700[0x3bb764 - 0x3bb700];
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
            union {
                int source_score; // Player.total_score +0x2e4
                int completion_base_score; // completion result-screen spelling
            };
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
    // Fixed row-major runtime grid owned by SubgameRuntime. Gameplay actors
    // retain pointers into this slab only for the lifetime of the built track.
    TrackRowCell runtime_cells[3200][8]; // +0x3bfac8, ends at +0x5ccac8
    // Fixed row records owned by SubgameRuntime. Their body objects are
    // embedded; source_segment and attachment-cell fields are borrowed links.
    TrackAttachmentRuntimeRow runtime_rows[3200]; // +0x5ccac8, ends at +0x68b4c8
    // Both objects are embedded in SubgameRuntime. complete_subgame snapshots
    // into current_high_score_record, then lends that record to high_score_bank
    // for in-place normalization and value-copy persistence.
    HighScoreBank high_score_bank; // +0x68b4c8, owns persistent record arrays
    HighScoreRecord current_high_score_record; // +0xfd2b10, working run snapshot
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
        HighScoreRecord* selected_level_record; // +0xff25d4
        HighScoreRecord* replay_launch_record; // front-end replay handoff alias
    };
    union {
        int selected_level_record_cursor; // +0xff25d8, replay/update cursor window
        int replay_launch_return_state; // front-end state restored after replay
    };
    int replay_update_cursor; // +0xff25dc
    char unknown_ff25e0[0xff2914 - 0xff25e0];
    // Startup constructs 126 records here. initialize_game_assets_and_world
    // consumes them as 63 adjacent primary/secondary pairs; public Path=
    // indices occupy 0..50 and transition-only auxiliary pairs occupy 51..62.
    AttachmentPathTemplatePair path_template_pairs[ATTACHMENT_PATH_TEMPLATE_PAIR_COUNT]; // +0xff2914, ends +0xff7bc4
    BarrierActor barrier; // +0xff7bc4, embedded tutorial barrier actor
    ActiveLandscapePool active_landscapes; // +0xff7c00, fixed 10-slot owner
    char unknown_ff81a4[0x125e480 - 0xff81a4];
    TrackParcelPool parcel_pool; // +0x125e480
    int source_timer_a; // +0x125ffd8
    int source_timer_b; // +0x125ffdc
    ChallengeSetupScreen challenge_setup; // +0x125ffe0
    HelpScreen help_screen; // +0x1260008, embedded front-end controller
    ThanksScreen thanks_screen; // +0x126000c, embedded front-end controller
    GalaxyRoute galaxy; // +0x1260020, embedded route controller
    char unknown_1270fc4[0x1270fc8 - 0x1270fc4];
    int subgame_rebuild_selector; // +0x1270fc8
    char unknown_1270fcc[0x1270fd4 - 0x1270fcc];
    ContactTargetRegistry contact_targets; // +0x1270fd4, embedded 256-entry frame registry
    RowEventDisplayController row_event_display; // +0x12727d8, embedded HUD controller
    TimesUpController times_up; // +0x1272828, embedded completion controller
};

// GameRoot embeds cRSubGame at +0x74618. Its exact extent reaches the root
// high-score screen at +0x12e6e50, proving that the replay, help, thanks, and
// high-score-bank fields above all share this single owner.
typedef char SubgameRuntime_must_be_0x1272838[
    (sizeof(SubgameRuntime) == 0x1272838) ? 1 : -1];

inline Player* SubgameRuntime::embedded_player()
{
    return (Player*)player_storage;
}

inline Vector3* SubgameRuntime::parcel_delivery_arc_basis()
{
    return &embedded_player()->presentation.live_matrix.basis_up;
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
    return (TrackRowCellFringeLinkView*)&runtime_cells[0][0].fringe_front;
}

inline TimeTrialStringFormatter* SubgameRuntime::time_trial_formatter()
{
    return (TimeTrialStringFormatter*)((char*)this + 0xff25e0);
}

#endif
