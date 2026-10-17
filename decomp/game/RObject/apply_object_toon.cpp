// ApplyToon @ 0x42fa80 (thiscall)

#include "object_render_types.h"
#include "tracked_allocation_stack.h"

void cRObject::ApplyToon(int toon_flags)
{
    toon_flags |= OBJECT_FLAG_TOON_ENABLED | OBJECT_FLAG_BUILD_TOON_EDGES;
    flags |= toon_flags;
    toon_vertices =
        (Vector3*)allocate_tracked_memory(vertex_count * 12, "Object Toon Vertices");
    toon_facequad_normals = (ObjectToonFaceQuadNormal*)allocate_tracked_memory(
        facequad_count * 24, "Object Toon FaceQuadNormals");
}
