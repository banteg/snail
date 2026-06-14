// cross_vectors @ 0x44cd40 (thiscall)

struct Vec3 {
    Vec3() {}
    ~Vec3() {}

    float x;
    float y;
    float z;

    void cross_vectors(const Vec3* lhs, const Vec3* rhs);
};

void Vec3::cross_vectors(const Vec3* lhs, const Vec3* rhs)
{
    static Vec3 result;

    result.x = lhs->y * rhs->z - rhs->y * lhs->z;
    result.y = lhs->z * rhs->x - lhs->x * rhs->z;
    result.z = rhs->y * lhs->x - lhs->y * rhs->x;
    *this = result;
}
