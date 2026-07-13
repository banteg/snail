// Player (Goldy) runtime struct, partial. iOS symbols name this owner
// cRSubGoldy, with the presentation subobject carrying cRSnail methods.
// Fields recovered around the
// attachment-exit lanes. Offsets per analysis/decompile/*/0043af60-*.c and
// the swept-entry asm (position vector at +0x68; the global instance lives
// at game+0x42fd7c, so game+0x42fde8 is position.y).
#ifndef PLAYER_H
#define PLAYER_H

#include "cameraman.h"
#include "click_start.h"
#include "cut_scene.h"
#include "damage_guage.h"
#include "firework.h"
#include "golb.h"
#include "invincible.h"
#include "sub_hover.h"
#include "nuke.h"
#include "presentation_animation_channel.h"
#include "progress_bar.h"
#include "score_buckets.h"
#include "snail_skin.h"
#include "squidge.h"
#include "sub_loc_fwd.h"
#include "game_time.h"
#include "tip_manager.h"
#include "transform_matrix.h"
#include "vector3.h"
#include "warning.h"

struct Path;
struct Object;

class Player;
class Sprite;
class SubgameRuntime;
class SubHealth;

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

class Snail;

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
    TipData definition; // +0x04, authored cRTipData
};
typedef char PlayerRowEventState_must_be_0x18[
    (sizeof(PlayerRowEventState) == 0x18) ? 1 : -1];

// Authored hotpoint order from g_snail_hotspot_texture_names. These indices
// address both the local model-space bank and its world-space projection.
enum SnailHotspotIndex {
    SNAIL_HOTSPOT_BLASTER_LEFT_FIRE = 0,
    SNAIL_HOTSPOT_BLASTER_LEFT_BOLT = 1,
    SNAIL_HOTSPOT_BLASTER_RIGHT_FIRE = 2,
    SNAIL_HOTSPOT_BLASTER_RIGHT_BOLT = 3,
    SNAIL_HOTSPOT_BLASTER_TOP_FIRE = 4,
    SNAIL_HOTSPOT_BLASTER_TOP_BOLT = 5,
    SNAIL_HOTSPOT_LASER_LEFT = 6,
    SNAIL_HOTSPOT_LASER_RIGHT = 7,
    SNAIL_HOTSPOT_ROCKET_RIGHT = 8,
    SNAIL_HOTSPOT_ROCKET_LEFT = 9,
    SNAIL_HOTSPOT_ROCKET_BASE = 10,
    SNAIL_HOTSPOT_PARCEL_POINT = 11,
    SNAIL_HOTSPOT_CAMERA_SKID_STOP = 12,
    SNAIL_HOTSPOT_JETPACK_LEFT = 13,
    SNAIL_HOTSPOT_JETPACK_RIGHT = 14,
    SNAIL_HOTSPOT_LASER_RIGHT_BASE = 15,
    SNAIL_HOTSPOT_LASER_LEFT_BASE = 16,
    SNAIL_HOTSPOT_CAMERA_SLUG_DEATH = 17,
    SNAIL_HOTSPOT_CAMERA_INTRO_TALK = 18,
    SNAIL_HOTSPOT_COUNT = 19,
};

class Snail {
public:
    Snail* initialize_player_presentation_controller(); // @ 0x4086d0
    void release_snail_weapons();          // @ 0x442e40
    void set_snail_jetpack(int state);      // @ 0x445860
    void set_snail_weapon(int movement_flags); // @ 0x445920
    void initialize_cutscene();             // @ 0x4428d0
    int dispatch_cutscene_animation(int animation, unsigned char immediate, int initial_frame); // @ 0x444600
    void update_snail_skin();               // @ 0x445cd0
    void build_snail_hotspots();            // @ 0x445d50

