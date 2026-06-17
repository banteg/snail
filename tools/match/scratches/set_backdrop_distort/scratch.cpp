// set_backdrop_distort @ 0x410c40 (thiscall, ret 0x4)
// Seeds the backdrop distortion grid from the script Distort scalar.

#include "backdrop.h"

int next_math_random_value(); // @ 0x44c900

void Backdrop::set_backdrop_distort(float distort)
{
    int i;
    int j;
    float* result;
    float* cell;

    for (i = 0; i < 64; i += 8) {
        for (j = 0; j < 8; j++) {
            if (!j || !i || j == 7 || i == 56) {
                result = (float*)this + i * 6 + j * 6;
                result[22] = 0.0f;
                result[23] = 0.0f;
                *((float*)this + i * 6 + j * 6 + 24) = 0.0f;
                result[25] = 0.0f;
            } else {
                cell = (float*)this + i * 6 + j * 6;
                cell[22] =
                    (float)next_math_random_value() * 0.000191747604f;
                cell[23] =
                    (1.0f /
                        (((float)next_math_random_value() * 0.00006103515625f +
                             3.0f) *
                            60.0f)) *
                    6.28318548f;
                *((float*)this + i * 6 + j * 6 + 24) =
                    ((float)next_math_random_value() - 16384.0f) *
                    distort *
                    0.00006103515625f;
                cell[25] =
                    ((float)next_math_random_value() - 16384.0f) *
                    distort *
                    0.00006103515625f;
            }
        }
    }
}
