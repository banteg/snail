// sine @ 0x44c9d0 (cdecl)

extern float g_sine_table[]; // data_77ff8c

float sine(float angle)
{
    float scaled_angle = angle * 0.159154937f;
    int index = (int)(scaled_angle * 8192.0f);
    return g_sine_table[index & 0x1fff];
}
