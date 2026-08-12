// Authored cRPath records and attachment-follow runtime views. Windows stores
// 126 exact 0xa8-byte owners as 63 primary/secondary pairs; Android and iOS
// preserve the cRPath methods and cRPathFollowGoldy traversal vocabulary.
#ifndef TRACK_ATTACHMENT_TYPES_H
#define TRACK_ATTACHMENT_TYPES_H

#include "attachment_sample.h"
#include "bod_list.h"
#include "bod_types.h"
#include "fringe_fwd.h"
#include "object_render_types.h"
#include "player_fwd.h"
#include "sub_loc_tile_ids.h"
#include "sub_loc_fwd.h"
#include "transform_matrix_fwd.h"
#include "vector3.h"
#include "vector_types.h"

struct cRSubSegment;
typedef cRSubSegment SubSegment;

// Windows-native cRPath template discriminants. Android/iOS constructor
// symbols corroborate the authored identities, but their numeric values are
// not assumed to be ABI-compatible with this Windows enum.
enum PathTemplateKind {
    PATH_TEMPLATE_KIND_LOOPTHELOOP_FAMILY = 0x00,
    PATH_TEMPLATE_KIND_LOOPTHELOOPW = 0x06,
    PATH_TEMPLATE_KIND_CAGE2 = 0x0f,
    PATH_TEMPLATE_KIND_FAMILY_10 = 0x10,
    PATH_TEMPLATE_KIND_FAMILY_11 = 0x11,
    PATH_TEMPLATE_KIND_DIP = 0x14,
    PATH_TEMPLATE_KIND_SCREW = 0x15,
    PATH_TEMPLATE_KIND_SLALOM = 0x16,
    PATH_TEMPLATE_KIND_SLALOMBIG = 0x17,
    PATH_TEMPLATE_KIND_WORM = 0x18,
    PATH_TEMPLATE_KIND_LOOPOUT = 0x19,
    PATH_TEMPLATE_KIND_SWEEP = 0x1c,
    PATH_TEMPLATE_KIND_SNAKE = 0x1d,
    PATH_TEMPLATE_KIND_SUPERTRAMP = 0x1f,
    PATH_TEMPLATE_KIND_SLALOMDOUBLE = 0x20,
    PATH_TEMPLATE_KIND_START = 0x24,
    PATH_TEMPLATE_KIND_TURNOVER = 0x25,
    PATH_TEMPLATE_KIND_TURNOVERDOUBLE = 0x26,
    PATH_TEMPLATE_KIND_TURNUNDER_TOAD_FAMILY = 0x27,
    PATH_TEMPLATE_KIND_WIBBLE = 0x28,
    PATH_TEMPLATE_KIND_INVERT = 0x29,
    PATH_TEMPLATE_KIND_NONLINEAR_42 = 0x2a,
    PATH_TEMPLATE_KIND_TWISTER = 0x2b,
    PATH_TEMPLATE_KIND_TWISTER2 = 0x2d,
};

