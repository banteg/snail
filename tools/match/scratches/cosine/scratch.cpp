// cosine @ 0x44c980 (cdecl)

extern "C" double __cdecl cos(double value);

extern float g_cosine_table[]; // data_777f3c

float cosine(float angle)
{
    float scaled_angle = angle * 0.159154937f;
    int index = (int)(scaled_angle * 8192.0f);
    float exact = (float)cos(angle);
    int table_index = index & 0x1fff;
    float delta = g_cosine_table[table_index] - exact;

    if (delta < 0.0f)
        delta = -delta;
    if (delta > 0.02f) {
        for (;;) {
        }
    }
    return g_cosine_table[table_index];
}
