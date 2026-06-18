// load_level_definition_file @ 0x447480 (thiscall, ret 0x4)

#include "sprite.h"

extern char* g_game_base; // data_4df904
extern char* g_current_level_definition_name; // data_74ec74

#define LEVEL_FILE_BUFFER ((char*)&g_current_level_definition_name + 4)

int sprintf(char* buffer, char* format, ...);
int report_errorf(char* format, ...);
int report_warningf(char* format, ...);
int load_file_bytes_from_archive_or_fs(char* path, char* out_buffer, void* out_size);
char* find_case_insensitive_substring(char* needle, char* haystack);
char* advance_to_next_crlf_line(char* cursor); // @ 0x44e690
int parse_next_signed_int(char** cursor);
float parse_next_float32(char** cursor);
void rstrcpy_checked_ascii(char* destination, char* source); // @ 0x44e5b0
int sub_432FC0(char* sample_name);

struct AuthoredSegmentRow {
    int flags;
    int parcel_set_id;
    int local_x_bits;
    int local_y_bits;
    int local_z_bits;
    int object_id;
    int object_position_x_bits;
    int object_position_y_bits;
    int object_position_z_bits;
    int object_velocity_x_bits;
    int object_velocity_y_bits;
    int object_velocity_z_bits;
    int path_template_index;
    int ring_speed_bits;
};

struct LevelSegmentSlot {
    int row_base;                 // +0x00
    int row_count;                // +0x04
    int visited;                  // +0x08
    int path_index;               // +0x0c
    char* source_name;            // +0x10
    char glyph_rows[8][0x100];    // +0x14
    AuthoredSegmentRow rows[256]; // +0x814
    float angle_radians;          // +0x4014, parsed from Angle=
    char message_text[0x4218 - 0x4018]; // +0x4018, parsed from Message=
    float message_duration;       // +0x4218, parsed from Duration=
    int message_sample_id;        // +0x421c, parsed from Sample=
};

typedef char LevelSegmentSlot_must_be_0x4220[
    (sizeof(LevelSegmentSlot) == 0x4220) ? 1 : -1];

class LandscapeScriptBank {
public:
    int load_landscape_script_by_name(char* script_name);
};

struct LevelDefinitionParseBuffers {
    char level_path[512];
    char line_options[128];
    char sample_name[128];
    char segment_name[512];
    char background_name[512];
};

class LevelDefinitionLoader {
public:
    int* load_level_definition_file(char* filename);
    int* copy_segment_definition_to_level_slot(char* segment_name, LevelSegmentSlot* slot);

    int segment_count;                 // +0x000000
    LevelSegmentSlot segment_slots[100]; // +0x000004
    LevelSegmentSlot first_segment;    // +0x19d484
    LevelSegmentSlot last_segment;     // +0x1a16a4
    int random_length;                 // +0x1a58c4
    unsigned char random_enabled;      // +0x1a58c8
    char unknown_1a58c9[0x1a58cc - 0x1a58c9];
    Color4f fringe_color;              // +0x1a58cc
    char level_display_name[0x80];     // +0x1a58dc, parsed from Name:'...'
    float selected_speed;              // +0x1a595c
    float garbage_frequency;           // +0x1a5960
    float salt_frequency;              // +0x1a5964
    int landscape_script_index;        // +0x1a5968
    int parcel_count;                  // +0x1a596c
    int track_texture_set;             // +0x1a5970
    int parcel_quota;                  // +0x1a5974
};

typedef char LevelDefinitionLoader_layout_check[
    (sizeof(LevelDefinitionLoader) == 0x1a5978) ? 1 : -1];

