/*
 * mangled: _ZN6cRSlug3HitEi
 * demangled: cRSlug::Hit(int)
 * address: 000794cc
 * size: 104
 */

/* cRSlug::Hit(int) */

void __thiscall cRSlug::Hit(cRSlug *this,int param_1)

{
  undefined4 uVar1;
  int iVar2;
  uint in_fpscr;

  iVar2 = *(int *)(this + 0xbc);
  *(int *)(this + 0xbc) = iVar2 - param_1;
  if (-1 < iVar2 - param_1) {
    this[0xc0] = (cRSlug)0x1;
    uVar1 = gRMathRand2();
    VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
    VoicePlay((int)this);
    return;
  }
  *(undefined4 *)(this + 0xbc) = 0;
  Kill(this);
  return;
}
