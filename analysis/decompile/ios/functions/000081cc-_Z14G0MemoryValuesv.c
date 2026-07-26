/*
 * mangled: _Z14G0MemoryValuesv
 * demangled: G0MemoryValues()
 * address: 000081cc
 * size: 1752
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* G0MemoryValues() */

void G0MemoryValues(void)

{
  undefined1 auStack_c8 [4];
  undefined4 *local_c4;
  undefined4 *local_c0;
  undefined4 *local_bc;
  undefined4 *local_b8;
  undefined4 *local_b4;
  undefined1 *local_b0;
  int local_ac;
  int local_a8;
  cRBod *local_a4;
  int local_a0;
  cRBod *local_9c;
  int local_98;
  undefined1 auStack_94 [4];
  undefined4 local_90;
  undefined *local_7c;
  undefined *local_78;
  undefined1 *local_74;
  undefined1 *local_70;
  undefined1 *local_6c;

  local_74 = &stack0xfffffff8;
  local_6c = auStack_c8;
  local_7c = PTR_001b615c;
  local_78 = &GCC_except_table5;
  local_70 = &LAB_000088a4;
  __Unwind_SjLj_Register(auStack_94);
  local_90 = 0xffffffff;
  wprintf("Size of cRGame %i\n",&DAT_00378444);
  wprintf("Size of cRSubGame %i\n",&DAT_00305734);
  wprintf("   Size of cRTutorial\t%i\n",0x1c);
  wprintf("   Size of cRSubTracks %i\n",0x1270);
  wprintf("   Size of cRSubSpeedUp %i\n",0xa8);
  wprintf("   Size of cRJetPack %i\n",0x178);
  wprintf("   Size of cRSubHealth %i\n",0x340);
  wprintf("   Size of cRSlug %i\n",0xe00);
  wprintf("   Size of cRSubLazerManager %i\n",0xcd0);
  wprintf("   Size of cRSaltManager %i\n",0x15e0);
  wprintf("   Size of cRSubGarbage %i\n",&DAT_000023f0);
  wprintf("   Size of cRSubRing %i\n",0x358);
  wprintf("   Size of cRFringeManager %i\n",0x6d64);
  wprintf("   Size of cRSubGoldy %i\n",0x4010);
  wprintf("   Size of cRSubLoc %i\n",0x1d0d80);
  wprintf("   Size of cRSubRow %i\n",770000);
  wprintf("   Size of cRSubHighScore %i\n",0x40820);
  wprintf("   Size of cRSubSolution %i\n",0x1fac0);
  wprintf("   Size of cRTimeTrial %i\n",0x330);
  wprintf("   Size of cRPathManager %i\n",1);
  wprintf("   Size of cRPath %i\n",0x5b20);
  wprintf("   Size of cRLandscapeManager %i\n",0x3588);
  wprintf("   Size of cRSMTracks %i\n",0x6544);
  wprintf("   Size of cRParcelManager %i\n",0x1900);
  wprintf("   Size of cRGUI %i\n",0x28);
  wprintf("   Size of cRGalaxy %i\n",0x8e6c);
  wprintf("   Size of cREnemyManager %i\n",0x1804);
  wprintf("   Size of cRCompletion %i\n",0x4c);
  wprintf("   Size of cRTimesUp %i\n",0x10);
  wprintf("Size of cRSubHighScore %i\n",0x40820);
  wprintf("Size of cRBod %i\n",0x2c);
  wprintf("Size of cRObject %i\n",0x110);
  wprintf("Size of cRSubLoc %i\n",0x44);
  wprintf("Size of cRBorder %i\n",0x71c);
  wprintf("Solutions %i\n",0x40820);
  local_c4 = operator_new(0x378444);
  *local_c4 = PTR_vtable_001b6120 + 8;
  local_90 = 1;
  tColour::tColour((tColour *)(local_c4 + 5));
  cRBod::cRBod((cRBod *)(local_c4 + 0x1a));
  local_c4[0x1a] = PTR_vtable_001b6178 + 8;
  cRBodPos::cRBodPos((cRBodPos *)(local_c4 + 0x35));
  local_c4[0x35] = PTR_vtable_001b6168 + 8;
  cRBodPos::cRBodPos((cRBodPos *)(local_c4 + 0x5a));
  local_c4[0x5a] = PTR_vtable_001b6154 + 8;
  tColour::tColour((tColour *)(local_c4 + 0x98));
  tColour::tColour((tColour *)(local_c4 + 0x9c));
  cRBod::cRBod((cRBod *)(local_c4 + 0xcb));
  cRViewport::cRViewport((cRViewport *)(local_c4 + 0xd9));
  cRViewport::cRViewport((cRViewport *)(local_c4 + 0xe5));
  cRViewport::cRViewport((cRViewport *)(local_c4 + 0xf1));
  cRBodPos::cRBodPos((cRBodPos *)(local_c4 + 0xfd));
  local_c4[0xfd] = PTR_vtable_001b6130 + 8;
  cRBodPos::cRBodPos((cRBodPos *)(local_c4 + 0x11a));
  local_c4[0x11a] = PTR_vtable_001b6154 + 8;
  cRBodPos::cRBodPos((cRBodPos *)(local_c4 + 0x14a));
  local_c4[0x14a] = PTR_vtable_001b6130 + 8;
  cRBodPos::cRBodPos((cRBodPos *)(local_c4 + 0x167));
  local_c4[0x167] = PTR_vtable_001b6154 + 8;
  cRBodPos::cRBodPos((cRBodPos *)(local_c4 + 0x197));
  local_c4[0x197] = PTR_vtable_001b6130 + 8;
  cRBodPos::cRBodPos((cRBodPos *)(local_c4 + 0x1b4));
  local_c4[0x1b4] = PTR_vtable_001b6154 + 8;
  cRBodPos::cRBodPos((cRBodPos *)(local_c4 + 0x1e4));
  local_c4[0x1e4] = PTR_vtable_001b6154 + 8;
  cRBod::cRBod((cRBod *)(local_c4 + 0x345));
  local_c0 = local_c4 + 0x4e3;
  local_c4[0x345] = PTR_vtable_001b6198 + 8;
  local_a0 = 0;
  do {
    local_90 = 1;
    local_98 = (int)local_c0 + local_a0;
    cRBod::cRBod((cRBod *)((int)local_c0 + local_a0));
    *(undefined **)(local_a0 + (int)local_c0) = PTR_vtable_001b6188 + 8;
    tColour::tColour((tColour *)(local_98 + 0x60));
    tColour::tColour((tColour *)(local_98 + 0x1a0));
    tColour::tColour((tColour *)(local_98 + 0x1b0));
    tColour::tColour((tColour *)(local_98 + 0x1c0));
    tColour::tColour((tColour *)(local_98 + 0x1d0));
    tColour::tColour((tColour *)(local_98 + 0x1e0));
    tColour::tColour((tColour *)(local_98 + 0x1f0));
    local_a0 = local_a0 + 0x71c;
  } while (local_a0 != 0x42a68);
  local_a4 = (cRBod *)(local_c4 + 0x10f89);
  local_a0 = 0x42a68;
  local_9c = local_a4;
  do {
    local_90 = 1;
    cRBod::cRBod(local_a4);
    local_a4 = local_a4 + 0x2c;
  } while (local_a4 != local_9c + 0x3cac);
  local_a8 = 0;
  local_bc = local_c4 + 0x11eb6;
  do {
    local_90 = 1;
    cRBod::cRBod((cRBod *)((int)local_bc + local_a8));
    *(undefined ***)(local_a8 + (int)local_bc) = &PTR_AI_001b6ac4;
    local_a8 = local_a8 + 0xb0;
  } while (local_a8 != 0x5800);
  cRBod::cRBod((cRBod *)(local_c4 + 0x134b8));
  local_c4[0x134b8] = PTR_vtable_001b61b4 + 8;
  tColour::tColour((tColour *)(local_c4 + 0x13997));
  tColour::tColour((tColour *)(local_c4 + 0x1399f));
  cRBod::cRBod((cRBod *)(local_c4 + 0x139c6));
  local_c4[0x139c6] = PTR_vtable_001b61b0 + 8;
  cRBod::cRBod((cRBod *)(local_c4 + 0x139e7));
  local_ac = 0;
  local_b8 = local_c4 + 0x139f9;
  do {
    local_90 = 1;
    cRBodPos::cRBodPos((cRBodPos *)((int)local_b8 + local_ac));
    *(undefined **)(local_ac + (int)local_b8) = PTR_vtable_001b617c + 8;
    local_ac = local_ac + 0x84;
  } while (local_ac != 0x21000);
  local_b0 = (undefined1 *)0x0;
  local_b4 = local_c4 + 0x1bdfa;
  local_ac = 0x21000;
  do {
    local_90 = 1;
    cRBodPos::cRBodPos((cRBodPos *)(local_b0 + (int)local_b4));
    *(undefined **)(local_b0 + (int)local_b4) = PTR_vtable_001b616c + 8;
    local_b0 = local_b0 + 0x84;
  } while (local_b0 != &LAB_00003390);
  cRSubGame::cRSubGame((cRSubGame *)(local_c4 + 0x1cade));
  cRBod::cRBod((cRBod *)(local_c4 + 0xde0ed));
  local_c4[0xde0ed] = PTR_vtable_001b6140 + 8;
  _Game = local_c4;
  local_90 = 0xffffffff;
  wprintf("BodCount=%i  Memory=%i\n",*(int *)PTR__gBodCount_001b61ac,
          *(int *)PTR__gBodCount_001b61ac * 0x2c);
  wprintf("LocCount=%i Memory=%i\n",_gLocCount,_gLocCount * 0x44);
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
