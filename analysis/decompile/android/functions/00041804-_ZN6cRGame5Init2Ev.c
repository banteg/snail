/*
 * mangled: _ZN6cRGame5Init2Ev
 * demangled: cRGame::Init2()
 * address: 00041804
 * size: 1948
 */

/* cRGame::Init2() */

void __thiscall cRGame::Init2(cRGame *this)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  cRSpriteManager *this_00;
  int *piVar4;
  undefined8 uVar5;

  iVar3 = DAT_00041d44 + 0x41820;
  wprintf((char *)(iVar3 + DAT_00041d48));
  *(undefined4 *)(this + 0x71904) = *(undefined4 *)(*(int *)(iVar3 + DAT_00041d4c) + 0xa4);
  cRSubGame::GetSkirtColourRandomOpen((cRSubGame *)(this + 0x718a0));
  cRGUI::Open((cRGUI *)(this + 0x392918));
  cRSplash::Open((cRSplash *)(this + 0x392948));
  cRGalaxy::Open((cRGalaxy *)(this + 0x392964),0);
  cRGalaxy::Open((cRGalaxy *)(this + 0x39b7d0),1);
  cRCameraman::Init((cRCameraman *)(this + 0x8154c));
  cRLogo::Open((cRLogo *)(this + 0x4d4f0));
  cROptions::Apply((bool)((char)this + -0x80));
  cRSMTracks::OpenLevels();
  piVar4 = *(int **)(iVar3 + DAT_00041d50);
  cRLandscapeManager::Import
            ((cRLandscapeManager *)(gSegmentText + *piVar4 + 0x3d8),(char *)(iVar3 + DAT_00041d54));
  cRSubTracks::Init((cRSubTracks *)(this + 0x72ee8),*(cRSubSegmentRaw ***)(iVar3 + DAT_00041d58));
  *(undefined4 *)(this + 0x398) = 1;
  *(undefined4 *)(this + 0x39c) = 0x2000009;
  cRViewport::SetCamera((cRViewport *)(this + 0x394),(cRCamera *)(this + 0x168));
  uVar1 = DAT_00041d40;
  iVar2 = *piVar4;
  *(undefined4 *)(this + 0x3d4) = DAT_00041d40;
  *(undefined4 *)(this + 0x3d0) = uVar1;
  *(undefined4 *)(this + 0x3cc) = 0x400000b;
  *(undefined4 *)(this + 0x3c8) = 2;
  *(undefined4 *)(this + 0x3d8) = 0x3f800000;
  *(cRGame **)(this + 0x3e4) = this + 0x59c;
  *(undefined4 *)(this + 0x3dc) = 0x3f800000;
  *(undefined4 *)(this + 0x220) = 0x2000000;
  this[1000] = (cRGame)0x0;
  cLinkedList<cRBod>::Add((cLinkedList<cRBod> *)(iVar2 + 0x358),(cRBod *)(this + 0x528));
  uVar5 = cROverlay::Init((cROverlay *)(this + 0x528));
  RShellFontLoad((char *)(iVar3 + DAT_00041d5c),2,(float)uVar5,(float)((ulonglong)uVar5 >> 0x20));
  FontMake3D(0);
  FontInit();
  this_00 = *(cRSpriteManager **)(iVar3 + DAT_00041d60);
  cRSpriteManager::Init(this_00);
  cRSpriteManager::LoadSet(this_00,(char *)(iVar3 + DAT_00041d64),2,0x20400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041d68),1,0);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041d6c),3,0x20000);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041d70),6,0x20400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041d74),8,0x20400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041d78),0x51,0x20400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041d7c),0x52,0x400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041d80),0xd,0x400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041d84),0x12,0x400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041d88),0x13,0x400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041d8c),0x2b,0x400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041d90),0x4b,0x400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041d94),0x4c,0x400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041d98),0x4d,0x400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041d9c),0x4e,0x400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041da0),0x4f,0x400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041da4),0x50,0x400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041da8),0x57,0x20400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041dac),0x6a,0x400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041db0),0x6b,0x400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041db4),0x6c,0x400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041db8),0x6d,0x400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041dbc),0x6e,0x400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041dc0),0x66,0x400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041dc4),0x67,0x400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041dc8),0x68,0x400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041dcc),0x69,0x400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041dd0),0x6f,0x400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041dd4),0x70,0x400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041dd8),0x74,0x400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041ddc),0x75,0x400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041de0),0x16,0x400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041de4),0x17,0x400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041de8),0x18,0x400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041dec),0x1a,0x400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041df0),0x1b,0x520);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041df4),0x1c,0x400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041df8),0x1e,0x400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041dfc),0x1f,0x520);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041e00),0x76,0x400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041e04),0x77,0x400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041e08),0x78,0x400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041e0c),0x79,0x400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041e10),0x7a,0x400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041e14),0x7b,0x400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041e18),0x7c,0x400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041e1c),0x7d,0x20400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041e20),0x7e,0x20400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041e24),0x7f,0x20400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041e28),0x80,0x20400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041e2c),0x81,0x20400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041e30),0x82,0x20400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041e34),0x83,0x20400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041e38),0x84,0x20400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041e3c),0x85,0x20400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041e40),0x86,0x20400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041e44),0x87,0x20400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041e48),0x88,0x20400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041e4c),0x89,0x400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041e50),0x8a,0x400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041e54),0x8b,0x20400);
  cRSpriteManager::Load(this_00,(char *)(iVar3 + DAT_00041e58),0x8c,0x20400);
  return;
}
