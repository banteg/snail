// place_parcels_on_track @ 0x4438e0 (thiscall, ret) — cRSubGame::PlaceParcels()
// Modes 0/7 run the seeded placement: scan every segment's authored parcel
// records + character grid into two candidate banks (digit 1-9 sets, digit-0
// singles), then randomly place sets until 80% of the requirement, digit-0
// singles for the rest, compacting the banks per draw, and finally project
// flagged rows onto their attachments.

#include "track_attachment.h"
#include "transform_matrix.h"

double random_float_below(float upper_bound, const char* tag);
void report_errorf(const char* format, ...);
void compute_kind42_attachment_transform(float scale, float x, float y,
                                         TransformMatrix* transform, float* out_angle);

struct ParcelCandidate { // 16 bytes
    int row;             // +0x00 row within the segment
    Vector3 position;    // +0x04
};

struct CandidateEntry {              // 524 bytes (131 dwords)
    ParcelCandidate candidates[32];  // +0x000
    int candidate_count;             // +0x200
    int set_id;                      // +0x204
    int segment_index;               // +0x208
};

extern CandidateEntry g_parcel_set_buckets[2048];  // 0x6487e8
extern CandidateEntry g_zero_parcel_buckets[2048]; // 0x53d190

struct AuthoredParcelRecord { // segment +0x814, one per row, 56 bytes
    int flags;                // bit 1 = flagged parcel
    int set_id;
    Vector3 position;
    char unknown_14[0x38 - 0x14];
};

struct SegmentRecord { // game+0xa878, stride 16928
    int row_base;      // +0x00 absolute row of the segment start
    int row_count;     // +0x04
    char unknown_08[0x14 - 0x08];
    char grid[8][256]; // +0x14 lane-major authored characters
    // +0x814: AuthoredParcelRecord rows[], 56-byte stride
};

struct Game {
    char unknown_00[0x40];
    int level_mode; // +0x40
    char unknown_44[0x54 - 0x44];
    int runtime_row_count; // +0x54
    char unknown_58[0xa874 - 0x58];
    int level_segment_count; // +0xa874
    SegmentRecord segments[1]; // +0xa878 stride 16928

    int place_parcels_on_track();
    int place_challenge_parcels_on_track();
};

// row records at game + 244*row + 0x5ccac8: flags +0x00 (0x01 live, 0x10
// parcel occupied, 0x11 written on claim, 0x20 mirror lateral, 0x40
// attachment row), payload vec3 +0x90, count accumulator +0x94, row-center
// accumulator +0x98, attachment cell ptr +0xa4.

