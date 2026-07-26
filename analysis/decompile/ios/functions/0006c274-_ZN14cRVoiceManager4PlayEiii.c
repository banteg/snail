/*
 * mangled: _ZN14cRVoiceManager4PlayEiii
 * demangled: cRVoiceManager::Play(int, int, int)
 * address: 0006c274
 * size: 552
 */

/* cRVoiceManager::Play(int, int, int) */

undefined4 __thiscall cRVoiceManager::Play(cRVoiceManager *this,int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;

  if ((uint)param_2 < 2) {
    iVar4 = 0;
    iVar5 = iVar4;
    iVar3 = iVar4;
    iVar6 = iVar4;
    while( true ) {
      iVar2 = iVar3 - iVar6;
      if (*(int *)(this + iVar2) <= iVar5) {
        do {
          iVar4 = iVar4 + 1;
          if (0xf < iVar4) goto LAB_0006c3f8;
          iVar6 = iVar4 * 8;
          iVar3 = iVar4 * 0x20;
          iVar2 = iVar4 * 0x18;
          iVar5 = 0;
        } while (*(int *)(this + iVar2) < 1);
      }
      iVar1 = cRBass::SamplePlaying((int)PTR__gBass_001b61c4);
      if (iVar1 != 0) break;
      iVar5 = iVar5 + 1;
    }
    if (*(int *)(*(int *)(this + iVar2 + 0xc) + iVar5 * 4) != -1) {
      return 0;
    }
LAB_0006c3f8:
    if ((param_2 == 1) && (*(float *)(this + 0x180) < *(float *)(this + 0x184))) {
      return 0;
    }
  }
  else if (param_2 == 2) {
    iVar5 = 0;
    iVar4 = iVar5;
    iVar3 = iVar5;
    iVar6 = iVar5;
    while( true ) {
      iVar2 = iVar3 - iVar6;
      if (*(int *)(this + iVar2) <= iVar4) {
        do {
          iVar5 = iVar5 + 1;
          if (0xf < iVar5) goto LAB_0006c2c4;
          iVar6 = iVar5 * 8;
          iVar3 = iVar5 * 0x20;
          iVar2 = iVar5 * 0x18;
          iVar4 = 0;
        } while (*(int *)(this + iVar2) < 1);
      }
      iVar1 = cRBass::SamplePlaying((int)PTR__gBass_001b61c4);
      if (iVar1 != 0) break;
      iVar4 = iVar4 + 1;
    }
    if (*(int *)(*(int *)(this + iVar2 + 0xc) + iVar4 * 4) != -1) {
      cRBass::StopSample((int)PTR__gBass_001b61c4);
    }
  }
LAB_0006c2c4:
  iVar6 = param_1 * 0x18;
  if (*(float *)(this + iVar6 + 0x10) != 0.0) {
    return 0;
  }
  *(undefined4 *)(this + iVar6 + 0x10) = *(undefined4 *)(this + iVar6 + 0x14);
  if (param_3 == -1) {
    RShellVoicePlay(*(int *)(*(int *)(this + iVar6 + 0xc) +
                            *(int *)(*(int *)(this + iVar6 + 8) + *(int *)(this + iVar6 + 4) * 4) *
                            4),1.0,-1.0,0.0);
    iVar3 = *(int *)(this + iVar6 + 4);
    *(int *)(this + iVar6 + 4) = iVar3 + 1;
    if (iVar3 + 1 == *(int *)(this + iVar6)) {
      *(undefined4 *)(this + iVar6 + 4) = 0;
    }
  }
  else {
    RShellVoicePlay(param_3,1.0,-1.0,0.0);
  }
  if (param_2 - 1U < 2) {
    *(undefined4 *)(this + 0x180) = 0;
    return 1;
  }
  return 1;
}
