// place_parcels_on_track @ 0x4438e0 (thiscall, ret) — cRSubGame::PlaceParcels()
// Modes 0/7 run the seeded placement: scan every segment's authored parcel
// records + character grid into two candidate banks (digit 1-9 sets, digit-0
// singles), then randomly place sets until 80% of the requirement, digit-0
// singles for the rest, compacting the banks per draw, and finally project
// flagged rows onto their attachments. The catalog set index is reused as the
// post-scan set-placement target, matching the native scalar lifetime.

#include <stddef.h>

#include "track_attachment.h"
#include "transform_matrix.h"
#include "parcel_bucket.h"
#include "rmath_random.h"
#include "subgame_runtime.h"

void report_errorf(const char* format, ...);

// row records at game + 244*row + 0x5ccac8: flags +0x00, payload vec3
// +0x90, count accumulator +0x94, row-center accumulator +0x98, and primary
// attachment cell ptr +0xa4. SubRowFlag owns the packed state transitions.

void cRSubGame::PlaceParcels()
{
    if (level_mode == 1) {
        PlaceParcelsSurvival();
        return;
    }
    if (level_mode != 0 && level_mode != 7)
        return;

    for (int reset = 0;
         reset < (int)sizeof(g_zero_parcel_buckets);
         reset += sizeof(ParcelBucket)) {
        *(int*)((char*)g_zero_parcel_buckets + reset
               + offsetof(ParcelBucket, candidate_count)) = 0;
        *(int*)((char*)g_parcel_set_buckets + reset
               + offsetof(ParcelBucket, candidate_count)) = 0;
    }

    int min_set_sizes[100];
    int zero_entry_count = 0;
    int zero_candidate_total = 0;
    int set_entry_count = 0;
    int set_or_target;
    int last_segment_max_set_size;

    for (int segment = 0; segment < level_definition.segment_count; ++segment) {
        last_segment_max_set_size = 0;
        SubSegmentParcelScanAnchor* record =
            (SubSegmentParcelScanAnchor*)
                &level_definition.segment_slots[segment].row_count;
        min_set_sizes[segment] = 10000;
        for (set_or_target = 0; set_or_target < 10; ++set_or_target) {
            for (int row = 0; row < record->row_count; ++row) {
                AuthoredSegmentRow* authored = &record->rows[row];
                if ((authored->flags & AUTHORED_SEGMENT_ROW_FLAG_PARCEL) != 0
                    && authored->parcel_set_id == set_or_target) {
                    if (set_or_target == 0) {
                        g_zero_parcel_buckets[zero_entry_count].segment_index =
                            segment;
                        g_zero_parcel_buckets[zero_entry_count]
                            .candidates[g_zero_parcel_buckets[zero_entry_count]
                                            .candidate_count]
                            .row = row;
                        g_zero_parcel_buckets[zero_entry_count]
                            .candidates[g_zero_parcel_buckets[zero_entry_count]
                                            .candidate_count]
                            .position = *authored->parcel_position();
                        g_zero_parcel_buckets[zero_entry_count].set_id = 0;
                        ++g_zero_parcel_buckets[zero_entry_count].candidate_count;
                        ++zero_entry_count;
                        ++zero_candidate_total;
                    } else {
                        g_parcel_set_buckets[set_entry_count].segment_index =
                            segment;
                        g_parcel_set_buckets[set_entry_count]
                            .candidates[g_parcel_set_buckets[set_entry_count]
                                            .candidate_count]
                            .row = row;
                        g_parcel_set_buckets[set_entry_count]
                            .candidates[g_parcel_set_buckets[set_entry_count]
                                            .candidate_count]
                            .position = *authored->parcel_position();
                        g_parcel_set_buckets[set_entry_count].set_id =
                            set_or_target;
                        ++g_parcel_set_buckets[set_entry_count].candidate_count;
                    }
                }
                for (int lane = 0; lane < 8; ++lane) {
                    if (record->glyph_rows[lane][row] == set_or_target + 48) {
                        if (set_or_target == 0) {
                            g_zero_parcel_buckets[zero_entry_count].segment_index =
                                segment;
                            g_zero_parcel_buckets[zero_entry_count]
                                .candidates[g_zero_parcel_buckets[zero_entry_count]
                                                .candidate_count]
                                .row = row;
                            g_zero_parcel_buckets[zero_entry_count]
                                .candidates[g_zero_parcel_buckets[zero_entry_count]
                                                .candidate_count]
                                .position = Vector3(
                                    (float)lane - 4.0f + 0.5f, 0.0f, 0.0f);
                            g_zero_parcel_buckets[zero_entry_count].set_id = 0;
                            ++g_zero_parcel_buckets[zero_entry_count].candidate_count;
                            ++zero_entry_count;
                            ++zero_candidate_total;
                        } else {
                            g_parcel_set_buckets[set_entry_count].segment_index =
                                segment;
                            g_parcel_set_buckets[set_entry_count]
                                .candidates[g_parcel_set_buckets[set_entry_count]
                                                .candidate_count]
                                .row = row;
                            g_parcel_set_buckets[set_entry_count]
                                .candidates[g_parcel_set_buckets[set_entry_count]
                                                .candidate_count]
                                .position = Vector3(
                                    (float)lane - 4.0f + 0.5f, 0.0f, 0.0f);
                            g_parcel_set_buckets[set_entry_count].set_id =
                                set_or_target;
                            ++g_parcel_set_buckets[set_entry_count].candidate_count;
                        }
                    }
                }
            }
            if (g_parcel_set_buckets[set_entry_count].candidate_count > 0) {
                int size =
                    g_parcel_set_buckets[set_entry_count].candidate_count;
                if (size
                    < min_set_sizes[g_parcel_set_buckets[set_entry_count]
                                        .segment_index])
                    min_set_sizes[g_parcel_set_buckets[set_entry_count]
                                      .segment_index] = size;
                if (size > last_segment_max_set_size)
                    last_segment_max_set_size = size;
                ++set_entry_count;
            }
        }
    }

    int required = level_definition.parcel_count;
    set_or_target = 80 * required / 100 - last_segment_max_set_size;
    int reachable = zero_candidate_total;
    for (int check = 0; check < level_definition.segment_count; ++check) {
        if (min_set_sizes[check] != 10000)
            reachable += min_set_sizes[check];
    }
    if (reachable < required)
        report_errorf("Parcel Allocation could fail in %s.  Add more parcel Sets",
                      level_definition.level_display_name);
    if (level_definition.parcel_count - set_or_target > zero_candidate_total)
        report_errorf("Parcel Allocation could fail in %s. Add more 0 parcels ",
                      level_definition.level_display_name);

    int placed = 0;
    if (set_or_target > 0 && set_entry_count > 0) {
        do {
            int picked = (int)RAND((float)set_entry_count, "P1");
            placed += g_parcel_set_buckets[picked].candidate_count;
            for (int spot = 0;
                 spot < g_parcel_set_buckets[picked].candidate_count;
                 ++spot) {
                int absolute_row =
                    g_parcel_set_buckets[picked].candidates[spot].row
                    + level_definition
                          .segment_slots[g_parcel_set_buckets[picked]
                                             .segment_index]
                          .row_base;
                if (runtime_rows[absolute_row].flags
                    & SUBROW_FLAG_PARCEL_SPAWN_REQUESTED)
                    report_errorf("Duplicate Parcel Request in %s.",
                                  level_definition.level_display_name);
                runtime_rows[absolute_row].flags |=
                    SUBROW_FLAG_PARCEL_CANDIDATE
                    | SUBROW_FLAG_PARCEL_SPAWN_REQUESTED;
                runtime_rows[absolute_row].parcel_spawn_position =
                    g_parcel_set_buckets[picked].candidates[spot].position;
                runtime_rows[absolute_row].parcel_spawn_position.z =
                    (float)absolute_row
                    + runtime_rows[absolute_row].parcel_spawn_position.z + 0.5f;
                runtime_rows[absolute_row].parcel_spawn_position.y =
                    runtime_rows[absolute_row].parcel_spawn_position.y + 1.0f;
                if (runtime_rows[absolute_row].flags & SUBROW_FLAG_MIRRORED)
                    runtime_rows[absolute_row].parcel_spawn_position.x =
                        runtime_rows[absolute_row].parcel_spawn_position.x * -1.0f;
            }
            int placed_segment =
                g_parcel_set_buckets[picked].segment_index;
            for (int scan = 0; scan < set_entry_count; ++scan) {
                if (g_parcel_set_buckets[scan].segment_index == placed_segment) {
                    for (int move = scan; move < set_entry_count - 1; ++move) {
                        for (int copy = 0;
                             copy
                             < g_parcel_set_buckets[move + 1].candidate_count;
                             ++copy)
                            g_parcel_set_buckets[move].candidates[copy] =
                                g_parcel_set_buckets[move + 1].candidates[copy];
                        g_parcel_set_buckets[move].candidate_count =
                            g_parcel_set_buckets[move + 1].candidate_count;
                        g_parcel_set_buckets[move].segment_index =
                            g_parcel_set_buckets[move + 1].segment_index;
                        g_parcel_set_buckets[move].set_id =
                            g_parcel_set_buckets[move + 1].set_id;
                    }
                    --set_entry_count;
                    --scan;
                }
            }
        } while (placed < set_or_target);
    }

    if (placed < level_definition.parcel_count && zero_entry_count > 0) {
        do {
            int picked = (int)RAND((float)zero_entry_count, "P2");
            placed += g_zero_parcel_buckets[picked].candidate_count;
            int absolute_row =
                g_zero_parcel_buckets[picked].candidates[0].row
                + level_definition
                      .segment_slots[g_zero_parcel_buckets[picked].segment_index]
                      .row_base;
            if (runtime_rows[absolute_row].flags
                & SUBROW_FLAG_PARCEL_SPAWN_REQUESTED)
                report_errorf("Duplicate Parcel Request in %s.",
                              level_definition.level_display_name);
            runtime_rows[absolute_row].flags |=
                SUBROW_FLAG_PARCEL_CANDIDATE
                | SUBROW_FLAG_PARCEL_SPAWN_REQUESTED;
            runtime_rows[absolute_row].parcel_spawn_position =
                g_zero_parcel_buckets[picked].candidates[0].position;
            runtime_rows[absolute_row].parcel_spawn_position.z =
                (float)absolute_row
                + runtime_rows[absolute_row].parcel_spawn_position.z + 0.5f;
            runtime_rows[absolute_row].parcel_spawn_position.y =
                runtime_rows[absolute_row].parcel_spawn_position.y + 1.0f;
            if (runtime_rows[absolute_row].flags & SUBROW_FLAG_MIRRORED)
                runtime_rows[absolute_row].parcel_spawn_position.x =
                    runtime_rows[absolute_row].parcel_spawn_position.x * -1.0f;
            for (int move = picked; move < zero_entry_count - 1; ++move) {
                g_zero_parcel_buckets[move].candidates[0] =
                    g_zero_parcel_buckets[move + 1].candidates[0];
                g_zero_parcel_buckets[move].candidate_count =
                    g_zero_parcel_buckets[move + 1].candidate_count;
                g_zero_parcel_buckets[move].segment_index =
                    g_zero_parcel_buckets[move + 1].segment_index;
                g_zero_parcel_buckets[move].set_id = 0;
            }
            --zero_entry_count;
        } while (placed < level_definition.parcel_count);
    }

    if (placed != level_definition.parcel_count) {
        report_errorf("Did not generate required Parcels(%i) in %s",
                      level_definition.parcel_count,
                      level_definition.level_display_name);
        if (level_definition.parcel_quota)
            level_definition.parcel_quota =
                placed * level_definition.parcel_count / level_definition.parcel_quota;
    }
    level_definition.parcel_count = placed;

    SubRow* row_record = runtime_rows;
    for (int row = 0; row < runtime_row_count; ++row, ++row_record) {
        if ((row_record->flags & SUBROW_FLAG_PARCEL_CANDIDATE) != 0
            && (row_record->flags & SUBROW_FLAG_PRIMARY_ATTACHMENT) != 0) {
            cRSubLoc* cell = row_record->primary_attachment_cell;
            int node =
                (int)row_record->parcel_spawn_position.z
                - cell->Yi();
            if (node < 0)
                node = 0;
            cRSubLoc* live_cell = row_record->primary_attachment_cell;
            Path* template_record = live_cell->attachment_template_record;
            if (template_record->kind == PATH_TEMPLATE_KIND_NONLINEAR_42) {
                TransformMatrix transform;
                float out_angle;
                template_record->compute_kind42_attachment_transform(
                    template_record->primary_samples[node].special_scalar,
                    row_record->parcel_spawn_position.x,
                    row_record->parcel_spawn_position.y,
                    &transform,
                    &out_angle);
                row_record->parcel_spawn_position.x = transform.position.x;
                row_record->parcel_spawn_position.y = transform.position.y;
            } else {
                int row_index = live_cell->Yi();
                live_cell->attachment_template_record->GetPos(
                    row_record->parcel_spawn_position, node, row_index,
                    row_record->parcel_spawn_position);
            }
        }
    }
}
