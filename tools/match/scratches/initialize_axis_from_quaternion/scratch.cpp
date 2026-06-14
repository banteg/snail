// initialize_axis_from_quaternion @ 0x44d580 (thiscall)

float sine(float angle);
float arccosine(float value);

struct Quaternion {
    float x;
    float y;
    float z;
    float w;
};

struct Axis {
    float x;
    float y;
    float z;
    float angle;

    void initialize_axis_from_quaternion(const Quaternion* quaternion);
};

void Axis::initialize_axis_from_quaternion(const Quaternion* quaternion)
{
    float half_angle = arccosine(quaternion->w);
    x = quaternion->x / sine(half_angle);
    y = quaternion->y / sine(half_angle);
    z = quaternion->z / sine(half_angle);
    angle = half_angle + half_angle;
}
