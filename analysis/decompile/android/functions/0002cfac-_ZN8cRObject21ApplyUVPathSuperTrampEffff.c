/*
 * mangled: _ZN8cRObject21ApplyUVPathSuperTrampEffff
 * demangled: cRObject::ApplyUVPathSuperTramp(float, float, float, float)
 * address: 0002cfac
 * size: 312
 */

/* cRObject::ApplyUVPathSuperTramp(float, float, float, float) */

void __thiscall
cRObject::ApplyUVPathSuperTramp
          (cRObject *this,float param_1,float param_2,float param_3,float param_4)

{
  float in_r1;
  uint uVar1;
  float in_r2;
  uint uVar2;
  float in_r3;
  int iVar3;
  float fVar4;
  float in_stack_00000000;

  uVar2 = *(uint *)(this + 0xc0);
  fVar4 = in_stack_00000000 + 0.09375;
  iVar3 = *(int *)(this + 200);
  if (0 < (int)uVar2) {
    uVar1 = 0;
    do {
      if ((uVar1 & 1) == 0) {
        if ((int)uVar1 < (int)(uVar2 - 4)) {
          *(float *)(iVar3 + 0x10) = in_r2 + in_r1 * *(float *)(iVar3 + 0x10);
          *(float *)(iVar3 + 0x18) = in_r2 + in_r1 * *(float *)(iVar3 + 0x18);
          *(float *)(iVar3 + 0x28) = in_r2 + in_r1 * *(float *)(iVar3 + 0x28);
          *(float *)(iVar3 + 0x20) = in_r2 + in_r1 * *(float *)(iVar3 + 0x20);
        }
        else {
          *(float *)(iVar3 + 0x10) = fVar4 + in_r1 * *(float *)(iVar3 + 0x10);
          *(float *)(iVar3 + 0x18) = fVar4 + in_r1 * *(float *)(iVar3 + 0x18);
          *(float *)(iVar3 + 0x28) = fVar4 + in_r1 * *(float *)(iVar3 + 0x28);
          *(float *)(iVar3 + 0x20) = fVar4 + in_r1 * *(float *)(iVar3 + 0x20);
        }
      }
      else {
        *(float *)(iVar3 + 0x10) = in_r3 + in_r1 * *(float *)(iVar3 + 0x10);
        *(float *)(iVar3 + 0x18) = in_r3 + in_r1 * *(float *)(iVar3 + 0x18);
        *(float *)(iVar3 + 0x20) = in_r3 + in_r1 * *(float *)(iVar3 + 0x20);
        *(float *)(iVar3 + 0x28) = in_r3 + in_r1 * *(float *)(iVar3 + 0x28);
      }
      iVar3 = iVar3 + 0x30;
      uVar1 = uVar1 + 1;
    } while (uVar1 != uVar2);
    return;
  }
  return;
}
