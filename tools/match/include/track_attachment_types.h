// Authored cRPath records and attachment-follow runtime views. Windows stores
// 126 exact 0xa8-byte Path owners as 63 primary/secondary pairs; iOS Path.o
// preserves the cRPath methods and cRPathFollowGoldy traversal vocabulary.
#ifndef TRACK_ATTACHMENT_TYPES_H
#define TRACK_ATTACHMENT_TYPES_H

#include "attachment_sample.h"
#include "bod_list.h"
#include "bod_types.h"
#include "fringe_fwd.h"
#include "object_render_types.h"
#include "sub_loc_fwd.h"
#include "vector3.h"
#include "vector_types.h"

struct TransformMatrix;
struct SubSegment;
class Player;

struct PathTemplateStripMesh {
    char unknown_00[0x10];
    int flags;                       // +0x10
};

struct Path : public BodBase {
    Path* initialize_path_template_record_pair(); // @ 0x4085c0
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
    void mirror_path_template_pair_x(Path* source); // @ 0x421dc0, cRPath::Mirror
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

    int kind;                        // +0x38, after the inherited BodBase
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

    void get_path_position_at_node(
        Vector3& out, int node, int row_index, Vector3& local); // @ 0x42b9c0, void cRPath::GetPos
};

typedef char Path_must_be_0xa8[
    (sizeof(Path) == 0xa8) ? 1 : -1];

struct PathPair {
    Path primary;   // +0x00
    Path secondary; // +0xa8, X-mirrored or explicitly built peer
};

typedef char PathPair_must_be_0x150[
    (sizeof(PathPair) == 0x150) ? 1 : -1];

enum {
    PATH_PAIR_COUNT = 63,
    PATH_COUNT = PATH_PAIR_COUNT * 2,
};

// Authored runtime-grid cell owner. iOS preserves this class as cRSubLoc;
// its cRSubLoc::Yi() accessor performs the same lane/slab row-index recovery
// as the exact Windows helper below. The Windows layout is 0x54 bytes.
struct SubLoc {
    SubLoc* initialize_sub_loc(); // @ 0x4088c0, cRSubLoc constructor wrapper

    BodNode bod;                       // +0x00, active/free BOD prefix

    void remove_sub_loc(); // @ 0x439bc0, cRSubLoc::Remove
    void update_sub_loc(); // @ 0x439d50, cRSubLoc::AI
    unsigned char is_sub_loc_floor(); // @ 0x439a40, cRSubLoc::IsFloor
    unsigned char is_sub_loc_ramp(); // @ 0x439a70, cRSubLoc::IsRamp
    unsigned char is_sub_loc_empty(); // @ 0x439ab0, cRSubLoc::IsEmpty
    unsigned char is_sub_loc_slide(); // @ 0x439ad0, cRSubLoc::IsSlide

    Vector3 anchor_position;            // +0x10 (z at +0x18)
    float render_arg_1c;                // +0x1c, inline BodBase texture-u argument
    float render_arg_20;                // +0x20
    Object* object;                     // +0x24, swapped by entry-mesh transitions
    Color4f color;                      // +0x28, alpha at +0x34
    Path* attachment_template_record; // +0x38, installed by P/p entry tiles
    unsigned char tile_id;              // +0x3c
    unsigned char tile_flags_3d;        // +0x3d
    char unknown_3e[0x40 - 0x3e];
    unsigned int lane_and_flags;        // +0x40, unsigned packed lane/variant/lifecycle flags
    Fringe* fringe_front;               // +0x44, borrowed from FringeManager
    Fringe* fringe_right;               // +0x48
    Fringe* fringe_left;                // +0x4c
    Fringe* fringe_back;                // +0x50

    int get_track_cell_row_index(); // @ 0x447040, cRSubLoc::Yi
};

typedef char SubLoc_must_be_0x54[(sizeof(SubLoc) == 0x54) ? 1 : -1];

// Owned moving model embedded in each SubRow. iOS preserves the authored
// class and callback as cRRowModel::AI().
class RowModel : public RenderableBod {
public:
    void update_row_model(); // @ 0x443070, cRRowModel::AI

    char unknown_78[0x80 - 0x78];
    Vector3 velocity; // +0x80, outer SubRow +0x84
};

typedef char RowModel_must_be_0x8c[(sizeof(RowModel) == 0x8c) ? 1 : -1];

// Authored per-track-row runtime owner. The Windows constructor ledger names
// the complete 3200-entry slab cRSubRow and reports 0xbea00 bytes, fixing one
// SubRow at 0xf4 bytes. The historical matcher name remains an alias below.
struct SubRow {                          // stride 0xf4
    SubRow* initialize_track_row_runtime(); // @ 0x408590

    unsigned int flags;                  // +0x00, 0x40 primary, 0x80 secondary
    RowModel row_model;                   // +0x04, ends at +0x90
    // place_parcels_on_track uses this as an overloaded parcel projection
    // payload: x is lateral/local x, y is incremented as a claim/count lane,
    // and z accumulates absolute row + 0.5 before the attachment projection
    // tail consumes the same vector-shaped storage.
    Vector3 projection_payload;          // +0x90, x/y/z = local/count/row-center during parcel placement
    int parcel_set_id;                   // +0x9c, authored parcel set/payload id
    int attachment_template_index;       // +0xa0, P/p template bank index
    SubLoc* primary_attachment_cell; // +0xa4, first P/p entry spanning this row
    SubLoc* secondary_attachment_cell; // +0xa8, overlapping P/p entry spanning this row
    float installed_heading_delta;        // +0xac, copied into an entered path template
    BodBase attachment_body;              // +0xb0, embedded attachment/fringe row actor
    float ring_speed;                     // +0xe8, authored ring/effect rate source
    SubSegment* source_segment;           // +0xec, borrowed embedded subsegment
    int row_event_id;                     // +0xf0, completed-segment event-definition index
};

typedef SubRow TrackAttachmentRuntimeRow;

typedef char SubRow_must_be_0xf4[(sizeof(SubRow) == 0xf4) ? 1 : -1];

class FollowState {
public:
    Path* begin_track_attachment_follow_state(
        SubLoc* source_cell, const Vector3* world_position, Player* player); // @ 0x420c40
    int update_track_attachment_follow_state(
        float rate, Vector3* out_position, Vector3* motion); // @ 0x420cb0

    unsigned char active;        // +0x00
    char unknown_01[3];
    Path* template_record; // +0x04
    SubLoc* source_cell;         // +0x08
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
