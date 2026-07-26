/*
 * mangled: _ZN8cRPlayer2AIEv
 * demangled: cRPlayer::AI()
 * address: 00041ff0
 * size: 1448
 */

/* WARNING: Type propagation algorithm not settling */
/* cRPlayer::AI() */

void __thiscall cRPlayer::AI(cRPlayer *this)

{
  cRPlayer cVar1;
  undefined *puVar2;

  this[0x1ec] = (cRPlayer)0x1;
  do {
    this[0x1ec] = (cRPlayer)0x0;
    puVar2 = PTR__Game_001b60b8;
    switch(*(undefined4 *)(this + 0x88)) {
    case 1:
      *(undefined4 *)(this + 0x88) = 0;
      cRMouse::SetActive((cRMouse *)(this + 0x154));
      puVar2 = PTR__Game_001b60b8;
      *(undefined4 *)(*(int *)PTR__Game_001b60b8 + 0x4e6b0) = 0;
      cRIntro::Init((cRIntro *)(*(int *)puVar2 + 0x4e6b0));
      cVar1 = this[0x1ec];
      break;
    case 2:
      *(undefined4 *)(this + 0x88) = 0;
      cRMouse::SetActive((cRMouse *)(this + 0x154));
      cRIntro::Init((cRIntro *)(*(int *)PTR__Game_001b60b8 + 0x4e6b0));
    case 0:
      cRIntro::AI((cRIntro *)(*(int *)PTR__Game_001b60b8 + 0x4e6b0));
      cVar1 = this[0x1ec];
      break;
    case 3:
      *(undefined4 *)(this + 0x88) = 5;
      cRMouse::SetActive((cRMouse *)(this + 0x154));
      cRMainMenu::Init((cRMainMenu *)(*(int *)PTR__Game_001b60b8 + 0x4e6fc));
      cVar1 = this[0x1ec];
      break;
    case 4:
      *(undefined4 *)(this + 0x88) = 5;
      cRMouse::SetActive((cRMouse *)(this + 0x154));
      cRMainMenu::Init((cRMainMenu *)(*(int *)PTR__Game_001b60b8 + 0x4e6fc));
    case 5:
      cRMainMenu::AI((cRMainMenu *)(*(int *)PTR__Game_001b60b8 + 0x4e6fc));
      cVar1 = this[0x1ec];
      break;
    case 6:
      *(undefined4 *)(this + 0x88) = 7;
      cROptions::Init((cROptions *)(*(int *)PTR__Game_001b60b8 + 0x4e758));
    case 7:
      cROptions::AI((cROptions *)(*(int *)PTR__Game_001b60b8 + 0x4e758));
      cVar1 = this[0x1ec];
      break;
    case 8:
      cRExit::Init((cRExit *)(*(int *)PTR__Game_001b60b8 + 0x4e780));
      *(undefined4 *)(this + 0x88) = 9;
    case 9:
      cRExit::AI((cRExit *)(*(int *)PTR__Game_001b60b8 + 0x4e780));
      cVar1 = this[0x1ec];
      break;
    case 10:
      *(undefined4 *)(*(int *)(&DAT_00353540 + *(int *)PTR__Game_001b60b8) + 4) = 0;
      cRSubGame::Init((cRSubGame *)(*(int *)puVar2 + 0x72b78));
      *(undefined4 *)(this + 0x88) = 0xb;
    case 0xb:
      cRSubGame::AI((cRSubGame *)(*(int *)PTR__Game_001b60b8 + 0x72b78));
      cVar1 = this[0x1ec];
      break;
    case 0xc:
      cRLogo::Init((cRLogo *)(*(int *)PTR__Game_001b60b8 + 0x4e7c8),"Intro/Intro.txt");
      *(undefined4 *)(this + 0x88) = 0xd;
      cVar1 = this[0x1ec];
      break;
    case 0xd:
      goto LAB_000420b4;
    case 0xe:
      cRLogo::Init((cRLogo *)(*(int *)PTR__Game_001b60b8 + 0x4e7c8),"Intro/Credits.txt");
      *(undefined4 *)(this + 0x88) = 0xf;
      cVar1 = this[0x1ec];
      break;
    case 0xf:
LAB_000420b4:
      cRLogo::AI((cRLogo *)(*(int *)PTR__Game_001b60b8 + 0x4e7c8));
switchD_00042014_caseD_10:
      cVar1 = this[0x1ec];
      break;
    default:
      goto switchD_00042014_caseD_10;
    case 0x12:
      cRHighScore::Init(*(int *)PTR__Game_001b60b8 + 0x3782ac,*(int *)(PTR__gConfig_001b60d4 + 0xa8)
                       );
      *(undefined4 *)(this + 0x88) = 0x13;
      cVar1 = this[0x1ec];
      break;
    case 0x13:
      goto LAB_0004249c;
    case 0x14:
      cRHighScore::Init(*(int *)PTR__Game_001b60b8 + 0x3782ac,
                        *(int *)(*(int *)PTR__Game_001b60b8 + 0x2c8));
      *(undefined4 *)(this + 0x88) = 0x15;
      cVar1 = this[0x1ec];
      break;
    case 0x15:
LAB_0004249c:
      cRHighScore::AI((cRHighScore *)(*(int *)PTR__Game_001b60b8 + 0x3782ac));
      cVar1 = this[0x1ec];
      break;
    case 0x19:
      *(undefined4 *)(*(int *)PTR__Game_001b60b8 + 0x5c) = 1;
      cVar1 = this[0x1ec];
      break;
    case 0x1a:
      cRSubGame::UnInit((cRSubGame *)(*(int *)PTR__Game_001b60b8 + 0x72b78));
      if (*(int *)(this + 0x8c) == -1) goto switchD_00042014_caseD_10;
      *(int *)(this + 0x88) = *(int *)(this + 0x8c);
      goto LAB_0004241c;
    case 0x1b:
      cRSubGame::UnInit((cRSubGame *)(*(int *)PTR__Game_001b60b8 + 0x72b78));
      goto LAB_000423fc;
    case 0x1c:
      cRSubGame::UnInit((cRSubGame *)(*(int *)PTR__Game_001b60b8 + 0x72b78));
      *(undefined4 *)(&DAT_00376620 + *(int *)puVar2) = 0;
LAB_000423fc:
      cRSubGame::Init((cRSubGame *)(*(int *)puVar2 + 0x72b78));
      if (*(int *)(this + 0x8c) != -1) {
        *(int *)(this + 0x88) = *(int *)(this + 0x8c);
LAB_0004241c:
        cVar1 = this[0x1ec];
        break;
      }
      goto switchD_00042014_caseD_10;
    case 0x1d:
      *(undefined4 *)(this + 0x88) = 0x1e;
      cRSplash::Init((cRSplash *)(*(int *)PTR__Game_001b60b8 + 0x36492c));
    case 0x1e:
      cRSplash::AI((cRSplash *)(*(int *)PTR__Game_001b60b8 + 0x36492c));
      cVar1 = this[0x1ec];
      break;
    case 0x1f:
      *(undefined4 *)(this + 0x88) = 0x20;
      cRHelp::Init((cRHelp *)(*(int *)PTR__Game_001b60b8 + 0x364924));
    case 0x20:
      cRHelp::AI((cRHelp *)(*(int *)PTR__Game_001b60b8 + 0x364924));
      cVar1 = this[0x1ec];
      break;
    case 0x21:
      *(undefined4 *)(this + 0x88) = 0x22;
      cRContinue::Init((cRContinue *)(*(int *)PTR__Game_001b60b8 + 0x43e0c));
    case 0x22:
      cRContinue::AI((cRContinue *)(*(int *)PTR__Game_001b60b8 + 0x43e0c));
      cVar1 = this[0x1ec];
      break;
    case 0x23:
      *(undefined4 *)(this + 0x88) = 0x24;
      cRSure::Init((cRSure *)(*(int *)PTR__Game_001b60b8 + 0x43e18));
    case 0x24:
      cRSure::AI((cRSure *)(*(int *)PTR__Game_001b60b8 + 0x43e18));
      cVar1 = this[0x1ec];
    }
    if (cVar1 == (cRPlayer)0x0) {
      *(undefined4 *)(this + 0x160) = *(undefined4 *)(*(int *)(this + 0x150) + 0x54);
      *(undefined4 *)(this + 0x164) = *(undefined4 *)(*(int *)(this + 0x150) + 0x58);
      *(undefined4 *)(this + 0xc0) = *(undefined4 *)(this + 0x2c);
      *(undefined4 *)(this + 0xc4) = *(undefined4 *)(this + 0x30);
      *(undefined4 *)(this + 200) = *(undefined4 *)(this + 0x34);
      *(undefined4 *)(this + 0xcc) = *(undefined4 *)(this + 0x38);
      *(undefined4 *)(this + 0xd0) = *(undefined4 *)(this + 0x3c);
      *(undefined4 *)(this + 0xd4) = *(undefined4 *)(this + 0x40);
      *(undefined4 *)(this + 0xd8) = *(undefined4 *)(this + 0x44);
      *(undefined4 *)(this + 0xdc) = *(undefined4 *)(this + 0x48);
      *(undefined4 *)(this + 0xe0) = *(undefined4 *)(this + 0x4c);
      *(undefined4 *)(this + 0xe4) = *(undefined4 *)(this + 0x50);
      *(undefined4 *)(this + 0xe8) = *(undefined4 *)(this + 0x54);
      *(undefined4 *)(this + 0xec) = *(undefined4 *)(this + 0x58);
      *(undefined4 *)(this + 0xf0) = *(undefined4 *)(this + 0x5c);
      *(undefined4 *)(this + 0xf4) = *(undefined4 *)(this + 0x60);
      *(undefined4 *)(this + 0xf8) = *(undefined4 *)(this + 100);
      *(undefined4 *)(this + 0xfc) = *(undefined4 *)(this + 0x68);
      tMatrix::Invert((tMatrix *)(this + 0x108),(tMatrix *)(this + 0x2c));
      return;
    }
  } while( true );
}
