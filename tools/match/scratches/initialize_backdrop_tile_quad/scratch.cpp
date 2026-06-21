// initialize_backdrop_tile_quad @ 0x41a4d0 (cdecl)

#include "object_render_types.h"
#include "sprite.h"

#define SHRINK_BACKDROP_TILE_COMPONENT(component_expr)     \
    do {                                                   \
        float* component = &(component_expr);               \
        float component_value = *(volatile float*)component;\
        int sign;                                          \
        if (component_value < 0.0f) {                       \
            sign = -1;                                     \
        } else {                                           \
            float zero_check = *component;                  \
            sign = 0;                                      \
            if (zero_check != 0.0f)                         \
                sign = 1;                                  \
        }                                                  \
        *component = *component - (float)sign * 0.2f;       \
    } while (0)

void initialize_backdrop_tile_quad(
    Object* object,
    int edge_selector,
    int orientation,
    int row_selector,
    int column_selector,
    char* texture_path)
{
    float row_offset = (float)row_selector * 0.40000001f;
    float column_offset = (float)column_selector * 0.40000001f;

    object->request_object_vertices(4);
    object->request_object_facequads(1);

    Vector3* vertices = object->vertices;
    ObjectFaceQuad* quad = object->facequads;

    vertices[0].y = 0.0f;
    vertices[1].y = 0.0f;
    vertices[2].y = 0.0f;
    vertices[3].y = 0.0f;

    *(unsigned short*)&quad->flags = 0;
    quad->vertex_0 = 0;
    quad->vertex_1 = 1;
    quad->vertex_2 = 3;
    quad->vertex_3 = 2;
    quad->texture_ref = g_texture_refs.get_or_create_texture_ref(texture_path, 0, 0);

    quad->uv[0].u = 0.80000001f;
    quad->uv[0].v = 1.0f;
    quad->uv[1].u = 0.2f;
    quad->uv[1].v = 1.0f;
    quad->uv[2].u = 0.2f;
    quad->uv[2].v = 0.0f;
    quad->uv[3].u = 0.80000001f;
    quad->uv[3].v = 0.0f;

    switch (orientation) {
    case 0:
        vertices[0].x = row_offset + 0.5f;
        vertices[0].z = 0.89999998f;
        vertices[1].x = -0.5f - column_offset;
        vertices[1].z = 0.89999998f;
        vertices[2].x = 0.5f;
        vertices[2].z = 0.5f;
        vertices[3].x = -0.5f;
        vertices[3].z = 0.5f;
        break;
    case 1:
        rotate_object_facequad_uv_pairs(quad);
        vertices[0].x = 0.89999998f;
        vertices[0].z = column_offset + 0.5f;
        vertices[1].x = 0.5f;
        vertices[1].z = 0.5f;
        vertices[2].x = 0.89999998f;
        vertices[2].z = -0.5f - row_offset;
        vertices[3].x = 0.5f;
        vertices[3].z = -0.5f;
        break;
    case 2:
        rotate_object_facequad_uv_pairs(quad);
        rotate_object_facequad_uv_pairs(quad);
        rotate_object_facequad_uv_pairs(quad);
        vertices[0].x = -0.5f;
        vertices[0].z = 0.5f;
        vertices[1].x = -0.89999998f;
        vertices[1].z = row_offset + 0.5f;
        vertices[2].x = -0.5f;
        vertices[2].z = -0.5f;
        vertices[3].x = -0.89999998f;
        vertices[3].z = -0.5f - column_offset;
        break;
    case 3:
        rotate_object_facequad_uv_pairs(quad);
        rotate_object_facequad_uv_pairs(quad);
        vertices[0].x = 0.5f;
        vertices[0].z = -0.5f;
        vertices[1].x = -0.5f;
        vertices[1].z = -0.5f;
        vertices[2].x = column_offset + 0.5f;
        vertices[2].z = -0.89999998f;
        vertices[3].x = -0.5f - row_offset;
        vertices[3].z = -0.89999998f;
        break;
    }

    int edge_index = edge_selector - 1;
    float* z_component = &vertices[0].z;
    int vertex_count = 4;
    do {
        switch (edge_index) {
        case 0:
            if (z_component[-2] < 0.0f && *z_component < 0.0f) {
                SHRINK_BACKDROP_TILE_COMPONENT(z_component[-2]);
                SHRINK_BACKDROP_TILE_COMPONENT(*z_component);
            }
            break;
        case 1:
            if (z_component[-2] < 0.0f && *z_component > 0.0f) {
                SHRINK_BACKDROP_TILE_COMPONENT(z_component[-2]);
                SHRINK_BACKDROP_TILE_COMPONENT(*z_component);
            }
            break;
        case 2:
            if (z_component[-2] > 0.0f && *z_component < 0.0f) {
                SHRINK_BACKDROP_TILE_COMPONENT(z_component[-2]);
                SHRINK_BACKDROP_TILE_COMPONENT(*z_component);
            }
            break;
        case 3:
            if (z_component[-2] > 0.0f && *z_component > 0.0f) {
                SHRINK_BACKDROP_TILE_COMPONENT(z_component[-2]);
                SHRINK_BACKDROP_TILE_COMPONENT(*z_component);
            }
            break;
        case 4:
            if (z_component[-2] > 0.0f) {
                if (*z_component > 0.0f) {
                    if (*(int*)z_component == 0x3f000000)
                        z_component[-1] = z_component[-1] + 0.5f;
                    else
                        z_component[-1] = z_component[-1] + 0.60000002f;
                }
            }
            break;
        case 5:
            if (*z_component > 0.0f) {
                if (*(int*)z_component == 0x3f000000)
                    z_component[-1] = z_component[-1] + 0.5f;
                else
                    z_component[-1] = z_component[-1] + 0.60000002f;
            }
            break;
        case 6:
            if (z_component[-2] < 0.0f) {
                if (*z_component > 0.0f) {
                    if (*(int*)z_component == 0x3f000000)
                        z_component[-1] = z_component[-1] + 0.5f;
                    else
                        z_component[-1] = z_component[-1] + 0.60000002f;
                }
            }
            break;
        }
        z_component += 3;
        --vertex_count;
    } while (vertex_count != 0);
}

#undef SHRINK_BACKDROP_TILE_COMPONENT
