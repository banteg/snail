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

  fVar1 = 0.0;
  *(undefined4 *)(this + 0x18) = 0;
  *(undefined4 *)(this + 0x14) = 1;
  if (in_r2 != 0.0) {
    fVar1 = 1.0 / (in_r2 * 60.0);
  }
  *(float *)(this + 0x1c) = fVar1;
  *(int *)this = param_1;
  return;
}
