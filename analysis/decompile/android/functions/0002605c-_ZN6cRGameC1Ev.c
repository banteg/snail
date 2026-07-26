/*
 * mangled: _ZN6cRGameC1Ev
 * demangled: cRGame::cRGame()
 * address: 0002605c
 * size: 776
 */

/* cRGame::cRGame() */

cRGame * __thiscall cRGame::cRGame(cRGame *this)

{
  int iVar1;
  int iVar2;
  cRBod *this_00;
  cRGame *pcVar3;
  cRGame *pcVar4;
  int iVar5;
  int iVar6;
  int iVar7;

  iVar2 = DAT_00026374;
  iVar1 = DAT_00026370;
  iVar6 = DAT_0002636c;
  iVar5 = DAT_00026364 + 0x26074;
  *(int *)this = *(int *)(iVar5 + DAT_00026368) + 8;
  tColour::tColour((tColour *)(this + 0x14));
  cRBod::cRBod((cRBod *)(this + 0x68));
  this_00 = (cRBod *)(this + 0x138c);
  *(int *)(this + 0x68) = *(int *)(iVar5 + DAT_00026378) + 8;
  cRBodPos::cRBodPos((cRBodPos *)(this + 0xd4));
  *(int *)(this + 0xd4) = *(int *)(iVar5 + DAT_0002637c) + 8;
  cRBodPos::cRBodPos((cRBodPos *)(this + 0x168));
  iVar7 = *(int *)(iVar5 + iVar6) + 8;
  *(int *)(this + 0x168) = iVar7;
  tColour::tColour((tColour *)(this + 0x260));
  tColour::tColour((tColour *)(this + 0x270));
  cRBod::cRBod((cRBod *)(this + 0x32c));
  cRViewport::cRViewport((cRViewport *)(this + 0x364));
  cRViewport::cRViewport((cRViewport *)(this + 0x394));
  cRViewport::cRViewport((cRViewport *)(this + 0x3c4));
  cRBodPos::cRBodPos((cRBodPos *)(this + 0x3f4));
  iVar6 = *(int *)(iVar5 + iVar1) + 8;
  *(int *)(this + 0x3f4) = iVar6;
  cRBodPos::cRBodPos((cRBodPos *)(this + 0x468));
  *(int *)(this + 0x468) = iVar7;
  cRBodPos::cRBodPos((cRBodPos *)(this + 0x528));
  *(int *)(this + 0x528) = iVar6;
  cRBodPos::cRBodPos((cRBodPos *)(this + 0x59c));
  *(int *)(this + 0x59c) = iVar7;
  cRBodPos::cRBodPos((cRBodPos *)(this + 0x65c));
  *(int *)(this + 0x65c) = iVar6;
  cRBodPos::cRBodPos((cRBodPos *)(this + 0x6d0));
  *(int *)(this + 0x6d0) = iVar7;
  cRBodPos::cRBodPos((cRBodPos *)(this + 0x790));
  *(int *)(this + 0x790) = iVar7;
  cRBod::cRBod((cRBod *)(this + 0xd14));
  *(int *)(this + 0xd14) = *(int *)(iVar5 + DAT_00026380) + 8;
  do {
    cRBod::cRBod(this_00);
    *(int *)this_00 = *(int *)(iVar5 + iVar2) + 8;
    tColour::tColour((tColour *)(this_00 + 0x60));
    tColour::tColour((tColour *)(this_00 + 0x1a0));
    tColour::tColour((tColour *)(this_00 + 0x1b0));
    tColour::tColour((tColour *)(this_00 + 0x1c0));
    tColour::tColour((tColour *)(this_00 + 0x1d0));
    tColour::tColour((tColour *)(this_00 + 0x1e0));
    tColour::tColour((tColour *)(this_00 + 0x1f0));
    this_00 = this_00 + 0x71c;
  } while (this_00 != (cRBod *)(this + 0x43df4));
  iVar6 = 0;
  do {
    iVar1 = iVar6 + 0x43e24;
    iVar6 = iVar6 + 0x2c;
    cRBod::cRBod((cRBod *)(this + iVar1));
    iVar1 = DAT_00026384;
  } while (iVar6 != 0x3cac);
  pcVar4 = this + 0x47ad8;
  do {
    cRBod::cRBod((cRBod *)pcVar4);
    pcVar3 = pcVar4 + 0xb0;
    *(int *)pcVar4 = *(int *)(iVar5 + iVar1) + 8;
    pcVar4 = pcVar3;
  } while (pcVar3 != this + 0x4d2d8);
  cRBod::cRBod((cRBod *)(this + 0x4d2e0));
  iVar6 = DAT_0002638c;
  *(int *)(this + 0x4d2e0) = *(int *)(iVar5 + DAT_00026388) + 8;
  tColour::tColour((tColour *)(this + 0x4d384));
  tColour::tColour((tColour *)(this + 0x4d3a4));
  *(undefined4 *)(this + 0x4d324) = 0;
  cRBod::cRBod((cRBod *)(this + 0x4d440));
  *(int *)(this + 0x4d440) = *(int *)(iVar5 + DAT_00026390) + 8;
  cRBod::cRBod((cRBod *)(this + 0x4d4c4));
  pcVar4 = this + 0x4d50c;
  do {
    cRBodPos::cRBodPos((cRBodPos *)pcVar4);
    pcVar3 = pcVar4 + 0x84;
    *(int *)pcVar4 = *(int *)(iVar5 + iVar6) + 8;
    iVar1 = DAT_00026394;
    pcVar4 = pcVar3;
  } while (pcVar3 != this + 0x6e50c);
  pcVar4 = this + 0x6e510;
  do {
    cRBodPos::cRBodPos((cRBodPos *)pcVar4);
    pcVar3 = pcVar4 + 0x84;
    *(int *)pcVar4 = *(int *)(iVar5 + iVar1) + 8;
    pcVar4 = pcVar3;
  } while (pcVar3 != this + 0x718a0);
  cRSubGame::cRSubGame((cRSubGame *)(this + 0x718a0));
  cRBod::cRBod((cRBod *)(this + 0x3a63d8));
  *(int *)(this + 0x3a63d8) = *(int *)(iVar5 + DAT_00026398) + 8;
  return this;
}
