// build_track_render_caches @ 0x433220 (thiscall-shaped member, ret 0x10)

#include <string.h>

#include "audio_system.h"
#include "fringe_object.h"
#include "object_render_types.h"
#include "subgame_runtime.h"
#include "track_attachment_types.h"
#include "track_render_cache.h"

unsigned char __fastcall is_slide_cache_tile_family(TrackRowCell* cell);
unsigned char __fastcall is_floor_cache_tile_family(TrackRowCell* cell);
unsigned char __fastcall is_ramp_cache_tile_family(TrackRowCell* cell);
int report_errorf(const char* format, ...);
int debug_report_stub(const char* format, ...);

struct TrackRenderGrid {
    char unknown_00[0x54];
    int cell_count;
    char unknown_58[0x3bfa70];
    TrackRowCell cells[8];
};

int TrackRenderCacheManager::build_track_render_caches(Color4f skirt_color)
{
    int row_index;
    ColorBGRA8 white_color;
    int work_value;
    int cache_row;
    int cells_remaining;
    int row_mod;
    void* locked_vertices;
    void* locked_indices;
    int saved_cell_offset;
    int vertex_counts[5];
    int index_counts[5];

    white_color.noop_this_constructor();
    ((ColorBGRA8*)&skirt_color_bgra)->pack_color_rgba_u8(&skirt_color);
    *(int*)&white_color = -1;
    ((AudioBackend*)this)->noop_runtime_ai();

    row_index = 0;
    if (track_render_grid->cell_count > 0) {
        int cell_offset = 0;
        do {
            row_mod = row_index % 24;
            if (row_mod == 0) {
                cache_row = row_index / 24;

                int* slot_row_base = (int*)&slots[cache_row][0].cache_row_base;

                memset(index_counts, 0, sizeof(index_counts));

                build_cache_row_base = (float)cache_row * 24.0f;

                memset(vertex_counts, 0, sizeof(vertex_counts));
                work_value = 5;
                do {
                    *slot_row_base = *(int*)&build_cache_row_base;
                    slot_row_base += sizeof(TrackRenderCacheSlot) / sizeof(int);
                    --work_value;
                } while (work_value != 0);
            }

            cells_remaining = 8;
            do {
                int fringe_offset = cell_offset + 0x3bfb0c;
                work_value = 4;
                do {
                    FringeObject* fringe_object =
                        *(FringeObject**)((char*)track_render_grid + fringe_offset);
                    if (fringe_object != 0) {
                        append_track_cache_object(
                            row_index,
                            (Object*)fringe_object->object,
                            (Vector3*)((char*)&owner_subgame->runtime_cells[0][0].anchor_position
                                + cell_offset),
                            (ObjectRenderVertex*)shared_vertex_buffers[4],
                            &vertex_counts[4],
                            (unsigned short*)shared_index_buffers[4],
                            &index_counts[4],
                            max_vertex_counts[4],
                            max_index_counts[4],
                            skirt_color_bgra,
                            0);

                        ((Object*)slots[cache_row][4].bod.object)->group_texture_refs[0] =
                            ((Object*)(*(FringeObject**)((char*)track_render_grid +
                                fringe_offset))->object)->facequads[0].texture_ref;
                        *(FringeObject**)((char*)track_render_grid + fringe_offset) = 0;
                    }
                    fringe_offset += 4;
                    --work_value;
                } while (work_value != 0);

                int flags = *(int*)((char*)track_render_grid + cell_offset + 0x3bfb08);
                if ((flags & 0x20) != 0 && (flags & 0x4000) == 0x4000) {
                    append_track_cache_object(
                        row_index,
                        *(Object**)((char*)track_render_grid + cell_offset + 0x3bfaec),
                        (Vector3*)((char*)&owner_subgame->runtime_cells[0][0].anchor_position
                            + cell_offset),
                        (ObjectRenderVertex*)shared_vertex_buffers[2],
                        &vertex_counts[2],
                        (unsigned short*)shared_index_buffers[2],
                        &index_counts[2],
                        max_vertex_counts[2],
                        max_index_counts[2],
                        *(unsigned int*)&white_color,
                        1);

                    ((Object*)slots[cache_row][2].bod.object)->group_texture_refs[0] =
                        (*(Object**)((char*)track_render_grid + cell_offset +
                            0x3bfaec))->facequads[0].texture_ref;
                    *(int*)((char*)track_render_grid + cell_offset + 0x3bfb08) &= ~0x4000;
                } else if (is_slide_cache_tile_family(
                    (TrackRowCell*)((char*)track_render_grid + cell_offset + 0x3bfac8))
                    && ((*(int*)((char*)track_render_grid + cell_offset + 0x3bfb08)
                        & 0x4000) == 0x4000)) {
                    if ((*(int*)((char*)track_render_grid + cell_offset + 0x3bfb08)
                        & 0x40) == 0x40) {
                        append_track_cache_object(
                            row_index,
                            *(Object**)((char*)track_render_grid + cell_offset + 0x3bfaec),
                            (Vector3*)((char*)&owner_subgame->runtime_cells[0][0].anchor_position
                                + cell_offset),
                            (ObjectRenderVertex*)shared_vertex_buffers[1],
                            &vertex_counts[1],
                            (unsigned short*)shared_index_buffers[1],
                            &index_counts[1],
                            max_vertex_counts[1],
                            max_index_counts[1],
                            *(unsigned int*)&white_color,
                            1);

                        ((Object*)slots[cache_row][1].bod.object)->group_texture_refs[0] =
                            (*(Object**)((char*)track_render_grid + cell_offset +
                                0x3bfaec))->facequads[0].texture_ref;
                    } else {
                        append_track_cache_object(
                            row_index,
                            *(Object**)((char*)track_render_grid + cell_offset + 0x3bfaec),
                            (Vector3*)((char*)&owner_subgame->runtime_cells[0][0].anchor_position
                                + cell_offset),
                            (ObjectRenderVertex*)shared_vertex_buffers[0],
                            &vertex_counts[0],
                            (unsigned short*)shared_index_buffers[0],
                            &index_counts[0],
                            max_vertex_counts[0],
                            max_index_counts[0],
                            *(unsigned int*)&white_color,
                            1);

                        ((Object*)slots[cache_row][0].bod.object)->group_texture_refs[0] =
                            (*(Object**)((char*)track_render_grid + cell_offset +
                                0x3bfaec))->facequads[0].texture_ref;
                    }
                    *(int*)((char*)track_render_grid + cell_offset + 0x3bfb08) &= ~0x4000;
                } else if (is_floor_cache_tile_family(
                    (TrackRowCell*)((char*)track_render_grid + cell_offset + 0x3bfac8))
                    && ((*(int*)((char*)track_render_grid + cell_offset + 0x3bfb08)
                        & 0x4000) == 0x4000)) {
                    if ((*(int*)((char*)track_render_grid + cell_offset + 0x3bfb08)
                        & 0x40) == 0x40) {
                        append_track_cache_object(
                            row_index,
                            *(Object**)((char*)track_render_grid + cell_offset + 0x3bfaec),
                            (Vector3*)((char*)&owner_subgame->runtime_cells[0][0].anchor_position
                                + cell_offset),
                            (ObjectRenderVertex*)shared_vertex_buffers[0],
                            &vertex_counts[0],
                            (unsigned short*)shared_index_buffers[0],
                            &index_counts[0],
                            max_vertex_counts[0],
                            max_index_counts[0],
                            *(unsigned int*)&white_color,
                            1);

                        ((Object*)slots[cache_row][0].bod.object)->group_texture_refs[0] =
                            (*(Object**)((char*)track_render_grid + cell_offset +
                                0x3bfaec))->facequads[0].texture_ref;
                    } else {
                        append_track_cache_object(
                            row_index,
                            *(Object**)((char*)track_render_grid + cell_offset + 0x3bfaec),
                            (Vector3*)((char*)&owner_subgame->runtime_cells[0][0].anchor_position
                                + cell_offset),
                            (ObjectRenderVertex*)shared_vertex_buffers[1],
                            &vertex_counts[1],
                            (unsigned short*)shared_index_buffers[1],
                            &index_counts[1],
                            max_vertex_counts[1],
                            max_index_counts[1],
                            *(unsigned int*)&white_color,
                            1);

                        ((Object*)slots[cache_row][1].bod.object)->group_texture_refs[0] =
                            (*(Object**)((char*)track_render_grid + cell_offset +
                                0x3bfaec))->facequads[0].texture_ref;
                    }
                    *(int*)((char*)track_render_grid + cell_offset + 0x3bfb08) &= ~0x4000;
                } else if (is_ramp_cache_tile_family(
                    (TrackRowCell*)((char*)track_render_grid + cell_offset + 0x3bfac8))
                    && ((*(int*)((char*)track_render_grid + cell_offset + 0x3bfb08)
                        & 0x4000) == 0x4000)) {
                    append_track_cache_object(
                        row_index,
                        *(Object**)((char*)track_render_grid + cell_offset + 0x3bfaec),
                        (Vector3*)((char*)&owner_subgame->runtime_cells[0][0].anchor_position
                            + cell_offset),
                        (ObjectRenderVertex*)shared_vertex_buffers[3],
                        &vertex_counts[3],
                        (unsigned short*)shared_index_buffers[3],
                        &index_counts[3],
                        max_vertex_counts[3],
                        max_index_counts[3],
                        *(unsigned int*)&white_color,
                        0);

                    ((Object*)slots[cache_row][3].bod.object)->group_texture_refs[0] =
                        (*(Object**)((char*)track_render_grid + cell_offset +
                            0x3bfaec))->facequads[0].texture_ref;
                    *(int*)((char*)track_render_grid + cell_offset + 0x3bfb08) &= ~0x4000;
                }

                cell_offset += sizeof(TrackRowCell);
                --cells_remaining;
            } while (cells_remaining != 0);

            saved_cell_offset = cell_offset;
            if (row_mod == 23 || row_index == track_render_grid->cell_count - 1) {
                int* max_vertices = max_vertex_counts;
                Object** object_ref = (Object**)&slots[cache_row][0].bod.object;
                int family_index = 0;

                do {
                    (*object_ref)->render_buffers->vertex_buffer->vtbl->Lock(
                        (*object_ref)->render_buffers->vertex_buffer,
                        0,
                        (*max_vertices * 3) << 3,
                        &locked_vertices,
                        0);
                    (*object_ref)->index_buffer->buffer->vtbl->Lock(
                        (*object_ref)->index_buffer->buffer,
                        0,
                        max_vertices[5] << 1,
                        &locked_indices,
                        0);

                    memcpy(locked_vertices, (void*)max_vertices[10], (*max_vertices * 3) << 3);
                    memcpy(locked_indices, (void*)max_vertices[15], max_vertices[5] << 1);

                    (*object_ref)->render_buffers->vertex_buffer->vtbl->Unlock(
                        (*object_ref)->render_buffers->vertex_buffer);
                    (*object_ref)->index_buffer->buffer->vtbl->Unlock(
                        (*object_ref)->index_buffer->buffer);

                    (*object_ref)->grouped_vertex_count = vertex_counts[family_index];
                    (*object_ref)->group_primitive_counts[0] = index_counts[family_index] / 3;
                    (*object_ref)->vertex_count = vertex_counts[family_index];

                    object_ref = (Object**)((char*)object_ref + sizeof(TrackRenderCacheSlot));
                    ++max_vertices;
                    ++family_index;
                } while (family_index < 5);

                cell_offset = saved_cell_offset;
            }

            ++row_index;
        } while (row_index < track_render_grid->cell_count);
    }

    next_cache_row_z = 0.0f;
    next_cache_row_index = 0;

    int family_index = 0;
    int result;
    do {
        int max_vertices_seen = 0;
        int max_indices_seen = 0;
        int cache_rows = track_render_grid->cell_count / 24;

        if (cache_rows > 0) {
            Object** object_ref = (Object**)&slots[0][family_index].bod.object;
            do {
                Object* object = *object_ref;
                if (object->vertex_count > max_vertices_seen)
                    max_vertices_seen = object->vertex_count;

                int index_count = object->group_primitive_counts[0] * 4;
                if (index_count > max_indices_seen)
                    max_indices_seen = index_count;

                object_ref += 75;
                --cache_rows;
            } while (cache_rows != 0);
        }

        const char* cache_name;
        switch (family_index) {
        case 0:
            cache_name = "Floor";
            break;
        case 1:
            cache_name = "Slide";
            break;
        case 2:
            cache_name = "Warn";
            break;
        case 3:
            cache_name = "Ramp";
            break;
        case 4:
            cache_name = "Fringe";
            break;
        }

        result = debug_report_stub(
            "Max Cache Type=%s Vertices=%i   Indices=%i\n",
            cache_name,
            max_vertices_seen,
            max_indices_seen);
        ++family_index;
    } while (family_index < 5);

    return result;
}
