/*
 * mangled: _ZN12cRCompletion2AIEv
 * demangled: cRCompletion::AI()
 * address: 00060c0c
 * size: 1024
 */

/* cRCompletion::AI() */

void __thiscall cRCompletion::AI(cRCompletion *this)

{
  cRBorder *this_00;
  int iVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;

  if (*(int *)(this + 0x10) == 0) {
    return;
  }
  if (*(char *)(Game + 0x718b9) != '\0') {
    cRBorder::HideInit(*(cRBorder **)(this + 4));
    cRBorder::HideInit(*(cRBorder **)this);
    cRBorder::HideInit(*(cRBorder **)(this + 8));
    cRBorder::HideInit(*(cRBorder **)(this + 0xc));
    return;
  }
  if (*(int *)(Game + 0x71900) == 4) {
    cRBorder::HideInit(*(cRBorder **)(this + 4));
    cRBorder::HideInit(*(cRBorder **)this);
  }
  else {
    cRBorder::UnHideInit(*(cRBorder **)(this + 4));
    cRBorder::UnHideInit(*(cRBorder **)this);
  }
  switch(*(undefined4 *)(this + 0x10)) {
  case 0:
    return;
  case 1:
    fVar3 = *(float *)(this + 0x28);
    *(float *)(this + 0x28) = fVar3 + *(float *)(this + 0x2c);
    if (1.0 < fVar3 + *(float *)(this + 0x2c)) {
      iVar2 = *(int *)(this + 0x20);
      iVar1 = *(int *)(this + 0x18);
      if (iVar2 < iVar1) {
        *(int *)(this + 0x20) = iVar2 + 1;
        iVar1 = cRSubGame::AddParcel((tVector *)(Game + 0x718a0),(cRSubGoldy *)(Game + 0x851dc));
        iVar2 = *(int *)(iVar1 + 0x48);
        *(undefined4 *)(iVar2 + 0x60) = 0;
        *(undefined4 *)(iVar1 + 0x2c) = 6;
        *(undefined4 *)(iVar2 + 100) = 0;
        iVar2 = *(int *)(this + 0x20);
        iVar1 = *(int *)(this + 0x18);
      }
      *(undefined4 *)(this + 0x28) = 0;
      if (iVar2 == iVar1) {
        if (iVar2 == 0) {
          *(undefined4 *)(this + 0x2c) = 0x3c088889;
          *(undefined4 *)(this + 0x10) = 6;
        }
        else {
          *(undefined4 *)(this + 0x10) = 2;
        }
      }
    }
    break;
  case 2:
    break;
  case 3:
    cRBorder::UnHideInit(*(cRBorder **)(this + 0xc));
    *(undefined4 *)(this + 0x4c) = 0;
    this[0x14] = (cRCompletion)0x0;
    *(undefined4 *)(this + 0x50) = 0x3c088889;
    *(undefined4 *)(this + 0x10) = 4;
    if (*(int *)(this + 0x1c) != 0) {
      cRBorder::UnHideInit(*(cRBorder **)(this + 8));
      if (*(int *)(this + 0x18) == 0) {
        iVar1 = *(int *)(Game + 0x71900);
        if (iVar1 == 1) {
          cRSubGoldy::ScoreAdd((cRSubGoldy *)(Game + 0x81364),5,*(int *)(this + 0x44));
          cRSound::Play((int)&gRSound);
          iVar1 = *(int *)(Game + 0x71900);
        }
      }
      else {
        iVar1 = *(int *)(Game + 0x71900);
      }
      if (iVar1 == 4) {
        cRSound::Play((int)&gRSound);
      }
      goto LAB_00060de0;
    }
    goto LAB_00060e60;
  case 4:
LAB_00060de0:
    if ((*(int *)(this + 0x1c) != 0) &&
       (fVar3 = *(float *)(this + 0x3c), *(float *)(this + 0x3c) = fVar3 + *(float *)(this + 0x40),
       1.0 < fVar3 + *(float *)(this + 0x40))) {
      this_00 = *(cRBorder **)(this + 8);
      *(undefined4 *)(this + 0x3c) = 0;
      if ((*(uint *)(this_00 + 0x194) & 0x1000) == 0) {
        cRBorder::HideInit(this_00);
      }
      else {
        cRBorder::UnHideInit(this_00);
      }
    }
LAB_00060e60:
    if (((*(uint *)(*(int *)(Game + 0x224) + 0x30) & 0x4000) != 0) &&
       (gDirectory[Game + 0x2544] == '\0')) {
      *(undefined4 *)(this + 0x10) = 5;
      cRSound::Play((int)&gRSound);
    }
    break;
  case 5:
    break;
  case 6:
    fVar3 = *(float *)(this + 0x28);
    *(float *)(this + 0x28) = fVar3 + *(float *)(this + 0x2c);
    if (1.0 < fVar3 + *(float *)(this + 0x2c)) {
      *(undefined4 *)(this + 0x10) = 3;
    }
  }
  fVar4 = *(float *)(Game + 0x104);
  fVar3 = *(float *)(Game + 0x108);
  fVar7 = *(float *)(Game + 0x134);
  fVar8 = *(float *)(Game + 0x138);
  fVar10 = *(float *)(Game + 0x114);
  fVar9 = *(float *)(Game + 0x118);
  fVar5 = *(float *)(Game + 0x128);
  fVar6 = *(float *)(Game + 0x124);
  *(float *)(this + 0x30) =
       *(float *)(Game + 0x130) + *(float *)(Game + 0x100) * 7.3 +
       *(float *)(Game + 0x110) + *(float *)(Game + 0x110) + *(float *)(Game + 0x120) * 4.0;
  *(float *)(this + 0x38) = fVar8 + fVar3 * 7.3 + fVar9 + fVar9 + fVar5 * 4.0;
  *(float *)(this + 0x34) = fVar7 + fVar4 * 7.3 + fVar10 + fVar10 + fVar6 * 4.0;
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
