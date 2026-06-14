// normalize_vector @ 0x44cca0 (fastcall)

struct Vec3 {
    float x;
    float y;
    float z;
};

double __stdcall dot_vectors(const Vec3* lhs, const Vec3* rhs);
float square_root(float value);

float __fastcall normalize_vector(Vec3* vector)
{
    float length = square_root((float)dot_vectors(vector, vector));
    if (length == 0.0f) {
        return 0.0f;
    }

    float scale = 1.0f / length;
    vector->x = scale * vector->x;
    vector->y = scale * vector->y;
    vector->z = scale * vector->z;
    return length;
}