int Game::place_parcels_on_track()
{
    if (level_mode == 1)
        return place_challenge_parcels_on_track();
    if (level_mode != 0 && level_mode != 7)
        return level_mode;

    for (int reset = 0; reset < 0x106000; reset += 0x20c) {
        *(int*)((char*)g_zero_parcel_buckets + reset + 0x200) = 0;
        *(int*)((char*)g_parcel_set_buckets + reset + 0x200) = 0;
    }

    int min_set_sizes[100];
    int zero_entry_count = 0;
    int zero_candidate_total = 0;
    int set_entry_count = 0;
    int max_set_size = 0;

    for (int segment = 0; segment < level_segment_count; ++segment) {
        SegmentRecord* record = (SegmentRecord*)((char*)segments + 16928 * segment);
        min_set_sizes[segment] = 10000;
        for (int set = 0; set < 10; ++set) {
            CandidateEntry* set_entry = &g_parcel_set_buckets[set_entry_count];
            for (int row = 0; row < record->row_count; ++row) {
                AuthoredParcelRecord* authored =
                    (AuthoredParcelRecord*)((char*)record + 0x814 + 56 * row);
                if ((authored->flags & 1) != 0 && authored->set_id == set) {
                    if (set) {
                        set_entry->segment_index = segment;
                        set_entry->candidates[set_entry->candidate_count].row = row;
                        set_entry->candidates[set_entry->candidate_count].position =
                            authored->position;
                        set_entry->set_id = set;
                        ++set_entry->candidate_count;
                    } else {
                        CandidateEntry* zero_entry =
                            &g_zero_parcel_buckets[zero_entry_count];
                        zero_entry->segment_index = segment;
                        zero_entry->candidates[zero_entry->candidate_count].row = row;
                        zero_entry->candidates[zero_entry->candidate_count].position =
                            authored->position;
                        zero_entry->set_id = 0;
                        ++zero_entry_count;
                        ++zero_entry->candidate_count;
                        ++zero_candidate_total;
                    }
                }
                for (int lane = 0; lane < 8; ++lane) {
                    if (record->grid[lane][row] == set + 48) {
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
                            CandidateEntry* zero_entry =
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

    int required = *(int*)((char*)this + 0x1b01e0);
    int set_target = 80 * required / 100 - max_set_size;
    int reachable = zero_candidate_total;
    for (int check = 0; check < level_segment_count; ++check) {
        if (min_set_sizes[check] != 10000)
            reachable += min_set_sizes[check];
    }
    if (reachable < required)
        report_errorf("Parcel Allocation could fail in %s.  Add more parcel Sets",
                      (char*)this + 0x1b0150);
    if (*(int*)((char*)this + 0x1b01e0) - set_target > zero_candidate_total)
        report_errorf("Parcel Allocation could fail in %s. Add more 0 parcels ",
                      (char*)this + 0x1b0150);

    int placed = 0;
    if (set_target > 0) {
        while (set_entry_count > 0) {
            int picked = (int)random_float_below((float)set_entry_count, "P1");
            CandidateEntry* entry = &g_parcel_set_buckets[picked];
            placed += entry->candidate_count;
            for (int spot = 0; spot < entry->candidate_count; ++spot) {
                int absolute_row =
                    entry->candidates[spot].row
                    + ((SegmentRecord*)((char*)segments + 16928 * entry->segment_index))
                          ->row_base;
                TrackAttachmentRuntimeRow* row_record =
                    (TrackAttachmentRuntimeRow*)((char*)this + 244 * absolute_row + 0x5ccac8);
                if (row_record->flags & 0x10)
                    report_errorf("Duplicate Parcel Request in %s.",
                                  (char*)this + 0x1b0150);
                row_record->flags |= 0x11;
                row_record->projection_payload = entry->candidates[spot].position;
                row_record->projection_payload.z =
                    (float)((double)absolute_row + row_record->projection_payload.z + 0.5);
                row_record->projection_payload.y = row_record->projection_payload.y + 1.0f;
                if (row_record->flags & 0x20)
                    row_record->projection_payload.x = row_record->projection_payload.x * -1.0f;
            }
            int placed_segment = entry->segment_index;
            for (int scan = 0; scan < set_entry_count; ++scan) {
                if (g_parcel_set_buckets[scan].segment_index == placed_segment) {
                    for (int move = scan; move < set_entry_count - 1; ++move) {
                        CandidateEntry* destination = &g_parcel_set_buckets[move];
                        CandidateEntry* source = &g_parcel_set_buckets[move + 1];
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

    if (placed < *(int*)((char*)this + 0x1b01e0)) {
        while (zero_entry_count > 0) {
            int picked = (int)random_float_below((float)zero_entry_count, "P2");
            CandidateEntry* entry = &g_zero_parcel_buckets[picked];
            placed += entry->candidate_count;
            int absolute_row =
                entry->candidates[0].row
                + ((SegmentRecord*)((char*)segments + 16928 * entry->segment_index))->row_base;
            TrackAttachmentRuntimeRow* row_record =
                (TrackAttachmentRuntimeRow*)((char*)this + 244 * absolute_row + 0x5ccac8);
            if (row_record->flags & 0x10)
                report_errorf("Duplicate Parcel Request in %s.", (char*)this + 0x1b0150);
            row_record->flags |= 0x11;
            row_record->projection_payload = entry->candidates[0].position;
            row_record->projection_payload.z =
                (float)((double)absolute_row + row_record->projection_payload.z + 0.5);
            row_record->projection_payload.y = row_record->projection_payload.y + 1.0f;
            if (row_record->flags & 0x20)
                row_record->projection_payload.x = row_record->projection_payload.x * -1.0f;
            for (int move = picked; move < zero_entry_count - 1; ++move) {
                CandidateEntry* destination = &g_zero_parcel_buckets[move];
                CandidateEntry* source = &g_zero_parcel_buckets[move + 1];
                destination->candidates[0] = source->candidates[0];
                destination->candidate_count = source->candidate_count;
                destination->set_id = 0;
                destination->segment_index = source->segment_index;
            }
            --zero_entry_count;
            if (placed >= *(int*)((char*)this + 0x1b01e0))
                break;
        }
    }

    if (placed != *(int*)((char*)this + 0x1b01e0)) {
        report_errorf("Did not generate required Parcels(%i) in %s",
                      *(int*)((char*)this + 0x1b01e0), (char*)this + 0x1b0150);
        if (*(int*)((char*)this + 0x1b01e8))
            *(int*)((char*)this + 0x1b01e8) =
                placed * *(int*)((char*)this + 0x1b01e0) / *(int*)((char*)this + 0x1b01e8);
    }
    *(int*)((char*)this + 0x1b01e0) = placed;

    TransformMatrix transform;
    float out_angle;
    int result = runtime_row_count;
    for (int row = 0; row < runtime_row_count; ++row) {
        TrackAttachmentRuntimeRow* row_record =
            (TrackAttachmentRuntimeRow*)((char*)this + 244 * row + 0x5ccac8);
        if ((row_record->flags & 1) != 0 && (row_record->flags & 0x40) != 0) {
            TrackRowCell* cell = row_record->primary_attachment_cell;
            int node =
                (int)row_record->projection_payload.z - cell->get_track_cell_row_index();
            if (node < 0)
                node = 0;
            TrackRowCell* live_cell = row_record->primary_attachment_cell;
            AttachmentPathTemplate* template_record = live_cell->attachment_template_record;
            if (template_record->kind == 42) {
                compute_kind42_attachment_transform(
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
                    &row_record->projection_payload, node, row_index,
                    (float*)&row_record->projection_payload);
            }
        }
        result = row + 1;
    }
    return result;
}
