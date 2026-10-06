// FontMake3D @ 0x44ae10 (cdecl)

#include "bod_types.h"
#include "font_system.h"
#include "object_render_types.h"

void FontMake3D(short font_id)
{
    int font = font_id;
    int index = 0;

    if (g_font_sheets[font].slot_count > 0) {
        do {
            BodBase* bod = &g_font3d_bods[index];
            Object*& object = bod->object;
            float scale = g_font_sheets[font].glyph_width[index]
                / g_font_sheets[font].line_marker_y;
            bod->SetObject(g_object_list.Add());

            load_object_definition("Objects/Font3D", object);
            bod->render_arg_1c = 0;
            bod->render_arg_20 = 0.0f;

            int texture_page = g_font_sheets[font].texture_page[index];
            object->facequads[0].texture_ref =
                (&g_font_sheets[font].texture_ref_a)[texture_page];
            object->facequads[0].uv[0].u =
                g_font_sheets[font].glyph_u0[index];
            object->facequads[0].uv[0].v =
                1.0f - g_font_sheets[font].glyph_v0;
            object->facequads[0].uv[1].u =
                g_font_sheets[font].glyph_u1[index];
            object->facequads[0].uv[1].v =
                1.0f - g_font_sheets[font].glyph_v0;
            object->facequads[0].uv[2].u =
                g_font_sheets[font].glyph_u1[index];
            object->facequads[0].uv[2].v =
                1.0f - g_font_sheets[font].glyph_v1;
            object->facequads[0].uv[3].u =
                g_font_sheets[font].glyph_u0[index];
            object->facequads[0].uv[3].v =
                1.0f - g_font_sheets[font].glyph_v1;

            object->vertices[0].x = scale * object->vertices[0].x;
            object->vertices[1].x = scale * object->vertices[1].x;
            object->vertices[2].x = scale * object->vertices[2].x;
            object->vertices[3].x = scale * object->vertices[3].x;

            object->blend_mode = 1;
            object->flags |= OBJECT_FLAG_REFRESH_TINT_EACH_DRAW;
            g_font3d_scales[index] = scale;
            ++index;
        } while (index < g_font_sheets[font].slot_count);
    }

}
