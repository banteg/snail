/*
 * mangled: _ZN6cRGame5Init2Ev
 * demangled: cRGame::Init2()
 * address: 00041804
 * size: 1948
 */

/* cRGame::Init2() */

void __thiscall cRGame::Init2(cRGame *this)

{
  int iVar1;
  undefined8 uVar2;

  wprintf("GameInit2\n");
  *(undefined4 *)(this + 0x71904) = gConfig._164_4_;
  cRSubGame::GetSkirtColourRandomOpen((cRSubGame *)(this + 0x718a0));
  cRGUI::Open((cRGUI *)(this + 0x392918));
  cRSplash::Open((cRSplash *)(this + 0x392948));
  cRGalaxy::Open((cRGalaxy *)(this + 0x392964),0);
  cRGalaxy::Open((cRGalaxy *)(this + 0x39b7d0),1);
  cRCameraman::Init((cRCameraman *)(this + 0x8154c));
  cRLogo::Open((cRLogo *)(this + 0x4d4f0));
  cROptions::Apply((bool)((char)this + -0x80));
  cRSMTracks::OpenLevels();
  cRLandscapeManager::Import((cRLandscapeManager *)(gSegmentText + Game + 0x3d8),"Menubg.txt");
  cRSubTracks::Init((cRSubTracks *)(this + 0x72ee8),(cRSubSegmentRaw **)gSubTracksMain);
  *(undefined4 *)(this + 0x398) = 1;
  *(undefined4 *)(this + 0x39c) = 0x2000009;
  cRViewport::SetCamera((cRViewport *)(this + 0x394),(cRCamera *)(this + 0x168));
  iVar1 = Game;
  *(undefined4 *)(this + 0x3d4) = 0;
  *(undefined4 *)(this + 0x3d0) = 0;
  *(undefined4 *)(this + 0x3cc) = 0x400000b;
  *(undefined4 *)(this + 0x3c8) = 2;
  *(undefined4 *)(this + 0x3d8) = 0x3f800000;
  *(cRGame **)(this + 0x3e4) = this + 0x59c;
  *(undefined4 *)(this + 0x3dc) = 0x3f800000;
  *(undefined4 *)(this + 0x220) = 0x2000000;
  this[1000] = (cRGame)0x0;
  cLinkedList<cRBod>::Add((cLinkedList<cRBod> *)(iVar1 + 0x358),(cRBod *)(this + 0x528));
  uVar2 = cROverlay::Init((cROverlay *)(this + 0x528));
  RShellFontLoad("Objects/Font/Font.png",2,(float)uVar2,(float)((ulonglong)uVar2 >> 0x20));
  FontMake3D(0);
  FontInit();
  cRSpriteManager::Init((cRSpriteManager *)&gRSpriteManager);
  cRSpriteManager::LoadSet((cRSpriteManager *)&gRSpriteManager,"Sprites/Sprites.png",2,0x20400);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Sprites/Debug.tga",1,0);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Sprites/Overlay.tga",3,0x20000);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Sprites/Border.tga",6,0x20400);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Sprites/Mouse.tga",8,0x20400);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Sprites/Warning.tga",0x51,0x20400);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Sprites/btn_menu.tga",0x52,0x400);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Sprites/Play.tga",0xd,0x400);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Sprites/StarTail.tga",0x12,0x400);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Sprites/Jet.tga",0x13,0x400);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Sprites/Health.tga",0x2b,0x400);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Sprites/DamageGuage.tga",0x4b,0x400);
  cRSpriteManager::Load
            ((cRSpriteManager *)&gRSpriteManager,"Sprites/DamageGuageFull.tga",0x4c,0x400);
  cRSpriteManager::Load
            ((cRSpriteManager *)&gRSpriteManager,"Sprites/DamageGuageBright.tga",0x4d,0x400);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Sprites/Spark.tga",0x4e,0x400);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Sprites/Black.tga",0x4f,0x400);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Sprites/White.tga",0x50,0x400);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Sprites/BorderGlow.tga",0x57,0x20400);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Sprites/Slug000.tga",0x6a,0x400);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Sprites/Slug001.tga",0x6b,0x400);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Sprites/SlugMask.tga",0x6c,0x400);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Sprites/Parcel000.tga",0x6d,0x400);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Sprites/ParcelIcon.tga",0x6e,0x400);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Sprites/GarbageA.tga",0x66,0x400);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Sprites/GarbageB.tga",0x67,0x400);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Sprites/GarbageC.tga",0x68,0x400);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Sprites/GarbageD.tga",0x69,0x400);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Sprites/Life.tga",0x6f,0x400);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Sprites/JetPack000.tga",0x70,0x400);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Sprites/Smoke.tga",0x74,0x400);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Sprites/SlugGoo.tga",0x75,0x400);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Sprites/SliderBar.tga",0x16,0x400);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Sprites/SliderBarFull.tga",0x17,0x400);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Sprites/Less.tga",0x18,0x400);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Sprites/LessHover.tga",0x1a,0x400);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Sprites/LessMask.tga",0x1b,0x520);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Sprites/More.tga",0x1c,0x400);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Sprites/MoreHover.tga",0x1e,0x400);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Sprites/MoreMask.tga",0x1f,0x520);
  cRSpriteManager::Load
            ((cRSpriteManager *)&gRSpriteManager,"Sprites/ParticleBlasters.tga",0x76,0x400);
  cRSpriteManager::Load
            ((cRSpriteManager *)&gRSpriteManager,"Sprites/ParticleExplode-big.tga",0x77,0x400);
  cRSpriteManager::Load
            ((cRSpriteManager *)&gRSpriteManager,"Sprites/ParticleExplode-small.tga",0x78,0x400);
  cRSpriteManager::Load
            ((cRSpriteManager *)&gRSpriteManager,"Sprites/ParticleSlow-big.tga",0x79,0x400);
  cRSpriteManager::Load
            ((cRSpriteManager *)&gRSpriteManager,"Sprites/ParticleSlow-small.tga",0x7a,0x400);
  cRSpriteManager::Load
            ((cRSpriteManager *)&gRSpriteManager,"Sprites/ParticleRing-big.tga",0x7b,0x400);
  cRSpriteManager::Load
            ((cRSpriteManager *)&gRSpriteManager,"Sprites/ParticleRing-small.tga",0x7c,0x400);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Galaxy/SpaceMapLogo.tga",0x7d,0x20400);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Galaxy/LevelStar.tga",0x7e,0x20400);
  cRSpriteManager::Load
            ((cRSpriteManager *)&gRSpriteManager,"Galaxy/BorderSpacemap.tga",0x7f,0x20400);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Galaxy/Line.tga",0x80,0x20400);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Galaxy/LevelSelect.tga",0x81,0x20400);
  cRSpriteManager::Load
            ((cRSpriteManager *)&gRSpriteManager,"Galaxy/BorderSpacemapPro.tga",0x82,0x20400);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Galaxy/LinePro.tga",0x83,0x20400);
  cRSpriteManager::Load
            ((cRSpriteManager *)&gRSpriteManager,"Galaxy/LevelSelectPro.tga",0x84,0x20400);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Galaxy/LineStar.tga",0x85,0x20400);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Sprites/Progress-Bar.tga",0x86,0x20400)
  ;
  cRSpriteManager::Load
            ((cRSpriteManager *)&gRSpriteManager,"Sprites/Progress-Bar-lit.tga",0x87,0x20400);
  cRSpriteManager::Load
            ((cRSpriteManager *)&gRSpriteManager,"Sprites/Progress-Cursor.tga",0x88,0x20400);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Sprites/JetPackThrust.tga",0x89,0x400);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Sprites/Ghost.tga",0x8a,0x400);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"KeyPad/KeyPad.png",0x8b,0x20400);
  cRSpriteManager::Load((cRSpriteManager *)&gRSpriteManager,"Sprites/OFLogo.png",0x8c,0x20400);
  return;
}
