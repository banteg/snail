#ifndef SEGMENT_CATALOG_TYPES_H
#define SEGMENT_CATALOG_TYPES_H

typedef unsigned char uint8_t;
typedef int int32_t;

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
    AuthoredFloatBits local_x;
    AuthoredFloatBits local_y;
    AuthoredFloatBits local_z;
    int32_t object_id;
    AuthoredFloatBits object_position_x;
    AuthoredFloatBits object_position_y;
    AuthoredFloatBits object_position_z;
    AuthoredFloatBits object_velocity_x;
    AuthoredFloatBits object_velocity_y;
    AuthoredFloatBits object_velocity_z;
    int32_t path_template_index;
    AuthoredFloatBits ring_speed;
} AuthoredSegmentRow;

typedef struct SegmentCatalogEntry {
    int32_t count_alias;
    char display_name[0x40];
    char filename[0x40];
    int32_t id;
    int32_t row_count;
    char glyph_columns[0x100][8];
    AuthoredSegmentRow rows[255];
    uint8_t unknown_4054[0x4088 - 0x4054];
} SegmentCatalogEntry;

typedef struct SegmentCatalog {
    SegmentCatalogEntry entries[150];
    int32_t unknown_25cfb0;
} SegmentCatalog;

typedef struct LevelSegmentSlot {
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
} LevelSegmentSlot;

typedef struct LevelDefinitionLoader {
    int32_t segment_count;
    LevelSegmentSlot segment_slots[100];
    LevelSegmentSlot first_segment;
    LevelSegmentSlot last_segment;
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
} LevelDefinitionLoader;

typedef struct BuiltinSegmentDefinition {
    int32_t row_count;
    uint8_t unknown_04[0x18];
    int32_t path_index;
    char* source_name;
    int32_t unknown_24;
    char* glyph_rows[8];
} BuiltinSegmentDefinition;

#endif
