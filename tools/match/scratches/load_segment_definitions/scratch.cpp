// load_segment_definitions @ 0x448160 (thiscall)

#include "game_root.h"
#include "segment_catalog_types.h"

extern char* g_game_base; // data_4df904

int sprintf(char* buffer, char* format, ...);
int report_errorf(char* format, ...);
void enumerate_matching_archive_or_fs_entries(
    char* directory,
    char* pattern,
    int* out_count,
    char* out_names); // @ 0x431740
int load_file_bytes_from_archive_or_fs(char* path, char* out_buffer, void* out_size);
char* find_case_insensitive_substring(char* needle, char* haystack);
char* advance_to_next_crlf_line(char* cursor); // @ 0x44e690
int parse_next_signed_int(char** cursor);
float parse_next_float32(char** cursor);

class SegmentPathTable {
public:
    int find_segment_path_index_by_name(char* name); // @ 0x429ae0
};

int SegmentCatalog::load_segment_definitions()
{
    char path_name[60];
    char option_text[512];
    char mesh_name[128];
    char file_path[512];
    char file_buffer[4096];
    char segment_files[0x10000];

    int* catalog_count = (int*)this;
    SegmentCatalogEntry* entries = (SegmentCatalogEntry*)this;

    *catalog_count = 0;
    enumerate_matching_archive_or_fs_entries("Segments", "*.txt", catalog_count, segment_files);

    int result = *catalog_count;
    if (*catalog_count >= 150)
        return report_errorf("Too many Segments increase RSMTRACK_SEGMENT_MAX");

    int segment_index = 0;
    if (result <= 0)
        return result;

    char* segment_file_name = segment_files;
    do {
        SegmentCatalogEntry* entry = &entries[segment_index];
        sprintf(file_path, "Segments/%s", segment_file_name);
        load_file_bytes_from_archive_or_fs(file_path, file_buffer, (void*)0);

        char* id_cursor = find_case_insensitive_substring("ID:", file_buffer);
        if (id_cursor == 0)
            return report_errorf("Cannot find ID: in Segment %s\n", segment_file_name);

        id_cursor += 3;
        int id = 0;
        char value = *id_cursor;
        if (value >= '0') {
            do {
                if (value > '9')
                    break;
                ++id_cursor;
                id = value + 10 * id - '0';
                value = *id_cursor;
            } while (*id_cursor >= '0');
        }

        entry->id = id;
        sprintf(entry->filename, "%s", segment_file_name);

        char* name_cursor = find_case_insensitive_substring("Name:'", file_buffer);
        if (name_cursor == 0)
            return report_errorf("Cannot find Name: in Segment %s\n", segment_file_name);

        name_cursor = find_case_insensitive_substring("'", name_cursor) + 1;
        char* display_out = entry->display_name;
        if (*name_cursor != '\'') {
            do {
                *display_out++ = *name_cursor;
                ++name_cursor;
            } while (*name_cursor != '\'');
        }

        char* data_cursor = find_case_insensitive_substring("Data:", file_buffer);
        if (data_cursor == 0)
            return report_errorf("Cannot find Data: in Segment %s\n", segment_file_name);

        data_cursor = advance_to_next_crlf_line(data_cursor);
        if (data_cursor == 0)
            return report_errorf("Unexpected end of file in Segment %s\n", segment_file_name);

        data_cursor = advance_to_next_crlf_line(data_cursor);
        if (data_cursor == 0)
            return report_errorf("Unexpected end of file in Segment %s\n", segment_file_name);

        if (*data_cursor != '@')
            return report_errorf("Data line must start with '@' in Segment %s\n", segment_file_name);

        short row_index = 0;
        entry->row_count = 0;
        while (data_cursor[0] != '@' || data_cursor[1] != '@' || data_cursor[2] != '@') {
            AuthoredSegmentRow* row = &entry->rows[row_index];
            char* glyph_cursor = data_cursor + 1;
            row->flags = 0;

            int lane = 0;
            do {
                char glyph = *glyph_cursor++;
                entry->glyph_columns[entry->row_count][lane] = glyph;
                ++lane;
            } while (lane < 8);

            if (*glyph_cursor != '@')
                return report_errorf("Data line must end with '@' in Segment %s\n", segment_file_name);

            char* option_cursor = glyph_cursor + 1;
            ++entry->row_count;

            if (*option_cursor == '*')
                row->flags |= 4;

            char* option_out = option_text;
            char option_char = *option_cursor;
            while (option_char != '\r') {
                *option_out++ = option_char;
                ++option_cursor;
                option_char = *option_cursor;
            }
            *option_out = 0;

            char* model_cursor = find_case_insensitive_substring("3DModel=", option_text);
            if (model_cursor != 0) {
                model_cursor = find_case_insensitive_substring("=", model_cursor) + 1;
                char* mesh_out = mesh_name;
                char mesh_char = *model_cursor;
                while (mesh_char != '.') {
                    *mesh_out++ = mesh_char;
                    ++model_cursor;
                    mesh_char = *model_cursor;
                }
                row->flags |= 2;
                *mesh_out++ = '.';
                *mesh_out++ = 'x';
                *mesh_out = 0;
                row->object_id =
                    ((GameRoot*)g_game_base)->directx_loader
                        .load_or_reuse_cached_x_mesh(mesh_name);

                model_cursor = find_case_insensitive_substring("(", model_cursor);
                row->object_position_x.value = parse_next_float32(&model_cursor);
                row->object_position_y.value = parse_next_float32(&model_cursor);
                row->object_position_z.value = parse_next_float32(&model_cursor);

                char* velocity_cursor =
                    find_case_insensitive_substring("Velocity=", option_text);
                if (velocity_cursor != 0) {
                    velocity_cursor = find_case_insensitive_substring("=", velocity_cursor) + 1;
                    row->flags |= 8;
                    velocity_cursor = find_case_insensitive_substring("(", velocity_cursor);
                    row->object_velocity_x.value = parse_next_float32(&velocity_cursor);
                    row->object_velocity_y.value = parse_next_float32(&velocity_cursor);
                    row->object_velocity_z.value = parse_next_float32(&velocity_cursor);
                }
            }

            char* parcel_cursor = find_case_insensitive_substring("Parcel=", option_text);
            if (parcel_cursor != 0) {
                row->flags |= 1;
                parcel_cursor = find_case_insensitive_substring("=", parcel_cursor) + 1;
                row->parcel_set_id = parse_next_signed_int(&parcel_cursor);
                parcel_cursor = find_case_insensitive_substring("(", parcel_cursor) + 1;
                row->local_x.value = parse_next_float32(&parcel_cursor);
                row->local_y.value = parse_next_float32(&parcel_cursor);
                row->local_z.value = parse_next_float32(&parcel_cursor);
            }

            char* path_cursor = find_case_insensitive_substring("Path=", option_text);
            if (path_cursor != 0) {
                path_cursor = find_case_insensitive_substring("=", path_cursor) + 1;
                char* path_out = path_name;
                char path_char = *path_cursor;
                while (path_char >= 32) {
                    *path_out++ = path_char;
                    ++path_cursor;
                    path_char = *path_cursor;
                }
                *path_out = 0;
                row->path_template_index =
                    ((SegmentPathTable*)(g_game_base + 0x1066f28))
                        ->find_segment_path_index_by_name(path_name);
                if (row->path_template_index == -1)
                    report_errorf("Unknown path %s in %s", path_name, segment_file_name);
                else
                    row->flags |= 8;
            }

            if (find_case_insensitive_substring("NoFall", option_text) != 0)
                row->flags |= 0x100;
            if (find_case_insensitive_substring("Ring=None", option_text) != 0)
                row->flags |= 0x200;
            if (find_case_insensitive_substring("Ring=Normal", option_text) != 0)
                row->flags |= 0x400;
            if (find_case_insensitive_substring("Ring=PowerUp", option_text) != 0)
                row->flags |= 0x2000;
            if (find_case_insensitive_substring("Ring=Explode", option_text) != 0)
                row->flags |= 0x800;
            if (find_case_insensitive_substring("Ring=Slow", option_text) != 0)
                row->flags |= 0x1000;

            char* ring_speed_cursor =
                find_case_insensitive_substring("RingSpeed=", option_text);
            if (ring_speed_cursor != 0) {
                ring_speed_cursor =
                    find_case_insensitive_substring("=", ring_speed_cursor) + 1;
                row->ring_speed.value = parse_next_float32(&ring_speed_cursor);
            } else {
                row->ring_speed.bits = 0;
            }

            if (find_case_insensitive_substring("JetPack=Off", option_text) != 0)
                row->flags |= 0x8000;

            data_cursor = advance_to_next_crlf_line(option_cursor);
            if (data_cursor == 0)
                return report_errorf(
                    "Unexpected end of file in Segment %s\n",
                    segment_file_name);

            ++row_index;
        }

        ++segment_index;
        result = *catalog_count;
        segment_file_name += 0x80;
    } while (segment_index < result);

    return result;
}
