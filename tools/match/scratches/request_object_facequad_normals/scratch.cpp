// request_object_facequad_normals @ 0x42f800 (thiscall, ret)

#include "object_render_types.h"

void* allocate_tracked_memory(int size, char* name);

void* Object::request_object_facequad_normals()
{
    if (vertex_normals == 0)
        vertex_normals =
            (Vector3*)allocate_tracked_memory(
                vertex_count * sizeof(Vector3), "Object Vertex Normals List");

    Vector3* result = facequad_normals;
    if (result == 0) {
        result =
            (Vector3*)allocate_tracked_memory(
                facequad_count * sizeof(Vector3) * 2,
                "Object FaceQuad Normals List");
        facequad_normals = result;
    }
    return result;
}
