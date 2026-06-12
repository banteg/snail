// set_math_random_seed @ 0x44c970 (cdecl)

extern void __cdecl sub_48BFDB(int seed);

void __cdecl set_math_random_seed(int seed)
{
    sub_48BFDB(seed);
}
