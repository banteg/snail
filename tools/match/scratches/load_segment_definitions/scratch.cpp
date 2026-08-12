// load_segment_definitions @ 0x448160 (thiscall)

#include "game_root.h"
#include "rstring.h"
#include "rtext.h"
#include "segment_catalog_types.h"


int sprintf(char* buffer, char* format, ...);
int report_errorf(char* format, ...);
void enumerate_matching_archive_or_fs_entries(
    char* directory,
    char* pattern,
    int* out_count,
    char* out_names); // @ 0x431740
int load_file_bytes_from_archive_or_fs(char* path, char* out_buffer, void* out_size);

void cRSMTracks::Import()
{
    char path_name[64];
    char option_text[512];
    char mesh_name[128];
    char file_path[512];
    char file_buffer[4096];
    char segment_files[512][0x80];

    count = 0;
    enumerate_matching_archive_or_fs_entries("Segments", "*.txt", &count, segment_files[0]);

    if (count >= 150) {
        report_errorf("Too many Segments increase RSMTRACK_SEGMENT_MAX");
        return;
    }

    int segment_index = 0;
    char* segment_file_name = segment_files[0];
    int* row_count = &entries[0].row_count;
    while (segment_index < count) {
        // The authored call passes the text buffer as an unused fourth vararg;
        // the same source bug survives in the symbol-rich iOS build.
        sprintf(file_path, "Segments/%s", segment_file_name, file_buffer);
        load_file_bytes_from_archive_or_fs(file_path, file_buffer, (void*)0);

        char* id_cursor = Rstrfind("ID:", file_buffer);
        if (id_cursor == 0) {
            report_errorf("Cannot find ID: in Segment %s\n", segment_files[segment_index]);
            return;
        }

        id_cursor += 3;
        int id = 0;
        char value = *id_cursor;
        while (value >= '0') {
            if (value > '9')
                break;
            ++id_cursor;
            id = value + 10 * id - '0';
            value = *id_cursor;
        }

        entries[segment_index].id = id;
        sprintf(entries[segment_index].filename, "%s", segment_file_name);

        char* name_cursor = Rstrfind("Name:'", file_buffer);
        if (name_cursor == 0) {
            report_errorf("Cannot find Name: in Segment %s\n", segment_files[segment_index]);
            return;
        }

        name_cursor = Rstrfind("'", name_cursor) + 1;
        char* display_out = entries[segment_index].display_name;
        if (*name_cursor != '\'') {
            do {
                *display_out++ = *name_cursor;
                ++name_cursor;
            } while (*name_cursor != '\'');
        }

        char* data_cursor = Rstrfind("Data:", file_buffer);
        if (data_cursor == 0) {
            report_errorf("Cannot find Data: in Segment %s\n", segment_files[segment_index]);
            return;
        }

        data_cursor = Rstrnewline(data_cursor);
        if (data_cursor == 0) {
            report_errorf("Unexpected end of file in Segment %s\n", segment_files[segment_index]);
            return;
        }

        data_cursor = Rstrnewline(data_cursor);
        if (data_cursor == 0) {
            report_errorf("Unexpected end of file in Segment %s\n", segment_files[segment_index]);
            return;
        }

        if (*data_cursor != '@') {
            report_errorf("Data line must start with '@' in Segment %s\n", segment_files[segment_index]);
            return;
        }

        short row_index = 0;
        *row_count = 0;
        while (data_cursor[0] != '@' || data_cursor[1] != '@' || data_cursor[2] != '@') {
            AuthoredSegmentRow* row = &entries[segment_index].rows[row_index];
            char* glyph_cursor = data_cursor + 1;
            row->flags = 0;

            int lane = 0;
            do {
                char glyph = *glyph_cursor++;
                entries[segment_index]
                    .glyph_columns[*row_count][lane] = glyph;
                ++lane;
            } while (lane < 8);

            if (*glyph_cursor != '@') {
                report_errorf(
                    "Data line must end with '@' in Segment %s\n",
                    segment_files[segment_index]);
                return;
            }

            char* option_cursor = glyph_cursor + 1;
            ++*row_count;

            if (*option_cursor == '*')
                row->flags |= AUTHORED_SEGMENT_ROW_FLAG_SUPPRESS_TRACK_RENDER;

            char* option_out = option_text;
            char option_char = *option_cursor;
            while (option_char != '\r') {
                *option_out++ = option_char;
                ++option_cursor;
                option_char = *option_cursor;
            }
            *option_out = 0;

            char* option_match =
                Rstrfind("3DModel=", option_text);
            if (option_match != 0) {
                option_match = Rstrfind("=", option_match) + 1;
                char* mesh_out = mesh_name;
                char mesh_char = *option_match;
                while (mesh_char != '.') {
                    *mesh_out++ = mesh_char;
                    ++option_match;
                    mesh_char = *option_match;
                }
                row->flags |= AUTHORED_SEGMENT_ROW_FLAG_3D_MODEL;
                *mesh_out++ = '.';
                *mesh_out++ = 'x';
                *mesh_out = 0;
                row->object_id =
                    g_game->directx_loader
                        .ModelAdd(mesh_name);

                option_match = Rstrfind("(", option_match);
                row->object_position.x = RTextExtractFloat(&option_match);
                row->object_position.y = RTextExtractFloat(&option_match);
                row->object_position.z = RTextExtractFloat(&option_match);

                option_match = Rstrfind("Velocity=", option_text);
                if (option_match != 0) {
                    option_match = Rstrfind("=", option_match) + 1;
                    row->flags |=
                        AUTHORED_SEGMENT_ROW_FLAG_PATH_OR_MODEL_VELOCITY;
                    option_match = Rstrfind("(", option_match);
                    row->object_velocity.x = RTextExtractFloat(&option_match);
                    row->object_velocity.y = RTextExtractFloat(&option_match);
                    row->object_velocity.z = RTextExtractFloat(&option_match);
                }
            }

            option_match = Rstrfind("Parcel=", option_text);
            if (option_match != 0) {
                row->flags |= AUTHORED_SEGMENT_ROW_FLAG_PARCEL;
                option_match = Rstrfind("=", option_match) + 1;
                row->parcel_set_id = Rstrint(&option_match);
                option_match = Rstrfind("(", option_match) + 1;
                row->local_position.x = RTextExtractFloat(&option_match);
                row->local_position.y = RTextExtractFloat(&option_match);
                row->local_position.z = RTextExtractFloat(&option_match);
            }

            option_match = Rstrfind("Path=", option_text);
            if (option_match != 0) {
                option_match = Rstrfind("=", option_match) + 1;
                char* path_out = path_name;
                char path_char = *option_match;
                while (path_char >= 32) {
                    *path_out++ = path_char;
                    ++option_match;
                    path_char = *option_match;
                }
                *path_out = 0;
                row->path_template_index =
                    g_game->subgame.path_manager.NameCode(path_name);
                if (row->path_template_index == -1)
                    report_errorf("Unknown path %s in %s", path_name, segment_file_name);
                else
                    row->flags |=
                        AUTHORED_SEGMENT_ROW_FLAG_PATH_OR_MODEL_VELOCITY;
            }

            option_match = Rstrfind("NoFall", option_text);
            if (option_match != 0)
                row->flags |= AUTHORED_SEGMENT_ROW_FLAG_NO_FALL;
            option_match = Rstrfind("Ring=None", option_text);
            if (option_match != 0)
                row->flags |= AUTHORED_SEGMENT_ROW_FLAG_RING_NONE;
            option_match = Rstrfind("Ring=Normal", option_text);
            if (option_match != 0)
                row->flags |= AUTHORED_SEGMENT_ROW_FLAG_RING_NORMAL;
            option_match = Rstrfind("Ring=PowerUp", option_text);
            if (option_match != 0)
                row->flags |= AUTHORED_SEGMENT_ROW_FLAG_RING_POWER_UP;
            option_match = Rstrfind("Ring=Explode", option_text);
            if (option_match != 0)
                row->flags |= AUTHORED_SEGMENT_ROW_FLAG_RING_EXPLODE;
            option_match = Rstrfind("Ring=Slow", option_text);
            if (option_match != 0)
                row->flags |= AUTHORED_SEGMENT_ROW_FLAG_RING_SLOW;

            option_match = Rstrfind("RingSpeed=", option_text);
            if (option_match != 0) {
                option_match = Rstrfind("=", option_match) + 1;
                row->ring_speed.value = RTextExtractFloat(&option_match);
            } else {
                row->ring_speed.bits = 0;
            }

            option_match = Rstrfind("JetPack=Off", option_text);
            if (option_match != 0)
                row->flags |= AUTHORED_SEGMENT_ROW_FLAG_JETPACK_OFF;

            data_cursor = Rstrnewline(option_cursor);
            if (data_cursor == 0) {
                report_errorf(
                    "Unexpected end of file in Segment %s\n",
                    segment_files[segment_index]);
                return;
            }

            ++row_index;
        }

        ++segment_index;
        row_count = &entries[segment_index].row_count;
        segment_file_name += 0x80;
    }
}
