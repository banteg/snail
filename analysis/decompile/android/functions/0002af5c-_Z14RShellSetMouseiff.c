/*
 * mangled: _Z14RShellSetMouseiff
 * demangled: RShellSetMouse(int, float, float)
 * address: 0002af5c
 * size: 184
 */

/* RShellSetMouse(int, float, float) */

void RShellSetMouse(int param_1,float param_2,float param_3)

{
  float in_r1;
  int iVar1;
  float in_r2;
  int iVar2;
  int iVar3;
  uint in_fpscr;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;

  iVar1 = *(int *)((int)&gMouseWX0 + param_1 * 4);
  fVar5 = (float)VectorSignedToFloat(iVar1,(byte)(in_fpscr >> 0x16) & 3);
  iVar2 = *(int *)((int)&gMouseWY0 + param_1 * 4);
  iVar3 = *(int *)((int)&gMouseWX1 + param_1 * 4);
  fVar6 = (float)VectorSignedToFloat(*(int *)((int)&gMouseWY1 + param_1 * 4) - iVar2,
                                     (byte)(in_fpscr >> 0x16) & 3);
  *(float *)(RShellInput + param_1 * 0x40 + 0x28) = in_r1;
  *(float *)(RShellInput + param_1 * 0x40 + 0x2c) = in_r2;
  fVar4 = (float)VectorSignedToFloat(iVar3 - iVar1,(byte)(in_fpscr >> 0x16) & 3);
  fVar7 = (float)VectorSignedToFloat(iVar2,(byte)(in_fpscr >> 0x16) & 3);
  MouseSet(param_1,(int)((fVar4 * in_r1) / 640.0 + fVar5),(int)((fVar6 * in_r2) / 480.0 + fVar7));
  return;
}
