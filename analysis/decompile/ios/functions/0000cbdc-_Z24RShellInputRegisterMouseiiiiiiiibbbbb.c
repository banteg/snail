/*
 * mangled: _Z24RShellInputRegisterMouseiiiiiiiibbbbb
 * demangled: RShellInputRegisterMouse(int, int, int, int, int, int, int, int, bool, bool, bool, bool, bool)
 * address: 0000cbdc
 * size: 528
 */

/* RShellInputRegisterMouse(int, int, int, int, int, int, int, int, bool, bool, bool, bool, bool) */

void RShellInputRegisterMouse
               (int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,int param_7,
               int param_8,bool param_9,bool param_10,bool param_11,bool param_12,bool param_13)

{
  uint uVar1;
  uint in_fpscr;
  float fVar2;
  float fVar3;
  float fVar4;
  undefined4 uVar5;

  *(int *)(&_gMouseWX0 + param_1 * 4) = param_2;
  (&_gMouseWY0)[param_1] = param_3;
  (&_gMouseWX1)[param_1] = param_4;
  (&_gMouseWY1)[param_1] = param_5;
  if ((param_4 <= param_6 || param_6 < param_2) || (param_5 <= param_7 || param_7 < param_3)) {
    if ((param_12) && (!param_13)) {
      HideWindowMouse(false);
      goto LAB_0000ccc4;
    }
    if (param_6 < param_2) {
      param_6 = param_2;
    }
    if (param_4 <= param_6) {
      param_6 = param_4 + -1;
    }
    if (param_7 < param_3) {
      param_7 = param_3;
    }
    if (param_5 <= param_7) {
      param_7 = param_5 + -1;
    }
    MouseSet(param_1,param_6,param_7);
  }
  HideWindowMouse(true);
LAB_0000ccc4:
  fVar2 = (float)VectorSignedToFloat((param_6 - param_2) * 0x280,(byte)(in_fpscr >> 0x16) & 3);
  uVar1 = (param_7 - param_3) * 0x200;
  fVar3 = (float)VectorSignedToFloat(param_4 - param_2,(byte)(in_fpscr >> 0x16) & 3);
  (&DAT_00266588)[param_1 * 0x10] = fVar2 / fVar3;
  fVar3 = (float)VectorSignedToFloat((param_7 - param_3) * 0x1e0,(byte)(in_fpscr >> 0x16) & 3);
  fVar4 = (float)VectorSignedToFloat(param_5 - param_3,(byte)(in_fpscr >> 0x16) & 3);
  fVar2 = 1.0;
  (&DAT_0026658c)[param_1 * 0x10] = fVar3 / fVar4;
  uVar5 = VectorSignedToFloat(param_8,(byte)(in_fpscr >> 0x16) & 3);
  (&DAT_00266590)[param_1 * 0x10] = uVar5;
  fVar3 = (float)(&DAT_00266588)[param_1 * 0x10];
  if (param_9) {
    uVar1 = (&DAT_0026657c)[param_1 * 0x10];
  }
  if (param_9) {
    (&DAT_0026657c)[param_1 * 0x10] = uVar1 | 0x4000;
  }
  if (param_10) {
    (&DAT_0026657c)[param_1 * 0x10] = (&DAT_0026657c)[param_1 * 0x10] | 0x8000;
  }
  if (param_11) {
    (&DAT_0026657c)[param_1 * 0x10] = (&DAT_0026657c)[param_1 * 0x10] | 0x100000;
  }
  if ((1.0 <= fVar3) && (fVar2 = fVar3, 632.0 < fVar3)) {
    fVar2 = 632.0;
  }
  fVar3 = 1.0;
  (&DAT_00266588)[param_1 * 0x10] = fVar2;
  fVar2 = (float)(&DAT_0026658c)[param_1 * 0x10];
  if ((1.0 <= fVar2) && (fVar3 = fVar2, 472.0 < fVar2)) {
    fVar3 = 472.0;
  }
  (&DAT_0026658c)[param_1 * 0x10] = fVar3;
  return;
}
