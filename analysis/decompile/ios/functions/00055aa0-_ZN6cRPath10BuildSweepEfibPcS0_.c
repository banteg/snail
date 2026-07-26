/*
 * mangled: _ZN6cRPath10BuildSweepEfibPcS0_
 * demangled: cRPath::BuildSweep(float, int, bool, char*, char*)
 * address: 00055aa0
 * size: 2320
 */

/* cRPath::BuildSweep(float, int, bool, char*, char*) */

void cRPath::BuildSweep(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  char *pcVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint in_fpscr;
  float fVar7;
  undefined1 *puVar8;
  float fVar9;
  float fVar10;
  int local_2c;

  *(undefined4 *)((int)param_1 + 0x2c) = 0x20;
  *(undefined4 *)((int)param_1 + 0x44) = 0x3f800000;
  *(undefined4 *)((int)param_1 + 0x38) = 0x1e;
  *(uint *)((int)param_1 + 0x48) = (uint)param_3;
  *(undefined4 *)((int)param_1 + 0x40) = 0x41f00000;
  *(undefined1 *)((int)param_1 + 0x30) = 0;
  *(undefined4 *)((int)param_1 + 0x34) = 0;
  uVar2 = RShellMemoryMalloc(0x13b0,"Path Tile Nodes");
  *(undefined4 *)((int)param_1 + 0x4c) = uVar2;
  uVar2 = RShellMemoryMalloc(*(int *)((int)param_1 + 0x38) * 0xa8,"Path Ball nodes");
  *(undefined4 *)((int)param_1 + 0x50) = uVar2;
  if (0 < *(int *)((int)param_1 + 0x38)) {
    iVar4 = 0;
    iVar3 = 0;
    do {
      iVar4 = iVar4 + 1;
      *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar3 + 0xa0) = 0;
      iVar5 = *(int *)((int)param_1 + 0x4c) + iVar3;
      iVar3 = iVar3 + 0xa8;
      *(undefined4 *)(iVar5 + 0x9c) = 0x3f800000;
    } while (iVar4 < *(int *)((int)param_1 + 0x38));
  }
  *(undefined1 *)((int)param_1 + 0x84) = 0;
  puVar8 = &DAT_40800000;
  fVar9 = 0.5;
  fVar7 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                     (byte)(in_fpscr >> 0x16) & 3);
  *(float *)(*(int *)((int)param_1 + 0x4c) + 0x90) = fVar7 * 0.5 - 4.0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x98) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x94) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0xa0) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x9c) = 0x3f800000;
  tMatrix::Identity(*(tMatrix **)((int)param_1 + 0x4c));
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x30) =
       *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x90);
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x34) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x38) = 0;
  tMatrix::Identity(*(tMatrix **)((int)param_1 + 0x50));
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x30) =
       *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x90);
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x34) = 0x3efae148;
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x38) = 0;
  fVar7 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                     (byte)(in_fpscr >> 0x16) & 3);
  *(float *)(*(int *)((int)param_1 + 0x4c) + 0x138) = fVar7 * fVar9 - (float)puVar8;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x140) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x13c) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x148) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x144) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(*(int *)((int)param_1 + 0x4c) + 0xa8));
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0xd8) =
       *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x138);
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0xdc) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0xe0) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(*(int *)((int)param_1 + 0x50) + 0xa8));
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0xd8) =
       *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x138);
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0xdc) = 0x3efae148;
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0xe0) = 0x3f800000;
  fVar7 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                     (byte)(in_fpscr >> 0x16) & 3);
  fVar10 = -0.5;
  *(float *)(*(int *)((int)param_1 + 0x4c) + 0x1e0) = fVar7 * fVar9 - (float)puVar8;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x1e8) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x1e4) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x1f0) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x1ec) = 0x3f800000;
  tMatrix::Identity((tMatrix *)(*(int *)((int)param_1 + 0x4c) + 0x150));
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x180) =
       *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x1e0);
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x184) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x188) = 0x40000000;
  tMatrix::Identity((tMatrix *)(*(int *)((int)param_1 + 0x50) + 0x150));
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x180) =
       *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x1e0);
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x184) = 0x3efae148;
  *(undefined4 *)(*(int *)((int)param_1 + 0x50) + 0x188) = 0x40000000;
  fVar7 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                     (byte)(in_fpscr >> 0x16) & 3);
  *(float *)(segment_command_00001224.segname + *(int *)((int)param_1 + 0x4c) + 0x1c) =
       (float)puVar8 + fVar7 * fVar10;
  pcVar1 = segment_command_00001224.segname + *(int *)((int)param_1 + 0x4c) + 0x24;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  pcVar1 = segment_command_00001224.segname + *(int *)((int)param_1 + 0x4c) + 0x20;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  pcVar1 = segment_command_00001224.segname + *(int *)((int)param_1 + 0x4c) + 0x2c;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  pcVar1 = segment_command_00001224.segname + *(int *)((int)param_1 + 0x4c) + 0x28;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = -0x80;
  pcVar1[3] = '?';
  tMatrix::Identity((tMatrix *)(section_0000119c.segname + *(int *)((int)param_1 + 0x4c) + 0xc));
  *(undefined4 *)(section_000011e0.sectname + *(int *)((int)param_1 + 0x4c) + 8) =
       *(undefined4 *)(segment_command_00001224.segname + *(int *)((int)param_1 + 0x4c) + 0x1c);
  pcVar1 = section_000011e0.sectname + *(int *)((int)param_1 + 0x4c) + 0xc;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  pcVar1 = section_000011e0.segname + *(int *)((int)param_1 + 0x4c);
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = -0x28;
  pcVar1[3] = 'A';
  tMatrix::Identity((tMatrix *)(section_0000119c.segname + *(int *)((int)param_1 + 0x50) + 0xc));
  *(undefined4 *)(section_000011e0.sectname + *(int *)((int)param_1 + 0x50) + 8) =
       *(undefined4 *)(segment_command_00001224.segname + *(int *)((int)param_1 + 0x4c) + 0x1c);
  pcVar1 = section_000011e0.sectname + *(int *)((int)param_1 + 0x50) + 0xc;
  pcVar1[0] = 'H';
  pcVar1[1] = -0x1f;
  pcVar1[2] = -6;
  pcVar1[3] = '>';
  pcVar1 = section_000011e0.segname + *(int *)((int)param_1 + 0x50);
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = -0x28;
  pcVar1[3] = 'A';
  fVar7 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                     (byte)(in_fpscr >> 0x16) & 3);
  *(float *)(section_000012e4.sectname + *(int *)((int)param_1 + 0x4c) + 0xc) =
       (float)puVar8 + fVar7 * fVar10;
  pcVar1 = section_000012e4.segname + *(int *)((int)param_1 + 0x4c) + 4;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  pcVar1 = section_000012e4.segname + *(int *)((int)param_1 + 0x4c);
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  pcVar1 = section_000012e4.segname + *(int *)((int)param_1 + 0x4c) + 0xc;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  pcVar1 = section_000012e4.segname + *(int *)((int)param_1 + 0x4c) + 8;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = -0x80;
  pcVar1[3] = '?';
  tMatrix::Identity((tMatrix *)(section_0000125c.sectname + *(int *)((int)param_1 + 0x4c) + 4));
  *(undefined4 *)(section_0000125c.segname + *(int *)((int)param_1 + 0x4c) + 0x24) =
       *(undefined4 *)(section_000012e4.sectname + *(int *)((int)param_1 + 0x4c) + 0xc);
  pcVar1 = section_0000125c.segname + *(int *)((int)param_1 + 0x4c) + 0x28;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  pcVar1 = section_0000125c.segname + *(int *)((int)param_1 + 0x4c) + 0x2c;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = -0x20;
  pcVar1[3] = 'A';
  tMatrix::Identity((tMatrix *)(section_0000125c.sectname + *(int *)((int)param_1 + 0x50) + 4));
  *(undefined4 *)(section_0000125c.segname + *(int *)((int)param_1 + 0x50) + 0x24) =
       *(undefined4 *)(section_000012e4.sectname + *(int *)((int)param_1 + 0x4c) + 0xc);
  pcVar1 = section_0000125c.segname + *(int *)((int)param_1 + 0x50) + 0x28;
  pcVar1[0] = 'H';
  pcVar1[1] = -0x1f;
  pcVar1[2] = -6;
  pcVar1[3] = '>';
  pcVar1 = section_0000125c.segname + *(int *)((int)param_1 + 0x50) + 0x2c;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = -0x20;
  pcVar1[3] = 'A';
  fVar7 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                     (byte)(in_fpscr >> 0x16) & 3);
  *(float *)(section_0000136c.segname + *(int *)((int)param_1 + 0x4c) + 0x1c) =
       (float)puVar8 + fVar7 * fVar10;
  pcVar1 = section_0000136c.segname + *(int *)((int)param_1 + 0x4c) + 0x24;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  pcVar1 = section_0000136c.segname + *(int *)((int)param_1 + 0x4c) + 0x20;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  pcVar1 = section_0000136c.segname + *(int *)((int)param_1 + 0x4c) + 0x2c;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  pcVar1 = section_0000136c.segname + *(int *)((int)param_1 + 0x4c) + 0x28;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = -0x80;
  pcVar1[3] = '?';
  tMatrix::Identity((tMatrix *)(section_000012e4.segname + *(int *)((int)param_1 + 0x4c) + 0x14));
  *(undefined4 *)(section_00001328.segname + *(int *)((int)param_1 + 0x4c)) =
       *(undefined4 *)(section_0000136c.segname + *(int *)((int)param_1 + 0x4c) + 0x1c);
  pcVar1 = section_00001328.segname + *(int *)((int)param_1 + 0x4c) + 4;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  pcVar1 = section_00001328.segname + *(int *)((int)param_1 + 0x4c) + 8;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = -0x18;
  pcVar1[3] = 'A';
  tMatrix::Identity((tMatrix *)(section_000012e4.segname + *(int *)((int)param_1 + 0x50) + 0x14));
  *(undefined4 *)(section_00001328.segname + *(int *)((int)param_1 + 0x50)) =
       *(undefined4 *)(section_0000136c.segname + *(int *)((int)param_1 + 0x4c) + 0x1c);
  pcVar1 = section_00001328.segname + *(int *)((int)param_1 + 0x50) + 4;
  pcVar1[0] = 'H';
  pcVar1[1] = -0x1f;
  pcVar1[2] = -6;
  pcVar1[3] = '>';
  pcVar1 = section_00001328.segname + *(int *)((int)param_1 + 0x50) + 8;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = -0x18;
  pcVar1[3] = 'A';
  iVar3 = 0x1f8;
  local_2c = 1;
  do {
    iVar4 = *(int *)((int)param_1 + 0x4c);
    fVar7 = (float)VectorSignedToFloat(local_2c + -1,(byte)(in_fpscr >> 0x16) & 3);
    fVar9 = (fVar7 * 3.1415927) / 24.0;
    fVar7 = (float)Cos(fVar9);
    *(float *)(iVar3 + iVar4 + 0x90) = fVar7 * *(float *)(*(int *)((int)param_1 + 0x4c) + 0x90);
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar3 + 0x98) = 0;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar3 + 0x94) = 0;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar3 + 0xa0) = 0;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar3 + 0x9c) = 0x3f800000;
    tMatrix::Identity((tMatrix *)(iVar3 + *(int *)((int)param_1 + 0x4c)));
    iVar4 = iVar3 + *(int *)((int)param_1 + 0x4c);
    *(undefined4 *)(iVar4 + 0x30) = *(undefined4 *)(iVar4 + 0x90);
    iVar4 = *(int *)((int)param_1 + 0x4c);
    fVar7 = (float)Sin(fVar9);
    *(float *)(iVar3 + iVar4 + 0x34) = fVar7 * -0.3;
    uVar2 = VectorSignedToFloat(local_2c + 2,(byte)(in_fpscr >> 0x16) & 3);
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar3 + 0x38) = uVar2;
    tMatrix::Identity((tMatrix *)(iVar3 + *(int *)((int)param_1 + 0x50)));
    *(undefined4 *)(iVar3 + *(int *)((int)param_1 + 0x50) + 0x30) =
         *(undefined4 *)(iVar3 + *(int *)((int)param_1 + 0x4c) + 0x90);
    *(float *)(iVar3 + *(int *)((int)param_1 + 0x50) + 0x34) =
         *(float *)(iVar3 + *(int *)((int)param_1 + 0x4c) + 0x34) + 0.49;
    *(undefined4 *)(iVar3 + *(int *)((int)param_1 + 0x50) + 0x38) = uVar2;
    if (local_2c + -1 == 0) {
      tMatrix::RotIdentity((tMatrix *)(iVar3 + *(int *)((int)param_1 + 0x4c) + -0xa8));
      tMatrix::RotIdentity((tMatrix *)(iVar3 + *(int *)((int)param_1 + 0x50) + -0xa8));
    }
    else {
      iVar4 = iVar3 + *(int *)((int)param_1 + 0x4c) + -0xa8;
      *(undefined4 *)(iVar4 + 0x18) = 0;
      *(undefined4 *)(iVar4 + 0x14) = 0x3f800000;
      *(undefined4 *)(iVar4 + 0x10) = 0;
      iVar4 = iVar3 + *(int *)((int)param_1 + 0x4c) + -0xa8;
      iVar5 = iVar3 + *(int *)((int)param_1 + 0x4c);
      fVar7 = *(float *)(iVar5 + 0x34);
      fVar9 = *(float *)(iVar5 + 0x38);
      *(float *)(iVar4 + 0x20) = *(float *)(iVar5 + 0x30) - *(float *)(iVar4 + 0x30);
      *(float *)(iVar4 + 0x24) = fVar7 - *(float *)(iVar4 + 0x34);
      *(float *)(iVar4 + 0x28) = fVar9 - *(float *)(iVar4 + 0x38);
      tVector::Normalize((tVector *)(iVar3 + *(int *)((int)param_1 + 0x4c) + -0x88));
      iVar4 = *(int *)((int)param_1 + 0x4c) + -0xa8;
      iVar5 = iVar3 + iVar4;
      tVector::Cross((tVector *)(iVar3 + iVar4),(tVector *)(iVar5 + 0x10),(tVector *)(iVar5 + 0x20))
      ;
      iVar4 = iVar3 + *(int *)((int)param_1 + 0x50) + -0xa8;
      *(undefined4 *)(iVar4 + 0x18) = 0;
      *(undefined4 *)(iVar4 + 0x14) = 0x3f800000;
      *(undefined4 *)(iVar4 + 0x10) = 0;
      iVar4 = iVar3 + *(int *)((int)param_1 + 0x50) + -0xa8;
      iVar5 = iVar3 + *(int *)((int)param_1 + 0x50);
      fVar7 = *(float *)(iVar5 + 0x34);
      fVar9 = *(float *)(iVar5 + 0x38);
      *(float *)(iVar4 + 0x20) = *(float *)(iVar5 + 0x30) - *(float *)(iVar4 + 0x30);
      *(float *)(iVar4 + 0x24) = fVar7 - *(float *)(iVar4 + 0x34);
      *(float *)(iVar4 + 0x28) = fVar9 - *(float *)(iVar4 + 0x38);
      tVector::Normalize((tVector *)(iVar3 + *(int *)((int)param_1 + 0x50) + -0x88));
      iVar4 = *(int *)((int)param_1 + 0x50) + -0xa8;
      iVar5 = iVar3 + iVar4;
      tVector::Cross((tVector *)(iVar3 + iVar4),(tVector *)(iVar5 + 0x10),(tVector *)(iVar5 + 0x20))
      ;
      if (0x17 < local_2c) {
        iVar3 = *(int *)((int)param_1 + 0x38);
        if (0 < iVar3 + -1) {
          iVar5 = 0;
          iVar4 = 0;
          do {
            iVar5 = iVar5 + 1;
            iVar3 = *(int *)((int)param_1 + 0x4c) + iVar4;
            iVar6 = *(int *)((int)param_1 + 0x4c) + 0xa8 + iVar4;
            fVar7 = *(float *)(iVar6 + 0x34);
            fVar9 = *(float *)(iVar6 + 0x38);
            *(float *)(iVar3 + 0x80) = *(float *)(iVar6 + 0x30) - *(float *)(iVar3 + 0x30);
            *(float *)(iVar3 + 0x84) = fVar7 - *(float *)(iVar3 + 0x34);
            *(float *)(iVar3 + 0x88) = fVar9 - *(float *)(iVar3 + 0x38);
            iVar3 = iVar4 + *(int *)((int)param_1 + 0x4c);
            uVar2 = tVector::Normalize((tVector *)(iVar3 + 0x80));
            *(undefined4 *)(iVar3 + 0x8c) = uVar2;
            iVar3 = *(int *)((int)param_1 + 0x50) + iVar4;
            iVar6 = *(int *)((int)param_1 + 0x50) + 0xa8 + iVar4;
            fVar7 = *(float *)(iVar6 + 0x34);
            fVar9 = *(float *)(iVar6 + 0x38);
            *(float *)(iVar3 + 0x80) = *(float *)(iVar6 + 0x30) - *(float *)(iVar3 + 0x30);
            *(float *)(iVar3 + 0x84) = fVar7 - *(float *)(iVar3 + 0x34);
            *(float *)(iVar3 + 0x88) = fVar9 - *(float *)(iVar3 + 0x38);
            iVar3 = iVar4 + *(int *)((int)param_1 + 0x50);
            uVar2 = tVector::Normalize((tVector *)(iVar3 + 0x80));
            iVar4 = iVar4 + 0xa8;
            *(undefined4 *)(iVar3 + 0x8c) = uVar2;
            iVar3 = *(int *)((int)param_1 + 0x38);
          } while (iVar5 < iVar3 + -1);
        }
        iVar3 = *(int *)((int)param_1 + 0x4c) + -0xa8 + iVar3 * 0xa8;
        *(undefined4 *)(iVar3 + 0x84) = 0;
        *(undefined4 *)(iVar3 + 0x80) = 0;
        *(undefined4 *)(iVar3 + 0x88) = 0x3f800000;
        *(undefined4 *)
         (*(int *)((int)param_1 + 0x38) * 0xa8 + *(int *)((int)param_1 + 0x4c) + -0x1c) = 0x3f800000
        ;
        iVar3 = *(int *)((int)param_1 + 0x50) + -0xa8 + *(int *)((int)param_1 + 0x38) * 0xa8;
        *(undefined4 *)(iVar3 + 0x84) = 0;
        *(undefined4 *)(iVar3 + 0x80) = 0;
        *(undefined4 *)(iVar3 + 0x88) = 0x3f800000;
        *(undefined4 *)
         (*(int *)((int)param_1 + 0x38) * 0xa8 + *(int *)((int)param_1 + 0x50) + -0x1c) = 0x3f800000
        ;
        CalcLengthZ((cRPath *)param_1);
        return;
      }
    }
    iVar3 = iVar3 + 0xa8;
    local_2c = local_2c + 1;
  } while( true );
}
