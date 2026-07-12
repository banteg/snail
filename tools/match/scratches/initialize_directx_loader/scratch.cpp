// initialize_directx_loader @ 0x405c90 (thiscall, ret)

#include "directx_loader.h"

char* load_file_bytes(char* file_name, int* out_size);
extern char g_x_animation_script_path[]; // "XAnimation.txt"

void DirectXLoader::initialize_directx_loader()
{
    cached_x_mesh_count = 0;
    animation_bytes = load_file_bytes(g_x_animation_script_path, 0);
    duplicate_vertices.initialize_duplicate_vertices(2000);
}
