// initialize_object @ 0x42f6f0 (thiscall, ret)

class Object {
public:
    int initialize_object();

    char unknown_00[0x10];
    int object_flags; // +0x10
    int field_14; // +0x14
    char unknown_18[0x2c - 0x18];
    int vertex_count; // +0x2c
    char unknown_30[0x40 - 0x30];
    int field_40; // +0x40
    void* vertex_normals; // +0x44
    char unknown_48[0x54 - 0x48];
    int facequad_count; // +0x54
    char unknown_58[0x64 - 0x58];
    int texture_group_count; // +0x64
};

int Object::initialize_object()
{
    object_flags = 0;
    field_14 = 0;
    vertex_count = 0;
    facequad_count = 0;
    vertex_normals = 0;
    field_40 = 0;
    texture_group_count = 0;
    return 0;
}
