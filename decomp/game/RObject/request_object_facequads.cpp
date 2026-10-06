// RequestFaceQuads @ 0x42f8c0 (thiscall, ret 0x4)

#include "object_render_types.h"

#include "tracked_allocation_stack.h"
#include "rdebug.h"

void cRObject::RequestFaceQuads(int requested_count)
{
    if (requested_count == 0) {
        facequad_count = 0;
        return;
    }

    int capacity = facequad_capacity;
    if (capacity > 0 && capacity < requested_count) {
        report_errorf("Reallocation of FaceQuads impending\n");
        free_tracked_memory(facequads);
        facequad_count = 0;
    }
    if (facequad_count == 0) {
        facequads =
            (cRFaceQuad*)allocate_tracked_memory(
                requested_count * sizeof(cRFaceQuad), "Object FaceQuad List");
        if (requested_count > facequad_capacity)
            facequad_capacity = requested_count;
    }
    facequad_count = requested_count;
}
