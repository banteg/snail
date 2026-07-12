// build_snail_hotspots @ 0x445d50 (thiscall, ret)

#include "object_render_types.h"
#include "player.h"
#include "sprite.h"

int report_errorf(char* format, ...);

extern char* g_snail_hotspot_texture_names[]; // data_4a4aa0
extern char* g_snail_hotspot_texture_names_end[]; // 0x4a4aec, first string after the pointer table

void Snail::build_snail_hotspots()
{
    Object* model = snail_hotspot_model;
    char** name_cursor = g_snail_hotspot_texture_names;
    float* hotspot_z = &snail_hotspots_local[0].z;

    do {
        *hotspot_z = 0.0f;
        hotspot_z[-1] = 0.0f;
        hotspot_z[-2] = 0.0f;

        char* texture_name = *name_cursor;
        TextureRef* texture = g_texture_refs.get_or_create_texture_ref(texture_name, 0, 0);
        int facequad_count = model->facequad_count;
        int face_index = 0;

        if (facequad_count <= 0) {
            report_errorf("Cannot find HotPoint Texture %s", *name_cursor);
        } else {
            ObjectFaceQuad* facequad = model->facequads;
            while (1) {
                if (facequad->texture_ref == texture)
                    break;
                ++face_index;
                ++facequad;
                if (face_index >= facequad_count) {
                    report_errorf("Cannot find HotPoint Texture %s", *name_cursor);
                    goto next_hotspot;
                }
            }

            int vertex_index = model->facequads[face_index].vertex_0;
            Vector3* vertex = &model->vertices[vertex_index];
            hotspot_z[-2] += vertex->x;
            hotspot_z[-1] += vertex->y;
            *hotspot_z += vertex->z;
        }

    next_hotspot:
        ++name_cursor;
        hotspot_z += 3;
    } while ((int)name_cursor < (int)g_snail_hotspot_texture_names_end);

    snail_hotspots_local[18].y += 0.300000012f;
}
