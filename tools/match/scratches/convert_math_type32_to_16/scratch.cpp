// convert_math_type32_to_16 @ 0x44c890 (cdecl)

short convert_math_type32_to_16(float value, float scale)
{
    return (short)(value * (65536.0f / scale));
}
