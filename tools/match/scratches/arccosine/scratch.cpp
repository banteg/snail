// ACos @ 0x44ca00 (cdecl)

extern "C" double __cdecl acos(double value);

float ACos(float value)
{
    double result = acos(value);
    return result;
}
