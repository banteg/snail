/*
 * mangled: _ZN8cRObject7ApplyUVEff
 * demangled: cRObject::ApplyUV(float, float)
 * address: 00011ab4
 * size: 116
 */

/* cRObject::ApplyUV(float, float) */

void __thiscall cRObject::ApplyUV(cRObject *this,float param_1,float param_2)

{
  int iVar1;
  int iVar2;

  iVar2 = *(int *)(this + 200);
  if (*(int *)(this + 0xc0) < 1) {
    return;
  }
  iVar1 = 0;
  do {
    iVar1 = iVar1 + 1;
    *(float *)(iVar2 + 0x10) = param_2 + param_1 * *(float *)(iVar2 + 0x10);
    *(float *)(iVar2 + 0x18) = param_2 + param_1 * *(float *)(iVar2 + 0x18);
    *(float *)(iVar2 + 0x20) = param_2 + param_1 * *(float *)(iVar2 + 0x20);
    *(float *)(iVar2 + 0x28) = param_2 + param_1 * *(float *)(iVar2 + 0x28);
    iVar2 = iVar2 + 0x30;
  } while (iVar1 < *(int *)(this + 0xc0));
  return;
}
