// apply_object_toon @ 0x42fa80 (thiscall)

#include "object_render_types.h"

void* allocate_tracked_memory(int size, char* name);

void Object::apply_object_toon(int toon_flags)
{
    toon_flags |= 0x4001;
    flags |= toon_flags;
    toon_vertices =
        (Vector3*)allocate_tracked_memory(vertex_count * 12, "Object Toon Vertices");
    toon_facequad_normals = (ObjectToonFaceQuadNormal*)allocate_tracked_memory(
        facequad_count * 24, "Object Toon FaceQuadNormals");
}
