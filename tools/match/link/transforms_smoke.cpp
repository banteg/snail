// Reuse the base math assertions, then exercise the transform dependency chain.
#define main rmath_base_main
#include "rmath_smoke.cpp"
#undef main

static bool vector_is(const tVector& v, float x, float y, float z)
{
    return approximately(v.x, x) && approximately(v.y, y) && approximately(v.z, z);
}

int main(int argc, char** argv)
{
    rmath_base_main(argc, argv);
    tMatrix scale(2.0f);
    check(scale.basis_right.x == 2.0f && scale.basis_up.y == 2.0f &&
          scale.basis_forward.z == 2.0f && scale.position_w == 1.0f,
          "uniform scale constructor");
    tMatrix translation(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 5, 6, 7, 1);
    tVector source(1, 2, 3);
    tVector copied = source * translation;
    check(vector_is(copied, 6, 8, 10) && vector_is(source, 1, 2, 3),
          "value-return transform preserves source and translates");
    source *= scale;
    check(vector_is(source, 2, 4, 6), "by-value matrix transform ABI");
    tVector magnitude(3, 4, 0);
    check(magnitude.Magnitude() == 5, "const magnitude uses recovered square root");

    tMatrix rotation;
    // The native x87 lookup truncates this float quarter-turn to sample 2047.
    // Preserve its quantization instead of assuming an ideal rotation.
    float quarter_cos = g_cosine_table[2047];
    float quarter_sin = g_sine_table[2047];
    check(Cos(1.57079637f) == quarter_cos && Sin(1.57079637f) == quarter_sin,
          "quarter-turn lookup retains native truncation");
    rotation.Identity();
    rotation.RotLocalZ(1.57079637f);
    rotation.position = tVector(50, 60, 70);
    tVector axis(1, 0, 0);
    tVector* returned = &axis.Rotate(rotation);
    check(returned == &axis && vector_is(axis, quarter_cos, quarter_sin, 0),
          "Rotate mutates receiver and excludes translation");
    rotation.RotIdentity();
    check(vector_is(rotation.position, 50, 60, 70) &&
          vector_is(rotation.basis_right, 1, 0, 0), "RotIdentity preserves position");
    rotation.RotLocalX(1.57079637f);
    check(vector_is(rotation.basis_up, 0, quarter_cos, quarter_sin) &&
          vector_is(rotation.basis_forward, 0, -quarter_sin, quarter_cos), "local X quarter turn");
    rotation.RotIdentity();
    rotation.RotLocalY(1.57079637f);
    check(vector_is(rotation.basis_right, quarter_cos, 0, -quarter_sin) &&
          vector_is(rotation.basis_forward, quarter_sin, 0, quarter_cos), "local Y quarter turn");

    tMatrix product;
    product.Multiply(scale, translation);
    check(vector_is(tVector(1, 2, 3) * product, 7, 10, 13),
          "scale then translate composition");
    tMatrix assigned = scale;
    assigned *= translation;
    check(vector_is(tVector(1, 2, 3) * assigned, 7, 10, 13),
          "multiply assignment preserves aliased left input");
    assigned = scale;
    assigned.Multiply(translation);
    check(vector_is(tVector(1, 2, 3) * assigned, 7, 10, 13),
          "multiply forwarding method");
    assigned = translation;
    assigned.PreMultiply(scale);
    check(vector_is(tVector(1, 2, 3) * assigned, 7, 10, 13),
          "premultiply preserves aliased right input");
    translation.Invert();
    check(vector_is(copied * translation, 1, 2, 3), "in-place rigid inverse round trip");

    rotation.Identity();
    rotation.SetZDir(tVector(1, 0, 0));
    check(vector_is(rotation.basis_forward, 1, 0, 0) &&
          vector_is(rotation.basis_right, 0, 0, -1) &&
          vector_is(rotation.basis_up, 0, 1, 0), "direction basis and Cross dependency");
    rotation.position = tVector(2, 3, 4);
    rotation.LookAt(tVector(2, 3, 14));
    check(vector_is(rotation.basis_forward, 0, 0, 1), "LookAt subtracts position");
    rotation.basis_right *= 2;
    rotation.basis_up *= 3;
    rotation.basis_forward *= 4;
    rotation.Orthoganalize();
    check(vector_is(rotation.basis_right, 1, 0, 0) &&
          vector_is(rotation.basis_up, 0, 1, 0) &&
          vector_is(rotation.basis_forward, 0, 0, 1),
          "orthogonalization links authored Cross and normalizes axes");

    printf("transforms checks=%d failures=%d\n", checks, failures);
    fflush(0);
    return failures ? 1 : 0;
}
