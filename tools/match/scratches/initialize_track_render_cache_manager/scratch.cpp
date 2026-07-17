// initialize_track_render_cache_manager @ 0x433060 (thiscall, ret)

#include <stddef.h>

#include "direct3d_renderer.h"
#include "game_root.h"
#include "object_render_types.h"
#include "segment_cache.h"

void* allocate_tracked_memory(int size, char* name);


struct TrackRenderCacheSlotCursor {
    char manager_prefix[offsetof(SegmentCache, slots)];
    TrackRenderCacheSlot slot; // SegmentCache::slots[0][TRACK_RENDER_CACHE_FLOOR]
};

void SegmentCache::initialize_track_render_cache_manager()
{
    max_vertex_counts[TRACK_RENDER_CACHE_FLOOR] = 560;
    max_index_counts[TRACK_RENDER_CACHE_FLOOR] = 1280;
    max_vertex_counts[TRACK_RENDER_CACHE_SLIDE] = 560;
    max_index_counts[TRACK_RENDER_CACHE_SLIDE] = 1280;
    max_vertex_counts[TRACK_RENDER_CACHE_WARNING] = 160;
    max_index_counts[TRACK_RENDER_CACHE_WARNING] = 240;
    max_vertex_counts[TRACK_RENDER_CACHE_RAMP] = 80;
    max_index_counts[TRACK_RENDER_CACHE_RAMP] = 160;
    max_vertex_counts[TRACK_RENDER_CACHE_FRINGE] = 800;
    max_index_counts[TRACK_RENDER_CACHE_FRINGE] = 1280;
    owner_subgame = &g_game->subgame;

    int slot_base = 0;
    Object** skirt_object_ref =
        &slots[0][TRACK_RENDER_CACHE_FRINGE].object;
    int i;
    do {
        for (i = 0;
             i < (int)(sizeof(slots[0]) / sizeof(slots[0][0]));
             ++i) {
            TrackRenderCacheSlotCursor* slot =
                (TrackRenderCacheSlotCursor*)((char*)this
                    + (slot_base + i) * sizeof(TrackRenderCacheSlot));
            slot->slot.set_bod_object(g_object_list.add_object_to_list());

            slot->slot.object->flags = OBJECT_FLAG_RENDER_BUFFERS_READY;
            slot->slot.object->vertex_count = 0;
            slot->slot.object->vertices = 0;
            slot->slot.object->facequad_count = 0;
            slot->slot.object->facequads = 0;
            slot->slot.object->texture_group_count = 1;
            slot->slot.object->render_buffers = g_direct3d_renderer.vertex_buffer_factory
                .create_vertex_buffer(max_vertex_counts[i], 0x142);
            slot->slot.object->index_buffer = g_direct3d_renderer
                .index_buffer_factory.create_index_buffer(max_index_counts[i]);
            slot->slot.object->group_index_starts =
                (int*)allocate_tracked_memory(4, "DX TextureGroups");
            slot->slot.object->group_index_starts[0] = 0;
            slot->slot.object->group_texture_refs =
                (TextureRef**)allocate_tracked_memory(4, "DX TextureGroupsTexture Ref");
            slot->slot.object->group_primitive_counts =
                (int*)allocate_tracked_memory(4, "DX TextureGroupsTexture Primcount");

            if (i == TRACK_RENDER_CACHE_FRINGE)
                (*skirt_object_ref)->blend_mode = 5;
        }
        slot_base += sizeof(slots[0]) / sizeof(slots[0][0]);
        skirt_object_ref += sizeof(slots[0]) / sizeof(*skirt_object_ref);
    } while (slot_base < (int)(sizeof(slots) / sizeof(slots[0][0])));

    void** vertex_buffers = (void**)shared_vertex_buffers;
    int count = sizeof(shared_vertex_buffers) / sizeof(shared_vertex_buffers[0]);
    void* result;
    do {
        void* vertex_buffer =
            allocate_tracked_memory((*(int*)((char*)vertex_buffers
                + (int)offsetof(SegmentCache, max_vertex_counts)
                - (int)offsetof(SegmentCache, shared_vertex_buffers)) * 3) << 3,
                "GDX Cache Vertex Buffer");
        vertex_buffers[0] = vertex_buffer;
        int* index_buffer_count = (int*)((char*)vertex_buffers
            + (int)offsetof(SegmentCache, max_index_counts)
            - (int)offsetof(SegmentCache, shared_vertex_buffers));
        result = allocate_tracked_memory((*index_buffer_count) << 1,
            "GDX Cache Index Buffer");
        vertex_buffers[sizeof(shared_vertex_buffers) / sizeof(shared_vertex_buffers[0])] =
            result;
        ++vertex_buffers;
        --count;
    } while (count != 0);

}
