// load_galaxy_layout @ 0x4088e0 (thiscall)

#include <stddef.h>

#include "game_root.h"
#include "rstring.h"

int sprintf(char* buffer, char* format, ...);

char* get_archive_data_base();
char* load_file_bytes_from_archive_or_fs(char* path, char* out_buffer, void* out_size);
int report_errorf(char* format, ...);


void cRGalaxy::Open()
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
    while ((int)current_galaxy_point < (int)((char*)g_galaxy_group_points + sizeof(g_galaxy_group_points) + offsetof(GalaxyPoint, y))) {
        char marker[64];
        sprintf(marker, "Galaxy%i:", galaxy_index);

        char* cursor = Rstrfind(marker, file_text);
        if (cursor == 0)
            goto missing_galaxy;

        cursor = Rstrfind(":", cursor) + 1;
        if (*cursor != '"')
            goto missing_quote;

        cursor += 1;
        char* name_cursor = route_names[galaxy_index].name;
        while (*cursor != '"') {
            *name_cursor++ = *cursor;
            cursor += 1;
        }
        *name_cursor = 0;

        cursor = Rstrfind("StarNumber=", cursor);
        cursor = Rstrfind("=", cursor) + 1;
        route_names[galaxy_index].star_count =
            Rstrint(&cursor);
        route_names[galaxy_index].color.r = 1.0f;
        route_names[galaxy_index].color.g = 1.0f;
        route_names[galaxy_index].color.b = 1.0f;
        route_names[galaxy_index].color.a = 0.800000012f;
        route_names[galaxy_index].map_x_bits =
            *(int*)&current_galaxy_point[-1];
        route_names[galaxy_index].map_y_bits =
            *(int*)&current_galaxy_point[0];
        star_index = 0;
        route_names[galaxy_index].map_z_bits = star_index;

        for (; star_index < route_names[galaxy_index].star_count; ++star_index) {
            route_slots[record_count].record.route_name_index = galaxy_index;
            route_slots[record_count].record.map_x_bits =
                g_galaxy_route_points[
                    star_group_offset
                    + star_index * 10 / route_names[galaxy_index].star_count
                    + 1].x_bits;
            route_slots[record_count].record.map_y_bits =
                g_galaxy_route_points[
                    star_group_offset
                    + star_index * 10 / route_names[galaxy_index].star_count
                    + 1].y_bits;
            route_slots[record_count].record.map_z_bits = 0;

            char missing_label[128];
            sprintf(missing_label, "LEVEL %i MISSING", record_count);
            Rstrcpy(
                route_slots[record_count].record.detail_text, missing_label);
            Rstrcpy(
                route_slots[record_count].record.description_text,
                missing_label);
            ++record_count;
        }

        ++galaxy_index;
        star_group_offset += 10;
        current_galaxy_point += 2;
    }

    route_slots[0].record.route_name_index = 0;
    route_slots[0].record.map_x_bits = g_galaxy_route_points[0].x_bits;
    route_slots[0].record.map_y_bits = g_galaxy_route_points[0].y_bits;
    route_slots[0].record.map_z_bits = 0;
    route_slots[0].record.detail_text[0] = 0;
    route_slots[0].record.description_text[0] = 0;
    return;

missing_galaxy:
    report_errorf("Cannot find Galaxy %i in _Galaxy.txt");
    return;

missing_quote:
    report_errorf("missing \" in _Galaxy.txt");
    return;
}