struct cRPath : public BodBase {
    cRPath* initialize_path_template_record_pair(); // @ 0x4085c0
    void GetNodes(); // @ 0x41b0a0
    void initialize_worm_path_template_pair(char* texture_path);
    void initialize_cage2_path_template_pair(
        int width_cells_, char* texture_a, char* texture_b, char* vertical_texture);
    void initialize_halfpipe_path_template_pair(
        float scale,
        int width_cells_,
        bool side_exit,
        char* texture_a,
        char* texture_b,
        char* vertical_texture);
    void initialize_looptheloop_path_template_pair(
        float curve_source,
        int width_cells_,
        bool side_exit,
        char* texture_a,
        char* texture_b,
        char* cap_texture);
    void initialize_looptheloopw_path_template_pair(
        float curve_source,
        int width_cells_,
        bool side_exit,
        char* texture_a,
        char* texture_b,
        char* cap_texture);
    void initialize_loopout_path_template_pair(
        float curve_source,
        int width_cells_,
        bool side_exit,
        char* texture_a,
        char* texture_b,
        char* cap_texture);
    void initialize_hump_path_template_pair(
        float curve_source,
        float height_scale,
        int width_cells_,
        bool side_exit,
        char* texture_a,
        char* texture_b,
        char* cap_texture);
    void initialize_dump_path_template_pair(
        float curve_source,
        float height_scale,
        int width_cells_,
        bool side_exit,
        char* texture_a,
        char* texture_b,
        char* cap_texture);
    void initialize_dip_path_template_pair(
        float curve_source,
        int width_cells_,
        bool side_exit,
        char* texture_a,
        char* texture_b,
        char* cap_texture);
    void initialize_screw_path_template_pair(
        int curve_source,
        int width_cells_,
        bool side_exit,
        char* texture_a,
        char* texture_b,
        char* cap_texture);
    void initialize_slalom_path_template_pair(
        int curve_source,
        int width_cells_,
        bool side_exit,
        char* texture_a,
        char* texture_b,
        char* cap_texture);
    void initialize_loopbow_path_template_pair(
        float curve_scale,
        unsigned int width_cells_arg,
        bool mode,
        char* texture_a,
        char* texture_b,
        char* vertical_texture);
    void initialize_invert_path_template_pair(
        float radius,
        int width_cells_,
        bool side_exit,
        char* texture_a,
        char* texture_b,
        char* vertical_texture);
    void initialize_wibble_path_template_pair(
        float radius,
        int width_cells_,
        bool side_exit,
        char* texture_a,
        char* texture_b,
        char* vertical_texture);
    void initialize_start_path_template_pair(
        float length,
        int width_cells_,
        bool side_exit,
        char* texture_a,
        char* texture_b,
        char* cap_texture);
    void initialize_turnunder_path_template_pair(
        float turns,
        int width_cells_,
        bool side_exit,
        char* texture_a,
        char* texture_b,
        char* vertical_texture);
    void initialize_snake_path_template_pair(
        float scale_arg,
        int width_cells_,
        bool side_exit,
        char* texture_a,
        char* texture_b,
        char* cap_texture);
    void initialize_slalombig_path_template_pair(
        int curve_segments,
        int width_cells_,
        bool side_exit,
        char* texture_a,
        char* texture_b,
        char* cap_texture);
    void initialize_slalomdouble_path_template_pair(
        int curve_segments,
        int width_cells_,
        bool side_exit,
        char* texture_a,
        char* texture_b,
        char* cap_texture);
    void initialize_turnover_path_template_pair(
        float length,
        int width_cells_,
        bool side_exit,
        char* texture_a,
        char* texture_b,
        char* cap_texture);
    void initialize_turnoverdouble_path_template_pair(
        float length,
        int width_cells_,
        bool side_exit,
        char* texture_a,
        char* texture_b,
        char* cap_texture);
    void initialize_sweep_path_template_pair(
        float scale_arg,
        int width_cells_,
        bool side_exit,
        char* texture_a,
        char* texture_b,
        char* cap_texture);
    void initialize_supertramp_path_template_pair(
        float length,
        int width_cells_,
        bool side_exit,
        char* texture_a,
        char* texture_b,
        char* unused_texture,
        char* cap_texture);
    void initialize_hill_valley_path_template_pair(
        int width_cells_,
        float height,
        float length,
        bool centered,
        char* texture_a,
        char* texture_b,
        char* vertical_texture);
    void initialize_sbend_path_template_pair(
        int width_cells_,
        float height,
        float z_amplitude,
        bool centered,
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
        bool turn_left, char* texture_a, char* texture_b, char* vertical_texture);
    void initialize_twister_path_template_pair(
        float height,
        int width_cells_,
        bool handedness,
        char* texture_a,
        char* texture_b,
        char* vertical_texture);
    void initialize_twister2_path_template_pair(
        float height,
        int width_cells_,
        bool handedness,
        char* texture_a,
        char* texture_b,
        char* vertical_texture);
    void build_track_fringe_mesh(char* texture_path, float clamp_side); // @ 0x4246a0, cRPath::BuildFringe
    void build_track_fringe_supertramp_mesh(char* texture_path); // @ 0x424ad0, cRPath::BuildFringeSuperTramp
    void Mirror(cRPath* source); // @ 0x421dc0
    void __fastcall CalcLengthZ(); // @ 0x42c600, cRPath::CalcLengthZ
    void try_enter_track_attachment_from_swept_motion(
        float px, float py, float pz,
        float sweep_x, float sweep_y, float sweep_z,
        cRSubLoc* cell); // @ 0x42c770, cRPath::Search
    void compute_kind42_attachment_transform(
        float radius, float x, float y, TransformMatrix* transform, float* out_angle);
    bool SearchPos(
        tVector probe, tVector swept_motion, cRSubLoc* cell); // @ 0x42ca90