    // The first 0x10 bytes are an intrusive BOD-list node. build_subgame_level
    // links this embedded presentation object; the list does not own it.
    void* vtable;                          // +0x00, noop presentation callback
    unsigned int list_flags;               // +0x04, inherited BOD render/list flags
    char unknown_08[0x24 - 0x08];
    Object* object;                            // +0x24, borrowed animated cRObject
    char unknown_28[0x38 - 0x28];
    TransformMatrix live_matrix;            // +0x38
    // Installed only when the linked Object owns generated animation frames.
    // cRGame::Render borrows this manager's progress for Object::animation.
    AnimManager* render_animation_manager; // +0x78, borrowed owned manager at +0x104
    char unknown_7c[0x80 - 0x7c];
    TransformMatrix previous_live_matrix;   // +0x80
    TransformMatrix cached_cutscene_matrix; // +0xc0
    Player* owner_player;                   // +0x100, non-owning backlink to containing Player
    AnimManager anim_manager;               // +0x104
    PresentationAnimationSlot cutscene_animation_slots[10]; // +0x14c, owned slots
    PresentationAnimationChannel weapon_channels[3]; // +0x64c
    PresentationAnimationChannel jetpack_channel;     // +0x11e0
    float wobble_roll_phase;            // +0x15bc
    float wobble_roll_phase_step;       // +0x15c0
    float wobble_lift_phase;            // +0x15c4
    float wobble_lift_phase_step;       // +0x15c8 (Player +0x3f4c)
    char unknown_15cc[0x1604 - 0x15cc];
    TransformMatrix snail_hotspot_source_matrix_a; // +0x1604
    char unknown_1644[0x164c - 0x1644];
    RenderableBod snail_hotspot_body;        // +0x164c, owns model at +0x1670 and transform at +0x1684
    char unknown_16c4[0x16cc - 0x16c4];
    Vector3 snail_hotspots_local[SNAIL_HOTSPOT_COUNT];   // +0x16cc
    Vector3 snail_hotspots_world[SNAIL_HOTSPOT_COUNT];   // +0x17b0
    Invincible invincible_shell;                // +0x1894, authored cRInvincible
    SnailSkin snail_skin;                       // +0x1938, authored cRSnailSkin
    CutScene cutscene;                          // +0x1958, authored cRCutScene
};
typedef char Snail_must_be_0x19b4[(sizeof(Snail) == 0x19b4) ? 1 : -1];

class Player {
public:
    void begin_post_follow_carryover();   // @ 0x43af60
    int update_player_movement_flags();    // @ 0x43a1a0
    void update_movement_flag_emitters(Player* player); // @ 0x43a300
    void play_movement_state_sound();      // @ 0x43afd0
    void add_subgoldy_score(int score_kind, int bonus_score); // @ 0x4402c0
    int clear_subgoldy_score_buckets();    // @ 0x4403a0
    int display_score_stats();             // @ 0x4403c0
    void handle_subgoldy_collisions();      // @ 0x444cf0
    void health_collect_particles(SubHealth* pickup); // @ 0x43a010
    void initialize_subgoldy(int player_slot); // @ 0x43a9c0, cRSubGoldy::Init
    int initialize_subgoldy_ghost(int owner); // @ 0x43d230
    int initialize_subgoldy_resurrect(int final_loss); // @ 0x441fa0
    void update_subgoldy_resurrect();      // @ 0x441fd0
    int initialize_subgoldy_death();       // @ 0x446e30
    void kill_subgoldy();                 // @ 0x445840
    void show_subgoldy_lives();           // @ 0x43af10
    Sprite* set_subgoldy_ghost_z(float ghost_z); // @ 0x43d3d0
    TransformMatrix* live_transform(); // RenderableBod-compatible view at +0x38

