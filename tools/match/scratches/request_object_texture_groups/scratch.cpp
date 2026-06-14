// request_object_texture_groups @ 0x42f930 (thiscall, ret 0x4)

void* allocate_tracked_memory(int size, char* name);
int report_errorf(char* format, ...);

class Object {
public:
    void* request_object_texture_groups(int group_count);

    char unknown_00[0x64];
    int texture_group_count; // +0x64
    int texture_group_capacity; // +0x68
    void* texture_groups; // +0x6c
};

void* Object::request_object_texture_groups(int requested_count)
{
    void* result;
    if (texture_group_count == 0) {
        result = allocate_tracked_memory(requested_count << 2, "Object FaceQuad Texture Groups");
        texture_group_capacity = requested_count;
        texture_group_count = requested_count;
        texture_groups = result;
    } else {
        int count = requested_count;
        int capacity = texture_group_capacity;
        if (count <= capacity) {
            result = (void*)capacity;
        } else {
            result = (void*)report_errorf("Fixed FaceQuadTextureGroupsNumber too small");
        }
        texture_group_count = count;
    }
    return result;
}
