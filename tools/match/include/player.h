// Player (Goldy) runtime struct, partial. iOS symbols name this owner
// cRSubGoldy, with the presentation subobject carrying cRSnail methods.
// Fields recovered around the
// attachment-exit lanes. Offsets per analysis/decompile/*/0043af60-*.c and
// the swept-entry asm (position vector at +0x68; the global instance lives
// at game+0x42fd7c, so game+0x42fde8 is position.y).
#ifndef PLAYER_H
#define PLAYER_H

#include "cameraman_state.h"
#include "damage_gauge.h"
#include "invincible_shell.h"
#include "jetpack_gauge.h"
#include "nuke_controller.h"
#include "presentation_animation_channel.h"
#include "score_stats.h"
#include "snail_skin.h"
#include "timer_counters.h"
#include "tip_manager.h"
#include "transform_matrix.h"
#include "vector3.h"

struct AttachmentPathTemplate;
struct Object;
struct TrackRowCell;

class Game;
class Player;
class Sprite;
class TrackHealthPickup;

struct PlayerLiveMatrixRows {
    float basis_right_x;   // +0x00
    float basis_right_y;   // +0x04
    float basis_right_z;   // +0x08
    float basis_right_w;   // +0x0c
    float basis_up_x;      // +0x10
    float basis_up_y;      // +0x14
    float basis_up_z;      // +0x18
    float basis_up_w;      // +0x1c
    float basis_forward_x; // +0x20
    float basis_forward_y; // +0x24
    float basis_forward_z; // +0x28
    float basis_forward_w; // +0x2c
    float position_x;      // +0x30
    float position_y;      // +0x34
    float position_z;      // +0x38
    float position_w;      // +0x3c
};
typedef char PlayerLiveMatrixRows_must_be_0x40[
    (sizeof(PlayerLiveMatrixRows) == 0x40) ? 1 : -1];

extern char g_player_live_matrix_basis_right[];   // 0x42fdb4 = g_player_block + 0x38
extern char g_player_live_matrix_basis_up[];      // 0x42fdc4 = g_player_block + 0x48
extern char g_player_live_matrix_basis_forward[]; // 0x42fdd4 = g_player_block + 0x58

class PlayerPresentationController;

class PlayerControlSource {
public:
    char unknown_00[0x04];
    unsigned int control_flags_a; // +0x04
    char unknown_08[0x0c - 0x08];
    unsigned int control_flags_b; // +0x0c
    char unknown_10[0x28 - 0x10];
    float steering_x; // +0x28
};
typedef char PlayerControlSource_must_cover_0x2c[
    (sizeof(PlayerControlSource) == 0x2c) ? 1 : -1];

struct PlayerRowEventState {
    int id;                         // +0x00
    TipMessageDefinition definition; // +0x04
};
typedef char PlayerRowEventState_must_be_0x18[
    (sizeof(PlayerRowEventState) == 0x18) ? 1 : -1];

class CutsceneAI {
public:
    int initialize_cutscene_ai(); // @ 0x446130
    void update_cutscene();       // @ 0x4466d0

    PlayerPresentationController* presentation; // +0x00
    Player* player;                             // +0x04
    int camera_mode;                            // +0x08
    int state;                                  // +0x0c
    TransformMatrix live_matrix;                // +0x10
    float progress;                             // +0x50
    float progress_step;                        // +0x54
    unsigned char force_camera_update;          // +0x58
    char unknown_59[0x5c - 0x59];
};
typedef char CutsceneAI_must_be_0x5c[
    (sizeof(CutsceneAI) == 0x5c) ? 1 : -1];

class PlayerPresentationController {
public:
    void release_snail_weapons();          // @ 0x442e40
    void set_snail_jetpack(int state);      // @ 0x445860
    void set_snail_weapon(int movement_flags); // @ 0x445920
    void initialize_cutscene();             // @ 0x4428d0
    int dispatch_cutscene_animation(int animation, unsigned char immediate, int initial_frame); // @ 0x444600
    void update_snail_skin();               // @ 0x445cd0
    void build_snail_hotspots();            // @ 0x445d50

