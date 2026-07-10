// place_challenge_parcels_on_track @ 0x444240 (thiscall, ret)

#include "track_attachment.h"
#include "transform_matrix.h"
#include "parcel_bucket.h"
#include "subgame_runtime.h"

double random_float_below(float upper_bound, const char* tag);
int debug_report_stub(char* format, ...);

extern char g_zero_parcel_bucket_count_lane_end; // 0x643390
extern int g_challenge_parcel_rows[]; // 0x6447e8

int SubgameRuntime::place_challenge_parcels_on_track()
{
    float source_scaled = (float)completion_bonus_x_source * 50.0f;
    source_scaled = source_scaled * 0.00999999978f;
    int required = (int)(source_scaled + challenge_difficulty_scalar * 50.0f) + 1;
    level_definition.parcel_count = required;
    level_definition.parcel_quota = required;

    int* bucket_count = &g_zero_parcel_buckets[0].candidate_count;
    while ((int)bucket_count < (int)&g_zero_parcel_bucket_count_lane_end) {
        *bucket_count = 0;
        bucket_count = (int*)((char*)bucket_count + 0x20c);
    }

    int candidate_count = 0;
    int row_index = 0;
    int remaining = 0;
    if (runtime_row_count > 0) {
        TrackAttachmentRuntimeRow* row = runtime_rows;
        do {
            if ((row->flags & 1) != 0 && row->parcel_set_id == 0) {
                g_challenge_parcel_rows[candidate_count] = row_index;
                ++candidate_count;
            }
            ++row_index;
            ++row;
        } while (row_index < runtime_row_count);
        remaining = candidate_count;
    }

    int placed = 0;
    if (level_definition.parcel_count > 0) {
        int last_index = candidate_count - 1;
        while (remaining > 0) {
            int picked = (int)random_float_below((float)remaining, "P3");
            int selected_row = g_challenge_parcel_rows[picked];
            int* selected_slot = &g_challenge_parcel_rows[picked];
            ++placed;

            TrackAttachmentRuntimeRow* runtime_row = &runtime_rows[selected_row];
            runtime_row->flags |= 0x11;
            runtime_row->projection_payload.y += 1.0f;
            if ((runtime_row->flags & 0x20) != 0) {
                runtime_row->projection_payload.x *= -1.0f;
            }
            if ((runtime_row->flags & 0x4000) != 0) {
                runtime_row->projection_payload.z =
                    (float)selected_row + runtime_row->projection_payload.z + 0.5f;
            }

            if (picked < last_index) {
                int move_count = last_index - picked;
                do {
                    *selected_slot = selected_slot[1];
                    ++selected_slot;
                    --move_count;
                } while (move_count != 0);
            }

            --remaining;
            --last_index;
            if (placed >= level_definition.parcel_count) {
                break;
            }
        }
    }

    level_definition.parcel_count = placed;
    debug_report_stub("Challenge parcel count %i\n", placed);

    int result = runtime_row_count;
    int scan = 0;
    if (result > 0) {
        TrackAttachmentRuntimeRow* row = runtime_rows;
        do {
            if ((row->flags & 1) != 0 && (row->flags & 0x40) != 0) {
                TrackRowCell* cell = row->primary_attachment_cell;
                int node =
                    (int)row->projection_payload.z - cell->get_track_cell_row_index();
                if (node < 0) {
                    node = 0;
                }

                AttachmentPathTemplate* template_record =
                    row->primary_attachment_cell->attachment_template_record;
                if (template_record->kind == 42) {
                    TransformMatrix transform;
                    float out_angle;
                    template_record->compute_kind42_attachment_transform(
                        template_record->primary_samples[node].special_scalar,
                        row->projection_payload.x,
                        row->projection_payload.y,
                        &transform,
                        &out_angle);
                    row->projection_payload.x = transform.position.x;
                    row->projection_payload.y = transform.position.y;
                } else {
                    int row_origin =
                        row->primary_attachment_cell->get_track_cell_row_index();
                    row->primary_attachment_cell->attachment_template_record
                        ->get_path_position_at_node(
                            row->projection_payload,
                            node,
                            row_origin,
                            row->projection_payload);
                }
            }
            ++scan;
            ++row;
            result = scan;
        } while (scan < runtime_row_count);
    }

    return result;
}
