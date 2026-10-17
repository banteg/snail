// populate_runtime_track_cells_from_segments @ 0x435eb0 (thiscall, ret)
// Structure-first scratch for the runtime grid builder setup and clear pass.

#include <stddef.h>

extern "C" void* memset(void* destination, int value, unsigned int count);
#pragma intrinsic(memset)

#include "rdebug.h"
#include "sprite.h"
#include "fringe_object.h"
#include "game_root.h"
#include "rmath_random.h"
#include "runtime_config.h"
#include "subgame_runtime.h"
#include "game_time.h"
#include "root_bod_catalog.h"
#include "track_attachment_types.h"
#include "track.h"

#define ROOT_BOD_OBJECT(slot) (g_game->root_bod_catalog.slot.object)

void set_object_color(Object* object, tColour color);

void cRSubGame::BuildLevel()
{
    int runtime_build_seed;

    if (selected_level_record_active != 0) {
        SubSolution* record = selected_level_record;
        runtime_build_seed = record->runtime_build_seed;
    } else {
        int mode = level_mode;
        if (mode == 4 || mode == 7) {
            runtime_build_seed = 0;
        } else {
            runtime_build_seed = (int)RAND(32768.0f, "Seed");
        }
    }

    int mode = level_mode;
    switch (mode) {
    case 0:
        current_high_score_record.ReSet(
            runtime_build_seed,
            level_mode_arg,
            level_arg_tail,
            runtime_flags,
            0,
            level_mode_arg);
        break;
    case 1:
        current_high_score_record.ReSet(
            runtime_build_seed,
            level_mode_arg,
            level_arg_tail,
            runtime_flags,
            1,
            level_mode_arg);
        break;
    case 4:
        current_high_score_record.ReSet(
            runtime_build_seed,
            level_mode_arg,
            level_arg_tail,
            runtime_flags,
            2,
            level_mode_arg);
        break;
    }

    replay_update_cursor = 0;
    if (subgame_rebuild_selector == 3) {
        subgame_rebuild_selector = 1;
        player.total_score = 0;
        player.ScoreStatsInit();
        player.visible_life_stock = 3;
    }

    player.stopwatch.Zero();
    player.score_tail = 0;
    player.shooting_tier = 0;
    RandSeed(runtime_build_seed);
    g_game->track.Change(level_definition.track_texture_set);

    int segment_cursor;
    mode = level_mode;
    if (mode == 0 || mode == 7 || mode == 4 || mode == 1) {
        first_block_row_count = level_definition.first_segment.row_count;
        int authored_length = level_definition.random_length;
        runtime_row_count = authored_length;
        if (mode == 1) {
            runtime_row_count =
                (int)((challenge_difficulty_scalar * 0.64999998f + 0.34999999f)
                    * (float)authored_length);
        }
        if (level_definition.random_enabled == 0) {
            SubSegment* first_segment =
                &level_definition.first_segment;
            SubSegment* last_segment =
                &level_definition.last_segment;
            runtime_row_count = last_segment->row_count
                + first_segment->row_count;
            int* segment_count = &level_definition.segment_count;
            int segment_slot_index = 0;
            if (*segment_count > 0) {
                int* segment_row_count_cursor =
                    &level_definition.segment_slots[0].row_count;
                do {
                    runtime_row_count += *segment_row_count_cursor;
                    ++segment_slot_index;
                    segment_row_count_cursor = (int*)(
                        (char*)segment_row_count_cursor + sizeof(SubSegment));
                } while (segment_slot_index < *segment_count);
            }
            segment_cursor = 0;
        }
        completion_row_start = runtime_row_count - level_definition.last_segment.row_count;
        if (runtime_row_count >= 3100) {
            report_errorf(
                "Track (%s) too long, Maximum Length %i",
                level_definition.level_display_name,
                3100);
        }
    } else if (mode == 3) {
        SubSegment* first_segment =
            &level_definition.first_segment;
        SubSegment* last_segment =
            &level_definition.last_segment;
        first_block_row_count = first_segment->row_count;
        runtime_row_count = last_segment->row_count
            + first_segment->row_count;
        SubSegment* repeated_segment =
            &level_definition.segment_slots[0];
        int rows_remaining = 16;
        do {
            int next_runtime_row_count =
                runtime_row_count + repeated_segment->row_count;
            runtime_row_count = next_runtime_row_count;
        } while (--rows_remaining != 0);
        segment_cursor = 0;
        completion_row_start = runtime_row_count - last_segment->row_count;
        completion_row_start = runtime_row_count - last_segment->row_count;
    }

    track_mirror_enabled = false;
    track_mirror_repeat_count = 0;
    int trampoline_counter = 0;
    char first_or_last_row = 0;
    int row_event_owner = 0;
    player.follow_state.flag_3c = 0;

    enum {
        RUNTIME_LANE_COUNT =
            sizeof(runtime_cells[0]) / sizeof(runtime_cells[0][0]),
        CELL_FRINGE_COUNT =
            sizeof(((cRSubLoc*)0)->fringes) / sizeof(((cRSubLoc*)0)->fringes[0]),
        PATHS_BASE = offsetof(cRSubGame, paths),
        PATH_36_PRIMARY_SAMPLES =
            PATHS_BASE + 36 * sizeof(paths[0])
            + offsetof(Path, primary_samples),
        SEGMENT_AUTHORED_ROWS_BASE = offsetof(SubSegment, rows),
        AUTHORED_ROW_LOCAL_X =
            offsetof(AuthoredSegmentRow, local_position) + offsetof(Vector3, x),
        AUTHORED_ROW_OBJECT_ID = offsetof(AuthoredSegmentRow, object_id),
        AUTHORED_ROW_OBJECT_POSITION_X =
            offsetof(AuthoredSegmentRow, object_position) + offsetof(Vector3, x),
        AUTHORED_ROW_OBJECT_VELOCITY_X =
            offsetof(AuthoredSegmentRow, object_velocity) + offsetof(Vector3, x),
        AUTHORED_ROW_PATH_TEMPLATE_INDEX =
            offsetof(AuthoredSegmentRow, path_template_index),
        AUTHORED_ROW_RING_SPEED = offsetof(AuthoredSegmentRow, ring_speed),
        ROW_ATTACHMENT_POSITION_X =
            offsetof(SubRow, attachment_body) + offsetof(BodBase, position)
            + offsetof(Vector3, x),
        ROW_ATTACHMENT_POSITION_Y =
            offsetof(SubRow, attachment_body) + offsetof(BodBase, position)
            + offsetof(Vector3, y),
        ROW_ATTACHMENT_POSITION_Z =
            offsetof(SubRow, attachment_body) + offsetof(BodBase, position)
            + offsetof(Vector3, z),
        ROW_CURSOR_BASE =
            (int)(offsetof(SubRow, parcel_spawn_position) + offsetof(Vector3, y)),
        ROW_CURSOR_TO_FLAGS =
            ((int)offsetof(SubRow, flags) - ROW_CURSOR_BASE) / (int)sizeof(int),
        ROW_CURSOR_TO_PROJECTION_X =
            ((int)offsetof(SubRow, parcel_spawn_position)
             + (int)offsetof(Vector3, x) - ROW_CURSOR_BASE) / (int)sizeof(int),
        ROW_CURSOR_TO_PROJECTION_Y = 0,
        ROW_CURSOR_TO_PROJECTION_Z =
            ((int)offsetof(SubRow, parcel_spawn_position)
             + (int)offsetof(Vector3, z) - ROW_CURSOR_BASE) / (int)sizeof(int),
        ROW_CURSOR_TO_PARCEL_SET_ID =
            ((int)offsetof(SubRow, parcel_set_id) - ROW_CURSOR_BASE) / (int)sizeof(int),
        ROW_CURSOR_TO_ATTACHMENT_TEMPLATE_INDEX =
            ((int)offsetof(SubRow, attachment_template_index) - ROW_CURSOR_BASE)
            / (int)sizeof(int),
        ROW_CURSOR_TO_PRIMARY_ATTACHMENT_CELL =
            ((int)offsetof(SubRow, primary_attachment_cell) - ROW_CURSOR_BASE)
            / (int)sizeof(int),
        ROW_CURSOR_TO_INSTALLED_HEADING =
            ((int)offsetof(SubRow, installed_heading_delta) - ROW_CURSOR_BASE)
            / (int)sizeof(int),
        ROW_CURSOR_TO_RING_SPEED =
            ((int)offsetof(SubRow, ring_speed) - ROW_CURSOR_BASE) / (int)sizeof(int),
        ROW_CURSOR_TO_SOURCE_SEGMENT =
            ((int)offsetof(SubRow, source_segment) - ROW_CURSOR_BASE) / (int)sizeof(int),
        ROW_CURSOR_TO_ROW_EVENT_ID =
            ((int)offsetof(SubRow, row_event_id) - ROW_CURSOR_BASE) / (int)sizeof(int),
        CELL_FRINGE_TO_LANE_FLAGS =
            (int)offsetof(cRSubLoc, lane_and_flags)
            - (int)offsetof(cRSubLoc, fringe_front),
        CELL_LANE_FLAGS_TO_TILE_FLAGS =
            (int)offsetof(cRSubLoc, open_edge_mask)
            - (int)offsetof(cRSubLoc, lane_and_flags),
        CELL_LANE_FLAGS_TO_LIST_FLAGS =
            (int)offsetof(ContactTargetObject, list_flags)
            - (int)offsetof(cRSubLoc, lane_and_flags),
        CELL_LANE_FLAGS_TO_COLOR =
            (int)offsetof(BodBase, color)
            - (int)offsetof(cRSubLoc, lane_and_flags),
        ATTACHMENT_SAMPLE_POSITION_Y =
            offsetof(AttachmentSample, transform)
            + offsetof(TransformMatrix, position) + offsetof(Vector3, y),
    };
    char* cell_payload_cursor = (char*)&runtime_cells[0][0].fringes[0];
    int* row_cursor = (int*)&runtime_rows[0].parcel_spawn_position.y;
    for (int row = 0;
         row < (int)(sizeof(runtime_rows) / sizeof(runtime_rows[0]));
         ++row) {
        row_cursor[ROW_CURSOR_TO_FLAGS] = 0;
        row_cursor[ROW_CURSOR_TO_INSTALLED_HEADING] = 0;
        row_cursor[ROW_CURSOR_TO_ATTACHMENT_TEMPLATE_INDEX] = 0;
        row_cursor[ROW_CURSOR_TO_RING_SPEED] = 0;
        row_cursor[ROW_CURSOR_TO_PRIMARY_ATTACHMENT_CELL] = 0;
        row_cursor[ROW_CURSOR_TO_PROJECTION_Z] = 0;
        row_cursor[ROW_CURSOR_TO_PROJECTION_Y] = 0;
        row_cursor[ROW_CURSOR_TO_PROJECTION_X] = 0;
        row_cursor[ROW_CURSOR_TO_PARCEL_SET_ID] = 0;
        row_cursor[ROW_CURSOR_TO_SOURCE_SEGMENT] = 0;
        row_cursor[ROW_CURSOR_TO_ROW_EVENT_ID] = 0;

        char* cell_flags = cell_payload_cursor + CELL_FRINGE_TO_LANE_FLAGS;
        for (int lane = 0;
             lane < (int)(sizeof(runtime_cells[0]) / sizeof(runtime_cells[0][0]));
             ++lane) {
            int* lane_word = (int*)cell_flags;
            char* tile_flags =
                cell_flags + CELL_LANE_FLAGS_TO_TILE_FLAGS;
            int lane_and_flags = *lane_word;
            lane_and_flags &= 0xffff5fff;
            *lane_word = lane_and_flags;
            *tile_flags = 0;
            *(short*)cell_flags = 0;
            *lane_word &= 0xffffafa7;
            *(short*)cell_flags = 0;
            int* list_flags = (int*)(
                cell_flags + CELL_LANE_FLAGS_TO_LIST_FLAGS);
            *list_flags &= 0xffffff7f;
            ((tColour*)(cell_flags + CELL_LANE_FLAGS_TO_COLOR))->White();
            cell_flags += sizeof(cRSubLoc);
        }

        char* cell_payload = cell_payload_cursor;
        for (int lane_payload = 0;
             lane_payload
                < (int)(sizeof(runtime_cells[0]) / sizeof(runtime_cells[0][0]));
             ++lane_payload) {
            memset(cell_payload, 0, 4 * sizeof(int));
            cell_payload += sizeof(cRSubLoc);
        }
        cell_payload_cursor = cell_payload;
        row_cursor += sizeof(SubRow) / sizeof(int);
    }

    if (level_definition.random_enabled == 1) {
        for (int i = 0; i < level_definition.segment_count; ++i)
            level_definition.segment_slots[i].visited = 0;
    }

    int build_row = 0;
    if (runtime_row_count <= 0)
        return;

    char* base = (char*)this;
    SubSegment* active_segment;
    do {
        if (build_row == 0) {
            active_segment = &level_definition.first_segment;
            first_or_last_row = 1;
            active_segment->row_base = build_row;
        } else if (build_row == completion_row_start && level_definition.random_enabled == 0) {
            active_segment = &level_definition.last_segment;
            first_or_last_row = 1;
            active_segment->row_base = build_row;
        } else {
            base_subgame_rate = 1.0f;
            if (level_definition.random_enabled == 1) {
                float picked_value;
                if (level_mode == 1) {
                    picked_value = RAND(
                        (challenge_difficulty_scalar * 0.89999998f + 0.100000001f)
                            * (float)level_definition.segment_count,
                        "Segdif");
                } else {
                    picked_value = RAND(
                        (float)level_definition.segment_count,
                        "Segtra");
                }
                int picked = (int)picked_value;
                picked = (int)((float)picked * base_subgame_rate);
                active_segment =
                    &level_definition.segment_slots[picked];
                active_segment->visited = 1;
            } else {
                int picked = segment_cursor;
                ++segment_cursor;
                active_segment =
                    &level_definition.segment_slots[picked];
            }
        }
        SwitchMirror();
        active_segment->row_base = build_row;
        if (active_segment->row_count < 0)
            report_errorf("Negative Segment Length");

        int segment_row = 0;
        while (build_row < runtime_row_count) {
            if (segment_row >= active_segment->row_count)
                break;
            if (level_mode != 2 && build_row >= completion_row_start) {
                if (level_mode == 0
                    || level_mode == 4
                    || level_mode == 1
                    || level_mode == 7
                    || level_mode == 3)
                    active_segment = &level_definition.last_segment;
                else
                    active_segment =
                        &level_definition_scratch.segment_slots[1];
                if (build_row == completion_row_start)
                    segment_row = 0;
            }

            if (level_mode != 2) {
                int segment_end =
                    active_segment->row_count - segment_row + build_row;
                if (segment_end > completion_row_start
                    && active_segment
                        != &level_definition_scratch.segment_slots[1]
                    && active_segment
                        != &level_definition_scratch.segment_slots[3]
                    && active_segment
                        != &level_definition_scratch.segment_slots[4]
                    && (level_mode == 0
                        || level_mode == 4
                        || level_mode == 1
                        || level_mode == 7
                        || level_mode == 3)
                    && active_segment != &level_definition.last_segment) {
                    int extra_rows = active_segment->row_count
                        - completion_row_start - segment_row + build_row;
                    completion_row_start += extra_rows;
                    runtime_row_count += extra_rows;
                }
            }

            if (track_mirror_enabled)
                runtime_rows[build_row].flags |= SUBROW_FLAG_MIRRORED;

            char* authored_row_owner =
                (char*)active_segment + sizeof(AuthoredSegmentRow) * segment_row;
            if ((active_segment->rows[segment_row].flags
                    & AUTHORED_SEGMENT_ROW_FLAG_NO_FALL)
                != 0)
                runtime_rows[build_row].flags |= SUBROW_FLAG_NO_FALL;
            if ((active_segment->rows[segment_row].flags
                    & AUTHORED_SEGMENT_ROW_FLAG_JETPACK_OFF)
                != 0)
                runtime_rows[build_row].flags |= SUBROW_FLAG_JETPACK_OFF;

            runtime_rows[build_row].source_segment =
                active_segment;
            runtime_rows[build_row].row_event_id = row_event_owner;

            if ((active_segment->rows[segment_row].flags
                    & AUTHORED_SEGMENT_ROW_FLAG_3D_MODEL)
                != 0) {
                runtime_rows[build_row].flags |= SUBROW_FLAG_ROW_MODEL_PRESENT;
                int object_id = *(int*)(
                    authored_row_owner + SEGMENT_AUTHORED_ROWS_BASE
                    + AUTHORED_ROW_OBJECT_ID);
                runtime_rows[build_row].row_model.SetObject(
                    g_game->directx_loader.cached_x_mesh_slots[object_id].object);
                runtime_rows[build_row].row_model.transform.Identity();
                runtime_rows[build_row].row_model.transform.position =
                    *(Vector3*)(
                        authored_row_owner + SEGMENT_AUTHORED_ROWS_BASE
                        + AUTHORED_ROW_OBJECT_POSITION_X);
                runtime_rows[build_row].row_model.transform.position.z +=
                    (float)build_row;

                if ((active_segment->rows[segment_row].flags
                        & AUTHORED_SEGMENT_ROW_FLAG_PATH_OR_MODEL_VELOCITY)
                    != 0) {
                    runtime_rows[build_row].flags |=
                        SUBROW_FLAG_PATH_OR_MODEL_VELOCITY;
                    runtime_rows[build_row].row_model.velocity =
                        *(Vector3*)(
                            authored_row_owner + SEGMENT_AUTHORED_ROWS_BASE
                            + AUTHORED_ROW_OBJECT_VELOCITY_X);
                } else {
                    runtime_rows[build_row].row_model.velocity.x = 0;
                    runtime_rows[build_row].row_model.velocity.y = 0;
                    runtime_rows[build_row].row_model.velocity.z = 0;
                }
            }

            if ((active_segment->rows[segment_row].flags
                    & AUTHORED_SEGMENT_ROW_FLAG_PARCEL)
                != 0) {
                runtime_rows[build_row].flags |=
                    SUBROW_FLAG_PARCEL_CANDIDATE | SUBROW_FLAG_PARCEL_Z_IS_LOCAL;
                runtime_rows[build_row].parcel_set_id =
                    active_segment->rows[segment_row].parcel_set_id;
                runtime_rows[build_row].parcel_spawn_position =
                    *(Vector3*)(
                        authored_row_owner + SEGMENT_AUTHORED_ROWS_BASE
                        + AUTHORED_ROW_LOCAL_X);
            }
            if ((active_segment->rows[segment_row].flags
                    & AUTHORED_SEGMENT_ROW_FLAG_PATH_OR_MODEL_VELOCITY)
                != 0) {
                runtime_rows[build_row].flags |=
                    SUBROW_FLAG_PATH_OR_MODEL_VELOCITY;
                runtime_rows[build_row].attachment_template_index =
                    *(int*)(
                        authored_row_owner + SEGMENT_AUTHORED_ROWS_BASE
                        + AUTHORED_ROW_PATH_TEMPLATE_INDEX);
            }
            if ((active_segment->rows[segment_row].flags
                    & AUTHORED_SEGMENT_ROW_FLAG_SUPPRESS_TRACK_RENDER)
                != 0)
                runtime_rows[build_row].flags |=
                    SUBROW_FLAG_SUPPRESS_TRACK_RENDER;
            if ((active_segment->rows[segment_row].flags
                    & AUTHORED_SEGMENT_ROW_FLAG_RING_NONE)
                != 0)
                runtime_rows[build_row].flags |= SUBROW_FLAG_RING_NONE;
            if ((active_segment->rows[segment_row].flags
                    & AUTHORED_SEGMENT_ROW_FLAG_RING_NORMAL)
                != 0)
                runtime_rows[build_row].flags |= SUBROW_FLAG_RING_NORMAL;
            if ((active_segment->rows[segment_row].flags
                    & AUTHORED_SEGMENT_ROW_FLAG_RING_POWER_UP)
                != 0)
                runtime_rows[build_row].flags |= SUBROW_FLAG_RING_POWER_UP;
            if ((active_segment->rows[segment_row].flags
                    & AUTHORED_SEGMENT_ROW_FLAG_RING_EXPLODE)
                != 0)
                runtime_rows[build_row].flags |= SUBROW_FLAG_RING_EXPLODE;
            if ((active_segment->rows[segment_row].flags
                    & AUTHORED_SEGMENT_ROW_FLAG_RING_SLOW)
                != 0)
                runtime_rows[build_row].flags |= SUBROW_FLAG_RING_SLOW;
            int authored_ring_speed_bits =
                *(int*)(
                    authored_row_owner + SEGMENT_AUTHORED_ROWS_BASE
                    + AUTHORED_ROW_RING_SPEED);
            char attachment_entry_installed = 0;
            int lane = 0;
            *(int*)&runtime_rows[build_row].ring_speed = authored_ring_speed_bits;
            for (; lane < RUNTIME_LANE_COUNT; ++lane) {
                int authored_lane;
                if (track_mirror_enabled)
                    authored_lane = RUNTIME_LANE_COUNT - 1 - lane;
                else
                    authored_lane = lane;

                unsigned int* cell_word = &runtime_cells[build_row][lane].lane_and_flags;
                *cell_word &= 0xffffffe0;
                *cell_word ^= lane & SUBLOC_LANE_INDEX_MASK;

                Fringe** subobject_slot =
                    runtime_cells[build_row][lane].fringes;
                subobject_slot[0] = 0;
                subobject_slot[1] = 0;
                subobject_slot[2] = 0;
                subobject_slot[3] = 0;

                char edge_row = build_row < first_block_row_count || build_row >= completion_row_start;

                // initialize_sub_loc proves this is the shared cRBod base prefix.
                runtime_cells[build_row][lane].SetObject(0);

                char normalized = LevelConvert(
                    active_segment->glyph_rows[authored_lane][segment_row],
                    build_row,
                    edge_row);
                switch (normalized) {
                case ' ':
                    runtime_cells[build_row][lane].tile_id = SUBLOC_TILE_EMPTY;
                    runtime_cells[build_row][lane].list_flags &= 0xffffffdf;
                    break;
                case 'R':
                    runtime_cells[build_row][lane].tile_id = SUBLOC_TILE_RING_MARKER;
                    runtime_cells[build_row][lane].list_flags &= 0xffffffdf;
                    break;
                case '#':
                    runtime_cells[build_row][lane].tile_id = SUBLOC_TILE_FLOOR_HASH_MARKER;
                    runtime_cells[build_row][lane].list_flags &= 0xffffffdf;
                    break;
                case '@':
                    runtime_cells[build_row][lane].tile_id = SUBLOC_TILE_EMPTY;
                    runtime_cells[build_row][lane].list_flags &= 0xffffffdf;
                    SwitchMirror();
                    break;
                case 'G':
                    runtime_cells[build_row][lane].SetObject(ROOT_BOD_OBJECT(slide_slices.storage[0]));
                    runtime_cells[build_row][lane].tile_id = SUBLOC_TILE_GLYPH_G;
                    runtime_cells[build_row][lane].list_flags |= 0x20;
                    break;
                case '_':
                    runtime_cells[build_row][lane].SetObject(ROOT_BOD_OBJECT(slide_slices.storage[0]));
                    runtime_cells[build_row][lane].tile_id = SUBLOC_TILE_SLIDE_UNDERSCORE;
                    runtime_cells[build_row][lane].list_flags |= 0x20;
                    break;
                case '$':
                    runtime_cells[build_row][lane].SetObject(ROOT_BOD_OBJECT(slide_slices.storage[0]));
                    runtime_cells[build_row][lane].tile_id = SUBLOC_TILE_HEALTH_PICKUP;
                    runtime_cells[build_row][lane].list_flags |= 0x20;
                    break;
                case 'o':
                    runtime_cells[build_row][lane].SetObject(ROOT_BOD_OBJECT(slide_slices.storage[0]));
                    runtime_cells[build_row][lane].tile_id = SUBLOC_TILE_SLIDE_O;
                    runtime_cells[build_row][lane].list_flags |= 0x20;
                    break;
                case 'M':
                    runtime_cells[build_row][lane].SetObject(ROOT_BOD_OBJECT(slide_slices.storage[0]));
                    runtime_cells[build_row][lane].tile_id = SUBLOC_TILE_SLUG_HAZARD;
                    runtime_cells[build_row][lane].list_flags |= 0x20;
                    break;
                case 'F':
                    runtime_cells[build_row][lane].SetObject(ROOT_BOD_OBJECT(slide_slices.storage[0]));
                    runtime_cells[build_row][lane].tile_id = SUBLOC_TILE_SLIDE_F;
                    runtime_cells[build_row][lane].list_flags |= 0x20;
                    break;
                case '.':
                    runtime_cells[build_row][lane].SetObject(ROOT_BOD_OBJECT(floor_slices.storage[0]));
                    runtime_cells[build_row][lane].tile_id = SUBLOC_TILE_FLOOR_DOT;
                    runtime_cells[build_row][lane].list_flags |= 0x20;
                    break;
                case 's':
                    runtime_cells[build_row][lane].SetObject(ROOT_BOD_OBJECT(floor_slices.storage[0]));
                    runtime_cells[build_row][lane].tile_id = SUBLOC_TILE_GARBAGE_HAZARD;
                    runtime_cells[build_row][lane].list_flags |= 0x20;
                    break;
                case '&':
                    runtime_cells[build_row][lane].SetObject(ROOT_BOD_OBJECT(floor_slices.storage[0]));
                    runtime_cells[build_row][lane].tile_id = SUBLOC_TILE_SALT_HAZARD;
                    runtime_cells[build_row][lane].list_flags |= 0x20;
                    break;
                case ',':
                    runtime_cells[build_row][lane].SetObject(ROOT_BOD_OBJECT(universe_hole));
                    runtime_cells[build_row][lane].tile_id = SUBLOC_TILE_UNIVERSE_HOLE;
                    runtime_cells[build_row][lane].list_flags |= 0x20;
                    break;
                case '+':
                    runtime_cells[build_row][lane].SetObject(ROOT_BOD_OBJECT(slide_slices.storage[0]));
                    runtime_cells[build_row][lane].tile_id = SUBLOC_TILE_SPEEDUP_PICKUP;
                    runtime_cells[build_row][lane].list_flags |= 0x20;
                    break;
                case 'J':
                    runtime_cells[build_row][lane].SetObject(ROOT_BOD_OBJECT(slide_slices.storage[0]));
                    runtime_cells[build_row][lane].tile_id = SUBLOC_TILE_JETPACK_PICKUP;
                    runtime_cells[build_row][lane].list_flags |= 0x20;
                    break;
                case '-':
                    runtime_cells[build_row][lane].SetObject(ROOT_BOD_OBJECT(floor_slices.storage[0]));
                    runtime_cells[build_row][lane].tile_id = SUBLOC_TILE_FLOOR_DASH;
                    runtime_cells[build_row][lane].list_flags |= 0x20;
                    break;
                case '=':
                case '|':
                    runtime_cells[build_row][lane].SetObject(ROOT_BOD_OBJECT(pillars[0]));
                    runtime_cells[build_row][lane].tile_id = SUBLOC_TILE_WALL2;
                    runtime_cells[build_row][lane].list_flags |= 0x20;
                    break;
                case '(':
                    ++trampoline_counter;
                    runtime_cells[build_row][lane].list_flags &= 0xffffffdf;
                    if (trampoline_counter == 15) {
                        trampoline_counter = 0;
                    } else if (trampoline_counter == 8) {
                        runtime_cells[build_row][lane].SetObject(ROOT_BOD_OBJECT(trampoline));
                        runtime_cells[build_row][lane].list_flags |= 0x20;
                        runtime_cells[build_row][lane].color.store_color4f(1.0f, 1.0f, 1.0f, 0.99900001f);
                    } else {
                        runtime_cells[build_row][lane].list_flags &= 0xffffffdf;
                    }
                    runtime_cells[build_row][lane].tile_id = SUBLOC_TILE_TRAMPOLINE;
                    break;
                case '>':
                    if (build_row > 0
                        && runtime_cells[build_row - 1][lane].tile_id
                            == SUBLOC_TILE_RAMP_GREATER) {
                        runtime_cells[build_row][lane].SetObject(ROOT_BOD_OBJECT(ramp_edges[1]));
                        runtime_cells[build_row][lane].render_arg_1c = 0;
                        runtime_cells[build_row][lane].render_arg_20 = 0;
                        runtime_cells[build_row][lane].tile_id =
                            SUBLOC_TILE_RAMP_GREATER_RAISED;
                        runtime_cells[build_row][lane].list_flags |= 0x20;
                        runtime_cells[build_row - 1][lane].tile_id =
                            SUBLOC_TILE_RAMP_GREATER_BACKPATCH;
                    } else {
                        runtime_cells[build_row][lane].SetObject(ROOT_BOD_OBJECT(ramp_edges[1]));
                        runtime_cells[build_row][lane].render_arg_1c = 0;
                        runtime_cells[build_row][lane].render_arg_20 = 0;
                        runtime_cells[build_row][lane].tile_id = SUBLOC_TILE_RAMP_GREATER;
                        runtime_cells[build_row][lane].list_flags |= 0x20;
                    }
                    break;
                case '}':
                    if (build_row > 0
                        && runtime_cells[build_row - 1][lane].tile_id
                            == SUBLOC_TILE_RAMP_GREATER) {
                        runtime_cells[build_row][lane].SetObject(ROOT_BOD_OBJECT(ramp_edges[2]));
                        runtime_cells[build_row][lane].render_arg_1c = 0;
                        runtime_cells[build_row][lane].render_arg_20 = 0;
                        runtime_cells[build_row][lane].tile_id =
                            SUBLOC_TILE_RAMP_RIGHT_BRACE_RAISED;
                        runtime_cells[build_row][lane].list_flags |= 0x20;
                        runtime_cells[build_row - 1][lane].tile_id =
                            SUBLOC_TILE_RAMP_RIGHT_BRACE_BACKPATCH;
                    } else {
                        runtime_cells[build_row][lane].SetObject(ROOT_BOD_OBJECT(ramp_edges[2]));
                        runtime_cells[build_row][lane].render_arg_1c = 0;
                        runtime_cells[build_row][lane].render_arg_20 = 0;
                        runtime_cells[build_row][lane].tile_id =
                            SUBLOC_TILE_RAMP_RIGHT_BRACE;
                        runtime_cells[build_row][lane].list_flags |= 0x20;
                    }
                    break;
                case '{':
                    if (build_row > 0
                        && runtime_cells[build_row - 1][lane].tile_id
                            == SUBLOC_TILE_RAMP_GREATER) {
                        runtime_cells[build_row][lane].SetObject(ROOT_BOD_OBJECT(ramp_edges[0]));
                        runtime_cells[build_row][lane].render_arg_1c = 0;
                        runtime_cells[build_row][lane].render_arg_20 = 0;
                        runtime_cells[build_row][lane].tile_id =
                            SUBLOC_TILE_RAMP_LEFT_BRACE_RAISED;
                        runtime_cells[build_row][lane].list_flags |= 0x20;
                        runtime_cells[build_row - 1][lane].tile_id =
                            SUBLOC_TILE_RAMP_LEFT_BRACE_BACKPATCH;
                    } else {
                        runtime_cells[build_row][lane].SetObject(ROOT_BOD_OBJECT(ramp_edges[0]));
                        runtime_cells[build_row][lane].render_arg_1c = 0;
                        runtime_cells[build_row][lane].render_arg_20 = 0;
                        runtime_cells[build_row][lane].tile_id =
                            SUBLOC_TILE_RAMP_LEFT_BRACE;
                        runtime_cells[build_row][lane].list_flags |= 0x20;
                    }
                    break;
                case '<':
                    runtime_cells[build_row][lane].SetObject(ROOT_BOD_OBJECT(ramp_edges[1]));
                    runtime_cells[build_row][lane].render_arg_1c = 0;
                    runtime_cells[build_row][lane].render_arg_20 = 0;
                    runtime_cells[build_row][lane].tile_id = SUBLOC_TILE_RAMP_LESS;
                    runtime_cells[build_row][lane].list_flags |= 0x20;
                    break;
                case '[':
                    runtime_cells[build_row][lane].SetObject(ROOT_BOD_OBJECT(ramp_edges[0]));
                    runtime_cells[build_row][lane].render_arg_1c = 0;
                    runtime_cells[build_row][lane].render_arg_20 = 0;
                    runtime_cells[build_row][lane].tile_id = SUBLOC_TILE_RAMP_LEFT_BRACKET;
                    runtime_cells[build_row][lane].list_flags |= 0x20;
                    break;
                case 'P':
                case 'p': {
                    cRSubLoc* runtime_cell = &runtime_cells[build_row][lane];
                    if (normalized == 'P')
                        runtime_cells[build_row][lane].tile_id =
                            SUBLOC_TILE_PATH_ENTRY_UPPERCASE;
                    else if (normalized == 'p')
                        runtime_cells[build_row][lane].tile_id =
                            SUBLOC_TILE_PATH_ENTRY_LOWERCASE;

                    if (track_mirror_enabled)
                        runtime_cells[build_row][lane].attachment_template_record =
                            &paths[runtime_rows[build_row].attachment_template_index][1];
                    else
                        runtime_cells[build_row][lane].attachment_template_record =
                            &paths[runtime_rows[build_row].attachment_template_index][0];

                    runtime_cells[build_row][lane].list_flags &= 0xffffffdf;
                    if (attachment_entry_installed == 0) {
                        attachment_entry_installed = 1;
                        runtime_cells[build_row][lane].SetObject(
                            runtime_cells[build_row][lane].attachment_template_record->object);
                        runtime_cells[build_row][lane].list_flags |= 0x20;
                        runtime_rows[build_row].attachment_body.SetObject(
                            runtime_cells[build_row][lane].attachment_template_record
                                ->fringe_mesh_bod.object);
                        runtime_rows[build_row].attachment_body.list_flags |= 0x20;
                        runtime_rows[build_row].installed_heading_delta =
                            active_segment->angle_radians.value;

                        for (int span_index = 0;
                             span_index
                                < runtime_cells[build_row][lane].attachment_template_record->row_span_count;
                             ++span_index) {
                            unsigned int& row_flags = runtime_rows[build_row + span_index].flags;
                            unsigned int stamped_flags = row_flags;
                            if ((stamped_flags & SUBROW_FLAG_PRIMARY_ATTACHMENT) != 0) {
                                row_flags =
                                    stamped_flags | SUBROW_FLAG_SECONDARY_ATTACHMENT;
                                runtime_rows[build_row + span_index].secondary_attachment_cell =
                                    runtime_cell;
                            } else {
                                row_flags =
                                    stamped_flags | SUBROW_FLAG_PRIMARY_ATTACHMENT;
                                runtime_rows[build_row + span_index].primary_attachment_cell =
                                    runtime_cell;
                            }
                        }
                    }
                    break;
                }
                case '0':
                    if (level_mode == 1) {
                        runtime_rows[build_row].flags =
                            (runtime_rows[build_row].flags
                                & ~SUBROW_FLAG_PARCEL_Z_IS_LOCAL)
                            | SUBROW_FLAG_PARCEL_CANDIDATE;
                        runtime_rows[build_row].parcel_set_id = 0;
                        runtime_rows[build_row].parcel_spawn_position.x =
                            (float)lane - 4.0f + 0.5f;
                        runtime_rows[build_row].parcel_spawn_position.y =
                            runtime_cells[build_row][lane].position.y;
                        runtime_rows[build_row].parcel_spawn_position.z =
                            (float)build_row + 0.5f;
                        if (track_mirror_enabled)
                            runtime_rows[build_row].parcel_spawn_position.x *= -1.0f;
                    }
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    if ((runtime_rows[build_row].flags & SUBROW_ATTACHMENT_MASK)
                        == 0) {
                        runtime_cells[build_row][lane].SetObject(ROOT_BOD_OBJECT(slide_slices.storage[0]));
                        runtime_cells[build_row][lane].tile_id = SUBLOC_TILE_SLIDE_UNDERSCORE;
                        runtime_cells[build_row][lane].list_flags |= 0x20;
                    } else {
                        runtime_cells[build_row][lane].list_flags &= 0xffffffdf;
                        runtime_cells[build_row][lane].tile_id = SUBLOC_TILE_EMPTY;
                    }
                    break;
                default:
                    debug_report_stub(
                        "TrackError:%c in Segment %s\n",
                        LevelConvert(
                            active_segment->glyph_rows[authored_lane][segment_row], build_row, 1),
                        active_segment->source_name);
                    break;
                }

                Vector3* cell_position = &runtime_cells[build_row][lane].position;
                cell_position->z = 0.0f;
                cell_position->y = 0.0f;
                cell_position->x = 0.0f;
                *(int*)(
                    (char*)&runtime_rows[build_row] + ROW_ATTACHMENT_POSITION_Z) =
                    0;
                *(int*)(
                    (char*)&runtime_rows[build_row] + ROW_ATTACHMENT_POSITION_Y) =
                    0;
                *(int*)(
                    (char*)&runtime_rows[build_row] + ROW_ATTACHMENT_POSITION_X) =
                    0;

                unsigned char tile = runtime_cells[build_row][lane].tile_id;
                float row_anchor_z;
                if (tile == SUBLOC_TILE_PATH_ENTRY_LOWERCASE
                    || tile == SUBLOC_TILE_PATH_ENTRY_UPPERCASE) {
                    runtime_cells[build_row][lane].position.x = 0.0f;
                    row_anchor_z = (float)build_row + 0.5f;
                    runtime_cells[build_row][lane].position.z = row_anchor_z - 0.5f;
                    if ((g_runtime_config.render_flags & RUNTIME_RENDER_TRACK_FRINGE) != 0) {
                        *(int*)(
                            (char*)&runtime_rows[build_row]
                            + ROW_ATTACHMENT_POSITION_X) = 0;
                        *(float*)(
                            (char*)&runtime_rows[build_row]
                            + ROW_ATTACHMENT_POSITION_Z) =
                            row_anchor_z - 0.5f;

                        tColour skirt_color;
                        tColour* resolved_color =
                            g_game->subgame.GetSkirtColour(&skirt_color);
                        runtime_rows[build_row].attachment_body.color = *resolved_color;
                        set_object_color(
                            runtime_rows[build_row].attachment_body.object,
                            *resolved_color);
                    } else {
                        runtime_rows[build_row].attachment_body.list_flags &= 0xffffffdf;
                    }
                } else {
                    runtime_cells[build_row][lane].position.x = (float)lane - 4.0f + 0.5f;
                    runtime_cells[build_row][lane].position.y = 0.0f;
                    tile = runtime_cells[build_row][lane].tile_id;
                    if (tile == SUBLOC_TILE_RAMP_LEFT_BRACE_RAISED
                        || tile == SUBLOC_TILE_RAMP_GREATER_RAISED
                        || tile == SUBLOC_TILE_RAMP_RIGHT_BRACE_RAISED)
                        runtime_cells[build_row][lane].position.y = 0.5f;
                    row_anchor_z = (float)build_row + 0.5f;
                    runtime_cells[build_row][lane].position.z = row_anchor_z;
                }

                if (build_row < 4 && level_mode != 2)
                    runtime_cells[build_row][lane].position.y = *(float*)(
                        *(char**)(base + PATH_36_PRIMARY_SAMPLES)
                        + ATTACHMENT_SAMPLE_POSITION_Y);

                if (runtime_cells[build_row][lane].tile_id == SUBLOC_TILE_UNIVERSE_HOLE)
                    runtime_cells[build_row][lane].position.y -= 0.029999999f;

                tile = runtime_cells[build_row][lane].tile_id;
                if (tile == SUBLOC_TILE_FLOOR_DOT
                    || tile == SUBLOC_TILE_FLOOR_DASH
                    || tile == SUBLOC_TILE_FLOOR_VARIANT_14
                    || tile == SUBLOC_TILE_GARBAGE_HAZARD
                    || tile == SUBLOC_TILE_SALT_HAZARD
                    || tile == SUBLOC_TILE_SLIDE_UNDERSCORE
                    || tile == SUBLOC_TILE_SLIDE_O
                    || tile == SUBLOC_TILE_HEALTH_PICKUP
                    || tile == SUBLOC_TILE_SPEEDUP_PICKUP
                    || tile == SUBLOC_TILE_JETPACK_PICKUP
                    || tile == SUBLOC_TILE_SLIDE_VARIANT_1A
                    || tile == SUBLOC_TILE_FLOOR_VARIANT_1B
                    || tile == SUBLOC_TILE_SLUG_HAZARD
                    || tile == SUBLOC_TILE_SLIDE_F
                    || tile == SUBLOC_TILE_GLYPH_G) {
                    runtime_cells[build_row][lane].render_arg_1c =
                        (float)(RUNTIME_LANE_COUNT - lane) * 0.125f;
                    runtime_cells[build_row][lane].render_arg_20 =
                        (float)(build_row % 8) * 0.125f;
                }

                if (runtime_cells[build_row][lane].tile_id == SUBLOC_TILE_WIDE_VARIANT_1F)
                    runtime_cells[build_row][lane].position.x *= 1.10000002f;

                if (runtime_cells[build_row][lane].tile_id == SUBLOC_TILE_TRAMPOLINE) {
                    if (level_mode != 3
                        || (runtime_flags & SUBGAME_RUNTIME_FLAG_ALLOW_FALLING) != 0)
                        runtime_cells[build_row][lane].position.y = -3.0f;
                    runtime_cells[build_row][lane].position.z = row_anchor_z;
                }

                for (int subobject_index = 0;
                     subobject_index < CELL_FRINGE_COUNT;
                     ++subobject_index) {
                    Fringe* object = *subobject_slot;
                    if (object != 0) {
                        object->position.z = 0.0f;
                        object->position.y = 0.0f;
                        object->position.x = 0.0f;
                        object = *subobject_slot;
                        object->position = runtime_cells[build_row][lane].position;
                    }
                    ++subobject_slot;
                }
            }
            ++segment_row;
            ++build_row;
        }
        if (level_mode == 3) {
            if (first_or_last_row == 0)
                ++row_event_owner;
        } else {
            ++row_event_owner;
        }
    } while (build_row < runtime_row_count);

    (void)trampoline_counter;
}

#undef ROOT_BOD_OBJECT
