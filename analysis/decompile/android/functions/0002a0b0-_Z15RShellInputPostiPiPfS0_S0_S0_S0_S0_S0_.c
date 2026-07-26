/*
 * mangled: _Z15RShellInputPostiPiPfS0_S0_S0_S0_S0_S0_
 * demangled: RShellInputPost(int, int*, float*, float*, float*, float*, float*, float*, float*)
 * address: 0002a0b0
 * size: 132
 */

/* RShellInputPost(int, int*, float*, float*, float*, float*, float*, float*, float*) */

void RShellInputPost(int param_1,int *param_2,float *param_3,float *param_4,float *param_5,
                    float *param_6,float *param_7,float *param_8,float *param_9)

{
  int iVar1;
  int iVar2;
  int iVar3;
  float fVar4;

  iVar2 = *param_2;
  iVar3 = param_1 * 2 + 1;
  iVar1 = param_1 * 0x40;
  *(float *)(RShellInput + iVar1 + 0x14) = *param_3;
  fVar4 = *param_4;
  *(int *)(RShellInput + iVar1 + 0x1c) = iVar2;
  *(float *)(RShellInput + iVar1 + 0x18) = fVar4;
  *(float *)(RShellInput + iVar1 + 0x28) = *param_5;
  *(float *)(RShellInput + iVar1 + 0x2c) = *param_6;
  *(float *)(RShellInput + iVar1 + 0x30) = *param_7;
  *(float *)(RShellInput + iVar3 * 0x20) = *param_8;
  *(float *)(RShellInput + iVar3 * 0x20 + 4) = *param_9;
  return;
}
