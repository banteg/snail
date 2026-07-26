/*
 * mangled: _Z19RShellInputRegisteriiff
 * demangled: RShellInputRegister(int, int, float, float)
 * address: 00029fb0
 * size: 228
 */

/* RShellInputRegister(int, int, float, float) */

void RShellInputRegister(int param_1,int param_2,float param_3,float param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 in_r2;
  undefined4 in_r3;
  float fVar3;

  if (param_1 == 0) {
    if ((float)RShellInput._20_4_ == 0.0) {
      RShellInput._20_4_ = in_r2;
    }
    RShellInput._28_4_ = param_2 | RShellInput._28_4_;
    if ((float)RShellInput._24_4_ == 0.0) {
      RShellInput._24_4_ = in_r3;
    }
  }
  else {
    iVar1 = param_1 * 0x40;
    *(undefined4 *)(RShellInput + iVar1 + 0x14) = in_r2;
    uVar2 = RShellInput._20_4_;
    *(undefined4 *)(RShellInput + iVar1 + 0x18) = in_r3;
    *(int *)(RShellInput + iVar1 + 0x1c) = param_2;
    if (0.15 < (float)uVar2) {
      fVar3 = ((float)uVar2 - 0.15) / 0.85;
    }
    else if ((float)uVar2 <= -0.15) {
      fVar3 = -(-(float)uVar2 - 0.15) / 0.85;
    }
    else {
      fVar3 = 0.0;
    }
    RShellMusicCurrent._24_4_ = fVar3 * 320.0 + 320.0;
    if ((param_2 & 0xf0U) == 0) {
      RShellMusicCurrent._12_4_ = RShellMusicCurrent._12_4_ & 0xffffbfff;
    }
    else {
      RShellMusicCurrent._12_4_ = RShellMusicCurrent._12_4_ | 0x4000;
    }
  }
  return;
}
