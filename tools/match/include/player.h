// Player (Goldy) runtime struct, partial — fields recovered around the
// attachment-exit lanes. Offsets per analysis/decompile/*/0043af60-*.c and
// the swept-entry asm (position vector at +0x68; the global instance lives
// at game+0x42fd7c, so game+0x42fde8 is position.y).
#ifndef PLAYER_H
#define PLAYER_H

#include "vector3.h"

class Game;
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

class PlayerPresentationController {
public:
    void set_snail_weapon(int movement_flags); // @ 0x445920

    char unknown_00[0x4340 - 0x2984];
};

struct AttachmentRecord {
    int unknown_00[38];
    int installed_heading;            // +0x98
};

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
    char health_collect_particles(TrackHealthPickup* pickup); // @ 0x43a010
    int initialize_subgoldy_ghost(int owner); // @ 0x43d230
    int initialize_subgoldy_resurrect(int final_loss); // @ 0x441fa0
    void update_subgoldy_resurrect();      // @ 0x441fd0
    void kill_subgoldy();                 // @ 0x445840
    void show_subgoldy_lives();           // @ 0x43af10
    Sprite* mark_current_track_pair_with_payload(int payload); // @ 0x43d3d0

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
    // sprite slots are updated each tick by mark_current_track_pair_with_payload.
    Sprite* ghost_sprite_a;                // +0x98
    Sprite* ghost_sprite_b;                // +0x9c
    char unknown_a0[0x1cc - 0xa0];
    int movement_sound_variant_sample;      // +0x1cc
    char unknown_1d0[0x2e4 - 0x1d0];
    // Player-side score producer window. The run score block at game+0x3bb764
    // has matching inner offsets but is represented separately by RunScoreStats.
    int total_score;                        // +0x2e4
    char unknown_2e8[0x308 - 0x2e8];
    int movement_flag_selector;             // +0x308
    char unknown_30c[0x310 - 0x30c];
    int score_buckets[6];                  // +0x310
    char unknown_328[0x338 - 0x328];
    unsigned int movement_flags;           // +0x338
    unsigned int previous_movement_flags;   // +0x33c
    char unknown_340[0x370 - 0x340];
    float heading_roll;                     // +0x370
    float nuke_effect_progress;             // +0x374
    float nuke_effect_progress_step;        // +0x378
    char unknown_37c[0x380 - 0x37c];
    int player_slot;                       // +0x380
    // +0x384..+0x3bf is the embedded FollowState (track_attachment.h):
    // 0x42fd7c + 0x384 = 0x430100, the "shared FollowState global".
    // follow_active = FollowState.active, attachment_record =
    // FollowState.template_record, follow_orientation_b =
    // FollowState.orientation_b (+0x1c).
    unsigned char follow_active;           // +0x384
    char unknown_385[3];
    AttachmentRecord* attachment_record;   // +0x388
    char unknown_38c[0x3a0 - 0x38c];
    float follow_orientation_b;            // +0x3a0
    char unknown_3a4[0x408 - 0x3a4];
    Game* game;                            // +0x408
    char unknown_40c[0x410 - 0x40c];
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
    // +0x42c <- follow_orientation_b (the camera exit roll: update_cameraman
    // @ 0x4461d0, pinned, rotates world-z by it while exit_pending);
    // +0x430 <- attachment_record->installed_heading (consumer still open)
    float post_follow_orientation_carryover; // +0x42c (was "post_follow_value_b")
    int post_follow_heading_carryover;     // +0x430 (was "post_follow_value_a")
    int attachment_exit_progress;          // +0x434
    char unknown_438[0x44c - 0x438];
    unsigned char attachment_exit_gate_a;  // +0x44c
    unsigned char attachment_exit_gate_b;  // +0x44d
    char unknown_44e[0x2730 - 0x44e];
    float movement_fire_progress;           // +0x2730
    float movement_fire_progress_step;      // +0x2734
    char unknown_2738[0x2980 - 0x2738];
    float interaction_max_z;                // +0x2980
    PlayerPresentationController presentation; // +0x2984
    int visible_life_stock;                // +0x4340
};

#endif
