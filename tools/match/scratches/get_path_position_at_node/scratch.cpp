// get_path_position_at_node @ 0x42b9c0 (thiscall, ret 0x10)

#include "track_attachment.h"

inline Vector3 operator*(float scale, const Vector3& vector)
{
    return Vector3(scale * vector.x, scale * vector.y, scale * vector.z);
}

inline Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
{
    return Vector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

int Path::get_path_position_at_node(
    Vector3& out, int node, int row_index, Vector3& local)
{
    const Vector3* local_ptr = &local;
    double local_y = local_ptr->y;
    AttachmentSample* sample = &primary_samples[node];
    Vector3 scaled_up;
    scaled_up.x = (float)(local_y * sample->transform.basis_up.x);
    scaled_up.y = (float)(local_y * sample->transform.basis_up.y);
    scaled_up.z = (float)(local_y * sample->transform.basis_up.z);

    Vector3 projected =
        (local_ptr->x * sample->transform.basis_right + sample->transform.position)
        + scaled_up;
    projected.z += (float)row_index;
    out = projected;
    return *(int*)&projected.z;
}
