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
  int iVar2;
  int iVar3;
  cRObject *pcVar4;
  cRDirectX *this_00;
  cLinkedList<cRBod> *this_01;
  undefined4 uVar5;
  int iVar6;
  char cVar7;
  uint uVar8;
  undefined4 uVar9;
  uint *puVar10;
  int iVar11;
  undefined4 uVar12;
  undefined4 *puVar13;
  cRGame *pcVar14;
  cRBod *pcVar15;
  int iVar16;
  int iVar17;
  cRObjects *pcVar18;
  cRGame *pcVar19;
  int iVar20;
  cRTextures *pcVar21;
  char *pcVar22;
  int iVar23;
  undefined4 *puVar24;
  char *pcVar25;
  undefined4 *puVar26;
  undefined4 *puVar27;
  undefined4 *puVar28;
  undefined4 *puVar29;
  int iVar30;
  uint in_fpscr;
  float fVar31;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  undefined8 uVar32;
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

  iVar20 = DAT_0003fff4;
  iVar3 = DAT_0003fff0;
  iVar2 = DAT_0003ffec;
  iVar6 = DAT_0003ffe8 + 0x3f6ec;
  pcVar14 = this + 0x44370;
  iVar16 = 0;
  local_3c = **(int **)(iVar6 + DAT_0003ffec);
  pcVar22 = (char *)(iVar6 + DAT_0003fff4);
  wprintf((char *)(iVar6 + DAT_0003fff8));
  pcVar18 = *(cRObjects **)(iVar6 + iVar3);
  do {
    VectorSignedToFloat(iVar16,(byte)(in_fpscr >> 0x16) & 3);
    pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
    iVar17 = iVar16 * 0x2c;
    iVar16 = iVar16 + 1;
    fVar31 = (float)cRBod::SetObject((cRBod *)(this + iVar17 + 0x4434c),pcVar4);
    uVar32 = ObjectProcTileFloorFast(*(cRObject **)pcVar14,pcVar22,fVar31);
    cRObject::ApplyUV(*(cRObject **)pcVar14,(float)uVar32,(float)((ulonglong)uVar32 >> 0x20));
    pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
    fVar31 = (float)cRBod::SetObject((cRBod *)(this + iVar17 + 0x444ac),pcVar4);
    uVar32 = ObjectProcTileFloorFast(*(cRObject **)(pcVar14 + 0x160),pcVar22,fVar31);
    cRObject::ApplyUV(*(cRObject **)(pcVar14 + 0x160),(float)uVar32,
                      (float)((ulonglong)uVar32 >> 0x20));
    pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
    fVar31 = (float)cRBod::SetObject((cRBod *)(this + iVar17 + 0x4460c),pcVar4);
    uVar32 = ObjectProcTileFloorFast(*(cRObject **)(pcVar14 + 0x2c0),pcVar22,fVar31);
    cRObject::ApplyUV(*(cRObject **)(pcVar14 + 0x2c0),(float)uVar32,
                      (float)((ulonglong)uVar32 >> 0x20));
    pcVar14 = pcVar14 + 0x2c;
  } while (iVar16 != 8);
  tMatrix::Identity(atStack_fc);
  pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
  cRBod::SetObject((cRBod *)(this + 0x441ec),pcVar4);
  pcVar4 = *(cRObject **)(this + 0x44210);
  this_00 = (cRDirectX *)(this + 0x47ad0);
  pcVar22 = (char *)(iVar6 + DAT_0003fffc);
  *(uint *)pcVar4 = *(uint *)pcVar4 | 0x1000;
  cRDirectX::Load(this_00,pcVar22,pcVar4,1);
  if ((**(uint **)(this + 0x44210) & 0x2000000) == 0) {
    local_cc = 0;
    cRBod::ApplyPos((tMatrix *)(this + 0x441ec));
  }
  pcVar4 = (cRObject *)cRObjects::Add(*(cRObjects **)(iVar6 + iVar3));
  cRBod::SetObject((cRBod *)(this + 0x44218),pcVar4);
  pcVar4 = *(cRObject **)(this + 0x4423c);
  pcVar22 = (char *)(iVar6 + DAT_00040000);
  *(uint *)pcVar4 = *(uint *)pcVar4 | 0x1000;
  cRDirectX::Load(this_00,pcVar22,pcVar4,1);
  if ((**(uint **)(this + 0x4423c) & 0x2000000) == 0) {
    local_cc = DAT_000417fc;
    cRBod::ApplyPos((tMatrix *)(this + 0x44218));
  }
  pcVar4 = (cRObject *)cRObjects::Add(*(cRObjects **)(iVar6 + iVar3));
  cRBod::SetObject((cRBod *)(this + 0x44244),pcVar4);
  pcVar4 = *(cRObject **)(this + 0x44268);
  pcVar22 = (char *)(iVar6 + DAT_00040004);
  *(uint *)pcVar4 = *(uint *)pcVar4 | 0x1000;
  cRDirectX::Load(this_00,pcVar22,pcVar4,1);
  if ((**(uint **)(this + 0x44268) & 0x2000000) == 0) {
    local_cc = DAT_000417f8;
    cRBod::ApplyPos((tMatrix *)(this + 0x44244));
  }
  pcVar4 = (cRObject *)cRObjects::Add(*(cRObjects **)(iVar6 + iVar3));
  cRBod::SetObject((cRBod *)(this + 0x44270),pcVar4);
  pcVar4 = *(cRObject **)(this + 0x44294);
  pcVar22 = (char *)(iVar6 + DAT_00040008);
  *(uint *)pcVar4 = *(uint *)pcVar4 | 0x1000;
  cRDirectX::Load(this_00,pcVar22,pcVar4,1);
  if ((**(uint **)(this + 0x44294) & 0x2000000) == 0) {
    local_cc = DAT_000417f4;
    cRBod::ApplyPos((tMatrix *)(this + 0x44270));
  }
  pcVar4 = (cRObject *)cRObjects::Add(*(cRObjects **)(iVar6 + iVar3));
  cRBod::SetObject((cRBod *)(this + 0x4429c),pcVar4);
  pcVar4 = *(cRObject **)(this + 0x442c0);
  pcVar22 = (char *)(iVar6 + DAT_0004000c);
  *(uint *)pcVar4 = *(uint *)pcVar4 | 0x1000;
  cRDirectX::Load(this_00,pcVar22,pcVar4,1);
  if ((**(uint **)(this + 0x442c0) & 0x2000000) == 0) {
    local_cc = DAT_000417f0;
    cRBod::ApplyPos((tMatrix *)(this + 0x4429c));
  }
  pcVar4 = (cRObject *)cRObjects::Add(*(cRObjects **)(iVar6 + iVar3));
  cRBod::SetObject((cRBod *)(this + 0x442c8),pcVar4);
  pcVar4 = *(cRObject **)(this + 0x442ec);
  pcVar22 = (char *)(iVar6 + DAT_00040010);
  *(uint *)pcVar4 = *(uint *)pcVar4 | 0x1000;
  cRDirectX::Load(this_00,pcVar22,pcVar4,1);
  if ((**(uint **)(this + 0x442ec) & 0x2000000) == 0) {
    local_cc = DAT_000417ec;
    cRBod::ApplyPos((tMatrix *)(this + 0x442c8));
  }
  pcVar4 = (cRObject *)cRObjects::Add(*(cRObjects **)(iVar6 + iVar3));
  cRBod::SetObject((cRBod *)(this + 0x442f4),pcVar4);
  pcVar4 = *(cRObject **)(this + 0x44318);
  pcVar22 = (char *)(iVar6 + DAT_00040014);
  *(uint *)pcVar4 = *(uint *)pcVar4 | 0x1000;
  cRDirectX::Load(this_00,pcVar22,pcVar4,1);
  if ((**(uint **)(this + 0x44318) & 0x2000000) == 0) {
    local_cc = DAT_000417e8;
    cRBod::ApplyPos((tMatrix *)(this + 0x442f4));
  }
  pcVar4 = (cRObject *)cRObjects::Add(*(cRObjects **)(iVar6 + iVar3));
  cRBod::SetObject((cRBod *)(this + 0x44320),pcVar4);
  pcVar4 = *(cRObject **)(this + 0x44344);
  pcVar22 = (char *)(iVar6 + DAT_00040018);
  *(uint *)pcVar4 = *(uint *)pcVar4 | 0x1000;
  cRDirectX::Load(this_00,pcVar22,pcVar4,1);
  if ((**(uint **)(this + 0x44344) & 0x2000000) == 0) {
    local_cc = DAT_000417e4;
    cRBod::ApplyPos((tMatrix *)(this + 0x44320));
  }
  iVar16 = 0;
  pcVar14 = this + 0x44210;
  do {
    puVar10 = *(uint **)pcVar14;
    iVar16 = iVar16 + 1;
    puVar10[2] = 0;
    *puVar10 = *puVar10 & 0xffefffff;
    iVar17 = DAT_0004001c;
    pcVar14 = pcVar14 + 0x2c;
  } while (iVar16 != 8);
  pcVar18 = *(cRObjects **)(iVar6 + iVar3);
  pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
  pcVar22 = (char *)(iVar6 + iVar17);
  fVar31 = (float)cRBod::SetObject((cRBod *)(this + 0x4476c),pcVar4);
  ObjectProcTileFast(*(cRObject **)(this + 0x44790),pcVar22,fVar31);
  ObjectProcTileFastRamp(-1,*(cRObject **)(this + 0x44790));
  pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
  fVar31 = (float)cRBod::SetObject((cRBod *)(this + 0x44798),pcVar4);
  ObjectProcTileFast(*(cRObject **)(this + 0x447bc),pcVar22,fVar31);
  ObjectProcTileFastRamp(0,*(cRObject **)(this + 0x447bc));
  pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
  pcVar25 = (char *)(iVar6 + iVar20);
  fVar31 = (float)cRBod::SetObject((cRBod *)(this + 0x447c4),pcVar4);
  ObjectProcTileFast(*(cRObject **)(this + 0x447e8),pcVar22,fVar31);
  ObjectProcTileFastRamp(1,*(cRObject **)(this + 0x447e8));
  pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
  cRBod::SetObject((cRBod *)(this + 0x43f00),pcVar4);
  uVar32 = ObjectProcTileFloorCornerFast(0,*(cRObject **)(this + 0x43f24),pcVar25);
  cRObject::ApplyUV(*(cRObject **)(this + 0x43f24),(float)uVar32,(float)((ulonglong)uVar32 >> 0x20))
  ;
  pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
  cRBod::SetObject((cRBod *)(this + 0x43f2c),pcVar4);
  uVar32 = ObjectProcTileFloorCornerFast(1,*(cRObject **)(this + 0x43f50),pcVar25);
  cRObject::ApplyUV(*(cRObject **)(this + 0x43f50),(float)uVar32,(float)((ulonglong)uVar32 >> 0x20))
  ;
  pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
  cRBod::SetObject((cRBod *)(this + 0x43f84),pcVar4);
  uVar32 = ObjectProcTileFloorCornerFast(2,*(cRObject **)(this + 0x43fa8),pcVar25);
  cRObject::ApplyUV(*(cRObject **)(this + 0x43fa8),(float)uVar32,(float)((ulonglong)uVar32 >> 0x20))
  ;
  pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
  cRBod::SetObject((cRBod *)(this + 0x43f58),pcVar4);
  uVar32 = ObjectProcTileFloorCornerFast(3,*(cRObject **)(this + 0x43f7c),pcVar25);
  cRObject::ApplyUV(*(cRObject **)(this + 0x43f7c),(float)uVar32,(float)((ulonglong)uVar32 >> 0x20))
  ;
  pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
  cRBod::SetObject((cRBod *)(this + 0x43fb0),pcVar4);
  uVar32 = ObjectProcTileFloorCornerFast(0,*(cRObject **)(this + 0x43fd4),pcVar25);
  cRObject::ApplyUV(*(cRObject **)(this + 0x43fd4),(float)uVar32,(float)((ulonglong)uVar32 >> 0x20))
  ;
  pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
  cRBod::SetObject((cRBod *)(this + 0x43fdc),pcVar4);
  uVar32 = ObjectProcTileFloorCornerFast(1,*(cRObject **)(this + 0x44000),pcVar25);
  cRObject::ApplyUV(*(cRObject **)(this + 0x44000),(float)uVar32,(float)((ulonglong)uVar32 >> 0x20))
  ;
  pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
  cRBod::SetObject((cRBod *)(this + 0x44034),pcVar4);
  uVar32 = ObjectProcTileFloorCornerFast(2,*(cRObject **)(this + 0x44058),pcVar25);
  cRObject::ApplyUV(*(cRObject **)(this + 0x44058),(float)uVar32,(float)((ulonglong)uVar32 >> 0x20))
  ;
  pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
  pcVar14 = this + 0x75ac4;
  cRBod::SetObject((cRBod *)(this + 0x44008),pcVar4);
  uVar32 = ObjectProcTileFloorCornerFast(3,*(cRObject **)(this + 0x4402c),pcVar25);
  cRObject::ApplyUV(*(cRObject **)(this + 0x4402c),(float)uVar32,(float)((ulonglong)uVar32 >> 0x20))
  ;
  pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
  pcVar19 = this + 0x718a0;
  cRBod::SetObject((cRBod *)(this + 0x44060),pcVar4);
  uVar32 = ObjectProcTileFloorCornerFast(0,*(cRObject **)(this + 0x44084),pcVar25);
  cRObject::ApplyUV(*(cRObject **)(this + 0x44084),(float)uVar32,(float)((ulonglong)uVar32 >> 0x20))
  ;
  pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
  cRBod::SetObject((cRBod *)(this + 0x4408c),pcVar4);
  uVar32 = ObjectProcTileFloorCornerFast(1,*(cRObject **)(this + 0x440b0),pcVar25);
  cRObject::ApplyUV(*(cRObject **)(this + 0x440b0),(float)uVar32,(float)((ulonglong)uVar32 >> 0x20))
  ;
  pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
  cRBod::SetObject((cRBod *)(this + 0x440e4),pcVar4);
  uVar32 = ObjectProcTileFloorCornerFast(2,*(cRObject **)(this + 0x44108),pcVar25);
  cRObject::ApplyUV(*(cRObject **)(this + 0x44108),(float)uVar32,(float)((ulonglong)uVar32 >> 0x20))
  ;
  pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
  cRBod::SetObject((cRBod *)(this + 0x440b8),pcVar4);
  uVar32 = ObjectProcTileFloorCornerFast(3,*(cRObject **)(this + 0x440dc),pcVar25);
  cRObject::ApplyUV(*(cRObject **)(this + 0x440dc),(float)uVar32,(float)((ulonglong)uVar32 >> 0x20))
  ;
  pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
  cRBod::SetObject((cRBod *)(this + 0x44110),pcVar4);
  pcVar4 = *(cRObject **)(this + 0x44134);
  pcVar22 = (char *)(iVar6 + DAT_00040020);
  *(uint *)pcVar4 = *(uint *)pcVar4 | 0x1000;
  cRDirectX::Load(this_00,pcVar22,pcVar4,1);
  *(undefined4 *)(*(int *)(this + 0x44134) + 8) = 1;
  pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
  fVar31 = (float)cRBod::SetObject((cRBod *)(this + 0x43e24),pcVar4);
  ObjectProcTileFast(*(cRObject **)(this + 0x43e48),(char *)(iVar6 + DAT_00040024),fVar31);
  iVar16 = *(int *)(this + 0x43e48);
  *(undefined4 *)(iVar16 + 8) = 5;
  puVar10 = *(uint **)(*(int *)(iVar16 + 200) + 0xc);
  *puVar10 = *puVar10 | 0x400;
  pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
  cRBod::SetObject((cRBod *)(this + 0x447f0),pcVar4);
  ObjectTextLoad((char *)(iVar6 + DAT_00040028),*(cRObject **)(this + 0x44814));
  iVar16 = 0;
  do {
    iVar23 = iVar16 * 0xa4;
    iVar16 = iVar16 + 1;
    cRBod::SetObject((cRBod *)(this + iVar23 + 0x75a48),*(cRObject **)(this + 0x44814));
    *(cRGame **)pcVar14 = pcVar19;
    puVar10 = *(uint **)(*(int *)(*(int *)(pcVar14 + -0x58) + 200) + 0xc);
    *puVar10 = *puVar10 | 0x400;
    tColourSmall::Set((tColourSmall *)(this + iVar23 + 0x75a70),extraout_s0,extraout_s1,extraout_s2,
                      extraout_s3);
    *(undefined4 *)(*(int *)(pcVar14 + -0x58) + 8) = 5;
    *(uint *)(pcVar14 + -0x78) = *(uint *)(pcVar14 + -0x78) | 0x80;
    pcVar14 = pcVar14 + 0xa4;
  } while (iVar16 != 0x14);
  iVar16 = 0;
  pcVar4 = (cRObject *)cRObjects::Add(*(cRObjects **)(iVar6 + iVar3));
  cRBod::SetObject((cRBod *)(this + 0x47aa4),pcVar4);
  ObjectTextLoad((char *)(iVar6 + DAT_0004002c),*(cRObject **)(this + 0x47ac8));
  pcVar14 = this + 0x3a5f30;
  do {
    iVar23 = iVar16 * 0x84;
    iVar16 = iVar16 + 1;
    cRBod::SetObject((cRBod *)(this + iVar23 + 0x3a5eb0),*(cRObject **)(this + 0x47ac8));
    iVar11 = *(int *)(pcVar14 + -0x5c);
    *(cRGame **)pcVar14 = pcVar19;
    puVar10 = *(uint **)(*(int *)(iVar11 + 200) + 0xc);
    *puVar10 = *puVar10 | 0x400;
    *(undefined4 *)(iVar11 + 8) = 1;
    tMatrix::Identity((tMatrix *)(this + iVar23 + 0x3a5edc));
    pcVar14 = pcVar14 + 0x84;
  } while (iVar16 != 8);
  cRSubTrampRingManager::Init((cRSubTrampRingManager *)(this + 0x3a5eb0));
  iVar23 = 1;
  pcVar14 = this + 0x76794;
  pcVar4 = (cRObject *)cRObjects::Add(*(cRObjects **)(iVar6 + iVar3));
  cRBod::SetObject((cRBod *)(this + 0x47a78),pcVar4);
  pcVar4 = *(cRObject **)(this + 0x47a9c);
  pcVar22 = (char *)(iVar6 + DAT_00040030);
  *(uint *)pcVar4 = *(uint *)pcVar4 | 0x1000;
  cRDirectX::Load(this_00,pcVar22,pcVar4,1);
  iVar16 = 0;
  do {
    iVar11 = iVar16 * 0x8c;
    iVar16 = iVar16 + 1;
    cRBod::SetObject((cRBod *)(this + iVar11 + 0x76718),*(cRObject **)(this + 0x47a9c));
    *(cRGame **)pcVar14 = pcVar19;
    tColourSmall::Set((tColourSmall *)(this + iVar11 + 0x76740),extraout_s0_00,extraout_s1_00,
                      extraout_s2_00,extraout_s3_00);
    pcVar1 = pcVar14 + -0x58;
    pcVar14 = pcVar14 + 0x8c;
    *(undefined4 *)(*(int *)pcVar1 + 8) = 1;
    tMatrix::Identity((tMatrix *)((tColourSmall *)(this + iVar11 + 0x76740) + 4));
    uVar9 = DAT_00040048;
    uVar5 = DAT_00040044;
  } while (iVar16 != 0x28);
  pcVar14 = this + 0x77d10;
  pcVar22 = (char *)(iVar6 + DAT_00040034);
  pcVar18 = *(cRObjects **)(iVar6 + iVar3);
  iVar16 = 0;
  do {
    pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
    cRBod::SetObject((cRBod *)(this + iVar16 * 0x54 + 0x77cf8),pcVar4);
    if (iVar16 == 0) {
      pcVar4 = *(cRObject **)(this + 0x77d1c);
      *(uint *)pcVar4 = *(uint *)pcVar4 | 0x1000;
      cRDirectX::Load(this_00,pcVar22,pcVar4,1);
      *(undefined4 *)pcVar14 = uVar5;
      *(undefined4 *)(pcVar14 + -4) = uVar5;
      *(undefined4 *)(pcVar14 + -8) = uVar5;
      *(cRGame **)(pcVar14 + 0x24) = pcVar19;
      *(undefined4 *)(pcVar14 + 0x34) = uVar5;
      *(undefined4 *)(pcVar14 + 0x14) = 0;
      *(undefined4 *)(pcVar14 + 0x38) = uVar9;
    }
    else {
      pcVar4 = *(cRObject **)(this + 0x77d70);
      *(uint *)pcVar4 = *(uint *)pcVar4 | 0x1000;
      cRDirectX::Load(this_00,pcVar22,pcVar4,1);
      *(undefined4 *)pcVar14 = uVar5;
      *(undefined4 *)(pcVar14 + -4) = uVar5;
      *(undefined4 *)(pcVar14 + -8) = uVar5;
      *(cRGame **)(pcVar14 + 0x24) = pcVar19;
      *(int *)(pcVar14 + 0x14) = iVar16;
      *(undefined4 *)(pcVar14 + 0x34) = uVar5;
      *(undefined4 *)(pcVar14 + 0x38) = uVar9;
      if (1 < iVar23) {
        pcVar15 = (cRBod *)(this + 0x744bc);
        this_01 = (cLinkedList<cRBod> *)(this + 0x358);
        cLinkedList<cRBod>::Add(this_01,(cRBod *)(this + 0x7456c));
        cLinkedList<cRBod>::Add(this_01,pcVar15);
        cLinkedList<cRBod>::Add(this_01,(cRBod *)(this + 0x744e8));
        cLinkedList<cRBod>::Add(this_01,(cRBod *)(this + 0x74514));
        cLinkedList<cRBod>::AddAfter(this_01,(cRBod *)(this + 0x74540),pcVar15);
        cLinkedList<cRBod>::AddAfter(this_01,(cRBod *)(this + 0x74598),pcVar15);
        cLinkedList<cRBod>::AddAfter(this_01,(cRBod *)(this + 0x74674),pcVar15);
        cLinkedList<cRBod>::AddAfter(this_01,(cRBod *)(this + 0x74490),pcVar15);
        cLinkedList<cRBod>::AddAfter(this_01,(cRBod *)(this + 0x7461c),pcVar15);
        cLinkedList<cRBod>::AddAfter(this_01,(cRBod *)(this + 0x74648),pcVar15);
        cLinkedList<cRBod>::AddAfter(this_01,(cRBod *)(this + 0x745c4),pcVar15);
        cLinkedList<cRBod>::AddAfter(this_01,(cRBod *)(this + 0x745f0),pcVar15);
        pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
        cRBod::SetObject((cRBod *)(this + 0x83ca4),pcVar4);
        pcVar22 = (char *)Rstrfind((char *)(iVar6 + DAT_00040038),*(char **)(this + 0x47ad0));
        if (pcVar22 == (char *)0x0) {
          Rstrcpy(local_bc,(char *)(iVar6 + DAT_00041800));
        }
        else {
          iVar16 = Rstrfind((char *)(iVar6 + DAT_0004003c),pcVar22);
          cVar7 = *(char *)(iVar16 + 1);
          if (cVar7 == '.') {
            pcVar22 = local_bc;
          }
          else {
            pcVar22 = local_bc;
            do {
              pcVar22 = pcVar22 + 1;
              pcVar22[-1] = cVar7;
              cVar7 = *(char *)(iVar16 + 2);
              iVar16 = iVar16 + 1;
            } while (cVar7 != '.');
          }
          *pcVar22 = '.';
          pcVar22[1] = 'x';
          pcVar22[2] = '\0';
        }
        cRDirectX::LoadAnim(this_00,local_bc,*(cRObject **)(this + 0x83cc8));
        uVar5 = DAT_00040a34;
        pcVar18 = *(cRObjects **)(iVar6 + iVar3);
        pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
        cRBod::SetObject((cRBod *)(this + 0x83b64),pcVar4);
        iVar16 = 0;
        cRDirectX::LoadAnim(this_00,local_bc,*(cRObject **)(this + 0x83b88));
        pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
        cRBod::SetObject((cRBod *)(this + 0x83d18),pcVar4);
        cRDirectX::LoadAnim(this_00,(char *)(iVar6 + DAT_00040a38),*(cRObject **)(this + 0x83d3c));
        pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
        cRBod::SetObject((cRBod *)(this + 0x83d8c),pcVar4);
        cRDirectX::LoadAnim(this_00,(char *)(iVar6 + DAT_00040a3c),*(cRObject **)(this + 0x83db0));
        pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
        cRBod::SetObject((cRBod *)(this + 0x83e00),pcVar4);
        cRDirectX::LoadAnim(this_00,(char *)(iVar6 + DAT_00040a40),*(cRObject **)(this + 0x83e24));
        pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
        cRBod::SetObject((cRBod *)(this + 0x83e74),pcVar4);
        cRDirectX::LoadAnim(this_00,(char *)(iVar6 + DAT_00040a44),*(cRObject **)(this + 0x83e98));
        pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
        cRBod::SetObject((cRBod *)(this + 0x83ee8),pcVar4);
        cRDirectX::LoadAnim(this_00,(char *)(iVar6 + DAT_00040a48),*(cRObject **)(this + 0x83f0c));
        pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
        cRBod::SetObject((cRBod *)(this + 0x83f5c),pcVar4);
        cRDirectX::LoadAnim(this_00,(char *)(iVar6 + DAT_00040a4c),*(cRObject **)(this + 0x83f80));
        pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
        cRBod::SetObject((cRBod *)(this + 0x83fd0),pcVar4);
        cRDirectX::LoadAnim(this_00,(char *)(iVar6 + DAT_00040a50),*(cRObject **)(this + 0x83ff4));
        pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
        cRBod::SetObject((cRBod *)(this + 0x84044),pcVar4);
        cRDirectX::LoadAnim(this_00,(char *)(iVar6 + DAT_00040a54),*(cRObject **)(this + 0x84068));
        pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
        cRBod::SetObject((cRBod *)(this + 0x840b8),pcVar4);
        cRDirectX::LoadAnim(this_00,(char *)(iVar6 + DAT_00040a58),*(cRObject **)(this + 0x840dc));
        pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
        cRBod::SetObject((cRBod *)(this + 0x85000),pcVar4);
        cRDirectX::Load(this_00,(char *)(iVar6 + DAT_00040a5c),*(cRObject **)(this + 0x85024),2);
        **(uint **)(this + 0x85024) = **(uint **)(this + 0x85024) | 0x8000000;
        cRSnail::ExtractHotSpots((cRSnail *)(this + 0x83b64));
        pcVar14 = this + 0x83cc8;
        do {
          pcVar4 = *(cRObject **)pcVar14;
          iVar16 = iVar16 + 1;
          *(uint *)pcVar4 = *(uint *)pcVar4 | 4;
          cRObject::ApplyToon(pcVar4,0);
          iVar23 = *(int *)pcVar14;
          *(undefined4 *)(iVar23 + 0xf8) = uVar5;
          *(undefined4 *)(iVar23 + 0xf0) = uVar5;
          *(undefined4 *)(iVar23 + 0xf4) = uVar5;
          pcVar14 = pcVar14 + 0x74;
        } while (iVar16 != 10);
        iVar11 = 0;
        pcVar4 = *(cRObject **)(this + 0x83b88);
        *(uint *)pcVar4 = *(uint *)pcVar4 | 4;
        cRObject::ApplyToon(pcVar4,0);
        iVar16 = *(int *)(this + 0x83b88);
        *(undefined4 *)(iVar16 + 0xf8) = uVar5;
        *(undefined4 *)(iVar16 + 0xf0) = uVar5;
        *(undefined4 *)(iVar16 + 0xf4) = uVar5;
        iVar16 = DAT_00040a60;
        pcVar18 = *(cRObjects **)(iVar6 + iVar3);
        pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
        cRBod::SetObject((cRBod *)(this + 0x84be8),pcVar4);
        cRDirectX::LoadAnim(this_00,(char *)(iVar6 + iVar16),*(cRObject **)(this + 0x84c0c));
        pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
        cRBod::SetObject((cRBod *)(this + 0x84d2c),pcVar4);
        cRDirectX::LoadAnim(this_00,(char *)(iVar6 + iVar16),*(cRObject **)(this + 0x84d50));
        pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
        cRBod::SetObject((cRBod *)(this + 0x84da0),pcVar4);
        cRDirectX::LoadAnim(this_00,(char *)(iVar6 + DAT_00040a64),*(cRObject **)(this + 0x84dc4));
        pcVar4 = *(cRObject **)(this + 0x84d50);
        *(uint *)pcVar4 = *(uint *)pcVar4 | 4;
        cRObject::ApplyToon(pcVar4,0);
        pcVar4 = *(cRObject **)(this + 0x84dc4);
        iVar16 = *(int *)(this + 0x84d50);
        *(undefined4 *)(iVar16 + 0xf8) = uVar5;
        *(undefined4 *)(iVar16 + 0xf0) = uVar5;
        uVar8 = *(uint *)pcVar4;
        *(undefined4 *)(iVar16 + 0xf4) = uVar5;
        iVar16 = DAT_00040a68;
        *(uint *)pcVar4 = uVar8 | 4;
        cRObject::ApplyToon(pcVar4,0);
        pcVar4 = *(cRObject **)(this + 0x84c0c);
        iVar23 = *(int *)(this + 0x84dc4);
        *(undefined4 *)(iVar23 + 0xf8) = uVar5;
        *(undefined4 *)(iVar23 + 0xf0) = uVar5;
        uVar8 = *(uint *)pcVar4;
        *(undefined4 *)(iVar23 + 0xf4) = uVar5;
        *(uint *)pcVar4 = uVar8 | 4;
        cRObject::ApplyToon(pcVar4,0);
        iVar23 = *(int *)(this + 0x84c0c);
        *(undefined4 *)(iVar23 + 0xf8) = uVar5;
        *(undefined4 *)(iVar23 + 0xf0) = uVar5;
        *(undefined4 *)(iVar23 + 0xf4) = uVar5;
        pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
        cRBod::SetObject((cRBod *)(this + 0x8412c),pcVar4);
        cRDirectX::LoadAnim(this_00,(char *)(iVar6 + iVar16),*(cRObject **)(this + 0x84150));
        pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
        cRBod::SetObject((cRBod *)(this + 0x84270),pcVar4);
        cRDirectX::LoadAnim(this_00,(char *)(iVar6 + iVar16),*(cRObject **)(this + 0x84294));
        pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
        cRBod::SetObject((cRBod *)(this + 0x842e4),pcVar4);
        cRDirectX::LoadAnim(this_00,(char *)(iVar6 + DAT_00040a6c),*(cRObject **)(this + 0x84308));
        pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
        cRBod::SetObject((cRBod *)(this + 0x84358),pcVar4);
        cRDirectX::LoadAnim(this_00,(char *)(iVar6 + DAT_00040a70),*(cRObject **)(this + 0x8437c));
        pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
        cRBod::SetObject((cRBod *)(this + 0x843cc),pcVar4);
        cRDirectX::LoadAnim(this_00,(char *)(iVar6 + DAT_00040a74),*(cRObject **)(this + 0x843f0));
        pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
        cRBod::SetObject((cRBod *)(this + 0x84440),pcVar4);
        cRDirectX::LoadAnim(this_00,(char *)(iVar6 + DAT_00040a78),*(cRObject **)(this + 0x84464));
        pcVar14 = this + 0x84294;
        do {
          pcVar4 = *(cRObject **)pcVar14;
          iVar11 = iVar11 + 1;
          *(uint *)pcVar4 = *(uint *)pcVar4 | 4;
          cRObject::ApplyToon(pcVar4,0);
          iVar16 = *(int *)pcVar14;
          *(undefined4 *)(iVar16 + 0xf8) = uVar5;
          *(undefined4 *)(iVar16 + 0xf0) = uVar5;
          *(undefined4 *)(iVar16 + 0xf4) = uVar5;
          pcVar14 = pcVar14 + 0x74;
        } while (iVar11 != 5);
        iVar23 = 0;
        pcVar4 = *(cRObject **)(this + 0x84150);
        *(uint *)pcVar4 = *(uint *)pcVar4 | 4;
        cRObject::ApplyToon(pcVar4,0);
        iVar16 = *(int *)(this + 0x84150);
        *(undefined4 *)(iVar16 + 0xf8) = uVar5;
        *(undefined4 *)(iVar16 + 0xf0) = uVar5;
        *(undefined4 *)(iVar16 + 0xf4) = uVar5;
        iVar16 = DAT_00040a7c;
        pcVar18 = *(cRObjects **)(iVar6 + iVar3);
        pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
        cRBod::SetObject((cRBod *)(this + 0x844c0),pcVar4);
        cRDirectX::LoadAnim(this_00,(char *)(iVar6 + iVar16),*(cRObject **)(this + 0x844e4));
        pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
        cRBod::SetObject((cRBod *)(this + 0x84604),pcVar4);
        cRDirectX::LoadAnim(this_00,(char *)(iVar6 + iVar16),*(cRObject **)(this + 0x84628));
        pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
        cRBod::SetObject((cRBod *)(this + 0x84678),pcVar4);
        cRDirectX::LoadAnim(this_00,(char *)(iVar6 + DAT_00040a80),*(cRObject **)(this + 0x8469c));
        pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
        cRBod::SetObject((cRBod *)(this + 0x846ec),pcVar4);
        cRDirectX::LoadAnim(this_00,(char *)(iVar6 + DAT_00040a84),*(cRObject **)(this + 0x84710));
        pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
        cRBod::SetObject((cRBod *)(this + 0x84760),pcVar4);
        cRDirectX::LoadAnim(this_00,(char *)(iVar6 + DAT_00040a88),*(cRObject **)(this + 0x84784));
        pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
        cRBod::SetObject((cRBod *)(this + 0x847d4),pcVar4);
        cRDirectX::LoadAnim(this_00,(char *)(iVar6 + DAT_00040a8c),*(cRObject **)(this + 0x847f8));
        pcVar14 = this + 0x84628;
        do {
          pcVar4 = *(cRObject **)pcVar14;
          iVar23 = iVar23 + 1;
          *(uint *)pcVar4 = *(uint *)pcVar4 | 4;
          cRObject::ApplyToon(pcVar4,0);
          iVar16 = *(int *)pcVar14;
          *(undefined4 *)(iVar16 + 0xf8) = uVar5;
          *(undefined4 *)(iVar16 + 0xf0) = uVar5;
          *(undefined4 *)(iVar16 + 0xf4) = uVar5;
          pcVar14 = pcVar14 + 0x74;
        } while (iVar23 != 5);
        iVar23 = 0;
        pcVar4 = *(cRObject **)(this + 0x844e4);
        *(uint *)pcVar4 = *(uint *)pcVar4 | 4;
        cRObject::ApplyToon(pcVar4,0);
        iVar16 = *(int *)(this + 0x844e4);
        *(undefined4 *)(iVar16 + 0xf8) = uVar5;
        *(undefined4 *)(iVar16 + 0xf0) = uVar5;
        *(undefined4 *)(iVar16 + 0xf4) = uVar5;
        iVar16 = DAT_00040a90;
        pcVar18 = *(cRObjects **)(iVar6 + iVar3);
        pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
        cRBod::SetObject((cRBod *)(this + 0x84854),pcVar4);
        cRDirectX::LoadAnim(this_00,(char *)(iVar6 + iVar16),*(cRObject **)(this + 0x84878));
        pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
        cRBod::SetObject((cRBod *)(this + 0x84998),pcVar4);
        cRDirectX::LoadAnim(this_00,(char *)(iVar6 + iVar16),*(cRObject **)(this + 0x849bc));
        pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
        cRBod::SetObject((cRBod *)(this + 0x84a0c),pcVar4);
        cRDirectX::LoadAnim(this_00,(char *)(iVar6 + DAT_00040a94),*(cRObject **)(this + 0x84a30));
        pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
        cRBod::SetObject((cRBod *)(this + 0x84a80),pcVar4);
        cRDirectX::LoadAnim(this_00,(char *)(iVar6 + DAT_00040a98),*(cRObject **)(this + 0x84aa4));
        pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
        cRBod::SetObject((cRBod *)(this + 0x84af4),pcVar4);
        cRDirectX::LoadAnim(this_00,(char *)(iVar6 + DAT_00040a9c),*(cRObject **)(this + 0x84b18));
        pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
        cRBod::SetObject((cRBod *)(this + 0x84b68),pcVar4);
        cRDirectX::LoadAnim(this_00,(char *)(iVar6 + DAT_00040aa0),*(cRObject **)(this + 0x84b8c));
        pcVar14 = this + 0x849bc;
        do {
          pcVar4 = *(cRObject **)pcVar14;
          iVar23 = iVar23 + 1;
          *(uint *)pcVar4 = *(uint *)pcVar4 | 4;
          cRObject::ApplyToon(pcVar4,0);
          iVar16 = *(int *)pcVar14;
          *(undefined4 *)(iVar16 + 0xf8) = uVar5;
          *(undefined4 *)(iVar16 + 0xf0) = uVar5;
          *(undefined4 *)(iVar16 + 0xf4) = uVar5;
          iVar16 = DAT_00040aa4;
          pcVar14 = pcVar14 + 0x74;
        } while (iVar23 != 5);
        pcVar4 = *(cRObject **)(this + 0x84878);
        *(uint *)pcVar4 = *(uint *)pcVar4 | 4;
        cRObject::ApplyToon(pcVar4,0);
        iVar23 = DAT_00040aa8;
        iVar11 = *(int *)(this + 0x84878);
        *(undefined4 *)(iVar11 + 0xf8) = uVar5;
        pcVar21 = *(cRTextures **)(iVar6 + iVar16);
        *(undefined4 *)(iVar11 + 0xf0) = uVar5;
        *(undefined4 *)(iVar11 + 0xf4) = uVar5;
        uVar5 = cRTextures::Add(pcVar21,(char *)(iVar6 + iVar23),(cTgaHeader *)0x0,0);
        iVar23 = 0;
        pcVar22 = (char *)(iVar6 + DAT_00040aac);
        *(undefined4 *)(this + 0x852d8) = uVar5;
        uVar5 = cRTextures::Add(pcVar21,pcVar22,(cTgaHeader *)0x0,0);
        pcVar22 = (char *)(iVar6 + DAT_00040ab0);
        *(undefined4 *)(this + 0x852dc) = uVar5;
        uVar5 = cRTextures::Add(pcVar21,pcVar22,(cTgaHeader *)0x0,0);
        pcVar18 = *(cRObjects **)(iVar6 + iVar3);
        *(undefined4 *)(this + 0x852e0) = uVar5;
        pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
        cRBod::SetObject((cRBod *)(this + 0x8523c),pcVar4);
        cRDirectX::Load(this_00,(char *)(iVar6 + DAT_00040ab4),*(cRObject **)(this + 0x85260),1);
        puVar10 = *(uint **)(this + 0x85260);
        puVar10[2] = 1;
        *puVar10 = *puVar10 | 0x100000;
        pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
        cRBod::SetObject((cRBod *)(this + 0x818b0),pcVar4);
        iVar3 = DAT_00040abc;
        cRDirectX::Load(this_00,(char *)(iVar6 + DAT_00040ab8),*(cRObject **)(this + 0x818d4),1);
        pcVar14 = this + 0x81848;
        do {
          iVar11 = iVar23 * 0x2c8;
          pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
          iVar23 = iVar23 + 1;
          cRBod::SetObject((cRBod *)(this + iVar11 + 0x81824),pcVar4);
          pcVar4 = *(cRObject **)pcVar14;
          *(undefined4 *)(pcVar4 + 8) = 1;
          *(uint *)pcVar4 = *(uint *)pcVar4 | 0x100004;
          fVar31 = (float)ObjectTextLoad((char *)(iVar6 + iVar3),pcVar4);
          cRVapour::Init((cRVapour *)(this + iVar11 + 0x81824),*(cRObject **)pcVar14,fVar31);
          cRBod::SetObject((cRBod *)(this + iVar11 + 0x818b0),*(cRObject **)(this + 0x818d4));
          pcVar14 = pcVar14 + 0x2c8;
        } while (iVar23 != 0xc);
        pcVar21 = *(cRTextures **)(iVar6 + iVar16);
        pcVar25 = (char *)(iVar6 + iVar20);
        puVar10 = (uint *)cRTextures::Add(pcVar21,(char *)(iVar6 + DAT_00040ac0),(cTgaHeader *)0x0,0
                                         );
        pcVar22 = (char *)(iVar6 + DAT_00040ac4);
        *puVar10 = *puVar10 | 0x400;
        puVar10 = (uint *)cRTextures::Add(pcVar21,pcVar22,(cTgaHeader *)0x0,0);
        *puVar10 = *puVar10 | 0x1403;
        puVar10 = (uint *)cRTextures::Add(pcVar21,pcVar25,(cTgaHeader *)0x0,0);
        local_124 = 0x3a;
        *puVar10 = *puVar10 | 0x1400;
        puVar10 = (uint *)cRTextures::Add(pcVar21,(char *)(iVar6 + iVar17),(cTgaHeader *)0x0,0);
        local_138 = 0;
        *puVar10 = *puVar10 | 0x1000;
        *(undefined4 *)(this + 0xbcc) = 0xffffffff;
        puVar10 = (uint *)cRTextures::Add(pcVar21,pcVar25,(cTgaHeader *)0x0,0);
        puVar24 = (undefined4 *)(iVar6 + DAT_00040ac8);
        puVar26 = (undefined4 *)(iVar6 + DAT_00040acc);
        uVar8 = *puVar10;
        *(uint **)(this + 0x848) = puVar10;
        *puVar10 = uVar8 | 0x1000;
        uVar5 = *(undefined4 *)(pcVar25 + 4);
        uVar9 = *(undefined4 *)(pcVar25 + 8);
        uVar12 = *(undefined4 *)(pcVar25 + 0xc);
        puVar27 = (undefined4 *)(iVar6 + DAT_00040ad0);
        *(undefined4 *)(this + 0x84c) = *(undefined4 *)pcVar25;
        *(undefined4 *)(this + 0x850) = uVar5;
        *(undefined4 *)(this + 0x854) = uVar9;
        *(undefined4 *)(this + 0x858) = uVar12;
        puVar13 = (undefined4 *)(iVar6 + DAT_00040ad4);
        uVar5 = *(undefined4 *)(pcVar25 + 0x14);
        uVar9 = *(undefined4 *)(pcVar25 + 0x18);
        uVar12 = *(undefined4 *)(pcVar25 + 0x1c);
        puVar28 = (undefined4 *)(iVar6 + DAT_00040ad8);
        *(undefined4 *)(this + 0x85c) = *(undefined4 *)(pcVar25 + 0x10);
        *(undefined4 *)(this + 0x860) = uVar5;
        *(undefined4 *)(this + 0x864) = uVar9;
        this[0x868] = SUB41(uVar12,0);
        uVar5 = puVar24[1];
        uVar9 = puVar24[2];
        uVar12 = puVar24[3];
        puVar29 = (undefined4 *)(iVar6 + DAT_00040adc);
        *(undefined4 *)(this + 0x8cc) = *puVar24;
        *(undefined4 *)(this + 0x8d0) = uVar5;
        *(undefined4 *)(this + 0x8d4) = uVar9;
        *(undefined4 *)(this + 0x8d8) = uVar12;
        iVar3 = DAT_00040ae0;
        uVar5 = puVar24[5];
        uVar9 = puVar24[6];
        uVar12 = puVar24[7];
        *(undefined4 *)(this + 0x8dc) = puVar24[4];
        *(undefined4 *)(this + 0x8e0) = uVar5;
        *(undefined4 *)(this + 0x8e4) = uVar9;
        this[0x8e8] = SUB41(uVar12,0);
        uVar5 = puVar26[1];
        uVar9 = puVar26[2];
        uVar12 = puVar26[3];
        *(undefined4 *)(this + 0x94c) = *puVar26;
        *(undefined4 *)(this + 0x950) = uVar5;
        *(undefined4 *)(this + 0x954) = uVar9;
        *(undefined4 *)(this + 0x958) = uVar12;
        uVar5 = puVar26[5];
        uVar9 = puVar26[6];
        uVar12 = puVar26[7];
        *(undefined4 *)(this + 0x95c) = puVar26[4];
        *(undefined4 *)(this + 0x960) = uVar5;
        *(undefined4 *)(this + 0x964) = uVar9;
        this[0x968] = SUB41(uVar12,0);
        uVar5 = puVar13[1];
        uVar9 = puVar13[2];
        uVar12 = puVar13[3];
        *(undefined4 *)(this + 0x9cc) = *puVar13;
        *(undefined4 *)(this + 0x9d0) = uVar5;
        *(undefined4 *)(this + 0x9d4) = uVar9;
        *(undefined4 *)(this + 0x9d8) = uVar12;
        uVar5 = puVar13[5];
        uVar9 = puVar13[6];
        uVar12 = puVar13[7];
        *(undefined4 *)(this + 0x9dc) = puVar13[4];
        *(undefined4 *)(this + 0x9e0) = uVar5;
        *(undefined4 *)(this + 0x9e4) = uVar9;
        this[0x9e8] = SUB41(uVar12,0);
        uVar5 = puVar27[1];
        uVar9 = puVar27[2];
        uVar12 = puVar27[3];
        *(undefined4 *)(this + 0xa4c) = *puVar27;
        *(undefined4 *)(this + 0xa50) = uVar5;
        *(undefined4 *)(this + 0xa54) = uVar9;
        *(undefined4 *)(this + 0xa58) = uVar12;
        uVar5 = puVar27[5];
        uVar9 = puVar27[6];
        uVar12 = puVar27[7];
        *(undefined4 *)(this + 0xa5c) = puVar27[4];
        *(undefined4 *)(this + 0xa60) = uVar5;
        *(undefined4 *)(this + 0xa64) = uVar9;
        this[0xa68] = SUB41(uVar12,0);
        uVar5 = puVar28[1];
        uVar9 = puVar28[2];
        uVar12 = puVar28[3];
        *(undefined4 *)(this + 0xacc) = *puVar28;
        *(undefined4 *)(this + 0xad0) = uVar5;
        *(undefined4 *)(this + 0xad4) = uVar9;
        *(undefined4 *)(this + 0xad8) = uVar12;
        uVar5 = puVar28[5];
        uVar9 = puVar28[6];
        uVar12 = puVar28[7];
        *(undefined4 *)(this + 0xadc) = puVar28[4];
        *(undefined4 *)(this + 0xae0) = uVar5;
        *(undefined4 *)(this + 0xae4) = uVar9;
        this[0xae8] = SUB41(uVar12,0);
        uVar5 = puVar29[1];
        uVar9 = puVar29[2];
        uVar12 = puVar29[3];
        *(undefined4 *)(this + 0xb4c) = *puVar29;
        *(undefined4 *)(this + 0xb50) = uVar5;
        *(undefined4 *)(this + 0xb54) = uVar9;
        *(undefined4 *)(this + 0xb58) = uVar12;
        uVar5 = puVar29[5];
        uVar9 = puVar29[6];
        uVar12 = puVar29[7];
        *(undefined4 *)(this + 0xb5c) = puVar29[4];
        *(undefined4 *)(this + 0xb60) = uVar5;
        *(undefined4 *)(this + 0xb64) = uVar9;
        this[0xb68] = SUB41(uVar12,0);
        pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
        cRBod::SetObject((cRBod *)(this + 0x3873c4),pcVar4);
        ObjectTextLoad((char *)(iVar6 + DAT_00040ae4),*(cRObject **)(this + 0x3873e8));
        uVar5 = DAT_000417dc;
        *(undefined4 *)(this + 0x3873d4) = DAT_000417dc;
        *(undefined4 *)(this + 0x3873dc) = uVar5;
        *(undefined4 *)(this + 0x3873d8) = uVar5;
        tColourSmall::Set((tColourSmall *)(this + 0x3873ec),extraout_s0_01,extraout_s1_01,
                          extraout_s2_01,extraout_s3_01);
        *(undefined4 *)(*(int *)(this + 0x3873e8) + 8) = 3;
        cRWorld::Init((cRWorld *)(this + 0x81290),0xe10,0x38,0x38,8);
        do {
          iVar20 = 0;
          local_12c = local_124;
          do {
            iVar23 = -1;
            iVar17 = local_12c;
            do {
              iVar11 = 0;
              pcVar14 = this + iVar17 * 0x2c + 0x43e24;
              do {
                pcVar4 = (cRObject *)cRObjects::Add(pcVar18);
                cRBod::SetObject((cRBod *)(this + (iVar11 + iVar17) * 0x2c + 0x43e24),pcVar4);
                iVar30 = iVar11 + -1;
                iVar11 = iVar11 + 1;
                ObjectProcFringe(*(cRObject **)(pcVar14 + 0x24),local_138,iVar20,iVar23,iVar30,
                                 (char *)(iVar6 + iVar3));
                pcVar19 = pcVar14 + 0x24;
                pcVar14 = pcVar14 + 0x2c;
                *(undefined4 *)(*(int *)pcVar19 + 8) = 5;
              } while (iVar11 != 3);
              iVar23 = iVar23 + 1;
              iVar17 = iVar17 + 3;
            } while (iVar23 != 2);
            iVar20 = iVar20 + 1;
            local_12c = local_12c + 9;
          } while (iVar20 != 4);
          local_138 = local_138 + 1;
          local_124 = local_124 + 0x24;
        } while (local_138 != 8);
        puVar10 = (uint *)cRTextures::Add(*(cRTextures **)(iVar6 + iVar16),(char *)(iVar6 + iVar3),
                                          (cTgaHeader *)0x0,0);
        *puVar10 = *puVar10 | 0x400;
        cLinkedList<cRBod>::Add(this_01,(cRBod *)(this + 0x68));
        *(undefined4 *)(this + 0x94) = 0;
        cRInput::Init((cRInput *)(this + 0x94));
        if (local_3c != **(int **)(iVar6 + iVar2)) {
                    /* WARNING: Subroutine does not return */
          __stack_chk_fail();
        }
        return;
      }
    }
    iVar16 = iVar16 + 1;
    iVar23 = iVar23 + 1;
    pcVar14 = pcVar14 + 0x54;
  } while( true );
}