    char unknown_00[0x04];
    unsigned int visual_flags;              // +0x04
    char unknown_08[0x24 - 0x08];
    PresentationAnimationVisualRoot* visual_root; // +0x24
    char unknown_28[0x38 - 0x28];
    TransformMatrix live_matrix;            // +0x38
    char unknown_78[0x80 - 0x78];
    TransformMatrix previous_live_matrix;   // +0x80
    TransformMatrix cached_cutscene_matrix; // +0xc0
    Player* owner_player;                   // +0x100
    AnimManager anim_manager;               // +0x104
    char unknown_14c[0x170 - 0x14c];
    char cutscene_animation_slot_table[0x64c - 0x170]; // +0x170, 0x80-byte records
    PresentationAnimationChannel weapon_channels[3]; // +0x64c
    PresentationAnimationChannel jetpack_channel;     // +0x11e0
    float wobble_roll_phase;            // +0x15bc
    float wobble_roll_phase_step;       // +0x15c0
    float wobble_lift_phase;            // +0x15c4
    float wobble_lift_phase_step;       // +0x15c8 (Player +0x3f4c)
    char unknown_15cc[0x1604 - 0x15cc];
    TransformMatrix snail_hotspot_source_matrix_a; // +0x1604
    char unknown_1644[0x1670 - 0x1644];
    Object* snail_hotspot_model;            // +0x1670
    char unknown_1674[0x1684 - 0x1674];
    TransformMatrix snail_hotspot_source_matrix_b; // +0x1684
    char unknown_16c4[0x16cc - 0x16c4];
    Vector3 snail_hotspots_local[19];   // +0x16cc
    Vector3 snail_hotspots_world[19];   // +0x17b0
    InvincibleShellController invincible_shell; // +0x1894
    SnailSkinTransition snail_skin_transition;  // +0x1938
    CutsceneAI cutscene_ai;                     // +0x1958
};
typedef char PlayerPresentationController_must_be_0x19b4[
    (sizeof(PlayerPresentationController) == 0x19b4) ? 1 : -1];

class SquidgeState {
public:
    void start_squidge_y(float amount);   // @ 0x444980
    void start_squidge_z(float amount);   // @ 0x4449a0
    void update_squidge();                // @ 0x4449c0

    float y_output;   // +0x00
    float y_velocity; // +0x04
    float y_phase;    // +0x08
    float z_output;   // +0x0c
    float z_velocity; // +0x10
    float z_phase;    // +0x14
};

class Player {
public:
    void begin_post_follow_carryover();   // @ 0x43af60
    int update_player_movement_flags();    // @ 0x43a1a0
    void play_movement_state_sound();      // @ 0x43afd0
    void add_subgoldy_score(int score_kind, int bonus_score); // @ 0x4402c0
    void handle_subgoldy_collisions();      // @ 0x444cf0
    void health_collect_particles(TrackHealthPickup* pickup); // @ 0x43a010
    int initialize_subgoldy(int player_slot); // @ 0x43a9c0
    int initialize_subgoldy_ghost(int owner); // @ 0x43d230
    int initialize_subgoldy_resurrect(int final_loss); // @ 0x441fa0
    void update_subgoldy_resurrect();      // @ 0x441fd0
    int initialize_subgoldy_death();       // @ 0x446e30
    void kill_subgoldy();                 // @ 0x445840
    void show_subgoldy_lives();           // @ 0x43af10
    Sprite* set_subgoldy_ghost_z(float ghost_z); // @ 0x43d3d0

