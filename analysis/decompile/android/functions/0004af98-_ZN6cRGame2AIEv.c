/*
 * mangled: _ZN6cRGame2AIEv
 * demangled: cRGame::AI()
 * address: 0004af98
 * size: 672
 */

/* cRGame::AI() */

undefined4 __thiscall cRGame::AI(cRGame *this)

{
  cRSprite *this_00;
  undefined4 *puVar1;
  cRGame *pcVar2;
  cRSprite *pcVar3;
  cRGame *pcVar4;
  int iVar5;
  undefined8 uVar6;
  float fVar7;

  KeyboardAI();
  uVar6 = cRFade::AI();
  RShellInputRegisterKeyboard(0,(float)uVar6,(float)((ulonglong)uVar6 >> 0x20));
  cKeyPad::AI((cKeyPad *)(this + 0xbf0));
  cRMouse::AI((cRMouse *)(this + 0x228));
  cRCheat::AI((cRCheat *)&gCheat);
  cRVoiceManager::AI((cRVoiceManager *)&gVoiceManager);
  this[0x2dc] = (cRGame)0x1;
  if (this[0x23c] != (cRGame)0x0) {
    this[0x23c] = (cRGame)0x0;
  }
  *(int *)(this + 0x2d8) = *(int *)(this + 0x2d8) + 1;
  *(undefined4 *)(this + 0x5c) = 0;
  *(undefined4 *)(this + 0x60) = 1;
  *(float *)(this + 0x2d4) = *(float *)(this + 0x2d4) + 1.0;
  cKeyPad::Render((cKeyPad *)(this + 0xbf0));
  fVar7 = *(float *)(this + 0x2d4);
  if (1.0 < fVar7) {
    do {
      *(float *)(this + 0x2d4) = fVar7 - 1.0;
      cRFlash::AI((cRFlash *)(this + 0x25c));
      cRBackdrop::AI();
      cRGalaxy::AI((cRGalaxy *)(this + *(int *)(this + 0x392960) * 0x8e6c + 0x392964));
      pcVar4 = *(cRGame **)(this + 0x35c);
joined_r0x0004b100:
      if (pcVar4 != (cRGame *)0x0) {
        do {
          if ((*(uint *)(pcVar4 + 4) & 0x10) == 0) {
            pcVar2 = *(cRGame **)(pcVar4 + 0xc);
            if (pcVar2 == (cRGame *)0x0) goto LAB_0004b170;
LAB_0004b118:
            puVar1 = *(undefined4 **)pcVar4;
            *(uint *)(pcVar2 + 4) = *(uint *)(pcVar2 + 4) | 0x40;
            (*(code *)*puVar1)(pcVar4);
            *(uint *)(pcVar2 + 4) = *(uint *)(pcVar2 + 4) & 0xffffffbf;
            pcVar4 = pcVar2;
          }
          else {
            RShellError("Debug Bod AI");
            pcVar2 = *(cRGame **)(pcVar4 + 0xc);
            if (pcVar2 != (cRGame *)0x0) goto LAB_0004b118;
LAB_0004b170:
            (*(code *)**(undefined4 **)pcVar4)(pcVar4);
            pcVar4 = pcVar2;
          }
          if (pcVar4 != this + 0xd14) goto joined_r0x0004b100;
          (*(code *)**(undefined4 **)(this + 0xd4))(this + 0xd4);
          if (pcVar4 == (cRGame *)0x0) break;
        } while( true );
      }
      iVar5 = 0;
      cAccelerometer::AI();
      cRGalaxy::Render((cRGalaxy *)(this + *(int *)(this + 0x392960) * 0x8e6c + 0x392964));
      do {
        this_00 = *(cRSprite **)((int)&DAT_0015cfd4 + iVar5);
        while (this_00 != (cRSprite *)0x0) {
          pcVar3 = *(cRSprite **)(this_00 + 0xc);
          cRSprite::AI(this_00);
          this_00 = pcVar3;
        }
        iVar5 = iVar5 + 4;
      } while (iVar5 != 0xc);
      cREnemyManager::Init((cREnemyManager *)(this + 0x3a4648));
      fVar7 = *(float *)(this + 0x2d4);
      this[0x2dc] = (cRGame)0x0;
    } while (1.0 < fVar7);
  }
  return *(undefined4 *)(this + 0x5c);
}
