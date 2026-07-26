/*
 * mangled: _ZN6cRGame5Init3Ev
 * demangled: cRGame::Init3()
 * address: 0003f6d8
 * size: 8168
 */

/* cRGame::Init3() */

void __thiscall cRGame::Init3(cRGame *this)

{
  cRGame *pcVar1;
  cRObject *pcVar2;
  cRDirectX *this_00;
  cLinkedList<cRBod> *this_01;
  char *pcVar3;
  undefined4 uVar4;
  char cVar5;
  uint uVar6;
  uint *puVar7;
  int iVar8;
  cRGame *pcVar9;
  cRBod *pcVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  cRGame *pcVar14;
  int iVar15;
  uint in_fpscr;
  float fVar16;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  undefined8 uVar17;
  float extraout_s1;
  float extraout_s1_00;
  float extraout_s1_01;
  float extraout_s2;
  float extraout_s2_00;
  float extraout_s2_01;
  float extraout_s3;
  float extraout_s3_00;
  float extraout_s3_01;
  int local_138;
  int local_12c;
  int local_124;
  tMatrix atStack_fc [48];
  undefined4 local_cc;
  char local_bc [128];
  int local_3c;

  pcVar9 = this + 0x44370;
  iVar11 = 0;
  local_3c = __stack_chk_guard;
  wprintf("GameInit3\n");
  do {
    VectorSignedToFloat(iVar11,(byte)(in_fpscr >> 0x16) & 3);
    pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
    iVar13 = iVar11 * 0x2c;
    iVar11 = iVar11 + 1;
    fVar16 = (float)cRBod::SetObject((cRBod *)(this + iVar13 + 0x4434c),pcVar2);
    uVar17 = ObjectProcTileFloorFast(*(cRObject **)pcVar9,"Objects/World00/Surface0.png",fVar16);
    cRObject::ApplyUV(*(cRObject **)pcVar9,(float)uVar17,(float)((ulonglong)uVar17 >> 0x20));
    pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
    fVar16 = (float)cRBod::SetObject((cRBod *)(this + iVar13 + 0x444ac),pcVar2);
    uVar17 = ObjectProcTileFloorFast
                       (*(cRObject **)(pcVar9 + 0x160),"Objects/World00/Surface0.png",fVar16);
    cRObject::ApplyUV(*(cRObject **)(pcVar9 + 0x160),(float)uVar17,
                      (float)((ulonglong)uVar17 >> 0x20));
    pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
    fVar16 = (float)cRBod::SetObject((cRBod *)(this + iVar13 + 0x4460c),pcVar2);
    uVar17 = ObjectProcTileFloorFast
                       (*(cRObject **)(pcVar9 + 0x2c0),"Objects/World00/Surface0.png",fVar16);
    cRObject::ApplyUV(*(cRObject **)(pcVar9 + 0x2c0),(float)uVar17,
                      (float)((ulonglong)uVar17 >> 0x20));
    pcVar9 = pcVar9 + 0x2c;
  } while (iVar11 != 8);
  tMatrix::Identity(atStack_fc);
  pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
  cRBod::SetObject((cRBod *)(this + 0x441ec),pcVar2);
  pcVar2 = *(cRObject **)(this + 0x44210);
  this_00 = (cRDirectX *)(this + 0x47ad0);
  *(uint *)pcVar2 = *(uint *)pcVar2 | 0x1000;
  cRDirectX::Load(this_00,"pillar1.x",pcVar2,1);
  if ((**(uint **)(this + 0x44210) & 0x2000000) == 0) {
    local_cc = 0;
    cRBod::ApplyPos((tMatrix *)(this + 0x441ec));
  }
  pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
  cRBod::SetObject((cRBod *)(this + 0x44218),pcVar2);
  pcVar2 = *(cRObject **)(this + 0x4423c);
  *(uint *)pcVar2 = *(uint *)pcVar2 | 0x1000;
  cRDirectX::Load(this_00,"pillar2.x",pcVar2,1);
  if ((**(uint **)(this + 0x4423c) & 0x2000000) == 0) {
    local_cc = 0x3f000000;
    cRBod::ApplyPos((tMatrix *)(this + 0x44218));
  }
  pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
  cRBod::SetObject((cRBod *)(this + 0x44244),pcVar2);
  pcVar2 = *(cRObject **)(this + 0x44268);
  *(uint *)pcVar2 = *(uint *)pcVar2 | 0x1000;
  cRDirectX::Load(this_00,"pillar3.x",pcVar2,1);
  if ((**(uint **)(this + 0x44268) & 0x2000000) == 0) {
    local_cc = 0x3f800000;
    cRBod::ApplyPos((tMatrix *)(this + 0x44244));
  }
  pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
  cRBod::SetObject((cRBod *)(this + 0x44270),pcVar2);
  pcVar2 = *(cRObject **)(this + 0x44294);
  *(uint *)pcVar2 = *(uint *)pcVar2 | 0x1000;
  cRDirectX::Load(this_00,"pillar4.x",pcVar2,1);
  if ((**(uint **)(this + 0x44294) & 0x2000000) == 0) {
    local_cc = 0x3fc00000;
    cRBod::ApplyPos((tMatrix *)(this + 0x44270));
  }
  pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
  cRBod::SetObject((cRBod *)(this + 0x4429c),pcVar2);
  pcVar2 = *(cRObject **)(this + 0x442c0);
  *(uint *)pcVar2 = *(uint *)pcVar2 | 0x1000;
  cRDirectX::Load(this_00,"pillar5.x",pcVar2,1);
  if ((**(uint **)(this + 0x442c0) & 0x2000000) == 0) {
    local_cc = 0x40000000;
    cRBod::ApplyPos((tMatrix *)(this + 0x4429c));
  }
  pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
  cRBod::SetObject((cRBod *)(this + 0x442c8),pcVar2);
  pcVar2 = *(cRObject **)(this + 0x442ec);
  *(uint *)pcVar2 = *(uint *)pcVar2 | 0x1000;
  cRDirectX::Load(this_00,"pillar6.x",pcVar2,1);
  if ((**(uint **)(this + 0x442ec) & 0x2000000) == 0) {
    local_cc = 0x40200000;
    cRBod::ApplyPos((tMatrix *)(this + 0x442c8));
  }
  pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
  cRBod::SetObject((cRBod *)(this + 0x442f4),pcVar2);
  pcVar2 = *(cRObject **)(this + 0x44318);
  *(uint *)pcVar2 = *(uint *)pcVar2 | 0x1000;
  cRDirectX::Load(this_00,"pillar7.x",pcVar2,1);
  if ((**(uint **)(this + 0x44318) & 0x2000000) == 0) {
    local_cc = 0x40400000;
    cRBod::ApplyPos((tMatrix *)(this + 0x442f4));
  }
  pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
  cRBod::SetObject((cRBod *)(this + 0x44320),pcVar2);
  pcVar2 = *(cRObject **)(this + 0x44344);
  *(uint *)pcVar2 = *(uint *)pcVar2 | 0x1000;
  cRDirectX::Load(this_00,"pillar8.x",pcVar2,1);
  if ((**(uint **)(this + 0x44344) & 0x2000000) == 0) {
    local_cc = 0x40600000;
    cRBod::ApplyPos((tMatrix *)(this + 0x44320));
  }
  iVar11 = 0;
  pcVar9 = this + 0x44210;
  do {
    puVar7 = *(uint **)pcVar9;
    iVar11 = iVar11 + 1;
    puVar7[2] = 0;
    *puVar7 = *puVar7 & 0xffefffff;
    pcVar9 = pcVar9 + 0x2c;
  } while (iVar11 != 8);
  pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
  fVar16 = (float)cRBod::SetObject((cRBod *)(this + 0x4476c),pcVar2);
  ObjectProcTileFast(*(cRObject **)(this + 0x44790),"Objects/Universe/Ramp.tga",fVar16);
  ObjectProcTileFastRamp(-1,*(cRObject **)(this + 0x44790));
  pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
  fVar16 = (float)cRBod::SetObject((cRBod *)(this + 0x44798),pcVar2);
  ObjectProcTileFast(*(cRObject **)(this + 0x447bc),"Objects/Universe/Ramp.tga",fVar16);
  ObjectProcTileFastRamp(0,*(cRObject **)(this + 0x447bc));
  pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
  fVar16 = (float)cRBod::SetObject((cRBod *)(this + 0x447c4),pcVar2);
  ObjectProcTileFast(*(cRObject **)(this + 0x447e8),"Objects/Universe/Ramp.tga",fVar16);
  ObjectProcTileFastRamp(1,*(cRObject **)(this + 0x447e8));
  pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
  cRBod::SetObject((cRBod *)(this + 0x43f00),pcVar2);
  uVar17 = ObjectProcTileFloorCornerFast
                     (0,*(cRObject **)(this + 0x43f24),"Objects/World00/Surface0.png");
  cRObject::ApplyUV(*(cRObject **)(this + 0x43f24),(float)uVar17,(float)((ulonglong)uVar17 >> 0x20))
  ;
  pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
  cRBod::SetObject((cRBod *)(this + 0x43f2c),pcVar2);
  uVar17 = ObjectProcTileFloorCornerFast
                     (1,*(cRObject **)(this + 0x43f50),"Objects/World00/Surface0.png");
  cRObject::ApplyUV(*(cRObject **)(this + 0x43f50),(float)uVar17,(float)((ulonglong)uVar17 >> 0x20))
  ;
  pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
  cRBod::SetObject((cRBod *)(this + 0x43f84),pcVar2);
  uVar17 = ObjectProcTileFloorCornerFast
                     (2,*(cRObject **)(this + 0x43fa8),"Objects/World00/Surface0.png");
  cRObject::ApplyUV(*(cRObject **)(this + 0x43fa8),(float)uVar17,(float)((ulonglong)uVar17 >> 0x20))
  ;
  pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
  cRBod::SetObject((cRBod *)(this + 0x43f58),pcVar2);
  uVar17 = ObjectProcTileFloorCornerFast
                     (3,*(cRObject **)(this + 0x43f7c),"Objects/World00/Surface0.png");
  cRObject::ApplyUV(*(cRObject **)(this + 0x43f7c),(float)uVar17,(float)((ulonglong)uVar17 >> 0x20))
  ;
  pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
  cRBod::SetObject((cRBod *)(this + 0x43fb0),pcVar2);
  uVar17 = ObjectProcTileFloorCornerFast
                     (0,*(cRObject **)(this + 0x43fd4),"Objects/World00/Surface0.png");
  cRObject::ApplyUV(*(cRObject **)(this + 0x43fd4),(float)uVar17,(float)((ulonglong)uVar17 >> 0x20))
  ;
  pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
  cRBod::SetObject((cRBod *)(this + 0x43fdc),pcVar2);
  uVar17 = ObjectProcTileFloorCornerFast
                     (1,*(cRObject **)(this + 0x44000),"Objects/World00/Surface0.png");
  cRObject::ApplyUV(*(cRObject **)(this + 0x44000),(float)uVar17,(float)((ulonglong)uVar17 >> 0x20))
  ;
  pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
  cRBod::SetObject((cRBod *)(this + 0x44034),pcVar2);
  uVar17 = ObjectProcTileFloorCornerFast
                     (2,*(cRObject **)(this + 0x44058),"Objects/World00/Surface0.png");
  cRObject::ApplyUV(*(cRObject **)(this + 0x44058),(float)uVar17,(float)((ulonglong)uVar17 >> 0x20))
  ;
  pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
  pcVar9 = this + 0x75ac4;
  cRBod::SetObject((cRBod *)(this + 0x44008),pcVar2);
  uVar17 = ObjectProcTileFloorCornerFast
                     (3,*(cRObject **)(this + 0x4402c),"Objects/World00/Surface0.png");
  cRObject::ApplyUV(*(cRObject **)(this + 0x4402c),(float)uVar17,(float)((ulonglong)uVar17 >> 0x20))
  ;
  pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
  pcVar14 = this + 0x718a0;
  cRBod::SetObject((cRBod *)(this + 0x44060),pcVar2);
  uVar17 = ObjectProcTileFloorCornerFast
                     (0,*(cRObject **)(this + 0x44084),"Objects/World00/Surface0.png");
  cRObject::ApplyUV(*(cRObject **)(this + 0x44084),(float)uVar17,(float)((ulonglong)uVar17 >> 0x20))
  ;
  pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
  cRBod::SetObject((cRBod *)(this + 0x4408c),pcVar2);
  uVar17 = ObjectProcTileFloorCornerFast
                     (1,*(cRObject **)(this + 0x440b0),"Objects/World00/Surface0.png");
  cRObject::ApplyUV(*(cRObject **)(this + 0x440b0),(float)uVar17,(float)((ulonglong)uVar17 >> 0x20))
  ;
  pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
  cRBod::SetObject((cRBod *)(this + 0x440e4),pcVar2);
  uVar17 = ObjectProcTileFloorCornerFast
                     (2,*(cRObject **)(this + 0x44108),"Objects/World00/Surface0.png");
  cRObject::ApplyUV(*(cRObject **)(this + 0x44108),(float)uVar17,(float)((ulonglong)uVar17 >> 0x20))
  ;
  pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
  cRBod::SetObject((cRBod *)(this + 0x440b8),pcVar2);
  uVar17 = ObjectProcTileFloorCornerFast
                     (3,*(cRObject **)(this + 0x440dc),"Objects/World00/Surface0.png");
  cRObject::ApplyUV(*(cRObject **)(this + 0x440dc),(float)uVar17,(float)((ulonglong)uVar17 >> 0x20))
  ;
  pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
  cRBod::SetObject((cRBod *)(this + 0x44110),pcVar2);
  pcVar2 = *(cRObject **)(this + 0x44134);
  *(uint *)pcVar2 = *(uint *)pcVar2 | 0x1000;
  cRDirectX::Load(this_00,"Tramp.x",pcVar2,1);
  *(undefined4 *)(*(int *)(this + 0x44134) + 8) = 1;
  pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
  fVar16 = (float)cRBod::SetObject((cRBod *)(this + 0x43e24),pcVar2);
  ObjectProcTileFast(*(cRObject **)(this + 0x43e48),"Objects/Universe/Hole.tga",fVar16);
  iVar11 = *(int *)(this + 0x43e48);
  *(undefined4 *)(iVar11 + 8) = 5;
  puVar7 = *(uint **)(*(int *)(iVar11 + 200) + 0xc);
  *puVar7 = *puVar7 | 0x400;
  pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
  cRBod::SetObject((cRBod *)(this + 0x447f0),pcVar2);
  ObjectTextLoad("Objects/Lazer",*(cRObject **)(this + 0x44814));
  iVar11 = 0;
  do {
    iVar13 = iVar11 * 0xa4;
    iVar11 = iVar11 + 1;
    cRBod::SetObject((cRBod *)(this + iVar13 + 0x75a48),*(cRObject **)(this + 0x44814));
    *(cRGame **)pcVar9 = pcVar14;
    puVar7 = *(uint **)(*(int *)(*(int *)(pcVar9 + -0x58) + 200) + 0xc);
    *puVar7 = *puVar7 | 0x400;
    tColourSmall::Set((tColourSmall *)(this + iVar13 + 0x75a70),extraout_s0,extraout_s1,extraout_s2,
                      extraout_s3);
    *(undefined4 *)(*(int *)(pcVar9 + -0x58) + 8) = 5;
    *(uint *)(pcVar9 + -0x78) = *(uint *)(pcVar9 + -0x78) | 0x80;
    pcVar9 = pcVar9 + 0xa4;
  } while (iVar11 != 0x14);
  iVar11 = 0;
  pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
  cRBod::SetObject((cRBod *)(this + 0x47aa4),pcVar2);
  ObjectTextLoad("Objects/TrampRing",*(cRObject **)(this + 0x47ac8));
  pcVar9 = this + 0x3a5f30;
  do {
    iVar13 = iVar11 * 0x84;
    iVar11 = iVar11 + 1;
    cRBod::SetObject((cRBod *)(this + iVar13 + 0x3a5eb0),*(cRObject **)(this + 0x47ac8));
    iVar8 = *(int *)(pcVar9 + -0x5c);
    *(cRGame **)pcVar9 = pcVar14;
    puVar7 = *(uint **)(*(int *)(iVar8 + 200) + 0xc);
    *puVar7 = *puVar7 | 0x400;
    *(undefined4 *)(iVar8 + 8) = 1;
    tMatrix::Identity((tMatrix *)(this + iVar13 + 0x3a5edc));
    pcVar9 = pcVar9 + 0x84;
  } while (iVar11 != 8);
  cRSubTrampRingManager::Init((cRSubTrampRingManager *)(this + 0x3a5eb0));
  iVar13 = 1;
  pcVar9 = this + 0x76794;
  pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
  cRBod::SetObject((cRBod *)(this + 0x47a78),pcVar2);
  pcVar2 = *(cRObject **)(this + 0x47a9c);
  *(uint *)pcVar2 = *(uint *)pcVar2 | 0x1000;
  cRDirectX::Load(this_00,"salt.x",pcVar2,1);
  iVar11 = 0;
  do {
    iVar8 = iVar11 * 0x8c;
    iVar11 = iVar11 + 1;
    cRBod::SetObject((cRBod *)(this + iVar8 + 0x76718),*(cRObject **)(this + 0x47a9c));
    *(cRGame **)pcVar9 = pcVar14;
    tColourSmall::Set((tColourSmall *)(this + iVar8 + 0x76740),extraout_s0_00,extraout_s1_00,
                      extraout_s2_00,extraout_s3_00);
    pcVar1 = pcVar9 + -0x58;
    pcVar9 = pcVar9 + 0x8c;
    *(undefined4 *)(*(int *)pcVar1 + 8) = 1;
    tMatrix::Identity((tMatrix *)((tColourSmall *)(this + iVar8 + 0x76740) + 4));
  } while (iVar11 != 0x28);
  pcVar9 = this + 0x77d10;
  iVar11 = 0;
  do {
    pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
    cRBod::SetObject((cRBod *)(this + iVar11 * 0x54 + 0x77cf8),pcVar2);
    if (iVar11 == 0) {
      pcVar2 = *(cRObject **)(this + 0x77d1c);
      *(uint *)pcVar2 = *(uint *)pcVar2 | 0x1000;
      cRDirectX::Load(this_00,"postofficestop.x",pcVar2,1);
      *(undefined4 *)pcVar9 = 0;
      *(undefined4 *)(pcVar9 + -4) = 0;
      *(undefined4 *)(pcVar9 + -8) = 0;
      *(cRGame **)(pcVar9 + 0x24) = pcVar14;
      *(undefined4 *)(pcVar9 + 0x34) = 0;
      *(undefined4 *)(pcVar9 + 0x14) = 0;
      *(undefined4 *)(pcVar9 + 0x38) = 0x3be38e39;
    }
    else {
      pcVar2 = *(cRObject **)(this + 0x77d70);
      *(uint *)pcVar2 = *(uint *)pcVar2 | 0x1000;
      cRDirectX::Load(this_00,"postofficestop.x",pcVar2,1);
      *(undefined4 *)pcVar9 = 0;
      *(undefined4 *)(pcVar9 + -4) = 0;
      *(undefined4 *)(pcVar9 + -8) = 0;
      *(cRGame **)(pcVar9 + 0x24) = pcVar14;
      *(int *)(pcVar9 + 0x14) = iVar11;
      *(undefined4 *)(pcVar9 + 0x34) = 0;
      *(undefined4 *)(pcVar9 + 0x38) = 0x3be38e39;
      if (1 < iVar13) {
        pcVar10 = (cRBod *)(this + 0x744bc);
        this_01 = (cLinkedList<cRBod> *)(this + 0x358);
        cLinkedList<cRBod>::Add(this_01,(cRBod *)(this + 0x7456c));
        cLinkedList<cRBod>::Add(this_01,pcVar10);
        cLinkedList<cRBod>::Add(this_01,(cRBod *)(this + 0x744e8));
        cLinkedList<cRBod>::Add(this_01,(cRBod *)(this + 0x74514));
        cLinkedList<cRBod>::AddAfter(this_01,(cRBod *)(this + 0x74540),pcVar10);
        cLinkedList<cRBod>::AddAfter(this_01,(cRBod *)(this + 0x74598),pcVar10);
        cLinkedList<cRBod>::AddAfter(this_01,(cRBod *)(this + 0x74674),pcVar10);
        cLinkedList<cRBod>::AddAfter(this_01,(cRBod *)(this + 0x74490),pcVar10);
        cLinkedList<cRBod>::AddAfter(this_01,(cRBod *)(this + 0x7461c),pcVar10);
        cLinkedList<cRBod>::AddAfter(this_01,(cRBod *)(this + 0x74648),pcVar10);
        cLinkedList<cRBod>::AddAfter(this_01,(cRBod *)(this + 0x745c4),pcVar10);
        cLinkedList<cRBod>::AddAfter(this_01,(cRBod *)(this + 0x745f0),pcVar10);
        pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
        cRBod::SetObject((cRBod *)(this + 0x83ca4),pcVar2);
        pcVar3 = (char *)Rstrfind("Test:",*(char **)(this + 0x47ad0));
        if (pcVar3 == (char *)0x0) {
          Rstrcpy(local_bc,"turbo-base-000.x");
        }
        else {
          iVar11 = Rstrfind(":",pcVar3);
          cVar5 = *(char *)(iVar11 + 1);
          if (cVar5 == '.') {
            pcVar3 = local_bc;
          }
          else {
            pcVar3 = local_bc;
            do {
              pcVar3 = pcVar3 + 1;
              pcVar3[-1] = cVar5;
              cVar5 = *(char *)(iVar11 + 2);
              iVar11 = iVar11 + 1;
            } while (cVar5 != '.');
          }
          *pcVar3 = '.';
          pcVar3[1] = 'x';
          pcVar3[2] = '\0';
        }
        cRDirectX::LoadAnim(this_00,local_bc,*(cRObject **)(this + 0x83cc8));
        pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
        cRBod::SetObject((cRBod *)(this + 0x83b64),pcVar2);
        iVar11 = 0;
        cRDirectX::LoadAnim(this_00,local_bc,*(cRObject **)(this + 0x83b88));
        pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
        cRBod::SetObject((cRBod *)(this + 0x83d18),pcVar2);
        cRDirectX::LoadAnim(this_00,"turbo-move-000.x",*(cRObject **)(this + 0x83d3c));
        pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
        cRBod::SetObject((cRBod *)(this + 0x83d8c),pcVar2);
        cRDirectX::LoadAnim(this_00,"turbo-bobalong-000.x",*(cRObject **)(this + 0x83db0));
        pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
        cRBod::SetObject((cRBod *)(this + 0x83e00),pcVar2);
        cRDirectX::LoadAnim(this_00,"turbo-lookbackleft-000.x",*(cRObject **)(this + 0x83e24));
        pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
        cRBod::SetObject((cRBod *)(this + 0x83e74),pcVar2);
        cRDirectX::LoadAnim(this_00,"turbo-lookbackright-000.x",*(cRObject **)(this + 0x83e98));
        pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
        cRBod::SetObject((cRBod *)(this + 0x83ee8),pcVar2);
        cRDirectX::LoadAnim(this_00,"turbo-fall-000.x",*(cRObject **)(this + 0x83f0c));
        pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
        cRBod::SetObject((cRBod *)(this + 0x83f5c),pcVar2);
        cRDirectX::LoadAnim(this_00,"turbo-damaged-000.x",*(cRObject **)(this + 0x83f80));
        pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
        cRBod::SetObject((cRBod *)(this + 0x83fd0),pcVar2);
        cRDirectX::LoadAnim(this_00,"turbo-intoshell-000.x",*(cRObject **)(this + 0x83ff4));
        pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
        cRBod::SetObject((cRBod *)(this + 0x84044),pcVar2);
        cRDirectX::LoadAnim(this_00,"turbo-skidstop-000.x",*(cRObject **)(this + 0x84068));
        pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
        cRBod::SetObject((cRBod *)(this + 0x840b8),pcVar2);
        cRDirectX::LoadAnim(this_00,"turbo-talk-000.x",*(cRObject **)(this + 0x840dc));
        pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
        cRBod::SetObject((cRBod *)(this + 0x85000),pcVar2);
        cRDirectX::Load(this_00,"TurboHotSpots.x",*(cRObject **)(this + 0x85024),2);
        **(uint **)(this + 0x85024) = **(uint **)(this + 0x85024) | 0x8000000;
        cRSnail::ExtractHotSpots((cRSnail *)(this + 0x83b64));
        pcVar9 = this + 0x83cc8;
        do {
          pcVar2 = *(cRObject **)pcVar9;
          iVar11 = iVar11 + 1;
          *(uint *)pcVar2 = *(uint *)pcVar2 | 4;
          cRObject::ApplyToon(pcVar2,0);
          iVar13 = *(int *)pcVar9;
          *(undefined4 *)(iVar13 + 0xf8) = 0;
          *(undefined4 *)(iVar13 + 0xf0) = 0;
          *(undefined4 *)(iVar13 + 0xf4) = 0;
          pcVar9 = pcVar9 + 0x74;
        } while (iVar11 != 10);
        iVar13 = 0;
        pcVar2 = *(cRObject **)(this + 0x83b88);
        *(uint *)pcVar2 = *(uint *)pcVar2 | 4;
        cRObject::ApplyToon(pcVar2,0);
        iVar11 = *(int *)(this + 0x83b88);
        *(undefined4 *)(iVar11 + 0xf8) = 0;
        *(undefined4 *)(iVar11 + 0xf0) = 0;
        *(undefined4 *)(iVar11 + 0xf4) = 0;
        pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
        cRBod::SetObject((cRBod *)(this + 0x84be8),pcVar2);
        cRDirectX::LoadAnim(this_00,"jetpack-base-000.x",*(cRObject **)(this + 0x84c0c));
        pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
        cRBod::SetObject((cRBod *)(this + 0x84d2c),pcVar2);
        cRDirectX::LoadAnim(this_00,"jetpack-base-000.x",*(cRObject **)(this + 0x84d50));
        pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
        cRBod::SetObject((cRBod *)(this + 0x84da0),pcVar2);
        cRDirectX::LoadAnim(this_00,"jetpack-draw-000.x",*(cRObject **)(this + 0x84dc4));
        pcVar2 = *(cRObject **)(this + 0x84d50);
        *(uint *)pcVar2 = *(uint *)pcVar2 | 4;
        cRObject::ApplyToon(pcVar2,0);
        pcVar2 = *(cRObject **)(this + 0x84dc4);
        iVar11 = *(int *)(this + 0x84d50);
        *(undefined4 *)(iVar11 + 0xf8) = 0;
        *(undefined4 *)(iVar11 + 0xf0) = 0;
        uVar6 = *(uint *)pcVar2;
        *(undefined4 *)(iVar11 + 0xf4) = 0;
        *(uint *)pcVar2 = uVar6 | 4;
        cRObject::ApplyToon(pcVar2,0);
        pcVar2 = *(cRObject **)(this + 0x84c0c);
        iVar11 = *(int *)(this + 0x84dc4);
        *(undefined4 *)(iVar11 + 0xf8) = 0;
        *(undefined4 *)(iVar11 + 0xf0) = 0;
        uVar6 = *(uint *)pcVar2;
        *(undefined4 *)(iVar11 + 0xf4) = 0;
        *(uint *)pcVar2 = uVar6 | 4;
        cRObject::ApplyToon(pcVar2,0);
        iVar11 = *(int *)(this + 0x84c0c);
        *(undefined4 *)(iVar11 + 0xf8) = 0;
        *(undefined4 *)(iVar11 + 0xf0) = 0;
        *(undefined4 *)(iVar11 + 0xf4) = 0;
        pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
        cRBod::SetObject((cRBod *)(this + 0x8412c),pcVar2);
        cRDirectX::LoadAnim(this_00,"blasterleft-base-000.x",*(cRObject **)(this + 0x84150));
        pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
        cRBod::SetObject((cRBod *)(this + 0x84270),pcVar2);
        cRDirectX::LoadAnim(this_00,"blasterleft-base-000.x",*(cRObject **)(this + 0x84294));
        pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
        cRBod::SetObject((cRBod *)(this + 0x842e4),pcVar2);
        cRDirectX::LoadAnim(this_00,"blasterleft-draw-000.x",*(cRObject **)(this + 0x84308));
        pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
        cRBod::SetObject((cRBod *)(this + 0x84358),pcVar2);
        cRDirectX::LoadAnim(this_00,"blasterleft-fire-000.x",*(cRObject **)(this + 0x8437c));
        pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
        cRBod::SetObject((cRBod *)(this + 0x843cc),pcVar2);
        cRDirectX::LoadAnim(this_00,"Laserleft-base-000.x",*(cRObject **)(this + 0x843f0));
        pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
        cRBod::SetObject((cRBod *)(this + 0x84440),pcVar2);
        cRDirectX::LoadAnim(this_00,"Laserleft-draw-000.x",*(cRObject **)(this + 0x84464));
        pcVar9 = this + 0x84294;
        do {
          pcVar2 = *(cRObject **)pcVar9;
          iVar13 = iVar13 + 1;
          *(uint *)pcVar2 = *(uint *)pcVar2 | 4;
          cRObject::ApplyToon(pcVar2,0);
          iVar11 = *(int *)pcVar9;
          *(undefined4 *)(iVar11 + 0xf8) = 0;
          *(undefined4 *)(iVar11 + 0xf0) = 0;
          *(undefined4 *)(iVar11 + 0xf4) = 0;
          pcVar9 = pcVar9 + 0x74;
        } while (iVar13 != 5);
        iVar13 = 0;
        pcVar2 = *(cRObject **)(this + 0x84150);
        *(uint *)pcVar2 = *(uint *)pcVar2 | 4;
        cRObject::ApplyToon(pcVar2,0);
        iVar11 = *(int *)(this + 0x84150);
        *(undefined4 *)(iVar11 + 0xf8) = 0;
        *(undefined4 *)(iVar11 + 0xf0) = 0;
        *(undefined4 *)(iVar11 + 0xf4) = 0;
        pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
        cRBod::SetObject((cRBod *)(this + 0x844c0),pcVar2);
        cRDirectX::LoadAnim(this_00,"blasterRight-base-000.x",*(cRObject **)(this + 0x844e4));
        pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
        cRBod::SetObject((cRBod *)(this + 0x84604),pcVar2);
        cRDirectX::LoadAnim(this_00,"blasterRight-base-000.x",*(cRObject **)(this + 0x84628));
        pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
        cRBod::SetObject((cRBod *)(this + 0x84678),pcVar2);
        cRDirectX::LoadAnim(this_00,"blasterRight-draw-000.x",*(cRObject **)(this + 0x8469c));
        pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
        cRBod::SetObject((cRBod *)(this + 0x846ec),pcVar2);
        cRDirectX::LoadAnim(this_00,"blasterRight-fire-000.x",*(cRObject **)(this + 0x84710));
        pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
        cRBod::SetObject((cRBod *)(this + 0x84760),pcVar2);
        cRDirectX::LoadAnim(this_00,"Laserright-base-000.x",*(cRObject **)(this + 0x84784));
        pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
        cRBod::SetObject((cRBod *)(this + 0x847d4),pcVar2);
        cRDirectX::LoadAnim(this_00,"Laserright-draw-000.x",*(cRObject **)(this + 0x847f8));
        pcVar9 = this + 0x84628;
        do {
          pcVar2 = *(cRObject **)pcVar9;
          iVar13 = iVar13 + 1;
          *(uint *)pcVar2 = *(uint *)pcVar2 | 4;
          cRObject::ApplyToon(pcVar2,0);
          iVar11 = *(int *)pcVar9;
          *(undefined4 *)(iVar11 + 0xf8) = 0;
          *(undefined4 *)(iVar11 + 0xf0) = 0;
          *(undefined4 *)(iVar11 + 0xf4) = 0;
          pcVar9 = pcVar9 + 0x74;
        } while (iVar13 != 5);
        iVar13 = 0;
        pcVar2 = *(cRObject **)(this + 0x844e4);
        *(uint *)pcVar2 = *(uint *)pcVar2 | 4;
        cRObject::ApplyToon(pcVar2,0);
        iVar11 = *(int *)(this + 0x844e4);
        *(undefined4 *)(iVar11 + 0xf8) = 0;
        *(undefined4 *)(iVar11 + 0xf0) = 0;
        *(undefined4 *)(iVar11 + 0xf4) = 0;
        pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
        cRBod::SetObject((cRBod *)(this + 0x84854),pcVar2);
        cRDirectX::LoadAnim(this_00,"blasterTop-base-000.x",*(cRObject **)(this + 0x84878));
        pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
        cRBod::SetObject((cRBod *)(this + 0x84998),pcVar2);
        cRDirectX::LoadAnim(this_00,"blasterTop-base-000.x",*(cRObject **)(this + 0x849bc));
        pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
        cRBod::SetObject((cRBod *)(this + 0x84a0c),pcVar2);
        cRDirectX::LoadAnim(this_00,"blasterTop-draw-000.x",*(cRObject **)(this + 0x84a30));
        pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
        cRBod::SetObject((cRBod *)(this + 0x84a80),pcVar2);
        cRDirectX::LoadAnim(this_00,"blasterTop-fire-000.x",*(cRObject **)(this + 0x84aa4));
        pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
        cRBod::SetObject((cRBod *)(this + 0x84af4),pcVar2);
        cRDirectX::LoadAnim(this_00,"rocketlauncher-base-000.x",*(cRObject **)(this + 0x84b18));
        pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
        cRBod::SetObject((cRBod *)(this + 0x84b68),pcVar2);
        cRDirectX::LoadAnim(this_00,"rocketlauncher-draw-000.x",*(cRObject **)(this + 0x84b8c));
        pcVar9 = this + 0x849bc;
        do {
          pcVar2 = *(cRObject **)pcVar9;
          iVar13 = iVar13 + 1;
          *(uint *)pcVar2 = *(uint *)pcVar2 | 4;
          cRObject::ApplyToon(pcVar2,0);
          iVar11 = *(int *)pcVar9;
          *(undefined4 *)(iVar11 + 0xf8) = 0;
          *(undefined4 *)(iVar11 + 0xf0) = 0;
          *(undefined4 *)(iVar11 + 0xf4) = 0;
          pcVar9 = pcVar9 + 0x74;
        } while (iVar13 != 5);
        pcVar2 = *(cRObject **)(this + 0x84878);
        *(uint *)pcVar2 = *(uint *)pcVar2 | 4;
        cRObject::ApplyToon(pcVar2,0);
        iVar11 = *(int *)(this + 0x84878);
        *(undefined4 *)(iVar11 + 0xf8) = 0;
        *(undefined4 *)(iVar11 + 0xf0) = 0;
        *(undefined4 *)(iVar11 + 0xf4) = 0;
        uVar4 = cRTextures::Add((cRTextures *)gTextureList,"x/snail-turbo.tga",(cTgaHeader *)0x0,0);
        iVar11 = 0;
        *(undefined4 *)(this + 0x852d8) = uVar4;
        uVar4 = cRTextures::Add((cRTextures *)gTextureList,"x/snail-turbo-damage.tga",
                                (cTgaHeader *)0x0,0);
        *(undefined4 *)(this + 0x852dc) = uVar4;
        uVar4 = cRTextures::Add((cRTextures *)gTextureList,"x/snail-turbo-invincible.tga",
                                (cTgaHeader *)0x0,0);
        *(undefined4 *)(this + 0x852e0) = uVar4;
        pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
        cRBod::SetObject((cRBod *)(this + 0x8523c),pcVar2);
        cRDirectX::Load(this_00,"invincible-base-000.x",*(cRObject **)(this + 0x85260),1);
        puVar7 = *(uint **)(this + 0x85260);
        puVar7[2] = 1;
        *puVar7 = *puVar7 | 0x100000;
        pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
        cRBod::SetObject((cRBod *)(this + 0x818b0),pcVar2);
        cRDirectX::Load(this_00,"rocket-base-000.x",*(cRObject **)(this + 0x818d4),1);
        pcVar9 = this + 0x81848;
        do {
          iVar13 = iVar11 * 0x2c8;
          pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
          iVar11 = iVar11 + 1;
          cRBod::SetObject((cRBod *)(this + iVar13 + 0x81824),pcVar2);
          pcVar2 = *(cRObject **)pcVar9;
          *(undefined4 *)(pcVar2 + 8) = 1;
          *(uint *)pcVar2 = *(uint *)pcVar2 | 0x100004;
          fVar16 = (float)ObjectTextLoad("Objects/VapourLazer",pcVar2);
          cRVapour::Init((cRVapour *)(this + iVar13 + 0x81824),*(cRObject **)pcVar9,fVar16);
          cRBod::SetObject((cRBod *)(this + iVar13 + 0x818b0),*(cRObject **)(this + 0x818d4));
          pcVar9 = pcVar9 + 0x2c8;
        } while (iVar11 != 0xc);
        puVar7 = (uint *)cRTextures::Add((cRTextures *)gTextureList,"Objects/VapourLazer/Lazer.tga",
                                         (cTgaHeader *)0x0,0);
        *puVar7 = *puVar7 | 0x400;
        puVar7 = (uint *)cRTextures::Add((cRTextures *)gTextureList,"Objects/World00/Worm.png",
                                         (cTgaHeader *)0x0,0);
        *puVar7 = *puVar7 | 0x1403;
        puVar7 = (uint *)cRTextures::Add((cRTextures *)gTextureList,"Objects/World00/Surface0.png",
                                         (cTgaHeader *)0x0,0);
        local_124 = 0x3a;
        *puVar7 = *puVar7 | 0x1400;
        puVar7 = (uint *)cRTextures::Add((cRTextures *)gTextureList,"Objects/Universe/Ramp.tga",
                                         (cTgaHeader *)0x0,0);
        local_138 = 0;
        *puVar7 = *puVar7 | 0x1000;
        *(undefined4 *)(this + 0xbcc) = 0xffffffff;
        puVar7 = (uint *)cRTextures::Add((cRTextures *)gTextureList,"Objects/World00/Surface0.png",
                                         (cTgaHeader *)0x0,0);
        uVar6 = *puVar7;
        *(uint **)(this + 0x848) = puVar7;
        *puVar7 = uVar6 | 0x1000;
        *(undefined4 *)(this + 0x84c) = 0x656a624f;
        *(undefined4 *)(this + 0x850) = 0x2f737463;
        *(undefined4 *)(this + 0x854) = 0x6c726f57;
        *(undefined4 *)(this + 0x858) = 0x2f303064;
        *(undefined4 *)(this + 0x85c) = 0x66727553;
        *(undefined4 *)(this + 0x860) = 0x30656361;
        *(undefined4 *)(this + 0x864) = 0x676e702e;
        this[0x868] = (cRGame)0x0;
        *(undefined4 *)(this + 0x8cc) = 0x656a624f;
        *(undefined4 *)(this + 0x8d0) = 0x2f737463;
        *(undefined4 *)(this + 0x8d4) = 0x6c726f57;
        *(undefined4 *)(this + 0x8d8) = 0x2f303064;
        *(undefined4 *)(this + 0x8dc) = 0x66727553;
        *(undefined4 *)(this + 0x8e0) = 0x31656361;
        *(undefined4 *)(this + 0x8e4) = 0x676e702e;
        this[0x8e8] = (cRGame)0x0;
        *(undefined4 *)(this + 0x94c) = 0x656a624f;
        *(undefined4 *)(this + 0x950) = 0x2f737463;
        *(undefined4 *)(this + 0x954) = 0x6c726f57;
        *(undefined4 *)(this + 0x958) = 0x2f303064;
        *(undefined4 *)(this + 0x95c) = 0x66727553;
        *(undefined4 *)(this + 0x960) = 0x32656361;
        *(undefined4 *)(this + 0x964) = 0x676e702e;
        this[0x968] = (cRGame)0x0;
        *(undefined4 *)(this + 0x9cc) = 0x656a624f;
        *(undefined4 *)(this + 0x9d0) = 0x2f737463;
        *(undefined4 *)(this + 0x9d4) = 0x6c726f57;
        *(undefined4 *)(this + 0x9d8) = 0x2f303064;
        *(undefined4 *)(this + 0x9dc) = 0x66727553;
        *(undefined4 *)(this + 0x9e0) = 0x33656361;
        *(undefined4 *)(this + 0x9e4) = 0x676e702e;
        this[0x9e8] = (cRGame)0x0;
        *(undefined4 *)(this + 0xa4c) = 0x656a624f;
        *(undefined4 *)(this + 0xa50) = 0x2f737463;
        *(undefined4 *)(this + 0xa54) = 0x6c726f57;
        *(undefined4 *)(this + 0xa58) = 0x2f303064;
        *(undefined4 *)(this + 0xa5c) = 0x66727553;
        *(undefined4 *)(this + 0xa60) = 0x34656361;
        *(undefined4 *)(this + 0xa64) = 0x676e702e;
        this[0xa68] = (cRGame)0x0;
        *(undefined4 *)(this + 0xacc) = 0x656a624f;
        *(undefined4 *)(this + 0xad0) = 0x2f737463;
        *(undefined4 *)(this + 0xad4) = 0x6c726f57;
        *(undefined4 *)(this + 0xad8) = 0x2f303064;
        *(undefined4 *)(this + 0xadc) = 0x66727553;
        *(undefined4 *)(this + 0xae0) = 0x35656361;
        *(undefined4 *)(this + 0xae4) = 0x676e702e;
        this[0xae8] = (cRGame)0x0;
        *(undefined4 *)(this + 0xb4c) = 0x656a624f;
        *(undefined4 *)(this + 0xb50) = 0x2f737463;
        *(undefined4 *)(this + 0xb54) = 0x6c726f57;
        *(undefined4 *)(this + 0xb58) = 0x2f303064;
        *(undefined4 *)(this + 0xb5c) = 0x66727553;
        *(undefined4 *)(this + 0xb60) = 0x36656361;
        *(undefined4 *)(this + 0xb64) = 0x676e702e;
        this[0xb68] = (cRGame)0x0;
        pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
        cRBod::SetObject((cRBod *)(this + 0x3873c4),pcVar2);
        ObjectTextLoad("Objects/Barrier",*(cRObject **)(this + 0x3873e8));
        *(undefined4 *)(this + 0x3873d4) = 0;
        *(undefined4 *)(this + 0x3873dc) = 0;
        *(undefined4 *)(this + 0x3873d8) = 0;
        tColourSmall::Set((tColourSmall *)(this + 0x3873ec),extraout_s0_01,extraout_s1_01,
                          extraout_s2_01,extraout_s3_01);
        *(undefined4 *)(*(int *)(this + 0x3873e8) + 8) = 3;
        cRWorld::Init((cRWorld *)(this + 0x81290),0xe10,0x38,0x38,8);
        do {
          iVar11 = 0;
          local_12c = local_124;
          do {
            iVar8 = -1;
            iVar13 = local_12c;
            do {
              iVar12 = 0;
              pcVar9 = this + iVar13 * 0x2c + 0x43e24;
              do {
                pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
                cRBod::SetObject((cRBod *)(this + (iVar12 + iVar13) * 0x2c + 0x43e24),pcVar2);
                iVar15 = iVar12 + -1;
                iVar12 = iVar12 + 1;
                ObjectProcFringe(*(cRObject **)(pcVar9 + 0x24),local_138,iVar11,iVar8,iVar15,
                                 "Objects/Universe/Fringe.tga");
                pcVar14 = pcVar9 + 0x24;
                pcVar9 = pcVar9 + 0x2c;
                *(undefined4 *)(*(int *)pcVar14 + 8) = 5;
              } while (iVar12 != 3);
              iVar8 = iVar8 + 1;
              iVar13 = iVar13 + 3;
            } while (iVar8 != 2);
            iVar11 = iVar11 + 1;
            local_12c = local_12c + 9;
          } while (iVar11 != 4);
          local_138 = local_138 + 1;
          local_124 = local_124 + 0x24;
        } while (local_138 != 8);
        puVar7 = (uint *)cRTextures::Add((cRTextures *)gTextureList,"Objects/Universe/Fringe.tga",
                                         (cTgaHeader *)0x0,0);
        *puVar7 = *puVar7 | 0x400;
        cLinkedList<cRBod>::Add(this_01,(cRBod *)(this + 0x68));
        *(undefined4 *)(this + 0x94) = 0;
        cRInput::Init((cRInput *)(this + 0x94));
        if (local_3c != __stack_chk_guard) {
                    /* WARNING: Subroutine does not return */
          __stack_chk_fail();
        }
        return;
      }
    }
    iVar11 = iVar11 + 1;
    iVar13 = iVar13 + 1;
    pcVar9 = pcVar9 + 0x54;
  } while( true );
}
