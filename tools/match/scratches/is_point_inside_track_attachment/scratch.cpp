// is_point_inside_track_attachment @ 0x42ca90 (thiscall, ret 0x1c)

#include "track_attachment.h"

inline Vector3 operator-(const Vector3& lhs, const Vector3& rhs)
{
    return Vector3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

bool Path::is_point_inside_track_attachment(
    Vector3 probe, Vector3 swept_motion, TrackRowCell* cell)
{
    Vector3 local;
    Vector3 sample_origin;
    Vector3 anchor = cell->anchor_position;
    float anchor_x = anchor.x;
    float anchor_y = anchor.y;
    float anchor_z = anchor.z;

    int idx = segment_count - 1;
    while (idx >= 0) {
        sample_origin.x = anchor_x + secondary_samples[idx].transform.position.x;
        sample_origin.y = anchor_y + secondary_samples[idx].transform.position.y;
        TransformMatrix* inverse_matrix = &secondary_samples[idx].inverse_matrix;
        sample_origin.z = anchor_z + secondary_samples[idx].transform.position.z;
        local = probe - sample_origin;
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
