// load_object_definition @ 0x44c420 (cdecl)

#include "object_render_types.h"
#include "sprite.h"

char* get_archive_data_base();
char* load_file_bytes_from_archive_or_fs(char* file_name, char* buffer, int* out_size);
int sprintf(char* buffer, char* format, ...);
unsigned char strings_equal_case_insensitive(char* left, char* right);
char* skip_to_next_line(char** cursor);
int parse_next_int32(char** cursor);
float parse_next_float32(char** cursor);
char** parse_next_space_delimited_token(char** cursor, char* out);
unsigned char* copy_c_string(unsigned char* destination, unsigned char* source);
unsigned char* append_c_string(unsigned char* destination, unsigned char* source);

int load_object_definition(char* path, Object* object)
{
    char object_file_path[0x100];
    char texture_path[0x80];
    char texture_name[0x80];
    int byte_count;
    int vertex_count;
    int facequad_count;

    char* file_text = get_archive_data_base();
    sprintf(object_file_path, "%s/_Object.txt", path);
    load_file_bytes_from_archive_or_fs(object_file_path, file_text, &byte_count);
    file_text[byte_count - 2] = '\0';
    texture_name[0] = '\0';

    char* cursor = file_text;
    vertex_count = 0;
    facequad_count = 0;

    if (*cursor != '\0') {
        do {
            if (*cursor != '*') {
                if (*cursor == '[') {
                    if (strings_equal_case_insensitive(cursor, "[VERTEX START]")) {
                        skip_to_next_line(&cursor);

                        char* count_cursor = cursor;
                        if (!strings_equal_case_insensitive(cursor, "[VERTEX END]")) {
                            do {
                                ++vertex_count;
                                skip_to_next_line(&count_cursor);
                            } while (!strings_equal_case_insensitive(count_cursor, "[VERTEX END]"));
                        }

                        object->request_object_vertices(vertex_count);

                        while (!strings_equal_case_insensitive(cursor, "[VERTEX END]")) {
                            char* line_cursor = cursor;
                            int index = parse_next_int32(&line_cursor);
                            float x = parse_next_float32(&line_cursor);
                            float y = parse_next_float32(&line_cursor);
                            float z = parse_next_float32(&line_cursor);

                            skip_to_next_line(&cursor);

                            Vector3* vertex = &object->vertices[index];
                            vertex->x = x;
                            vertex->y = y;
                            vertex->z = z;
                        }
                    } else if (strings_equal_case_insensitive(cursor, "[FACEQUAD START]")) {
                        skip_to_next_line(&cursor);

                        char* count_cursor = cursor;
                        if (!strings_equal_case_insensitive(cursor, "[FACEQUAD END]")) {
                            do {
                                ++facequad_count;
                                skip_to_next_line(&count_cursor);
                            } while (!strings_equal_case_insensitive(count_cursor, "[FACEQUAD END]"));
                        }

                        object->request_object_facequads(facequad_count);

                        while (!strings_equal_case_insensitive(cursor, "[FACEQUAD END]")) {
                            char* line_cursor = cursor;
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
                            append_c_string((unsigned char*)texture_name, (unsigned char*)".tga");
                            copy_c_string((unsigned char*)texture_path, (unsigned char*)path);
                            append_c_string((unsigned char*)texture_path, (unsigned char*)"/");
                            append_c_string((unsigned char*)texture_path, (unsigned char*)texture_name);

                            ObjectFaceQuad* quad = &object->facequads[face_index];
                            quad->texture_ref = g_texture_refs.get_or_create_texture_ref(texture_path, 0, 0);

                            skip_to_next_line(&cursor);

                            *(unsigned short*)quad = 0;
                            quad->vertex_0 = (unsigned short)vertex_0;
                            quad->vertex_1 = (unsigned short)vertex_1;
                            quad->vertex_2 = (unsigned short)vertex_2;
                            quad->vertex_3 = (unsigned short)vertex_3;
                            quad->uv[0].u = u0;
                            quad->uv[0].v = v0;
                            quad->uv[1].u = u1;
                            quad->uv[1].v = v1;
                            quad->uv[2].u = u2;
                            quad->uv[2].v = v2;
                            quad->uv[3].u = u3;
                            quad->uv[3].v = v3;
                        }
                    }
                }

                skip_to_next_line(&cursor);
            } else {
                do {
                    ++cursor;
                } while (*cursor != '\n');
                ++cursor;
            }
        } while (*cursor != '\0');
    }

    return (int)cursor;
}