    char unknown_00[0x68];                 // +0x00; +0x38..+0x77 is PlayerLiveMatrixRows
    Vector3 position;                      // +0x68 (PlayerLiveMatrixRows.position)
    char unknown_74[0x80 - 0x74];
    int resurrect_final_loss;              // +0x80
    unsigned char resurrect_active;        // +0x84
    char unknown_85[0x8c - 0x85];
    float resurrect_progress;              // +0x8c
    float resurrect_progress_step;         // +0x90
    char unknown_94[0x98 - 0x94];
    // The ghost pair initialized by initialize_subgoldy_ghost. The same two
    // sprite slots are updated each tick by set_subgoldy_ghost_z.
    Sprite* ghost_sprite_a;                // +0x98
    Sprite* ghost_sprite_b;                // +0x9c
    char unknown_a0[0x120 - 0xa0];
    int movement_state;                    // +0x120
    char unknown_124[0x148 - 0x124];
    unsigned char intro_cutscene_latch;     // +0x148; cleared by update_cutscene state-8 handoff
    char unknown_149[0x14c - 0x149];
    unsigned char row_event_cutscene_started; // +0x14c
    char unknown_14d[0x150 - 0x14d];
    NukeController nuke;                  // +0x150
    int movement_sound_variant_sample;      // +0x1cc
    char unknown_1d0[0x1d4 - 0x1d0];
    float damage_retrigger_timer;           // +0x1d4
    float damage_retrigger_step;            // +0x1d8
    float surface_reaction_timer;           // +0x1dc
    float surface_reaction_step;            // +0x1e0
    unsigned char trampoline_bounce_active; // +0x1e4
    char unknown_1e5[0x1e8 - 0x1e5];
    PlayerRowEventState row_event;          // +0x1e8
    CameramanState cameraman;               // +0x200
    unsigned char control_override_active;  // +0x2d8
    char unknown_2d9[0x2dc - 0x2d9];
    float cutscene_pitch_cycle;             // +0x2dc
    float cutscene_pitch_cycle_step;        // +0x2e0
    // Player-side score producer window. The run score block at game+0x3bb764
    // has matching inner offsets but is represented separately by RunScoreStats.
    int total_score;                        // +0x2e4
    TimerCounters stopwatch;                // +0x2e8
    char unknown_300[0x304 - 0x300];
    // Click-start seeds this slot; update_subgoldy later reuses it as the
    // replay/ghost anchor cursor.
    int startup_track_index;                // +0x304
    int movement_flag_selector;             // +0x308
    char unknown_30c[0x310 - 0x30c];
    int score_buckets[SUBGOLDY_SCORE_BUCKET_COUNT]; // +0x310
    float barrier_hold_progress;            // +0x328
    float barrier_hold_step;                // +0x32c
    float startup_voice_timer;              // +0x330
    float startup_voice_step;               // +0x334
    unsigned int movement_flags;           // +0x338
    unsigned int previous_movement_flags;   // +0x33c
    char unknown_340[0x350 - 0x340];
    int lane_lean_state;                   // +0x350
    float lane_lean_amplitude;             // +0x354
    float lane_lean_progress;              // +0x358
    float lane_lean_progress_step;         // +0x35c
    char unknown_360[0x370 - 0x360];
    float heading_roll;                     // +0x370
    float nuke_effect_progress;             // +0x374
    float nuke_effect_progress_step;        // +0x378
    char unknown_37c[0x380 - 0x37c];
    int player_slot;                       // +0x380
    // +0x384..+0x3c3 is the embedded FollowState prefix (track_attachment.h):
    // 0x42fd7c + 0x384 = 0x430100, the "shared FollowState global".
    // Keep the fields flattened here so adjacent Player lanes remain under the
    // Player owner instead of a child view reaching past its 0x40-byte extent.
    unsigned char follow_active;           // +0x384
    char unknown_385[3];
    AttachmentPathTemplate* follow_template; // +0x388
    TrackRowCell* follow_source_cell;      // +0x38c
    int follow_sample_index;               // +0x390
    float follow_progress;                 // +0x394
    float follow_vertical_offset;          // +0x398
    float follow_orientation_a;            // +0x39c
    float follow_orientation_b;            // +0x3a0
    float follow_orientation_c;            // +0x3a4
    float follow_orientation_d;            // +0x3a8
    float follow_orientation_e;            // +0x3ac
    Vector3 follow_output_position;        // +0x3b0
    Player* follow_player;                 // +0x3bc
    unsigned char follow_flag_3c;          // +0x3c0
    char unknown_3c1[0x3c4 - 0x3c1];
    DamageGaugeController damage_gauge;     // +0x3c4
    char unknown_3f0[0x404 - 0x3f0];
    int lives;                            // +0x404
    Game* game;                            // +0x408
    int movement_mode_selector;            // +0x40c
    Vector3 velocity;                      // +0x410 (y at +0x414, z at +0x418)
    unsigned char boost_one_tick;          // +0x41c — DEAD: only ever written 0
                                           // (initialize_subgoldy reg-zero +
                                           // update_subgoldy clear); the boost
                                           // consumer lane never fires
    unsigned char attachment_exit_pending; // +0x41d
    char unknown_41e[0x424 - 0x41e];
    float attachment_exit_anchor_z;        // +0x424
    char unknown_428[0x42c - 0x428];
    // carryover pair written by begin_post_follow_carryover (matched 100%):
    // +0x42c <- follow_orientation_b, consumed by update_cameraman as the
    // exit roll while attachment_exit_pending is set.
    // +0x430 <- follow_template->installed_heading_bits (consumer still open)
    float post_follow_exit_roll;           // +0x42c (orientation-b carryover)
    int post_follow_heading_carryover;     // +0x430 (was "post_follow_value_b")
    float attachment_exit_progress;        // +0x434
    float attachment_exit_progress_step;    // +0x438
    PlayerControlSource* control_source;    // +0x43c
    unsigned char completion_handoff_active; // +0x440
    char unknown_441[0x44c - 0x441];
    unsigned char attachment_exit_gate_a;  // +0x44c
    unsigned char attachment_exit_gate_b;  // +0x44d
    unsigned char completion_handoff_voice_gate; // +0x44e
    char unknown_44f[0x2730 - 0x44f];
    float movement_fire_progress;           // +0x2730
    float movement_fire_progress_step;      // +0x2734
    float slide_extension_threshold_z;      // +0x2738
    float track_z_offset;                   // +0x273c
    float track_z_anchor;                   // +0x2740
    float completion_handoff_cycle_progress; // +0x2744
    float completion_handoff_cycle_step;    // +0x2748
    char unknown_274c[0x2750 - 0x274c];
    JetpackGaugeController jetpack_gauge;   // +0x2750
    Vector3 cached_camera_target_world;     // +0x2964, produced by update_subgoldy camera block
    int steering_mode_selector;             // +0x2970
    char unknown_2974[0x2980 - 0x2974];
    float interaction_max_z;                // +0x2980
    PlayerPresentationController presentation; // +0x2984
    int parcels_collected;                 // +0x4338
    char unknown_433c[0x4340 - 0x433c];
    int visible_life_stock;                // +0x4340
    SquidgeState squidge;                  // +0x4344
    float slow_commentary_timer;            // +0x435c
    float slow_commentary_step;             // +0x4360
};

typedef char Player_must_be_0x4364[(sizeof(Player) == 0x4364) ? 1 : -1];

#endif
