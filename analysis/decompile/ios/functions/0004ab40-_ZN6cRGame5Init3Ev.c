/*
 * mangled: _ZN6cRGame5Init3Ev
 * demangled: cRGame::Init3()
 * address: 0004ab40
 * size: 9960
 */

/* cRGame::Init3() */

void __thiscall cRGame::Init3(cRGame *this)

{
  int iVar1;
  undefined *puVar2;
  undefined *puVar3;
  cRObject *pcVar4;
  char *pcVar5;
  undefined4 uVar6;
  cRDirectX *this_00;
  uint uVar7;
  char *pcVar8;
  uint *puVar9;
  char cVar10;
  int iVar11;
  cRGame *pcVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  cRGame *pcVar17;
  uint in_fpscr;
  float fVar18;
  int local_100;
  int local_f4;
  int local_ec;
  char local_e8 [128];
  tMatrix atStack_68 [48];
  undefined4 local_38;

  wprintf("GameInit3\n");
  puVar2 = PTR__gObjectList_001b61cc;
  pcVar12 = this + 0x44370;
  iVar13 = 0;
  do {
    pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
    iVar16 = iVar13 * 0x2c;
    cRBod::SetObject((cRBod *)(this + iVar16 + 0x4434c),pcVar4);
    iVar15 = iVar13 + 1;
    fVar18 = (float)VectorSignedToFloat(iVar13,(byte)(in_fpscr >> 0x16) & 3);
    ObjectProcTileFloorFast(*(cRObject **)pcVar12,"Objects/World00/Surface0.tga",fVar18);
    cRObject::ApplyUV(*(cRObject **)pcVar12,0.25,0.0);
    pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
    cRBod::SetObject((cRBod *)(this + iVar16 + 0x444ac),pcVar4);
    ObjectProcTileFloorFast(*(cRObject **)(pcVar12 + 0x160),"Objects/World00/Surface0.tga",fVar18);
    cRObject::ApplyUV(*(cRObject **)(pcVar12 + 0x160),0.25,0.75);
    pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
    cRBod::SetObject((cRBod *)(this + iVar16 + 0x4460c),pcVar4);
    ObjectProcTileFloorFast(*(cRObject **)(pcVar12 + 0x2c0),"Objects/World00/Surface0.tga",fVar18);
    cRObject::ApplyUV(*(cRObject **)(pcVar12 + 0x2c0),0.25,0.25);
    pcVar12 = pcVar12 + 0x2c;
    iVar13 = iVar15;
  } while (iVar15 != 8);
  tMatrix::Identity(atStack_68);
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x441ec),pcVar4);
  this_00 = (cRDirectX *)(this + 0x47ad0);
  **(uint **)(this + 0x44210) = **(uint **)(this + 0x44210) | 0x1000;
  cRDirectX::Load(this_00,"pillar1.x",*(cRObject **)(this + 0x44210),1);
  if ((**(uint **)(this + 0x44210) & 0x2000000) == 0) {
    local_38 = 0;
    cRBod::ApplyPos((tMatrix *)(this + 0x441ec));
  }
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x44218),pcVar4);
  **(uint **)(this + 0x4423c) = **(uint **)(this + 0x4423c) | 0x1000;
  cRDirectX::Load(this_00,"pillar2.x",*(cRObject **)(this + 0x4423c),1);
  if ((**(uint **)(this + 0x4423c) & 0x2000000) == 0) {
    local_38 = 0x3f000000;
    cRBod::ApplyPos((tMatrix *)(this + 0x44218));
  }
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x44244),pcVar4);
  **(uint **)(this + 0x44268) = **(uint **)(this + 0x44268) | 0x1000;
  cRDirectX::Load(this_00,"pillar3.x",*(cRObject **)(this + 0x44268),1);
  if ((**(uint **)(this + 0x44268) & 0x2000000) == 0) {
    local_38 = 0x3f800000;
    cRBod::ApplyPos((tMatrix *)(this + 0x44244));
  }
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x44270),pcVar4);
  **(uint **)(this + 0x44294) = **(uint **)(this + 0x44294) | 0x1000;
  cRDirectX::Load(this_00,"pillar4.x",*(cRObject **)(this + 0x44294),1);
  if ((**(uint **)(this + 0x44294) & 0x2000000) == 0) {
    local_38 = 0x3fc00000;
    cRBod::ApplyPos((tMatrix *)(this + 0x44270));
  }
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x4429c),pcVar4);
  **(uint **)(this + 0x442c0) = **(uint **)(this + 0x442c0) | 0x1000;
  cRDirectX::Load(this_00,"pillar5.x",*(cRObject **)(this + 0x442c0),1);
  if ((**(uint **)(this + 0x442c0) & 0x2000000) == 0) {
    local_38 = 0x40000000;
    cRBod::ApplyPos((tMatrix *)(this + 0x4429c));
  }
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x442c8),pcVar4);
  **(uint **)(this + 0x442ec) = **(uint **)(this + 0x442ec) | 0x1000;
  cRDirectX::Load(this_00,"pillar6.x",*(cRObject **)(this + 0x442ec),1);
  if ((**(uint **)(this + 0x442ec) & 0x2000000) == 0) {
    local_38 = 0x40200000;
    cRBod::ApplyPos((tMatrix *)(this + 0x442c8));
  }
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x442f4),pcVar4);
  **(uint **)(this + 0x44318) = **(uint **)(this + 0x44318) | 0x1000;
  cRDirectX::Load(this_00,"pillar7.x",*(cRObject **)(this + 0x44318),1);
  if ((**(uint **)(this + 0x44318) & 0x2000000) == 0) {
    local_38 = 0x40400000;
    cRBod::ApplyPos((tMatrix *)(this + 0x442f4));
  }
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x44320),pcVar4);
  **(uint **)(this + 0x44344) = **(uint **)(this + 0x44344) | 0x1000;
  cRDirectX::Load(this_00,"pillar8.x",*(cRObject **)(this + 0x44344),1);
  if ((**(uint **)(this + 0x44344) & 0x2000000) == 0) {
    local_38 = 0x40600000;
    cRBod::ApplyPos((tMatrix *)(this + 0x44320));
  }
  **(uint **)(this + 0x44210) = **(uint **)(this + 0x44210) & 0xffefffff;
  *(undefined4 *)(*(int *)(this + 0x44210) + 8) = 0;
  **(uint **)(this + 0x4423c) = **(uint **)(this + 0x4423c) & 0xffefffff;
  *(undefined4 *)(*(int *)(this + 0x4423c) + 8) = 0;
  **(uint **)(this + 0x44268) = **(uint **)(this + 0x44268) & 0xffefffff;
  *(undefined4 *)(*(int *)(this + 0x44268) + 8) = 0;
  **(uint **)(this + 0x44294) = **(uint **)(this + 0x44294) & 0xffefffff;
  *(undefined4 *)(*(int *)(this + 0x44294) + 8) = 0;
  **(uint **)(this + 0x442c0) = **(uint **)(this + 0x442c0) & 0xffefffff;
  *(undefined4 *)(*(int *)(this + 0x442c0) + 8) = 0;
  **(uint **)(this + 0x442ec) = **(uint **)(this + 0x442ec) & 0xffefffff;
  *(undefined4 *)(*(int *)(this + 0x442ec) + 8) = 0;
  **(uint **)(this + 0x44318) = **(uint **)(this + 0x44318) & 0xffefffff;
  *(undefined4 *)(*(int *)(this + 0x44318) + 8) = 0;
  **(uint **)(this + 0x44344) = **(uint **)(this + 0x44344) & 0xffefffff;
  *(undefined4 *)(*(int *)(this + 0x44344) + 8) = 0;
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x4476c),pcVar4);
  ObjectProcTileFast(*(cRObject **)(this + 0x44790),"Objects/Universe/Ramp.tga",0.0);
  ObjectProcTileFastRamp(-1,*(cRObject **)(this + 0x44790));
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x44798),pcVar4);
  ObjectProcTileFast(*(cRObject **)(this + 0x447bc),"Objects/Universe/Ramp.tga",0.0);
  ObjectProcTileFastRamp(0,*(cRObject **)(this + 0x447bc));
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x447c4),pcVar4);
  ObjectProcTileFast(*(cRObject **)(this + 0x447e8),"Objects/Universe/Ramp.tga",0.0);
  ObjectProcTileFastRamp(1,*(cRObject **)(this + 0x447e8));
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x43f00),pcVar4);
  ObjectProcTileFloorCornerFast(0,*(cRObject **)(this + 0x43f24),"Objects/World00/Surface0.tga");
  cRObject::ApplyUV(*(cRObject **)(this + 0x43f24),0.25,0.0);
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x43f2c),pcVar4);
  ObjectProcTileFloorCornerFast(1,*(cRObject **)(this + 0x43f50),"Objects/World00/Surface0.tga");
  cRObject::ApplyUV(*(cRObject **)(this + 0x43f50),0.25,0.0);
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x43f84),pcVar4);
  ObjectProcTileFloorCornerFast(2,*(cRObject **)(this + 0x43fa8),"Objects/World00/Surface0.tga");
  cRObject::ApplyUV(*(cRObject **)(this + 0x43fa8),0.25,0.0);
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x43f58),pcVar4);
  ObjectProcTileFloorCornerFast(3,*(cRObject **)(this + 0x43f7c),"Objects/World00/Surface0.tga");
  cRObject::ApplyUV(*(cRObject **)(this + 0x43f7c),0.25,0.0);
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x43fb0),pcVar4);
  ObjectProcTileFloorCornerFast(0,*(cRObject **)(this + 0x43fd4),"Objects/World00/Surface0.tga");
  cRObject::ApplyUV(*(cRObject **)(this + 0x43fd4),0.25,0.75);
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x43fdc),pcVar4);
  ObjectProcTileFloorCornerFast(1,*(cRObject **)(this + 0x44000),"Objects/World00/Surface0.tga");
  cRObject::ApplyUV(*(cRObject **)(this + 0x44000),0.25,0.75);
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x44034),pcVar4);
  ObjectProcTileFloorCornerFast(2,*(cRObject **)(this + 0x44058),"Objects/World00/Surface0.tga");
  cRObject::ApplyUV(*(cRObject **)(this + 0x44058),0.25,0.75);
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x44008),pcVar4);
  ObjectProcTileFloorCornerFast(3,*(cRObject **)(this + 0x4402c),"Objects/World00/Surface0.tga");
  cRObject::ApplyUV(*(cRObject **)(this + 0x4402c),0.25,0.75);
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x44060),pcVar4);
  ObjectProcTileFloorCornerFast(0,*(cRObject **)(this + 0x44084),"Objects/World00/Surface0.tga");
  cRObject::ApplyUV(*(cRObject **)(this + 0x44084),0.25,0.25);
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x4408c),pcVar4);
  ObjectProcTileFloorCornerFast(1,*(cRObject **)(this + 0x440b0),"Objects/World00/Surface0.tga");
  cRObject::ApplyUV(*(cRObject **)(this + 0x440b0),0.25,0.25);
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x440e4),pcVar4);
  ObjectProcTileFloorCornerFast(2,*(cRObject **)(this + 0x44108),"Objects/World00/Surface0.tga");
  cRObject::ApplyUV(*(cRObject **)(this + 0x44108),0.25,0.25);
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x440b8),pcVar4);
  ObjectProcTileFloorCornerFast(3,*(cRObject **)(this + 0x440dc),"Objects/World00/Surface0.tga");
  cRObject::ApplyUV(*(cRObject **)(this + 0x440dc),0.25,0.25);
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x44110),pcVar4);
  **(uint **)(this + 0x44134) = **(uint **)(this + 0x44134) | 0x1000;
  cRDirectX::Load(this_00,"Tramp.x",*(cRObject **)(this + 0x44134),1);
  *(undefined4 *)(*(int *)(this + 0x44134) + 8) = 1;
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x43e24),pcVar4);
  ObjectProcTileFast(*(cRObject **)(this + 0x43e48),"Objects/Universe/Hole.tga",0.0);
  *(undefined4 *)(*(int *)(this + 0x43e48) + 8) = 5;
  puVar9 = *(uint **)(*(int *)(*(int *)(this + 0x43e48) + 200) + 0xc);
  *puVar9 = *puVar9 | 0x400;
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x447f0),pcVar4);
  ObjectTextLoad("Objects/Lazer",*(cRObject **)(this + 0x44814));
  pcVar12 = this + 0x76724;
  pcVar17 = this + 0x72b78;
  iVar13 = 0;
  do {
    iVar16 = iVar13;
    cRBod::SetObject((cRBod *)(this + iVar16 * 0xa4 + 0x766a8),*(cRObject **)(this + 0x44814));
    puVar9 = *(uint **)(*(int *)(*(int *)(pcVar12 + -0x58) + 200) + 0xc);
    *puVar9 = *puVar9 | 0x400;
    *(cRGame **)pcVar12 = pcVar17;
    tColourSmall::Set((tColourSmall *)(this + iVar16 * 0xa4 + 0x766d0),1.0,1.0,1.0,0.7);
    *(undefined4 *)(*(int *)(pcVar12 + -0x58) + 8) = 5;
    *(uint *)(pcVar12 + -0x78) = *(uint *)(pcVar12 + -0x78) | 0x80;
    pcVar12 = pcVar12 + 0xa4;
    iVar13 = iVar16 + 1;
  } while (iVar16 + 1 != 0x14);
  iVar16 = iVar16 + -0x12;
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)PTR__gObjectList_001b61cc);
  cRBod::SetObject((cRBod *)(this + 0x47aa4),pcVar4);
  ObjectTextLoad("Objects/TrampRing",*(cRObject **)(this + 0x47ac8));
  cRBod::SetObject((cRBod *)(this + 0x377e8c),*(cRObject **)(this + 0x47ac8));
  puVar9 = *(uint **)(*(int *)(*(int *)(this + 0x377eb0) + 200) + 0xc);
  *puVar9 = *puVar9 | 0x400;
  *(cRGame **)(this + 0x377f0c) = pcVar17;
  *(int *)(*(int *)(this + 0x377eb0) + 8) = iVar16;
  tMatrix::Identity((tMatrix *)(this + 0x377eb8));
  cRBod::SetObject((cRBod *)(this + 0x377f10),*(cRObject **)(this + 0x47ac8));
  puVar9 = *(uint **)(*(int *)(*(int *)(this + 0x377f34) + 200) + 0xc);
  *puVar9 = *puVar9 | 0x400;
  *(cRGame **)(this + 0x377f90) = pcVar17;
  *(int *)(*(int *)(this + 0x377f34) + 8) = iVar16;
  tMatrix::Identity((tMatrix *)(this + 0x377f3c));
  cRBod::SetObject((cRBod *)(this + 0x377f94),*(cRObject **)(this + 0x47ac8));
  puVar9 = *(uint **)(*(int *)(*(int *)(this + 0x377fb8) + 200) + 0xc);
  *puVar9 = *puVar9 | 0x400;
  *(cRGame **)(this + 0x378014) = pcVar17;
  *(int *)(*(int *)(this + 0x377fb8) + 8) = iVar16;
  tMatrix::Identity((tMatrix *)(this + 0x377fc0));
  cRBod::SetObject((cRBod *)(this + 0x378018),*(cRObject **)(this + 0x47ac8));
  puVar9 = *(uint **)(*(int *)(*(int *)(this + 0x37803c) + 200) + 0xc);
  *puVar9 = *puVar9 | 0x400;
  *(cRGame **)(this + 0x378098) = pcVar17;
  *(int *)(*(int *)(this + 0x37803c) + 8) = iVar16;
  tMatrix::Identity((tMatrix *)(this + 0x378044));
  cRBod::SetObject((cRBod *)(this + 0x37809c),*(cRObject **)(this + 0x47ac8));
  puVar9 = *(uint **)(*(int *)(*(int *)(this + 0x3780c0) + 200) + 0xc);
  *puVar9 = *puVar9 | 0x400;
  *(cRGame **)(this + 0x37811c) = pcVar17;
  *(int *)(*(int *)(this + 0x3780c0) + 8) = iVar16;
  tMatrix::Identity((tMatrix *)(this + 0x3780c8));
  cRBod::SetObject((cRBod *)(this + 0x378120),*(cRObject **)(this + 0x47ac8));
  puVar9 = *(uint **)(*(int *)(*(int *)(this + 0x378144) + 200) + 0xc);
  *puVar9 = *puVar9 | 0x400;
  *(cRGame **)(this + 0x3781a0) = pcVar17;
  *(int *)(*(int *)(this + 0x378144) + 8) = iVar16;
  tMatrix::Identity((tMatrix *)(this + 0x37814c));
  cRBod::SetObject((cRBod *)(this + 0x3781a4),*(cRObject **)(this + 0x47ac8));
  puVar9 = *(uint **)(*(int *)(*(int *)(this + 0x3781c8) + 200) + 0xc);
  *puVar9 = *puVar9 | 0x400;
  *(cRGame **)(this + 0x378224) = pcVar17;
  *(int *)(*(int *)(this + 0x3781c8) + 8) = iVar16;
  tMatrix::Identity((tMatrix *)(this + 0x3781d0));
  cRBod::SetObject((cRBod *)(this + 0x378228),*(cRObject **)(this + 0x47ac8));
  puVar9 = *(uint **)(*(int *)(*(int *)(this + 0x37824c) + 200) + 0xc);
  *puVar9 = *puVar9 | 0x400;
  *(cRGame **)(this + 0x3782a8) = pcVar17;
  *(int *)(*(int *)(this + 0x37824c) + 8) = iVar16;
  tMatrix::Identity((tMatrix *)(this + 0x378254));
  cRSubTrampRingManager::Init((cRSubTrampRingManager *)(this + 0x377e8c));
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)PTR__gObjectList_001b61cc);
  cRBod::SetObject((cRBod *)(this + 0x47a78),pcVar4);
  **(uint **)(this + 0x47a9c) = **(uint **)(this + 0x47a9c) | 0x1000;
  cRDirectX::Load(this_00,"salt.x",*(cRObject **)(this + 0x47a9c),iVar16);
  cRBod::SetObject((cRBod *)(this + 0x77378),*(cRObject **)(this + 0x47a9c));
  *(cRGame **)(this + 0x773f4) = pcVar17;
  tColourSmall::Set((tColourSmall *)(this + 0x773a0),1.0,1.0,1.0,0.9);
  pcVar12 = this + 0x77480;
  *(int *)(*(int *)(this + 0x7739c) + 8) = iVar16;
  tMatrix::Identity((tMatrix *)(this + 0x773a4));
  do {
    iVar15 = iVar16;
    iVar13 = iVar15 * 0x8c;
    cRBod::SetObject((cRBod *)(this + iVar13 + 0x77378),*(cRObject **)(this + 0x47a9c));
    *(cRGame **)pcVar12 = pcVar17;
    tColourSmall::Set((tColourSmall *)(this + iVar13 + 0x773a0),1.0,1.0,1.0,0.9);
    *(undefined4 *)(*(int *)(pcVar12 + -0x58) + 8) = 1;
    pcVar12 = pcVar12 + 0x8c;
    tMatrix::Identity((tMatrix *)(this + iVar13 + 0x773a4));
    iVar16 = iVar15 + 1;
  } while (iVar15 + 1 != 0x28);
  iVar15 = iVar15 + -0x27;
  do {
    iVar13 = iVar15 * 0x10;
    local_100 = iVar15 << 2;
    pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)PTR__gObjectList_001b61cc);
    cRBod::SetObject((cRBod *)(this + iVar15 * 0x54 + 0x78958),pcVar4);
    if (iVar15 == 0) {
      iVar13 = 0x10;
      **(uint **)(this + 0x7897c) = **(uint **)(this + 0x7897c) | 0x1000;
      cRDirectX::Load(this_00,"postofficestop.x",*(cRObject **)(this + 0x7897c),1);
      *(undefined4 *)(this + 0x78970) = 0;
      *(undefined4 *)(this + 0x7896c) = 0;
      *(undefined4 *)(this + 0x78968) = 0;
      *(undefined4 *)(this + 0x789a4) = 0;
      puVar2 = PTR__gObjectList_001b61cc;
      *(undefined4 *)(this + 0x78984) = 0;
      *(undefined4 *)(this + 0x789a8) = 0x3be38e39;
      *(cRGame **)(this + 0x78994) = pcVar17;
      pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
      iVar15 = 1;
      cRBod::SetObject((cRBod *)(this + 0x789ac),pcVar4);
      local_100 = 4;
    }
    **(uint **)(this + 0x789d0) = **(uint **)(this + 0x789d0) | 0x1000;
    cRDirectX::Load(this_00,"postofficestop.x",*(cRObject **)(this + 0x789d0),1);
    iVar13 = iVar13 - local_100;
    *(int *)(this + iVar13 * 7 + 0x78984) = iVar15;
    *(undefined4 *)(this + iVar13 * 7 + 0x78970) = 0;
    iVar15 = iVar15 + 1;
    *(cRGame **)(this + iVar13 * 7 + 0x78994) = pcVar17;
    *(undefined4 *)(this + iVar13 * 7 + 0x7896c) = 0;
    *(undefined4 *)(this + iVar13 * 7 + 0x78968) = 0;
    *(undefined4 *)(this + iVar13 * 7 + 0x789a4) = 0;
    *(undefined4 *)(this + iVar13 * 7 + 0x789a8) = 0x3be38e39;
  } while (iVar15 < 2);
  if ((*(uint *)(this + 0x751d0) & 0x200) == 0) {
    if (*(int *)(this + 0x35c) == 0) {
      *(cRGame **)(this + 0x35c) = this + 0x751cc;
      *(undefined4 *)(this + 0x751d4) = 0;
      *(undefined4 *)(this + 0x751d8) = 0;
    }
    else {
      *(cRGame **)(*(int *)(this + 0x35c) + 8) = this + 0x751cc;
      *(int *)(*(int *)(*(int *)(this + 0x35c) + 8) + 0xc) = *(int *)(this + 0x35c);
      iVar13 = *(int *)(*(int *)(this + 0x35c) + 8);
      *(int *)(this + 0x35c) = iVar13;
      *(undefined4 *)(iVar13 + 8) = 0;
    }
    *(uint *)(this + 0x751d0) = *(uint *)(this + 0x751d0) | 0x200;
  }
  else {
    RShellError("List ADD");
  }
  pcVar12 = this + 0x7511c;
  if ((*(uint *)(this + 0x75120) & 0x200) == 0) {
    if (*(int *)(this + 0x35c) == 0) {
      *(cRGame **)(this + 0x35c) = pcVar12;
      *(undefined4 *)(this + 0x75124) = 0;
      *(undefined4 *)(this + 0x75128) = 0;
    }
    else {
      *(cRGame **)(*(int *)(this + 0x35c) + 8) = pcVar12;
      *(int *)(*(int *)(*(int *)(this + 0x35c) + 8) + 0xc) = *(int *)(this + 0x35c);
      iVar13 = *(int *)(*(int *)(this + 0x35c) + 8);
      *(int *)(this + 0x35c) = iVar13;
      *(undefined4 *)(iVar13 + 8) = 0;
    }
    *(uint *)(this + 0x75120) = *(uint *)(this + 0x75120) | 0x200;
  }
  else {
    RShellError("List ADD");
  }
  if ((*(uint *)(this + 0x7514c) & 0x200) == 0) {
    if (*(int *)(this + 0x35c) == 0) {
      *(cRGame **)(this + 0x35c) = this + 0x75148;
      *(undefined4 *)(this + 0x75150) = 0;
      *(undefined4 *)(this + 0x75154) = 0;
    }
    else {
      *(cRGame **)(*(int *)(this + 0x35c) + 8) = this + 0x75148;
      *(int *)(*(int *)(*(int *)(this + 0x35c) + 8) + 0xc) = *(int *)(this + 0x35c);
      iVar13 = *(int *)(*(int *)(this + 0x35c) + 8);
      *(int *)(this + 0x35c) = iVar13;
      *(undefined4 *)(iVar13 + 8) = 0;
    }
    *(uint *)(this + 0x7514c) = *(uint *)(this + 0x7514c) | 0x200;
  }
  else {
    RShellError("List ADD");
  }
  if ((*(uint *)(this + 0x75178) & 0x200) == 0) {
    if (*(int *)(this + 0x35c) == 0) {
      *(cRGame **)(this + 0x35c) = this + 0x75174;
      *(undefined4 *)(this + 0x7517c) = 0;
      *(undefined4 *)(this + 0x75180) = 0;
    }
    else {
      *(cRGame **)(*(int *)(this + 0x35c) + 8) = this + 0x75174;
      *(int *)(*(int *)(*(int *)(this + 0x35c) + 8) + 0xc) = *(int *)(this + 0x35c);
      iVar13 = *(int *)(*(int *)(this + 0x35c) + 8);
      *(int *)(this + 0x35c) = iVar13;
      *(undefined4 *)(iVar13 + 8) = 0;
    }
    *(uint *)(this + 0x75178) = *(uint *)(this + 0x75178) | 0x200;
  }
  else {
    RShellError("List ADD");
  }
  uVar7 = *(uint *)(this + 0x751a4);
  if ((uVar7 & 0x200) == 0) {
    iVar13 = *(int *)(this + 0x75128);
    *(cRGame **)(this + 0x751a8) = pcVar12;
    *(int *)(this + 0x751ac) = iVar13;
    if (iVar13 != 0) {
      *(cRGame **)(iVar13 + 8) = this + 0x751a0;
    }
    *(cRGame **)(this + 0x75128) = this + 0x751a0;
    *(uint *)(this + 0x751a4) = uVar7 | 0x200;
  }
  else {
    RShellError("List ADDafter");
  }
  uVar7 = *(uint *)(this + 0x751fc);
  if ((uVar7 & 0x200) == 0) {
    *(cRGame **)(this + 0x75200) = pcVar12;
    iVar13 = *(int *)(this + 0x75128);
    *(cRGame **)(this + 0x75128) = this + 0x751f8;
    *(int *)(this + 0x75204) = iVar13;
    if (iVar13 != 0) {
      *(cRGame **)(iVar13 + 8) = this + 0x751f8;
    }
    *(uint *)(this + 0x751fc) = uVar7 | 0x200;
  }
  else {
    RShellError("List ADDafter");
  }
  uVar7 = *(uint *)(this + 0x752d8);
  if ((uVar7 & 0x200) == 0) {
    iVar13 = *(int *)(this + 0x75128);
    *(cRGame **)(this + 0x752dc) = pcVar12;
    *(int *)(this + 0x752e0) = iVar13;
    if (iVar13 != 0) {
      *(cRGame **)(iVar13 + 8) = this + 0x752d4;
    }
    *(cRGame **)(this + 0x75128) = this + 0x752d4;
    *(uint *)(this + 0x752d8) = uVar7 | 0x200;
  }
  else {
    RShellError("List ADDafter");
  }
  uVar7 = *(uint *)(this + 0x750f4);
  if ((uVar7 & 0x200) == 0) {
    iVar13 = *(int *)(this + 0x75128);
    *(cRGame **)(this + 0x750f8) = pcVar12;
    *(int *)(this + 0x750fc) = iVar13;
    if (iVar13 != 0) {
      *(cRGame **)(iVar13 + 8) = this + 0x750f0;
    }
    *(cRGame **)(this + 0x75128) = this + 0x750f0;
    *(uint *)(this + 0x750f4) = uVar7 | 0x200;
  }
  else {
    RShellError("List ADDafter");
  }
  uVar7 = *(uint *)(this + 0x75280);
  if ((uVar7 & 0x200) == 0) {
    *(cRGame **)(this + 0x75284) = pcVar12;
    iVar13 = *(int *)(this + 0x75128);
    *(cRGame **)(this + 0x75128) = this + 0x7527c;
    *(int *)(this + 0x75288) = iVar13;
    if (iVar13 != 0) {
      *(cRGame **)(iVar13 + 8) = this + 0x7527c;
    }
    *(uint *)(this + 0x75280) = uVar7 | 0x200;
  }
  else {
    RShellError("List ADDafter");
  }
  uVar7 = *(uint *)(this + 0x752ac);
  if ((uVar7 & 0x200) == 0) {
    iVar13 = *(int *)(this + 0x75128);
    *(cRGame **)(this + 0x752b0) = pcVar12;
    *(int *)(this + 0x752b4) = iVar13;
    if (iVar13 != 0) {
      *(cRGame **)(iVar13 + 8) = this + 0x752a8;
    }
    *(cRGame **)(this + 0x75128) = this + 0x752a8;
    *(uint *)(this + 0x752ac) = uVar7 | 0x200;
  }
  else {
    RShellError("List ADDafter");
  }
  uVar7 = *(uint *)(this + 0x75228);
  if ((uVar7 & 0x200) == 0) {
    iVar13 = *(int *)(this + 0x75128);
    *(cRGame **)(this + 0x7522c) = pcVar12;
    *(int *)(this + 0x75230) = iVar13;
    if (iVar13 != 0) {
      *(cRGame **)(iVar13 + 8) = this + 0x75224;
    }
    *(cRGame **)(this + 0x75128) = this + 0x75224;
    *(uint *)(this + 0x75228) = uVar7 | 0x200;
  }
  else {
    RShellError("List ADDafter");
  }
  uVar7 = *(uint *)(this + 0x75254);
  if ((uVar7 & 0x200) == 0) {
    *(cRGame **)(this + 0x75258) = pcVar12;
    iVar13 = *(int *)(this + 0x75128);
    *(cRGame **)(this + 0x75128) = this + 0x75250;
    *(int *)(this + 0x7525c) = iVar13;
    if (iVar13 != 0) {
      *(cRGame **)(iVar13 + 8) = this + 0x75250;
    }
    *(uint *)(this + 0x75254) = uVar7 | 0x200;
  }
  else {
    RShellError("List ADDafter");
  }
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)PTR__gObjectList_001b61cc);
  cRBod::SetObject((cRBod *)(this + 0x848f8),pcVar4);
  pcVar5 = (char *)Rstrfind("Test:",*(char **)(this + 0x47ad0));
  if (pcVar5 == (char *)0x0) {
    Rstrcpy(local_e8,"turbo-base-000.x");
  }
  else {
    iVar13 = Rstrfind(":",pcVar5);
    cVar10 = *(char *)(iVar13 + 1);
    if (cVar10 == '.') {
      pcVar8 = local_e8;
      pcVar5 = local_e8 + 1;
    }
    else {
      pcVar5 = local_e8 + 1;
      do {
        pcVar8 = pcVar5;
        pcVar8[-1] = cVar10;
        cVar10 = *(char *)(iVar13 + 2);
        iVar13 = iVar13 + 1;
        pcVar5 = pcVar8 + 1;
      } while (cVar10 != '.');
    }
    *pcVar8 = '.';
    *pcVar5 = 'x';
    pcVar8[2] = '\0';
  }
  cRDirectX::LoadAnim(this_00,local_e8,*(cRObject **)(this + 0x8491c));
  puVar2 = PTR__gObjectList_001b61cc;
  iVar13 = 0;
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)PTR__gObjectList_001b61cc);
  cRBod::SetObject((cRBod *)(this + 0x847b8),pcVar4);
  cRDirectX::LoadAnim(this_00,local_e8,*(cRObject **)(this + 0x847dc));
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x8496c),pcVar4);
  cRDirectX::LoadAnim(this_00,"turbo-move-000.x",*(cRObject **)(this + 0x84990));
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x849e0),pcVar4);
  cRDirectX::LoadAnim(this_00,"turbo-bobalong-000.x",*(cRObject **)(this + 0x84a04));
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x84a54),pcVar4);
  cRDirectX::LoadAnim(this_00,"turbo-lookbackleft-000.x",*(cRObject **)(this + 0x84a78));
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x84ac8),pcVar4);
  cRDirectX::LoadAnim(this_00,"turbo-lookbackright-000.x",*(cRObject **)(this + 0x84aec));
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x84b3c),pcVar4);
  cRDirectX::LoadAnim(this_00,"turbo-fall-000.x",*(cRObject **)(this + 0x84b60));
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x84bb0),pcVar4);
  cRDirectX::LoadAnim(this_00,"turbo-damaged-000.x",*(cRObject **)(this + 0x84bd4));
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x84c24),pcVar4);
  cRDirectX::LoadAnim(this_00,"turbo-intoshell-000.x",*(cRObject **)(this + 0x84c48));
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x84c98),pcVar4);
  cRDirectX::LoadAnim(this_00,"turbo-skidstop-000.x",*(cRObject **)(this + 0x84cbc));
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x84d0c),pcVar4);
  cRDirectX::LoadAnim(this_00,"turbo-talk-000.x",*(cRObject **)(this + 0x84d30));
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x85c54),pcVar4);
  cRDirectX::Load(this_00,"TurboHotSpots.x",*(cRObject **)(this + 0x85c78),2);
  **(uint **)(this + 0x85c78) = **(uint **)(this + 0x85c78) | 0x8000000;
  cRSnail::ExtractHotSpots((cRSnail *)(this + 0x847b8));
  **(uint **)(this + 0x8491c) = **(uint **)(this + 0x8491c) | 4;
  cRObject::ApplyToon(*(cRObject **)(this + 0x8491c),0);
  *(undefined4 *)(*(int *)(this + 0x8491c) + 0xf0) = 0;
  *(undefined4 *)(*(int *)(this + 0x8491c) + 0xf4) = 0;
  *(undefined4 *)(*(int *)(this + 0x8491c) + 0xf8) = 0;
  **(uint **)(this + 0x84990) = **(uint **)(this + 0x84990) | 4;
  cRObject::ApplyToon(*(cRObject **)(this + 0x84990),0);
  *(undefined4 *)(*(int *)(this + 0x84990) + 0xf0) = 0;
  *(undefined4 *)(*(int *)(this + 0x84990) + 0xf4) = 0;
  *(undefined4 *)(*(int *)(this + 0x84990) + 0xf8) = 0;
  **(uint **)(this + 0x84a04) = **(uint **)(this + 0x84a04) | 4;
  cRObject::ApplyToon(*(cRObject **)(this + 0x84a04),0);
  *(undefined4 *)(*(int *)(this + 0x84a04) + 0xf0) = 0;
  *(undefined4 *)(*(int *)(this + 0x84a04) + 0xf4) = 0;
  *(undefined4 *)(*(int *)(this + 0x84a04) + 0xf8) = 0;
  **(uint **)(this + 0x84a78) = **(uint **)(this + 0x84a78) | 4;
  cRObject::ApplyToon(*(cRObject **)(this + 0x84a78),0);
  *(undefined4 *)(*(int *)(this + 0x84a78) + 0xf0) = 0;
  *(undefined4 *)(*(int *)(this + 0x84a78) + 0xf4) = 0;
  *(undefined4 *)(*(int *)(this + 0x84a78) + 0xf8) = 0;
  **(uint **)(this + 0x84aec) = **(uint **)(this + 0x84aec) | 4;
  cRObject::ApplyToon(*(cRObject **)(this + 0x84aec),0);
  *(undefined4 *)(*(int *)(this + 0x84aec) + 0xf0) = 0;
  *(undefined4 *)(*(int *)(this + 0x84aec) + 0xf4) = 0;
  *(undefined4 *)(*(int *)(this + 0x84aec) + 0xf8) = 0;
  **(uint **)(this + 0x84b60) = **(uint **)(this + 0x84b60) | 4;
  cRObject::ApplyToon(*(cRObject **)(this + 0x84b60),0);
  *(undefined4 *)(*(int *)(this + 0x84b60) + 0xf0) = 0;
  *(undefined4 *)(*(int *)(this + 0x84b60) + 0xf4) = 0;
  *(undefined4 *)(*(int *)(this + 0x84b60) + 0xf8) = 0;
  **(uint **)(this + 0x84bd4) = **(uint **)(this + 0x84bd4) | 4;
  cRObject::ApplyToon(*(cRObject **)(this + 0x84bd4),0);
  *(undefined4 *)(*(int *)(this + 0x84bd4) + 0xf0) = 0;
  *(undefined4 *)(*(int *)(this + 0x84bd4) + 0xf4) = 0;
  *(undefined4 *)(*(int *)(this + 0x84bd4) + 0xf8) = 0;
  **(uint **)(this + 0x84c48) = **(uint **)(this + 0x84c48) | 4;
  cRObject::ApplyToon(*(cRObject **)(this + 0x84c48),0);
  *(undefined4 *)(*(int *)(this + 0x84c48) + 0xf0) = 0;
  *(undefined4 *)(*(int *)(this + 0x84c48) + 0xf4) = 0;
  *(undefined4 *)(*(int *)(this + 0x84c48) + 0xf8) = 0;
  **(uint **)(this + 0x84cbc) = **(uint **)(this + 0x84cbc) | 4;
  cRObject::ApplyToon(*(cRObject **)(this + 0x84cbc),0);
  *(undefined4 *)(*(int *)(this + 0x84cbc) + 0xf0) = 0;
  *(undefined4 *)(*(int *)(this + 0x84cbc) + 0xf4) = 0;
  *(undefined4 *)(*(int *)(this + 0x84cbc) + 0xf8) = 0;
  **(uint **)(this + 0x84d30) = **(uint **)(this + 0x84d30) | 4;
  cRObject::ApplyToon(*(cRObject **)(this + 0x84d30),0);
  *(undefined4 *)(*(int *)(this + 0x84d30) + 0xf0) = 0;
  *(undefined4 *)(*(int *)(this + 0x84d30) + 0xf4) = 0;
  *(undefined4 *)(*(int *)(this + 0x84d30) + 0xf8) = 0;
  **(uint **)(this + 0x847dc) = **(uint **)(this + 0x847dc) | 4;
  cRObject::ApplyToon(*(cRObject **)(this + 0x847dc),0);
  *(undefined4 *)(*(int *)(this + 0x847dc) + 0xf0) = 0;
  *(undefined4 *)(*(int *)(this + 0x847dc) + 0xf4) = 0;
  *(undefined4 *)(*(int *)(this + 0x847dc) + 0xf8) = 0;
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x8583c),pcVar4);
  cRDirectX::LoadAnim(this_00,"jetpack-base-000.x",*(cRObject **)(this + 0x85860));
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x85980),pcVar4);
  cRDirectX::LoadAnim(this_00,"jetpack-base-000.x",*(cRObject **)(this + 0x859a4));
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x859f4),pcVar4);
  cRDirectX::LoadAnim(this_00,"jetpack-draw-000.x",*(cRObject **)(this + 0x85a18));
  **(uint **)(this + 0x859a4) = **(uint **)(this + 0x859a4) | 4;
  cRObject::ApplyToon(*(cRObject **)(this + 0x859a4),0);
  *(undefined4 *)(*(int *)(this + 0x859a4) + 0xf0) = 0;
  *(undefined4 *)(*(int *)(this + 0x859a4) + 0xf4) = 0;
  *(undefined4 *)(*(int *)(this + 0x859a4) + 0xf8) = 0;
  **(uint **)(this + 0x85a18) = **(uint **)(this + 0x85a18) | 4;
  cRObject::ApplyToon(*(cRObject **)(this + 0x85a18),0);
  *(undefined4 *)(*(int *)(this + 0x85a18) + 0xf0) = 0;
  *(undefined4 *)(*(int *)(this + 0x85a18) + 0xf4) = 0;
  *(undefined4 *)(*(int *)(this + 0x85a18) + 0xf8) = 0;
  **(uint **)(this + 0x85860) = **(uint **)(this + 0x85860) | 4;
  cRObject::ApplyToon(*(cRObject **)(this + 0x85860),0);
  *(undefined4 *)(*(int *)(this + 0x85860) + 0xf0) = 0;
  *(undefined4 *)(*(int *)(this + 0x85860) + 0xf4) = 0;
  *(undefined4 *)(*(int *)(this + 0x85860) + 0xf8) = 0;
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x84d80),pcVar4);
  cRDirectX::LoadAnim(this_00,"blasterleft-base-000.x",*(cRObject **)(this + 0x84da4));
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x84ec4),pcVar4);
  cRDirectX::LoadAnim(this_00,"blasterleft-base-000.x",*(cRObject **)(this + 0x84ee8));
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x84f38),pcVar4);
  cRDirectX::LoadAnim(this_00,"blasterleft-draw-000.x",*(cRObject **)(this + 0x84f5c));
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x84fac),pcVar4);
  cRDirectX::LoadAnim(this_00,"blasterleft-fire-000.x",*(cRObject **)(this + 0x84fd0));
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x85020),pcVar4);
  cRDirectX::LoadAnim(this_00,"Laserleft-base-000.x",*(cRObject **)(this + 0x85044));
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x85094),pcVar4);
  cRDirectX::LoadAnim(this_00,"Laserleft-draw-000.x",*(cRObject **)(this + 0x850b8));
  **(uint **)(this + 0x84ee8) = **(uint **)(this + 0x84ee8) | 4;
  cRObject::ApplyToon(*(cRObject **)(this + 0x84ee8),0);
  *(undefined4 *)(*(int *)(this + 0x84ee8) + 0xf0) = 0;
  *(undefined4 *)(*(int *)(this + 0x84ee8) + 0xf4) = 0;
  *(undefined4 *)(*(int *)(this + 0x84ee8) + 0xf8) = 0;
  **(uint **)(this + 0x84f5c) = **(uint **)(this + 0x84f5c) | 4;
  cRObject::ApplyToon(*(cRObject **)(this + 0x84f5c),0);
  *(undefined4 *)(*(int *)(this + 0x84f5c) + 0xf0) = 0;
  *(undefined4 *)(*(int *)(this + 0x84f5c) + 0xf4) = 0;
  *(undefined4 *)(*(int *)(this + 0x84f5c) + 0xf8) = 0;
  **(uint **)(this + 0x84fd0) = **(uint **)(this + 0x84fd0) | 4;
  cRObject::ApplyToon(*(cRObject **)(this + 0x84fd0),0);
  *(undefined4 *)(*(int *)(this + 0x84fd0) + 0xf0) = 0;
  *(undefined4 *)(*(int *)(this + 0x84fd0) + 0xf4) = 0;
  *(undefined4 *)(*(int *)(this + 0x84fd0) + 0xf8) = 0;
  **(uint **)(this + 0x85044) = **(uint **)(this + 0x85044) | 4;
  cRObject::ApplyToon(*(cRObject **)(this + 0x85044),0);
  *(undefined4 *)(*(int *)(this + 0x85044) + 0xf0) = 0;
  *(undefined4 *)(*(int *)(this + 0x85044) + 0xf4) = 0;
  *(undefined4 *)(*(int *)(this + 0x85044) + 0xf8) = 0;
  **(uint **)(this + 0x850b8) = **(uint **)(this + 0x850b8) | 4;
  cRObject::ApplyToon(*(cRObject **)(this + 0x850b8),0);
  *(undefined4 *)(*(int *)(this + 0x850b8) + 0xf0) = 0;
  *(undefined4 *)(*(int *)(this + 0x850b8) + 0xf4) = 0;
  *(undefined4 *)(*(int *)(this + 0x850b8) + 0xf8) = 0;
  **(uint **)(this + 0x84da4) = **(uint **)(this + 0x84da4) | 4;
  cRObject::ApplyToon(*(cRObject **)(this + 0x84da4),0);
  *(undefined4 *)(*(int *)(this + 0x84da4) + 0xf0) = 0;
  *(undefined4 *)(*(int *)(this + 0x84da4) + 0xf4) = 0;
  *(undefined4 *)(*(int *)(this + 0x84da4) + 0xf8) = 0;
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x85114),pcVar4);
  cRDirectX::LoadAnim(this_00,"blasterRight-base-000.x",*(cRObject **)(this + 0x85138));
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x85258),pcVar4);
  cRDirectX::LoadAnim(this_00,"blasterRight-base-000.x",*(cRObject **)(this + 0x8527c));
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x852cc),pcVar4);
  cRDirectX::LoadAnim(this_00,"blasterRight-draw-000.x",*(cRObject **)(this + 0x852f0));
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x85340),pcVar4);
  cRDirectX::LoadAnim(this_00,"blasterRight-fire-000.x",*(cRObject **)(this + 0x85364));
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x853b4),pcVar4);
  cRDirectX::LoadAnim(this_00,"Laserright-base-000.x",*(cRObject **)(this + 0x853d8));
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x85428),pcVar4);
  cRDirectX::LoadAnim(this_00,"Laserright-draw-000.x",*(cRObject **)(this + 0x8544c));
  **(uint **)(this + 0x8527c) = **(uint **)(this + 0x8527c) | 4;
  cRObject::ApplyToon(*(cRObject **)(this + 0x8527c),0);
  *(undefined4 *)(*(int *)(this + 0x8527c) + 0xf0) = 0;
  *(undefined4 *)(*(int *)(this + 0x8527c) + 0xf4) = 0;
  *(undefined4 *)(*(int *)(this + 0x8527c) + 0xf8) = 0;
  **(uint **)(this + 0x852f0) = **(uint **)(this + 0x852f0) | 4;
  cRObject::ApplyToon(*(cRObject **)(this + 0x852f0),0);
  *(undefined4 *)(*(int *)(this + 0x852f0) + 0xf0) = 0;
  *(undefined4 *)(*(int *)(this + 0x852f0) + 0xf4) = 0;
  *(undefined4 *)(*(int *)(this + 0x852f0) + 0xf8) = 0;
  **(uint **)(this + 0x85364) = **(uint **)(this + 0x85364) | 4;
  cRObject::ApplyToon(*(cRObject **)(this + 0x85364),0);
  *(undefined4 *)(*(int *)(this + 0x85364) + 0xf0) = 0;
  *(undefined4 *)(*(int *)(this + 0x85364) + 0xf4) = 0;
  *(undefined4 *)(*(int *)(this + 0x85364) + 0xf8) = 0;
  **(uint **)(this + 0x853d8) = **(uint **)(this + 0x853d8) | 4;
  cRObject::ApplyToon(*(cRObject **)(this + 0x853d8),0);
  *(undefined4 *)(*(int *)(this + 0x853d8) + 0xf0) = 0;
  *(undefined4 *)(*(int *)(this + 0x853d8) + 0xf4) = 0;
  *(undefined4 *)(*(int *)(this + 0x853d8) + 0xf8) = 0;
  **(uint **)(this + 0x8544c) = **(uint **)(this + 0x8544c) | 4;
  cRObject::ApplyToon(*(cRObject **)(this + 0x8544c),0);
  *(undefined4 *)(*(int *)(this + 0x8544c) + 0xf0) = 0;
  *(undefined4 *)(*(int *)(this + 0x8544c) + 0xf4) = 0;
  *(undefined4 *)(*(int *)(this + 0x8544c) + 0xf8) = 0;
  **(uint **)(this + 0x85138) = **(uint **)(this + 0x85138) | 4;
  cRObject::ApplyToon(*(cRObject **)(this + 0x85138),0);
  *(undefined4 *)(*(int *)(this + 0x85138) + 0xf0) = 0;
  *(undefined4 *)(*(int *)(this + 0x85138) + 0xf4) = 0;
  *(undefined4 *)(*(int *)(this + 0x85138) + 0xf8) = 0;
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x854a8),pcVar4);
  cRDirectX::LoadAnim(this_00,"blasterTop-base-000.x",*(cRObject **)(this + 0x854cc));
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x855ec),pcVar4);
  cRDirectX::LoadAnim(this_00,"blasterTop-base-000.x",*(cRObject **)(this + 0x85610));
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x85660),pcVar4);
  cRDirectX::LoadAnim(this_00,"blasterTop-draw-000.x",*(cRObject **)(this + 0x85684));
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x856d4),pcVar4);
  cRDirectX::LoadAnim(this_00,"blasterTop-fire-000.x",*(cRObject **)(this + 0x856f8));
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x85748),pcVar4);
  cRDirectX::LoadAnim(this_00,"rocketlauncher-base-000.x",*(cRObject **)(this + 0x8576c));
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x857bc),pcVar4);
  cRDirectX::LoadAnim(this_00,"rocketlauncher-draw-000.x",*(cRObject **)(this + 0x857e0));
  **(uint **)(this + 0x85610) = **(uint **)(this + 0x85610) | 4;
  cRObject::ApplyToon(*(cRObject **)(this + 0x85610),0);
  *(undefined4 *)(*(int *)(this + 0x85610) + 0xf0) = 0;
  *(undefined4 *)(*(int *)(this + 0x85610) + 0xf4) = 0;
  *(undefined4 *)(*(int *)(this + 0x85610) + 0xf8) = 0;
  **(uint **)(this + 0x85684) = **(uint **)(this + 0x85684) | 4;
  cRObject::ApplyToon(*(cRObject **)(this + 0x85684),0);
  *(undefined4 *)(*(int *)(this + 0x85684) + 0xf0) = 0;
  *(undefined4 *)(*(int *)(this + 0x85684) + 0xf4) = 0;
  *(undefined4 *)(*(int *)(this + 0x85684) + 0xf8) = 0;
  **(uint **)(this + 0x856f8) = **(uint **)(this + 0x856f8) | 4;
  cRObject::ApplyToon(*(cRObject **)(this + 0x856f8),0);
  *(undefined4 *)(*(int *)(this + 0x856f8) + 0xf0) = 0;
  *(undefined4 *)(*(int *)(this + 0x856f8) + 0xf4) = 0;
  *(undefined4 *)(*(int *)(this + 0x856f8) + 0xf8) = 0;
  **(uint **)(this + 0x8576c) = **(uint **)(this + 0x8576c) | 4;
  cRObject::ApplyToon(*(cRObject **)(this + 0x8576c),0);
  *(undefined4 *)(*(int *)(this + 0x8576c) + 0xf0) = 0;
  *(undefined4 *)(*(int *)(this + 0x8576c) + 0xf4) = 0;
  *(undefined4 *)(*(int *)(this + 0x8576c) + 0xf8) = 0;
  **(uint **)(this + 0x857e0) = **(uint **)(this + 0x857e0) | 4;
  cRObject::ApplyToon(*(cRObject **)(this + 0x857e0),0);
  *(undefined4 *)(*(int *)(this + 0x857e0) + 0xf0) = 0;
  *(undefined4 *)(*(int *)(this + 0x857e0) + 0xf4) = 0;
  *(undefined4 *)(*(int *)(this + 0x857e0) + 0xf8) = 0;
  **(uint **)(this + 0x854cc) = **(uint **)(this + 0x854cc) | 4;
  cRObject::ApplyToon(*(cRObject **)(this + 0x854cc),0);
  *(undefined4 *)(*(int *)(this + 0x854cc) + 0xf0) = 0;
  puVar3 = PTR__gTextureList_001b61d0;
  *(undefined4 *)(*(int *)(this + 0x854cc) + 0xf4) = 0;
  *(undefined4 *)(*(int *)(this + 0x854cc) + 0xf8) = 0;
  uVar6 = cRTextures::Add((cRTextures *)puVar3,"x/snail-turbo.tga",(cTgaHeader *)0x0,0);
  *(undefined4 *)(this + 0x85f2c) = uVar6;
  uVar6 = cRTextures::Add((cRTextures *)puVar3,"x/snail-turbo-damage.tga",(cTgaHeader *)0x0,0);
  *(undefined4 *)(this + 0x85f30) = uVar6;
  uVar6 = cRTextures::Add((cRTextures *)puVar3,"x/snail-turbo-invincible.tga",(cTgaHeader *)0x0,0);
  *(undefined4 *)(this + 0x85f34) = uVar6;
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x85e90),pcVar4);
  cRDirectX::Load(this_00,"invincible-base-000.x",*(cRObject **)(this + 0x85eb4),1);
  **(uint **)(this + 0x85eb4) = **(uint **)(this + 0x85eb4) | 0x100000;
  *(undefined4 *)(*(int *)(this + 0x85eb4) + 8) = 1;
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x82504),pcVar4);
  cRDirectX::Load(this_00,"rocket-base-000.x",*(cRObject **)(this + 0x82528),1);
  pcVar12 = this + 0x8249c;
  do {
    pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
    iVar15 = iVar13 * 0x2c8;
    iVar13 = iVar13 + 1;
    iVar16 = iVar15 + 0x82478;
    cRBod::SetObject((cRBod *)(this + iVar16),pcVar4);
    **(uint **)pcVar12 = **(uint **)pcVar12 | 0x100004;
    *(undefined4 *)(*(int *)pcVar12 + 8) = 1;
    ObjectTextLoad("Objects/VapourLazer",*(cRObject **)pcVar12);
    cRVapour::Init((cRVapour *)(this + iVar16),*(cRObject **)pcVar12,0.16);
    cRBod::SetObject((cRBod *)(this + iVar15 + 0x82504),*(cRObject **)(this + 0x82528));
    puVar3 = PTR__gTextureList_001b61d0;
    pcVar12 = pcVar12 + 0x2c8;
  } while (iVar13 != 0xc);
  puVar9 = (uint *)cRTextures::Add((cRTextures *)PTR__gTextureList_001b61d0,
                                   "Objects/VapourLazer/Lazer.tga",(cTgaHeader *)0x0,0);
  *puVar9 = *puVar9 | 0x400;
  puVar9 = (uint *)cRTextures::Add((cRTextures *)puVar3,"Objects/World00/Worm.tga",(cTgaHeader *)0x0
                                   ,0);
  *puVar9 = *puVar9 | 0x1403;
  puVar9 = (uint *)cRTextures::Add((cRTextures *)puVar3,"Objects/World00/Surface0.tga",
                                   (cTgaHeader *)0x0,0);
  *puVar9 = *puVar9 | 0x1400;
  puVar9 = (uint *)cRTextures::Add((cRTextures *)puVar3,"Objects/Universe/Ramp.tga",
                                   (cTgaHeader *)0x0,0);
  *puVar9 = *puVar9 | 0x1000;
  *(undefined4 *)(this + 0xbcc) = 0xffffffff;
  puVar9 = (uint *)cRTextures::Add((cRTextures *)puVar3,"Objects/World00/Surface0.tga",
                                   (cTgaHeader *)0x0,0);
  *(uint **)(this + 0x848) = puVar9;
  *puVar9 = *puVar9 | 0x1000;
  *(undefined4 *)(this + 0x84c) = 0x656a624f;
  *(undefined4 *)(this + 0x850) = 0x2f737463;
  *(undefined4 *)(this + 0x854) = 0x6c726f57;
  *(undefined4 *)(this + 0x858) = 0x2f303064;
  *(undefined4 *)(this + 0x85c) = 0x66727553;
  *(undefined4 *)(this + 0x860) = 0x30656361;
  *(undefined4 *)(this + 0x864) = 0x6167742e;
  this[0x868] = (cRGame)0x0;
  *(undefined4 *)(this + 0x8cc) = 0x656a624f;
  *(undefined4 *)(this + 0x8d0) = 0x2f737463;
  *(undefined4 *)(this + 0x8d4) = 0x6c726f57;
  *(undefined4 *)(this + 0x8d8) = 0x2f303064;
  *(undefined4 *)(this + 0x8dc) = 0x66727553;
  *(undefined4 *)(this + 0x8e0) = 0x31656361;
  *(undefined4 *)(this + 0x8e4) = 0x6167742e;
  this[0x8e8] = (cRGame)0x0;
  *(undefined4 *)(this + 0x94c) = 0x656a624f;
  *(undefined4 *)(this + 0x950) = 0x2f737463;
  *(undefined4 *)(this + 0x954) = 0x6c726f57;
  *(undefined4 *)(this + 0x958) = 0x2f303064;
  *(undefined4 *)(this + 0x95c) = 0x66727553;
  *(undefined4 *)(this + 0x960) = 0x32656361;
  *(undefined4 *)(this + 0x964) = 0x6167742e;
  this[0x968] = (cRGame)0x0;
  *(undefined4 *)(this + 0x9cc) = 0x656a624f;
  *(undefined4 *)(this + 0x9d0) = 0x2f737463;
  *(undefined4 *)(this + 0x9d4) = 0x6c726f57;
  *(undefined4 *)(this + 0x9d8) = 0x2f303064;
  *(undefined4 *)(this + 0x9dc) = 0x66727553;
  *(undefined4 *)(this + 0x9e0) = 0x33656361;
  *(undefined4 *)(this + 0x9e4) = 0x6167742e;
  this[0x9e8] = (cRGame)0x0;
  *(undefined4 *)(this + 0xa4c) = 0x656a624f;
  *(undefined4 *)(this + 0xa50) = 0x2f737463;
  *(undefined4 *)(this + 0xa54) = 0x6c726f57;
  *(undefined4 *)(this + 0xa58) = 0x2f303064;
  *(undefined4 *)(this + 0xa5c) = 0x66727553;
  *(undefined4 *)(this + 0xa60) = 0x34656361;
  *(undefined4 *)(this + 0xa64) = 0x6167742e;
  this[0xa68] = (cRGame)0x0;
  *(undefined4 *)(this + 0xacc) = 0x656a624f;
  *(undefined4 *)(this + 0xad0) = 0x2f737463;
  *(undefined4 *)(this + 0xad4) = 0x6c726f57;
  *(undefined4 *)(this + 0xad8) = 0x2f303064;
  *(undefined4 *)(this + 0xadc) = 0x66727553;
  *(undefined4 *)(this + 0xae0) = 0x35656361;
  *(undefined4 *)(this + 0xae4) = 0x6167742e;
  this[0xae8] = (cRGame)0x0;
  *(undefined4 *)(this + 0xb4c) = 0x656a624f;
  *(undefined4 *)(this + 0xb50) = 0x2f737463;
  *(undefined4 *)(this + 0xb54) = 0x6c726f57;
  *(undefined4 *)(this + 0xb58) = 0x2f303064;
  *(undefined4 *)(this + 0xb5c) = 0x66727553;
  *(undefined4 *)(this + 0xb60) = 0x36656361;
  *(undefined4 *)(this + 0xb64) = 0x6167742e;
  this[0xb68] = (cRGame)0x0;
  pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
  cRBod::SetObject((cRBod *)(this + 0x3593a8),pcVar4);
  ObjectTextLoad("Objects/Barrier",*(cRObject **)(this + 0x3593cc));
  *(undefined4 *)(this + 0x3593c0) = 0;
  *(undefined4 *)(this + 0x3593bc) = 0;
  *(undefined4 *)(this + 0x3593b8) = 0;
  tColourSmall::Set((tColourSmall *)(this + 0x3593d0),1.0,1.0,1.0,0.8);
  *(undefined4 *)(*(int *)(this + 0x3593cc) + 8) = 3;
  cRWorld::Init((cRWorld *)(this + 0x81ef0),0xdac,0x38,8);
  local_f4 = 0;
  local_ec = 0x3a;
  do {
    iVar16 = 0;
    iVar13 = local_ec;
    do {
      iVar14 = -1;
      pcVar12 = this + iVar13 * 0x2c + 0x43e24;
      iVar15 = iVar13;
      do {
        pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)PTR__gObjectList_001b61cc);
        iVar1 = iVar15 * 0x2c;
        cRBod::SetObject((cRBod *)(this + iVar1 + 0x43e24),pcVar4);
        ObjectProcFringe(*(cRObject **)(pcVar12 + 0x24),local_f4,iVar16,iVar14,-1,
                         "Objects/Universe/Fringe.tga");
        puVar2 = PTR__gObjectList_001b61cc;
        *(undefined4 *)(*(int *)(pcVar12 + 0x24) + 8) = 5;
        pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
        iVar11 = iVar15 + 1;
        iVar15 = iVar15 + 3;
        cRBod::SetObject((cRBod *)(this + iVar11 * 0x2c + 0x43e24),pcVar4);
        ObjectProcFringe(*(cRObject **)(pcVar12 + 0x50),local_f4,iVar16,iVar14,0,
                         "Objects/Universe/Fringe.tga");
        puVar2 = PTR__gObjectList_001b61cc;
        *(undefined4 *)(*(int *)(pcVar12 + 0x50) + 8) = 5;
        pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)puVar2);
        cRBod::SetObject((cRBod *)(this + iVar1 + 0x43e7c),pcVar4);
        ObjectProcFringe(*(cRObject **)(pcVar12 + 0x7c),local_f4,iVar16,iVar14,1,
                         "Objects/Universe/Fringe.tga");
        pcVar17 = pcVar12 + 0x7c;
        iVar14 = iVar14 + 1;
        pcVar12 = pcVar12 + 0x84;
        *(undefined4 *)(*(int *)pcVar17 + 8) = 5;
      } while (iVar14 != 2);
      iVar16 = iVar16 + 1;
      iVar13 = iVar13 + 9;
    } while (iVar16 != 4);
    local_f4 = local_f4 + 1;
    local_ec = local_ec + 0x24;
  } while (local_f4 != 8);
  puVar9 = (uint *)cRTextures::Add((cRTextures *)PTR__gTextureList_001b61d0,
                                   "Objects/Universe/Fringe.tga",(cTgaHeader *)0x0,0);
  *puVar9 = *puVar9 | 0x400;
  uVar7 = *(uint *)(this + 0x6c);
  if ((uVar7 & 0x200) == 0) {
    if (*(int *)(this + 0x35c) == 0) {
      *(cRGame **)(this + 0x35c) = this + 0x68;
      *(undefined4 *)(this + 0x70) = 0;
      *(undefined4 *)(this + 0x74) = 0;
    }
    else {
      *(cRGame **)(*(int *)(this + 0x35c) + 8) = this + 0x68;
      *(int *)(*(int *)(*(int *)(this + 0x35c) + 8) + 0xc) = *(int *)(this + 0x35c);
      iVar13 = *(int *)(*(int *)(this + 0x35c) + 8);
      *(int *)(this + 0x35c) = iVar13;
      *(undefined4 *)(iVar13 + 8) = 0;
    }
    *(uint *)(this + 0x6c) = uVar7 | 0x200;
  }
  else {
    RShellError("List ADD");
  }
  *(undefined4 *)(this + 0x94) = 0;
  *(undefined4 *)(this + 0xd0) = 0;
  *(undefined4 *)(this + 0x98) = 0;
  *(undefined4 *)(this + 0x9c) = 0;
  *(undefined4 *)(this + 0xa0) = 0;
  *(undefined4 *)(this + 0xa4) = 0xffffffff;
  *(undefined4 *)(this + 0xa8) = 0;
  *(undefined4 *)(this + 0xac) = 0;
  *(undefined4 *)(this + 0xbc) = 0x43a00000;
  *(undefined4 *)(this + 0xc0) = 0x43a00000;
  *(undefined4 *)(this + 0xc4) = 0;
  return;
}
