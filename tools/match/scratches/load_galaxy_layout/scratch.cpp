// load_galaxy_layout @ 0x4088e0 (thiscall)

#include "galaxy_route_types.h"

int sprintf(char* buffer, char* format, ...);

char* get_archive_data_base();
char* load_file_bytes_from_archive_or_fs(char* path, char* out_buffer, void* out_size);
char* find_case_insensitive_substring(char* needle, char* haystack);
int parse_next_signed_int(char** cursor);
void rstrcpy_checked_ascii(char* destination, char* source);
int report_errorf(char* format, ...);

extern char* g_game_base; // data_4df904

extern int dword_4a1d14;
extern int dword_4a1d18[];
extern int dword_4a1d1c[];
extern int dword_4a1d20[];
extern int data_4a1c50[];

int GalaxyRoute::load_galaxy_layout()
{
    float* first_point_cursor = (float*)dword_4a1d18;

    active = 0;
    record_count = 1;

    do {
        float scaled_x = first_point_cursor[-1] * 0.80000001f;
        first_point_cursor[-1] = scaled_x;
        first_point_cursor[0] =
            (first_point_cursor[0] * 0.80000001f - 240.0f) * 0.93000001f + 250.0f;
        first_point_cursor += 2;
    } while ((int)first_point_cursor < 0x4a2040);

    float* galaxy_point_cursor = (float*)data_4a1c50;
    do {
        float scaled_x = galaxy_point_cursor[-1] * 0.80000001f;
        galaxy_point_cursor[-1] = scaled_x;
        galaxy_point_cursor[0] =
            (galaxy_point_cursor[0] * 0.80000001f - 240.0f) * 0.93000001f + 250.0f;
        galaxy_point_cursor += 2;
    } while ((int)galaxy_point_cursor < 0x4a1ca0);

    int star_index = 0;
    level_progress_base = g_game_base + 0x74618;

    char* file_text = load_file_bytes_from_archive_or_fs(
        "Galaxy/_Galaxy.txt",
        get_archive_data_base(),
        (void*)star_index);

    int galaxy_index = star_index;
    int star_group_offset = star_index;
    int* current_galaxy_point = data_4a1c50;
    int* route_name_cursor = (int*)((char*)route_names + 0x84);

    while (1) {
        char marker[64];
        sprintf(marker, "Galaxy%i:", galaxy_index);

        char* cursor = find_case_insensitive_substring(marker, file_text);
        if (cursor == (char*)0) {
            return report_errorf("Cannot find Galaxy %i in _Galaxy.txt");
        }

        cursor = find_case_insensitive_substring(":", cursor) + 1;
        if (*cursor != '"') {
            return report_errorf("missing \" in _Galaxy.txt");
        }

        cursor += 1;
        char* name_cursor = (char*)(route_name_cursor - 33);
        while (*cursor != '"') {
            *name_cursor++ = *cursor;
            cursor += 1;
        }
        *name_cursor = 0;

        cursor = find_case_insensitive_substring("StarNumber=", cursor);
        cursor = find_case_insensitive_substring("=", cursor) + 1;
        route_name_cursor[-1] = parse_next_signed_int(&cursor);
        route_name_cursor[0] = 0x3f800000;
        route_name_cursor[1] = 0x3f800000;
        route_name_cursor[2] = 0x3f800000;
        route_name_cursor[3] = 0x3f4ccccd;
        route_name_cursor[4] = current_galaxy_point[-1];
        route_name_cursor[5] = current_galaxy_point[0];
        route_name_cursor[6] = star_index;

        if (route_name_cursor[-1] > star_index) {
            int step = 0;
            int* saved_galaxy_point = current_galaxy_point;
            do {
                *(int*)((char*)this + record_count * 0x2a0 + 0x14) = galaxy_index;
                *(int*)((char*)this + record_count * 0x2a0 + 0x1c) =
                    dword_4a1d1c[(star_group_offset + step / route_name_cursor[-1]) * 2];
                *(int*)((char*)this + record_count * 0x2a0 + 0x20) =
                    dword_4a1d20[(star_group_offset + step / route_name_cursor[-1]) * 2];
                *(int*)((char*)this + record_count * 0x2a0 + 0x24) = 0;

                char missing_label[128];
                sprintf(missing_label, "LEVEL %i MISSING", record_count);
                rstrcpy_checked_ascii((char*)this + record_count * 0x2a0 + 0x30, missing_label);
                rstrcpy_checked_ascii((char*)this + record_count * 0x2a0 + 0xb0, missing_label);
                ++star_index;
                ++record_count;
                step += 10;
            } while (star_index < route_name_cursor[-1]);

            current_galaxy_point = saved_galaxy_point;
            star_index = 0;
        }

        current_galaxy_point += 2;
        route_name_cursor += 40;
        ++galaxy_index;
        star_group_offset += 10;
        if ((int)current_galaxy_point < 0x4a1ca0) {
            continue;
        }

        {
            records[0].route_name_index = 0;
            records[0].map_x_bits = dword_4a1d14;
            records[0].map_y_bits = dword_4a1d18[0];
            records[0].map_z_bits = 0;
            records[0].detail_text[0] = 0;
            records[0].description_text[0] = 0;
            return dword_4a1d18[0];
        }
    }
}
