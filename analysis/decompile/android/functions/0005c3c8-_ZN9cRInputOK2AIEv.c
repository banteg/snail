/*
 * mangled: _ZN9cRInputOK2AIEv
 * demangled: cRInputOK::AI()
 * address: 0005c3c8
 * size: 172
 */

/* cRInputOK::AI() */

void __thiscall cRInputOK::AI(cRInputOK *this)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  float fVar4;
  float fVar5;
  float fVar6;

  iVar2 = *(int *)(this + 0x1c);
  if ((*(uint *)(iVar2 + 0x704) & 4) != 0) {
    fVar5 = *(float *)(iVar2 + 0x22c);
    fVar6 = *(float *)(iVar2 + 0x23c);
    fVar4 = *(float *)(iVar2 + 0x20c);
    iVar1 = *(int *)(this + 0x20);
    uVar3 = *(undefined4 *)(iVar2 + 0x6f0);
    *(undefined4 *)(iVar1 + 0x230) = *(undefined4 *)(iVar2 + 0x230);
    *(undefined4 *)(iVar1 + 0x6f0) = uVar3;
    fVar4 = fVar5 + fVar6 + fVar4 + *(float *)(iVar1 + 0x20c);
    *(float *)(iVar1 + 0x22c) = fVar4;
    *(float *)(iVar1 + 0x6ec) = fVar4;
    return;
  }
  if ((*(uint *)(iVar2 + 0x704) & 8) == 0) {
    return;
  }
  iVar1 = *(int *)(this + 0x20);
  fVar5 = *(float *)(iVar2 + 0x22c);
  fVar4 = *(float *)(iVar2 + 0x20c);
  uVar3 = *(undefined4 *)(iVar2 + 0x6f0);
  *(undefined4 *)(iVar1 + 0x230) = *(undefined4 *)(iVar2 + 0x230);
  *(undefined4 *)(iVar1 + 0x6f0) = uVar3;
  fVar4 = ((fVar5 - *(float *)(iVar1 + 0x23c)) - fVar4) + *(float *)(iVar1 + 0x20c) * -2.0;
  *(float *)(iVar1 + 0x22c) = fVar4;
  *(float *)(iVar1 + 0x6ec) = fVar4;
  return;
}
