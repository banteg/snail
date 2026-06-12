struct Vec3 {
    float x;
    float y;
    float z;
};

double __stdcall dot_vectors(const Vec3* lhs, const Vec3* rhs)
{
    return lhs->z * rhs->z + lhs->y * rhs->y + lhs->x * rhs->x;
}
