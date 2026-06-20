// add_object_to_list @ 0x42fad0 (thiscall)

#include "object_render_types.h"

int report_errorf(char* format, ...);

Object* ObjectList::add_object_to_list()
{
    if (count == capacity) {
        report_errorf("Too many Objects - Increase ObjectList.Init(MAX) in G0.cpp");
    }

    Object* object = &objects[count++];
    object->initialize_object();
    return object;
}
