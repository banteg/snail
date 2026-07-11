#ifndef SEGMENT_CATALOG_TYPES_H
#define SEGMENT_CATALOG_TYPES_H

typedef unsigned char uint8_t;
typedef int int32_t;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Color4f {
    float r;
    float g;
    float b;
    float a;
} Color4f;

typedef union AuthoredFloatBits {
    int32_t bits;
    float value;
} AuthoredFloatBits;

typedef struct AuthoredSegmentRow {
    int32_t flags;
    int32_t parcel_set_id;
    Vec3 local_position;
    int32_t object_id;
    Vec3 object_position;
    Vec3 object_velocity;
    int32_t path_template_index;
    AuthoredFloatBits ring_speed;
} AuthoredSegmentRow;

typedef struct SegmentCatalogEntry {
    char display_name[0x40];
    char filename[0x40];
    int32_t id;
    int32_t row_count;
    char glyph_columns[0x100][8];
    AuthoredSegmentRow rows[255];
    uint8_t unknown_4050[0x4088 - 0x4050];
} SegmentCatalogEntry;

typedef struct SMTracks {
    int32_t count;
    SegmentCatalogEntry entries[150];
} SMTracks;

/* Windows cRSubSegment with inline glyph and authored-row storage. */
typedef struct SubSegment {
    int32_t row_base;
    int32_t row_count;
    int32_t visited;
    int32_t path_index;
    char* source_name;
    char glyph_rows[8][0x100];
    AuthoredSegmentRow rows[256];
    AuthoredFloatBits angle_radians;
    char message_text[0x4218 - 0x4018];
    AuthoredFloatBits message_duration;
    int32_t message_sample_id;
} SubSegment;

typedef struct SubTracks {
    int32_t segment_count;
    SubSegment segment_slots[100];
    SubSegment first_segment;
    SubSegment last_segment;
    int32_t random_length;
    uint8_t random_enabled;
    uint8_t unknown_1a58c9[0x1a58cc - 0x1a58c9];
    Color4f fringe_color;
    char level_display_name[0x80];
    float selected_speed;
    float garbage_frequency;
    float salt_frequency;
    int32_t landscape_script_index;
    int32_t parcel_count;
    int32_t track_texture_set;
    int32_t parcel_quota;
} SubTracks;

/* Windows layout of the cRSubSegmentRaw parameter records. */
typedef struct SubSegmentRaw {
    int32_t row_count;
    uint8_t unknown_04[0x18];
    int32_t path_index;
    char* source_name;
    int32_t unknown_24;
    char* glyph_rows[8];
} SubSegmentRaw;

#endif
