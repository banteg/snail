/*
 * mangled: _ZN6cRGame2AIEv
 * demangled: cRGame::AI()
 * address: 0004d704
 * size: 1068
 */

/* cRGame::AI() */

undefined4 __thiscall cRGame::AI(cRGame *this)

{
  cRSprite *this_00;
  undefined *puVar1;
  int iVar2;
  cRGame *pcVar3;
  cRSprite *pcVar4;
  cRGame *pcVar5;
  int iVar6;
  float fVar7;
  float fVar8;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;

  KeyboardAI();
  puVar1 = PTR__Game_001b60b8;
  switch(*(undefined4 *)(this + 0x24)) {
  case 0:
    goto switchD_0004d728_caseD_0;
  case 1:
    fVar8 = *(float *)(this + 0x28) - 0.055555556;
    *(float *)(this + 0x28) = fVar8;
    if (*(int *)(*(int *)puVar1 + 0x328) < 1) {
      if (fVar8 <= 0.0) {
        fVar8 = 0.0;
        *(undefined4 *)(this + 0x24) = 0;
        *(undefined4 *)(this + 0x28) = 0;
      }
    }
    else {
      fVar8 = 1.0;
      *(undefined4 *)(this + 0x28) = 0x3f800000;
    }
    break;
  case 2:
    fVar8 = *(float *)(this + 0x28) + 0.055555556;
    *(float *)(this + 0x28) = fVar8;
    if ((1.0 < fVar8) &&
       (*(undefined4 *)(this + 0x28) = 0x3f800000, fVar8 = 1.0,
       *PTR__G0RenderNextFlag_001b60f4 != '\0')) {
      *(undefined4 *)(this + 0x24) = 4;
      *(undefined4 *)(this + 0x2c) = 0;
      *(undefined4 *)(this + 0x30) = 0x3eaaaaab;
    }
    break;
  default:
switchD_0004d728_caseD_3:
    fVar8 = *(float *)(this + 0x28);
    break;
  case 5:
    iVar6 = *(int *)(this + 0x38);
    iVar2 = iVar6 + -1;
    *(int *)(this + 0x38) = iVar2;
    if (iVar2 != 0) goto switchD_0004d728_caseD_3;
    *(int *)(this + 0x24) = iVar6;
    fVar8 = *(float *)(this + 0x28);
  }
  tColour::tColour((tColour *)&local_38,0.0,0.0,0.0,fVar8);
  OSDPrint(3,0,0,0x44200000,0x43f00000,0x1000000,local_38,uStack_34,uStack_30,uStack_2c,9);
switchD_0004d728_caseD_0:
  RShellInputRegisterKeyboard(0,0.0,0.0);
  cKeyPad::AI((cKeyPad *)(this + 0xbf0));
  cRMouse::AI((cRMouse *)(this + 0x228));
  fVar8 = 1.0;
  cRBass::AI();
  cRCheat::AI((cRCheat *)PTR__gCheat_001b61dc);
  cRVoiceManager::AI((cRVoiceManager *)PTR__gVoiceManager_001b61d8);
  *(int *)(this + 0x2d8) = *(int *)(this + 0x2d8) + 1;
  *(undefined4 *)(this + 0x5c) = 0;
  if (this[0x23c] != (cRGame)0x0) {
    this[0x23c] = (cRGame)0x0;
  }
  *(undefined4 *)(this + 0x60) = 1;
  *(float *)(this + 0x2d4) = *(float *)(this + 0x2d4) + fVar8;
  this[0x2dc] = (cRGame)0x1;
  cKeyPad::Render((cKeyPad *)(this + 0xbf0));
  fVar7 = *(float *)(this + 0x2d4);
  if (fVar8 < fVar7) {
    do {
      *(float *)(this + 0x2d4) = fVar7 - 1.0;
      *(float *)(this + 0x270) =
           *(float *)(this + 0x270) + (*(float *)(this + 0x260) - *(float *)(this + 0x270)) * 0.145;
      *(float *)(this + 0x274) =
           *(float *)(this + 0x274) + (*(float *)(this + 0x264) - *(float *)(this + 0x274)) * 0.145;
      *(float *)(this + 0x278) =
           *(float *)(this + 0x278) + (*(float *)(this + 0x268) - *(float *)(this + 0x278)) * 0.145;
      fVar8 = *(float *)(this + 0x27c) +
              (*(float *)(this + 0x26c) - *(float *)(this + 0x27c)) * 0.145;
      *(float *)(this + 0x27c) = fVar8;
      if (0.01 < fVar8) {
        OSDPrint(3,0,0,0x44200000,0x43f00000,*(uint *)(this + 0x25c) & 0xff000000,
                 *(undefined4 *)(this + 0x270),*(undefined4 *)(this + 0x274),
                 *(undefined4 *)(this + 0x278),*(undefined4 *)(this + 0x27c),5);
      }
      cRBackdrop::AI((cRBackdrop *)(this + 0x4d2e0));
      cRGalaxy::AI((cRGalaxy *)(this + *(int *)(this + 0x364944) * 0x8e6c + 0x364948));
      if (*(cRGame **)(this + 0x35c) != (cRGame *)0x0) {
        pcVar5 = *(cRGame **)(this + 0x35c);
        do {
          if ((*(uint *)(pcVar5 + 4) & 0x10) == 0) {
            pcVar3 = *(cRGame **)(pcVar5 + 0xc);
            if (pcVar3 != (cRGame *)0x0) goto LAB_0004d940;
LAB_0004d9a8:
            (*(code *)**(undefined4 **)pcVar5)(pcVar5);
          }
          else {
            RShellError("Debug Bod AI");
            pcVar3 = *(cRGame **)(pcVar5 + 0xc);
            if (pcVar3 == (cRGame *)0x0) goto LAB_0004d9a8;
LAB_0004d940:
            *(uint *)(pcVar3 + 4) = *(uint *)(pcVar3 + 4) | 0x40;
            (*(code *)**(undefined4 **)pcVar5)(pcVar5);
            *(uint *)(pcVar3 + 4) = *(uint *)(pcVar3 + 4) & 0xffffffbf;
          }
          if (pcVar3 == this + 0xd14) {
            (*(code *)**(undefined4 **)(this + 0xd4))(this + 0xd4);
          }
          pcVar5 = pcVar3;
        } while (pcVar3 != (cRGame *)0x0);
      }
      cAccelerometer::AI((cAccelerometer *)(this + 0xbd4));
      iVar6 = 0;
      cRGalaxy::Render((cRGalaxy *)(this + *(int *)(this + 0x364944) * 0x8e6c + 0x364948));
      puVar1 = PTR__gRSpriteManager_001b61e4;
      do {
        this_00 = *(cRSprite **)(puVar1 + iVar6 + 0x2af84);
        while (this_00 != (cRSprite *)0x0) {
          pcVar4 = *(cRSprite **)(this_00 + 0xc);
          cRSprite::AI(this_00);
          this_00 = pcVar4;
        }
        iVar6 = iVar6 + 4;
      } while (iVar6 != 0xc);
      cREnemyManager::Init((cREnemyManager *)(this + 0x37662c));
      fVar7 = *(float *)(this + 0x2d4);
      this[0x2dc] = (cRGame)0x0;
    } while (1.0 < fVar7);
  }
  return *(undefined4 *)(this + 0x5c);
}
