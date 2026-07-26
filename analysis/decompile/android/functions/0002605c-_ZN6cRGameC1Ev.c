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
  cRBod *this_00;
  int iVar2;
  cRGame *pcVar3;
  cRGame *pcVar4;

  *(undefined ***)this = &PTR_LevelInit_0009abe0;
  tColour::tColour((tColour *)(this + 0x14));
  cRBod::cRBod((cRBod *)(this + 0x68));
  this_00 = (cRBod *)(this + 0x138c);
  *(undefined ***)(this + 0x68) = &PTR_AI_0009ac10;
  cRBodPos::cRBodPos((cRBodPos *)(this + 0xd4));
  *(undefined ***)(this + 0xd4) = &PTR_AI_0009ac00;
  cRBodPos::cRBodPos((cRBodPos *)(this + 0x168));
  *(undefined ***)(this + 0x168) = &PTR_AI_0009ac30;
  tColour::tColour((tColour *)(this + 0x260));
  tColour::tColour((tColour *)(this + 0x270));
  cRBod::cRBod((cRBod *)(this + 0x32c));
  cRViewport::cRViewport((cRViewport *)(this + 0x364));
  cRViewport::cRViewport((cRViewport *)(this + 0x394));
  cRViewport::cRViewport((cRViewport *)(this + 0x3c4));
  cRBodPos::cRBodPos((cRBodPos *)(this + 0x3f4));
  *(undefined ***)(this + 0x3f4) = &PTR_AI_0009ac20;
  cRBodPos::cRBodPos((cRBodPos *)(this + 0x468));
  *(undefined ***)(this + 0x468) = &PTR_AI_0009ac30;
  cRBodPos::cRBodPos((cRBodPos *)(this + 0x528));
  *(undefined ***)(this + 0x528) = &PTR_AI_0009ac20;
  cRBodPos::cRBodPos((cRBodPos *)(this + 0x59c));
  *(undefined ***)(this + 0x59c) = &PTR_AI_0009ac30;
  cRBodPos::cRBodPos((cRBodPos *)(this + 0x65c));
  *(undefined ***)(this + 0x65c) = &PTR_AI_0009ac20;
  cRBodPos::cRBodPos((cRBodPos *)(this + 0x6d0));
  *(undefined ***)(this + 0x6d0) = &PTR_AI_0009ac30;
  cRBodPos::cRBodPos((cRBodPos *)(this + 0x790));
  *(undefined ***)(this + 0x790) = &PTR_AI_0009ac30;
  cRBod::cRBod((cRBod *)(this + 0xd14));
  *(undefined ***)(this + 0xd14) = &PTR_AI_0009ac40;
  do {
    cRBod::cRBod(this_00);
    *(undefined ***)this_00 = &PTR_AI_0009ac50;
    tColour::tColour((tColour *)(this_00 + 0x60));
    tColour::tColour((tColour *)(this_00 + 0x1a0));
    tColour::tColour((tColour *)(this_00 + 0x1b0));
    tColour::tColour((tColour *)(this_00 + 0x1c0));
    tColour::tColour((tColour *)(this_00 + 0x1d0));
    tColour::tColour((tColour *)(this_00 + 0x1e0));
    tColour::tColour((tColour *)(this_00 + 0x1f0));
    this_00 = this_00 + 0x71c;
  } while (this_00 != (cRBod *)(this + 0x43df4));
  iVar2 = 0;
  do {
    iVar1 = iVar2 + 0x43e24;
    iVar2 = iVar2 + 0x2c;
    cRBod::cRBod((cRBod *)(this + iVar1));
  } while (iVar2 != 0x3cac);
  pcVar4 = this + 0x47ad8;
  do {
    cRBod::cRBod((cRBod *)pcVar4);
    pcVar3 = pcVar4 + 0xb0;
    *(undefined ***)pcVar4 = &PTR_AI_0009ab90;
    pcVar4 = pcVar3;
  } while (pcVar3 != this + 0x4d2d8);
  cRBod::cRBod((cRBod *)(this + 0x4d2e0));
  *(undefined ***)(this + 0x4d2e0) = &PTR_AI_0009abf0;
  tColour::tColour((tColour *)(this + 0x4d384));
  tColour::tColour((tColour *)(this + 0x4d3a4));
  *(undefined4 *)(this + 0x4d324) = 0;
  cRBod::cRBod((cRBod *)(this + 0x4d440));
  *(undefined ***)(this + 0x4d440) = &PTR_AI_0009aca0;
  cRBod::cRBod((cRBod *)(this + 0x4d4c4));
  pcVar4 = this + 0x4d50c;
  do {
    cRBodPos::cRBodPos((cRBodPos *)pcVar4);
    pcVar3 = pcVar4 + 0x84;
    *(undefined ***)pcVar4 = &PTR_AI_0009ac90;
    pcVar4 = pcVar3;
  } while (pcVar3 != this + 0x6e50c);
  pcVar4 = this + 0x6e510;
  do {
    cRBodPos::cRBodPos((cRBodPos *)pcVar4);
    pcVar3 = pcVar4 + 0x84;
    *(undefined ***)pcVar4 = &PTR_AI_0009ac80;
    pcVar4 = pcVar3;
  } while (pcVar3 != this + 0x718a0);
  cRSubGame::cRSubGame((cRSubGame *)(this + 0x718a0));
  cRBod::cRBod((cRBod *)(this + 0x3a63d8));
  *(undefined ***)(this + 0x3a63d8) = &PTR_AI_0009ae20;
  return this;
}
