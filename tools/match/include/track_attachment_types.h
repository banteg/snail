// Attachment-follow runtime type views, partial.
// iOS Path.o keeps the template owner as cRPath and the live player traversal
// state as cRPathFollowGoldy.
#ifndef TRACK_ATTACHMENT_TYPES_H
#define TRACK_ATTACHMENT_TYPES_H

#include "attachment_sample.h"
#include "bod_list.h"
#include "bod_types.h"
#include "object_render_types.h"
#include "vector3.h"
#include "vector_types.h"

struct TransformMatrix;
struct LevelSegmentSlot;
class Player;
class FringeObject;

struct PathTemplateStripMesh {
    char unknown_00[0x10];
    int flags;                       // +0x10
};

struct TrackRowCell;

struct AttachmentPathTemplate {
    void allocate_path_template_samples(); // @ 0x41b0a0
    void initialize_worm_path_template_pair(char* texture_path);
    void initialize_cage2_path_template_pair(
        int width_cells_, char* texture_a, char* texture_b, char* vertical_texture);
    void initialize_halfpipe_path_template_pair(
        int unused_scale_bits,
        int width_cells_,
        int unused_kind_arg,
        char* texture_a,
        char* texture_b,
        char* unused_path_version);
    void initialize_looptheloop_path_template_pair(
        float curve_source,
        int width_cells_,
        int side_exit,
        char* texture_a,
        char* texture_b,
        char* cap_texture);
    void initialize_looptheloopw_path_template_pair(
        float curve_source,
        int width_cells_,
        int side_exit,
        char* texture_a,
        char* texture_b,
        char* cap_texture);
    void initialize_loopout_path_template_pair(
        float curve_source,
        int width_cells_,
        int side_exit,
        char* texture_a,
        char* texture_b,
        char* cap_texture);
    void initialize_hump_path_template_pair(
        float curve_source,
        float height_scale,
        int width_cells_,
        int side_exit,
        char* texture_a,
        char* texture_b,
        char* cap_texture);
    void initialize_dump_path_template_pair(
        float curve_source,
        float height_scale,
        int width_cells_,
        int side_exit,
        char* texture_a,
        char* texture_b,
        char* cap_texture);
    void initialize_dip_path_template_pair(
        float curve_source,
        int width_cells_,
        int side_exit,
        char* texture_a,
        char* texture_b,
        char* cap_texture);
    void initialize_screw_path_template_pair(
        int curve_source,
        int width_cells_,
        int side_exit,
        char* texture_a,
        char* texture_b,
        char* cap_texture);
    void initialize_slalom_path_template_pair(
        int curve_source,
        int width_cells_,
        int side_exit,
        char* texture_a,
        char* texture_b,
        char* cap_texture);
    int initialize_loopbow_path_template_pair(
        float curve_scale,
        unsigned int width_cells_arg,
        char unused_mode,
        char* texture_a,
        char* texture_b,
        char* unused_texture);
    void initialize_invert_path_template_pair(
        float radius,
        int width_cells_,
        int side_exit,
        char* texture_a,
        char* texture_b,
        char* vertical_texture);
    void initialize_wibble_path_template_pair(
        float radius,
        int width_cells_,
        int side_exit,
        char* texture_a,
        char* texture_b,
        char* vertical_texture);
    void initialize_start_path_template_pair(
        float length,
        int width_cells_,
        int side_exit,
        char* texture_a,
        char* texture_b,
        char* cap_texture);
    void initialize_turnunder_path_template_pair(
        float turns,
        int width_cells_,
        int side_exit,
        char* texture_a,
        char* texture_b,
        char* vertical_texture);
    void initialize_snake_path_template_pair(
        float scale_arg,
        int width_cells_,
        int side_exit,
        char* texture_a,
        char* texture_b,
        char* cap_texture);
    void initialize_slalombig_path_template_pair(
        int curve_segments,
        int width_cells_,
        int side_exit,
        char* texture_a,
        char* texture_b,
        char* cap_texture);
    void initialize_slalomdouble_path_template_pair(
        int curve_segments,
        int width_cells_,
        int side_exit,
        char* texture_a,
        char* texture_b,
        char* cap_texture);
    void initialize_turnover_path_template_pair(
        float length,
        int width_cells_,
        int side_exit,
        char* texture_a,
        char* texture_b,
        char* cap_texture);
    void initialize_turnoverdouble_path_template_pair(
        float length,
        int width_cells_,
        int side_exit,
        char* texture_a,
        char* texture_b,
        char* cap_texture);
    void initialize_sweep_path_template_pair(
        float scale_arg,
        int width_cells_,
        int side_exit,
        char* texture_a,
        char* texture_b,
        char* cap_texture);
    void initialize_supertramp_path_template_pair(
        float length,
        int width_cells_,
        int side_exit,
        char* texture_a,
        char* texture_b,
        char* cap_texture,
        char* underside_texture);
    void initialize_hill_valley_path_template_pair(
        int width_cells_,
        float height,
        float length,
        int centered,
        char* texture_a,
        char* texture_b,
        char* vertical_texture);
    void initialize_sbend_path_template_pair(
        int width_cells_,
        float height,
        float z_amplitude,
        int centered,
        char* texture_a,
        char* texture_b,
        char* vertical_texture);
    void initialize_p_path_template_pair(
        int variant,
        float scale_arg,
        int width_cells_,
        float start_x,
        float end_x,
        int curve_segments,
        char* texture_a,
        char* texture_b,
        char* cap_texture);
    void initialize_toad_path_template_pair(
        char turn_left, char* texture_a, char* texture_b, char* vertical_texture);
    void initialize_twister_path_template_pair(
        float height,
        int width_cells_,
        int handedness,
        char* texture_a,
        char* texture_b,
        char* vertical_texture);
    void initialize_twister2_path_template_pair(
        float height,
        int width_cells_,
        int handedness,
        char* texture_a,
        char* texture_b,
        char* vertical_texture);
    void build_track_fringe_mesh(char* texture_path, float clamp_side); // @ 0x4246a0, cRPath::BuildFringe
    void build_track_fringe_supertramp_mesh(char* texture_path); // @ 0x424ad0, cRPath::BuildFringeSuperTramp
    void mirror_path_template_pair_x(AttachmentPathTemplate* source); // @ 0x421dc0, cRPath::Mirror
    void try_enter_track_attachment_from_swept_motion(
        float px, float py, float pz,
        float sweep_x, float sweep_y, float sweep_z,
        TrackRowCell* cell); // @ 0x42c770, cRPath::Search
    // Semantically void/thiscall; the non-void return is preserved only for
    // caller scratches that still model the stale EAX value after the call.
    int compute_kind42_attachment_transform(
        float radius, float x, float y, TransformMatrix* transform, float* out_angle);
    bool is_point_inside_track_attachment(
        Vector3 probe, Vector3 swept_motion, TrackRowCell* cell); // @ 0x42ca90, cRPath::SearchPos

