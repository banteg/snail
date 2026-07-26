/*
 * mangled: _ZN10cRSubGoldy9GhostDrawEf
 * demangled: cRSubGoldy::GhostDraw(float)
 * address: 0006bf6c
 * size: 44
 */

/* cRSubGoldy::GhostDraw(float) */

void __thiscall cRSubGoldy::GhostDraw(cRSubGoldy *this,float param_1)

{
  undefined4 in_r1;
  int iVar1;
  int iVar2;

  iVar1 = *(int *)(this + 0x8c);
  iVar2 = *(int *)(this + 0x90);
  *(undefined4 *)(iVar1 + 0x50) = in_r1;
  *(undefined4 *)(iVar2 + 0x50) = in_r1;
  *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) | 0x40;
  *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) | 0x40;
  return;
}
