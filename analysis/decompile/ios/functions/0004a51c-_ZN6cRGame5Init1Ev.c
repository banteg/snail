/*
 * mangled: _ZN6cRGame5Init1Ev
 * demangled: cRGame::Init1()
 * address: 0004a51c
 * size: 472
 */

/* cRGame::Init1() */

void __thiscall cRGame::Init1(cRGame *this)

{
  undefined *puVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  cRLandscapeManager *this_00;

  cRSound::Init((cRSound *)PTR__gRSound_001b61e0,(cRSoundBank *)&_SFXBank);
  cRVoiceManager::Init((cRVoiceManager *)PTR__gVoiceManager_001b61d8);
  *(undefined4 *)(this + 0xbd0) = 0;
  _ZBufferIndex = 0;
  iVar3 = 4;
  do {
    *(undefined4 *)((int)&_ZBufferIndex + iVar3) = 0;
    iVar3 = iVar3 + 4;
  } while (iVar3 != 0x400);
  *(undefined4 *)(this + 0x368) = 0;
  *(undefined4 *)(this + 0x36c) = 0x1000007;
  *(cRGame **)(this + 900) = this + 0x468;
  *(undefined4 *)(this + 0x370) = 0;
  *(undefined4 *)(this + 0x374) = 0;
  *(undefined4 *)(this + 0x378) = 0x3f800000;
  *(undefined4 *)(this + 0x37c) = 0x3f800000;
  this[1000] = (cRGame)0x0;
  wprintf("GameInit1\n");
  uVar2 = *(uint *)(this + 0x3f8);
  iVar3 = *(int *)PTR__Game_001b60b8;
  if ((uVar2 & 0x200) == 0) {
    if (*(int *)(iVar3 + 0x35c) == 0) {
      *(cRGame **)(iVar3 + 0x35c) = this + 0x3f4;
      *(undefined4 *)(this + 0x3fc) = 0;
      *(undefined4 *)(this + 0x400) = 0;
    }
    else {
      *(cRGame **)(*(int *)(iVar3 + 0x35c) + 8) = this + 0x3f4;
      *(int *)(*(int *)(*(int *)(iVar3 + 0x35c) + 8) + 0xc) = *(int *)(iVar3 + 0x35c);
      iVar4 = *(int *)(*(int *)(iVar3 + 0x35c) + 8);
      *(int *)(iVar3 + 0x35c) = iVar4;
      *(undefined4 *)(iVar4 + 8) = 0;
    }
    *(uint *)(this + 0x3f8) = uVar2 | 0x200;
  }
  else {
    RShellError("List ADD");
  }
  *(undefined4 *)(this + 0x520) = 0;
  *(undefined4 *)(this + 0x524) = 0x39bf9cd1;
  tMatrix::Identity((tMatrix *)(this + 0x420));
  *(undefined4 *)(this + 0x51c) = 0x42180000;
  tMatrix::Identity((tMatrix *)(this + 0x494));
  tMatrix::Invert((tMatrix *)(this + 0x4dc),(tMatrix *)(this + 0x420));
  puVar1 = PTR__gSegmentIndex_001b61ec;
  *(undefined4 *)PTR__gSegmentIndex_001b61ec = 0;
  iVar3 = 4;
  do {
    *(undefined4 *)(puVar1 + iVar3) = 0;
    iVar3 = iVar3 + 4;
  } while (iVar3 != 0x170);
  cRDirectX::Init((cRDirectX *)(this + 0x47ad0));
  wprintf("!!!Import Segments - START\n");
  this_00 = (cRLandscapeManager *)(this + 0x3593d8);
  cRSMTracks::Import((cRSMTracks *)(this + 0x35cab0));
  wprintf("!!!Import Segments - STOP\n");
  cRLandscapeManager::Open(this_00);
  cRLandscapeManager::Import(this_00,"Starmap.txt");
  cRLandscapeManager::Import(this_00,"Starmappro.txt");
  cRLandscapeManager::Import(this_00,"Splash.txt");
  cRLandscapeManager::Import(this_00,"Help.txt");
  return;
}