    PathTemplateKind kind;           // +0x38, after the inherited BodBase
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
    // When set, follow progress swaps the installed entry cell to the
    // auxiliary mesh at 3/7 and restores the public mesh at the end.
    unsigned char has_entry_mesh_transition; // +0x9c
    char unknown_9d[0xa0 - 0x9d];
    Object* entry_transition_strip_mesh; // +0xa0, borrowed from an auxiliary pair
    Object* entry_base_strip_mesh;       // +0xa4, the public pair's own strip mesh

    void GetPos(
        tVector& out, int node, int row_index, tVector& local); // @ 0x42b9c0
};

typedef char cRPath_must_be_0xa8[
    (sizeof(cRPath) == 0xa8) ? 1 : -1];

// Compatibility vocabulary for older scratches and analysis notes. Mobile
// symbols establish cRPath as the authored identity; Windows establishes the
// complete layout and ABI.
typedef cRPath Path;

struct PathPair {
    cRPath primary;   // +0x00
    cRPath secondary; // +0xa8, X-mirrored or explicitly built peer
};

typedef char PathPair_must_be_0x150[
    (sizeof(PathPair) == 0x150) ? 1 : -1];

enum {
    PATH_PAIR_COUNT = 63,
    PATH_COUNT = PATH_PAIR_COUNT * 2,
    SUBGAME_RUNTIME_ROW_CAPACITY = 3200,
    SUBGAME_TRACK_LANE_COUNT = 8,
    SUBLOC_FRINGE_COUNT = 4,
};

// Cardinal openness is produced by select_track_tile_edge_variants from the
// four adjacent cells. The lane/row names describe the stable slab topology;
// previous/next map to left/right and back/front in the rendered track.
enum SubLocOpenEdgeFlag {
    SUBLOC_OPEN_PREVIOUS_ROW = 0x01,
    SUBLOC_OPEN_NEXT_ROW = 0x02,
    SUBLOC_OPEN_NEXT_LANE = 0x04,
    SUBLOC_OPEN_PREVIOUS_LANE = 0x08,
    SUBLOC_OPEN_EDGE_MASK = 0x0f,
};

// Packed runtime state at cRSubLoc +0x40. Keep the owning field as a dword:
// these masks have independent producers and consumers rather than a stable
// compiler bitfield layout.
enum SubLocFlag {
    SUBLOC_LANE_INDEX_MASK = 0x0007,
    SUBLOC_FLAG_SUPPRESS_SALT_SPAWN = 0x0008,
    SUBLOC_FLAG_SUPPRESS_GARBAGE_SPAWN = 0x0010,
    SUBLOC_FLAG_RANDOM_HAZARD_BLOCKED =
        SUBLOC_FLAG_SUPPRESS_SALT_SPAWN | SUBLOC_FLAG_SUPPRESS_GARBAGE_SPAWN,
    SUBLOC_FLAG_WARNING_CACHE_FAMILY = 0x0020,
    SUBLOC_FLAG_CACHE_FAMILY_SWAPPED = 0x0040,
    SUBLOC_MERGED_RUN_WIDTH_ONE = 0x0100,
    SUBLOC_MERGED_RUN_WIDTH_REMAINDER_MASK = 0x0e00,
    SUBLOC_MERGED_RUN_WIDTH_MASK = 0x0f00,
    SUBLOC_MERGED_RUN_WIDTH_SHIFT = 8,
    SUBLOC_MERGED_RUN_WIDTH_VALUE_MASK = 0x000f,
    SUBLOC_FLAG_AI_ENABLED = 0x2000,
    SUBLOC_FLAG_UNCACHED_BODY = 0x4000,
    SUBLOC_FLAG_CORNER_OBJECT = 0x8000,
};

