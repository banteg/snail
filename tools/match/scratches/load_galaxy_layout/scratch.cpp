// load_galaxy_layout @ 0x4088e0 (thiscall)

#include <stddef.h>

#include "game_root.h"

int sprintf(char* buffer, char* format, ...);

char* get_archive_data_base();
char* load_file_bytes_from_archive_or_fs(char* path, char* out_buffer, void* out_size);
char* find_case_insensitive_substring(char* needle, char* haystack);
int parse_next_signed_int(char** cursor);
void rstrcpy_checked_ascii(char* destination, char* source);
int report_errorf(char* format, ...);

extern GameRoot* g_game; // data_4df904

void Galaxy::load_galaxy_layout()
{
    float* first_point_cursor = &g_galaxy_route_points[0].y;

    active = 0;
    record_count = 1;

    do {
        float scaled_x = first_point_cursor[-1] * 0.80000001f;
        first_point_cursor[-1] = scaled_x;
        first_point_cursor[0] =
            (first_point_cursor[0] * 0.80000001f - 240.0f) * 0.93000001f + 250.0f;
        first_point_cursor += 2;
    } while ((int)first_point_cursor < 0x4a2040);

    float* galaxy_point_cursor = &g_galaxy_group_points[0].y;
    do {
        float scaled_x = galaxy_point_cursor[-1] * 0.80000001f;
        galaxy_point_cursor[-1] = scaled_x;
        galaxy_point_cursor[0] =
            (galaxy_point_cursor[0] * 0.80000001f - 240.0f) * 0.93000001f + 250.0f;
        galaxy_point_cursor += 2;
    } while ((int)galaxy_point_cursor < 0x4a1ca0);

    level_progress_base = &g_game->subgame;

    char* file_text = load_file_bytes_from_archive_or_fs(
        "Galaxy/_Galaxy.txt",
        get_archive_data_base(),
        (void*)0);

    int galaxy_index = 0;
    int star_group_offset = 0;
    int star_index = 0;
    float* current_galaxy_point = &g_galaxy_group_points[0].y;
    enum {
        ROUTE_NAME_COLOR_TO_NAME =
            offsetof(GalaxyRouteNameRecord, name)
            - offsetof(GalaxyRouteNameRecord, color),
        ROUTE_NAME_COLOR_TO_STAR_COUNT =
            (offsetof(GalaxyRouteNameRecord, star_count)
             - offsetof(GalaxyRouteNameRecord, color))
            / sizeof(int),
        ROUTE_NAME_COLOR_TO_MAP_X =
            (offsetof(GalaxyRouteNameRecord, map_x_bits)
             - offsetof(GalaxyRouteNameRecord, color))
            / sizeof(int),
        ROUTE_NAME_COLOR_TO_MAP_Y =
            (offsetof(GalaxyRouteNameRecord, map_y_bits)
             - offsetof(GalaxyRouteNameRecord, color))
            / sizeof(int),
        ROUTE_NAME_COLOR_TO_MAP_Z =
            (offsetof(GalaxyRouteNameRecord, map_z_bits)
             - offsetof(GalaxyRouteNameRecord, color))
            / sizeof(int),
        ROUTE_NAME_COLOR_STRIDE = sizeof(GalaxyRouteNameRecord) / sizeof(int),
    };
    int* route_name_cursor = (int*)&route_names[0].color;

    while (1) {
        char marker[64];
        sprintf(marker, "Galaxy%i:", galaxy_index);

        char* cursor;
        if ((cursor = find_case_insensitive_substring(marker, file_text)) == (char*)0)
            goto missing_galaxy;

        cursor = find_case_insensitive_substring(":", cursor) + 1;
        if (*cursor != '"')
            goto missing_quote;

        cursor += 1;
        char* name_cursor = (char*)route_name_cursor + ROUTE_NAME_COLOR_TO_NAME;
        while (*cursor != '"') {
            *name_cursor++ = *cursor;
            cursor += 1;
        }
        *name_cursor = 0;

        cursor = find_case_insensitive_substring("StarNumber=", cursor);
        cursor = find_case_insensitive_substring("=", cursor) + 1;
        route_name_cursor[ROUTE_NAME_COLOR_TO_STAR_COUNT] =
            parse_next_signed_int(&cursor);
        route_name_cursor[0] = 0x3f800000;
        route_name_cursor[1] = 0x3f800000;
        route_name_cursor[2] = 0x3f800000;
        route_name_cursor[3] = 0x3f4ccccd;
        route_name_cursor[ROUTE_NAME_COLOR_TO_MAP_X] =
            *(int*)&current_galaxy_point[-1];
        route_name_cursor[ROUTE_NAME_COLOR_TO_MAP_Y] =
            *(int*)&current_galaxy_point[0];
        route_name_cursor[ROUTE_NAME_COLOR_TO_MAP_Z] = star_index;

        for (int step = 0;
             star_index < route_name_cursor[ROUTE_NAME_COLOR_TO_STAR_COUNT];
             step += 10) {
            route_slots[record_count].record.route_name_index = galaxy_index;
            route_slots[record_count].record.map_x_bits =
                g_galaxy_route_points[
                    star_group_offset
                    + step / route_name_cursor[ROUTE_NAME_COLOR_TO_STAR_COUNT]
                    + 1].x_bits;
            route_slots[record_count].record.map_y_bits =
                g_galaxy_route_points[
                    star_group_offset
                    + step / route_name_cursor[ROUTE_NAME_COLOR_TO_STAR_COUNT]
                    + 1].y_bits;
            route_slots[record_count].record.map_z_bits = 0;

            char missing_label[128];
            sprintf(missing_label, "LEVEL %i MISSING", record_count);
            rstrcpy_checked_ascii(
                route_slots[record_count].record.detail_text, missing_label);
            rstrcpy_checked_ascii(
                route_slots[record_count].record.description_text,
                missing_label);
            ++record_count;
            ++star_index;
        }

        star_index = 0;

        current_galaxy_point += 2;
        ++galaxy_index;
        star_group_offset += 10;
        route_name_cursor += ROUTE_NAME_COLOR_STRIDE;
        if ((int)current_galaxy_point < 0x4a1ca0)
            continue;

        route_slots[0].record.route_name_index = 0;
        route_slots[0].record.map_x_bits = g_galaxy_route_points[0].x_bits;
        route_slots[0].record.map_y_bits = g_galaxy_route_points[0].y_bits;
        route_slots[0].record.map_z_bits = 0;
        route_slots[0].record.detail_text[0] = 0;
        route_slots[0].record.description_text[0] = 0;
        return;
    }

missing_galaxy:
    report_errorf("Cannot find Galaxy %i in _Galaxy.txt");
    return;

missing_quote:
    report_errorf("missing \" in _Galaxy.txt");
    return;
}
