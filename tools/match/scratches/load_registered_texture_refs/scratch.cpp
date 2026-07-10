// load_registered_texture_refs @ 0x412a00 (cdecl)

#include "texture_registry.h"

void* allocate_tracked_memory(int size, char* name); // @ 0x431b60
void load_registered_texture_ref(int texture_index, int unused_legacy_mode); // @ 0x412a70
int debug_report_stub(char* format, ...); // @ 0x449c00, stripped in release

void load_registered_texture_refs(int legacy_mode)
{
    g_d3d_texture_slots = (Direct3DTexture8**)allocate_tracked_memory(
        g_texture_refs.count * sizeof(Direct3DTexture8*),
        "DirectX Texture name list");

    g_estimated_texture_vram_bytes = 0;
    for (int index = 0; index < g_texture_refs.count; ++index) {
        load_registered_texture_ref(index, legacy_mode);
    }

    debug_report_stub("Estimate %i K VRAM\n", g_estimated_texture_vram_bytes / 1024);
}
