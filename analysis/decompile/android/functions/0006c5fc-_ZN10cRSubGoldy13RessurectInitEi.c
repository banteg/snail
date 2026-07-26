/*
 * mangled: _ZN10cRSubGoldy13RessurectInitEi
 * demangled: cRSubGoldy::RessurectInit(int)
 * address: 0006c5fc
 * size: 32
 */

/* cRSubGoldy::RessurectInit(int) */

void __thiscall cRSubGoldy::RessurectInit(cRSubGoldy *this,int param_1)

{
  *(undefined4 *)(this + 0x80) = 0;
  *(int *)(this + 0x74) = param_1;
  this[0x78] = (cRSubGoldy)0x1;
  *(undefined4 *)(this + 0x84) = 0x3c088889;
  return;
}
