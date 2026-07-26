/*
 * mangled: _ZN10cRRowModel2AIEv
 * demangled: cRRowModel::AI()
 * address: 0003044c
 * size: 196
 */

/* cRRowModel::AI() */

void __thiscall cRRowModel::AI(cRRowModel *this)

{
  undefined *puVar1;
  int iVar2;
  int iVar3;
  float fVar4;

  puVar1 = PTR__Game_001b60b8;
  *(float *)(this + 0x5c) = *(float *)(this + 0x5c) + *(float *)(this + 0x74);
  fVar4 = *(float *)(this + 100);
  *(float *)(this + 0x60) = *(float *)(this + 0x60) + *(float *)(this + 0x78);
  *(float *)(this + 100) = fVar4 + *(float *)(this + 0x7c);
  iVar2 = *(int *)puVar1;
  if (*(float *)(iVar2 + 0x847b4) <= fVar4 + *(float *)(this + 0x7c)) {
    return;
  }
  if ((*(uint *)(this + 4) & 0x200) == 0) {
    RShellError("List remove");
    return;
  }
  if ((*(uint *)(this + 4) & 0x40) != 0) {
    RShellError("List remove NEXTBOD");
    return;
  }
  iVar3 = *(int *)(this + 0xc);
  if (iVar3 != 0) {
    *(undefined4 *)(iVar3 + 8) = *(undefined4 *)(this + 8);
  }
  if (*(int *)(this + 8) == 0) {
    *(int *)(iVar2 + 0x35c) = iVar3;
  }
  else {
    *(int *)(*(int *)(this + 8) + 0xc) = iVar3;
  }
  *(undefined4 *)(this + 0xc) = *(undefined4 *)(iVar2 + 0x360);
  *(cRRowModel **)(iVar2 + 0x360) = this;
  *(uint *)(this + 4) = *(uint *)(this + 4) & 0xfffffdff;
  return;
}
