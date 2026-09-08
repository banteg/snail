// Behavioral fixtures for the partial matrix-to-quaternion constructor.
// This harness and original-code oracle receive no reconstruction credit.
#include <stdio.h>
#include <string.h>
#include "quaternion.h"
#include "transform_matrix.h"

static bool approximately(float actual, float expected)
{
    float delta = actual - expected;
    return delta >= -0.000002f && delta <= 0.000002f;
}

static const float diagonals[][3] = {
    {1, 1, 1},       // positive trace
    {1, -1, -1},     // X dominant
    {-1, 1, -1},     // Y dominant
    {-1, -1, 1},     // Z dominant
    {0, 0, -1},      // X/Y tie selects X
    {-1, 0, 0},      // Y/Z tie selects Y
    {0, -1, 0},      // X/Z tie selects Z
    {-1, -1, -1},    // all equal selects Z
    {-3, -2, -1},    // less-than continuation selects Z
    {0.5f, 0.25f, 0.25f}, // non-unit positive trace
};

int main(int argc, char** argv)
{
    if (argc < 2 || argc > 3)
        return 2;
    FILE* output = fopen(argv[1], "wb");
    if (!output)
        return 2;
    int failures = 0;
    for (int index = 0; index < sizeof(diagonals) / sizeof(diagonals[0]); ++index) {
        tMatrix matrix;
        matrix.basis_right = tVector(diagonals[index][0], 2, 3);
        matrix.basis_up = tVector(5, diagonals[index][1], 7);
        matrix.basis_forward = tVector(11, 13, diagonals[index][2]);
        // These values are deliberately unrelated to the rotational basis.
        matrix.position = tVector(17, 19, 23);
        matrix.basis_right_w = 29;
        matrix.basis_up_w = 31;
        matrix.basis_forward_w = 37;
        matrix.position_w = 41;
        tMatrix before = matrix;
        tQuaternian result(matrix);
        if (argc == 3 && argv[2][0] == '!' && index == 1)
            result.w = (matrix.basis_forward.y - matrix.basis_up.z) / 4.0f;

        if (memcmp(&before, &matrix, sizeof(matrix)))
            ++failures;
        // Independent exact/simple expectations expose the shipped fallback
        // w sums: changing them to the conventional differences must fail.
        static const float expected[][4] = {
            {-1.5f, 2.0f, -0.75f, 1.0f},
            {1.0f, 1.75f, 3.5f, 5.0f},
            {1.75f, 1.0f, 5.0f, 3.5f},
            {3.5f, 5.0f, 1.0f, 1.75f},
        };
        if (index < 4 &&
            (!approximately(result.x, expected[index][0]) ||
             !approximately(result.y, expected[index][1]) ||
             !approximately(result.z, expected[index][2]) ||
             !approximately(result.w, expected[index][3])))
            ++failures;
        if (fwrite(&result, sizeof(result), 1, output) != 1)
            ++failures;
        printf("quaternion case=%d x=%.9g y=%.9g z=%.9g w=%.9g\n",
               index, result.x, result.y, result.z, result.w);
    }
    if (fclose(output))
        ++failures;
    printf("quaternion cases=10 failures=%d\n", failures);
    fflush(0);
    return failures ? 1 : 0;
}
