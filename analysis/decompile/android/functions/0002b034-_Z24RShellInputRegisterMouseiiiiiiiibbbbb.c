/*
 * mangled: _Z24RShellInputRegisterMouseiiiiiiiibbbbb
 * demangled: RShellInputRegisterMouse(int, int, int, int, int, int, int, int, bool, bool, bool, bool, bool)
 * address: 0002b034
 * size: 608
 */

/* RShellInputRegisterMouse(int, int, int, int, int, int, int, int, bool, bool, bool, bool, bool) */

void RShellInputRegisterMouse
               (int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,int param_7,
               int param_8,bool param_9,bool param_10,bool param_11,bool param_12,bool param_13)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined1 *puVar4;
  uint in_fpscr;
  float fVar5;
  float fVar6;
  float fVar7;
  undefined4 uVar8;

  *(int *)((int)&gMouseWX0 + param_1 * 4) = param_2;
  *(int *)((int)&gMouseWX1 + param_1 * 4) = param_4;
  *(int *)((int)&gMouseWY0 + param_1 * 4) = param_3;
  *(int *)((int)&gMouseWY1 + param_1 * 4) = param_5;
  if ((param_6 < param_2 || param_4 <= param_6) || (param_7 < param_3 || param_5 <= param_7)) {
    if ((!param_12) || (param_13)) {
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
      HideWindowMouse(true);
    }
    else {
      HideWindowMouse(false);
    }
  }
  else {
    HideWindowMouse(true);
  }
  fVar7 = (float)VectorSignedToFloat(param_4 - param_2,(byte)(in_fpscr >> 0x16) & 3);
  iVar1 = param_1 * 0x40;
  uVar2 = (param_7 - param_3) * 0x1e0;
  fVar5 = (float)VectorSignedToFloat((param_6 - param_2) * 0x280,(byte)(in_fpscr >> 0x16) & 3);
  puVar4 = RShellInput + iVar1;
  uVar3 = uVar2;
  if (param_9) {
    uVar3 = *(uint *)(RShellInput + iVar1 + 0x1c) | 0x4000;
  }
  fVar6 = (float)VectorSignedToFloat(uVar2,(byte)(in_fpscr >> 0x16) & 3);
  *(float *)(RShellInput + iVar1 + 0x28) = fVar5 / fVar7;
  if (param_9) {
    *(uint *)(RShellInput + iVar1 + 0x1c) = uVar3;
  }
  fVar5 = (float)VectorSignedToFloat(param_5 - param_3,(byte)(in_fpscr >> 0x16) & 3);
  uVar8 = VectorSignedToFloat(param_8,(byte)(in_fpscr >> 0x16) & 3);
  *(float *)(RShellInput + iVar1 + 0x2c) = fVar6 / fVar5;
  *(undefined4 *)(RShellInput + iVar1 + 0x30) = uVar8;
  if (param_10) {
    puVar4 = RShellInput;
  }
  fVar5 = 1.0;
  if (param_10) {
    *(uint *)(puVar4 + iVar1 + 0x1c) = *(uint *)(puVar4 + iVar1 + 0x1c) | 0x8000;
  }
  if (param_11) {
    *(uint *)(RShellInput + iVar1 + 0x1c) = *(uint *)(RShellInput + iVar1 + 0x1c) | 0x100000;
  }
  fVar7 = *(float *)(RShellInput + iVar1 + 0x28);
  if ((1.0 <= fVar7) && (fVar5 = fVar7, 632.0 < fVar7)) {
    fVar5 = 632.0;
  }
  fVar7 = 1.0;
  fVar6 = *(float *)(RShellInput + iVar1 + 0x2c);
  *(float *)(RShellInput + iVar1 + 0x28) = fVar5;
  if ((1.0 <= fVar6) && (fVar7 = fVar6, 472.0 < fVar6)) {
    fVar7 = 472.0;
  }
  *(float *)(RShellInput + iVar1 + 0x2c) = fVar7;
  return;
}