// Authored runtime-grid cell owner. iOS preserves this class as cRSubLoc;
// its cRSubLoc::Yi() accessor performs the same lane/slab row-index recovery
// as the exact Windows helper below. Its exact constructor proves the inherited
// BodBase at +0x00 and its world/track anchor is BodBase::position at +0x10.
// The complete Windows layout is 0x54 bytes.
struct cRSubLoc : public BodBase {
    cRSubLoc* initialize_sub_loc(); // @ 0x4088c0, cRSubLoc constructor wrapper

    void Remove(); // @ 0x439bc0
    void AI(); // @ 0x439d50
    bool IsFloor(); // @ 0x439a40
    bool IsRamp(); // @ 0x439a70
    bool IsEmpty(); // @ 0x439ab0
    bool IsSlide(); // @ 0x439ad0

    cRPath* attachment_template_record; // +0x38, installed by P/p entry tiles
    SubLocTileId tile_id;                // +0x3c, SubLocTileIdValue
    unsigned char open_edge_mask;       // +0x3d, SubLocOpenEdgeFlag bits
    char _pad_3e[0x40 - 0x3e];
    unsigned int lane_and_flags;        // +0x40, lane index plus SubLocFlag bits
    union {
        struct {
            Fringe* fringe_front; // +0x44, borrowed from FringeManager
            Fringe* fringe_right; // +0x48
            Fringe* fringe_left;  // +0x4c
            Fringe* fringe_back;  // +0x50
        };
        Fringe* fringes[SUBLOC_FRINGE_COUNT]; // +0x44, directional scan view
    };

    int Yi(); // @ 0x447040
};

typedef char cRSubLoc_must_be_0x54[(sizeof(cRSubLoc) == 0x54) ? 1 : -1];

// Authored moving-model owner embedded in each cRSubRow. Android and iOS both
// preserve the class and callback as cRRowModel::AI().
class cRRowModel : public RenderableBod {
public:
    void AI(); // @ 0x443070

    Vector3 velocity; // +0x80, outer cRSubRow +0x84
};

// Compatibility vocabulary retained for existing Windows-analysis callers.
typedef cRRowModel RowModel;

typedef char cRRowModel_must_be_0x8c[
    (sizeof(cRRowModel) == 0x8c) ? 1 : -1];
typedef char RowModel_must_be_0x8c[(sizeof(RowModel) == 0x8c) ? 1 : -1];

// Runtime row state. The builder copies the authored lanes, then adds parcel
// selection, mirror, attachment-span, and coordinate-space state. The 0x08
// lane remains deliberately overloaded between path metadata and model
// velocity because the authored parser stores both concepts in the same bit.
enum SubRowFlag {
    SUBROW_FLAG_PARCEL_CANDIDATE = 0x0001,
    SUBROW_FLAG_ROW_MODEL_PRESENT = 0x0002,
    SUBROW_FLAG_SUPPRESS_TRACK_RENDER = 0x0004,
    SUBROW_FLAG_PATH_OR_MODEL_VELOCITY = 0x0008,
    SUBROW_FLAG_PARCEL_SPAWN_REQUESTED = 0x0010,
    SUBROW_FLAG_MIRRORED = 0x0020,
    SUBROW_FLAG_PRIMARY_ATTACHMENT = 0x0040,
    SUBROW_FLAG_SECONDARY_ATTACHMENT = 0x0080,
    SUBROW_ATTACHMENT_MASK = 0x00c0,
    SUBROW_FLAG_NO_FALL = 0x0100,
    SUBROW_FLAG_RING_NONE = 0x0200,
    SUBROW_FLAG_RING_NORMAL = 0x0400,
    SUBROW_FLAG_RING_EXPLODE = 0x0800,
    SUBROW_FLAG_RING_SLOW = 0x1000,
    SUBROW_FLAG_RING_POWER_UP = 0x2000,
    SUBROW_FLAG_PARCEL_Z_IS_LOCAL = 0x4000,
    SUBROW_FLAG_JETPACK_OFF = 0x8000,
};

