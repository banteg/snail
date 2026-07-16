// load_x_mesh @ 0x405640 (thiscall, ret 0xc)

#include <stdio.h>
#include <string.h>

#include "directx_loader.h"
#include "sprite.h"

char* get_archive_data_base(); // @ 0x431a90
char is_archive_index_loaded(); // @ 0x431a80
char* load_file_bytes_from_archive_or_fs(char* file_name, char* buffer, int* out_size);
char* find_case_insensitive_substring(char* needle, char* haystack); // @ 0x44e600
int parse_next_signed_int(char** cursor); // @ 0x44e710
float parse_next_float32(char** cursor); // @ 0x431f20
void* allocate_tracked_memory(int size, char* name); // @ 0x431b60
void free_tracked_memory(void* pointer); // @ 0x431bf0 / RShellMemoryFree(void*)
int report_errorf(char* format, ...); // @ 0x431cc0
int report_warningf(char* format, ...); // @ 0x431d10

void DirectXLoader::load_x_mesh(char* mesh_path, Object* object, int options_flags)
{
    char* file_text = get_archive_data_base();
    char mesh_file_path[0x100];
    char texture_path[0x100];
    int byte_count;

    if (is_archive_index_loaded() != 0) {
        if (mesh_path[strlen(mesh_path) - 1] != '2')
            sprintf(mesh_file_path, "X/%s2", mesh_path);
        else
            sprintf(mesh_file_path, "X/%s", mesh_path);
    } else {
        sprintf(mesh_file_path, "X/%s", mesh_path);
    }

    load_file_bytes_from_archive_or_fs(mesh_file_path, file_text, &byte_count);
    file_text[byte_count - 2] = 0;

    char* frame_cursor = find_case_insensitive_substring("Frame ", file_text);
    if (frame_cursor == 0) {
        report_errorf("No 'Frame ' Data in %s", mesh_file_path);
        return;
    }
    char* frame_start = frame_cursor;

    char* duplicate_cursor = find_case_insensitive_substring("Mesh ", frame_cursor);
    if (duplicate_cursor == 0)
        report_errorf("No 'VertexDuplicationIndices 'Data in %s", mesh_file_path);
    duplicate_cursor = find_case_insensitive_substring("{", duplicate_cursor);

    char* mesh_cursor = find_case_insensitive_substring("Mesh ", frame_cursor);
    if (mesh_cursor == 0)
        report_errorf("No 'Mesh 'Data in %s", mesh_file_path);
    mesh_cursor = find_case_insensitive_substring("{", mesh_cursor);

    char* material_header_cursor = find_case_insensitive_substring("MeshMaterialList ", frame_cursor);
    if (material_header_cursor == 0)
        report_errorf("No 'MeshMaterialList 'Data in %s", mesh_file_path);
    material_header_cursor = find_case_insensitive_substring("{", material_header_cursor);

    parse_next_signed_int(&material_header_cursor);
    short parsed_facequad_count = (short)parse_next_signed_int(&material_header_cursor);
    int parsed_vertex_count = parse_next_signed_int(&duplicate_cursor);
    int vertex_count = (short)parsed_vertex_count;
    if (vertex_count != parse_next_signed_int(&mesh_cursor))
        report_errorf(
            "Mesh vertices count does not match vertext duplicate vertices count in %s",
            mesh_file_path);
    parse_next_signed_int(&duplicate_cursor);

    char* texcoord_cursor = find_case_insensitive_substring("MeshTextureCoords ", frame_cursor);
    if (texcoord_cursor == 0)
        report_errorf("No 'Mesh 'Data in %s", mesh_file_path);
    texcoord_cursor = find_case_insensitive_substring("{", texcoord_cursor);
    if (vertex_count != parse_next_signed_int(&texcoord_cursor))
        report_errorf(
            "Mesh texture coords number does not match mesh vertext count in %s",
            mesh_file_path);

    int facequad_count = parsed_facequad_count;
    object->request_object_facequads(facequad_count);
    object->request_object_vertices(vertex_count);

    int* vertex_remap =
        (int*)allocate_tracked_memory(vertex_count << 2, "Mesh vertex remap");
    ObjectUv* texture_coords =
        (ObjectUv*)allocate_tracked_memory(vertex_count << 3, "Mesh texture coords");

    int i;
    for (i = 0; i < vertex_count; ++i) {
        texture_coords[i].u = parse_next_float32(&texcoord_cursor);
        texture_coords[i].v = parse_next_float32(&texcoord_cursor);
    }

    if ((short)parsed_vertex_count > 0) {
        int vertex_index = 0;
        do {
            object->vertices[vertex_index].x = parse_next_float32(&mesh_cursor);
            object->vertices[vertex_index].y = parse_next_float32(&mesh_cursor);
            object->vertices[vertex_index].z = parse_next_float32(&mesh_cursor);
            ++vertex_index;
            --vertex_count;
        } while (vertex_count != 0);
    }

    if (facequad_count != parse_next_signed_int(&mesh_cursor))
        report_errorf("Mesh face count does not match material face count in %s", mesh_file_path);

    for (i = 0; i < facequad_count; ++i) {
        object->facequads[i].header_word = 0;

        int arity = parse_next_signed_int(&mesh_cursor);
        int vertex_2 = parse_next_signed_int(&mesh_cursor);
        int vertex_1 = parse_next_signed_int(&mesh_cursor);
        int vertex_0 = parse_next_signed_int(&mesh_cursor);
        int vertex_3;
        if (arity == 4) {
            vertex_3 = parse_next_signed_int(&mesh_cursor);
        } else {
            vertex_3 = 0;
            object->facequads[i].flags |= OBJECT_FACEQUAD_FLAG_TRIANGLE;
        }

        object->facequads[i].uv[2].u = texture_coords[vertex_2].u;
        object->facequads[i].uv[2].v = texture_coords[vertex_2].v;
        object->facequads[i].uv[1].u = texture_coords[vertex_1].u;
        object->facequads[i].uv[1].v = texture_coords[vertex_1].v;
        object->facequads[i].uv[0].u = texture_coords[vertex_0].u;
        object->facequads[i].uv[0].v = texture_coords[vertex_0].v;
        object->facequads[i].uv[3].u = texture_coords[vertex_3].u;
        object->facequads[i].uv[3].v = texture_coords[vertex_3].v;
        object->facequads[i].texture_ref =
            g_texture_refs.get_or_create_texture_ref("X/snail-turbo.tga", 0, 0);
        object->facequads[i].texture_ref->flags |= TEXTURE_REF_WRAP_ADDRESSING;
        object->facequads[i].vertex_2 = (unsigned short)vertex_2;
        object->facequads[i].vertex_1 = (unsigned short)vertex_1;
        object->facequads[i].vertex_0 = (unsigned short)vertex_0;
        object->facequads[i].vertex_3 = (unsigned short)vertex_3;
    }

    object->flags |= OBJECT_FLAG_DISABLE_CULLING;
    free_tracked_memory(texture_coords);
    free_tracked_memory(vertex_remap);

    char* material_cursor = find_case_insensitive_substring("MeshMaterialList", frame_start);
    if (material_cursor == 0) {
        report_errorf("No MeshMaterialList { in %s", mesh_file_path);
        return;
    }

    material_cursor = find_case_insensitive_substring("{", material_cursor);
    int material_count = parse_next_signed_int(&material_cursor);
    int material_face_count = parse_next_signed_int(&material_cursor);
    if (material_face_count != facequad_count) {
        report_errorf(
            "No MeshMaterialList face number is not equal to Mesh face number in %s",
            mesh_file_path);
        return;
    }

    TextureRef** materials = (TextureRef**)allocate_tracked_memory(
        material_count << 2, "Direct X Materiallist");
    char* material_text = material_cursor;
    int material_index = 0;
    if (material_count > 0) {
        TextureRef** material_slot = materials;
        do {
            char* texture_name =
                find_case_insensitive_substring("TextureFilename ", material_text);
            if (texture_name == 0) {
                if ((options_flags & 2) == 0)
                    report_warningf(
                        "No TextureFilename for Material %i in %s",
                        material_index,
                        mesh_file_path);
                *material_slot =
                    g_texture_refs.get_or_create_texture_ref("Sprites/debug.tga", 0, 0);
                material_text = material_cursor;
            } else {
                material_text = find_case_insensitive_substring("\"", texture_name) + 1;
                texture_path[0] = 'X';
                texture_path[1] = '/';
                char* out = texture_path + 2;
                while (*material_text != '.') {
                    *out++ = *material_text++;
                }
                *out++ = '.';
                *out++ = 't';
                *out++ = 'g';
                *out++ = 'a';
                *out = 0;

                *material_slot =
                    g_texture_refs.get_or_create_texture_ref(texture_path, 0, 0);
                (*material_slot)->flags |= TEXTURE_REF_WRAP_ADDRESSING;
                if ((options_flags & 2) != 0)
                    (*material_slot)->flags |= TEXTURE_REF_SKIP_RUNTIME_LOAD;
            }
            ++material_index;
            ++material_slot;
        } while (material_index < material_count);
    }

    for (i = 0; i < material_face_count; ++i) {
        object->facequads[i].texture_ref =
            materials[(short)parse_next_signed_int(&material_cursor)];
    }

    free_tracked_memory(materials);
}
