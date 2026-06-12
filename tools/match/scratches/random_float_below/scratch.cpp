extern "C" int __cdecl rand(void);

double __cdecl random_float_below(float upper_bound)
{
    return rand() * upper_bound * 0.000030517578f;
}
