/*
 * mangled: _ZN11cRSnailSkin6ChangeEif
 * demangled: cRSnailSkin::Change(int, float)
 * address: 0006d338
 * size: 60
 */

/* cRSnailSkin::Change(int, float) */

void __thiscall cRSnailSkin::Change(cRSnailSkin *this,int param_1,float param_2)

{
  float in_r2;
  float fVar1;

  fVar1 = DAT_0006d374;
  *(float *)(this + 0x18) = DAT_0006d374;
  *(undefined4 *)(this + 0x14) = 1;
  if (in_r2 != 0.0) {
    fVar1 = DAT_0006d37c / (in_r2 * DAT_0006d378);
  }
  *(float *)(this + 0x1c) = fVar1;
  *(int *)this = param_1;
  return;
}
