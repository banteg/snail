// cRDirectX::Init @ 0x405c90 (thiscall, ret)

#include "directx_loader.h"
#include "rshell.h"

extern char g_x_animation_script_path[]; // "XAnimation.txt"

void cRDirectX::Init()
{
    cached_x_mesh_count = 0;
    animation_bytes = load_file_bytes(g_x_animation_script_path, 0);
    duplicate_vertices.Init(2000);
}
