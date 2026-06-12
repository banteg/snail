// next_math_random_value @ 0x44c900

extern int g_math_random_index; // 0x77ff3c
extern int g_math_random_table[]; // 0x787f8c

int next_math_random_value()
{
    g_math_random_index = (g_math_random_index + 1) % 0x1fff;
    return g_math_random_table[g_math_random_index];
}
