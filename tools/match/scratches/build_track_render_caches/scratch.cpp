// build_track_render_caches @ 0x433220 (thiscall-shaped member, ret 0x10)

#include <string.h>
#include <stddef.h>

#include "audio_system.h"
#include "fringe_object.h"
#include "object_render_types.h"
#include "subgame_runtime.h"
#include "track_attachment_types.h"
#include "segment_cache.h"

unsigned char __fastcall is_sub_loc_floor(TrackRowCell* cell);
unsigned char __fastcall is_sub_loc_slide(TrackRowCell* cell);
unsigned char __fastcall is_sub_loc_ramp(TrackRowCell* cell);
int report_errorf(const char* format, ...);
int debug_report_stub(const char* format, ...);

#define RUNTIME_CELL_BASE_OFFSET ((int)offsetof(SubgameRuntime, runtime_cells))
#define RUNTIME_CELL_OFFSET(field) \
    ((int)offsetof(SubgameRuntime, runtime_cells[0][0].field))

int SegmentCache::build_track_render_caches(tColour skirt_color)
{
    enum {
        MAX_INDEX_COUNT_LANE =
            ((int)offsetof(SegmentCache, max_index_counts)
                - (int)offsetof(SegmentCache, max_vertex_counts)) / sizeof(int),
        SHARED_VERTEX_BUFFER_LANE =
            ((int)offsetof(SegmentCache, shared_vertex_buffers)
                - (int)offsetof(SegmentCache, max_vertex_counts)) / sizeof(int),
        SHARED_INDEX_BUFFER_LANE =
            ((int)offsetof(SegmentCache, shared_index_buffers)
                - (int)offsetof(SegmentCache, max_vertex_counts)) / sizeof(int),
    };

    int row_index;
    tColourSmall white_color;
    int work_value;
    int cache_row;
    int cells_remaining;
    int row_mod;
    void* locked_vertices;
    void* locked_indices;
    int saved_cell_offset;
    int vertex_counts[TRACK_RENDER_CACHE_FAMILY_COUNT];
    int index_counts[TRACK_RENDER_CACHE_FAMILY_COUNT];

    white_color.noop_this_constructor();
    skirt_color_bgra.pack_color_rgba_u8(&skirt_color);
    *(int*)&white_color = -1;
    ((AudioBackend*)this)->noop_runtime_ai();

    row_index = 0;
    if (owner_subgame->runtime_row_count > 0) {
        int cell_offset = 0;
        do {
            row_mod = row_index % 24;
            if (row_mod == 0) {
                cache_row = row_index / 24;

                int* slot_row_base =
                    (int*)&slots[cache_row][TRACK_RENDER_CACHE_FLOOR].cache_row_base;

                memset(index_counts, 0, sizeof(index_counts));

                build_cache_row_base = (float)cache_row * 24.0f;

                memset(vertex_counts, 0, sizeof(vertex_counts));
                work_value = TRACK_RENDER_CACHE_FAMILY_COUNT;
                do {
                    *slot_row_base = *(int*)&build_cache_row_base;
                    slot_row_base += sizeof(TrackRenderCacheSlot) / sizeof(int);
                    --work_value;
                } while (work_value != 0);
            }

            cells_remaining =
                sizeof(owner_subgame->runtime_cells[0])
                / sizeof(owner_subgame->runtime_cells[0][0]);
            do {
                int fringe_offset = cell_offset + RUNTIME_CELL_OFFSET(fringe_front);
                work_value = 4;
                do {
                    Fringe* fringe_object =
                        *(Fringe**)((char*)owner_subgame + fringe_offset);
                    if (fringe_object != 0) {
                        append_track_cache_object(
                            row_index,
                            fringe_object->object,
                            (Vector3*)((char*)&owner_subgame->runtime_cells[0][0].position
                                + cell_offset),
                            (ObjectRenderVertex*)shared_vertex_buffers[
                                TRACK_RENDER_CACHE_FRINGE],
                            &vertex_counts[TRACK_RENDER_CACHE_FRINGE],
                            (unsigned short*)shared_index_buffers[
                                TRACK_RENDER_CACHE_FRINGE],
                            &index_counts[TRACK_RENDER_CACHE_FRINGE],
                            max_vertex_counts[TRACK_RENDER_CACHE_FRINGE],
                            max_index_counts[TRACK_RENDER_CACHE_FRINGE],
                            *(unsigned int*)&skirt_color_bgra,
                            0);

                        slots[cache_row][TRACK_RENDER_CACHE_FRINGE]
                            .bod.object->group_texture_refs[0] =
                            (*(Fringe**)((char*)owner_subgame + fringe_offset))
                                ->object->facequads[0].texture_ref;
                        *(Fringe**)((char*)owner_subgame + fringe_offset) = 0;
                    }
                    fringe_offset += 4;
                    --work_value;
                } while (work_value != 0);

                int flags = *(int*)((char*)owner_subgame + cell_offset + RUNTIME_CELL_OFFSET(lane_and_flags));
                if ((flags & 0x20) != 0 && (flags & 0x4000) == 0x4000) {
                    append_track_cache_object(
                        row_index,
                        *(Object**)((char*)owner_subgame + cell_offset + RUNTIME_CELL_OFFSET(object)),
                        (Vector3*)((char*)&owner_subgame->runtime_cells[0][0].position
                            + cell_offset),
                        (ObjectRenderVertex*)shared_vertex_buffers[
                            TRACK_RENDER_CACHE_WARNING],
                        &vertex_counts[TRACK_RENDER_CACHE_WARNING],
                        (unsigned short*)shared_index_buffers[
                            TRACK_RENDER_CACHE_WARNING],
                        &index_counts[TRACK_RENDER_CACHE_WARNING],
                        max_vertex_counts[TRACK_RENDER_CACHE_WARNING],
                        max_index_counts[TRACK_RENDER_CACHE_WARNING],
                        *(unsigned int*)&white_color,
                        1);

                    slots[cache_row][TRACK_RENDER_CACHE_WARNING]
                        .bod.object->group_texture_refs[0] =
                        (*(Object**)((char*)owner_subgame + cell_offset + RUNTIME_CELL_OFFSET(object)))
                            ->facequads[0].texture_ref;
                    *(int*)((char*)owner_subgame + cell_offset + RUNTIME_CELL_OFFSET(lane_and_flags))
                        &= ~0x4000;
                } else if (is_sub_loc_floor(
                    (TrackRowCell*)((char*)owner_subgame + cell_offset + RUNTIME_CELL_BASE_OFFSET))
                    && ((*(int*)((char*)owner_subgame + cell_offset + RUNTIME_CELL_OFFSET(lane_and_flags))
                        & 0x4000) == 0x4000)) {
                    if ((*(int*)((char*)owner_subgame + cell_offset + RUNTIME_CELL_OFFSET(lane_and_flags))
                        & 0x40) == 0x40) {
                        append_track_cache_object(
                            row_index,
                            *(Object**)((char*)owner_subgame + cell_offset + RUNTIME_CELL_OFFSET(object)),
                            (Vector3*)((char*)&owner_subgame->runtime_cells[0][0].position
                                + cell_offset),
                            (ObjectRenderVertex*)shared_vertex_buffers[
                                TRACK_RENDER_CACHE_SLIDE],
                            &vertex_counts[TRACK_RENDER_CACHE_SLIDE],
                            (unsigned short*)shared_index_buffers[
                                TRACK_RENDER_CACHE_SLIDE],
                            &index_counts[TRACK_RENDER_CACHE_SLIDE],
                            max_vertex_counts[TRACK_RENDER_CACHE_SLIDE],
                            max_index_counts[TRACK_RENDER_CACHE_SLIDE],
                            *(unsigned int*)&white_color,
                            1);

                        slots[cache_row][TRACK_RENDER_CACHE_SLIDE]
                            .bod.object->group_texture_refs[0] =
                            (*(Object**)((char*)owner_subgame + cell_offset + RUNTIME_CELL_OFFSET(object)))
                                ->facequads[0].texture_ref;
                    } else {
                        append_track_cache_object(
                            row_index,
                            *(Object**)((char*)owner_subgame + cell_offset + RUNTIME_CELL_OFFSET(object)),
                            (Vector3*)((char*)&owner_subgame->runtime_cells[0][0].position
                                + cell_offset),
                            (ObjectRenderVertex*)shared_vertex_buffers[
                                TRACK_RENDER_CACHE_FLOOR],
                            &vertex_counts[TRACK_RENDER_CACHE_FLOOR],
                            (unsigned short*)shared_index_buffers[
                                TRACK_RENDER_CACHE_FLOOR],
                            &index_counts[TRACK_RENDER_CACHE_FLOOR],
                            max_vertex_counts[TRACK_RENDER_CACHE_FLOOR],
                            max_index_counts[TRACK_RENDER_CACHE_FLOOR],
                            *(unsigned int*)&white_color,
                            1);

                        slots[cache_row][TRACK_RENDER_CACHE_FLOOR]
                            .bod.object->group_texture_refs[0] =
                            (*(Object**)((char*)owner_subgame + cell_offset + RUNTIME_CELL_OFFSET(object)))
                                ->facequads[0].texture_ref;
                    }
                    *(int*)((char*)owner_subgame + cell_offset + RUNTIME_CELL_OFFSET(lane_and_flags))
                        &= ~0x4000;
                } else if (is_sub_loc_slide(
                    (TrackRowCell*)((char*)owner_subgame + cell_offset + RUNTIME_CELL_BASE_OFFSET))
                    && ((*(int*)((char*)owner_subgame + cell_offset + RUNTIME_CELL_OFFSET(lane_and_flags))
                        & 0x4000) == 0x4000)) {
                    if ((*(int*)((char*)owner_subgame + cell_offset + RUNTIME_CELL_OFFSET(lane_and_flags))
                        & 0x40) == 0x40) {
                        append_track_cache_object(
                            row_index,
                            *(Object**)((char*)owner_subgame + cell_offset + RUNTIME_CELL_OFFSET(object)),
                            (Vector3*)((char*)&owner_subgame->runtime_cells[0][0].position
                                + cell_offset),
                            (ObjectRenderVertex*)shared_vertex_buffers[
                                TRACK_RENDER_CACHE_FLOOR],
                            &vertex_counts[TRACK_RENDER_CACHE_FLOOR],
                            (unsigned short*)shared_index_buffers[
                                TRACK_RENDER_CACHE_FLOOR],
                            &index_counts[TRACK_RENDER_CACHE_FLOOR],
                            max_vertex_counts[TRACK_RENDER_CACHE_FLOOR],
                            max_index_counts[TRACK_RENDER_CACHE_FLOOR],
                            *(unsigned int*)&white_color,
                            1);

                        slots[cache_row][TRACK_RENDER_CACHE_FLOOR]
                            .bod.object->group_texture_refs[0] =
                            (*(Object**)((char*)owner_subgame + cell_offset + RUNTIME_CELL_OFFSET(object)))
                                ->facequads[0].texture_ref;
                    } else {
                        append_track_cache_object(
                            row_index,
                            *(Object**)((char*)owner_subgame + cell_offset + RUNTIME_CELL_OFFSET(object)),
                            (Vector3*)((char*)&owner_subgame->runtime_cells[0][0].position
                                + cell_offset),
                            (ObjectRenderVertex*)shared_vertex_buffers[
                                TRACK_RENDER_CACHE_SLIDE],
                            &vertex_counts[TRACK_RENDER_CACHE_SLIDE],
                            (unsigned short*)shared_index_buffers[
                                TRACK_RENDER_CACHE_SLIDE],
                            &index_counts[TRACK_RENDER_CACHE_SLIDE],
                            max_vertex_counts[TRACK_RENDER_CACHE_SLIDE],
                            max_index_counts[TRACK_RENDER_CACHE_SLIDE],
                            *(unsigned int*)&white_color,
                            1);

                        slots[cache_row][TRACK_RENDER_CACHE_SLIDE]
                            .bod.object->group_texture_refs[0] =
                            (*(Object**)((char*)owner_subgame + cell_offset + RUNTIME_CELL_OFFSET(object)))
                                ->facequads[0].texture_ref;
                    }
                    *(int*)((char*)owner_subgame + cell_offset + RUNTIME_CELL_OFFSET(lane_and_flags))
                        &= ~0x4000;
                } else if (is_sub_loc_ramp(
                    (TrackRowCell*)((char*)owner_subgame + cell_offset + RUNTIME_CELL_BASE_OFFSET))
                    && ((*(int*)((char*)owner_subgame + cell_offset + RUNTIME_CELL_OFFSET(lane_and_flags))
                        & 0x4000) == 0x4000)) {
                    append_track_cache_object(
                        row_index,
                        *(Object**)((char*)owner_subgame + cell_offset + RUNTIME_CELL_OFFSET(object)),
                        (Vector3*)((char*)&owner_subgame->runtime_cells[0][0].position
                            + cell_offset),
                        (ObjectRenderVertex*)shared_vertex_buffers[
                            TRACK_RENDER_CACHE_RAMP],
                        &vertex_counts[TRACK_RENDER_CACHE_RAMP],
                        (unsigned short*)shared_index_buffers[
                            TRACK_RENDER_CACHE_RAMP],
                        &index_counts[TRACK_RENDER_CACHE_RAMP],
                        max_vertex_counts[TRACK_RENDER_CACHE_RAMP],
                        max_index_counts[TRACK_RENDER_CACHE_RAMP],
                        *(unsigned int*)&white_color,
                        0);

                    slots[cache_row][TRACK_RENDER_CACHE_RAMP]
                        .bod.object->group_texture_refs[0] =
                        (*(Object**)((char*)owner_subgame + cell_offset + RUNTIME_CELL_OFFSET(object)))
                            ->facequads[0].texture_ref;
                    *(int*)((char*)owner_subgame + cell_offset + RUNTIME_CELL_OFFSET(lane_and_flags))
                        &= ~0x4000;
                }

                cell_offset += sizeof(TrackRowCell);
                --cells_remaining;
            } while (cells_remaining != 0);

            saved_cell_offset = cell_offset;
            if (row_mod == 23 || row_index == owner_subgame->runtime_row_count - 1) {
                int* max_vertices = max_vertex_counts;
                Object** object_ref =
                    &slots[cache_row][TRACK_RENDER_CACHE_FLOOR].bod.object;
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
                        max_vertices[MAX_INDEX_COUNT_LANE] << 1,
                        &locked_indices,
                        0);

                    memcpy(locked_vertices, (void*)max_vertices[SHARED_VERTEX_BUFFER_LANE],
                        (*max_vertices * 3) << 3);
                    memcpy(locked_indices, (void*)max_vertices[SHARED_INDEX_BUFFER_LANE],
                        max_vertices[MAX_INDEX_COUNT_LANE] << 1);

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
                } while (family_index < TRACK_RENDER_CACHE_FAMILY_COUNT);

                cell_offset = saved_cell_offset;
            }

            ++row_index;
        } while (row_index < owner_subgame->runtime_row_count);
    }

    next_cache_row_z = 0.0f;
    next_cache_row_index = 0;

    int family_index = 0;
    int result;
    do {
        int max_vertices_seen = 0;
        int max_indices_seen = 0;
        int cache_rows = owner_subgame->runtime_row_count / 24;

        if (cache_rows > 0) {
            Object** object_ref = &slots[0][family_index].bod.object;
            do {
                Object* object = *object_ref;
                if (object->vertex_count > max_vertices_seen)
                    max_vertices_seen = object->vertex_count;

                int index_count = object->group_primitive_counts[0] * 4;
                if (index_count > max_indices_seen)
                    max_indices_seen = index_count;

                object_ref += sizeof(slots[0]) / sizeof(*object_ref);
                --cache_rows;
            } while (cache_rows != 0);
        }

        const char* cache_name;
        switch (family_index) {
        case TRACK_RENDER_CACHE_FLOOR:
            cache_name = "Floor";
            break;
        case TRACK_RENDER_CACHE_SLIDE:
            cache_name = "Slide";
            break;
        case TRACK_RENDER_CACHE_WARNING:
            cache_name = "Warn";
            break;
        case TRACK_RENDER_CACHE_RAMP:
            cache_name = "Ramp";
            break;
        case TRACK_RENDER_CACHE_FRINGE:
            cache_name = "Fringe";
            break;
        }

        result = debug_report_stub(
            "Max Cache Type=%s Vertices=%i   Indices=%i\n",
            cache_name,
            max_vertices_seen,
            max_indices_seen);
        ++family_index;
    } while (family_index < TRACK_RENDER_CACHE_FAMILY_COUNT);

    return result;
}
