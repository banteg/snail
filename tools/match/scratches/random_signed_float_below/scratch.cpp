// random_signed_float_below @ 0x44dc70 (cdecl)

extern "C" int __cdecl rand();

double __cdecl random_signed_float_below(float upper_bound)
{
    return ((float)rand() - 16384.0f) * upper_bound * 0.000061035156f;
}
