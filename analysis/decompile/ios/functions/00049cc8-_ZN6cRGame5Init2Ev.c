/*
 * mangled: _ZN6cRGame5Init2Ev
 * demangled: cRGame::Init2()
 * address: 00049cc8
 * size: 1800
 */

/* cRGame::Init2() */

void __thiscall cRGame::Init2(cRGame *this)

{
  undefined *puVar1;
  uint uVar2;
  int iVar3;
  int iVar4;

  wprintf("GameInit2\n");
  *(undefined4 *)(this + 0x72bd4) = *(undefined4 *)(PTR__gConfig_001b60d4 + 0xa4);
  cRSubGame::GetSkirtColourRandomOpen((cRSubGame *)(this + 0x72b78));
  cRGUI::Open((cRGUI *)(this + 0x3648fc));
  cRSplash::Open((cRSplash *)(this + 0x36492c));
  cRGalaxy::Open((cRGalaxy *)(this + 0x364948),0);
  cRGalaxy::Open((cRGalaxy *)(this + 0x36d7b4),1);
  cRCameraman::Init((cRCameraman *)(this + 0x821a8));
  cRLogo::Open((cRLogo *)(this + 0x4e7c8));
  cROptions::Apply((cROptions *)(this + 0x4e758),true);
  cRSMTracks::OpenLevels();
  puVar1 = PTR__Game_001b60b8;
  cRLandscapeManager::Import
            ((cRLandscapeManager *)(&DAT_003593d8 + *(int *)PTR__Game_001b60b8),"Menubg.txt");
  cRSubTracks::Init((cRSubTracks *)(this + 0x73e80),(cRSubSegmentRaw **)PTR__gSubTracksMain_001b61e8
                   );
  *(undefined4 *)(this + 0x398) = 1;
  *(undefined4 *)(this + 0x39c) = 0x2000009;
  cRViewport::SetCamera((cRViewport *)(this + 0x394),(cRCamera *)(this + 0x168));
  *(undefined4 *)(this + 0x220) = 0x2000000;
  *(undefined4 *)(this + 0x3c8) = 2;
  uVar2 = *(uint *)(this + 0x52c);
  *(undefined4 *)(this + 0x3cc) = 0x400000b;
  *(cRGame **)(this + 0x3e4) = this + 0x59c;
  *(undefined4 *)(this + 0x3d0) = 0;
  *(undefined4 *)(this + 0x3d4) = 0;
  *(undefined4 *)(this + 0x3d8) = 0x3f800000;
  *(undefined4 *)(this + 0x3dc) = 0x3f800000;
  this[1000] = (cRGame)0x0;
  iVar3 = *(int *)puVar1;
  if ((uVar2 & 0x200) == 0) {
    if (*(int *)(iVar3 + 0x35c) == 0) {
      *(cRGame **)(iVar3 + 0x35c) = this + 0x528;
      *(undefined4 *)(this + 0x530) = 0;
      *(undefined4 *)(this + 0x534) = 0;
    }
    else {
      *(cRGame **)(*(int *)(iVar3 + 0x35c) + 8) = this + 0x528;
      *(int *)(*(int *)(*(int *)(iVar3 + 0x35c) + 8) + 0xc) = *(int *)(iVar3 + 0x35c);
      iVar4 = *(int *)(*(int *)(iVar3 + 0x35c) + 8);
      *(int *)(iVar3 + 0x35c) = iVar4;
      *(undefined4 *)(iVar4 + 8) = 0;
    }
    *(uint *)(this + 0x52c) = uVar2 | 0x200;
  }
  else {
    RShellError("List ADD");
  }
  *(undefined4 *)(this + 0x654) = 0;
  *(undefined4 *)(this + 0x658) = 0x39bf9cd1;
  tMatrix::Identity((tMatrix *)(this + 0x554));
  *(undefined4 *)(this + 0x650) = 0x42180000;
  tMatrix::Identity((tMatrix *)(this + 0x5c8));
  tMatrix::Invert((tMatrix *)(this + 0x610),(tMatrix *)(this + 0x554));
  RShellFontLoad("Objects/Font/Font.png",2,0.75,1.0);
  FontMake3D(0);
  FontInit();
  puVar1 = PTR__gRSpriteManager_001b61e4;
  cRSpriteManager::Init((cRSpriteManager *)PTR__gRSpriteManager_001b61e4);
  cRSpriteManager::LoadSet((cRSpriteManager *)puVar1,"Sprites/Sprites.png",2,0x20400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/Debug.tga",1,0);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/Overlay.tga",3,0x20000);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/Border.tga",6,0x20400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/Mouse.tga",8,0x20400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/Warning.tga",0x51,0x20400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/btn_menu.tga",0x52,0x400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/Play.tga",0xd,0x400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/StarTail.tga",0x12,0x400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/Jet.tga",0x13,0x400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/Health.tga",0x2b,0x400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/DamageGuage.png",0x4b,0x400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/DamageGuageFull.png",0x4c,0x400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/DamageGuageBright.png",0x4d,0x400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/Spark.tga",0x4e,0x400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/Black.tga",0x4f,0x400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/White.tga",0x50,0x400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/BorderGlow.tga",0x57,0x20400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/Slug000.tga",0x6a,0x400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/Slug001.tga",0x6b,0x400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/SlugMask.tga",0x6c,0x400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/Parcel000.tga",0x6d,0x400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/ParcelIcon.tga",0x6e,0x400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/GarbageA.tga",0x66,0x400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/GarbageB.tga",0x67,0x400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/GarbageC.tga",0x68,0x400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/GarbageD.tga",0x69,0x400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/Life.tga",0x6f,0x400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/JetPack000.tga",0x70,0x400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/Smoke.tga",0x74,0x400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/SlugGoo.tga",0x75,0x400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/SliderBar.tga",0x16,0x400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/SliderBarFull.tga",0x17,0x400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/Less.tga",0x18,0x400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/LessHover.tga",0x1a,0x400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/LessMask.tga",0x1b,0x420);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/More.tga",0x1c,0x400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/MoreHover.tga",0x1e,0x400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/MoreMask.tga",0x1f,0x420);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/ParticleBlasters.tga",0x76,0x400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/ParticleExplode-big.tga",0x77,0x400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/ParticleExplode-small.tga",0x78,0x400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/ParticleSlow-big.tga",0x79,0x400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/ParticleSlow-small.tga",0x7a,0x400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/ParticleRing-big.tga",0x7b,0x400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/ParticleRing-small.tga",0x7c,0x400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Galaxy/SpaceMapLogo.tga",0x7d,0x20400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Galaxy/LevelStar.tga",0x7e,0x20400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Galaxy/BorderSpacemap.tga",0x7f,0x20400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Galaxy/Line.tga",0x80,0x20400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Galaxy/LevelSelect.tga",0x81,0x20400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Galaxy/BorderSpacemapPro.tga",0x82,0x20400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Galaxy/LinePro.tga",0x83,0x20400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Galaxy/LevelSelectPro.tga",0x84,0x20400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Galaxy/LineStar.tga",0x85,0x20400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/Progress-Bar.tga",0x86,0x20400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/Progress-Bar-lit.tga",0x87,0x20400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/Progress-Cursor.tga",0x88,0x20400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/JetPackThrust.tga",0x89,0x400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/Ghost.tga",0x8a,0x400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"KeyPad/KeyPad.png",0x8b,0x20400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/OFLogo.png",0x8c,0x20400);
  cRSpriteManager::Load((cRSpriteManager *)puVar1,"Sprites/OFLogoPortrait.png",0x8d,0x20400);
  return;
}
