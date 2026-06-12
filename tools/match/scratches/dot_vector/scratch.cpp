struct Vec3 {
    float x;
    float y;
    float z;

    double dot_vector(const Vec3* rhs);
};

double Vec3::dot_vector(const Vec3* rhs)
{
    return rhs->z * z + rhs->y * y + rhs->x * x;
}
