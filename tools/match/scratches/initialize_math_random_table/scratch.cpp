// initialize_math_random_table @ 0x44c8d0 (cdecl)

extern "C" int __cdecl rand();

extern int g_math_random_index; // 0x77ff3c
extern int g_math_random_table[]; // 0x787f8c

int initialize_math_random_table()
{
    int* cursor = g_math_random_table;
    int result;

    do {
        result = rand();
        *cursor++ = result;
    } while ((int)cursor < (int)&g_math_random_table[0x1fff]);

    g_math_random_index = 0;
    return result;
}
