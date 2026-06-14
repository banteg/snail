// arccosine @ 0x44ca00 (cdecl)

extern "C" double __cdecl acos(double value);

double arccosine(float value)
{
    double result = acos(value);
    return result;
}
