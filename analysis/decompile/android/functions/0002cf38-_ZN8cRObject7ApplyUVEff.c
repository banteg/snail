/*
 * mangled: _ZN8cRObject7ApplyUVEff
 * demangled: cRObject::ApplyUV(float, float)
 * address: 0002cf38
 * size: 116
 */

/* cRObject::ApplyUV(float, float) */

void __thiscall cRObject::ApplyUV(cRObject *this,float param_1,float param_2)

{
  float in_r1;
  int iVar1;
  float in_r2;
  int iVar2;
  int iVar3;

  iVar1 = *(int *)(this + 0xc0);
  iVar3 = *(int *)(this + 200);
  if (iVar1 < 1) {
    return;
  }
  iVar2 = 0;
  do {
    iVar2 = iVar2 + 1;
    *(float *)(iVar3 + 0x10) = in_r2 + in_r1 * *(float *)(iVar3 + 0x10);
    *(float *)(iVar3 + 0x18) = in_r2 + in_r1 * *(float *)(iVar3 + 0x18);
    *(float *)(iVar3 + 0x20) = in_r2 + in_r1 * *(float *)(iVar3 + 0x20);
    *(float *)(iVar3 + 0x28) = in_r2 + in_r1 * *(float *)(iVar3 + 0x28);
    iVar3 = iVar3 + 0x30;
  } while (iVar2 != iVar1);
  return;
}
