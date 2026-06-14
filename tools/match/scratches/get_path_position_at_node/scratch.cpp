// get_path_position_at_node @ 0x42b9c0 (thiscall, ret 0x10)

struct Vector3 {
    float x;
    float y;
    float z;
};

struct PathTemplateSample {
    float words[0xa8 / 4];
};

class PathTemplate {
public:
    int get_path_position_at_node(Vector3* out, int node, int row_index, float* local);

    char unknown_00[0x58];
    PathTemplateSample* primary_samples; // +0x58
};

int PathTemplate::get_path_position_at_node(Vector3* out, int node, int row_index, float* local)
{
    float* local_ptr = local;
    float temp[9];
    double local_y = local_ptr[1];
    temp[6] = (float)(local_y * primary_samples[node].words[4]);
    float* sample = primary_samples[node].words;
    temp[7] = (float)(local_y * sample[5]);
    double up_z = local_y * sample[6];

    double local_x = local_ptr[0];
    temp[0] = (float)(local_x * sample[0]);
    temp[1] = (float)(local_x * sample[1]);
    double base_z = local_x * sample[2] + sample[14];

    temp[3] = temp[0] + sample[12];
    temp[4] = temp[1] + sample[13];
    temp[0] = temp[3] + temp[6];
    temp[1] = temp[4] + temp[7];
    temp[2] = (float)(base_z + up_z);

    out->x = temp[0];
    out->y = temp[1];
    float result = (float)((double)row_index + temp[2]);
    out->z = result;
    return *(int*)&result;
}
