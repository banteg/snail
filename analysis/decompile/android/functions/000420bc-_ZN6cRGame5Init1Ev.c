/*
 * mangled: _ZN6cRGame5Init1Ev
 * demangled: cRGame::Init1()
 * address: 000420bc
 * size: 328
 */

/* cRGame::Init1() */

void __thiscall cRGame::Init1(cRGame *this)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  cRLandscapeManager *this_00;
  int iVar6;

  iVar6 = DAT_0004220c + 0x420d4;
  iVar4 = 0;
  iVar5 = 0;
  iVar3 = *(int *)(iVar6 + DAT_00042210);
  *(undefined4 *)(this + 0xbd0) = 0;
  do {
    *(undefined4 *)(iVar3 + iVar4) = 0;
    iVar2 = DAT_00042214;
    iVar4 = iVar4 + 4;
  } while (iVar4 != 0x400);
  *(undefined4 *)(this + 0x36c) = 0x1000007;
  uVar1 = DAT_00042204;
  *(cRGame **)(this + 900) = this + 0x468;
  *(undefined4 *)(this + 0x374) = uVar1;
  *(undefined4 *)(this + 0x370) = uVar1;
  *(undefined4 *)(this + 0x368) = 0;
  uVar1 = DAT_00042208;
  this[1000] = (cRGame)0x0;
  *(undefined4 *)(this + 0x37c) = uVar1;
  *(undefined4 *)(this + 0x378) = uVar1;
  wprintf((char *)(iVar6 + iVar2));
  cLinkedList<cRBod>::Add
            ((cLinkedList<cRBod> *)(**(int **)(iVar6 + DAT_00042218) + 0x358),
             (cRBod *)(this + 0x3f4));
  cROverlay::Init((cROverlay *)(this + 0x3f4));
  iVar3 = *(int *)(iVar6 + DAT_0004221c);
  do {
    *(undefined4 *)(iVar3 + iVar5) = 0;
    iVar5 = iVar5 + 4;
  } while (iVar5 != 0x170);
  cRDirectX::Init((cRDirectX *)(this + 0x47ad0));
  this_00 = (cRLandscapeManager *)(this + 0x3873f4);
  wprintf((char *)(iVar6 + DAT_00042220));
  cRSMTracks::Import((cRSMTracks *)(this + 0x38aacc));
  wprintf((char *)(iVar6 + DAT_00042224));
  cRLandscapeManager::Open(this_00);
  cRLandscapeManager::Import(this_00,(char *)(iVar6 + DAT_00042228));
  cRLandscapeManager::Import(this_00,(char *)(iVar6 + DAT_0004222c));
  cRLandscapeManager::Import(this_00,(char *)(iVar6 + DAT_00042230));
  cRLandscapeManager::Import(this_00,(char *)(iVar6 + DAT_00042234));
  return;
}
