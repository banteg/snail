// atan2_positive @ 0x44ca10 (cdecl)

extern "C" double __cdecl atan(double value);

float atan2_positive(float y, float x)
{
    int quadrant;

    if (y > 0.0f) {
        if (x > 0.0f) {
            quadrant = 0;
        } else {
            quadrant = 1;
            x = -x;
        }
    } else {
        y = -y;
        if (x > 0.0f) {
            quadrant = 3;
        } else {
            quadrant = 2;
            x = -x;
        }
    }

    float result;
    if (x == 0.0f) {
        result = 1.5707964f;
    } else {
        result = (float)atan(y / x);
    }

    if (quadrant == 0) {
        return result;
    }
    if (quadrant == 1) {
        return 3.1415927f - result;
    }
    if (quadrant == 2) {
        return result + 3.1415927f;
    }
    return -result;
}
