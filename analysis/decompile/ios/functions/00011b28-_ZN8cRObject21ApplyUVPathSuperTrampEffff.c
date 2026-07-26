/*
 * mangled: _ZN8cRObject21ApplyUVPathSuperTrampEffff
 * demangled: cRObject::ApplyUVPathSuperTramp(float, float, float, float)
 * address: 00011b28
 * size: 308
 */

/* cRObject::ApplyUVPathSuperTramp(float, float, float, float) */

void __thiscall
cRObject::ApplyUVPathSuperTramp
          (cRObject *this,float param_1,float param_2,float param_3,float param_4)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  float fVar4;

  iVar2 = *(int *)(this + 0xc0);
  iVar3 = *(int *)(this + 200);
  fVar4 = param_4 + 0.09375;
  if (iVar2 < 1) {
    return;
  }
  uVar1 = 0;
  do {
    while ((uVar1 & 1) != 0) {
      *(float *)(iVar3 + 0x10) = param_3 + param_1 * *(float *)(iVar3 + 0x10);
      *(float *)(iVar3 + 0x18) = param_3 + param_1 * *(float *)(iVar3 + 0x18);
      *(float *)(iVar3 + 0x20) = param_3 + param_1 * *(float *)(iVar3 + 0x20);
      *(float *)(iVar3 + 0x28) = param_3 + param_1 * *(float *)(iVar3 + 0x28);
LAB_00011b98:
      iVar2 = *(int *)(this + 0xc0);
      uVar1 = uVar1 + 1;
      iVar3 = iVar3 + 0x30;
      if (iVar2 <= (int)uVar1) {
        return;
      }
    }
    if ((int)uVar1 <= iVar2 + -5) {
      *(float *)(iVar3 + 0x10) = param_2 + param_1 * *(float *)(iVar3 + 0x10);
      *(float *)(iVar3 + 0x18) = param_2 + param_1 * *(float *)(iVar3 + 0x18);
      *(float *)(iVar3 + 0x20) = param_2 + param_1 * *(float *)(iVar3 + 0x20);
      *(float *)(iVar3 + 0x28) = param_2 + param_1 * *(float *)(iVar3 + 0x28);
      goto LAB_00011b98;
    }
    uVar1 = uVar1 + 1;
    *(float *)(iVar3 + 0x10) = fVar4 + param_1 * *(float *)(iVar3 + 0x10);
    *(float *)(iVar3 + 0x18) = fVar4 + param_1 * *(float *)(iVar3 + 0x18);
    *(float *)(iVar3 + 0x20) = fVar4 + param_1 * *(float *)(iVar3 + 0x20);
    *(float *)(iVar3 + 0x28) = fVar4 + param_1 * *(float *)(iVar3 + 0x28);
    iVar3 = iVar3 + 0x30;
    iVar2 = *(int *)(this + 0xc0);
    if (iVar2 <= (int)uVar1) {
      return;
    }
  } while( true );
}
