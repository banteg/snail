/*
 * mangled: _ZN6cRGame5Init0Ev
 * demangled: cRGame::Init0()
 * address: 0004a230
 * size: 420
 */

/* cRGame::Init0() */

void __thiscall cRGame::Init0(cRGame *this)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  float extraout_s0;
  float fVar4;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  tColour atStack_30 [16];

  uVar1 = DAT_0004a3d4;
  iVar2 = DAT_0004a3e4 + 0x4a250;
  wprintf((char *)(iVar2 + DAT_0004a3e8));
  tColour::tColour(atStack_30);
  cRSound::Init(*(cRSound **)(iVar2 + DAT_0004a3ec),*(cRSoundBank **)(iVar2 + DAT_0004a3f0));
  cRVoiceManager::Init(*(cRVoiceManager **)(iVar2 + DAT_0004a3f4));
  KeyboardInit();
  tColour::Set((tColour *)(this + 0x14),extraout_s0,extraout_s1,extraout_s2,extraout_s3);
  this[4] = (cRGame)0x1;
  *(undefined4 *)(this + 0x10) = DAT_0004a3d8;
  *(undefined4 *)(this + 8) = DAT_0004a3dc;
  *(undefined4 *)(this + 0xc) = DAT_0004a3e0;
  cAccelerometer::Init((cAccelerometer *)(this + 0xbd4));
  iVar3 = DAT_0004a3f8;
  *(undefined4 *)(this + 100) = 1;
  *(undefined4 *)(this + 0x392960) = 0;
  *(undefined4 *)(this + 0x3c) = *(undefined4 *)(*(int *)(iVar2 + iVar3) + 200);
  cRFade::Init((cRFade *)(this + 0x24));
  this[0x324] = (cRGame)0x0;
  this[0x718b9] = (cRGame)0x0;
  cRCheat::Init(*(cRCheat **)(iVar2 + DAT_0004a3fc));
  this[0x4d3dc] = (cRGame)0x0;
  fVar4 = (float)cRSubGame::BlinkRandInit((cRSubGame *)(this + 0x718a0));
  iVar3 = **(int **)(iVar2 + DAT_0004a400);
  *(int *)(this + 0x381564) = iVar3 + 0x361a9c;
  *(int *)(this + 0x38155c) = iVar3 + 0x341fdc;
  cRSubGame::SetRate((cRSubGame *)(this + 0x718a0),fVar4);
  *(undefined4 *)(this + 0x328) = 2;
  iVar3 = DAT_0004a404;
  *(undefined4 *)(this + 0x60) = 1;
  cRTextures::Init(*(cRTextures **)(iVar2 + iVar3),0x5a);
  cRObjects::Init(*(cRObjects **)(iVar2 + DAT_0004a408),1000);
  *(undefined4 *)(this + 0x2d4) = uVar1;
  *(undefined4 *)(this + 0x35c) = 0;
  *(undefined4 *)(this + 0x2d0) = 0;
  *(cRGame **)(this + 0x360) = this + 0x32c;
  *(undefined4 *)(this + 0x2d8) = 0;
  *(undefined4 *)(this + 0x338) = 0;
  LoadPaths(this);
  return;
}
