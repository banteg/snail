// cRSubTracks::Init(char*) @ 0x447480 (thiscall, ret 0x4)

#include "sprite.h"
#include "landscape_manager.h"
#include "rstring.h"
#include "rtext.h"
#include "sub_tracks.h"
#include "segment_catalog_types.h"
#include "game_root.h"

extern char* g_current_level_definition_name; // data_74ec74
extern char g_level_file_text_buffer[]; // data_74ec78

#define LEVEL_FILE_BUFFER g_level_file_text_buffer

int sprintf(char* buffer, const char* format, ...);
int report_errorf(char* format, ...);
int report_warningf(char* format, ...);
void* load_file_bytes_from_archive_or_fs(
    char* path, void* out_buffer, int* out_size);
int find_registered_sound_sample_id_by_name(char* sample_name); // @ 0x432fc0

struct LevelDefinitionParseBuffers {
    char level_path[512];
    char line_options[128];
    char sample_name[128];
    char segment_name[512];
    char background_name[512];
};

void cRSubTracks::Init(char* filename)
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
    if (!load_file_bytes_from_archive_or_fs(level_path, LEVEL_FILE_BUFFER, 0)) {
        report_errorf("Cannot find %s reverting to default.txt", level_path);
        sprintf(level_path, "Levels/Default.txt");
        load_file_bytes_from_archive_or_fs(level_path, LEVEL_FILE_BUFFER, 0);
    }

    cursor = Rstrfind("Name:'", LEVEL_FILE_BUFFER);
    if (cursor == 0) {
        report_errorf("Cannot find Name:' in %s", level_path);
    }

    cursor = Rstrfind("'", cursor) + 1;
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

    if (g_game->subgame.galaxy.active == 0) {
        cursor = Rstrfind("Arcade", filename);
        if (cursor != 0) {
            cursor = Rstrfind("e", cursor) + 1;
            int galaxy_route_index = Rstrint(&cursor);
            sprintf(
                g_game->subgame.galaxy.route_slots[galaxy_route_index]
                    .record.detail_text,
                "%s",
                level_display_name);

            cursor = Rstrfind("GalaxyText:", LEVEL_FILE_BUFFER);
            if (cursor == 0) {
                report_warningf("Cannot find GalaxyText: in %s", filename);
                Rstrcpy(
                    g_game->subgame.galaxy.route_slots[galaxy_route_index]
                        .record.description_text,
                    "TEXT MISSING");
            } else {
                cursor = Rstrfind("{", cursor);
                if (cursor == 0) {
                    report_warningf("Cannot find { for GalaxyText: in %s", filename);
                    Rstrcpy(
                        g_game->subgame.galaxy.route_slots[galaxy_route_index]
                            .record.description_text,
                        "TEXT ERROR { MISSING");
                } else {
                    cursor = Rstrnewline(cursor);
                    char* close_brace = Rstrfind("}", cursor);
                    if (close_brace == 0) {
                        report_warningf("Cannot find } for GalaxyText: in %s", filename);
                        Rstrcpy(
                            g_game->subgame.galaxy.route_slots[galaxy_route_index]
                                .record.description_text,
                            "TEXT ERROR } MISSING");
                    } else {
                        close_brace -= 2;
                        char* text_out =
                            g_game->subgame.galaxy.route_slots[galaxy_route_index]
                                .record.description_text;
                        while (cursor < close_brace) {
                            if (*cursor < 32) {
                                *text_out++ = '>';
                                while (*cursor < 32)
                                    cursor++;
                            }
                            *text_out++ = *cursor++;
                        }
                        *text_out = 0;
                    }
                }
            }
        }
    }

    cursor = Rstrfind("Random:yes", LEVEL_FILE_BUFFER);
    if (cursor != 0) {
        random_enabled = 1;
        cursor = Rstrfind("Length:", LEVEL_FILE_BUFFER);
        if (cursor == 0) {
            report_errorf("Cannot Length: in %s", level_path);
            return;
        }
        cursor = Rstrfind(":", cursor) + 1;
        random_length = 0;
        ch = *cursor;
        if (ch != 'a' && ch != 'A') {
            while (ch >= '0') {
                if (ch > '9')
                    break;
                cursor++;
                random_length = ch + 10 * random_length - '0';
                ch = *cursor;
            }
        }
    } else {
        random_enabled = 0;
        random_length = 0;
    }

    cursor = Rstrfind("Background:", LEVEL_FILE_BUFFER);
    if (cursor == 0) {
        report_errorf("No Background: in %s", level_path);
        return;
    }
    cursor = Rstrfind(":", cursor) + 1;
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
    landscape_script_index = g_game->subgame.landscape_manager
        .Import(background_name);

    cursor = Rstrfind("Fringe:", LEVEL_FILE_BUFFER);
    if (cursor == 0) {
        report_errorf("No Fringe: in %s using white", level_path);
        fringe_color.store_color4f(1.0f, 1.0f, 1.0f, 1.0f);
    } else {
        cursor = Rstrfind(":", cursor) + 1;
        parsed_int = Rstrint(&cursor);
        fringe_color.r = (float)parsed_int * 0.0039215689f;
        parsed_int = Rstrint(&cursor);
        fringe_color.g = (float)parsed_int * 0.0039215689f;
        parsed_int = Rstrint(&cursor);
        fringe_color.b = (float)parsed_int * 0.0039215689f;
    }

    cursor = Rstrfind("Track:", LEVEL_FILE_BUFFER);
    if (cursor == 0) {
        report_errorf("No Track: in %s using Track0.tga", level_path);
        track_texture_set = 0;
    } else {
        cursor = Rstrfind(":", cursor) + 1;
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
    }

    cursor = Rstrfind("Parcels:", LEVEL_FILE_BUFFER);
    if (cursor == 0) {
        parcel_count = 0;
        report_errorf("No Parcel: in %s", level_path);
        return;
    }
    cursor = Rstrfind(":", cursor);
    parcel_count = Rstrint(&cursor);

    cursor = Rstrfind("Quota:", LEVEL_FILE_BUFFER);
    if (cursor == 0) {
        parcel_quota = 0;
        report_errorf("No Quota: in %s", level_path);
        return;
    }
    cursor = Rstrfind(":", cursor);
    parcel_quota = Rstrint(&cursor);

    cursor = Rstrfind("Speed:select", LEVEL_FILE_BUFFER);
    if (cursor != 0) {
        selected_speed = -1.0f;
    } else {
        cursor = Rstrfind("Speed:", LEVEL_FILE_BUFFER);
        if (cursor == 0) {
            report_errorf("Cannot find Speed: in Segment %s\n", level_path);
            selected_speed = 100.0f;
        } else {
            cursor = Rstrfind(":", cursor) + 1;
            selected_speed = RTextExtractFloat(&cursor);
        }
    }

    cursor = Rstrfind("Garbage:", LEVEL_FILE_BUFFER);
    if (cursor == 0)
        garbage_frequency = -1.0f;
    else
        garbage_frequency = RTextExtractFloat(&cursor);

    cursor = Rstrfind("Salt:", LEVEL_FILE_BUFFER);
    if (cursor == 0)
        salt_frequency = -1.0f;
    else
        salt_frequency = RTextExtractFloat(&cursor);

    segment_count = 0;
    cursor = Rstrfind("Segments Begin:", LEVEL_FILE_BUFFER);
    if (cursor == 0) {
        report_errorf("Cannot find Segments Begin: in %s", level_path);
        return;
    }
    segments_end = Rstrfind("Segments End:", LEVEL_FILE_BUFFER);
    if (segments_end == 0) {
        report_errorf("Cannot find Segments End: in %s", level_path);
        return;
    }

    cursor = Rstrnewline(cursor);
    if (cursor == 0) {
        report_errorf("Unexpected end of file in %s", level_path);
        return;
    }

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
            ImportSegment(segment_name, &segment_slots[slot_index]);

            line_cursor = cursor + 3;
            char* options_out = line_options;
            ch = *line_cursor;
            while (ch >= 32) {
                *options_out++ = ch;
                line_cursor++;
                ch = *line_cursor;
            }
            *options_out = 0;

            line_cursor = Rstrfind("Angle=", line_options);
            if (line_cursor != 0) {
                line_cursor = Rstrfind("=", line_cursor);
                parsed_int = Rstrint(&line_cursor);
                segment_slots[segment_count].angle_radians.value =
                    (float)parsed_int * 0.017453292f;
            } else {
                segment_slots[segment_count].angle_radians.value = 0.0f;
            }

            segment_slots[segment_count].message_text[0] = 0;
            line_cursor = Rstrfind("Message=", line_options);
            if (line_cursor != 0) {
                line_cursor = Rstrfind("=", line_cursor) + 1;
                if (*line_cursor != '"') {
                    report_errorf("Need \" after Message=");
                    return;
                }
                line_cursor++;
                char* message_end = line_cursor;
                if (*message_end != '"') {
                    do {
                        message_end++;
                        ch = *message_end;
                    } while (ch != '"');
                }
                char* message_out = segment_slots[segment_count].message_text;
                while ((unsigned int)line_cursor < (unsigned int)message_end) {
                    *message_out++ = *line_cursor++;
                }
                *message_out = 0;

                line_cursor = Rstrfind("Duration=", line_options);
                segment_slots[segment_count].message_duration.value = 4.0f;
                if (line_cursor != 0) {
                    line_cursor = Rstrfind("=", line_cursor) + 1;
                    segment_slots[segment_count].message_duration.value =
                        RTextExtractFloat(&line_cursor);
                }

                line_cursor = Rstrfind("Sample=", line_options);
                segment_slots[segment_count].message_sample_id = -1;
                if (line_cursor != 0) {
                    line_cursor = Rstrfind("=", line_cursor) + 2;
                    char* sample_out = sample_name;
                    ch = *line_cursor;
                    while (*line_cursor != '"') {
                        *sample_out++ = ch;
                        line_cursor++;
                        ch = *line_cursor;
                    }
                    *sample_out = 0;
                    segment_slots[segment_count].message_sample_id =
                        find_registered_sound_sample_id_by_name(sample_name);
                    if (segment_slots[segment_count].message_sample_id == -1)
                        report_errorf("Cannot find sample %s in %s", sample_name, level_path);
                }
            }

            segment_count++;
            cursor = Rstrnewline(cursor);
        } while (cursor != 0 && cursor < segments_end);
        if (cursor == 0) {
            report_errorf("Unexpected end of file in %s", filename);
            return;
        }
    }

    cursor = Rstrfind("First:", LEVEL_FILE_BUFFER);
    if (cursor == 0) {
        report_errorf("Cannot find 'First:' in %s", level_path);
        return;
    }
    cursor = Rstrnewline(cursor);
    if (cursor == 0) {
        report_errorf("Unexpected end of file in %s", level_path);
        return;
    }

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
    ImportSegment(segment_name, &first_segment);

    cursor = Rstrfind("Last:", LEVEL_FILE_BUFFER);
    if (cursor == 0) {
        report_errorf("Cannot find 'Last:' in %s", level_path);
        return;
    }
    cursor = Rstrnewline(cursor);
    if (cursor == 0) {
        report_errorf("Unexpected end of file in %s", level_path);
        return;
    }

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
    ImportSegment(segment_name, &last_segment);

#undef background_name
#undef segment_name
#undef sample_name
#undef line_options
#undef level_path
}
