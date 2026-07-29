// load_object_definition @ 0x44c420 (cdecl)

#include "object_render_types.h"
#include "rtext.h"
#include "sprite.h"

char* get_archive_data_base();
char* load_file_bytes_from_archive_or_fs(char* file_name, char* buffer, int* out_size);
int sprintf(char* buffer, char* format, ...);

void load_object_definition(char* path, Object* object)
{
    char object_file_path[0x100];
    char texture_path[0x80];
    char texture_name[0x80];
    int byte_count;

    char* file_text = get_archive_data_base();
    sprintf(object_file_path, "%s/_Object.txt", path);
    load_file_bytes_from_archive_or_fs(
        object_file_path, file_text, &byte_count);
    file_text[byte_count - 2] = '\0';
    int vertex_count = 0;
    int facequad_count = 0;
    texture_name[0] = '\0';

    char* cursor = file_text;
    char* line_cursor;

    if (*cursor != '\0') {
        do {
            if (*cursor != '*') {
                if (*cursor != '[') {
                    skip_to_next_line(&cursor);
                } else if (strings_equal_case_insensitive(cursor, "[VERTEX START]")) {
                    skip_to_next_line(&cursor);

                    line_cursor = cursor;
                    if (!strings_equal_case_insensitive(cursor, "[VERTEX END]")) {
                        do {
                            ++vertex_count;
                            skip_to_next_line(&line_cursor);
                        } while (!strings_equal_case_insensitive(line_cursor, "[VERTEX END]"));
                    }

                    object->RequestVertices(vertex_count);

                    while (!strings_equal_case_insensitive(cursor, "[VERTEX END]")) {
                        line_cursor = cursor;
                        int index = parse_next_int32(&line_cursor);
                        float x = parse_next_float32(&line_cursor);
                        float y = parse_next_float32(&line_cursor);
                        float z = parse_next_float32(&line_cursor);

                        skip_to_next_line(&cursor);

                        object->vertices[index].x = x;
                        object->vertices[index].y = y;
                        object->vertices[index].z = z;
                    }

                    skip_to_next_line(&cursor);
                } else if (strings_equal_case_insensitive(cursor, "[FACEQUAD START]")) {
                    skip_to_next_line(&cursor);

                    line_cursor = cursor;
                    if (!strings_equal_case_insensitive(cursor, "[FACEQUAD END]")) {
                        do {
                            ++facequad_count;
                            skip_to_next_line(&line_cursor);
                        } while (!strings_equal_case_insensitive(line_cursor, "[FACEQUAD END]"));
                    }

                    object->RequestFaceQuads(facequad_count);

                    while (!strings_equal_case_insensitive(cursor, "[FACEQUAD END]")) {
                        line_cursor = cursor;
                        int face_index = parse_next_int32(&line_cursor);
                        int vertex_0 = parse_next_int32(&line_cursor);
                        int vertex_1 = parse_next_int32(&line_cursor);
                        int vertex_2 = parse_next_int32(&line_cursor);
                        int vertex_3 = parse_next_int32(&line_cursor);
                        float u0 = parse_next_float32(&line_cursor);
                        float v0 = parse_next_float32(&line_cursor);
                        float u1 = parse_next_float32(&line_cursor);
                        float v1 = parse_next_float32(&line_cursor);
                        float u2 = parse_next_float32(&line_cursor);
                        float v2 = parse_next_float32(&line_cursor);
                        float u3 = parse_next_float32(&line_cursor);
                        float v3 = parse_next_float32(&line_cursor);

                        parse_next_space_delimited_token(&line_cursor, texture_name);
                        append_c_string(texture_name, ".tga");
                        copy_c_string(texture_path, path);
                        append_c_string(texture_path, "/");
                        append_c_string(texture_path, texture_name);

                        object->facequads[face_index].texture_ref =
                            g_texture_refs.Add(
                                texture_path, 0, 0);

                        skip_to_next_line(&cursor);

                        object->facequads[face_index].header_word = 0;
                        object->facequads[face_index].vertex_0 =
                            (unsigned short)vertex_0;
                        object->facequads[face_index].vertex_1 =
                            (unsigned short)vertex_1;
                        object->facequads[face_index].vertex_2 =
                            (unsigned short)vertex_2;
                        object->facequads[face_index].vertex_3 =
                            (unsigned short)vertex_3;
                        object->facequads[face_index].uv[0].u = u0;
                        object->facequads[face_index].uv[0].v = v0;
                        object->facequads[face_index].uv[1].u = u1;
                        object->facequads[face_index].uv[1].v = v1;
                        object->facequads[face_index].uv[2].u = u2;
                        object->facequads[face_index].uv[2].v = v2;
                        object->facequads[face_index].uv[3].u = u3;
                        object->facequads[face_index].uv[3].v = v3;
                    }

                    skip_to_next_line(&cursor);
                }
            } else {
                do {
                    ++cursor;
                } while (*cursor != '\n');
                ++cursor;
            }
        } while (*cursor != '\0');
    }

}
