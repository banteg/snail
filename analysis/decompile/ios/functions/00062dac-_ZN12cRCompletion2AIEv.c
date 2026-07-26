/*
 * mangled: _ZN12cRCompletion2AIEv
 * demangled: cRCompletion::AI()
 * address: 00062dac
 * size: 932
 */

/* cRCompletion::AI() */

void __thiscall cRCompletion::AI(cRCompletion *this)

{
  int iVar1;
  cRBorder *this_00;
  int extraout_r1;
  int extraout_r1_00;
  int extraout_r1_01;
  int iVar2;
  int extraout_r1_02;
  int extraout_r1_03;
  int extraout_r1_04;
  int extraout_r1_05;
  int extraout_r1_06;
  int extraout_r1_07;
  int iVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;

  if (*(int *)(this + 0x10) == 0) {
    return;
  }
  iVar3 = *(int *)PTR__Game_001b60b8;
  if (*(char *)(iVar3 + 0x72b8a) != '\0') {
    cRBorder::HideInit(*(cRBorder **)(this + 4));
    cRBorder::HideInit(*(cRBorder **)this);
    cRBorder::HideInit(*(cRBorder **)(this + 8));
    cRBorder::HideInit(*(cRBorder **)(this + 0xc));
    return;
  }
  if (*(int *)(iVar3 + 0x72bd0) == 4) {
    cRBorder::HideInit(*(cRBorder **)(this + 4));
    cRBorder::HideInit(*(cRBorder **)this);
    iVar2 = extraout_r1_05;
  }
  else {
    cRBorder::UnHideInit(*(cRBorder **)(this + 4));
    cRBorder::UnHideInit(*(cRBorder **)this);
    iVar2 = extraout_r1;
  }
  switch(*(undefined4 *)(this + 0x10)) {
  case 0:
    goto switchD_00062e0c_caseD_0;
  case 1:
    fVar7 = *(float *)(this + 0x28);
    *(float *)(this + 0x28) = fVar7 + *(float *)(this + 0x2c);
    if (1.0 < fVar7 + *(float *)(this + 0x2c)) {
      iVar5 = *(int *)(this + 0x20);
      iVar3 = *(int *)(this + 0x18);
      if (iVar5 < iVar3) {
        *(int *)(this + 0x20) = iVar5 + 1;
        iVar3 = cRSubGame::AddParcel
                          ((tVector *)(*(int *)PTR__Game_001b60b8 + 0x72b78),
                           (cRSubGoldy *)(*(int *)PTR__Game_001b60b8 + 0x85e30));
        *(undefined4 *)(iVar3 + 0x2c) = 6;
        iVar3 = *(int *)(iVar3 + 0x48);
        *(undefined4 *)(iVar3 + 100) = 0;
        *(undefined4 *)(iVar3 + 0x60) = 0;
        iVar5 = *(int *)(this + 0x20);
        iVar3 = *(int *)(this + 0x18);
      }
      iVar2 = 0;
      *(undefined4 *)(this + 0x28) = 0;
      if (iVar5 == iVar3) {
        if (iVar5 == 0) {
          *(undefined4 *)(this + 0x10) = 6;
          *(undefined4 *)(this + 0x2c) = 0x3c088889;
        }
        else {
          *(undefined4 *)(this + 0x10) = 2;
        }
      }
    }
    break;
  case 3:
    cRBorder::UnHideInit(*(cRBorder **)(this + 0xc));
    this[0x14] = (cRCompletion)0x0;
    *(undefined4 *)(this + 0x10) = 4;
    iVar2 = extraout_r1_00;
    if (*(int *)(this + 0x1c) != 0) {
      cRBorder::UnHideInit(*(cRBorder **)(this + 8));
      iVar2 = extraout_r1_02;
      if ((*(int *)(this + 0x18) == 0) && (*(int *)(*(int *)PTR__Game_001b60b8 + 0x72bd0) == 1)) {
        cRSubGoldy::ScoreAdd
                  ((cRSubGoldy *)(*(int *)PTR__Game_001b60b8 + 0x81fc0),5,*(int *)(this + 0x44));
        cRSound::Play((cRSound *)PTR__gRSound_001b61e0,0x32);
        iVar2 = extraout_r1_07;
      }
      if (*(int *)(*(int *)PTR__Game_001b60b8 + 0x72bd0) == 4) {
        cRSound::Play((cRSound *)PTR__gRSound_001b61e0,0x32);
        iVar2 = extraout_r1_03;
      }
      goto switchD_00062e0c_caseD_4;
    }
    goto LAB_00062e78;
  case 4:
switchD_00062e0c_caseD_4:
    if ((*(int *)(this + 0x1c) != 0) &&
       (fVar7 = *(float *)(this + 0x3c), *(float *)(this + 0x3c) = fVar7 + *(float *)(this + 0x40),
       1.0 < fVar7 + *(float *)(this + 0x40))) {
      this_00 = *(cRBorder **)(this + 8);
      *(undefined4 *)(this + 0x3c) = 0;
      if ((*(uint *)(this_00 + 0x194) & 0x1000) == 0) {
        cRBorder::HideInit(this_00);
        iVar2 = extraout_r1_06;
      }
      else {
        cRBorder::UnHideInit(this_00);
        iVar2 = extraout_r1_04;
      }
    }
LAB_00062e78:
    iVar3 = *(int *)PTR__Game_001b60b8;
    if (((*(uint *)(*(int *)(iVar3 + 0x224) + 0x30) & 0x4000) != 0) &&
       ((&DAT_00353544)[iVar3] == '\0')) {
      *(undefined4 *)(this + 0x10) = 5;
      cRSound::Play((cRSound *)PTR__gRSound_001b61e0,8);
      iVar2 = extraout_r1_01;
    }
    break;
  case 6:
    fVar7 = *(float *)(this + 0x28);
    *(float *)(this + 0x28) = fVar7 + *(float *)(this + 0x2c);
    if (1.0 < fVar7 + *(float *)(this + 0x2c)) {
      *(undefined4 *)(this + 0x10) = 3;
    }
  }
  iVar5 = *(int *)PTR__Game_001b60b8;
  fVar7 = *(float *)(iVar5 + 0x104);
  fVar11 = *(float *)(iVar5 + 0x134);
  fVar8 = *(float *)(iVar5 + 0x114);
  *(float *)(this + 0x30) =
       *(float *)(iVar5 + 0x130) + *(float *)(iVar5 + 0x100) * 7.3 +
       *(float *)(iVar5 + 0x110) + *(float *)(iVar5 + 0x110) + *(float *)(iVar5 + 0x120) * 4.0;
  fVar9 = *(float *)(iVar5 + 0x108);
  fVar12 = *(float *)(iVar5 + 0x138);
  fVar10 = *(float *)(iVar5 + 0x118);
  *(float *)(this + 0x34) = fVar11 + fVar7 * 7.3 + fVar8 + fVar8 + *(float *)(iVar5 + 0x124) * 4.0;
  iVar6 = *(int *)(this + 0x24);
  if (iVar6 < 10) {
    iVar1 = 0x20;
  }
  else {
    iVar3 = 0x66666667;
    iVar1 = iVar6;
  }
  if (iVar6 < 10) {
    iVar3 = *(int *)(this + 4);
    cVar4 = (char)iVar1;
  }
  else {
    iVar2 = *(int *)(this + 4);
    iVar3 = (int)((ulonglong)((longlong)iVar1 * (longlong)iVar3) >> 0x20);
    cVar4 = ((char)(iVar3 >> 2) - (char)(iVar1 >> 0x1f)) + '0';
  }
  *(float *)(this + 0x38) = fVar12 + fVar9 * 7.3 + fVar10 + fVar10 + *(float *)(iVar5 + 0x128) * 4.0
  ;
  if (iVar6 < 10) {
    *(char *)(iVar3 + 0x2c4) = cVar4;
  }
  else {
    *(char *)(iVar2 + 0x2c4) = cVar4;
  }
  *(char *)(*(int *)(this + 4) + 0x2c5) =
       (char)*(int *)(this + 0x24) + (char)(*(int *)(this + 0x24) / 10) * -10 + '0';
switchD_00062e0c_caseD_0:
  return;
}
