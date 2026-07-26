/*
 * mangled: _ZN5cRGUI2AIEv
 * demangled: cRGUI::AI()
 * address: 00064600
 * size: 1448
 */

/* cRGUI::AI() */

undefined4 __thiscall cRGUI::AI(cRGUI *this)

{
  undefined *puVar1;
  char *pcVar2;
  int iVar3;
  uint uVar4;
  int iVar5;

  cRSubGame::HideScores(*(cRSubGame **)this);
  puVar1 = PTR__Game_001b60b8;
  if (*(float *)(*(int *)PTR__Game_001b60b8 + 0x3c) == *(float *)(*(int *)PTR__Game_001b60b8 + 0x44)
     ) {
    iVar5 = *(int *)(*(int *)this + 0x58);
  }
  else {
    UnInit(this);
    Init(this);
    iVar5 = *(int *)(*(int *)this + 0x58);
  }
  if (iVar5 == 1) {
    cRBorder::RePosition(*(cRBorder **)(this + 0x10));
    cRBorder::RePosition(*(cRBorder **)(this + 0x24));
    if ((*(uint *)(*(cRBorder **)(this + 0x24) + 0x194) & 0x1000) == 0) {
      cRBorder::SetRight(*(cRBorder **)(this + 0x10),*(cRBorder **)(this + 0x24));
    }
    cRBorderManager::CentreRow
              ((cRBorderManager *)(*(int *)puVar1 + 0xd14),*(cRBorder **)(this + 0x10),false,100.0);
    puVar1 = PTR__gConfig_001b60d4;
    iVar5 = *(int *)(this + 0x18);
    uVar4 = *(uint *)(iVar5 + 0x194);
    if ((uVar4 & 0x20) != 0) {
LAB_000646f0:
      *(uint *)(iVar5 + 0x194) = uVar4 & 0xffffffdf;
      UnInit(this);
      return 3;
    }
    uVar4 = *(uint *)(*(int *)(this + 0x10) + 0x194);
    if ((uVar4 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 0x10) + 0x194) = uVar4 & 0xffffffdf;
      UnInit(this);
      *(undefined4 *)(*(int *)this + 0xf714) = 0;
      cRSubGoldy::ScoreStatsInit((cRSubGoldy *)(FontType + *(int *)this + 4));
      return 1;
    }
    *(int *)(PTR__gConfig_001b60d4 + 0x40) =
         (int)(*(float *)(*(int *)(this + 0x1c) + 0x170) * 100.0 + 0.1);
    *(int *)(puVar1 + 0x48) = (int)(*(float *)(*(int *)(this + 0x20) + 0x170) * 100.0 + 0.1);
    uVar4 = *(uint *)(*(int *)(this + 0x24) + 0x194);
    if ((uVar4 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 0x24) + 0x194) = uVar4 & 0xffffffdf;
      UnInit(this);
      *(undefined4 *)(*(int *)this + 0xf714) = 0;
      cRSubGoldy::ScoreStatsInit((cRSubGoldy *)(FontType + *(int *)this + 4));
      iVar3 = 0x49;
      (&DAT_002e09cc)[*(int *)this] = 1;
      iVar5 = *(int *)this;
LAB_00064940:
      cRSubHighScore::MiniLoad((cRSubHighScore *)(&DAT_002a01a8 + iVar5),iVar3);
      *(int *)(&DAT_002e09d0 + *(int *)this) = *(int *)this + 0x2c0f08;
      return 1;
    }
  }
  else if (iVar5 == 4) {
    uVar4 = *(uint *)(*(int *)(this + 4) + 0x194);
    if ((uVar4 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 4) + 0x194) = uVar4 & 0xffffffdf;
      *(int *)(*(int *)this + 0x5c) = *(int *)(*(int *)this + 0x5c) + 1;
      iVar5 = *(int *)this;
      cRSubTracks::Load((cRSubTracks *)(iVar5 + 0x98),*(int *)(iVar5 + 0x58),*(int *)(iVar5 + 0x5c))
      ;
      Rstrcpy((char *)(*(int *)(this + 0xc) + 0x2c4),section_0000125c.sectname + *(int *)this + 0xc)
      ;
      cRBorder::RePosition(*(cRBorder **)(this + 0xc));
      iVar3 = *(int *)this;
      iVar5 = *(int *)(iVar3 + 0x85e4);
      pcVar2 = (char *)cRTimeTrial::TimeString
                                 ((cRTimeTrial *)(iVar3 + 0x2e09dc),
                                  (cRTime *)(&DAT_002a0684 + iVar3 + *(int *)(iVar3 + 0x5c) * 0x38))
      ;
      Rstrcpy((char *)(iVar5 + 0x2c4),pcVar2);
    }
    iVar5 = *(int *)(this + 8);
    if ((*(uint *)(iVar5 + 0x194) & 0x20) != 0) {
      *(uint *)(iVar5 + 0x194) = *(uint *)(iVar5 + 0x194) & 0xffffffdf;
      *(int *)(*(int *)this + 0x5c) = *(int *)(*(int *)this + 0x5c) + -1;
      iVar5 = *(int *)this;
      cRSubTracks::Load((cRSubTracks *)(iVar5 + 0x98),*(int *)(iVar5 + 0x58),*(int *)(iVar5 + 0x5c))
      ;
      Rstrcpy((char *)(*(int *)(this + 0xc) + 0x2c4),section_0000125c.sectname + *(int *)this + 0xc)
      ;
      cRBorder::RePosition(*(cRBorder **)(this + 0xc));
      iVar3 = *(int *)this;
      iVar5 = *(int *)(iVar3 + 0x85e4);
      pcVar2 = (char *)cRTimeTrial::TimeString
                                 ((cRTimeTrial *)(iVar3 + 0x2e09dc),
                                  (cRTime *)(&DAT_002a0684 + iVar3 + *(int *)(iVar3 + 0x5c) * 0x38))
      ;
      Rstrcpy((char *)(iVar5 + 0x2c4),pcVar2);
      iVar5 = *(int *)(this + 8);
    }
    if (*(int *)(*(int *)this + 0x5c) == 0) {
      *(uint *)(iVar5 + 0x194) = *(uint *)(iVar5 + 0x194) | 0x8000;
    }
    else {
      *(uint *)(iVar5 + 0x194) = *(uint *)(iVar5 + 0x194) & 0xffff7fff;
    }
    if (*(int *)(*(int *)this + 0x5c) == *(int *)(PTR__gConfig_001b60d4 + 0xa0)) {
      *(uint *)(*(int *)(this + 4) + 0x194) = *(uint *)(*(int *)(this + 4) + 0x194) | 0x8000;
    }
    else {
      *(uint *)(*(int *)(this + 4) + 0x194) = *(uint *)(*(int *)(this + 4) + 0x194) & 0xffff7fff;
    }
    if (*(int *)(&DAT_002a0680 + *(int *)(*(int *)this + 0x5c) * 0x38 + *(int *)this) == 1) {
      cRBorder::UnHideInit(*(cRBorder **)(this + 0x24));
      cRBorder::SetBelow(*(cRBorder **)(this + 0x18),*(cRBorder **)(this + 0x24));
    }
    else {
      cRBorder::HideInit(*(cRBorder **)(this + 0x24));
      cRBorder::SetBelow(*(cRBorder **)(this + 0x18),*(cRBorder **)(this + 0x10));
    }
    iVar5 = *(int *)(this + 0x18);
    uVar4 = *(uint *)(iVar5 + 0x194);
    if ((uVar4 & 0x20) != 0) goto LAB_000646f0;
    iVar5 = *(int *)(this + 0x10);
    uVar4 = *(uint *)(iVar5 + 0x194);
    if ((uVar4 & 0x20) != 0) {
LAB_00064b5c:
      *(uint *)(iVar5 + 0x194) = uVar4 & 0xffffffdf;
      UnInit(this);
      return 1;
    }
    uVar4 = *(uint *)(*(int *)(this + 0x24) + 0x194);
    if ((uVar4 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 0x24) + 0x194) = uVar4 & 0xffffffdf;
      UnInit(this);
      (&DAT_002e09cc)[*(int *)this] = 1;
      iVar5 = *(int *)this;
      iVar3 = *(int *)(iVar5 + 0x5c) + 0x16;
      goto LAB_00064940;
    }
  }
  else if (iVar5 == 0) {
    uVar4 = *(uint *)(*(int *)(this + 4) + 0x194);
    if ((uVar4 & 0x20) != 0) {
      *(uint *)(*(int *)(this + 4) + 0x194) = uVar4 & 0xffffffdf;
      *(int *)(*(int *)this + 0x5c) = *(int *)(*(int *)this + 0x5c) + 1;
      iVar5 = *(int *)this;
      cRSubTracks::Load((cRSubTracks *)(iVar5 + 0x98),*(int *)(iVar5 + 0x58),*(int *)(iVar5 + 0x5c))
      ;
      Rstrcpy((char *)(*(int *)(this + 0xc) + 0x2c4),section_0000125c.sectname + *(int *)this + 0xc)
      ;
      cRBorder::RePosition(*(cRBorder **)(this + 0xc));
    }
    iVar5 = *(int *)(this + 8);
    if ((*(uint *)(iVar5 + 0x194) & 0x20) != 0) {
      *(uint *)(iVar5 + 0x194) = *(uint *)(iVar5 + 0x194) & 0xffffffdf;
      *(int *)(*(int *)this + 0x5c) = *(int *)(*(int *)this + 0x5c) + -1;
      iVar5 = *(int *)this;
      cRSubTracks::Load((cRSubTracks *)(iVar5 + 0x98),*(int *)(iVar5 + 0x58),*(int *)(iVar5 + 0x5c))
      ;
      Rstrcpy((char *)(*(int *)(this + 0xc) + 0x2c4),section_0000125c.sectname + *(int *)this + 0xc)
      ;
      cRBorder::RePosition(*(cRBorder **)(this + 0xc));
      iVar5 = *(int *)(this + 8);
    }
    if (*(int *)(*(int *)this + 0x5c) == 0) {
      *(uint *)(iVar5 + 0x194) = *(uint *)(iVar5 + 0x194) | 0x8000;
    }
    else {
      *(uint *)(iVar5 + 0x194) = *(uint *)(iVar5 + 0x194) & 0xffff7fff;
    }
    if (*(int *)(*(int *)this + 0x5c) == *(int *)(PTR__gConfig_001b60d4 + 0xa0)) {
      *(uint *)(*(int *)(this + 4) + 0x194) = *(uint *)(*(int *)(this + 4) + 0x194) | 0x8000;
    }
    else {
      *(uint *)(*(int *)(this + 4) + 0x194) = *(uint *)(*(int *)(this + 4) + 0x194) & 0xffff7fff;
    }
    iVar5 = *(int *)(this + 0x18);
    uVar4 = *(uint *)(iVar5 + 0x194);
    if ((uVar4 & 0x20) != 0) goto LAB_000646f0;
    iVar5 = *(int *)(this + 0x10);
    uVar4 = *(uint *)(iVar5 + 0x194);
    if ((uVar4 & 0x20) != 0) goto LAB_00064b5c;
  }
  return 0;
}
