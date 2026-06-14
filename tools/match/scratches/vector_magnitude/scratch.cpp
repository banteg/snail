// vector_magnitude @ 0x44ccf0 (thiscall)

float square_root(float value);

struct Vec3 {
    float x;
    float y;
    float z;

    float vector_magnitude();
};

float Vec3::vector_magnitude()
{
    return square_root(x * x + y * y + z * z);
}
