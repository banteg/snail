// RandSeed @ 0x44c970 (cdecl)

extern "C" void __cdecl srand(unsigned int seed);

void __cdecl RandSeed(int seed)
{
    srand(seed);
}