// Authored per-track-row runtime owner. The Windows constructor ledger names
// the complete 3200-entry slab cRSubRow and reports 0xbea00 bytes, fixing one
// cRSubRow at 0xf4 bytes. iOS independently retains cRSubRow* parameters on
// AddParcel and AddRing.
struct cRSubRow {                         // stride 0xf4
    cRSubRow(); // @ 0x408590

    unsigned int flags;                  // +0x00, SubRowFlag bits
    cRRowModel row_model;                 // +0x04, ends at +0x90
    // Authored parcel-local coordinates become the final world-space spawn
    // position in place_parcels_on_track: x mirrors with the row, y gains the
    // one-unit spawn-height offset, and z gains the absolute row center before
    // the attachment projection rewrites x/y (or the complete vector).
    Vector3 parcel_spawn_position;       // +0x90, parcel-local then world-space
    int parcel_set_id;                   // +0x9c, authored parcel set/payload id
    int attachment_template_index;       // +0xa0, P/p template bank index
    cRSubLoc* primary_attachment_cell; // +0xa4, first P/p entry spanning this row
    cRSubLoc* secondary_attachment_cell; // +0xa8, overlapping P/p entry spanning this row
    float installed_heading_delta;        // +0xac, copied into an entered path template
    BodBase attachment_body;              // +0xb0, embedded attachment/fringe row actor
    float ring_speed;                     // +0xe8, authored ring/effect rate source
    SubSegment* source_segment;           // +0xec, borrowed embedded subsegment
    int row_event_id;                     // +0xf0, completed-segment event-definition index
};

// Compatibility vocabulary retained for existing Windows-analysis callers.
typedef cRSubRow SubRow;

typedef char cRSubRow_must_be_0xf4[
    (sizeof(cRSubRow) == 0xf4) ? 1 : -1];
typedef char SubRow_must_be_0xf4[(sizeof(SubRow) == 0xf4) ? 1 : -1];

class cRPathFollowGoldy {
public:
    // VC6 folds this empty owner constructor into the shared body at
    // 0x408600. The cRSubGame constructor passes cRSubGoldy::follow_state exactly.
    cRPathFollowGoldy* noop_runtime_slot_constructor();
    void Init(
        cRSubLoc* source_cell, tVector& world_position, cRSubGoldy* player); // @ 0x420c40
    int update_track_attachment_follow_state(
        float rate, Vector3* out_position, Vector3* motion); // @ 0x420cb0

    unsigned char active;        // +0x00
    char unknown_01[3];
    cRPath* template_record; // +0x04
    cRSubLoc* source_cell;         // +0x08
    int sample_index;            // +0x0c
    float progress;              // +0x10
    float vertical_offset;       // +0x14
    // slot order pinned by the update_track_attachment_follow_state scratch;
    // orientation_b (+0x1c) = player+0x3a0, cross-confirmed by
    // cRSubGoldy::FallingInit's embedded-state read.
    float orientation_a;         // +0x18 (zeroed by the swept entry)
    float orientation_b;         // +0x1c (zeroed by the swept entry)
    // Aggregate assignment from the interpolated transform's up basis is
    // preserved in both Windows and iOS cRPathFollowGoldy::Traverse.
    Vector3 orientation_up;      // +0x20
    Vector3 output_position;     // +0x2c
    cRSubGoldy* player;              // +0x38 back-reference (player+0x3bc)
    unsigned char flag_3c;       // +0x3c, completion handoff gate
    char unknown_3d[0x40 - 0x3d];
};

typedef char cRPathFollowGoldy_must_be_0x40[
    (sizeof(cRPathFollowGoldy) == 0x40) ? 1 : -1];
// Compatibility vocabulary retained for older analysis notes and scratch-local
// views. Android and iOS preserve cRPathFollowGoldy as the authored class name.
typedef cRPathFollowGoldy FollowState;

#endif
