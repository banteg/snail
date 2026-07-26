/*
 * mangled: _ZN6cRGame5Init0Ev
 * demangled: cRGame::Init0()
 * address: 0004a230
 * size: 420
 */

/* cRGame::Init0() */

void __thiscall cRGame::Init0(cRGame *this)

{
  int iVar1;
  float extraout_s0;
  float fVar2;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  tColour atStack_30 [16];

  wprintf("GameInit0\n");
  tColour::tColour(atStack_30);
  cRSound::Init((cRSound *)&gRSound,(cRSoundBank *)&gSFXBank);
  cRVoiceManager::Init((cRVoiceManager *)&gVoiceManager);
  KeyboardInit();
  tColour::Set((tColour *)(this + 0x14),extraout_s0,extraout_s1,extraout_s2,extraout_s3);
  this[4] = (cRGame)0x1;
  *(undefined4 *)(this + 0x10) = 0x3da3d70a;
  *(undefined4 *)(this + 8) = 0x42480000;
  *(undefined4 *)(this + 0xc) = 0x42a00000;
  cAccelerometer::Init((cAccelerometer *)(this + 0xbd4));
  *(undefined4 *)(this + 100) = 1;
  *(undefined4 *)(this + 0x392960) = 0;
  *(undefined4 *)(this + 0x3c) = gConfig._200_4_;
  cRFade::Init((cRFade *)(this + 0x24));
  this[0x324] = (cRGame)0x0;
  this[0x718b9] = (cRGame)0x0;
  cRCheat::Init((cRCheat *)&gCheat);
  this[0x4d3dc] = (cRGame)0x0;
  fVar2 = (float)cRSubGame::BlinkRandInit((cRSubGame *)(this + 0x718a0));
  iVar1 = Game + 0x341fdc;
  *(int *)(this + 0x381564) = Game + 0x361a9c;
  *(int *)(this + 0x38155c) = iVar1;
  cRSubGame::SetRate((cRSubGame *)(this + 0x718a0),fVar2);
  *(undefined4 *)(this + 0x328) = 2;
  *(undefined4 *)(this + 0x60) = 1;
  cRTextures::Init((cRTextures *)gTextureList,0x5a);
  cRObjects::Init((cRObjects *)gObjectList,1000);
  *(undefined4 *)(this + 0x2d4) = 0;
  *(undefined4 *)(this + 0x35c) = 0;
  *(undefined4 *)(this + 0x2d0) = 0;
  *(cRGame **)(this + 0x360) = this + 0x32c;
  *(undefined4 *)(this + 0x2d8) = 0;
  *(undefined4 *)(this + 0x338) = 0;
  LoadPaths(this);
  return;
}
