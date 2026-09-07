// Integration checks call separately compiled recovered functions. This test
// program is not part of the reconstructed game's code or progress totals.
#include <stdio.h>
#include "rmath_random.h"
#include "rmath_tables.h"
#include "transform_matrix.h"
#include "vector3.h"

static int checks;
static int failures;

static bool approximately(float actual, float expected)
{
    float delta = actual - expected;
    return delta >= -0.000002f && delta <= 0.000002f;
}

static void check(bool condition, const char* label)
{
    ++checks;
    if (!condition) {
        ++failures;
        printf("FAIL: %s\n", label);
    }
}

int main(int argc, char** argv)
{
    RMathInit();
    // The driver always runs this fault-injection control separately and
    // requires failure, proving it actually reached the assertions.
    if (argc == 2 && argv[1][0] == '!')
        g_sine_table[0] = 1.0f;

    check(g_cosine_table[0] == 1.0f, "cosine array starts at sample zero");
    check(g_sine_table[0] == 0.0f, "sine array starts at sample zero");
    check(approximately(g_cosine_table[2048], 0.0f), "cosine quarter turn");
    check(approximately(g_sine_table[2048], 1.0f), "sine quarter turn");
    check(approximately(g_cosine_table[4096], -1.0f), "cosine half turn");
    check(approximately(g_sine_table[6144], -1.0f), "sine three-quarter turn");
    check(g_cosine_table[8191] > 0.999f, "last cosine entry initialized");
    check(g_sine_table[8191] < -0.0007f, "last sine entry initialized");
    check(approximately(Cos(0.0f), 1.0f), "Cos uses initialized array");
    check(approximately(Sin(1.57079637f), 1.0f), "Sin uses initialized array");
    check(g_math_random_index == 0, "RMathInit resets RNG cursor");
    check(gRMathRand2() == g_math_random_table[1], "RNG advances before reading");
    int last = 0;
    for (int i = 1; i < RMATH_RANDOM_TABLE_COUNT; ++i)
        last = gRMathRand2();
    check(g_math_random_index == 0 && last == g_math_random_table[0],
          "RNG wraps after 8191 reads");

    tVector left(1.0f, 0.0f, 0.0f);
    tVector right(0.0f, 1.0f, 0.0f);
    left.Cross(left, right);
    check(left.x == 0.0f && left.y == 0.0f && left.z == 1.0f,
          "Cross allows destination to alias left input");
    right.Cross(left, right);
    check(right.x == -1.0f && right.y == 0.0f && right.z == 0.0f,
          "Cross allows destination to alias right input");
    check(left.Dot(right) == 0.0f && tVector::Dot(left, left) == 1.0,
          "member and static Dot ABIs");
    tVector value(3.0f, 4.0f, 0.0f);
    check(value.Normalize() == 5.0f && approximately(value.x, 0.6f) && approximately(value.y, 0.8f),
          "Normalize returns length and updates components");
    tVector zero(0.0f, 0.0f, 0.0f);
    check(zero.Normalize() == 0.0f && zero.x == 0.0f && zero.y == 0.0f && zero.z == 0.0f,
          "Normalize preserves the zero vector");
    tVector source(0.0f, 0.0f, 7.0f);
    check(value.Normalize(source) == 7.0f && value.z == 1.0f && source.z == 7.0f,
          "Normalize from source preserves its input");
    check(Sqrt(81.0f) == 9.0f, "Sqrt return ABI");

    tMatrix matrix;
    matrix.Identity();
    check(matrix.basis_right.x == 1.0f && matrix.basis_up.y == 1.0f &&
          matrix.basis_forward.z == 1.0f && matrix.position_w == 1.0f &&
          matrix.position.x == 0.0f && matrix.position.y == 0.0f && matrix.position.z == 0.0f,
          "Identity basis and translation");
    matrix.basis_right = tVector(0.0f, 1.0f, 0.0f);
    matrix.basis_up = tVector(-1.0f, 0.0f, 0.0f);
    matrix.position = tVector(2.0f, 3.0f, 4.0f);
    tMatrix inverse;
    inverse.Invert(matrix);
    check(inverse.position.x == -3.0f && inverse.position.y == 2.0f && inverse.position.z == -4.0f,
          "rigid inverse translation");
    check(inverse.basis_right.y == -1.0f && inverse.basis_up.x == 1.0f &&
          inverse.basis_forward.z == 1.0f && inverse.position_w == 1.0f,
          "rigid inverse orientation");

    printf("rmath checks=%d failures=%d\n", checks, failures);
    // Wibo's process-exit path does not flush this CRT stream automatically.
    fflush(0);
    return failures ? 1 : 0;
}
