/*
 * mangled: _ZN5cRGUI2AIEv
 * demangled: cRGUI::AI()
 * address: 00064584
 * size: 1452
 */

/* cRGUI::AI() */

undefined4 __thiscall cRGUI::AI(cRGUI *this)

{
  char *pcVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  float fVar5;

  cRSubGame::HideScores(*(cRSubGame **)this);
  if (*(float *)(Game + 0x3c) == *(float *)(Game + 0x44)) {
    iVar4 = *(int *)this;
    iVar3 = *(int *)(iVar4 + 0x60);
  }
  else {
    UnInit(this);
    Init(this);
    iVar4 = *(int *)this;
    iVar3 = *(int *)(iVar4 + 0x60);
  }
  if (iVar3 == 1) {
    cRBorder::RePosition(*(cRBorder **)(this + 0x10));
    fVar5 = (float)cRBorder::RePosition(*(cRBorder **)(this + 0x24));
    if ((*(uint *)(*(cRBorder **)(this + 0x24) + 0x194) & 0x1000) == 0) {
      fVar5 = (float)cRBorder::SetRight(*(cRBorder **)(this + 0x10),*(cRBorder **)(this + 0x24));
    }
    cRBorderManager::CentreRow
              ((cRBorderManager *)(Game + 0xd14),*(cRBorder **)(this + 0x10),false,fVar5);
    uVar2 = *(uint *)(*(int *)(this + 0x18) + 0x194);
    if ((uVar2 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 0x18) + 0x194) = uVar2 & 0xffffffdf;
      UnInit(this);
      return 3;
    }
    uVar2 = *(uint *)(*(int *)(this + 0x10) + 0x194);
    if ((uVar2 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 0x10) + 0x194) = uVar2 & 0xffffffdf;
      UnInit(this);
      iVar4 = *(int *)this;
      *(undefined4 *)(iVar4 + 0xfd90) = 0;
      cRSubGoldy::ScoreStatsInit((cRSubGoldy *)(iVar4 + 0xfac4));
      return 1;
    }
    gConfig._64_4_ = (undefined4)(*(float *)(*(int *)(this + 0x1c) + 0x170) * 100.0 + 0.1);
    gConfig._72_4_ = (undefined4)(*(float *)(*(int *)(this + 0x20) + 0x170) * 100.0 + 0.1);
    uVar2 = *(uint *)(*(int *)(this + 0x24) + 0x194);
    if ((uVar2 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 0x24) + 0x194) = uVar2 & 0xffffffdf;
      UnInit(this);
      iVar4 = *(int *)this;
      *(undefined4 *)(iVar4 + 0xfd90) = 0;
      cRSubGoldy::ScoreStatsInit((cRSubGoldy *)(iVar4 + 0xfac4));
      iVar3 = *(int *)this;
      iVar4 = 0x49;
      gGroup0[iVar3 + 0x9d618] = 1;
