double __fastcall normalize_vector(void* vector);

struct Vec3 {
    float x;
    float y;
    float z;

    double normalize_vector_from_source(const Vec3* source);
};

double Vec3::normalize_vector_from_source(const Vec3* source)
{
    *this = *source;
    return normalize_vector(this);
}
