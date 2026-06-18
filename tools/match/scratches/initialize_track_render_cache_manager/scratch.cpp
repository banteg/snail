// initialize_track_render_cache_manager @ 0x433060 (thiscall, ret)

#include "object_render_types.h"
#include "track_render_cache.h"

void* allocate_tracked_memory(int size, char* name);

struct VertexBufferFactory {
    void* create_vertex_buffer(int vertex_count, int fvf); // @ 0x4114b0
};

struct IndexBufferFactory {
    ObjectIndexBuffer* create_index_buffer(int index_count); // @ 0x4115d0
};

extern char* g_game_base; // data_4df904
extern VertexBufferFactory g_direct3d_renderer; // data_4f7458
extern IndexBufferFactory g_object_index_buffer_factory; // data_5000fc

struct TrackRenderCacheSlotCursor {
    char unknown_00[0x58];
    BodBase bod; // +0x58
};

void* TrackRenderCacheManager::initialize_track_render_cache_manager()
{
    int vertex_count = 560;
    int index_count = 1280;
    max_vertex_counts[0] = vertex_count;
    max_vertex_counts[1] = vertex_count;
    max_index_counts[0] = index_count;
    max_index_counts[1] = index_count;
    vertex_count = 160;
    max_vertex_counts[2] = vertex_count;
    max_index_counts[2] = 240;
    max_vertex_counts[3] = 80;
    max_index_counts[3] = vertex_count;
    max_vertex_counts[4] = 800;
    max_index_counts[4] = index_count;
    track_render_grid = (TrackRenderGrid*)(g_game_base + 0x74618);

    int slot_base = 0;
    Object** skirt_object_ref = (Object**)&slots[0][4].bod.object;
    int i;
    do {
        for (i = 0; i < 5; ++i) {
            TrackRenderCacheSlotCursor* slot =
                (TrackRenderCacheSlotCursor*)((char*)this + (slot_base + i) * 0x3c);
            slot->bod.set_bod_object(g_object_list.add_object_to_list());

            ((Object*)slot->bod.object)->flags = 0x80000;
            ((Object*)slot->bod.object)->vertex_count = 0;
            ((Object*)slot->bod.object)->vertices = 0;
            ((Object*)slot->bod.object)->facequad_count = 0;
            ((Object*)slot->bod.object)->facequads = 0;
            ((Object*)slot->bod.object)->texture_group_count = 1;
            ((Object*)slot->bod.object)->render_buffers =
                (ObjectRenderBuffers*)g_direct3d_renderer.create_vertex_buffer(
                    max_vertex_counts[i], 0x142);
            ((Object*)slot->bod.object)->index_buffer =
                g_object_index_buffer_factory.create_index_buffer(max_index_counts[i]);
            ((Object*)slot->bod.object)->group_index_starts =
                (int*)allocate_tracked_memory(4, "DX TextureGroups");
            ((Object*)slot->bod.object)->group_index_starts[0] = 0;
            ((Object*)slot->bod.object)->group_texture_refs =
                (TextureRef**)allocate_tracked_memory(4, "DX TextureGroupsTexture Ref");
            ((Object*)slot->bod.object)->group_primitive_counts =
                (int*)allocate_tracked_memory(4, "DX TextureGroupsTexture Primcount");

            if (i == 4)
                (*skirt_object_ref)->blend_mode = 5;
        }
        slot_base += 5;
        skirt_object_ref += 75;
    } while (slot_base < 0x2cb);

    void** vertex_buffers = shared_vertex_buffers;
    int count = 5;
    void* result;
    do {
        vertex_buffers[0] =
            allocate_tracked_memory((*(int*)((char*)vertex_buffers - 0x28) * 3) << 3,
                "GDX Cache Vertex Buffer");
        result = allocate_tracked_memory(*(int*)((char*)vertex_buffers - 0x14) << 1,
            "GDX Cache Index Buffer");
        vertex_buffers[5] = result;
        ++vertex_buffers;
        --count;
    } while (count != 0);

    return result;
}