LAB_000647c4:
      cRSubHighScore::MiniLoad((cRSubHighScore *)(gGroup0 + iVar3 + 0x5cdf4),iVar4);
      *(int *)(gGroup0 + *(int *)this + 0x9d61c) = *(int *)this + 0x2f01fc;
      return 1;
    }
  }
  else if (iVar3 == 4) {
    uVar2 = *(uint *)(*(int *)(this + 4) + 0x194);
    if ((uVar2 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 4) + 0x194) = uVar2 & 0xffffffdf;
      iVar3 = *(int *)(iVar4 + 100) + 1;
      *(int *)(iVar4 + 100) = iVar3;
      cRSubTracks::Load((cRSubTracks *)(iVar4 + 0xa0),*(int *)(iVar4 + 0x60),iVar3);
      Rstrcpy((char *)(*(int *)(this + 0xc) + 0x2c4),(char *)(*(int *)this + 0x15a8));
      cRBorder::RePosition(*(cRBorder **)(this + 0xc));
      iVar4 = *(int *)this;
      iVar3 = *(int *)(iVar4 + 0x8c5c);
      pcVar1 = (char *)cRTimeTrial::TimeString
                                 ((cRTimeTrial *)(gGroup0 + iVar4 + 0x9d628),
                                  (cRTime *)
                                  (gGroup0 + iVar4 + (*(int *)(iVar4 + 100) + 0x16) * 0x38 + 0x5ce00
                                  ));
      Rstrcpy((char *)(iVar3 + 0x2c4),pcVar1);
      iVar4 = *(int *)this;
    }
    iVar3 = *(int *)(this + 8);
    uVar2 = *(uint *)(iVar3 + 0x194);
    if ((uVar2 & 0x20) != 0) {
      *(uint *)(iVar3 + 0x194) = uVar2 & 0xffffffdf;
      iVar3 = *(int *)(iVar4 + 100) + -1;
      *(int *)(iVar4 + 100) = iVar3;
      cRSubTracks::Load((cRSubTracks *)(iVar4 + 0xa0),*(int *)(iVar4 + 0x60),iVar3);
      Rstrcpy((char *)(*(int *)(this + 0xc) + 0x2c4),(char *)(*(int *)this + 0x15a8));
      cRBorder::RePosition(*(cRBorder **)(this + 0xc));
      iVar4 = *(int *)this;
      iVar3 = *(int *)(iVar4 + 0x8c5c);
      pcVar1 = (char *)cRTimeTrial::TimeString
                                 ((cRTimeTrial *)(gGroup0 + iVar4 + 0x9d628),
                                  (cRTime *)
                                  (gGroup0 + iVar4 + (*(int *)(iVar4 + 100) + 0x16) * 0x38 + 0x5ce00
                                  ));
      Rstrcpy((char *)(iVar3 + 0x2c4),pcVar1);
      iVar3 = *(int *)(this + 8);
      iVar4 = *(int *)this;
      uVar2 = *(uint *)(iVar3 + 0x194);
    }
    if (*(int *)(iVar4 + 100) == 0) {
      *(uint *)(iVar3 + 0x194) = uVar2 | 0x8000;
    }
    else {
      *(uint *)(iVar3 + 0x194) = uVar2 & 0xffff7fff;
    }
    if (*(int *)(iVar4 + 100) == gConfig._160_4_) {
      *(uint *)(*(int *)(this + 4) + 0x194) = *(uint *)(*(int *)(this + 4) + 0x194) | 0x8000;
    }
    else {
      *(uint *)(*(int *)(this + 4) + 0x194) = *(uint *)(*(int *)(this + 4) + 0x194) & 0xffff7fff;
    }
    if (*(int *)(gGroup0 + iVar4 + (*(int *)(iVar4 + 100) + 0x16) * 0x38 + 0x5cdfc) == 1) {
      cRBorder::UnHideInit(*(cRBorder **)(this + 0x24));
      cRBorder::SetBelow(*(cRBorder **)(this + 0x18),*(cRBorder **)(this + 0x24));
    }
    else {
      cRBorder::HideInit(*(cRBorder **)(this + 0x24));
      cRBorder::SetBelow(*(cRBorder **)(this + 0x18),*(cRBorder **)(this + 0x10));
    }
    iVar4 = *(int *)(this + 0x18);
    uVar2 = *(uint *)(iVar4 + 0x194);
    if ((uVar2 & 0x20) != 0) {
LAB_00064690:
      *(uint *)(iVar4 + 0x194) = uVar2 & 0xffffffdf;
      UnInit(this);
      return 3;
    }
    iVar4 = *(int *)(this + 0x10);
    uVar2 = *(uint *)(iVar4 + 0x194);
    if ((uVar2 & 0x20) != 0) {
LAB_00064678:
      *(uint *)(iVar4 + 0x194) = uVar2 & 0xffffffdf;
      UnInit(this);
      return 1;
    }
    uVar2 = *(uint *)(*(int *)(this + 0x24) + 0x194);
    if ((uVar2 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 0x24) + 0x194) = uVar2 & 0xffffffdf;
      UnInit(this);
      iVar3 = *(int *)this;
      iVar4 = *(int *)(iVar3 + 100);
      gGroup0[iVar3 + 0x9d618] = 1;
      iVar4 = iVar4 + 0x16;
      goto LAB_000647c4;
    }
  }
  else if (iVar3 == 0) {
    uVar2 = *(uint *)(*(int *)(this + 4) + 0x194);
    if ((uVar2 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 4) + 0x194) = uVar2 & 0xffffffdf;
      iVar3 = *(int *)(iVar4 + 100) + 1;
      *(int *)(iVar4 + 100) = iVar3;
      cRSubTracks::Load((cRSubTracks *)(iVar4 + 0xa0),*(int *)(iVar4 + 0x60),iVar3);
      Rstrcpy((char *)(*(int *)(this + 0xc) + 0x2c4),(char *)(*(int *)this + 0x15a8));
      cRBorder::RePosition(*(cRBorder **)(this + 0xc));
      iVar4 = *(int *)this;
    }
    iVar3 = *(int *)(this + 8);
    uVar2 = *(uint *)(iVar3 + 0x194);
    if ((uVar2 & 0x20) != 0) {
      *(uint *)(iVar3 + 0x194) = uVar2 & 0xffffffdf;
      iVar3 = *(int *)(iVar4 + 100) + -1;
      *(int *)(iVar4 + 100) = iVar3;
      cRSubTracks::Load((cRSubTracks *)(iVar4 + 0xa0),*(int *)(iVar4 + 0x60),iVar3);
      Rstrcpy((char *)(*(int *)(this + 0xc) + 0x2c4),(char *)(*(int *)this + 0x15a8));
      cRBorder::RePosition(*(cRBorder **)(this + 0xc));
      iVar3 = *(int *)(this + 8);
      iVar4 = *(int *)this;
      uVar2 = *(uint *)(iVar3 + 0x194);
    }
    if (*(int *)(iVar4 + 100) == 0) {
      *(uint *)(iVar3 + 0x194) = uVar2 | 0x8000;
    }
    else {
      *(uint *)(iVar3 + 0x194) = uVar2 & 0xffff7fff;
    }
    if (*(int *)(iVar4 + 100) == gConfig._160_4_) {
      *(uint *)(*(int *)(this + 4) + 0x194) = *(uint *)(*(int *)(this + 4) + 0x194) | 0x8000;
    }
    else {
      *(uint *)(*(int *)(this + 4) + 0x194) = *(uint *)(*(int *)(this + 4) + 0x194) & 0xffff7fff;
    }
    iVar4 = *(int *)(this + 0x18);
    uVar2 = *(uint *)(iVar4 + 0x194);
    if ((uVar2 & 0x20) != 0) goto LAB_00064690;
    iVar4 = *(int *)(this + 0x10);
    uVar2 = *(uint *)(iVar4 + 0x194);
    if ((uVar2 & 0x20) != 0) goto LAB_00064678;
  }
  return 0;
}
