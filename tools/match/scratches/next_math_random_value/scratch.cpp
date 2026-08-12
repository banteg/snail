// gRMathRand2 @ 0x44c900

extern int g_math_random_index; // 0x77ff3c
extern int g_math_random_table[]; // 0x787f8c

int gRMathRand2()
{
    g_math_random_index = (g_math_random_index + 1) % 0x1fff;
    return g_math_random_table[g_math_random_index];
}
