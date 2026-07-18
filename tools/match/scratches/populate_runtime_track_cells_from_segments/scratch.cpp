// populate_runtime_track_cells_from_segments @ 0x435eb0 (thiscall, ret)
// Structure-first scratch for the runtime grid builder setup and clear pass.

#include <stddef.h>

#include "sprite.h"
#include "fringe_object.h"
#include "game_root.h"
#include "runtime_config.h"
#include "subgame_runtime.h"
#include "game_time.h"
#include "root_bod_catalog.h"
#include "track_attachment_types.h"
#include "track.h"


#define ROOT_BOD_OBJECT(slot) (g_game->root_bod_catalog.slot.object)

double random_float_below(float upper_bound, const char* tag);
void set_math_random_seed(int seed);
int report_errorf(const char* format, ...);
int debug_report_stub(const char* format, ...);
void set_object_color(Object* object, tColour color);

void SubgameRuntime::populate_runtime_track_cells_from_segments()
{
    char* base = (char*)this;
    int runtime_build_seed;

    if (selected_level_record_active != 0) {
        SubSolution* record = selected_level_record;
        runtime_build_seed = record->runtime_build_seed;
    } else {
        int mode = level_mode;
        if (mode == 4 || mode == 7) {
            runtime_build_seed = 0;
        } else {
            runtime_build_seed = (int)random_float_below(32768.0f, "Seed");
        }
    }

    int mode = level_mode;
    switch (mode) {
    case 0:
        current_high_score_record.initialize_high_score_entry(
            runtime_build_seed,
            level_mode_arg,
            level_arg_tail,
            runtime_flags,
            0,
            level_mode_arg);
        break;
    case 1:
        current_high_score_record.initialize_high_score_entry(
            runtime_build_seed,
            level_mode_arg,
            level_arg_tail,
            runtime_flags,
            1,
            level_mode_arg);
        break;
    case 4:
        current_high_score_record.initialize_high_score_entry(
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
        player.clear_subgoldy_score_buckets();
        player.visible_life_stock = 3;
    }

    player.stopwatch.Zero();
    player.score_tail = 0;
    player.movement_flag_selector = 0;
    set_math_random_seed(runtime_build_seed);
    g_game->track.Change(level_definition.track_texture_set);

    int segment_cursor = 0;
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
            runtime_row_count = level_definition.first_segment.row_count
                + level_definition.last_segment.row_count;
            for (int i = 0; i < level_definition.segment_count; ++i)
                runtime_row_count += level_definition.segment_slots[i].row_count;
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
        first_block_row_count = level_definition.first_segment.row_count;
        runtime_row_count = level_definition.first_segment.row_count
            + level_definition.last_segment.row_count;
        for (int i = 0; i < 16; ++i)
            runtime_row_count += level_definition.segment_slots[0].row_count;
        segment_cursor = 0;
        completion_row_start = runtime_row_count - level_definition.last_segment.row_count;
        completion_row_start = runtime_row_count - level_definition.last_segment.row_count;
    }

    track_mirror_enabled = false;
    track_mirror_repeat_count = 0;
    int trampoline_counter = 0;
    char first_or_last_row = 0;
    int row_event_owner = 0;
    player.follow_state.flag_3c = 0;

    enum {
        TRACK_MIRROR_FLAG_OFFSET =
            offsetof(SubgameRuntime, track_mirror_enabled),
        LEVEL_SEGMENT_SLOTS_BASE =
            offsetof(SubgameRuntime, level_definition)
            + offsetof(SubTracks, segment_slots),
        LEVEL_FIRST_SEGMENT_BASE =
            offsetof(SubgameRuntime, level_definition)
            + offsetof(SubTracks, first_segment),
        LEVEL_LAST_SEGMENT_BASE =
            offsetof(SubgameRuntime, level_definition)
            + offsetof(SubTracks, last_segment),
        SCRATCH_SEGMENT_SLOTS_BASE =
            offsetof(SubgameRuntime, level_definition_scratch)
            + offsetof(SubTracks, segment_slots),
        RUNTIME_CELLS_BASE = offsetof(SubgameRuntime, runtime_cells),
        RUNTIME_ROWS_BASE = offsetof(SubgameRuntime, runtime_rows),
        RUNTIME_LANE_COUNT =
            sizeof(runtime_cells[0]) / sizeof(runtime_cells[0][0]),
        CELL_BOD_BASE = RUNTIME_CELLS_BASE,
        CELL_LIST_FLAGS =
            RUNTIME_CELLS_BASE + offsetof(ContactTargetObject, list_flags),
        CELL_POSITION_X =
            RUNTIME_CELLS_BASE + offsetof(BodBase, position)
            + offsetof(Vector3, x),
        CELL_POSITION_Y =
            RUNTIME_CELLS_BASE + offsetof(BodBase, position)
            + offsetof(Vector3, y),
        CELL_POSITION_Z =
            RUNTIME_CELLS_BASE + offsetof(BodBase, position)
            + offsetof(Vector3, z),
        CELL_RENDER_ARG_1C =
            RUNTIME_CELLS_BASE + offsetof(BodBase, render_arg_1c),
        CELL_RENDER_ARG_20 =
            RUNTIME_CELLS_BASE + offsetof(BodBase, render_arg_20),
        CELL_COLOR_INDEX_BIAS =
            (RUNTIME_CELLS_BASE + offsetof(BodBase, color)) / sizeof(SubLoc),
        CELL_TILE_ID = RUNTIME_CELLS_BASE + offsetof(SubLoc, tile_id),
        PREVIOUS_ROW_CELL_TILE_ID =
            CELL_TILE_ID - RUNTIME_LANE_COUNT * sizeof(SubLoc),
        CELL_LANE_FLAGS =
            RUNTIME_CELLS_BASE + offsetof(SubLoc, lane_and_flags),
        CELL_FRINGE_FRONT =
            RUNTIME_CELLS_BASE + offsetof(SubLoc, fringe_front),
        CELL_FRINGE_RIGHT =
            RUNTIME_CELLS_BASE + offsetof(SubLoc, fringe_right),
        CELL_FRINGE_LEFT =
            RUNTIME_CELLS_BASE + offsetof(SubLoc, fringe_left),
        CELL_FRINGE_BACK =
            RUNTIME_CELLS_BASE + offsetof(SubLoc, fringe_back),
        CELL_FRINGE_COUNT =
            sizeof(((SubLoc*)0)->fringes) / sizeof(((SubLoc*)0)->fringes[0]),
        PATH_PAIRS_BASE = offsetof(SubgameRuntime, path_pairs),
        PATH_PAIR_SECONDARY_DELTA = offsetof(PathPair, secondary),
        PATH_36_PRIMARY_SAMPLES =
            PATH_PAIRS_BASE + 36 * sizeof(PathPair)
            + offsetof(PathPair, primary) + offsetof(Path, primary_samples),
        SEGMENT_GLYPH_ROWS_BASE = offsetof(SubSegment, glyph_rows),
        SEGMENT_GLYPH_ROW_STRIDE =
            sizeof(((SubSegment*)0)->glyph_rows[0]),
        SEGMENT_AUTHORED_ROWS_BASE = offsetof(SubSegment, rows),
        SEGMENT_ANGLE_RADIANS = offsetof(SubSegment, angle_radians),
        AUTHORED_ROW_PARCEL_SET_ID =
            offsetof(AuthoredSegmentRow, parcel_set_id),
        AUTHORED_ROW_LOCAL_X =
            offsetof(AuthoredSegmentRow, local_position) + offsetof(Vector3, x),
        AUTHORED_ROW_LOCAL_Y =
            offsetof(AuthoredSegmentRow, local_position) + offsetof(Vector3, y),
        AUTHORED_ROW_LOCAL_Z =
            offsetof(AuthoredSegmentRow, local_position) + offsetof(Vector3, z),
        AUTHORED_ROW_OBJECT_ID = offsetof(AuthoredSegmentRow, object_id),
        AUTHORED_ROW_OBJECT_POSITION_X =
            offsetof(AuthoredSegmentRow, object_position) + offsetof(Vector3, x),
        AUTHORED_ROW_OBJECT_POSITION_Y =
            offsetof(AuthoredSegmentRow, object_position) + offsetof(Vector3, y),
        AUTHORED_ROW_OBJECT_POSITION_Z =
            offsetof(AuthoredSegmentRow, object_position) + offsetof(Vector3, z),
        AUTHORED_ROW_OBJECT_VELOCITY_X =
            offsetof(AuthoredSegmentRow, object_velocity) + offsetof(Vector3, x),
        AUTHORED_ROW_OBJECT_VELOCITY_Y =
            offsetof(AuthoredSegmentRow, object_velocity) + offsetof(Vector3, y),
        AUTHORED_ROW_OBJECT_VELOCITY_Z =
            offsetof(AuthoredSegmentRow, object_velocity) + offsetof(Vector3, z),
        AUTHORED_ROW_PATH_TEMPLATE_INDEX =
            offsetof(AuthoredSegmentRow, path_template_index),
        AUTHORED_ROW_RING_SPEED = offsetof(AuthoredSegmentRow, ring_speed),
        ROW_MODEL_TRANSFORM =
            offsetof(SubRow, row_model) + offsetof(RenderableBod, transform),
        ROW_MODEL_POSITION_X =
            ROW_MODEL_TRANSFORM + offsetof(TransformMatrix, position)
            + offsetof(Vector3, x),
        ROW_MODEL_POSITION_Y =
            ROW_MODEL_TRANSFORM + offsetof(TransformMatrix, position)
            + offsetof(Vector3, y),
        ROW_MODEL_POSITION_Z =
            ROW_MODEL_TRANSFORM + offsetof(TransformMatrix, position)
            + offsetof(Vector3, z),
        ROW_MODEL_VELOCITY_X =
            offsetof(SubRow, row_model) + offsetof(RowModel, velocity)
            + offsetof(Vector3, x),
        ROW_MODEL_VELOCITY_Y =
            offsetof(SubRow, row_model) + offsetof(RowModel, velocity)
            + offsetof(Vector3, y),
        ROW_MODEL_VELOCITY_Z =
            offsetof(SubRow, row_model) + offsetof(RowModel, velocity)
            + offsetof(Vector3, z),
        ROW_PROJECTION_X =
            offsetof(SubRow, projection_payload) + offsetof(Vector3, x),
        ROW_PROJECTION_Y =
            offsetof(SubRow, projection_payload) + offsetof(Vector3, y),
        ROW_PROJECTION_Z =
            offsetof(SubRow, projection_payload) + offsetof(Vector3, z),
        ROW_ATTACHMENT_LIST_FLAGS =
            offsetof(SubRow, attachment_body)
            + offsetof(ContactTargetObject, list_flags),
        ROW_ATTACHMENT_POSITION_X =
            offsetof(SubRow, attachment_body) + offsetof(BodBase, position)
            + offsetof(Vector3, x),
        ROW_ATTACHMENT_POSITION_Y =
            offsetof(SubRow, attachment_body) + offsetof(BodBase, position)
            + offsetof(Vector3, y),
        ROW_ATTACHMENT_POSITION_Z =
            offsetof(SubRow, attachment_body) + offsetof(BodBase, position)
            + offsetof(Vector3, z),
        ROW_ATTACHMENT_COLOR =
            offsetof(SubRow, attachment_body) + offsetof(BodBase, color),
        ROW_CURSOR_BASE =
            offsetof(SubRow, projection_payload) + offsetof(Vector3, y),
        ROW_CURSOR_TO_FLAGS =
            ((int)offsetof(SubRow, flags) - ROW_CURSOR_BASE) / sizeof(int),
        ROW_CURSOR_TO_PROJECTION_X =
            ((int)offsetof(SubRow, projection_payload)
             + (int)offsetof(Vector3, x) - ROW_CURSOR_BASE) / sizeof(int),
        ROW_CURSOR_TO_PROJECTION_Y = 0,
        ROW_CURSOR_TO_PROJECTION_Z =
            ((int)offsetof(SubRow, projection_payload)
             + (int)offsetof(Vector3, z) - ROW_CURSOR_BASE) / sizeof(int),
        ROW_CURSOR_TO_PARCEL_SET_ID =
            ((int)offsetof(SubRow, parcel_set_id) - ROW_CURSOR_BASE) / sizeof(int),
        ROW_CURSOR_TO_ATTACHMENT_TEMPLATE_INDEX =
            ((int)offsetof(SubRow, attachment_template_index) - ROW_CURSOR_BASE)
            / sizeof(int),
        ROW_CURSOR_TO_PRIMARY_ATTACHMENT_CELL =
            ((int)offsetof(SubRow, primary_attachment_cell) - ROW_CURSOR_BASE)
            / sizeof(int),
        ROW_CURSOR_TO_INSTALLED_HEADING =
            ((int)offsetof(SubRow, installed_heading_delta) - ROW_CURSOR_BASE)
            / sizeof(int),
        ROW_CURSOR_TO_RING_SPEED =
            ((int)offsetof(SubRow, ring_speed) - ROW_CURSOR_BASE) / sizeof(int),
        ROW_CURSOR_TO_SOURCE_SEGMENT =
            ((int)offsetof(SubRow, source_segment) - ROW_CURSOR_BASE) / sizeof(int),
        ROW_CURSOR_TO_ROW_EVENT_ID =
            ((int)offsetof(SubRow, row_event_id) - ROW_CURSOR_BASE) / sizeof(int),
        CELL_FRINGE_TO_LANE_FLAGS =
            (int)offsetof(SubLoc, lane_and_flags)
            - (int)offsetof(SubLoc, fringe_front),
        CELL_LANE_FLAGS_TO_TILE_FLAGS =
            (int)offsetof(SubLoc, open_edge_mask)
            - (int)offsetof(SubLoc, lane_and_flags),
        CELL_LANE_FLAGS_TO_LIST_FLAGS =
            (int)offsetof(ContactTargetObject, list_flags)
            - (int)offsetof(SubLoc, lane_and_flags),
        CELL_LANE_FLAGS_TO_COLOR =
            (int)offsetof(BodBase, color)
            - (int)offsetof(SubLoc, lane_and_flags),
        ATTACHMENT_SAMPLE_POSITION_Y =
            offsetof(AttachmentSample, transform)
            + offsetof(TransformMatrix, position) + offsetof(Vector3, y),
    };
    char* cell_payload_cursor = (char*)&runtime_cells[0][0].fringes[0];
    int* row_cursor = (int*)&runtime_rows[0].projection_payload.y;
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
            int flags = *(int*)cell_flags;
            ((unsigned char*)&flags)[1] &= 0x5f;
            *(int*)cell_flags = flags;
            *(cell_flags + CELL_LANE_FLAGS_TO_TILE_FLAGS) = 0;
            *(short*)cell_flags = 0;
            *(int*)cell_flags &= 0xffffafa7;
            *(short*)cell_flags = 0;
            *(int*)(cell_flags + CELL_LANE_FLAGS_TO_LIST_FLAGS) &= 0xffffff7f;
            ((tColour*)(cell_flags + CELL_LANE_FLAGS_TO_COLOR))->set_color_white();
            cell_flags += sizeof(SubLoc);
        }

        char* cell_payload = cell_payload_cursor;
        for (int lane_payload = 0;
             lane_payload
                < (int)(sizeof(runtime_cells[0]) / sizeof(runtime_cells[0][0]));
             ++lane_payload) {
            *(int*)cell_payload = 0;
            *(int*)(cell_payload + 4) = 0;
            *(int*)(cell_payload + 8) = 0;
            *(int*)(cell_payload + 12) = 0;
            cell_payload += sizeof(SubLoc);
        }
        cell_payload_cursor = cell_payload;
        row_cursor += sizeof(SubRow) / sizeof(int);
    }

    if (level_definition.random_enabled == 1) {
        for (int i = 0; i < level_definition.segment_count; ++i)
            level_definition.segment_slots[i].visited = 0;
    }

    if (runtime_row_count <= 0)
        return;

    int segment_row = 0;
    char* active_segment = 0;
    for (int build_row = 0; build_row < runtime_row_count; ++build_row) {
        if (build_row == 0) {
            active_segment = base + LEVEL_FIRST_SEGMENT_BASE;
            first_or_last_row = 1;
            segment_row = 0;
            ((SubSegment*)active_segment)->row_base = build_row;
        } else if (build_row == completion_row_start && level_definition.random_enabled == 0) {
            active_segment = base + LEVEL_LAST_SEGMENT_BASE;
            first_or_last_row = 1;
            segment_row = 0;
            ((SubSegment*)active_segment)->row_base = build_row;
        } else if (segment_row >= ((SubSegment*)active_segment)->row_count) {
            first_or_last_row = 0;
            base_subgame_rate = 1.0f;
            if (level_definition.random_enabled == 1) {
                float segment_pick_range;
                if (level_mode == 1) {
                    segment_pick_range =
                        (challenge_difficulty_scalar * 0.89999998f + 0.100000001f)
                        * (float)level_definition.segment_count;
                    int picked = (int)random_float_below(segment_pick_range, "Segdif");
                    picked = (int)((float)picked * base_subgame_rate);
                    active_segment =
                        base + LEVEL_SEGMENT_SLOTS_BASE + sizeof(SubSegment) * picked;
                } else {
                    segment_pick_range = (float)level_definition.segment_count;
                    int picked = (int)random_float_below(segment_pick_range, "Segtra");
                    picked = (int)((float)picked * base_subgame_rate);
                    active_segment =
                        base + LEVEL_SEGMENT_SLOTS_BASE + sizeof(SubSegment) * picked;
                }
                ((SubSegment*)active_segment)->visited = 1;
            } else {
                int picked = segment_cursor;
                ++segment_cursor;
                active_segment =
                    base + LEVEL_SEGMENT_SLOTS_BASE + sizeof(SubSegment) * picked;
                switch_track_mirror();
            }
            segment_row = 0;
            ((SubSegment*)active_segment)->row_base = build_row;
            if (((SubSegment*)active_segment)->row_count < 0)
                report_errorf("Negative Segment Length");
        }

        if (level_mode != 2 && build_row >= completion_row_start) {
            if (level_mode == 0 || level_mode == 4 || level_mode == 1 || level_mode == 7) {
                active_segment = base + LEVEL_LAST_SEGMENT_BASE;
                if (build_row == completion_row_start)
                    segment_row = 0;
            } else if (level_mode == 3) {
                active_segment =
                    base + SCRATCH_SEGMENT_SLOTS_BASE + sizeof(SubSegment);
            }

            int segment_end =
                ((SubSegment*)active_segment)->row_count - segment_row + build_row;
            // Keep byte-shaped address formation for scratch slots 1, 3, and
            // 4 while deriving their storage from the complete owner.
            if (segment_end > completion_row_start
                && active_segment
                    != base + SCRATCH_SEGMENT_SLOTS_BASE + sizeof(SubSegment)
                && active_segment
                    != base + SCRATCH_SEGMENT_SLOTS_BASE + 3 * sizeof(SubSegment)
                && active_segment
                    != base + SCRATCH_SEGMENT_SLOTS_BASE + 4 * sizeof(SubSegment)
                && (level_mode == 0
                    || level_mode == 4
                    || level_mode == 1
                    || level_mode == 7
                    || (level_mode == 3
                        && active_segment != base + LEVEL_LAST_SEGMENT_BASE))) {
                int extra_rows = ((SubSegment*)active_segment)->row_count
                    - completion_row_start - segment_row + build_row;
                completion_row_start += extra_rows;
                runtime_row_count += extra_rows;
            }
        }

        char* row_record = base + sizeof(SubRow) * build_row + RUNTIME_ROWS_BASE;
        if (base[TRACK_MIRROR_FLAG_OFFSET])
            *(int*)row_record |= SUBROW_FLAG_MIRRORED;

        int authored_flags = *(int*)(
            active_segment + SEGMENT_AUTHORED_ROWS_BASE
            + sizeof(AuthoredSegmentRow) * segment_row);
        if ((authored_flags & AUTHORED_SEGMENT_ROW_FLAG_NO_FALL) != 0)
            *(int*)row_record |= SUBROW_FLAG_NO_FALL;
        if ((authored_flags & AUTHORED_SEGMENT_ROW_FLAG_JETPACK_OFF) != 0)
            *(int*)row_record |= SUBROW_FLAG_JETPACK_OFF;

        *(char**)(row_record + offsetof(SubRow, source_segment)) = active_segment;
        *(int*)(row_record + offsetof(SubRow, row_event_id)) = row_event_owner;

        char* authored_row = active_segment + SEGMENT_AUTHORED_ROWS_BASE
            + sizeof(AuthoredSegmentRow) * segment_row;
        if ((authored_flags & AUTHORED_SEGMENT_ROW_FLAG_3D_MODEL) != 0) {
            *(int*)row_record |= SUBROW_FLAG_ROW_MODEL_PRESENT;
            int object_id = *(int*)(authored_row + AUTHORED_ROW_OBJECT_ID);
            Object* object =
                g_game->directx_loader.cached_x_mesh_slots[object_id].object;
            ((SubRow*)row_record)->row_model.set_bod_object(object);
            ((SubRow*)row_record)->row_model.transform.set_matrix_identity();
            *(int*)(row_record + ROW_MODEL_POSITION_X) =
                *(int*)(authored_row + AUTHORED_ROW_OBJECT_POSITION_X);
            *(int*)(row_record + ROW_MODEL_POSITION_Y) =
                *(int*)(authored_row + AUTHORED_ROW_OBJECT_POSITION_Y);
            *(int*)(row_record + ROW_MODEL_POSITION_Z) =
                *(int*)(authored_row + AUTHORED_ROW_OBJECT_POSITION_Z);
            *(float*)(row_record + ROW_MODEL_POSITION_Z) += (float)build_row;

            if ((authored_flags
                    & AUTHORED_SEGMENT_ROW_FLAG_PATH_OR_MODEL_VELOCITY)
                != 0) {
                *(int*)row_record |= SUBROW_FLAG_PATH_OR_MODEL_VELOCITY;
                *(int*)(row_record + ROW_MODEL_VELOCITY_X) =
                    *(int*)(authored_row + AUTHORED_ROW_OBJECT_VELOCITY_X);
                *(int*)(row_record + ROW_MODEL_VELOCITY_Y) =
                    *(int*)(authored_row + AUTHORED_ROW_OBJECT_VELOCITY_Y);
                *(int*)(row_record + ROW_MODEL_VELOCITY_Z) =
                    *(int*)(authored_row + AUTHORED_ROW_OBJECT_VELOCITY_Z);
            } else {
                *(int*)(row_record + ROW_MODEL_VELOCITY_X) = 0;
                *(int*)(row_record + ROW_MODEL_VELOCITY_Y) = 0;
                *(int*)(row_record + ROW_MODEL_VELOCITY_Z) = 0;
            }
        }

        if ((authored_flags & AUTHORED_SEGMENT_ROW_FLAG_PARCEL) != 0) {
            *(int*)row_record |=
                SUBROW_FLAG_PARCEL_CANDIDATE | SUBROW_FLAG_PARCEL_Z_IS_LOCAL;
            ((SubRow*)row_record)->parcel_set_id =
                *(int*)(authored_row + AUTHORED_ROW_PARCEL_SET_ID);
            *(int*)(row_record + ROW_PROJECTION_X) =
                *(int*)(authored_row + AUTHORED_ROW_LOCAL_X);
            *(int*)(row_record + ROW_PROJECTION_Y) =
                *(int*)(authored_row + AUTHORED_ROW_LOCAL_Y);
            *(int*)(row_record + ROW_PROJECTION_Z) =
                *(int*)(authored_row + AUTHORED_ROW_LOCAL_Z);
        }
        if ((authored_flags
                & AUTHORED_SEGMENT_ROW_FLAG_PATH_OR_MODEL_VELOCITY)
            != 0) {
            *(int*)row_record |= SUBROW_FLAG_PATH_OR_MODEL_VELOCITY;
            ((SubRow*)row_record)->attachment_template_index =
                *(int*)(authored_row + AUTHORED_ROW_PATH_TEMPLATE_INDEX);
        }
        if ((authored_flags & AUTHORED_SEGMENT_ROW_FLAG_STAR_MARKER) != 0)
            *(int*)row_record |= SUBROW_FLAG_SUPPRESS_TRACK_RENDER;
        if ((authored_flags & AUTHORED_SEGMENT_ROW_FLAG_RING_NONE) != 0)
            *(int*)row_record |= SUBROW_FLAG_RING_NONE;
        if ((authored_flags & AUTHORED_SEGMENT_ROW_FLAG_RING_NORMAL) != 0)
            *(int*)row_record |= SUBROW_FLAG_RING_NORMAL;
        if ((authored_flags & AUTHORED_SEGMENT_ROW_FLAG_RING_POWER_UP) != 0)
            *(int*)row_record |= SUBROW_FLAG_RING_POWER_UP;
        if ((authored_flags & AUTHORED_SEGMENT_ROW_FLAG_RING_EXPLODE) != 0)
            *(int*)row_record |= SUBROW_FLAG_RING_EXPLODE;
        if ((authored_flags & AUTHORED_SEGMENT_ROW_FLAG_RING_SLOW) != 0)
            *(int*)row_record |= SUBROW_FLAG_RING_SLOW;
        *(int*)(row_record + offsetof(SubRow, ring_speed)) =
            *(int*)(authored_row + AUTHORED_ROW_RING_SPEED);

        char attachment_entry_installed = 0;
        for (int lane = 0; lane < RUNTIME_LANE_COUNT; ++lane) {
            int authored_lane;
            if (base[TRACK_MIRROR_FLAG_OFFSET])
                authored_lane = RUNTIME_LANE_COUNT - 1 - lane;
            else
                authored_lane = lane;

            char* cell =
                base + sizeof(SubLoc) * (lane + build_row * RUNTIME_LANE_COUNT);
            int cell_word = *(int*)(cell + CELL_LANE_FLAGS);
            ((unsigned char*)&cell_word)[0] &= 0xe0;
            cell_word ^= lane & SUBLOC_LANE_INDEX_MASK;
            *(int*)(cell + CELL_LANE_FLAGS) = cell_word;

            *(int*)(cell + CELL_FRINGE_FRONT) = 0;
            *(int*)(cell + CELL_FRINGE_RIGHT) = 0;
            *(int*)(cell + CELL_FRINGE_LEFT) = 0;
            *(int*)(cell + CELL_FRINGE_BACK) = 0;

            char edge_row;
            if (build_row >= first_block_row_count) {
                edge_row = 0;
                if (build_row >= completion_row_start)
                    edge_row = 1;
            } else {
                edge_row = 1;
            }

            // initialize_sub_loc proves this is the shared cRBod base prefix;
            // keep the raw cursor so the large VC6 switch retains its shape.
            ((BodBase*)(cell + CELL_BOD_BASE))->set_bod_object(0);

            char* glyph_ptr = active_segment
                + authored_lane * SEGMENT_GLYPH_ROW_STRIDE + lane
                + SEGMENT_GLYPH_ROWS_BASE;
            char glyph = *glyph_ptr;
            char normalized =
                normalize_segment_glyph_for_track_flags(glyph, build_row, edge_row);
            switch (normalized) {
            case ' ':
                *(unsigned char*)(cell + CELL_TILE_ID) = 0;
                *(int*)(cell + CELL_LIST_FLAGS) &= 0xffffffdf;
                break;
            case '#':
                *(unsigned char*)(cell + CELL_TILE_ID) = 0x20;
                *(int*)(cell + CELL_LIST_FLAGS) &= 0xffffffdf;
                break;
            case '$':
                ((BodBase*)(cell + CELL_BOD_BASE))
                    ->set_bod_object(ROOT_BOD_OBJECT(slide_slices.storage[0]));
                *(unsigned char*)(cell + CELL_TILE_ID) = 0x17;
                *(int*)(cell + CELL_LIST_FLAGS) |= 0x20;
                break;
            case '&':
                ((BodBase*)(cell + CELL_BOD_BASE))
                    ->set_bod_object(ROOT_BOD_OBJECT(floor_slices.storage[0]));
                *(unsigned char*)(cell + CELL_TILE_ID) = 0x22;
                *(int*)(cell + CELL_LIST_FLAGS) |= 0x20;
                break;
            case '(':
                ++trampoline_counter;
                *(int*)(cell + CELL_LIST_FLAGS) &= 0xffffffdf;
                if (trampoline_counter == 15)
                    trampoline_counter = 0;
                if (trampoline_counter == 8) {
                    ((BodBase*)(cell + CELL_BOD_BASE))
                        ->set_bod_object(ROOT_BOD_OBJECT(trampoline));
                    *(int*)(cell + CELL_LIST_FLAGS) |= 0x20;
                    ((tColour*)(
                        base + sizeof(SubLoc)
                            * (lane + build_row * RUNTIME_LANE_COUNT
                               + CELL_COLOR_INDEX_BIAS)))
                        ->store_color4f(1.0f, 1.0f, 1.0f, 0.99900001f);
                }
                *(unsigned char*)(cell + CELL_TILE_ID) = 0x16;
                break;
            case '+':
                ((BodBase*)(cell + CELL_BOD_BASE))
                    ->set_bod_object(ROOT_BOD_OBJECT(slide_slices.storage[0]));
                *(unsigned char*)(cell + CELL_TILE_ID) = 0x18;
                *(int*)(cell + CELL_LIST_FLAGS) |= 0x20;
                break;
            case ',':
                ((BodBase*)(cell + CELL_BOD_BASE))
                    ->set_bod_object(ROOT_BOD_OBJECT(universe_hole));
                *(unsigned char*)(cell + CELL_TILE_ID) = 0x1c;
                *(int*)(cell + CELL_LIST_FLAGS) |= 0x20;
                break;
            case '-':
                ((BodBase*)(cell + CELL_BOD_BASE))
                    ->set_bod_object(ROOT_BOD_OBJECT(floor_slices.storage[0]));
                *(unsigned char*)(cell + CELL_TILE_ID) = 0x15;
                *(int*)(cell + CELL_LIST_FLAGS) |= 0x20;
                break;
            case '.':
                ((BodBase*)(cell + CELL_BOD_BASE))
                    ->set_bod_object(ROOT_BOD_OBJECT(floor_slices.storage[0]));
                *(unsigned char*)(cell + CELL_TILE_ID) = 1;
                *(int*)(cell + CELL_LIST_FLAGS) |= 0x20;
                break;
            case '0':
                if (level_mode == 1) {
                    *(int*)row_record =
                        (*(int*)row_record & ~SUBROW_FLAG_PARCEL_Z_IS_LOCAL)
                        | SUBROW_FLAG_PARCEL_CANDIDATE;
                    ((SubRow*)row_record)->parcel_set_id = 0;
                    *(float*)(row_record + ROW_PROJECTION_X) = (float)lane - 3.5f;
                    *(int*)(row_record + ROW_PROJECTION_Y) =
                        *(int*)(cell + CELL_POSITION_Y);
                    *(float*)(row_record + ROW_PROJECTION_Z) =
                        (float)build_row + 0.5f;
                    if (base[TRACK_MIRROR_FLAG_OFFSET])
                        *(float*)(row_record + ROW_PROJECTION_X) *= -1.0f;
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
                if ((*(int*)row_record & SUBROW_ATTACHMENT_MASK) == 0) {
                    ((BodBase*)(cell + CELL_BOD_BASE))
                        ->set_bod_object(ROOT_BOD_OBJECT(slide_slices.storage[0]));
                    *(unsigned char*)(cell + CELL_TILE_ID) = 0xf;
                    *(int*)(cell + CELL_LIST_FLAGS) |= 0x20;
                } else {
                    *(int*)(cell + CELL_LIST_FLAGS) &= 0xffffffdf;
                    *(unsigned char*)(cell + CELL_TILE_ID) = 0;
                }
                break;
            case '<':
                ((BodBase*)(cell + CELL_BOD_BASE))
                    ->set_bod_object(ROOT_BOD_OBJECT(ramp_edges[1]));
                *(int*)(cell + CELL_RENDER_ARG_1C) = 0;
                *(int*)(cell + CELL_RENDER_ARG_20) = 0;
                *(unsigned char*)(cell + CELL_TILE_ID) = 6;
                *(int*)(cell + CELL_LIST_FLAGS) |= 0x20;
                break;
            case '=':
            case '|':
                ((BodBase*)(cell + CELL_BOD_BASE))
                    ->set_bod_object(ROOT_BOD_OBJECT(pillars[0]));
                *(unsigned char*)(cell + CELL_TILE_ID) = 0xe;
                *(int*)(cell + CELL_LIST_FLAGS) |= 0x20;
                break;
            case '>':
                if (build_row > 0 && *(unsigned char*)(cell + PREVIOUS_ROW_CELL_TILE_ID) == 3) {
                    ((BodBase*)(cell + CELL_BOD_BASE))
                        ->set_bod_object(ROOT_BOD_OBJECT(ramp_edges[1]));
                    *(int*)(cell + CELL_RENDER_ARG_1C) = 0;
                    *(int*)(cell + CELL_RENDER_ARG_20) = 0;
                    *(unsigned char*)(cell + CELL_TILE_ID) = 9;
                    *(int*)(cell + CELL_LIST_FLAGS) |= 0x20;
                    *(unsigned char*)(cell + PREVIOUS_ROW_CELL_TILE_ID) = 0xc;
                } else {
                    ((BodBase*)(cell + CELL_BOD_BASE))
                        ->set_bod_object(ROOT_BOD_OBJECT(ramp_edges[1]));
                    *(int*)(cell + CELL_RENDER_ARG_1C) = 0;
                    *(int*)(cell + CELL_RENDER_ARG_20) = 0;
                    *(unsigned char*)(cell + CELL_TILE_ID) = 3;
                    *(int*)(cell + CELL_LIST_FLAGS) |= 0x20;
                }
                break;
            case '@':
                *(unsigned char*)(cell + CELL_TILE_ID) = 0;
                *(int*)(cell + CELL_LIST_FLAGS) &= 0xffffffdf;
                switch_track_mirror();
                break;
            case 'F':
                ((BodBase*)(cell + CELL_BOD_BASE))
                    ->set_bod_object(ROOT_BOD_OBJECT(slide_slices.storage[0]));
                *(unsigned char*)(cell + CELL_TILE_ID) = 0x13;
                *(int*)(cell + CELL_LIST_FLAGS) |= 0x20;
                break;
            case 'G':
                ((BodBase*)(cell + CELL_BOD_BASE))
                    ->set_bod_object(ROOT_BOD_OBJECT(slide_slices.storage[0]));
                *(unsigned char*)(cell + CELL_TILE_ID) = 0x11;
                *(int*)(cell + CELL_LIST_FLAGS) |= 0x20;
                break;
            case 'J':
                ((BodBase*)(cell + CELL_BOD_BASE))
                    ->set_bod_object(ROOT_BOD_OBJECT(slide_slices.storage[0]));
                *(unsigned char*)(cell + CELL_TILE_ID) = 0x19;
                *(int*)(cell + CELL_LIST_FLAGS) |= 0x20;
                break;
            case 'M':
                ((BodBase*)(cell + CELL_BOD_BASE))
                    ->set_bod_object(ROOT_BOD_OBJECT(slide_slices.storage[0]));
                *(unsigned char*)(cell + CELL_TILE_ID) = 0x12;
                *(int*)(cell + CELL_LIST_FLAGS) |= 0x20;
                break;
            case 'P':
            case 'p': {
                TrackRowCell* runtime_cell = (TrackRowCell*)(cell + CELL_BOD_BASE);
                if (glyph == 'P')
                    *(unsigned char*)(cell + CELL_TILE_ID) = 0x1e;
                if (glyph == 'p')
                    *(unsigned char*)(cell + CELL_TILE_ID) = 0x1d;

                int template_index =
                    ((SubRow*)row_record)->attachment_template_index;
                Path* template_record;
                if (base[TRACK_MIRROR_FLAG_OFFSET] == 0)
                    template_record = (Path*)(
                        base + PATH_PAIRS_BASE + template_index * sizeof(PathPair));
                else
                    template_record = (Path*)(
                        base + PATH_PAIRS_BASE + PATH_PAIR_SECONDARY_DELTA
                        + template_index * sizeof(PathPair));

                runtime_cell->attachment_template_record = template_record;
                *(int*)(cell + CELL_LIST_FLAGS) &= 0xffffffdf;
                if (attachment_entry_installed == 0) {
                    attachment_entry_installed = 1;
                    ((BodBase*)(cell + CELL_BOD_BASE))->set_bod_object(
                        template_record->object);
                    *(int*)(cell + CELL_LIST_FLAGS) |= 0x20;
                    ((SubRow*)row_record)->attachment_body.set_bod_object(
                        template_record->fringe_mesh_bod.object);
                    *(int*)(row_record + ROW_ATTACHMENT_LIST_FLAGS) |= 0x20;
                    *(int*)(row_record + offsetof(SubRow, installed_heading_delta)) =
                        *(int*)(active_segment + SEGMENT_ANGLE_RADIANS);

                    SubRow* stamped_row = (SubRow*)row_record;
                    int span_index = 0;
                    if (template_record->row_span_count > 0) {
                        do {
                            int stamped_flags = stamped_row->flags;
                            if ((stamped_flags & SUBROW_FLAG_PRIMARY_ATTACHMENT) == 0) {
                                stamped_row->flags =
                                    stamped_flags | SUBROW_FLAG_PRIMARY_ATTACHMENT;
                                stamped_row->primary_attachment_cell = runtime_cell;
                            } else {
                                stamped_row->flags =
                                    stamped_flags | SUBROW_FLAG_SECONDARY_ATTACHMENT;
                                stamped_row->secondary_attachment_cell = runtime_cell;
                            }
                            ++span_index;
                            ++stamped_row;
                        } while (span_index < template_record->row_span_count);
                    }
                }
                break;
            }
            case 'R':
                *(unsigned char*)(cell + CELL_TILE_ID) = 0x23;
                *(int*)(cell + CELL_LIST_FLAGS) &= 0xffffffdf;
                break;
            case '[':
                ((BodBase*)(cell + CELL_BOD_BASE))
                    ->set_bod_object(ROOT_BOD_OBJECT(ramp_edges[0]));
                *(int*)(cell + CELL_RENDER_ARG_1C) = 0;
                *(int*)(cell + CELL_RENDER_ARG_20) = 0;
                *(unsigned char*)(cell + CELL_TILE_ID) = 5;
                *(int*)(cell + CELL_LIST_FLAGS) |= 0x20;
                break;
            case '_':
                ((BodBase*)(cell + CELL_BOD_BASE))
                    ->set_bod_object(ROOT_BOD_OBJECT(slide_slices.storage[0]));
                *(unsigned char*)(cell + CELL_TILE_ID) = 0xf;
                *(int*)(cell + CELL_LIST_FLAGS) |= 0x20;
                break;
            case 'o':
                ((BodBase*)(cell + CELL_BOD_BASE))
                    ->set_bod_object(ROOT_BOD_OBJECT(slide_slices.storage[0]));
                *(unsigned char*)(cell + CELL_TILE_ID) = 0x10;
                *(int*)(cell + CELL_LIST_FLAGS) |= 0x20;
                break;
            case '{':
                if (build_row > 0 && *(unsigned char*)(cell + PREVIOUS_ROW_CELL_TILE_ID) == 3) {
                    ((BodBase*)(cell + CELL_BOD_BASE))
                        ->set_bod_object(ROOT_BOD_OBJECT(ramp_edges[0]));
                    *(int*)(cell + CELL_RENDER_ARG_1C) = 0;
                    *(int*)(cell + CELL_RENDER_ARG_20) = 0;
                    *(unsigned char*)(cell + CELL_TILE_ID) = 8;
                    *(int*)(cell + CELL_LIST_FLAGS) |= 0x20;
                    *(unsigned char*)(cell + PREVIOUS_ROW_CELL_TILE_ID) = 0xb;
                } else {
                    ((BodBase*)(cell + CELL_BOD_BASE))
                        ->set_bod_object(ROOT_BOD_OBJECT(ramp_edges[0]));
                    *(int*)(cell + CELL_RENDER_ARG_1C) = 0;
                    *(int*)(cell + CELL_RENDER_ARG_20) = 0;
                    *(unsigned char*)(cell + CELL_TILE_ID) = 2;
                    *(int*)(cell + CELL_LIST_FLAGS) |= 0x20;
                }
                break;
            case '}':
                if (build_row > 0 && *(unsigned char*)(cell + PREVIOUS_ROW_CELL_TILE_ID) == 3) {
                    ((BodBase*)(cell + CELL_BOD_BASE))
                        ->set_bod_object(ROOT_BOD_OBJECT(ramp_edges[2]));
                    *(int*)(cell + CELL_RENDER_ARG_1C) = 0;
                    *(int*)(cell + CELL_RENDER_ARG_20) = 0;
                    *(unsigned char*)(cell + CELL_TILE_ID) = 0xa;
                    *(int*)(cell + CELL_LIST_FLAGS) |= 0x20;
                    *(unsigned char*)(cell + PREVIOUS_ROW_CELL_TILE_ID) = 0xd;
                } else {
                    ((BodBase*)(cell + CELL_BOD_BASE))
                        ->set_bod_object(ROOT_BOD_OBJECT(ramp_edges[2]));
                    *(int*)(cell + CELL_RENDER_ARG_1C) = 0;
                    *(int*)(cell + CELL_RENDER_ARG_20) = 0;
                    *(unsigned char*)(cell + CELL_TILE_ID) = 4;
                    *(int*)(cell + CELL_LIST_FLAGS) |= 0x20;
                }
                break;
            case 's':
                ((BodBase*)(cell + CELL_BOD_BASE))
                    ->set_bod_object(ROOT_BOD_OBJECT(floor_slices.storage[0]));
                *(unsigned char*)(cell + CELL_TILE_ID) = 0x21;
                *(int*)(cell + CELL_LIST_FLAGS) |= 0x20;
                break;
            default:
                debug_report_stub(
                    "TrackError:%c in Segment %s\n",
                    normalize_segment_glyph_for_track_flags(glyph, build_row, 1),
                    ((SubSegment*)active_segment)->source_name);
                break;
            }

            *(int*)(cell + CELL_POSITION_Z) = 0;
            *(int*)(cell + CELL_POSITION_Y) = 0;
            *(int*)(cell + CELL_POSITION_X) = 0;
            *(int*)(row_record + ROW_ATTACHMENT_POSITION_Z) = 0;
            *(int*)(row_record + ROW_ATTACHMENT_POSITION_Y) = 0;
            *(int*)(row_record + ROW_ATTACHMENT_POSITION_X) = 0;

            unsigned char tile = *(unsigned char*)(cell + CELL_TILE_ID);
            float row_anchor_z;
            if (tile == 0x1d || tile == 0x1e) {
                row_anchor_z = (float)build_row + 0.5f;
                *(int*)(cell + CELL_POSITION_X) = 0;
                *(float*)(cell + CELL_POSITION_Z) = row_anchor_z - 0.5f;
                if ((g_runtime_config.render_flags & RUNTIME_RENDER_TRACK_FRINGE) != 0) {
                    *(int*)(row_record + ROW_ATTACHMENT_POSITION_X) = 0;
                    *(float*)(row_record + ROW_ATTACHMENT_POSITION_Z) =
                        row_anchor_z - 0.5f;

                    tColour skirt_color;
                    tColour* resolved_color =
                        g_game->subgame.get_track_skirt_color(&skirt_color);
                    *(tColour*)(row_record + ROW_ATTACHMENT_COLOR) = *resolved_color;
                    set_object_color(
                        ((SubRow*)row_record)->attachment_body.object,
                        *resolved_color);
                } else {
                    *(int*)(row_record + ROW_ATTACHMENT_LIST_FLAGS) &= 0xffffffdf;
                }
            } else {
                *(float*)(cell + CELL_POSITION_X) = (float)lane - 4.0f + 0.5f;
                *(int*)(cell + CELL_POSITION_Y) = 0;
                tile = *(unsigned char*)(cell + CELL_TILE_ID);
                if (tile == 8 || tile == 9 || tile == 0xa)
                    *(float*)(cell + CELL_POSITION_Y) = 0.5f;
                row_anchor_z = (float)build_row + 0.5f;
                *(float*)(cell + CELL_POSITION_Z) = row_anchor_z;
            }

            if (build_row < 4 && level_mode != 2)
                *(int*)(cell + CELL_POSITION_Y) = *(int*)(
                    *(char**)(base + PATH_36_PRIMARY_SAMPLES)
                    + ATTACHMENT_SAMPLE_POSITION_Y);

            if (*(unsigned char*)(cell + CELL_TILE_ID) == 0x1c)
                *(float*)(cell + CELL_POSITION_Y) -= 0.029999999f;

            tile = *(unsigned char*)(cell + CELL_TILE_ID);
            if (tile == 1 || tile == 0x15 || tile == 0x14 || tile == 0x21
                || tile == 0x22 || tile == 0xf || tile == 0x10 || tile == 0x17
                || tile == 0x18 || tile == 0x19 || tile == 0x1a || tile == 0x1b
                || tile == 0x12 || tile == 0x13 || tile == 0x11) {
                int lane_uv = RUNTIME_LANE_COUNT - lane;
                *(float*)(cell + CELL_RENDER_ARG_1C) = (float)lane_uv * 0.125f;
                int row_uv = build_row % 8;
                *(float*)(cell + CELL_RENDER_ARG_20) = (float)row_uv * 0.125f;
            }

            if (*(unsigned char*)(cell + CELL_TILE_ID) == 0x1f)
                *(float*)(cell + CELL_POSITION_X) *= 1.10000002f;

            if (*(unsigned char*)(cell + CELL_TILE_ID) == 0x16) {
                if (level_mode != 3
                    || (runtime_flags & SUBGAME_RUNTIME_FLAG_ALLOW_FALLING) != 0) {
                    *(float*)(cell + CELL_POSITION_Y) = -3.0f;
                    *(float*)(cell + CELL_POSITION_Z) = row_anchor_z;
                }
            }

            Fringe** subobject_slot =
                &((SubLoc*)(cell + CELL_BOD_BASE))->fringes[0];
            for (int subobject_index = 0;
                 subobject_index < CELL_FRINGE_COUNT;
                 ++subobject_index) {
                Fringe* object = *subobject_slot;
                if (object != 0) {
                    object->position.z = 0.0f;
                    object->position.y = 0.0f;
                    object->position.x = 0.0f;
                    object = *subobject_slot;
                    object->position.x =
                        *(float*)(cell + CELL_POSITION_X);
                    object->position.y =
                        *(float*)(cell + CELL_POSITION_Y);
                    object->position.z =
                        *(float*)(cell + CELL_POSITION_Z);
                }
                ++subobject_slot;
            }
        }
        ++segment_row;
        if (segment_row >= ((SubSegment*)active_segment)->row_count
            && (level_mode != 3 || first_or_last_row == 0)) {
            ++row_event_owner;
        }
    }

    (void)trampoline_counter;
}

#undef ROOT_BOD_OBJECT
