// initialize_font3d_objects @ 0x44ae10 (cdecl)

#include "bod_types.h"
#include "font_system.h"
#include "object_render_types.h"

extern BodBase g_font3d_bods[];    // data_7754e8
extern float g_font3d_scales[];    // data_7770e8

int initialize_font3d_objects(short font_id)
{
    int font = font_id;
    FontSheet* sheet = &g_font_sheets[font];
    int index = 0;

    if (sheet->slot_count > 0) {
        do {
            float scale = sheet->glyph_width[index] / sheet->line_marker_y;
            BodBase* bod = &g_font3d_bods[index];
            bod->set_bod_object(g_object_list.add_object_to_list());

            Object* object = (Object*)bod->object;
            load_object_definition("Objects/Font3D", (Object*)bod->object);
            bod->render_arg_1c = 0;
            bod->render_arg_20 = 0.0f;

            ObjectFaceQuad* quad = object->facequads;
            TextureRef** textures = &sheet->texture_ref_a;
            quad->texture_ref = textures[sheet->texture_page[index]];
            quad->uv[0].u = sheet->u0[index];
            quad->uv[0].v = 1.0f - sheet->line_step;
            quad->uv[1].u = sheet->v0[index];
            quad->uv[1].v = 1.0f - sheet->line_step;
            quad->uv[2].u = sheet->v0[index];
            quad->uv[2].v = 1.0f - sheet->line_marker_fraction;
            quad->uv[3].u = sheet->u0[index];
            quad->uv[3].v = 1.0f - sheet->line_marker_fraction;

            Vector3* vertices = object->vertices;
            vertices[0].x = scale * vertices[0].x;
            vertices[1].x = scale * vertices[1].x;
            vertices[2].x = scale * vertices[2].x;
            vertices[3].x = scale * vertices[3].x;

            object->blend_mode = 1;
            object->flags |= 0x10;
            g_font3d_scales[index] = scale;
            ++index;
        } while (index < sheet->slot_count);
    }

    return index;
}
