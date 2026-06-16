// Attachment-follow runtime type views, partial.
#ifndef TRACK_ATTACHMENT_TYPES_H
#define TRACK_ATTACHMENT_TYPES_H

#include "vector3.h"
#include "vector_types.h"

struct TransformMatrix;
class Player;
class FringeObject;

struct AttachmentTransform {
    Vector4 basis_right;             // +0x00
    Vector4 basis_up;                // +0x10
    Vector4 basis_forward;           // +0x20
    Vector4 position;                // +0x30
};

struct AttachmentSample {            // stride 0xa8
    AttachmentTransform transform;   // +0x00
    float inverse_matrix[12];        // +0x40, local-frame rotation
    char unknown_70[0x80 - 0x70];
    Vector3 delta_dir_to_next;       // +0x80
    float delta_length;              // +0x8c, segment length (the swept-entry
                                     // "depth limit" gate is z < this)
    float center_x;                  // +0x90
    float rotation_scalar_94;        // +0x94
    float rotation_scalar_98;        // +0x98
    float lateral_scale;             // +0x9c
    float special_scalar;            // +0xa0, kind-42 scale/radius source
    float lateral_source;            // +0xa4
};

struct TrackRowCell;

struct AttachmentPathTemplate {
    void allocate_path_template_samples(); // @ 0x41b0a0
    void try_enter_track_attachment_from_swept_motion(
        float px, float py, float pz,
        float sweep_x, float sweep_y, float sweep_z,
        TrackRowCell* cell); // @ 0x42c770
    int compute_kind42_attachment_transform(
        float radius, float x, float y, TransformMatrix* transform, float* out_angle);

    char unknown_00[0x38];
    int kind;                        // +0x38
    unsigned char is_mirrored_x;     // +0x3c
    char unknown_3d[0x40 - 0x3d];
    int side_exit_mode;              // +0x40
    int segment_count;               // +0x44
    int row_span_count;              // +0x48, runtime rows stamped by entry tiles
    float segment_count_f;           // +0x4c
    float width_or_scale;            // +0x50
    int width_cells;                 // +0x54, integer half-span source
    AttachmentSample* primary_samples; // +0x58
    AttachmentSample* secondary_samples; // +0x5c
    char unknown_60[0x98 - 0x60];
    union {
        float installed_heading_delta;
        int installed_heading_bits;
    };                               // +0x98
    unsigned char special_runtime_flag_9c; // +0x9c
    char unknown_9d[0xa8 - 0x9d];

    int get_path_position_at_node(Vector3* out, int node, int row_index, float* local);
};

struct TrackRowCell {
    char unknown_00[0x10];
    Vector3 anchor_position;            // +0x10 (z at +0x18)
    char unknown_1c[0x38 - 0x1c];
    AttachmentPathTemplate* attachment_template_record; // +0x38
    unsigned char tile_id;              // +0x3c
    unsigned char tile_flags_3d;        // +0x3d
    char unknown_3e[0x40 - 0x3e];
    int lane_and_flags;                 // +0x40, low 3 bits are lane; 0x18 warning footprint
    FringeObject* fringe_front;         // +0x44
    FringeObject* fringe_right;         // +0x48
    FringeObject* fringe_left;          // +0x4c
    FringeObject* fringe_back;          // +0x50

    int get_track_cell_row_index();
};

struct TrackAttachmentRuntimeRow {       // stride 0xf4
    unsigned int flags;                  // +0x00, 0x40 primary, 0x80 secondary
    char unknown_04[0x90 - 0x04];
    // place_parcels_on_track uses this as an overloaded parcel projection
    // payload: x is lateral/local x, y is incremented as a claim/count lane,
    // and z accumulates absolute row + 0.5 before the attachment projection
    // tail consumes the same vector-shaped storage.
    Vector3 projection_payload;          // +0x90, parcel/path projection payload
    char unknown_9c[0xa4 - 0x9c];
    TrackRowCell* primary_attachment_cell; // +0xa4
    TrackRowCell* secondary_attachment_cell; // +0xa8
    char unknown_ac[0xf0 - 0xac];
    int row_event_id;                    // +0xf0
};

class FollowState {
public:
    AttachmentPathTemplate* begin_track_attachment_follow_state(
        TrackRowCell* source_cell, const Vector3* world_position, Player* player); // @ 0x420c40
    int update_track_attachment_follow_state(
        float rate, Vector3* out_position, Vector3* motion); // @ 0x420cb0

    unsigned char active;        // +0x00
    char unknown_01[3];
    AttachmentPathTemplate* template_record; // +0x04
    TrackRowCell* source_cell;   // +0x08
    int sample_index;            // +0x0c
    float progress;              // +0x10
    float vertical_offset;       // +0x14
    // slot order pinned by the update_track_attachment_follow_state scratch;
    // orientation_b (+0x1c) = player+0x3a0, cross-confirmed by
    // begin_post_follow_carryover's follow_orientation_b read.
    float orientation_a;         // +0x18 (zeroed by the swept entry)
    float orientation_b;         // +0x1c (zeroed by the swept entry)
    float orientation_c;         // +0x20
    float orientation_d;         // +0x24
    float orientation_e;         // +0x28
    Vector3 output_position;     // +0x2c
    Player* player;              // +0x38 back-reference (player+0x3bc)
    char unknown_3c[0x8c - 0x3c];
    // adjacent Player fields, reachable from the follow base because the
    // struct is embedded at player+0x384 (see track_attachment.h header comment):
    float player_velocity_x;     // +0x8c = player+0x410
    float player_velocity_y;     // +0x90 = player+0x414
    float player_velocity_z;     // +0x94 = player+0x418
    char unknown_98;             // +0x98 = player+0x41c boost byte (dead: never set)
    unsigned char attachment_exit_pending; // +0x99 = player+0x41d
};

#endif
