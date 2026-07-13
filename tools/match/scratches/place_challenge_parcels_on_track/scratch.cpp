// place_challenge_parcels_on_track @ 0x444240 (thiscall, ret)

#include "track_attachment.h"
#include "transform_matrix.h"
#include "parcel_bucket.h"
#include "subgame_runtime.h"

double random_float_below(float upper_bound, const char* tag);
int debug_report_stub(char* format, ...);

extern char g_zero_parcel_bucket_count_lane_end; // 0x643390

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
    if (runtime_row_count > 0) {
        TrackAttachmentRuntimeRow* row = runtime_rows;
        do {
            if ((row->flags & 1) != 0 && row->parcel_set_id == 0) {
                g_parcel_group_survival_0[candidate_count] = row_index;
                ++candidate_count;
            }
            ++row_index;
            ++row;
        } while (row_index < runtime_row_count);
    }

    int placed = 0;
    if (level_definition.parcel_count > 0) {
        int last_index = candidate_count - 1;
        while (placed < level_definition.parcel_count) {
            if (candidate_count <= 0) {
                break;
            }
            int picked = (int)random_float_below((float)candidate_count, "P3");
            int selected_row = g_parcel_group_survival_0[picked];
            ++placed;

            runtime_rows[selected_row].flags |= 0x11;
            runtime_rows[selected_row].projection_payload.y += 1.0f;
            if ((runtime_rows[selected_row].flags & 0x20) != 0) {
                runtime_rows[selected_row].projection_payload.x *= -1.0f;
            }
            if ((runtime_rows[selected_row].flags & 0x4000) != 0) {
                runtime_rows[selected_row].projection_payload.z =
                    (float)selected_row
                    + runtime_rows[selected_row].projection_payload.z
                    + 0.5f;
            }

            for (int move_index = picked; move_index < last_index; ++move_index) {
                g_parcel_group_survival_0[move_index] =
                    g_parcel_group_survival_0[move_index + 1];
            }

            --candidate_count;
            --last_index;
        }
    }

    level_definition.parcel_count = placed;
    debug_report_stub("Challenge parcel count %i\n", placed);

    int result = runtime_row_count;
    int scan = 0;
    if (result > 0) {
        do {
            if ((runtime_rows[scan].flags & 1) != 0
                && (runtime_rows[scan].flags & 0x40) != 0) {
                TrackRowCell* cell = runtime_rows[scan].primary_attachment_cell;
                int source_row = cell->get_track_cell_row_index();
                int node =
                    (int)runtime_rows[scan].projection_payload.z
                    - source_row;
                if (node < 0) {
                    node = 0;
                }

                Path* template_record =
                    runtime_rows[scan]
                        .primary_attachment_cell->attachment_template_record;
                if (template_record->kind == 42) {
                    TransformMatrix transform;
                    float out_angle;
                    template_record->compute_kind42_attachment_transform(
                        template_record->primary_samples[node].special_scalar,
                        runtime_rows[scan].projection_payload.x,
                        runtime_rows[scan].projection_payload.y,
                        &transform,
                        &out_angle);
                    runtime_rows[scan].projection_payload.x = transform.position.x;
                    runtime_rows[scan].projection_payload.y = transform.position.y;
                } else {
                    runtime_rows[scan]
                        .primary_attachment_cell->attachment_template_record
                        ->get_path_position_at_node(
                            runtime_rows[scan].projection_payload,
                            node,
                            cell->get_track_cell_row_index(),
                            runtime_rows[scan].projection_payload);
                }
            }
            ++scan;
            result = scan;
        } while (scan < runtime_row_count);
    }

    return result;
}
