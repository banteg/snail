/*
 * mangled: _ZN10cRSubGoldy13RessurectInitEi
 * demangled: cRSubGoldy::RessurectInit(int)
 * address: 0006c5fc
 * size: 32
 */

/* cRSubGoldy::RessurectInit(int) */

void __thiscall cRSubGoldy::RessurectInit(cRSubGoldy *this,int param_1)

{
  undefined4 uVar1;

  *(undefined4 *)(this + 0x80) = DAT_0006c61c;
  *(int *)(this + 0x74) = param_1;
  uVar1 = DAT_0006c620;
  this[0x78] = (cRSubGoldy)0x1;
  *(undefined4 *)(this + 0x84) = uVar1;
  return;
}
