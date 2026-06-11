// Attachment-follow runtime structures, partial.
// Offsets per analysis/decompile/*/00420c40-*.c and 00420cb0-*.c
#ifndef TRACK_ATTACHMENT_H
#define TRACK_ATTACHMENT_H

#include "golb.h"

struct AttachmentPathTemplate {
    char unknown_00[0x98];
    float installed_heading_delta; // +0x98
};

struct TrackRowCell {
    char unknown_00[0x10];
    Vector3 anchor_position;            // +0x10 (z at +0x18)
    char unknown_1c[0x38 - 0x1c];
    AttachmentPathTemplate* attachment_template_record; // +0x38

    int get_row_index(); // get_track_cell_row_index, thiscall
};

struct GamePlayer; // opaque

class FollowState {
public:
    AttachmentPathTemplate* begin_track_attachment_follow_state(
        TrackRowCell* source_cell, const Vector3* world_position, GamePlayer* player); // @ 0x420c40

    unsigned char active;        // +0x00
    char unknown_01[3];
    AttachmentPathTemplate* template_record; // +0x04
    TrackRowCell* source_cell;   // +0x08
    int sample_index;            // +0x0c
    float progress;              // +0x10
    float vertical_offset;       // +0x14
    char unknown_18[0x38 - 0x18];
    GamePlayer* player;          // +0x38
};

// data_4df904: relocatable game-allocation base; the per-row heading table
// lives at a fixed VA offset from it
extern char* g_game_base;
extern char g_row_heading_table[];

#endif
