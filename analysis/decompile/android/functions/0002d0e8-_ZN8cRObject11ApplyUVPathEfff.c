/*
 * mangled: _ZN8cRObject11ApplyUVPathEfff
 * demangled: cRObject::ApplyUVPath(float, float, float)
 * address: 0002d0e8
 * size: 216
 */

/* cRObject::ApplyUVPath(float, float, float) */

void __thiscall cRObject::ApplyUVPath(cRObject *this,float param_1,float param_2,float param_3)

{
  float in_r1;
  uint uVar1;
  float in_r2;
  uint uVar2;
  float in_r3;
  int iVar3;

  uVar1 = *(uint *)(this + 0xc0);
  iVar3 = *(int *)(this + 200);
  if ((int)uVar1 < 1) {
    return;
  }
  uVar2 = 0;
  do {
    while ((uVar2 & 1) == 0) {
      uVar2 = uVar2 + 1;
      *(float *)(iVar3 + 0x10) = in_r2 + in_r1 * *(float *)(iVar3 + 0x10);
      *(float *)(iVar3 + 0x18) = in_r2 + in_r1 * *(float *)(iVar3 + 0x18);
      *(float *)(iVar3 + 0x28) = in_r2 + in_r1 * *(float *)(iVar3 + 0x28);
      *(float *)(iVar3 + 0x20) = in_r2 + in_r1 * *(float *)(iVar3 + 0x20);
      iVar3 = iVar3 + 0x30;
      if (uVar2 == uVar1) {
        return;
      }
    }
    uVar2 = uVar2 + 1;
    *(float *)(iVar3 + 0x10) = in_r3 + in_r1 * *(float *)(iVar3 + 0x10);
    *(float *)(iVar3 + 0x18) = in_r3 + in_r1 * *(float *)(iVar3 + 0x18);
    *(float *)(iVar3 + 0x20) = in_r3 + in_r1 * *(float *)(iVar3 + 0x20);
    *(float *)(iVar3 + 0x28) = in_r3 + in_r1 * *(float *)(iVar3 + 0x28);
    iVar3 = iVar3 + 0x30;
  } while (uVar2 != uVar1);
  return;
}
