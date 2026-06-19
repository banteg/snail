// is_point_inside_track_attachment @ 0x42ca90 (thiscall, ret 0x1c)

#include "track_attachment.h"

bool AttachmentPathTemplate::is_point_inside_track_attachment(
    Vector3 probe, Vector3 swept_motion, TrackRowCell* cell)
{
    Vector3 local;
    Vector3 sample_origin;
    Vector3 anchor = cell->anchor_position;
    float anchor_x = anchor.x;
    float anchor_y = anchor.y;
    float anchor_z = anchor.z;
    float delta_x;
    float delta_y;
    float delta_z;
    float origin_y;
    float origin_z;

    int idx = segment_count - 1;
    while (idx >= 0) {
        sample_origin.x = anchor_x + secondary_samples[idx].transform.position.x;
        sample_origin.y = anchor_y + secondary_samples[idx].transform.position.y;
        float* inverse_matrix = secondary_samples[idx].inverse_matrix;
        sample_origin.z = anchor_z + secondary_samples[idx].transform.position.z;
        origin_y = sample_origin.y;
        origin_z = sample_origin.z;
        delta_x = probe.x - sample_origin.x;
        delta_y = probe.y;
        delta_y -= origin_y;
        delta_z = probe.z;
        delta_z -= origin_z;
        local = Vector3(delta_x, delta_y, delta_z);
        local.rotate_vector_by_matrix(inverse_matrix);

        if ((float)(width_cells / -2) - 0.300000012f < local.x
            && (float)(width_cells / 2) + 0.300000012f > local.x
            && local.y >= -0.300000012f
            && local.y < 0.300000012f
            && local.z > 0.0f
            && local.z < secondary_samples[idx].delta_length)
        {
            return true;
        }
        idx--;
    }

    return false;
}
