#ifndef X87_STORE_H
#define X87_STORE_H

#ifdef SNAIL_PORT
#include <float.h>
#include <math.h>

// A float the original computed in an x87 register at 24-bit precision and
// then stored. The register has the extended exponent range, so a result in
// the float denormal range is first rounded to a 24-bit mantissa and then
// rounded again to the denormal on the store; wasm rounds once. `value` must
// be exact in double (a product of two floats is).
static inline float x87_store_float(double value)
{
    float single = (float)value;
    if (single == 0.0f || fabsf(single) >= FLT_MIN)
        return single;
    int exponent;
    double mantissa = frexp(value, &exponent);
    return (float)ldexp(rint(ldexp(mantissa, 24)), exponent - 24);
}
#endif

#endif
