// initialize_quaternion_from_matrix @ 0x44d5d0 (thiscall, ret 0x4)
// Builds a quaternion from the rotational basis rows of a transform matrix.

float square_root(float value);
int debug_report_stub(char* format, ...); // @ 0x449c00, stripped in release

struct Quaternion {
    float x;
    float y;
    float z;
    float w;

    Quaternion* initialize_quaternion_from_matrix(const float* matrix_rows);
};

Quaternion* Quaternion::initialize_quaternion_from_matrix(const float* matrix_rows)
{
    float trace = matrix_rows[5] + matrix_rows[0] + matrix_rows[10] + 1.0f;
    if (trace > 0.000001f) {
        float scale = 0.5f / square_root(trace);
        w = 0.25f / scale;
        x = (matrix_rows[6] - matrix_rows[9]) * scale;
        y = (matrix_rows[8] - matrix_rows[2]) * scale;
        z = (matrix_rows[1] - matrix_rows[4]) * scale;
        return this;
    }

    if (matrix_rows[0] < matrix_rows[5]) {
        goto right_less_than_up;
    }
    if (matrix_rows[0] > matrix_rows[10]) {
        goto x_dominant;
    }
    if (matrix_rows[5] > matrix_rows[10]) {
        goto y_dominant;
    }

z_dominant:
    {
        float radicand = matrix_rows[10] + 1.0f - matrix_rows[0] - matrix_rows[5];
        if (radicand < 0.0f) {
            debug_report_stub("ERROR:sqt %f\n", radicand);
            radicand = 0.0f;
        }

        float doubled_root = square_root(radicand);
        doubled_root = doubled_root + doubled_root;
        x = (matrix_rows[8] + matrix_rows[2]) / doubled_root;
        y = (matrix_rows[9] + matrix_rows[6]) / doubled_root;
        z = doubled_root * 0.25f;
        w = (matrix_rows[4] + matrix_rows[1]) / doubled_root;
        return this;
    }

right_less_than_up:
    if (matrix_rows[5] >= matrix_rows[10]) {
        goto y_dominant;
    }
    if (matrix_rows[0] <= matrix_rows[10]) {
        goto z_dominant;
    }

x_dominant:
    {
        float radicand = matrix_rows[0] + 1.0f - matrix_rows[5] - matrix_rows[10];
        if (radicand < 0.0f) {
            debug_report_stub("ERROR:sqrt %f\n", radicand);
            radicand = 0.0f;
        }

        float doubled_root = square_root(radicand);
        doubled_root = doubled_root + doubled_root;
        x = doubled_root * 0.25f;
        y = (matrix_rows[4] + matrix_rows[1]) / doubled_root;
        z = (matrix_rows[8] + matrix_rows[2]) / doubled_root;
        w = (matrix_rows[9] + matrix_rows[6]) / doubled_root;
        return this;
    }

y_dominant:
    {
        float radicand = matrix_rows[5] + 1.0f - matrix_rows[0] - matrix_rows[10];
        if (radicand < 0.0f) {
            debug_report_stub("ERROR:sqt %f\n", radicand);
            radicand = 0.0f;
        }

        float doubled_root = square_root(radicand);
        doubled_root = doubled_root + doubled_root;
        x = (matrix_rows[4] + matrix_rows[1]) / doubled_root;
        y = doubled_root * 0.25f;
        z = (matrix_rows[9] + matrix_rows[6]) / doubled_root;
        w = (matrix_rows[8] + matrix_rows[2]) / doubled_root;
        return this;
    }
}
