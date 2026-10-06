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
                    RTextNewLine(&cursor);
                } else if (RTextCompStart(cursor, "[VERTEX START]")) {
                    RTextNewLine(&cursor);

                    line_cursor = cursor;
                    if (!RTextCompStart(cursor, "[VERTEX END]")) {
                        do {
                            ++vertex_count;
                            RTextNewLine(&line_cursor);
                        } while (!RTextCompStart(line_cursor, "[VERTEX END]"));
                    }

                    object->RequestVertices(vertex_count);

                    while (!RTextCompStart(cursor, "[VERTEX END]")) {
                        line_cursor = cursor;
                        int index = RTextExtractInt(&line_cursor);
                        float x = RTextExtractFloat(&line_cursor);
                        float y = RTextExtractFloat(&line_cursor);
                        float z = RTextExtractFloat(&line_cursor);

                        RTextNewLine(&cursor);

                        object->vertices[index].x = x;
                        object->vertices[index].y = y;
                        object->vertices[index].z = z;
                    }

                    RTextNewLine(&cursor);
                } else if (RTextCompStart(cursor, "[FACEQUAD START]")) {
                    RTextNewLine(&cursor);

                    line_cursor = cursor;
                    if (!RTextCompStart(cursor, "[FACEQUAD END]")) {
                        do {
                            ++facequad_count;
                            RTextNewLine(&line_cursor);
                        } while (!RTextCompStart(line_cursor, "[FACEQUAD END]"));
                    }

                    object->RequestFaceQuads(facequad_count);

                    while (!RTextCompStart(cursor, "[FACEQUAD END]")) {
                        line_cursor = cursor;
                        int face_index = RTextExtractInt(&line_cursor);
                        int vertex_0 = RTextExtractInt(&line_cursor);
                        int vertex_1 = RTextExtractInt(&line_cursor);
                        int vertex_2 = RTextExtractInt(&line_cursor);
                        int vertex_3 = RTextExtractInt(&line_cursor);
                        float u0 = RTextExtractFloat(&line_cursor);
                        float v0 = RTextExtractFloat(&line_cursor);
                        float u1 = RTextExtractFloat(&line_cursor);
                        float v1 = RTextExtractFloat(&line_cursor);
                        float u2 = RTextExtractFloat(&line_cursor);
                        float v2 = RTextExtractFloat(&line_cursor);
                        float u3 = RTextExtractFloat(&line_cursor);
                        float v3 = RTextExtractFloat(&line_cursor);

                        RTextExtractString(&line_cursor, texture_name);
                        RTextAppend(texture_name, ".tga");
                        RTextCopy(texture_path, path);
                        RTextAppend(texture_path, "/");
                        RTextAppend(texture_path, texture_name);

                        object->facequads[face_index].texture_ref =
                            g_texture_refs.Add(
                                texture_path, 0, 0);

                        RTextNewLine(&cursor);

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

                    RTextNewLine(&cursor);
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
