// request_object_texture_groups @ 0x42f930 (thiscall, ret 0x4)

#include "object_render_types.h"

void* allocate_tracked_memory(int size, char* name);
int report_errorf(char* format, ...);

void Object::request_object_texture_groups(int requested_count)
{
    if (texture_group_count == 0) {
        void* result = allocate_tracked_memory(requested_count << 2, "Object FaceQuad Texture Groups");
        texture_group_capacity = requested_count;
        texture_group_count = requested_count;
        texture_group_ends = (int*)result;
    } else {
        if (requested_count > texture_group_capacity) {
            report_errorf("Fixed FaceQuadTextureGroupsNumber too small");
        }
        texture_group_count = requested_count;
    }
}
