// convert_math_type16_to_32 @ 0x44c8b0 (cdecl)

float convert_math_type16_to_32(short value, float scale)
{
    return (scale * 0.0000152587891f) * value;
}