int* LevelDefinitionLoader::load_level_definition_file(char* filename)
{
    char* cursor;
    char* line_cursor;
    int parsed_int;
    char* segments_end;
    LevelDefinitionParseBuffers buffers;

#define level_path buffers.level_path
#define line_options buffers.line_options
#define sample_name buffers.sample_name
#define segment_name buffers.segment_name
#define background_name buffers.background_name

    g_current_level_definition_name = filename;
    sprintf(level_path, "Levels/%s", filename);
    if (!load_file_bytes_from_archive_or_fs(level_path, LEVEL_FILE_BUFFER, (void*)0)) {
        report_errorf("Cannot find %s reverting to default.txt", level_path);
        sprintf(level_path, "Levels/Default.txt");
        load_file_bytes_from_archive_or_fs(level_path, LEVEL_FILE_BUFFER, (void*)0);
    }

    cursor = find_case_insensitive_substring("Name:'", LEVEL_FILE_BUFFER);
    if (cursor == 0) {
        report_errorf("Cannot find Name:' in %s", level_path);
        cursor = 0;
    }

    cursor = find_case_insensitive_substring("'", cursor) + 1;
    char* name_out = level_display_name;
    char ch = *cursor;
    while (*cursor != '\'') {
        if (ch < 32)
            break;
        *name_out++ = ch;
        cursor++;
        ch = *cursor;
    }
    *name_out = 0;

    if (*(g_game_base + 0x12d4638) == 0) {
        cursor = find_case_insensitive_substring("Arcade", filename);
        if (cursor != 0) {
            cursor = find_case_insensitive_substring("e", cursor) + 1;
            int galaxy_index = 0x2a0 * parse_next_signed_int(&cursor);
            sprintf(g_game_base + galaxy_index + 0x12d4668, "%s", level_display_name);

            cursor = find_case_insensitive_substring("GalaxyText:", LEVEL_FILE_BUFFER);
            if (cursor == 0) {
                report_warningf("Cannot find GalaxyText: in %s", filename);
                rstrcpy_checked_ascii(g_game_base + galaxy_index + 0x12d46e8, "TEXT MISSING");
            } else {
                cursor = find_case_insensitive_substring("{", cursor);
                if (cursor == 0) {
                    report_warningf("Cannot find { for GalaxyText: in %s", filename);
                    rstrcpy_checked_ascii(g_game_base + galaxy_index + 0x12d46e8, "TEXT ERROR { MISSING");
                } else {
                    cursor = advance_to_next_crlf_line(cursor);
                    char* close_brace = find_case_insensitive_substring("}", cursor);
                    if (close_brace == 0) {
                        report_warningf("Cannot find } for GalaxyText: in %s", filename);
                        rstrcpy_checked_ascii(g_game_base + galaxy_index + 0x12d46e8, "TEXT ERROR } MISSING");
                    } else {
                        unsigned int text_end = (unsigned int)(close_brace - 2);
                        char* text_out = g_game_base + galaxy_index + 0x12d46e8;
                        char* text_cursor = cursor;
                        while ((unsigned int)cursor < text_end) {
                            if (*text_cursor < 32) {
                                *text_out++ = '>';
                                text_cursor = cursor;
                                if (*cursor < 32) {
                                    do {
                                        text_cursor++;
                                        cursor = text_cursor;
                                    } while (*text_cursor < 32);
                                }
                            }
                            *text_out++ = *text_cursor;
                            text_cursor = cursor + 1;
                            cursor = text_cursor;
                        }
                        *text_out = 0;
                    }
                }
            }
        }
    }

    cursor = find_case_insensitive_substring("Random:yes", LEVEL_FILE_BUFFER);
    if (cursor != 0) {
        random_enabled = 1;
        cursor = find_case_insensitive_substring("Length:", LEVEL_FILE_BUFFER);
        if (cursor == 0)
            return (int*)report_errorf("Cannot Length: in %s", level_path);
        cursor = find_case_insensitive_substring(":", cursor) + 1;
        random_length = 0;
        ch = *cursor;
        if (ch != 'a' && ch != 'A' && ch >= '0') {
            do {
                if (ch > '9')
                    break;
                cursor++;
                random_length = ch + 10 * random_length - '0';
                ch = *cursor;
            } while (*cursor >= '0');
        }
    } else {
        random_enabled = 0;
        random_length = 0;
    }

    cursor = find_case_insensitive_substring("Background:", LEVEL_FILE_BUFFER);
    if (cursor == 0)
        return (int*)report_errorf("No Background: in %s", level_path);
    cursor = find_case_insensitive_substring(":", cursor) + 1;
    char* background_out = background_name;
    ch = *cursor;
    while (*cursor != '.') {
        *background_out++ = ch;
        cursor++;
        ch = *cursor;
    }
    *background_out++ = '.';
    *background_out++ = 't';
    *background_out++ = 'x';
    *background_out++ = 't';
    *background_out = 0;
    landscape_script_index =
        ((LandscapeScriptBank*)(g_game_base + 0x106c218))
            ->load_landscape_script_by_name(background_name);

    cursor = find_case_insensitive_substring("Fringe:", LEVEL_FILE_BUFFER);
    if (cursor != 0) {
        cursor = find_case_insensitive_substring(":", cursor) + 1;
        parsed_int = parse_next_signed_int(&cursor);
        fringe_color.r = (float)parsed_int * 0.0039215689f;
        parsed_int = parse_next_signed_int(&cursor);
        fringe_color.g = (float)parsed_int * 0.0039215689f;
        parsed_int = parse_next_signed_int(&cursor);
        fringe_color.b = (float)parsed_int * 0.0039215689f;
    } else {
        report_errorf("No Fringe: in %s using white", level_path);
        fringe_color.store_color4f(0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000);
    }

    cursor = find_case_insensitive_substring("Track:", LEVEL_FILE_BUFFER);
    if (cursor != 0) {
        cursor = find_case_insensitive_substring(":", cursor) + 1;
        ch = *cursor;
        if (ch == '0') {
            track_texture_set = 0;
        } else if (ch == '1') {
            track_texture_set = 1;
        } else if (ch == '2') {
            track_texture_set = 2;
        } else if (ch == '3') {
            track_texture_set = 3;
        } else if (ch == 'r') {
            track_texture_set = 5;
        } else {
        }
    } else {
        report_errorf("No Track: in %s using Track0.tga", level_path);
        track_texture_set = 0;
    }

    cursor = find_case_insensitive_substring("Parcels:", LEVEL_FILE_BUFFER);
    if (cursor == 0) {
        parcel_count = 0;
        return (int*)report_errorf("No Parcel: in %s", level_path);
    }
    cursor = find_case_insensitive_substring(":", cursor);
    parcel_count = parse_next_signed_int(&cursor);

    cursor = find_case_insensitive_substring("Quota:", LEVEL_FILE_BUFFER);
    if (cursor == 0) {
        parcel_quota = 0;
        return (int*)report_errorf("No Quota: in %s", level_path);
    }
    cursor = find_case_insensitive_substring(":", cursor);
    parcel_quota = parse_next_signed_int(&cursor);

    cursor = find_case_insensitive_substring("Speed:select", LEVEL_FILE_BUFFER);
    if (cursor != 0) {
        selected_speed = -1.0f;
    } else {
        cursor = find_case_insensitive_substring("Speed:", LEVEL_FILE_BUFFER);
        if (cursor != 0) {
            cursor = find_case_insensitive_substring(":", cursor) + 1;
            selected_speed = parse_next_float32(&cursor);
        } else {
            report_errorf("Cannot find Speed: in Segment %s\n", level_path);
            selected_speed = 100.0f;
        }
    }

    cursor = find_case_insensitive_substring("Garbage:", LEVEL_FILE_BUFFER);
    if (cursor != 0)
        garbage_frequency = parse_next_float32(&cursor);
    else
        garbage_frequency = -1.0f;

    cursor = find_case_insensitive_substring("Salt:", LEVEL_FILE_BUFFER);
    if (cursor != 0)
        salt_frequency = parse_next_float32(&cursor);
    else
        salt_frequency = -1.0f;

    segment_count = 0;
    cursor = find_case_insensitive_substring("Segments Begin:", LEVEL_FILE_BUFFER);
    if (cursor == 0)
        return (int*)report_errorf("Cannot find Segments Begin: in %s", level_path);
    segments_end = find_case_insensitive_substring("Segments End:", LEVEL_FILE_BUFFER);
    if (segments_end == 0)
        return (int*)report_errorf("Cannot find Segments End: in %s", level_path);

    cursor = advance_to_next_crlf_line(cursor);
    if (cursor == 0)
        return (int*)report_errorf("Unexpected end of file in %s", level_path);

    if (cursor < segments_end) {
        do {
            ch = *cursor;
            char* segment_out = segment_name;
            while (*cursor != '.') {
                *segment_out++ = ch;
                cursor++;
                ch = *cursor;
            }
            int slot_index = segment_count;
            *segment_out++ = '.';
            *segment_out++ = 't';
            *segment_out++ = 'x';
            *segment_out++ = 't';
            *segment_out = 0;
            copy_segment_definition_to_level_slot(segment_name, &segment_slots[slot_index]);

            line_cursor = cursor + 3;
            char* options_out = line_options;
            ch = *line_cursor;
            while (ch >= 32) {
                *options_out++ = ch;
                line_cursor++;
                ch = *line_cursor;
            }
            *options_out = 0;

            char* option_cursor = find_case_insensitive_substring("Angle=", line_options);
            if (option_cursor != 0) {
                option_cursor = find_case_insensitive_substring("=", option_cursor);
                parsed_int = parse_next_signed_int(&option_cursor);
                segment_slots[segment_count].angle_radians =
                    (float)parsed_int * 0.017453292f;
            } else {
                segment_slots[segment_count].angle_radians = 0.0f;
            }

            segment_slots[segment_count].message_text[0] = 0;
            option_cursor = find_case_insensitive_substring("Message=", line_options);
            if (option_cursor != 0) {
                option_cursor = find_case_insensitive_substring("=", option_cursor) + 1;
                if (*option_cursor != '"')
                    return (int*)report_errorf("Need \" after Message=");
                char* message_start = option_cursor + 1;
                option_cursor = message_start;
                char* message_end = option_cursor;
                if (*message_end != '"') {
                    do {
                        message_end++;
                        ch = *message_end;
                    } while (ch != '"');
                }
                char* message_out = segment_slots[segment_count].message_text;
                while ((unsigned int)message_start < (unsigned int)message_end) {
                    *message_out++ = *message_start;
                    message_start++;
                    option_cursor = message_start;
                }
                *message_out = 0;

                option_cursor = find_case_insensitive_substring("Duration=", line_options);
                segment_slots[segment_count].message_duration = 4.0f;
                if (option_cursor != 0) {
                    option_cursor = find_case_insensitive_substring("=", option_cursor) + 1;
                    segment_slots[segment_count].message_duration =
                        parse_next_float32(&option_cursor);
                }

                option_cursor = find_case_insensitive_substring("Sample=", line_options);
                segment_slots[segment_count].message_sample_id = -1;
                if (option_cursor != 0) {
                    option_cursor = find_case_insensitive_substring("=", option_cursor) + 2;
                    char* sample_out = sample_name;
                    ch = *option_cursor;
                    while (*option_cursor != '"') {
                        *sample_out++ = ch;
                        option_cursor++;
                        ch = *option_cursor;
                    }
                    *sample_out = 0;
                    segment_slots[segment_count].message_sample_id = sub_432FC0(sample_name);
                    if (segment_slots[segment_count].message_sample_id == -1)
                        report_errorf("Cannot find sample %s in %s", sample_name, level_path);
                }
            }

            cursor = advance_to_next_crlf_line(cursor);
            segment_count++;
            if (cursor == 0)
                return (int*)report_errorf("Unexpected end of file in %s", filename);
        } while (cursor < segments_end);
    }

    cursor = find_case_insensitive_substring("First:", LEVEL_FILE_BUFFER);
    if (cursor == 0)
        return (int*)report_errorf("Cannot find 'First:' in %s", level_path);
    cursor = advance_to_next_crlf_line(cursor);
    if (cursor == 0)
        return (int*)report_errorf("Unexpected end of file in %s", level_path);

    char* special_out = segment_name;
    ch = *cursor;
    while (*cursor != '.') {
        *special_out++ = ch;
        cursor++;
        ch = *cursor;
    }
    *special_out++ = '.';
    *special_out++ = 't';
    *special_out++ = 'x';
    *special_out++ = 't';
    *special_out = 0;
    copy_segment_definition_to_level_slot(segment_name, &first_segment);

    cursor = find_case_insensitive_substring("Last:", LEVEL_FILE_BUFFER);
    if (cursor == 0)
        return (int*)report_errorf("Cannot find 'Last:' in %s", level_path);
    cursor = advance_to_next_crlf_line(cursor);
    if (cursor == 0)
        return (int*)report_errorf("Unexpected end of file in %s", level_path);

    special_out = segment_name;
    ch = *cursor;
    while (*cursor != '.') {
        *special_out++ = ch;
        cursor++;
        ch = *cursor;
    }
    *special_out++ = '.';
    *special_out++ = 't';
    *special_out++ = 'x';
    *special_out++ = 't';
    *special_out = 0;
    return copy_segment_definition_to_level_slot(segment_name, &last_segment);

#undef background_name
#undef segment_name
#undef sample_name
#undef line_options
#undef level_path
}
