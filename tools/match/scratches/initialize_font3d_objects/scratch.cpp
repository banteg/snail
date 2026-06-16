// initialize_font3d_objects @ 0x44ae10 (cdecl)

#include "bod_types.h"
#include "font_system.h"

struct Font3DFacequad {
    char unknown_00[0x0c];
    TextureRef* texture; // +0x0c
    float u0;            // +0x10
    float v0;            // +0x14
    float u1;            // +0x18
    float v1;            // +0x1c
    float u2;            // +0x20
    float v2;            // +0x24
    float u3;            // +0x28
    float v3;            // +0x2c
};

struct Font3DObject {
    char unknown_00[0x10];
    int flags;             // +0x10
    int ready;             // +0x14
    char unknown_18[0x38 - 0x18];
    float* vertices;       // +0x38
    char unknown_3c[0x5c - 0x3c];
    Font3DFacequad* quads; // +0x5c
};

extern BodBase g_font3d_bods[];    // data_7754e8
extern float g_font3d_scales[];    // data_7770e8
extern int g_object_list;          // data_4b7648

void* __fastcall add_object_to_list(void* list); // @ 0x42fad0
int load_object_definition(char* path, void* object); // @ 0x44c420

int initialize_font3d_objects(short font_id)
{
    int font = font_id;
    FontSheet* sheet = &g_font_sheets[font];
    int index = 0;

    if (sheet->slot_count > 0) {
        do {
            float scale = sheet->glyph_width[index] / sheet->line_marker_y;
            BodBase* bod = &g_font3d_bods[index];
            bod->set_bod_object(add_object_to_list(&g_object_list));

            Font3DObject* object = (Font3DObject*)bod->object;
            load_object_definition("Objects/Font3D", object);
            bod->unknown_1c = 0;
            bod->unknown_20 = 0;

            Font3DFacequad* quad = object->quads;
            TextureRef** textures = &sheet->texture_ref_a;
            quad->texture = textures[sheet->texture_page[index]];
            quad->u0 = sheet->u0[index];
            quad->v0 = 1.0f - sheet->line_step;
            quad->u1 = sheet->v0[index];
            quad->v1 = 1.0f - sheet->line_step;
            quad->u2 = sheet->v0[index];
            quad->v2 = 1.0f - sheet->line_marker_fraction;
            quad->u3 = sheet->u0[index];
            quad->v3 = 1.0f - sheet->line_marker_fraction;

            float* vertices = object->vertices;
            vertices[0] = scale * vertices[0];
            vertices[3] = scale * vertices[3];
            vertices[6] = scale * vertices[6];
            vertices[9] = scale * vertices[9];

            object->ready = 1;
            object->flags |= 0x10;
            g_font3d_scales[index] = scale;
            ++index;
        } while (index < sheet->slot_count);
    }

    return index;
}
