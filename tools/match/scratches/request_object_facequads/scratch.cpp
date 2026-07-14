// request_object_facequads @ 0x42f8c0 (thiscall, ret 0x4)

#include "object_render_types.h"

void* allocate_tracked_memory(int size, char* name);
void free_tracked_memory(void* ptr);
int report_errorf(char* format, ...);

void Object::request_object_facequads(int requested_count)
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
            (ObjectFaceQuad*)allocate_tracked_memory(
                requested_count * sizeof(ObjectFaceQuad), "Object FaceQuad List");
        if (requested_count > facequad_capacity)
            facequad_capacity = requested_count;
    }
    facequad_count = requested_count;
}
