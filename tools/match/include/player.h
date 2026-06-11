// Player (Goldy) runtime struct, partial — fields recovered around the
// attachment-exit lanes. Offsets per analysis/decompile/*/0043af60-*.c and
// the swept-entry asm (position vector at +0x68; the global instance lives
// at game+0x42fd7c, so game+0x42fde8 is position.y).
#ifndef PLAYER_H
#define PLAYER_H

#include "golb.h"

struct AttachmentRecord {
    int unknown_00[38];
    int installed_heading;            // +0x98
};

class Player {
public:
    void begin_post_follow_carryover();   // @ 0x43af60
    void start_squidge_y(float amount);   // thiscall, image-resident

    int unknown_00[26];                    // +0x00
    Vector3 position;                      // +0x68 (y at +0x6c, z at +0x70)
    char unknown_74[0x384 - 0x74];
    unsigned char follow_active;           // +0x384
    char unknown_385[3];
    AttachmentRecord* attachment_record;   // +0x388
    char unknown_38c[0x3a0 - 0x38c];
    int follow_orientation_b;              // +0x3a0
    char unknown_3a4[0x41d - 0x3a4];
    unsigned char attachment_exit_pending; // +0x41d
    char unknown_41e[0x424 - 0x41e];
    float attachment_exit_anchor_z;        // +0x424
    char unknown_428[0x42c - 0x428];
    int post_follow_value_b;               // +0x42c
    int post_follow_value_a;               // +0x430
    int attachment_exit_progress;          // +0x434
    char unknown_438[0x44c - 0x438];
    unsigned char attachment_exit_gate_a;  // +0x44c
    unsigned char attachment_exit_gate_b;  // +0x44d
};

#endif
