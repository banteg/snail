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
  int iVar3;
  cRSubGame *pcVar4;
  int *piVar5;
  int iVar6;
  cRSubGame *pcVar7;
  cRBod *this_00;
  int iVar8;
  int iVar9;

  pcVar4 = this + 0xa4;
  iVar3 = 0;
  iVar6 = 0;
  iVar8 = DAT_00026008 + 0x25a94;
  *(undefined4 *)(this + 8) = 0;
  do {
    iVar3 = iVar3 + 0x34;
    *(undefined4 *)(pcVar4 + 0x14) = 0;
    *(undefined4 *)(pcVar4 + 0x18) = 0;
    pcVar4 = pcVar4 + 0x34;
  } while (iVar3 != 0x1450);
  *(undefined4 *)(this + 0x1508) = 0;
  *(undefined4 *)(this + 0x150c) = 0;
  *(undefined4 *)(this + 0x153c) = 0;
  *(undefined4 *)(this + 0x1540) = 0;
  *(undefined4 *)(this + 0x1570) = 0;
  *(undefined4 *)(this + 0x1574) = 0;
  tColour::tColour((tColour *)(this + 0x1598));
  pcVar4 = this + 0x164c;
  do {
    iVar6 = iVar6 + 0x34;
    *(undefined4 *)(pcVar4 + 0x14) = 0;
    *(undefined4 *)(pcVar4 + 0x18) = 0;
    pcVar4 = pcVar4 + 0x34;
  } while (iVar6 != 0x1450);
  *(undefined4 *)(this + 0x2ab0) = 0;
  iVar3 = DAT_0002600c;
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
  iVar6 = DAT_00026010;
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
  *(int *)(this + 0x2e48) = *(int *)(iVar8 + DAT_00026014) + 8;
  cRBod::cRBod((cRBod *)(this + 0x2ef0));
  *(int *)(this + 0x2ef0) = *(int *)(iVar8 + DAT_00026018) + 8;
  cRBodPos::cRBodPos((cRBodPos *)(this + 0x2f58));
  iVar6 = *(int *)(iVar8 + iVar6) + 8;
  *(int *)(this + 0x2f58) = iVar6;
  cRBodPos::cRBodPos((cRBodPos *)(this + 0x2fe0));
  *(int *)(this + 0x2fe0) = iVar6;
  pcVar4 = this + 0x3068;
  do {
    cRBod::cRBod((cRBod *)pcVar4);
    pcVar7 = pcVar4 + 0x68;
    *(int *)pcVar4 = *(int *)(iVar8 + iVar3) + 8;
    iVar6 = DAT_0002601c;
    pcVar4 = pcVar7;
  } while (pcVar7 != this + 0x33a8);
  pcVar4 = this + 0x33a8;
  do {
    cRBodPos::cRBodPos((cRBodPos *)pcVar4);
    pcVar7 = pcVar4 + 0xe0;
    *(int *)pcVar4 = *(int *)(iVar8 + iVar6) + 8;
    iVar3 = DAT_00026020;
    pcVar4 = pcVar7;
  } while (pcVar7 != this + 0x41a8);
  pcVar4 = this + 0x41a8;
  do {
    cRBodPos::cRBodPos((cRBodPos *)pcVar4);
    pcVar7 = pcVar4 + 0xa4;
    *(int *)pcVar4 = *(int *)(iVar8 + iVar3) + 8;
    iVar6 = DAT_00026024;
    pcVar4 = pcVar7;
  } while (pcVar7 != this + 0x4e78);
  pcVar4 = this + 0x4e78;
  do {
    cRBodPos::cRBodPos((cRBodPos *)pcVar4);
    pcVar7 = pcVar4 + 0x8c;
    *(int *)pcVar4 = *(int *)(iVar8 + iVar6) + 8;
    iVar3 = DAT_00026028;
    pcVar4 = pcVar7;
  } while (pcVar7 != this + 0x6458);
  cRBod::cRBod((cRBod *)(this + 0x6458));
  iVar6 = DAT_0002602c;
  iVar3 = *(int *)(iVar8 + iVar3) + 8;
  *(int *)(this + 0x6458) = iVar3;
  cRBod::cRBod((cRBod *)(this + 0x64ac));
  *(int *)(this + 0x64ac) = iVar3;
  pcVar4 = this + 0x6504;
  do {
    cRBodPos::cRBodPos((cRBodPos *)pcVar4);
    pcVar7 = pcVar4 + 0xb8;
    *(int *)pcVar4 = *(int *)(iVar8 + iVar6) + 8;
    iVar3 = DAT_00026030;
    pcVar4 = pcVar7;
  } while (pcVar7 != this + 0x88f4);
  cRBodPos::cRBodPos((cRBodPos *)(this + 0x88f4));
  iVar6 = DAT_00026034;
  iVar3 = *(int *)(iVar8 + iVar3) + 8;
  *(int *)(this + 0x88f4) = iVar3;
  cRBodPos::cRBodPos((cRBodPos *)(this + 0x8aa0));
  *(int *)(this + 0x8aa0) = iVar3;
  cRBod::cRBod((cRBod *)(this + 0xf9f0));
  iVar3 = DAT_0002603c;
  iVar9 = 0;
  *(int *)(this + 0xf9f0) = *(int *)(iVar8 + DAT_00026038) + 8;
  cRBod::cRBod((cRBod *)(this + 0xfa1c));
  cRSubGoldy::cRSubGoldy((cRSubGoldy *)(this + 0xfac4));
  do {
    pcVar4 = this + iVar9 + 0x13adc;
    do {
      cRBod::cRBod((cRBod *)pcVar4);
      piVar5 = *(int **)(iVar8 + iVar3);
      pcVar7 = pcVar4 + 0x48;
      *(int *)pcVar4 = *(int *)(iVar8 + iVar6) + 8;
      *piVar5 = *piVar5 + 1;
      iVar2 = DAT_00026044;
      iVar1 = DAT_00026040;
      pcVar4 = pcVar7;
    } while (pcVar7 != this + iVar9 + 0x13adc + 0x240);
    iVar9 = iVar9 + 0x240;
  } while (iVar9 != 0x1fa400);
  pcVar4 = this + 0x20dedc;
  do {
    cRBodPos::cRBodPos((cRBodPos *)(pcVar4 + 4));
    *(int *)(pcVar4 + 4) = *(int *)(iVar8 + iVar1) + 8;
    cRBod::cRBod((cRBod *)(pcVar4 + 0xa4));
    pcVar4 = pcVar4 + 0xdc;
    **(int **)(iVar8 + iVar2) = **(int **)(iVar8 + iVar2) + 1;
    iVar3 = DAT_00026048;
  } while (pcVar4 != this + 0x2cf49c);
  iVar6 = 0;
  do {
    this_00 = (cRBod *)(this + iVar6 + 0x310004);
    cRBod::cRBod(this_00);
    iVar9 = *(int *)(iVar8 + iVar3) + 8;
    *(int *)(this + iVar6 + 0x310004) = iVar9;
    cRBod::cRBod(this_00 + 0x54);
    cRBod::cRBod(this_00 + 0x90);
    iVar6 = iVar6 + 0x120;
    *(int *)(this_00 + 0x90) = iVar9;
    cRBod::cRBod(this_00 + 0xe4);
  } while (iVar6 != 0x5b20);
  cRBod::cRBod((cRBod *)(this + 0x315b24));
  *(int *)(this + 0x315b24) = *(int *)(iVar8 + DAT_0002604c) + 8;
  iVar3 = 0;
  do {
    iVar6 = iVar3 + 0x1ac;
    tColour::tColour((tColour *)(this + iVar3 + 0x315ce4));
    iVar3 = iVar6;
  } while (iVar6 != 0x3580);
  cRBod::cRBod((cRBod *)(this + 0x3190dc));
  iVar3 = DAT_00026054;
  *(int *)(this + 0x3190dc) = *(int *)(iVar8 + DAT_00026050) + 8;
  cRObject::cRObject((cRObject *)(this + 0x319108));
  pcVar4 = this + 0x31f770;
  do {
    cRBod::cRBod((cRBod *)pcVar4);
    pcVar7 = pcVar4 + 0x80;
    *(int *)pcVar4 = *(int *)(iVar8 + iVar3) + 8;
    pcVar4 = pcVar7;
  } while (pcVar7 != this + 0x321070);
  iVar3 = 0;
  do {
    iVar6 = 0;
    do {
      iVar9 = iVar6 + iVar3;
      iVar6 = iVar6 + 0xa0;
      tColour::tColour((tColour *)(this + iVar9 + 0x32992c));
      iVar9 = DAT_00026058;
    } while (iVar6 != 0x640);
    iVar3 = iVar3 + 0x8e6c;
  } while (iVar3 != 0x11cd8);
  pcVar4 = this + 0x334610;
  do {
    cRBodPos::cRBodPos((cRBodPos *)pcVar4);
    pcVar7 = pcVar4 + 0x84;
    *(int *)pcVar4 = *(int *)(iVar8 + iVar9) + 8;
    pcVar4 = pcVar7;
  } while (pcVar7 != this + 0x334a30);
  return this;
}
