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
  float fVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  cRGame *pcVar5;
  cRSprite *pcVar6;
  cRGame *pcVar7;
  int iVar8;
  char *pcVar9;
  int iVar10;
  undefined8 uVar11;
  float fVar12;

  fVar1 = DAT_0004b238;
  KeyboardAI();
  uVar11 = cRFade::AI();
  RShellInputRegisterKeyboard(0,(float)uVar11,(float)((ulonglong)uVar11 >> 0x20));
  cKeyPad::AI((cKeyPad *)(this + 0xbf0));
  iVar4 = DAT_0004b23c;
  cRMouse::AI((cRMouse *)(this + 0x228));
  iVar4 = iVar4 + 0x4afec;
  cRCheat::AI(*(cRCheat **)(iVar4 + DAT_0004b240));
  cRVoiceManager::AI(*(cRVoiceManager **)(iVar4 + DAT_0004b244));
  fVar12 = *(float *)(this + 0x2d4) + DAT_0004b238;
  this[0x2dc] = (cRGame)0x1;
  if (this[0x23c] != (cRGame)0x0) {
    this[0x23c] = (cRGame)0x0;
  }
  *(int *)(this + 0x2d8) = *(int *)(this + 0x2d8) + 1;
  *(undefined4 *)(this + 0x5c) = 0;
  *(undefined4 *)(this + 0x60) = 1;
  *(float *)(this + 0x2d4) = fVar12;
  cKeyPad::Render((cKeyPad *)(this + 0xbf0));
  iVar2 = DAT_0004b248;
  fVar12 = *(float *)(this + 0x2d4);
  if (fVar1 < fVar12) {
    pcVar9 = (char *)(iVar4 + DAT_0004b24c);
    do {
      *(float *)(this + 0x2d4) = fVar12 - fVar1;
      cRFlash::AI((cRFlash *)(this + 0x25c));
      cRBackdrop::AI();
      cRGalaxy::AI((cRGalaxy *)(this + *(int *)(this + 0x392960) * 0x8e6c + 0x392964));
      pcVar7 = *(cRGame **)(this + 0x35c);
joined_r0x0004b100:
      if (pcVar7 != (cRGame *)0x0) {
        do {
          if ((*(uint *)(pcVar7 + 4) & 0x10) == 0) {
            pcVar5 = *(cRGame **)(pcVar7 + 0xc);
            if (pcVar5 == (cRGame *)0x0) goto LAB_0004b170;
LAB_0004b118:
            puVar3 = *(undefined4 **)pcVar7;
            *(uint *)(pcVar5 + 4) = *(uint *)(pcVar5 + 4) | 0x40;
            (*(code *)*puVar3)(pcVar7);
            *(uint *)(pcVar5 + 4) = *(uint *)(pcVar5 + 4) & 0xffffffbf;
            pcVar7 = pcVar5;
          }
          else {
            RShellError(pcVar9);
            pcVar5 = *(cRGame **)(pcVar7 + 0xc);
            if (pcVar5 != (cRGame *)0x0) goto LAB_0004b118;
LAB_0004b170:
            (*(code *)**(undefined4 **)pcVar7)(pcVar7);
            pcVar7 = pcVar5;
          }
          if (pcVar7 != this + 0xd14) goto joined_r0x0004b100;
          (*(code *)**(undefined4 **)(this + 0xd4))(this + 0xd4);
          if (pcVar7 == (cRGame *)0x0) break;
        } while( true );
      }
      iVar8 = 0;
      cAccelerometer::AI();
      cRGalaxy::Render((cRGalaxy *)(this + *(int *)(this + 0x392960) * 0x8e6c + 0x392964));
      iVar10 = *(int *)(iVar4 + iVar2);
      do {
        this_00 = *(cRSprite **)(iVar10 + iVar8 + 0x2af84);
        while (this_00 != (cRSprite *)0x0) {
          pcVar6 = *(cRSprite **)(this_00 + 0xc);
          cRSprite::AI(this_00);
          this_00 = pcVar6;
        }
        iVar8 = iVar8 + 4;
      } while (iVar8 != 0xc);
      cREnemyManager::Init((cREnemyManager *)(this + 0x3a4648));
      fVar12 = *(float *)(this + 0x2d4);
      this[0x2dc] = (cRGame)0x0;
    } while (fVar1 < fVar12);
  }
  return *(undefined4 *)(this + 0x5c);
}
