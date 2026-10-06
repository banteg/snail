// initialize_object_list @ 0x42f990 (thiscall, ret 0x4)

#include "object_render_types.h"

void* allocate_tracked_memory(int size, char* name);

void cRObjects::Init(int object_capacity)
{
    count = 0;
    capacity = object_capacity;
    objects = (Object*)allocate_tracked_memory(
        sizeof(Object) * object_capacity, "Object List");

    if (object_capacity > 0) {
        int offset = 0;
        do {
            Object* object = (Object*)((char*)objects + offset);
            object->Init();
            offset += sizeof(Object);
            --object_capacity;
        } while (object_capacity != 0);
    }
}
