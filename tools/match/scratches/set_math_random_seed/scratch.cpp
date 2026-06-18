// set_math_random_seed @ 0x44c970 (cdecl)

extern "C" void __cdecl srand(unsigned int seed);

void __cdecl set_math_random_seed(int seed)
{
    srand(seed);
}
