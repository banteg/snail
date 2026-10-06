// MathType32to16 @ 0x44c890 (cdecl)

short MathType32to16(float value, float scale)
{
    return (short)(value * (65536.0f / scale));
}
