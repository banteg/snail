/*
 * mangled: _ZN6cRSlug3HitEi
 * demangled: cRSlug::Hit(int)
 * address: 00026068
 * size: 196
 */

/* cRSlug::Hit(int) */

void __thiscall cRSlug::Hit(cRSlug *this,int param_1)

{
  undefined *puVar1;
  undefined4 uVar2;
  int iVar3;
  uint in_fpscr;
  float fVar4;

  iVar3 = *(int *)(this + 0xbc);
  *(int *)(this + 0xbc) = iVar3 - param_1;
  if (iVar3 - param_1 < 0) {
    *(undefined4 *)(this + 0xbc) = 0;
    Kill(this);
    return;
  }
  this[0xc0] = (cRSlug)0x1;
  uVar2 = gRMathRand2();
  puVar1 = PTR__Game_001b60b8;
  if (this[0xcc] != (cRSlug)0x0) {
    return;
  }
  iVar3 = *(int *)PTR__Game_001b60b8;
  if (*(char *)(iVar3 + 0x7b14c) != '\0') {
    return;
  }
  fVar4 = (float)VectorSignedToFloat(uVar2,(byte)(in_fpscr >> 0x16) & 3);
  *(undefined4 *)(iVar3 + 0x7b150) = *(undefined4 *)((int)&DAT_0007b154 + iVar3);
  *(undefined1 *)(*(int *)puVar1 + 0x7b14c) = 1;
  this[0xcc] = (cRSlug)0x1;
  *(undefined4 *)(this + 0xd0) = 0;
  RShellVoicePlay((int)(fVar4 * 3.0517578e-05 * 3.0) + 0x24,1.0,-1.0,0.0);
  return;
}
