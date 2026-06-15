// initialize_trigonometry_tables @ 0x44c930 (cdecl)

extern "C" double __cdecl cos(double value);
extern "C" double __cdecl sin(double value);

extern float g_cosine_table_init_base[]; // 0x777f38, one element before g_cosine_table
extern float g_sine_table_init_base[]; // 0x77ff88, one element before g_sine_table

int initialize_math_random_table();

int initialize_trigonometry_tables()
{
    int index = 0;
    int source_index = 0;

    do {
        float source_angle = (float)source_index;
        source_index = ++index;
        float angle = source_angle * 0.00012207031f;
        angle = angle * 6.2831855f;
        g_cosine_table_init_base[index] = (float)cos(angle);
        g_sine_table_init_base[index] = (float)sin(angle);
    } while (index < 0x2000);

    return initialize_math_random_table();
}
