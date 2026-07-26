/*
 * mangled: _Z14RShellSetMouseiff
 * demangled: RShellSetMouse(int, float, float)
 * address: 0000cb1c
 * size: 164
 */

/* RShellSetMouse(int, float, float) */

void RShellSetMouse(int param_1,float param_2,float param_3)

{
  uint in_fpscr;
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;

  (&DAT_00266588)[param_1 * 0x10] = param_2;
  (&DAT_0026658c)[param_1 * 0x10] = param_3;
  fVar1 = (float)VectorSignedToFloat((&_gMouseWX1)[param_1] - *(int *)(&_gMouseWX0 + param_1 * 4),
                                     (byte)(in_fpscr >> 0x16) & 3);
  fVar2 = (float)VectorSignedToFloat(*(int *)(&_gMouseWX0 + param_1 * 4),
                                     (byte)(in_fpscr >> 0x16) & 3);
  fVar3 = (float)VectorSignedToFloat((&_gMouseWY1)[param_1] - (&_gMouseWY0)[param_1],
                                     (byte)(in_fpscr >> 0x16) & 3);
  fVar4 = (float)VectorSignedToFloat((&_gMouseWY0)[param_1],(byte)(in_fpscr >> 0x16) & 3);
  MouseSet(param_1,(int)((fVar1 * param_2) / 640.0 + fVar2),(int)((fVar3 * param_3) / 480.0 + fVar4)
          );
  return;
}
