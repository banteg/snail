/*
 * mangled: _ZN5cRGUI2AIEv
 * demangled: cRGUI::AI()
 * address: 00064584
 * size: 1452
 */

/* cRGUI::AI() */

undefined4 __thiscall cRGUI::AI(cRGUI *this)

{
  float fVar1;
  char *pcVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  float fVar8;

  iVar5 = DAT_00064af4;
  iVar7 = DAT_00064af0 + 0x645a0;
  cRSubGame::HideScores(*(cRSubGame **)this);
  iVar6 = **(int **)(iVar7 + iVar5);
  if (*(float *)(iVar6 + 0x3c) == *(float *)(iVar6 + 0x44)) {
    iVar6 = *(int *)this;
    iVar4 = *(int *)(iVar6 + 0x60);
  }
  else {
    UnInit(this);
    Init(this);
    iVar6 = *(int *)this;
    iVar4 = *(int *)(iVar6 + 0x60);
  }
  if (iVar4 == 1) {
    cRBorder::RePosition(*(cRBorder **)(this + 0x10));
    fVar8 = (float)cRBorder::RePosition(*(cRBorder **)(this + 0x24));
    if ((*(uint *)(*(cRBorder **)(this + 0x24) + 0x194) & 0x1000) == 0) {
      fVar8 = (float)cRBorder::SetRight(*(cRBorder **)(this + 0x10),*(cRBorder **)(this + 0x24));
    }
    fVar1 = DAT_00064ae8;
    cRBorderManager::CentreRow
              ((cRBorderManager *)(**(int **)(iVar7 + iVar5) + 0xd14),*(cRBorder **)(this + 0x10),
               false,fVar8);
    uVar3 = *(uint *)(*(int *)(this + 0x18) + 0x194);
    if ((uVar3 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 0x18) + 0x194) = uVar3 & 0xffffffdf;
      UnInit(this);
      return 3;
    }
    uVar3 = *(uint *)(*(int *)(this + 0x10) + 0x194);
    if ((uVar3 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 0x10) + 0x194) = uVar3 & 0xffffffdf;
      UnInit(this);
      iVar5 = *(int *)this;
      *(undefined4 *)(iVar5 + 0xfd90) = 0;
      cRSubGoldy::ScoreStatsInit((cRSubGoldy *)(iVar5 + 0xfac4));
      return 1;
    }
    iVar5 = *(int *)(this + 0x24);
    fVar8 = DAT_00064aec + fVar1 * *(float *)(*(int *)(this + 0x20) + 0x170);
    iVar6 = *(int *)(iVar7 + DAT_00064af8);
    *(int *)(iVar6 + 0x40) = (int)(DAT_00064aec + fVar1 * *(float *)(*(int *)(this + 0x1c) + 0x170))
    ;
    *(int *)(iVar6 + 0x48) = (int)fVar8;
    uVar3 = *(uint *)(iVar5 + 0x194);
    if ((uVar3 & 0x20) != 0) {
      *(uint *)(iVar5 + 0x194) = uVar3 & 0xffffffdf;
      UnInit(this);
      iVar5 = *(int *)this;
      *(undefined4 *)(iVar5 + 0xfd90) = 0;
      cRSubGoldy::ScoreStatsInit((cRSubGoldy *)(iVar5 + 0xfac4));
      iVar6 = *(int *)this;
      iVar5 = 0x49;
      gGroup0[iVar6 + 0x9d618] = 1;
LAB_000647c4:
      cRSubHighScore::MiniLoad((cRSubHighScore *)(gGroup0 + iVar6 + 0x5cdf4),iVar5);
      *(int *)(gGroup0 + *(int *)this + 0x9d61c) = *(int *)this + 0x2f01fc;
      return 1;
    }
  }
  else if (iVar4 == 4) {
    uVar3 = *(uint *)(*(int *)(this + 4) + 0x194);
    if ((uVar3 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 4) + 0x194) = uVar3 & 0xffffffdf;
      iVar5 = *(int *)(iVar6 + 100) + 1;
      *(int *)(iVar6 + 100) = iVar5;
      cRSubTracks::Load((cRSubTracks *)(iVar6 + 0xa0),*(int *)(iVar6 + 0x60),iVar5);
      Rstrcpy((char *)(*(int *)(this + 0xc) + 0x2c4),(char *)(*(int *)this + 0x15a8));
      cRBorder::RePosition(*(cRBorder **)(this + 0xc));
      iVar5 = *(int *)this;
      iVar6 = *(int *)(iVar5 + 0x8c5c);
      pcVar2 = (char *)cRTimeTrial::TimeString
                                 ((cRTimeTrial *)(gGroup0 + iVar5 + 0x9d628),
                                  (cRTime *)
                                  (gGroup0 + iVar5 + (*(int *)(iVar5 + 100) + 0x16) * 0x38 + 0x5ce00
                                  ));
      Rstrcpy((char *)(iVar6 + 0x2c4),pcVar2);
      iVar6 = *(int *)this;
    }
    iVar5 = *(int *)(this + 8);
    uVar3 = *(uint *)(iVar5 + 0x194);
    if ((uVar3 & 0x20) != 0) {
      *(uint *)(iVar5 + 0x194) = uVar3 & 0xffffffdf;
      iVar5 = *(int *)(iVar6 + 100) + -1;
      *(int *)(iVar6 + 100) = iVar5;
      cRSubTracks::Load((cRSubTracks *)(iVar6 + 0xa0),*(int *)(iVar6 + 0x60),iVar5);
      Rstrcpy((char *)(*(int *)(this + 0xc) + 0x2c4),(char *)(*(int *)this + 0x15a8));
      cRBorder::RePosition(*(cRBorder **)(this + 0xc));
      iVar5 = *(int *)this;
      iVar6 = *(int *)(iVar5 + 0x8c5c);
      pcVar2 = (char *)cRTimeTrial::TimeString
                                 ((cRTimeTrial *)(gGroup0 + iVar5 + 0x9d628),
                                  (cRTime *)
                                  (gGroup0 + iVar5 + (*(int *)(iVar5 + 100) + 0x16) * 0x38 + 0x5ce00
                                  ));
      Rstrcpy((char *)(iVar6 + 0x2c4),pcVar2);
      iVar5 = *(int *)(this + 8);
      iVar6 = *(int *)this;
      uVar3 = *(uint *)(iVar5 + 0x194);
    }
    if (*(int *)(iVar6 + 100) == 0) {
      *(uint *)(iVar5 + 0x194) = uVar3 | 0x8000;
    }
    else {
      *(uint *)(iVar5 + 0x194) = uVar3 & 0xffff7fff;
    }
    if (*(int *)(iVar6 + 100) == *(int *)(*(int *)(iVar7 + DAT_00064af8) + 0xa0)) {
      *(uint *)(*(int *)(this + 4) + 0x194) = *(uint *)(*(int *)(this + 4) + 0x194) | 0x8000;
    }
    else {
      *(uint *)(*(int *)(this + 4) + 0x194) = *(uint *)(*(int *)(this + 4) + 0x194) & 0xffff7fff;
    }
    if (*(int *)(gGroup0 + iVar6 + (*(int *)(iVar6 + 100) + 0x16) * 0x38 + 0x5cdfc) == 1) {
      cRBorder::UnHideInit(*(cRBorder **)(this + 0x24));
      cRBorder::SetBelow(*(cRBorder **)(this + 0x18),*(cRBorder **)(this + 0x24));
    }
    else {
      cRBorder::HideInit(*(cRBorder **)(this + 0x24));
      cRBorder::SetBelow(*(cRBorder **)(this + 0x18),*(cRBorder **)(this + 0x10));
    }
    iVar5 = *(int *)(this + 0x18);
    uVar3 = *(uint *)(iVar5 + 0x194);
    if ((uVar3 & 0x20) != 0) {
LAB_00064690:
      *(uint *)(iVar5 + 0x194) = uVar3 & 0xffffffdf;
      UnInit(this);
      return 3;
    }
    iVar5 = *(int *)(this + 0x10);
    uVar3 = *(uint *)(iVar5 + 0x194);
    if ((uVar3 & 0x20) != 0) {
LAB_00064678:
      *(uint *)(iVar5 + 0x194) = uVar3 & 0xffffffdf;
      UnInit(this);
      return 1;
    }
    uVar3 = *(uint *)(*(int *)(this + 0x24) + 0x194);
    if ((uVar3 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 0x24) + 0x194) = uVar3 & 0xffffffdf;
      UnInit(this);
      iVar6 = *(int *)this;
      iVar5 = *(int *)(iVar6 + 100);
      gGroup0[iVar6 + 0x9d618] = 1;
      iVar5 = iVar5 + 0x16;
      goto LAB_000647c4;
    }
  }
  else if (iVar4 == 0) {
    uVar3 = *(uint *)(*(int *)(this + 4) + 0x194);
    if ((uVar3 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 4) + 0x194) = uVar3 & 0xffffffdf;
      iVar5 = *(int *)(iVar6 + 100) + 1;
      *(int *)(iVar6 + 100) = iVar5;
      cRSubTracks::Load((cRSubTracks *)(iVar6 + 0xa0),*(int *)(iVar6 + 0x60),iVar5);
      Rstrcpy((char *)(*(int *)(this + 0xc) + 0x2c4),(char *)(*(int *)this + 0x15a8));
      cRBorder::RePosition(*(cRBorder **)(this + 0xc));
      iVar6 = *(int *)this;
    }
    iVar5 = *(int *)(this + 8);
    uVar3 = *(uint *)(iVar5 + 0x194);
    if ((uVar3 & 0x20) != 0) {
      *(uint *)(iVar5 + 0x194) = uVar3 & 0xffffffdf;
      iVar5 = *(int *)(iVar6 + 100) + -1;
      *(int *)(iVar6 + 100) = iVar5;
      cRSubTracks::Load((cRSubTracks *)(iVar6 + 0xa0),*(int *)(iVar6 + 0x60),iVar5);
      Rstrcpy((char *)(*(int *)(this + 0xc) + 0x2c4),(char *)(*(int *)this + 0x15a8));
      cRBorder::RePosition(*(cRBorder **)(this + 0xc));
      iVar5 = *(int *)(this + 8);
      iVar6 = *(int *)this;
      uVar3 = *(uint *)(iVar5 + 0x194);
    }
    if (*(int *)(iVar6 + 100) == 0) {
      *(uint *)(iVar5 + 0x194) = uVar3 | 0x8000;
    }
    else {
      *(uint *)(iVar5 + 0x194) = uVar3 & 0xffff7fff;
    }
    if (*(int *)(iVar6 + 100) == *(int *)(*(int *)(iVar7 + DAT_00064af8) + 0xa0)) {
      *(uint *)(*(int *)(this + 4) + 0x194) = *(uint *)(*(int *)(this + 4) + 0x194) | 0x8000;
    }
    else {
      *(uint *)(*(int *)(this + 4) + 0x194) = *(uint *)(*(int *)(this + 4) + 0x194) & 0xffff7fff;
    }
    iVar5 = *(int *)(this + 0x18);
    uVar3 = *(uint *)(iVar5 + 0x194);
    if ((uVar3 & 0x20) != 0) goto LAB_00064690;
    iVar5 = *(int *)(this + 0x10);
    uVar3 = *(uint *)(iVar5 + 0x194);
    if ((uVar3 & 0x20) != 0) goto LAB_00064678;
  }
  return 0;
}