    char unknown_00[0x24];
    Object* strip_mesh;               // +0x24
    char unknown_28[0x38 - 0x28];
    int kind;                        // +0x38
    unsigned char is_mirrored_x;     // +0x3c
    char unknown_3d[0x40 - 0x3d];
    int side_exit_mode;              // +0x40
    int segment_count;               // +0x44
    int row_span_count;              // +0x48, runtime rows stamped by P/p entry tiles
    float segment_count_f;           // +0x4c
    float width_or_scale;            // +0x50
    int width_cells;                 // +0x54, integer half-span source
    AttachmentSample* primary_samples; // +0x58
    AttachmentSample* secondary_samples; // +0x5c
    BodBase fringe_mesh_bod;         // +0x60, generated side/fringe mesh object
    union {
        float installed_heading_delta;
        int installed_heading_bits;
    };                               // +0x98
    union {
        // When set, follow progress swaps the installed entry cell to the
        // auxiliary mesh at 3/7 and restores the public mesh at the end.
        unsigned char has_entry_mesh_transition; // +0x9c
        unsigned char special_runtime_flag_9c;   // provenance alias
    };
    char unknown_9d[0xa0 - 0x9d];
    Object* entry_transition_strip_mesh; // +0xa0, borrowed from an auxiliary pair
    Object* entry_base_strip_mesh;       // +0xa4, the public pair's own strip mesh

