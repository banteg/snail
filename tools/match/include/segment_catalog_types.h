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
    AuthoredFloatBits local_x;     // +0x08
    AuthoredFloatBits local_y;     // +0x0c
    AuthoredFloatBits local_z;     // +0x10
    int object_id;                 // +0x14
    AuthoredFloatBits object_position_x; // +0x18
    AuthoredFloatBits object_position_y; // +0x1c
    AuthoredFloatBits object_position_z; // +0x20
    AuthoredFloatBits object_velocity_x; // +0x24
    AuthoredFloatBits object_velocity_y; // +0x28
    AuthoredFloatBits object_velocity_z; // +0x2c
    int path_template_index;       // +0x30
    AuthoredFloatBits ring_speed;  // +0x34

    Vector3* parcel_position()
    {
        return (Vector3*)&local_x;
    }
};

typedef char AuthoredSegmentRow_must_be_0x38[
    (sizeof(AuthoredSegmentRow) == 0x38) ? 1 : -1];

struct SegmentCatalogEntry {
    int count_alias;               // +0x00 on entry 0; overlaps catalog count
    char display_name[0x40];       // +0x04, copied from Name:'...'
    char filename[0x40];           // +0x44, copied from Segments/*.txt enumeration
    int id;                        // +0x84
    int row_count;                 // +0x88
    char glyph_columns[0x100][8];  // +0x8c, column-major source grid
    AuthoredSegmentRow rows[255];  // +0x88c
    char unknown_4054[0x4088 - 0x4054];
};

typedef char SegmentCatalogEntry_must_be_0x4088[
    (sizeof(SegmentCatalogEntry) == 0x4088) ? 1 : -1];

struct LevelSegmentSlot {
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

typedef char LevelSegmentSlot_must_be_0x4220[
    (sizeof(LevelSegmentSlot) == 0x4220) ? 1 : -1];

struct BuiltinSegmentDefinition {
    int row_count;                 // +0x00, filled after measuring row 0
    char unknown_04[0x18];
    int path_index;                // +0x1c
    char* source_name;             // +0x20
    int unknown_24;                // +0x24
    char* glyph_rows[8];           // +0x28
};

class LevelSegmentSlotStore {
public:
    int count;                     // +0x00
    LevelSegmentSlot slots[103];   // +0x04

    char* load_builtin_segment_definitions(BuiltinSegmentDefinition** builtins);
};

#endif
