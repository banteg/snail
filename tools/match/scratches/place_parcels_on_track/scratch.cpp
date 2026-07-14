// place_parcels_on_track @ 0x4438e0 (thiscall, ret) — cRSubGame::PlaceParcels()
// Modes 0/7 run the seeded placement: scan every segment's authored parcel
// records + character grid into two candidate banks (digit 1-9 sets, digit-0
// singles), then randomly place sets until 80% of the requirement, digit-0
// singles for the rest, compacting the banks per draw, and finally project
// flagged rows onto their attachments.

#include <stddef.h>

#include "track_attachment.h"
#include "transform_matrix.h"
#include "parcel_bucket.h"
#include "subgame_runtime.h"

double random_float_below(float upper_bound, const char* tag);
void report_errorf(const char* format, ...);

// row records at game + 244*row + 0x5ccac8: flags +0x00 (0x01 live, 0x10
// parcel occupied, 0x11 written on claim, 0x20 mirror lateral, 0x40
// attachment row), payload vec3 +0x90, count accumulator +0x94, row-center
// accumulator +0x98, attachment cell ptr +0xa4.

int SubgameRuntime::place_parcels_on_track()
{
    if (level_mode == 1)
        return place_challenge_parcels_on_track();
    if (level_mode != 0 && level_mode != 7)
        return level_mode;

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
    int max_set_size = 0;

    for (int segment = 0; segment < level_definition.segment_count; ++segment) {
        SubSegment* record = &level_definition.segment_slots[segment];
        min_set_sizes[segment] = 10000;
        for (int set = 0; set < 10; ++set) {
            ParcelBucket* set_entry = &g_parcel_set_buckets[set_entry_count];
            for (int row = 0; row < record->row_count; ++row) {
                AuthoredSegmentRow* authored = &record->rows[row];
                if ((authored->flags & 1) != 0 && authored->parcel_set_id == set) {
                    if (set) {
                        set_entry->segment_index = segment;
                        set_entry->candidates[set_entry->candidate_count].row = row;
                        set_entry->candidates[set_entry->candidate_count].position =
                            *authored->parcel_position();
                        set_entry->set_id = set;
                        ++set_entry->candidate_count;
                    } else {
                        ParcelBucket* zero_entry =
                            &g_zero_parcel_buckets[zero_entry_count];
                        zero_entry->segment_index = segment;
                        zero_entry->candidates[zero_entry->candidate_count].row = row;
                        zero_entry->candidates[zero_entry->candidate_count].position =
                            *authored->parcel_position();
                        zero_entry->set_id = 0;
                        ++zero_entry_count;
                        ++zero_entry->candidate_count;
                        ++zero_candidate_total;
                    }
                }
                for (int lane = 0; lane < 8; ++lane) {
                    if (record->glyph_rows[lane][row] == set + 48) {
                        if (set) {
                            set_entry->segment_index = segment;
                            set_entry->candidates[set_entry->candidate_count].row = row;
                            set_entry->candidates[set_entry->candidate_count].position.x =
                                (float)lane - 4.0f + 0.5f;
                            set_entry->candidates[set_entry->candidate_count].position.y = 0;
                            set_entry->candidates[set_entry->candidate_count].position.z = 0;
                            set_entry->set_id = set;
                            ++set_entry->candidate_count;
                        } else {
                            ParcelBucket* zero_entry =
                                &g_zero_parcel_buckets[zero_entry_count];
                            zero_entry->segment_index = segment;
                            zero_entry->candidates[zero_entry->candidate_count].row = row;
                            zero_entry->candidates[zero_entry->candidate_count].position.x =
                                (float)lane - 4.0f + 0.5f;
                            zero_entry->candidates[zero_entry->candidate_count].position.y = 0;
                            zero_entry->candidates[zero_entry->candidate_count].position.z = 0;
                            zero_entry->set_id = 0;
                            ++zero_entry_count;
                            ++zero_entry->candidate_count;
                            ++zero_candidate_total;
                        }
                    }
                }
            }
            if (set_entry->candidate_count > 0) {
                int size = set_entry->candidate_count;
                if (size < min_set_sizes[set_entry->segment_index])
                    min_set_sizes[set_entry->segment_index] = size;
                if (size > max_set_size)
                    max_set_size = size;
                ++set_entry_count;
            }
        }
    }

    int required = level_definition.parcel_count;
    int set_target = 80 * required / 100 - max_set_size;
    int reachable = zero_candidate_total;
    for (int check = 0; check < level_definition.segment_count; ++check) {
        if (min_set_sizes[check] != 10000)
            reachable += min_set_sizes[check];
    }
    if (reachable < required)
        report_errorf("Parcel Allocation could fail in %s.  Add more parcel Sets",
                      level_definition.level_display_name);
    if (level_definition.parcel_count - set_target > zero_candidate_total)
        report_errorf("Parcel Allocation could fail in %s. Add more 0 parcels ",
                      level_definition.level_display_name);

    int placed = 0;
    if (set_target > 0) {
        while (set_entry_count > 0) {
            int picked = (int)random_float_below((float)set_entry_count, "P1");
            ParcelBucket* entry = &g_parcel_set_buckets[picked];
            placed += entry->candidate_count;
            for (int spot = 0; spot < entry->candidate_count; ++spot) {
                int absolute_row =
                    entry->candidates[spot].row
                    + level_definition.segment_slots[entry->segment_index].row_base;
                if (runtime_rows[absolute_row].flags & 0x10)
                    report_errorf("Duplicate Parcel Request in %s.",
                                  level_definition.level_display_name);
                runtime_rows[absolute_row].flags |= 0x11;
                runtime_rows[absolute_row].projection_payload = entry->candidates[spot].position;
                runtime_rows[absolute_row].projection_payload.z =
                    (float)((double)absolute_row
                            + runtime_rows[absolute_row].projection_payload.z + 0.5);
                runtime_rows[absolute_row].projection_payload.y =
                    runtime_rows[absolute_row].projection_payload.y + 1.0f;
                if (runtime_rows[absolute_row].flags & 0x20)
                    runtime_rows[absolute_row].projection_payload.x =
                        runtime_rows[absolute_row].projection_payload.x * -1.0f;
            }
            int placed_segment = entry->segment_index;
            for (int scan = 0; scan < set_entry_count; ++scan) {
                if (g_parcel_set_buckets[scan].segment_index == placed_segment) {
                    for (int move = scan; move < set_entry_count - 1; ++move) {
                        ParcelBucket* destination = &g_parcel_set_buckets[move];
                        ParcelBucket* source = &g_parcel_set_buckets[move + 1];
                        for (int copy = 0; copy < source->candidate_count; ++copy)
                            destination->candidates[copy] = source->candidates[copy];
                        destination->candidate_count = source->candidate_count;
                        destination->segment_index = source->segment_index;
                        destination->set_id = source->set_id;
                    }
                    --set_entry_count;
                    --scan;
                }
            }
            if (placed >= set_target)
                break;
        }
    }

    if (placed < level_definition.parcel_count) {
        while (zero_entry_count > 0) {
            int picked = (int)random_float_below((float)zero_entry_count, "P2");
            ParcelBucket* entry = &g_zero_parcel_buckets[picked];
            placed += entry->candidate_count;
            int absolute_row =
                entry->candidates[0].row
                + level_definition.segment_slots[entry->segment_index].row_base;
            if (runtime_rows[absolute_row].flags & 0x10)
                report_errorf("Duplicate Parcel Request in %s.",
                              level_definition.level_display_name);
            runtime_rows[absolute_row].flags |= 0x11;
            runtime_rows[absolute_row].projection_payload = entry->candidates[0].position;
            runtime_rows[absolute_row].projection_payload.z =
                (float)((double)absolute_row
                        + runtime_rows[absolute_row].projection_payload.z + 0.5);
            runtime_rows[absolute_row].projection_payload.y =
                runtime_rows[absolute_row].projection_payload.y + 1.0f;
            if (runtime_rows[absolute_row].flags & 0x20)
                runtime_rows[absolute_row].projection_payload.x =
                    runtime_rows[absolute_row].projection_payload.x * -1.0f;
            for (int move = picked; move < zero_entry_count - 1; ++move) {
                ParcelBucket* destination = &g_zero_parcel_buckets[move];
                ParcelBucket* source = &g_zero_parcel_buckets[move + 1];
                destination->candidates[0] = source->candidates[0];
                destination->candidate_count = source->candidate_count;
                destination->set_id = 0;
                destination->segment_index = source->segment_index;
            }
            --zero_entry_count;
            if (placed >= level_definition.parcel_count)
                break;
        }
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

    TransformMatrix transform;
    float out_angle;
    int result = runtime_row_count;
    SubRow* row_record = runtime_rows;
    for (int row = 0; row < runtime_row_count; ++row, ++row_record) {
        if ((row_record->flags & 1) != 0 && (row_record->flags & 0x40) != 0) {
            TrackRowCell* cell = row_record->primary_attachment_cell;
            int node =
                (int)row_record->projection_payload.z - cell->get_track_cell_row_index();
            if (node < 0)
                node = 0;
            TrackRowCell* live_cell = row_record->primary_attachment_cell;
            Path* template_record = live_cell->attachment_template_record;
            if (template_record->kind == 42) {
                template_record->compute_kind42_attachment_transform(
                    template_record->primary_samples[node].special_scalar,
                    row_record->projection_payload.x,
                    row_record->projection_payload.y,
                    &transform,
                    &out_angle);
                row_record->projection_payload.x = transform.position.x;
                row_record->projection_payload.y = transform.position.y;
            } else {
                int row_index = live_cell->get_track_cell_row_index();
                live_cell->attachment_template_record->get_path_position_at_node(
                    row_record->projection_payload, node, row_index,
                    row_record->projection_payload);
            }
        }
        result = row + 1;
    }
    return result;
}
