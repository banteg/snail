/*
 * mangled: _ZN8cRObject11ApplyUVPathEfff
 * demangled: cRObject::ApplyUVPath(float, float, float)
 * address: 00011c60
 * size: 216
 */

/* cRObject::ApplyUVPath(float, float, float) */

void __thiscall cRObject::ApplyUVPath(cRObject *this,float param_1,float param_2,float param_3)

{
  uint uVar1;
  int iVar2;

  iVar2 = *(int *)(this + 200);
  if (*(int *)(this + 0xc0) < 1) {
    return;
  }
  uVar1 = 0;
  do {
    while ((uVar1 & 1) == 0) {
      uVar1 = uVar1 + 1;
      *(float *)(iVar2 + 0x10) = param_2 + param_1 * *(float *)(iVar2 + 0x10);
      *(float *)(iVar2 + 0x18) = param_2 + param_1 * *(float *)(iVar2 + 0x18);
      *(float *)(iVar2 + 0x20) = param_2 + param_1 * *(float *)(iVar2 + 0x20);
      *(float *)(iVar2 + 0x28) = param_2 + param_1 * *(float *)(iVar2 + 0x28);
      iVar2 = iVar2 + 0x30;
      if (*(int *)(this + 0xc0) <= (int)uVar1) {
        return;
      }
    }
    uVar1 = uVar1 + 1;
    *(float *)(iVar2 + 0x10) = param_3 + param_1 * *(float *)(iVar2 + 0x10);
    *(float *)(iVar2 + 0x18) = param_3 + param_1 * *(float *)(iVar2 + 0x18);
    *(float *)(iVar2 + 0x20) = param_3 + param_1 * *(float *)(iVar2 + 0x20);
    *(float *)(iVar2 + 0x28) = param_3 + param_1 * *(float *)(iVar2 + 0x28);
    iVar2 = iVar2 + 0x30;
  } while ((int)uVar1 < *(int *)(this + 0xc0));
  return;
}
