// Shared authored segment catalog records, cross-checked by segment parsing
// and level-slot copy paths.
#ifndef SEGMENT_CATALOG_TYPES_H
#define SEGMENT_CATALOG_TYPES_H

#include "vector3.h"

union AuthoredFloatBits {
    int bits;
    float value;
};

struct AuthoredSegmentRow {
    int flags;                     // +0x00
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
    AuthoredSegmentRow rows[255];  // +0x888
    char unknown_4050[0x4088 - 0x4050];
};

typedef char SegmentCatalogEntry_must_be_0x4088[
    (sizeof(SegmentCatalogEntry) == 0x4088) ? 1 : -1];

// Root-owned authored-definition catalog. The constructor starts its 150
// records four bytes after the receiver and their exact extent reaches the
// following parcel pool, proving the leading count plus embedded entry array.
class SegmentCatalog {
public:
    int load_segment_definitions(); // @ 0x448160
    int load_level_definitions(); // @ 0x448900, receiver unused by body

    int count; // +0x00
    SegmentCatalogEntry entries[150]; // +0x04
};

typedef char SegmentCatalog_must_be_0x25cfb4[
    (sizeof(SegmentCatalog) == 0x25cfb4) ? 1 : -1];

// Windows cRSubSegment layout. Unlike later iOS ports, Windows owns its glyph
// and authored-row storage inline.
struct SubSegment {
    int row_base;                  // +0x00
    int row_count;                 // +0x04
    int visited;                   // +0x08
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
    char unknown_04[0x18];
    int path_index;                // +0x1c
    char* source_name;             // +0x20
    int unknown_24;                // +0x24
    char* glyph_rows[8];           // +0x28
};

typedef char SubSegmentRaw_must_be_0x48[
    (sizeof(SubSegmentRaw) == 0x48) ? 1 : -1];

#endif
