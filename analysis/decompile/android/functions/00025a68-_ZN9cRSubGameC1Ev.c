/*
 * mangled: _ZN9cRSubGameC1Ev
 * demangled: cRSubGame::cRSubGame()
 * address: 00025a68
 * size: 1440
 */

/* cRSubGame::cRSubGame() */

cRSubGame * __thiscall cRSubGame::cRSubGame(cRSubGame *this)

{
  int iVar1;
  int iVar2;
  cRSubGame *pcVar3;
  int iVar4;
  cRSubGame *pcVar5;
  cRBod *this_00;

  pcVar3 = this + 0xa4;
  iVar2 = 0;
  iVar4 = 0;
  *(undefined4 *)(this + 8) = 0;
  do {
    iVar2 = iVar2 + 0x34;
    *(undefined4 *)(pcVar3 + 0x14) = 0;
    *(undefined4 *)(pcVar3 + 0x18) = 0;
    pcVar3 = pcVar3 + 0x34;
  } while (iVar2 != 0x1450);
  *(undefined4 *)(this + 0x1508) = 0;
  *(undefined4 *)(this + 0x150c) = 0;
  *(undefined4 *)(this + 0x153c) = 0;
  *(undefined4 *)(this + 0x1540) = 0;
  *(undefined4 *)(this + 0x1570) = 0;
  *(undefined4 *)(this + 0x1574) = 0;
  tColour::tColour((tColour *)(this + 0x1598));
  pcVar3 = this + 0x164c;
  do {
    iVar4 = iVar4 + 0x34;
    *(undefined4 *)(pcVar3 + 0x14) = 0;
    *(undefined4 *)(pcVar3 + 0x18) = 0;
    pcVar3 = pcVar3 + 0x34;
  } while (iVar4 != 0x1450);
  *(undefined4 *)(this + 0x2ab0) = 0;
  *(undefined4 *)(this + 0x2b1c) = 0;
  *(undefined4 *)(this + 0x2ab4) = 0;
  *(undefined4 *)(this + 0x2ae4) = 0;
  *(undefined4 *)(this + 0x2ae8) = 0;
  *(undefined4 *)(this + 0x2b18) = 0;
  tColour::tColour((tColour *)(this + 0x2b40));
  cRBod::cRBod((cRBod *)(this + 0x2bf0));
  cRBod::cRBod((cRBod *)(this + 0x2c1c));
  cRBod::cRBod((cRBod *)(this + 0x2c48));
  cRBod::cRBod((cRBod *)(this + 0x2c74));
  cRBod::cRBod((cRBod *)(this + 0x2ca0));
  cRBod::cRBod((cRBod *)(this + 0x2ccc));
  cRBod::cRBod((cRBod *)(this + 0x2cf8));
  cRBod::cRBod((cRBod *)(this + 0x2d24));
  cRBod::cRBod((cRBod *)(this + 0x2d50));
  cRBod::cRBod((cRBod *)(this + 0x2d7c));
  cRBod::cRBod((cRBod *)(this + 0x2da8));
  cRBod::cRBod((cRBod *)(this + 0x2dd4));
  cRBod::cRBod((cRBod *)(this + 0x2e00));
  cRBodPos::cRBodPos((cRBodPos *)(this + 0x2e48));
  *(undefined ***)(this + 0x2e48) = &PTR_AI_0009adb0;
  cRBod::cRBod((cRBod *)(this + 0x2ef0));
  *(undefined ***)(this + 0x2ef0) = &PTR_AI_0009ada0;
  cRBodPos::cRBodPos((cRBodPos *)(this + 0x2f58));
  *(undefined ***)(this + 0x2f58) = &PTR_AI_0009add0;
  cRBodPos::cRBodPos((cRBodPos *)(this + 0x2fe0));
  *(undefined ***)(this + 0x2fe0) = &PTR_AI_0009add0;
  pcVar3 = this + 0x3068;
  do {
    cRBod::cRBod((cRBod *)pcVar3);
    pcVar5 = pcVar3 + 0x68;
    *(undefined ***)pcVar3 = &PTR_AI_0009adc0;
    pcVar3 = pcVar5;
  } while (pcVar5 != this + 0x33a8);
  pcVar3 = this + 0x33a8;
  do {
    cRBodPos::cRBodPos((cRBodPos *)pcVar3);
    pcVar5 = pcVar3 + 0xe0;
    *(undefined ***)pcVar3 = &PTR_AI_0009ad70;
    pcVar3 = pcVar5;
  } while (pcVar5 != this + 0x41a8);
  pcVar3 = this + 0x41a8;
  do {
    cRBodPos::cRBodPos((cRBodPos *)pcVar3);
    pcVar5 = pcVar3 + 0xa4;
    *(undefined ***)pcVar3 = &PTR_AI_0009ad60;
    pcVar3 = pcVar5;
  } while (pcVar5 != this + 0x4e78);
  pcVar3 = this + 0x4e78;
  do {
    cRBodPos::cRBodPos((cRBodPos *)pcVar3);
    pcVar5 = pcVar3 + 0x8c;
    *(undefined ***)pcVar3 = &PTR_AI_0009ad50;
    pcVar3 = pcVar5;
  } while (pcVar5 != this + 0x6458);
  cRBod::cRBod((cRBod *)(this + 0x6458));
  *(undefined ***)(this + 0x6458) = &PTR_AI_0009ad40;
  cRBod::cRBod((cRBod *)(this + 0x64ac));
  *(undefined ***)(this + 0x64ac) = &PTR_AI_0009ad40;
  pcVar3 = this + 0x6504;
  do {
    cRBodPos::cRBodPos((cRBodPos *)pcVar3);
    pcVar5 = pcVar3 + 0xb8;
    *(undefined ***)pcVar3 = &PTR_AI_0009ad90;
    pcVar3 = pcVar5;
  } while (pcVar5 != this + 0x88f4);
  cRBodPos::cRBodPos((cRBodPos *)(this + 0x88f4));
  *(undefined ***)(this + 0x88f4) = &PTR_AI_0009acd0;
  cRBodPos::cRBodPos((cRBodPos *)(this + 0x8aa0));
  *(undefined ***)(this + 0x8aa0) = &PTR_AI_0009acd0;
  cRBod::cRBod((cRBod *)(this + 0xf9f0));
  iVar2 = 0;
  *(undefined ***)(this + 0xf9f0) = &PTR_AI_0009aba0;
  cRBod::cRBod((cRBod *)(this + 0xfa1c));
  cRSubGoldy::cRSubGoldy((cRSubGoldy *)(this + 0xfac4));
  do {
    pcVar3 = this + iVar2 + 0x13adc;
    do {
      cRBod::cRBod((cRBod *)pcVar3);
      pcVar5 = pcVar3 + 0x48;
      *(undefined ***)pcVar3 = &PTR_AI_0009ade0;
      gLocCount = gLocCount + 1;
      pcVar3 = pcVar5;
    } while (pcVar5 != this + iVar2 + 0x13adc + 0x240);
    iVar2 = iVar2 + 0x240;
  } while (iVar2 != 0x1fa400);
  pcVar3 = this + 0x20dedc;
  do {
    cRBodPos::cRBodPos((cRBodPos *)(pcVar3 + 4));
    *(undefined ***)(pcVar3 + 4) = &PTR_AI_0009adf0;
    cRBod::cRBod((cRBod *)(pcVar3 + 0xa4));
    pcVar3 = pcVar3 + 0xdc;
    gSubRowCount = gSubRowCount + 1;
  } while (pcVar3 != this + 0x2cf49c);
  iVar2 = 0;
  do {
    this_00 = (cRBod *)(this + iVar2 + 0x310004);
    cRBod::cRBod(this_00);
    *(undefined ***)(this + iVar2 + 0x310004) = &PTR_AI_0009abb0;
    cRBod::cRBod(this_00 + 0x54);
    cRBod::cRBod(this_00 + 0x90);
    iVar2 = iVar2 + 0x120;
    *(undefined ***)(this_00 + 0x90) = &PTR_AI_0009abb0;
    cRBod::cRBod(this_00 + 0xe4);
  } while (iVar2 != 0x5b20);
  cRBod::cRBod((cRBod *)(this + 0x315b24));
  *(undefined ***)(this + 0x315b24) = &PTR_AI_0009acc0;
  iVar2 = 0;
  do {
    iVar4 = iVar2 + 0x1ac;
    tColour::tColour((tColour *)(this + iVar2 + 0x315ce4));
    iVar2 = iVar4;
  } while (iVar4 != 0x3580);
  cRBod::cRBod((cRBod *)(this + 0x3190dc));
  *(undefined ***)(this + 0x3190dc) = &PTR_AI_0009acb0;
  cRObject::cRObject((cRObject *)(this + 0x319108));
  pcVar3 = this + 0x31f770;
  do {
    cRBod::cRBod((cRBod *)pcVar3);
    pcVar5 = pcVar3 + 0x80;
    *(undefined ***)pcVar3 = &PTR_AI_0009ad80;
    pcVar3 = pcVar5;
  } while (pcVar5 != this + 0x321070);
  iVar2 = 0;
  do {
    iVar4 = 0;
    do {
      iVar1 = iVar4 + iVar2;
      iVar4 = iVar4 + 0xa0;
      tColour::tColour((tColour *)(this + iVar1 + 0x32992c));
    } while (iVar4 != 0x640);
    iVar2 = iVar2 + 0x8e6c;
  } while (iVar2 != 0x11cd8);
  pcVar3 = this + 0x334610;
  do {
    cRBodPos::cRBodPos((cRBodPos *)pcVar3);
    pcVar5 = pcVar3 + 0x84;
    *(undefined ***)pcVar3 = &PTR_AI_0009ad30;
    pcVar3 = pcVar5;
  } while (pcVar5 != this + 0x334a30);
  return this;
}
