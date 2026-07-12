// load_x_animation_clip @ 0x405d60 (thiscall, ret 0x8)

#include <stdio.h>

#include "bod_types.h"
#include "directx_loader.h"
#include "object_animation_types.h"

void* allocate_tracked_memory(int size, char* name); // @ 0x431b60
char* find_case_insensitive_substring(char* needle, char* haystack); // @ 0x44e600
char is_archive_index_loaded(); // @ 0x431a80
void enumerate_matching_archive_or_fs_entries(
    char* directory,
    char* pattern,
    int* out_count,
    char* out_names); // @ 0x431740
int parse_next_signed_int(char** cursor); // @ 0x44e710
float parse_next_float32(char** cursor); // @ 0x431f20
int report_errorf(char* format, ...); // @ 0x431cc0

extern char g_x_animation_clip_enumeration_names[]; // data_4b2f50

ObjectAnimation* DirectXLoader::load_x_animation_clip(char* mesh_name, Object* object)
{
    char* cursor;
    char saved_end_char;
    float progress_step;
    int keyframe_count;
    XAnimationKeyframe* keyframes;
    unsigned short mode_flags;
    char animation_tag[0x80];
    char path_pattern[0x100];

    sprintf(path_pattern, "%s", mesh_name);
    cursor = path_pattern;
    cursor = find_case_insensitive_substring("-", cursor) + 1;
    cursor = find_case_insensitive_substring("-", cursor) + 1;
    *cursor++ = '*';
    *cursor++ = '.';
    *cursor++ = 'x';
    if (is_archive_index_loaded() != 0)
        *cursor++ = '2';
    *cursor++ = 0;

    enumerate_matching_archive_or_fs_entries("X", path_pattern, &keyframe_count,
        g_x_animation_clip_enumeration_names);

    keyframes = (XAnimationKeyframe*)allocate_tracked_memory(
        keyframe_count << 7, "Anim Key frame bods");

    int i = 0;
    duplicate_vertices.active_count = 0;
    if (keyframe_count > 0) {
        char* mesh_path = g_x_animation_clip_enumeration_names;
        XAnimationKeyframe* keyframe = keyframes;
        do {
            keyframe->set_bod_object(g_object_list.add_object_to_list());
            load_x_mesh(mesh_path, keyframe->object, 0);

            cursor = mesh_path;
            cursor = find_case_insensitive_substring("-", cursor) + 1;
            cursor = find_case_insensitive_substring("-", cursor) + 1;
            keyframe->frame_number = parse_next_signed_int(&cursor);

            ++i;
            mesh_path += 0x80;
            ++keyframe;
        } while (i < keyframe_count);
    }

    duplicate_vertices.clean_duplicate_vertices(keyframe_count);
    load_x_mesh(g_x_animation_clip_enumeration_names, object, 0);
    object->request_object_vertices_copy();
    object->flags |= 0x800000;

    sprintf(animation_tag, "Anim:%s", mesh_name);
    char* animation_block = find_case_insensitive_substring(animation_tag, animation_bytes);
    if (animation_block != 0) {
        char* animation_end = find_case_insensitive_substring("AnimEnd:", animation_block);
        if (animation_end == 0) {
            return (ObjectAnimation*)report_errorf(
                "Cannot find AnimEnd: for %s \n", mesh_name);
        }

        saved_end_char = *animation_end;
        *animation_end = 0;

        cursor = find_case_insensitive_substring("Duration:", animation_block);
        if (cursor != 0) {
            cursor = find_case_insensitive_substring(":", cursor) + 1;
            progress_step = 1.0f / (parse_next_float32(&cursor) * 60.0f);
        } else {
            progress_step = 0.0166666675f;
        }

        mode_flags = 0;
        cursor = find_case_insensitive_substring("Mode:Loop", animation_block);
        if (cursor != 0)
            mode_flags = 1;
        cursor = find_case_insensitive_substring("Mode:Once", animation_block);
        if (cursor != 0)
            mode_flags |= 4;
        cursor = find_case_insensitive_substring("Mode:Pingpong", animation_block);
        if (cursor != 0)
            mode_flags |= 2;

        *animation_end = saved_end_char;
    } else {
        report_errorf("Did not find Anim:%s in _Animation.txt. Using defaults", mesh_name);
        progress_step = 0.0166666675f;
        mode_flags |= 1;
    }

    if (keyframe_count == 1)
        progress_step = 1.0f;

    return object->request_object_animation(
        keyframe_count, keyframes, progress_step, mode_flags);
}
