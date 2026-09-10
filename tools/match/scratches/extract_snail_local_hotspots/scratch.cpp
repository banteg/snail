// extract_snail_local_hotspots @ 0x445d50 (thiscall, ret)

#include "object_render_types.h"
#include "player.h"
#include "sprite.h"

int report_errorf(char* format, ...);

extern char* g_snail_hotspot_texture_names[]; // data_4a4aa0
extern char* g_snail_hotspot_texture_names_end[]; // 0x4a4aec, first string after the pointer table

void cRSnail::ExtractHotSpots()
{
    Object* model = snail_hotspot_body.object;
    char** name_cursor = g_snail_hotspot_texture_names;
    float* hotspot_z = &snail_hotspots_local[0].z;

    do {
        *hotspot_z = 0.0f;
        hotspot_z[-1] = 0.0f;
        hotspot_z[-2] = 0.0f;

        char* texture_name = *name_cursor;
        cRTexture* texture = g_texture_refs.Add(texture_name, 0, 0);
        float count = 0;
        for (int face_index = 0; face_index < model->facequad_count; ++face_index) {
            if (model->facequads[face_index].texture_ref == texture) {
                Vector3* vertex = &model->vertices[model->facequads[face_index].vertex_0];
                hotspot_z[-2] += vertex->x;
                hotspot_z[-1] += vertex->y;
                *hotspot_z += vertex->z;
                ++count;
                break;
            }
        }
        if (count == 0) {
            report_errorf("Cannot find HotPoint Texture %s", *name_cursor);
        } else {
            float scale = 1.0f / count;
            hotspot_z[-2] *= scale;
            hotspot_z[-1] *= scale;
            *hotspot_z *= scale;
        }

        ++name_cursor;
        hotspot_z += 3;
    } while ((int)name_cursor < (int)g_snail_hotspot_texture_names_end);

    snail_hotspots_local[SNAIL_HOTSPOT_CAMERA_INTRO_TALK].y += 0.300000012f;
}
