// initialize_directx_loader @ 0x405c90 (thiscall, ret)

char* load_file_bytes(char* file_name, int* out_size);
extern char g_x_animation_script_path[]; // "XAnimation.txt"

class DuplicateVertexBuffer {
public:
    void* initialize_duplicate_vertices(int count);
};

class DirectXLoader {
public:
    void* initialize_directx_loader();

    char* animation_bytes; // +0x00
    int field_04;          // +0x04
    char pad_008[0x5e08 - 0x008];
    DuplicateVertexBuffer duplicate_vertices; // +0x5e08
};

void* DirectXLoader::initialize_directx_loader()
{
    field_04 = 0;
    animation_bytes = load_file_bytes(g_x_animation_script_path, 0);
    return duplicate_vertices.initialize_duplicate_vertices(2000);
}
