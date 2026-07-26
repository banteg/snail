/*
 * mangled: _ZN8cRPlayer2AIEv
 * demangled: cRPlayer::AI()
 * address: 0003ed80
 * size: 1436
 */

/* cRPlayer::AI() */

void __thiscall cRPlayer::AI(cRPlayer *this)

{
  int iVar1;
  cRSubGame *this_00;
  cRPlayer cVar2;
  cRMouse *this_01;

  this_01 = (cRMouse *)(this + 0x154);
  cVar2 = (cRPlayer)0x1;
  this[0x1ec] = (cRPlayer)0x1;
LAB_0003edc0:
  if (cVar2 == (cRPlayer)0x0) {
switchD_0003edd8_default:
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
  this[0x1ec] = (cRPlayer)0x0;
  switch(*(undefined4 *)(this + 0x88)) {
  case 0:
    break;
  case 1:
    *(undefined4 *)(this + 0x88) = 0;
    cRMouse::SetActive(this_01);
    iVar1 = Game;
    *(undefined4 *)(Game + 0x4d3d8) = 0;
    cRIntro::Init((cRIntro *)(iVar1 + 0x4d3d8));
    cVar2 = this[0x1ec];
    goto LAB_0003edc0;
  case 2:
    *(undefined4 *)(this + 0x88) = 0;
    cRMouse::SetActive(this_01);
    cRIntro::Init((cRIntro *)(Game + 0x4d3d8));
    break;
  case 3:
    *(undefined4 *)(this + 0x88) = 5;
    cRMouse::SetActive(this_01);
    cRMainMenu::Init();
    cVar2 = this[0x1ec];
    goto LAB_0003edc0;
  case 4:
    *(undefined4 *)(this + 0x88) = 5;
    cRMouse::SetActive(this_01);
    cRMainMenu::Init();
    goto LAB_0003efdc;
  case 5:
LAB_0003efdc:
    cRMainMenu::AI((cRMainMenu *)(Game + 0x4d424));
    cVar2 = this[0x1ec];
    goto LAB_0003edc0;
  case 6:
    *(undefined4 *)(this + 0x88) = 7;
    cROptions::Init((cROptions *)(Game + 0x4d480));
    goto LAB_0003ef98;
  case 7:
LAB_0003ef98:
    cROptions::AI((cROptions *)(Game + 0x4d480));
    cVar2 = this[0x1ec];
    goto LAB_0003edc0;
  case 8:
    cRExit::Init((cRExit *)(Game + 0x4d4a8));
    *(undefined4 *)(this + 0x88) = 9;
    goto LAB_0003ef5c;
  case 9:
LAB_0003ef5c:
    cRExit::AI((cRExit *)(Game + 0x4d4a8));
    cVar2 = this[0x1ec];
    goto LAB_0003edc0;
  case 10:
    this_00 = (cRSubGame *)(Game + 0x718a0);
    *(undefined4 *)(*(int *)(gDirectory + Game + 0x2540) + 4) = 0;
    cRSubGame::Init(this_00);
    *(undefined4 *)(this + 0x88) = 0xb;
    goto LAB_0003ef20;
  case 0xb:
LAB_0003ef20:
    cRSubGame::AI((cRSubGame *)(Game + 0x718a0));
    cVar2 = this[0x1ec];
    goto LAB_0003edc0;
  case 0xc:
    cRLogo::Init((cRLogo *)(Game + 0x4d4f0),"Intro/Intro.txt");
    *(undefined4 *)(this + 0x88) = 0xd;
    cVar2 = this[0x1ec];
    goto LAB_0003edc0;
  case 0xd:
    goto LAB_0003ee94;
  case 0xe:
    cRLogo::Init((cRLogo *)(Game + 0x4d4f0),"Intro/Credits.txt");
    *(undefined4 *)(this + 0x88) = 0xf;
    cVar2 = this[0x1ec];
    goto LAB_0003edc0;
  case 0xf:
LAB_0003ee94:
    cRLogo::AI((cRLogo *)(Game + 0x4d4f0));
    cVar2 = this[0x1ec];
    goto LAB_0003edc0;
  case 0x10:
    goto switchD_0003edd8_default;
  case 0x11:
    goto switchD_0003edd8_default;
  case 0x12:
    cRHighScore::Init((cRHighScore *)(Game + 0x3a62d0),gConfig._168_4_,-1);
    *(undefined4 *)(this + 0x88) = 0x13;
    cVar2 = this[0x1ec];
    goto LAB_0003edc0;
  case 0x13:
    goto LAB_0003ee74;
  case 0x14:
    cRHighScore::Init((cRHighScore *)(Game + 0x3a62d0),*(int *)(Game + 0x2c8),*(int *)(Game + 0x2c4)
                     );
    *(undefined4 *)(this + 0x88) = 0x15;
    cVar2 = this[0x1ec];
    goto LAB_0003edc0;
  case 0x15:
LAB_0003ee74:
    cRHighScore::AI((cRHighScore *)(Game + 0x3a62d0));
LAB_0003ee8c:
    cVar2 = this[0x1ec];
    goto LAB_0003edc0;
  case 0x16:
    goto switchD_0003edd8_default;
  case 0x17:
    goto switchD_0003edd8_default;
  case 0x18:
    goto switchD_0003edd8_default;
  case 0x19:
    *(undefined4 *)(Game + 0x5c) = 1;
    cVar2 = this[0x1ec];
    goto LAB_0003edc0;
  case 0x1a:
    cRSubGame::UnInit((cRSubGame *)(Game + 0x718a0));
    if (*(int *)(this + 0x8c) != -1) {
      *(int *)(this + 0x88) = *(int *)(this + 0x8c);
      goto LAB_0003f1b8;
    }
    goto LAB_0003ee8c;
  case 0x1b:
    cRSubGame::UnInit((cRSubGame *)(Game + 0x718a0));
    iVar1 = Game;
    goto LAB_0003f1a0;
  case 0x1c:
    cRSubGame::UnInit((cRSubGame *)(Game + 0x718a0));
    iVar1 = Game;
    *(undefined4 *)(&DAT_003a463c + Game) = 0;
LAB_0003f1a0:
    cRSubGame::Init((cRSubGame *)(iVar1 + 0x718a0));
    if (*(int *)(this + 0x8c) == -1) goto LAB_0003ee8c;
    *(int *)(this + 0x88) = *(int *)(this + 0x8c);
LAB_0003f1b8:
    cVar2 = this[0x1ec];
    goto LAB_0003edc0;
  case 0x1d:
    *(undefined4 *)(this + 0x88) = 0x1e;
    cRSplash::Init((cRSplash *)(gOFOData + Game + 0x1ea4));
    goto LAB_0003f094;
  case 0x1e:
LAB_0003f094:
    cRSplash::AI((cRSplash *)(gOFOData + Game + 0x1ea4));
    cVar2 = this[0x1ec];
    goto LAB_0003edc0;
  case 0x1f:
    *(undefined4 *)(this + 0x88) = 0x20;
    cRHelp::Init((cRHelp *)(gOFOData + Game + 0x1e9c));
    goto LAB_0003f058;
  case 0x20:
LAB_0003f058:
    cRHelp::AI((cRHelp *)(gOFOData + Game + 0x1e9c));
    cVar2 = this[0x1ec];
    goto LAB_0003edc0;
  case 0x21:
    *(undefined4 *)(this + 0x88) = 0x22;
    cRContinue::Init((cRContinue *)(Game + 0x43e0c));
    goto LAB_0003eed0;
  case 0x22:
LAB_0003eed0:
    cRContinue::AI((cRContinue *)(Game + 0x43e0c));
    cVar2 = this[0x1ec];
    goto LAB_0003edc0;
  case 0x23:
    *(undefined4 *)(this + 0x88) = 0x24;
    cRSure::Init((cRSure *)(Game + 0x43e18));
    goto LAB_0003f0d4;
  case 0x24:
LAB_0003f0d4:
    cRSure::AI((cRSure *)(Game + 0x43e18));
    cVar2 = this[0x1ec];
    goto LAB_0003edc0;
  default:
    goto switchD_0003edd8_default;
  }
  cRIntro::AI((cRIntro *)(Game + 0x4d3d8));
  cVar2 = this[0x1ec];
  goto LAB_0003edc0;
}