    // The first 0x10 bytes are an intrusive BOD-list node. Player storage is
    // embedded in SubgameRuntime and merely linked into the global active list.
    char unknown_00[0x04];
    unsigned int list_flags;               // +0x04, intrusive BOD membership/render flags
    char unknown_08[0x68 - 0x08];          // +0x38..+0x77 is PlayerLiveMatrixRows
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
    ClickStart click_start;                // +0xa0, exact authored cRClickStart
    unsigned char row_event_cutscene_started; // +0x14c
    char unknown_14d[0x150 - 0x14d];
    Nuke nuke;                            // +0x150, authored cRNuke owner
    int movement_sound_variant_sample;      // +0x1cc
    FireWork firework;                      // +0x1d0, empty authored cRFireWork child
    char unknown_1d1[0x1d4 - 0x1d1];
    float damage_retrigger_timer;           // +0x1d4
    float damage_retrigger_step;            // +0x1d8
    float surface_reaction_timer;           // +0x1dc
    float surface_reaction_step;            // +0x1e0
    unsigned char trampoline_bounce_active; // +0x1e4
    char unknown_1e5[0x1e8 - 0x1e5];
    PlayerRowEventState row_event;          // +0x1e8
    Cameraman cameraman;                    // +0x200, authored cRCameraman owner
    unsigned char control_override_active;  // +0x2d8
    char unknown_2d9[0x2dc - 0x2d9];
    float cutscene_pitch_cycle;             // +0x2dc
    float cutscene_pitch_cycle_step;        // +0x2e0
    // Player-owned run score producer and completion snapshot window.
    int total_score;                        // +0x2e4
    Time stopwatch;                         // +0x2e8, authored cRTime value
    // Only confirmed consumer copies this value into SubSolution::score_tail.
    int score_tail;                         // +0x300
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
    float last_ring_spawn_z;                // +0x37c, initialized here and maintained by update_subgame
    int player_slot;                       // +0x380
    // +0x384..+0x3c3 is the embedded FollowState prefix (track_attachment.h):
    // 0x42fd7c + 0x384 = 0x430100, the "shared FollowState global".
    // Keep the fields flattened here so adjacent Player lanes remain under the
    // Player owner instead of a child view reaching past its 0x40-byte extent.
    unsigned char follow_active;           // +0x384
    char unknown_385[3];
    Path* follow_template; // +0x388
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
    DamageGuage damage_gauge;     // +0x3c4
    ProgressBar progress_bar;               // +0x3f0, empty authored cRProgressBar
    char unknown_3f1[0x3f4 - 0x3f1];
    Warning warning;                       // +0x3f4, authored cRWarning owner
    int lives;                            // +0x404
    // Non-owning backlink to the SubgameRuntime that embeds this Player.
    // initialize_subgoldy is its sole setter; teardown never frees through it.
    SubgameRuntime* game;                  // +0x408
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
    // Borrowed input view inside the root game object, selected by player_slot.
    PlayerControlSource* control_source;    // +0x43c
    unsigned char completion_handoff_active; // +0x440
    char unknown_441[0x444 - 0x441];
    float completion_handoff_timer;         // +0x444
    float completion_handoff_timer_step;    // +0x448
    unsigned char attachment_exit_gate_a;  // +0x44c
    unsigned char attachment_exit_gate_b;  // +0x44d
    unsigned char completion_handoff_voice_gate; // +0x44e
    char unknown_44f[0x450 - 0x44f];
    GolbShot golb_shots[12];               // +0x450, owned projectile bank through +0x2730
    float movement_fire_progress;           // +0x2730
    float movement_fire_progress_step;      // +0x2734
    float slide_extension_threshold_z;      // +0x2738
    float track_z_offset;                   // +0x273c
    float track_z_anchor;                   // +0x2740
    float completion_handoff_cycle_progress; // +0x2744
    float completion_handoff_cycle_step;    // +0x2748
    char unknown_274c[0x2750 - 0x274c];
    SubHover sub_hover;                     // +0x2750, authored cRSubHover
    Vector3 cached_camera_target_world;     // +0x2964, produced by update_subgoldy camera block
    int steering_mode_selector;             // +0x2970
    char unknown_2974[0x2980 - 0x2974];
    float interaction_max_z;                // +0x2980
    Snail presentation;                       // +0x2984, authored cRSnail
    int parcels_collected;                 // +0x4338
    char unknown_433c[0x4340 - 0x433c];
    int visible_life_stock;                // +0x4340
    Squidge squidge;                       // +0x4344, authored cRSquidge
    float slow_commentary_timer;            // +0x435c
    float slow_commentary_step;             // +0x4360
};

typedef char Player_must_be_0x4364[(sizeof(Player) == 0x4364) ? 1 : -1];

inline TransformMatrix* Player::live_transform()
{
    return (TransformMatrix*)((char*)this + 0x38);
}

#endif
