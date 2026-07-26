/*
 * mangled: _ZN10cRSubGoldy12SameViewportEii
 * demangled: cRSubGoldy::SameViewport(int, int)
 * address: 0006bee4
 * size: 20
 */

/* cRSubGoldy::SameViewport(int, int) */

bool __thiscall cRSubGoldy::SameViewport(cRSubGoldy *this,int param_1,int param_2)

{
  return (param_2 & param_1 & 0xff000000U) != 0;
}
