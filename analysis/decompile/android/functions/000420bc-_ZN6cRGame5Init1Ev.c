/*
 * mangled: _ZN6cRGame5Init1Ev
 * demangled: cRGame::Init1()
 * address: 000420bc
 * size: 328
 */

/* cRGame::Init1() */

void __thiscall cRGame::Init1(cRGame *this)

{
  int iVar1;
  int iVar2;
  cRLandscapeManager *this_00;

  iVar1 = 0;
  iVar2 = 0;
  *(undefined4 *)(this + 0xbd0) = 0;
  do {
    *(undefined4 *)(ZBufferIndex + iVar1) = 0;
    iVar1 = iVar1 + 4;
  } while (iVar1 != 0x400);
  *(undefined4 *)(this + 0x36c) = 0x1000007;
  *(cRGame **)(this + 900) = this + 0x468;
  *(undefined4 *)(this + 0x374) = 0;
  *(undefined4 *)(this + 0x370) = 0;
  *(undefined4 *)(this + 0x368) = 0;
  this[1000] = (cRGame)0x0;
  *(undefined4 *)(this + 0x37c) = 0x3f800000;
  *(undefined4 *)(this + 0x378) = 0x3f800000;
  wprintf("GameInit1\n");
  cLinkedList<cRBod>::Add((cLinkedList<cRBod> *)(Game + 0x358),(cRBod *)(this + 0x3f4));
  cROverlay::Init((cROverlay *)(this + 0x3f4));
  do {
    *(undefined4 *)(gSegmentIndex + iVar2) = 0;
    iVar2 = iVar2 + 4;
  } while (iVar2 != 0x170);
  cRDirectX::Init((cRDirectX *)(this + 0x47ad0));
  this_00 = (cRLandscapeManager *)(this + 0x3873f4);
  wprintf("!!!Import Segments - START\n");
  cRSMTracks::Import((cRSMTracks *)(this + 0x38aacc));
  wprintf("!!!Import Segments - STOP\n");
  cRLandscapeManager::Open(this_00);
  cRLandscapeManager::Import(this_00,"Starmap.txt");
  cRLandscapeManager::Import(this_00,"Starmappro.txt");
  cRLandscapeManager::Import(this_00,"Splash.txt");
  cRLandscapeManager::Import(this_00,"Help.txt");
  return;
}
