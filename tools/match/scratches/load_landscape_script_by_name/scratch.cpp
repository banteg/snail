// load_landscape_script_by_name @ 0x4182f0 (thiscall, ret 0x4)

#include "game_root.h"
#include "landscape_manager.h"

extern char* g_game_base; // data_4df904

int sprintf(char* buffer, char* format, ...);
char* load_file_bytes(char* path, char* out_buffer);
int report_errorf(char* format, ...);
char* find_case_insensitive_substring(char* needle, char* haystack);
int strings_equal_case_insensitive_path(char* left, char* right);
void rstrcpy_checked_ascii(char* destination, char* source);
int parse_next_signed_int(char** cursor);
float parse_next_float32(char** cursor);
char archive_or_file_exists(char* path, char force_filesystem);
int debug_report_stub(char* format, ...); // @ 0x449c00, stripped in release

int LandscapeManager::load_landscape_script_by_name(char* script_name)
{
    char* cursor;
    char* loaded_name;
    int parsed_int;
    char split_texture_b[128];
    char split_texture_a[128];
    char script_path[512];
    char texture_stem[512];
    char object_mesh_name[512];

    sprintf(script_path, "Backgrounds/%s", script_name);

    int index = 0;
    if (script_count <= 0)
        goto load_script;

    loaded_name = scripts[0].name;
    while (index < script_count) {
        if (strings_equal_case_insensitive_path(loaded_name, script_name) != 0)
            goto found_existing;
        ++index;
        loaded_name += sizeof(LandscapeScriptRecord);
    }
    goto load_script;

found_existing:
    return index;

load_script:
    char* file_bytes = load_file_bytes(script_path, 0);
    if (file_bytes == 0) {
        report_errorf("Landscape.Cannot load %s", script_path);
        return 0;
    }

    rstrcpy_checked_ascii(scripts[script_count].name, script_name);

    cursor = find_case_insensitive_substring("ID:", file_bytes);
    if (cursor == 0) {
        report_errorf("Landscape. Cannot find ID: %s", script_path);
        scripts[script_count].id = 0;
    } else {
        cursor = find_case_insensitive_substring(":", cursor);
        scripts[script_count].id = parse_next_signed_int(&cursor);
    }

    cursor = find_case_insensitive_substring("Fog:", file_bytes);
    if (cursor == 0) {
        report_errorf("Landscape. Cannot find Fog: %s", script_path);
        scripts[script_count].fog_color.set_color_black();
    } else {
        cursor = find_case_insensitive_substring(":", cursor);
        parsed_int = parse_next_signed_int(&cursor);
        scripts[script_count].fog_color.r = (float)parsed_int * 0.00392156886f;
        parsed_int = parse_next_signed_int(&cursor);
        scripts[script_count].fog_color.g = (float)parsed_int * 0.00392156886f;
        parsed_int = parse_next_signed_int(&cursor);
        scripts[script_count].fog_color.b = (float)parsed_int * 0.00392156886f;
    }

    cursor = find_case_insensitive_substring("Picture:", file_bytes);
    if (cursor == 0) {
        report_errorf("Landscape. Cannot find Picture: in %s", script_path);
    } else {
        cursor = find_case_insensitive_substring(":", cursor) + 1;
        char* out = texture_stem;
        char ch = *cursor;
        while (*cursor != '.') {
            *out++ = ch;
            cursor++;
            ch = *cursor;
        }
        *out = 0;

        sprintf(scripts[script_count].backdrop_texture_path,
            "Backgrounds/%s.tga", texture_stem);
        scripts[script_count].backdrop_texture_id = script_count * 2 + 6;

        if (archive_or_file_exists(
                scripts[script_count].backdrop_texture_path, 0) != 0) {
            g_sprite_manager.register_sprite_texture(
                scripts[script_count].backdrop_texture_path,
                scripts[script_count].backdrop_texture_id, 0x400);
            scripts[script_count].split_backdrop_texture_pair = 0;
        } else {
            scripts[script_count].split_backdrop_texture_pair = 1;

            rstrcpy_checked_ascii(split_texture_a,
                scripts[script_count].backdrop_texture_path);
            rstrcpy_checked_ascii(split_texture_b,
                scripts[script_count].backdrop_texture_path);

            char* dot = split_texture_a;
            if (split_texture_a[0] != '.') {
                do {
                    ++dot;
                } while (*dot != '.');
            }
            dot[0] = '_';
            dot[1] = 'A';
            dot[2] = '.';
            dot[3] = 't';
            dot[4] = 'g';
            dot[5] = 'a';
            dot[6] = 0;

            dot = split_texture_b;
            if (split_texture_b[0] != '.') {
                do {
                    ++dot;
                } while (*dot != '.');
            }
            dot[0] = '_';
            dot[1] = 'B';
            dot[2] = '.';
            dot[3] = 't';
            dot[4] = 'g';
            dot[5] = 'a';
            dot[6] = 0;

            g_sprite_manager.register_sprite_texture(split_texture_a,
                scripts[script_count].backdrop_texture_id, 0x400);
            g_sprite_manager.register_sprite_texture(split_texture_b,
                scripts[script_count].backdrop_texture_id + 1, 0x400);
        }

        debug_report_stub("Loading backdrop texture %s",
            scripts[script_count].backdrop_texture_path);
    }

    cursor = find_case_insensitive_substring("Landscape:", file_bytes);
    if (cursor == 0) {
        report_errorf("Landscape. Cannot find Landscape: in %s", script_path);
    } else {
        cursor = find_case_insensitive_substring(":", cursor) + 1;
        char ch = *cursor;
        if (ch == ' ' || ch < ' ') {
            scripts[script_count].object_index = -1;
        } else {
            char* out = object_mesh_name;
            while (*cursor != '.') {
                *out++ = ch;
                cursor++;
                ch = *cursor;
            }
            *out++ = '.';
            *out = 'x';
            out[1] = 0;

            scripts[script_count].object_index =
                ((GameRoot*)g_game_base)->directx_loader
                    .load_or_reuse_cached_x_mesh(object_mesh_name);
        }
    }

    cursor = find_case_insensitive_substring("Distort:", file_bytes);
    if (cursor == 0) {
        report_errorf("Landscape. Cannot find Distort: in %s", script_path);
    } else {
        cursor = find_case_insensitive_substring(":", cursor) + 1;
        scripts[script_count].distort = parse_next_float32(&cursor);
    }

    script_count++;
    debug_report_stub("Landscape: %s imported\n", script_name);
    return script_count - 1;
}
