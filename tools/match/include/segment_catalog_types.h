// Shared authored segment catalog records, cross-checked by segment parsing
// and level-slot copy paths.
#ifndef SEGMENT_CATALOG_TYPES_H
#define SEGMENT_CATALOG_TYPES_H

#include "vector3.h"

union AuthoredFloatBits {
    int bits;
    float value;
};

// Parser-owned metadata bits stored with each authored segment row. Bit 0x08
// is intentionally shared: 3DModel Velocity= and Path= both set it.
enum AuthoredSegmentRowFlag {
    AUTHORED_SEGMENT_ROW_FLAG_PARCEL = 0x0001,
    AUTHORED_SEGMENT_ROW_FLAG_3D_MODEL = 0x0002,
    AUTHORED_SEGMENT_ROW_FLAG_STAR_MARKER = 0x0004,
    AUTHORED_SEGMENT_ROW_FLAG_PATH_OR_MODEL_VELOCITY = 0x0008,
    AUTHORED_SEGMENT_ROW_FLAG_NO_FALL = 0x0100,
    AUTHORED_SEGMENT_ROW_FLAG_RING_NONE = 0x0200,
    AUTHORED_SEGMENT_ROW_FLAG_RING_NORMAL = 0x0400,
    AUTHORED_SEGMENT_ROW_FLAG_RING_EXPLODE = 0x0800,
    AUTHORED_SEGMENT_ROW_FLAG_RING_SLOW = 0x1000,
    AUTHORED_SEGMENT_ROW_FLAG_RING_POWER_UP = 0x2000,
    AUTHORED_SEGMENT_ROW_FLAG_JETPACK_OFF = 0x8000,
};

struct AuthoredSegmentRow {
    int flags;                     // +0x00, AuthoredSegmentRowFlag bits
    int parcel_set_id;             // +0x04
    Vector3 local_position;        // +0x08
    int object_id;                 // +0x14
    Vector3 object_position;       // +0x18
    Vector3 object_velocity;       // +0x24
    int path_template_index;       // +0x30
    AuthoredFloatBits ring_speed;  // +0x34

    Vector3* parcel_position()
    {
        return &local_position;
    }
};

typedef char AuthoredSegmentRow_must_be_0x38[
    (sizeof(AuthoredSegmentRow) == 0x38) ? 1 : -1];

struct SegmentCatalogEntry {
    char display_name[0x40];       // +0x00, copied from Name:'...'
    char filename[0x40];           // +0x40, copied from Segments/*.txt enumeration
    int id;                        // +0x80
    int row_count;                 // +0x84
    char glyph_columns[0x100][8];  // +0x88, column-major source grid
    AuthoredSegmentRow rows[256];  // +0x888, fills the entry through +0x4088
};

typedef char SegmentCatalogEntry_must_be_0x4088[
    (sizeof(SegmentCatalogEntry) == 0x4088) ? 1 : -1];

// Root-owned authored-definition catalog. The constructor starts its 150
// records four bytes after the receiver and their exact extent reaches the
// following parcel pool, proving the leading count plus embedded entry array.
class SMTracks {
public:
    void load_segment_definitions(); // @ 0x448160
    void load_level_definitions(); // @ 0x448900, receiver unused by body

    int count; // +0x00
    SegmentCatalogEntry entries[150]; // +0x04
};

typedef char SMTracks_must_be_0x25cfb4[
    (sizeof(SMTracks) == 0x25cfb4) ? 1 : -1];

// Windows cRSubSegment layout. Unlike later iOS ports, Windows owns its glyph
// and authored-row storage inline.
struct SubSegment {
    int row_base;                  // +0x00
    int row_count;                 // +0x04
    unsigned char visited;         // +0x08, random-segment selection latch
    char unknown_09[0x0c - 0x09];
    int path_index;                // +0x0c
    char* source_name;             // +0x10
    char glyph_rows[8][0x100];     // +0x14
    AuthoredSegmentRow rows[256];  // +0x814
    AuthoredFloatBits angle_radians; // +0x4014, optional Angle=
    char message_text[0x4218 - 0x4018]; // +0x4018, optional Message=
    AuthoredFloatBits message_duration; // +0x4218, optional Duration=
    int message_sample_id;         // +0x421c, optional Sample=
};

typedef char SubSegment_must_be_0x4220[
    (sizeof(SubSegment) == 0x4220) ? 1 : -1];

// Windows layout of the authored cRSubSegmentRaw records named by the iOS
// cRSubTracks::Init(cRSubSegmentRaw**) symbol.
struct SubSegmentRaw {
    int row_count;                 // +0x00, filled after measuring row 0
    int metadata_words[6];         // +0x04, authored static metadata unused here
    int path_index;                // +0x1c
    char* source_name;             // +0x20
    char* marker_row;              // +0x24, one '*' across the segment width
    char* glyph_rows[8];           // +0x28
};

typedef char SubSegmentRaw_must_be_0x48[
    (sizeof(SubSegmentRaw) == 0x48) ? 1 : -1];

#endif
