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

void Path::get_path_position_at_node(
    Vector3& out, int node, int row_index, Vector3& local)
{
    const Vector3* local_ptr = &local;
    float local_y = local_ptr->y;
    AttachmentSample* sample = &primary_samples[node];
    Vector3 scaled_up;
    scaled_up.x = local_y * sample->transform.basis_up.x;
    scaled_up.y = local_y * sample->transform.basis_up.y;
    scaled_up.z = local_y * sample->transform.basis_up.z;

    Vector3 projected =
        local_ptr->x * sample->transform.basis_right
        + sample->transform.position;
    projected = projected + scaled_up;
    Vector3 final_position = projected;
    final_position.z += (float)row_index;
    out = final_position;
}
