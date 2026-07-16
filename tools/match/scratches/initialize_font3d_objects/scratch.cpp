// initialize_font3d_objects @ 0x44ae10 (cdecl)

#include "bod_types.h"
#include "font_system.h"
#include "object_render_types.h"

void initialize_font3d_objects(short font_id)
{
    int font = font_id;
    int index = 0;

    if (g_font_sheets[font].slot_count > 0) {
        float* scale_out = g_font3d_scales;
        do {
            BodBase* bod = &g_font3d_bods[index];
            float scale = g_font_sheets[font].glyph_width[index]
                / g_font_sheets[font].line_marker_y;
            bod->set_bod_object(g_object_list.add_object_to_list());

            load_object_definition("Objects/Font3D", bod->object);
            bod->render_arg_1c = 0;
            bod->render_arg_20 = 0.0f;

            int texture_page = g_font_sheets[font].texture_page[index];
            bod->object->facequads[0].texture_ref =
                (&g_font_sheets[font].texture_ref_a)[texture_page];
            bod->object->facequads[0].uv[0].u =
                g_font_sheets[font].u0[index];
            bod->object->facequads[0].uv[0].v =
                1.0f - g_font_sheets[font].line_step;
            bod->object->facequads[0].uv[1].u =
                g_font_sheets[font].v0[index];
            bod->object->facequads[0].uv[1].v =
                1.0f - g_font_sheets[font].line_step;
            bod->object->facequads[0].uv[2].u =
                g_font_sheets[font].v0[index];
            bod->object->facequads[0].uv[2].v =
                1.0f - g_font_sheets[font].line_marker_fraction;
            bod->object->facequads[0].uv[3].u =
                g_font_sheets[font].u0[index];
            bod->object->facequads[0].uv[3].v =
                1.0f - g_font_sheets[font].line_marker_fraction;

            bod->object->vertices[0].x = scale * bod->object->vertices[0].x;
            bod->object->vertices[1].x = scale * bod->object->vertices[1].x;
            bod->object->vertices[2].x = scale * bod->object->vertices[2].x;
            bod->object->vertices[3].x = scale * bod->object->vertices[3].x;

            bod->object->blend_mode = 1;
            bod->object->flags |= OBJECT_FLAG_REFRESH_TINT_EACH_DRAW;
            *scale_out = scale;
            ++index;
            ++scale_out;
        } while (index < g_font_sheets[font].slot_count);
    }

}
