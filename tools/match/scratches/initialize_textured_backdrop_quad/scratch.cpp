// initialize_textured_backdrop_quad @ 0x41a0b0 (cdecl)

#include "object_render_types.h"
#include "sprite.h"

void initialize_textured_backdrop_quad(Object* object, char* texture_path, float x_offset)
{
    object->request_object_vertices(4);
    object->request_object_facequads(1);

    float left_x = x_offset + 0.5f;
    Vector3* vertices = object->vertices;
    ObjectFaceQuad* quad = object->facequads;

    vertices[0].y = 0.0f;
    vertices[0].x = left_x;
    vertices[2].x = left_x;
    vertices[0].z = 0.5f;
    vertices[1].x = -0.5f;
    vertices[1].y = 0.0f;
    vertices[1].z = 0.5f;
    vertices[2].y = 0.0f;
    vertices[2].z = -0.5f;
    vertices[3].x = -0.5f;
    vertices[3].y = 0.0f;
    vertices[3].z = -0.5f;

    *(unsigned short*)&quad->flags = 0;
    quad->vertex_0 = 0;
    quad->vertex_1 = 1;
    quad->vertex_2 = 3;
    quad->vertex_3 = 2;

    TextureRef* texture = g_texture_refs.get_or_create_texture_ref(texture_path, 0, 0);
    float right_u = x_offset + 1.0f;
    quad->texture_ref = texture;
    texture->flags |= 2;
    quad->uv[1].u = right_u;
    quad->uv[2].u = right_u;
    quad->uv[0].u = 0.0f;
    quad->uv[2].v = 0.0f;
    quad->uv[3].u = 0.0f;
    quad->uv[3].v = 0.0f;
    quad->uv[0].v = 1.0f;
    quad->uv[1].v = 1.0f;
}
