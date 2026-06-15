extern "C" int __cdecl j_rand(void); // jmp thunk @ 0x44c920 to CRT rand

double __cdecl random_float_below(float upper_bound)
{
    return j_rand() * upper_bound * 0.000030517578f;
}
