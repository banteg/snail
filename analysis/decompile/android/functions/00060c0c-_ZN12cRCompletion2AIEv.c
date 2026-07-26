/*
 * mangled: _ZN12cRCompletion2AIEv
 * demangled: cRCompletion::AI()
 * address: 00060c0c
 * size: 1024
 */

/* cRCompletion::AI() */

void __thiscall cRCompletion::AI(cRCompletion *this)

{
  float fVar1;
  float fVar2;
  float fVar3;
  undefined4 uVar4;
  cRBorder *this_00;
  int iVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  int iVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;

  iVar6 = DAT_00061024;
  iVar9 = DAT_00061020 + 0x60c28;
  if (*(int *)(this + 0x10) == 0) {
    return;
  }
  if (*(char *)(**(int **)(iVar9 + DAT_00061024) + 0x718b9) != '\0') {
    cRBorder::HideInit(*(cRBorder **)(this + 4));
    cRBorder::HideInit(*(cRBorder **)this);
    cRBorder::HideInit(*(cRBorder **)(this + 8));
    cRBorder::HideInit(*(cRBorder **)(this + 0xc));
    return;
  }
  if (*(int *)(**(int **)(iVar9 + DAT_00061024) + 0x71900) == 4) {
    cRBorder::HideInit(*(cRBorder **)(this + 4));
    cRBorder::HideInit(*(cRBorder **)this);
  }
  else {
    cRBorder::UnHideInit(*(cRBorder **)(this + 4));
    cRBorder::UnHideInit(*(cRBorder **)this);
  }
  fVar1 = DAT_0006100c;
  switch(*(undefined4 *)(this + 0x10)) {
  case 0:
    return;
  case 1:
    fVar13 = *(float *)(this + 0x28);
    *(float *)(this + 0x28) = fVar13 + *(float *)(this + 0x2c);
    if (fVar1 < fVar13 + *(float *)(this + 0x2c)) {
      iVar7 = *(int *)(this + 0x20);
      iVar5 = *(int *)(this + 0x18);
      if (iVar7 < iVar5) {
        piVar8 = *(int **)(iVar9 + iVar6);
        *(int *)(this + 0x20) = iVar7 + 1;
        iVar5 = cRSubGame::AddParcel
                          ((tVector *)(*piVar8 + 0x718a0),(cRSubGoldy *)(*piVar8 + 0x851dc));
        uVar4 = DAT_00061018;
        iVar7 = *(int *)(iVar5 + 0x48);
        *(undefined4 *)(iVar7 + 0x60) = DAT_00061018;
        *(undefined4 *)(iVar5 + 0x2c) = 6;
        *(undefined4 *)(iVar7 + 100) = uVar4;
        iVar7 = *(int *)(this + 0x20);
        iVar5 = *(int *)(this + 0x18);
      }
      *(undefined4 *)(this + 0x28) = DAT_00061018;
      if (iVar7 == iVar5) {
        if (iVar7 == 0) {
          piVar8 = *(int **)(iVar9 + iVar6);
          *(undefined4 *)(this + 0x2c) = DAT_0006101c;
          *(undefined4 *)(this + 0x10) = 6;
          iVar6 = *piVar8;
        }
        else {
          piVar8 = *(int **)(iVar9 + iVar6);
          *(undefined4 *)(this + 0x10) = 2;
          iVar6 = *piVar8;
        }
        goto switchD_00060c74_default;
      }
    }
    break;
  case 2:
    break;
  case 3:
    cRBorder::UnHideInit(*(cRBorder **)(this + 0xc));
    *(undefined4 *)(this + 0x4c) = DAT_00061018;
    uVar4 = DAT_0006101c;
    this[0x14] = (cRCompletion)0x0;
    *(undefined4 *)(this + 0x50) = uVar4;
    *(undefined4 *)(this + 0x10) = 4;
    if (*(int *)(this + 0x1c) != 0) {
      cRBorder::UnHideInit(*(cRBorder **)(this + 8));
      if (*(int *)(this + 0x18) == 0) {
        piVar8 = *(int **)(iVar9 + iVar6);
        iVar5 = *piVar8;
        iVar7 = *(int *)(iVar5 + 0x71900);
        if (iVar7 == 1) {
          cRSubGoldy::ScoreAdd((cRSubGoldy *)(iVar5 + 0x81364),5,*(int *)(this + 0x44));
          cRSound::Play(*(int *)(iVar9 + DAT_00061028));
          iVar7 = *(int *)(*piVar8 + 0x71900);
        }
      }
      else {
        iVar7 = *(int *)(**(int **)(iVar9 + iVar6) + 0x71900);
      }
      if (iVar7 == 4) {
        cRSound::Play(*(int *)(iVar9 + DAT_00061028));
      }
      goto LAB_00060de0;
    }
    goto LAB_00060e60;
  case 4:
LAB_00060de0:
    fVar1 = DAT_0006100c;
    if ((*(int *)(this + 0x1c) != 0) &&
       (fVar13 = *(float *)(this + 0x3c), *(float *)(this + 0x3c) = fVar13 + *(float *)(this + 0x40)
       , fVar1 < fVar13 + *(float *)(this + 0x40))) {
      this_00 = *(cRBorder **)(this + 8);
      *(undefined4 *)(this + 0x3c) = DAT_00061018;
      if ((*(uint *)(this_00 + 0x194) & 0x1000) == 0) {
        cRBorder::HideInit(this_00);
      }
      else {
        cRBorder::UnHideInit(this_00);
      }
    }
LAB_00060e60:
    piVar8 = *(int **)(iVar9 + iVar6);
    iVar6 = *piVar8;
    if (((*(uint *)(*(int *)(iVar6 + 0x224) + 0x30) & 0x4000) != 0) &&
       (gDirectory[iVar6 + 0x2544] == '\0')) {
      *(undefined4 *)(this + 0x10) = 5;
      cRSound::Play(*(int *)(iVar9 + DAT_00061028));
      iVar6 = *piVar8;
    }
    goto switchD_00060c74_default;
  case 5:
    break;
  case 6:
    fVar13 = *(float *)(this + 0x28);
    *(float *)(this + 0x28) = fVar13 + *(float *)(this + 0x2c);
    if (fVar1 < fVar13 + *(float *)(this + 0x2c)) {
      piVar8 = *(int **)(iVar9 + iVar6);
      *(undefined4 *)(this + 0x10) = 3;
      iVar6 = *piVar8;
      goto switchD_00060c74_default;
    }
  }
  iVar6 = **(int **)(iVar9 + iVar6);
switchD_00060c74_default:
  fVar3 = DAT_00061014;
  fVar11 = *(float *)(iVar6 + 0x134);
  fVar12 = *(float *)(iVar6 + 0x138);
  fVar15 = *(float *)(iVar6 + 0x114);
  fVar14 = *(float *)(iVar6 + 0x118);
  fVar10 = *(float *)(iVar6 + 0x124);
  fVar1 = DAT_00061010 * *(float *)(iVar6 + 0x108);
  fVar13 = DAT_00061010 * *(float *)(iVar6 + 0x104);
  fVar2 = DAT_00061014 * *(float *)(iVar6 + 0x128);
  *(float *)(this + 0x30) =
       *(float *)(iVar6 + 0x130) + DAT_00061010 * *(float *)(iVar6 + 0x100) +
       *(float *)(iVar6 + 0x110) + *(float *)(iVar6 + 0x110) +
       DAT_00061014 * *(float *)(iVar6 + 0x120);
  *(float *)(this + 0x38) = fVar12 + fVar1 + fVar14 + fVar14 + fVar2;
  *(float *)(this + 0x34) = fVar11 + fVar13 + fVar15 + fVar15 + fVar3 * fVar10;
  if (*(int *)(this + 0x24) < 10) {
    *(undefined1 *)(*(int *)(this + 4) + 0x2c4) = 0x20;
  }
  else {
    *(char *)(*(int *)(this + 4) + 0x2c4) = (char)(*(int *)(this + 0x24) / 10) + '0';
  }
  *(char *)(*(int *)(this + 4) + 0x2c5) =
       (char)*(int *)(this + 0x24) + (char)(*(int *)(this + 0x24) / 10) * -10 + '0';
  return;
}
