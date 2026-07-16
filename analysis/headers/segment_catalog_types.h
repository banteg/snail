#ifndef SEGMENT_CATALOG_TYPES_H
#define SEGMENT_CATALOG_TYPES_H

typedef unsigned char uint8_t;
typedef int int32_t;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct tColour {
    float r;
    float g;
    float b;
    float a;
} tColour;

typedef union AuthoredFloatBits {
    int32_t bits;
    float value;
} AuthoredFloatBits;

/* Writable level-definition text storage at 0x74ec78. The next independently
 * referenced global begins at 0x751478, and no interior address is referenced. */
typedef char LevelFileTextBuffer[0x2800];

typedef enum AuthoredSegmentRowFlag {
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
} AuthoredSegmentRowFlag;

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
    AuthoredSegmentRow rows[256];
} SegmentCatalogEntry;

/* The native importer strides 0x4088 bytes from the SMTracks base, leaving
 * its EDX cursor four bytes before the selected entry. At index zero the
 * prefix is SMTracks::count; at later indices it overlaps the previous
 * entry's final word. Only entry is consumed through this analysis view. */
typedef struct SegmentCatalogEntryAnchor {
    int32_t stride_prefix_word;
    SegmentCatalogEntry entry;
} SegmentCatalogEntryAnchor;

typedef struct SMTracks {
    int32_t count;
    SegmentCatalogEntry entries[150];
} SMTracks;

/* Windows cRSubSegment with inline glyph and authored-row storage. */
typedef struct SubSegment {
    int32_t row_base;
    int32_t row_count;
    uint8_t visited;
    uint8_t unknown_09[0x0c - 0x09];
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
    tColour fringe_color;
    char level_display_name[0x80];
    AuthoredFloatBits selected_speed;
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
    int32_t metadata_words[6];
    int32_t path_index;
    char* source_name;
    char* marker_row;
    char* glyph_rows[8];
} SubSegmentRaw;

#endif
