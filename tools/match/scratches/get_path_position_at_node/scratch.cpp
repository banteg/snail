// get_path_position_at_node @ 0x42b9c0 (thiscall, ret 0x10)

#include "track_attachment.h"

int AttachmentPathTemplate::get_path_position_at_node(
    Vector3* out, int node, int row_index, float* local)
{
    float* local_ptr = local;
    float temp[9];
    double local_y = local_ptr[1];
    AttachmentSample* sample = &primary_samples[node];
    temp[6] = (float)(local_y * sample->transform.basis_up.x);
    temp[7] = (float)(local_y * sample->transform.basis_up.y);
    double up_z = local_y * sample->transform.basis_up.z;

    double local_x = local_ptr[0];
    temp[0] = (float)(local_x * sample->transform.basis_right.x);
    temp[1] = (float)(local_x * sample->transform.basis_right.y);
    double base_z = local_x * sample->transform.basis_right.z + sample->transform.position.z;

    temp[3] = temp[0] + sample->transform.position.x;
    temp[4] = temp[1] + sample->transform.position.y;
    temp[0] = temp[3] + temp[6];
    temp[1] = temp[4] + temp[7];
    temp[2] = (float)(base_z + up_z);

    out->x = temp[0];
    out->y = temp[1];
    float result = (float)((double)row_index + temp[2]);
    out->z = result;
    return *(int*)&result;
}