    int get_path_position_at_node(Vector3* out, int node, int row_index, float* local); // cRPath::GetPos
};

typedef char AttachmentPathTemplate_must_be_0xa8[
    (sizeof(AttachmentPathTemplate) == 0xa8) ? 1 : -1];

struct AttachmentPathTemplatePair {
    AttachmentPathTemplate primary;   // +0x00
    AttachmentPathTemplate secondary; // +0xa8, X-mirrored or explicitly built peer
};

typedef char AttachmentPathTemplatePair_must_be_0x150[
    (sizeof(AttachmentPathTemplatePair) == 0x150) ? 1 : -1];

enum { ATTACHMENT_PATH_TEMPLATE_PAIR_COUNT = 63 };

struct TrackRowCell {
    BodNode bod;                       // +0x00, active/free BOD prefix

    void destroy_sub_lazer_projectile(); // @ 0x439bc0

    Vector3 anchor_position;            // +0x10 (z at +0x18)
    int render_arg_1c;                  // +0x1c, inline BodBase tail
    float render_arg_20;                // +0x20
    Object* object;                     // +0x24, swapped by entry-mesh transitions
    Color4f color;                      // +0x28, alpha at +0x34
    AttachmentPathTemplate* attachment_template_record; // +0x38, installed by P/p entry tiles
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

typedef char TrackRowCell_must_be_0x54[
    (sizeof(TrackRowCell) == 0x54) ? 1 : -1];

struct TrackAttachmentRuntimeRow {       // stride 0xf4
    unsigned int flags;                  // +0x00, 0x40 primary, 0x80 secondary
    RenderableBod primary_body;           // +0x04, embedded authored row actor
    char unknown_7c[0x84 - 0x7c];
    Vector3 authored_object_velocity;     // +0x84, copied from the authored row
    // place_parcels_on_track uses this as an overloaded parcel projection
    // payload: x is lateral/local x, y is incremented as a claim/count lane,
    // and z accumulates absolute row + 0.5 before the attachment projection
    // tail consumes the same vector-shaped storage.
    Vector3 projection_payload;          // +0x90, x/y/z = local/count/row-center during parcel placement
    int parcel_set_id;                   // +0x9c, authored parcel set/payload id
    int attachment_template_index;       // +0xa0, P/p template bank index
    TrackRowCell* primary_attachment_cell; // +0xa4, first P/p entry spanning this row
    TrackRowCell* secondary_attachment_cell; // +0xa8, overlapping P/p entry spanning this row
    float installed_heading_delta;        // +0xac, copied into an entered path template
    BodBase attachment_body;              // +0xb0, embedded attachment/fringe row actor
    float ring_speed;                     // +0xe8, authored ring/effect rate source
    LevelSegmentSlot* source_segment;     // +0xec, borrowed embedded level-segment slot
    int row_event_id;                     // +0xf0, segment-definition/message index
};

typedef char TrackAttachmentRuntimeRow_must_be_0xf4[
    (sizeof(TrackAttachmentRuntimeRow) == 0xf4) ? 1 : -1];

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
    unsigned char flag_3c;       // +0x3c, completion handoff gate
    char unknown_3d[0x40 - 0x3d];
};

typedef char FollowState_must_be_0x40[
    (sizeof(FollowState) == 0x40) ? 1 : -1];

#endif
