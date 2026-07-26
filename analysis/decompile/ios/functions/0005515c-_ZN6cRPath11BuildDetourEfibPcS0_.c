/*
 * mangled: _ZN6cRPath11BuildDetourEfibPcS0_
 * demangled: cRPath::BuildDetour(float, int, bool, char*, char*)
 * address: 0005515c
 * size: 2312
 */

/* cRPath::BuildDetour(float, int, bool, char*, char*) */

void cRPath::BuildDetour(float param_1,int param_2,bool param_3,char *param_4,char *param_5)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  uint in_fpscr;
  double dVar7;
  float fVar8;
  undefined1 *puVar9;
  float fVar10;
  float fVar11;

  *(undefined4 *)((int)param_1 + 0x2c) = 0x23;
  *(undefined4 *)((int)param_1 + 0x44) = 0x3f800000;
  *(undefined4 *)((int)param_1 + 0x38) = 0x2e;
  *(uint *)((int)param_1 + 0x48) = (uint)param_3;
  *(undefined4 *)((int)param_1 + 0x40) = 0x42380000;
  *(undefined1 *)((int)param_1 + 0x30) = 0;
  *(undefined4 *)((int)param_1 + 0x34) = 0;
  uVar1 = RShellMemoryMalloc(0x1e30,"Path Tile Nodes");
  *(undefined4 *)((int)param_1 + 0x4c) = uVar1;
  uVar1 = RShellMemoryMalloc(*(int *)((int)param_1 + 0x38) * 0xa8,"Path Ball nodes");
  *(undefined4 *)((int)param_1 + 0x50) = uVar1;
  if (0 < *(int *)((int)param_1 + 0x38)) {
    iVar3 = 0;
    iVar2 = 0;
    do {
      iVar3 = iVar3 + 1;
      *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0xa0) = 0;
      iVar4 = *(int *)((int)param_1 + 0x4c) + iVar2;
      iVar2 = iVar2 + 0xa8;
      *(undefined4 *)(iVar4 + 0x9c) = 0x3f800000;
    } while (iVar3 < *(int *)((int)param_1 + 0x38));
  }
  *(undefined1 *)((int)param_1 + 0x84) = 0;
  puVar9 = &DAT_40800000;
  fVar11 = 0.5;
  fVar8 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                     (byte)(in_fpscr >> 0x16) & 3);
  iVar3 = 1;
  *(float *)(*(int *)((int)param_1 + 0x4c) + 0x90) = fVar8 * 0.5 - 4.0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x98) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x94) = 0;
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
  fVar8 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                     (byte)(in_fpscr >> 0x16) & 3);
  *(float *)(*(int *)((int)param_1 + 0x4c) + 0x138) = fVar8 * fVar11 - (float)puVar9;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x140) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x13c) = 0;
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
  fVar8 = (float)VectorSignedToFloat(*(undefined4 *)((int)param_1 + 0x48),
                                     (byte)(in_fpscr >> 0x16) & 3);
  *(float *)(*(int *)((int)param_1 + 0x4c) + 0x1e0) = fVar8 * fVar11 - (float)puVar9;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x1e8) = 0;
  *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x1e4) = 0;
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
  iVar2 = 0x1f8;
  do {
    fVar8 = (float)VectorSignedToFloat(iVar3 + -1,(byte)(in_fpscr >> 0x16) & 3);
    fVar10 = (fVar8 * 6.2831855) / 39.0;
    fVar8 = (float)Sin(fVar10 * 0.5);
    fVar11 = (float)Cos(fVar10);
    iVar4 = *(int *)((int)param_1 + 0x4c);
    fVar11 = fVar8 * -1.3959999 * fVar11;
    fVar8 = (float)Cos(fVar10);
    *(float *)(iVar2 + iVar4 + 0x90) = fVar8 * *(float *)(*(int *)((int)param_1 + 0x4c) + 0x90);
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x98) = 0;
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x94) = 0;
    tMatrix::Identity((tMatrix *)(iVar2 + *(int *)((int)param_1 + 0x4c)));
    iVar4 = iVar2 + *(int *)((int)param_1 + 0x4c);
    *(undefined4 *)(iVar4 + 0x30) = *(undefined4 *)(iVar4 + 0x90);
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x34) = 0;
    uVar1 = VectorSignedToFloat(iVar3 + 2,(byte)(in_fpscr >> 0x16) & 3);
    *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x38) = uVar1;
    tMatrix::Identity((tMatrix *)(iVar2 + *(int *)((int)param_1 + 0x50)));
    *(undefined4 *)(*(int *)((int)param_1 + 0x50) + iVar2 + 0x30) =
         *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x90);
    *(undefined4 *)(*(int *)((int)param_1 + 0x50) + iVar2 + 0x34) =
         *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + iVar2 + 0x34);
    *(undefined4 *)(*(int *)((int)param_1 + 0x50) + iVar2 + 0x38) = uVar1;
    if (iVar3 + -1 == 0) {
      tMatrix::RotIdentity((tMatrix *)(iVar2 + *(int *)((int)param_1 + 0x4c)));
      tMatrix::RotIdentity((tMatrix *)(iVar2 + *(int *)((int)param_1 + 0x50)));
    }
    else {
      iVar4 = *(int *)((int)param_1 + 0x4c) + -0xa8 + iVar2;
      *(undefined4 *)(iVar4 + 0x18) = 0;
      *(undefined4 *)(iVar4 + 0x14) = 0x3f800000;
      *(undefined4 *)(iVar4 + 0x10) = 0;
      iVar5 = *(int *)((int)param_1 + 0x4c) + -0xa8 + iVar2;
      iVar4 = *(int *)((int)param_1 + 0x4c) + iVar2;
      fVar8 = *(float *)(iVar4 + 0x34);
      fVar10 = *(float *)(iVar4 + 0x38);
      *(float *)(iVar5 + 0x20) = *(float *)(iVar4 + 0x30) - *(float *)(iVar5 + 0x30);
      *(float *)(iVar5 + 0x24) = fVar8 - *(float *)(iVar5 + 0x34);
      *(float *)(iVar5 + 0x28) = fVar10 - *(float *)(iVar5 + 0x38);
      tVector::Normalize((tVector *)(iVar2 + *(int *)((int)param_1 + 0x4c) + -0x88));
      iVar4 = *(int *)((int)param_1 + 0x4c) + -0xa8;
      iVar5 = iVar4 + iVar2;
      tVector::Cross((tVector *)(iVar4 + iVar2),(tVector *)(iVar5 + 0x10),(tVector *)(iVar5 + 0x20))
      ;
      tMatrix::RotLocalZ((tMatrix *)(*(int *)((int)param_1 + 0x4c) + -0xa8 + iVar2),fVar11);
      iVar4 = *(int *)((int)param_1 + 0x50) + -0xa8 + iVar2;
      *(undefined4 *)(iVar4 + 0x18) = 0;
      *(undefined4 *)(iVar4 + 0x14) = 0x3f800000;
      *(undefined4 *)(iVar4 + 0x10) = 0;
      iVar5 = *(int *)((int)param_1 + 0x50) + -0xa8 + iVar2;
      iVar4 = *(int *)((int)param_1 + 0x50) + iVar2;
      fVar8 = *(float *)(iVar4 + 0x34);
      fVar10 = *(float *)(iVar4 + 0x38);
      *(float *)(iVar5 + 0x20) = *(float *)(iVar4 + 0x30) - *(float *)(iVar5 + 0x30);
      *(float *)(iVar5 + 0x24) = fVar8 - *(float *)(iVar5 + 0x34);
      *(float *)(iVar5 + 0x28) = fVar10 - *(float *)(iVar5 + 0x38);
      tVector::Normalize((tVector *)(iVar2 + *(int *)((int)param_1 + 0x50) + -0x88));
      iVar4 = *(int *)((int)param_1 + 0x50) + -0xa8;
      iVar5 = iVar4 + iVar2;
      tVector::Cross((tVector *)(iVar4 + iVar2),(tVector *)(iVar5 + 0x10),(tVector *)(iVar5 + 0x20))
      ;
      tMatrix::RotLocalZ((tMatrix *)(*(int *)((int)param_1 + 0x50) + -0xa8 + iVar2),fVar11);
      iVar4 = *(int *)((int)param_1 + 0x50) + -0xa8 + iVar2;
      *(float *)(iVar4 + 0x30) = *(float *)(iVar4 + 0x30) + *(float *)(iVar4 + 0x10) * 0.49;
      *(float *)(iVar4 + 0x34) = *(float *)(iVar4 + 0x34) + *(float *)(iVar4 + 0x14) * 0.49;
      *(float *)(iVar4 + 0x38) = *(float *)(iVar4 + 0x38) + *(float *)(iVar4 + 0x18) * 0.49;
      if (0x28 < iVar3) {
        *(undefined4 *)
         ("/System/Library/Frameworks/CFNetwork.framework/CFNetwork" +
         *(int *)((int)param_1 + 0x4c) + 0x30) =
             *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x90);
        pcVar6 = "/System/Library/Frameworks/CFNetwork.framework/CFNetwork" +
                 *(int *)((int)param_1 + 0x4c) + 0x38;
        pcVar6[0] = '\0';
        pcVar6[1] = '\0';
        pcVar6[2] = '\0';
        pcVar6[3] = '\0';
        pcVar6 = "/System/Library/Frameworks/CFNetwork.framework/CFNetwork" +
                 *(int *)((int)param_1 + 0x4c) + 0x34;
        pcVar6[0] = '\0';
        pcVar6[1] = '\0';
        pcVar6[2] = '\0';
        pcVar6[3] = '\0';
        tMatrix::Identity((tMatrix *)
                          ((int)&dylib_command_00001c28.dylib.current_version +
                          *(int *)((int)param_1 + 0x4c)));
        *(undefined4 *)
         ("/System/Library/Frameworks/CoreLocation.framework/CoreLocation" +
         *(int *)((int)param_1 + 0x4c) + 0x28) =
             *(undefined4 *)
              ("/System/Library/Frameworks/CFNetwork.framework/CFNetwork" +
              *(int *)((int)param_1 + 0x4c) + 0x30);
        pcVar6 = "/System/Library/Frameworks/CoreLocation.framework/CoreLocation" +
                 *(int *)((int)param_1 + 0x4c) + 0x2c;
        pcVar6[0] = '\0';
        pcVar6[1] = '\0';
        pcVar6[2] = '\0';
        pcVar6[3] = '\0';
        pcVar6 = "/System/Library/Frameworks/CoreLocation.framework/CoreLocation" +
                 *(int *)((int)param_1 + 0x4c) + 0x30;
        pcVar6[0] = '\0';
        pcVar6[1] = '\0';
        pcVar6[2] = ',';
        pcVar6[3] = 'B';
        tMatrix::Identity((tMatrix *)
                          ((int)&dylib_command_00001c28.dylib.current_version +
                          *(int *)((int)param_1 + 0x50)));
        *(undefined4 *)
         ("/System/Library/Frameworks/CoreLocation.framework/CoreLocation" +
         *(int *)((int)param_1 + 0x50) + 0x28) =
             *(undefined4 *)
              ("/System/Library/Frameworks/CFNetwork.framework/CFNetwork" +
              *(int *)((int)param_1 + 0x4c) + 0x30);
        pcVar6 = "/System/Library/Frameworks/CoreLocation.framework/CoreLocation" +
                 *(int *)((int)param_1 + 0x50) + 0x2c;
        pcVar6[0] = 'H';
        pcVar6[1] = -0x1f;
        pcVar6[2] = -6;
        pcVar6[3] = '>';
        pcVar6 = "/System/Library/Frameworks/CoreLocation.framework/CoreLocation" +
                 *(int *)((int)param_1 + 0x50) + 0x30;
        pcVar6[0] = '\0';
        pcVar6[1] = '\0';
        pcVar6[2] = ',';
        pcVar6[3] = 'B';
        *(undefined4 *)("/usr/lib/libstdc++.6.dylib" + *(int *)((int)param_1 + 0x4c) + 8) =
             *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x90);
        pcVar6 = "/usr/lib/libstdc++.6.dylib" + *(int *)((int)param_1 + 0x4c) + 0x10;
        pcVar6[0] = '\0';
        pcVar6[1] = '\0';
        pcVar6[2] = '\0';
        pcVar6[3] = '\0';
        pcVar6 = "/usr/lib/libstdc++.6.dylib" + *(int *)((int)param_1 + 0x4c) + 0xc;
        pcVar6[0] = '\0';
        pcVar6[1] = '\0';
        pcVar6[2] = '\0';
        pcVar6[3] = '\0';
        tMatrix::Identity((tMatrix *)
                          ((int)&dylib_command_00001cd4.dylib.timestamp +
                          *(int *)((int)param_1 + 0x4c)));
        *(undefined4 *)
         ((int)&dylib_command_00001d04.dylib.timestamp + *(int *)((int)param_1 + 0x4c)) =
             *(undefined4 *)("/usr/lib/libstdc++.6.dylib" + *(int *)((int)param_1 + 0x4c) + 8);
        *(undefined4 *)
         ((int)&dylib_command_00001d04.dylib.current_version + *(int *)((int)param_1 + 0x4c)) = 0;
        *(undefined4 *)
         ((int)&dylib_command_00001d04.dylib.compatibility_version + *(int *)((int)param_1 + 0x4c))
             = 0x42300000;
        tMatrix::Identity((tMatrix *)
                          ((int)&dylib_command_00001cd4.dylib.timestamp +
                          *(int *)((int)param_1 + 0x50)));
        *(undefined4 *)
         ((int)&dylib_command_00001d04.dylib.timestamp + *(int *)((int)param_1 + 0x50)) =
             *(undefined4 *)("/usr/lib/libstdc++.6.dylib" + *(int *)((int)param_1 + 0x4c) + 8);
        *(undefined4 *)
         ((int)&dylib_command_00001d04.dylib.current_version + *(int *)((int)param_1 + 0x50)) =
             0x3efae148;
        *(undefined4 *)
         ((int)&dylib_command_00001d04.dylib.compatibility_version + *(int *)((int)param_1 + 0x50))
             = 0x42300000;
        *(undefined4 *)("/usr/lib/libobjc.A.dylib" + *(int *)((int)param_1 + 0x4c) + 0x14) =
             *(undefined4 *)(*(int *)((int)param_1 + 0x4c) + 0x90);
        *(undefined4 *)((int)&dylib_command_00001e20.cmd + *(int *)((int)param_1 + 0x4c)) = 0;
        pcVar6 = "/usr/lib/libobjc.A.dylib" + *(int *)((int)param_1 + 0x4c) + 0x18;
        pcVar6[0] = '\0';
        pcVar6[1] = '\0';
        pcVar6[2] = '\0';
        pcVar6[3] = '\0';
        tMatrix::Identity((tMatrix *)
                          ((int)&dylib_command_00001d84.cmdsize + *(int *)((int)param_1 + 0x4c)));
        *(undefined4 *)((int)&dylib_command_00001db8.cmd + *(int *)((int)param_1 + 0x4c)) =
             *(undefined4 *)("/usr/lib/libobjc.A.dylib" + *(int *)((int)param_1 + 0x4c) + 0x14);
        *(undefined4 *)((int)&dylib_command_00001db8.cmdsize + *(int *)((int)param_1 + 0x4c)) = 0;
        *(undefined4 *)
         ((int)&dylib_command_00001db8.dylib.name.offset + *(int *)((int)param_1 + 0x4c)) =
             0x42340000;
        tMatrix::Identity((tMatrix *)
                          ((int)&dylib_command_00001d84.cmdsize + *(int *)((int)param_1 + 0x50)));
        *(undefined4 *)((int)&dylib_command_00001db8.cmd + *(int *)((int)param_1 + 0x50)) =
             *(undefined4 *)("/usr/lib/libobjc.A.dylib" + *(int *)((int)param_1 + 0x4c) + 0x14);
        *(undefined4 *)((int)&dylib_command_00001db8.cmdsize + *(int *)((int)param_1 + 0x50)) =
             0x3efae148;
        *(undefined4 *)
         ((int)&dylib_command_00001db8.dylib.name.offset + *(int *)((int)param_1 + 0x50)) =
             0x42340000;
        iVar2 = *(int *)((int)param_1 + 0x38);
        if (0 < iVar2 + -1) {
          iVar4 = 0;
          iVar3 = 0;
          do {
            iVar4 = iVar4 + 1;
            iVar2 = *(int *)((int)param_1 + 0x4c) + iVar3;
            iVar5 = *(int *)((int)param_1 + 0x4c) + 0xa8 + iVar3;
            fVar8 = *(float *)(iVar5 + 0x34);
            fVar11 = *(float *)(iVar5 + 0x38);
            *(float *)(iVar2 + 0x80) = *(float *)(iVar5 + 0x30) - *(float *)(iVar2 + 0x30);
            *(float *)(iVar2 + 0x84) = fVar8 - *(float *)(iVar2 + 0x34);
            *(float *)(iVar2 + 0x88) = fVar11 - *(float *)(iVar2 + 0x38);
            iVar2 = iVar3 + *(int *)((int)param_1 + 0x4c);
            uVar1 = tVector::Normalize((tVector *)(iVar2 + 0x80));
            *(undefined4 *)(iVar2 + 0x8c) = uVar1;
            iVar2 = *(int *)((int)param_1 + 0x50) + iVar3;
            iVar5 = *(int *)((int)param_1 + 0x50) + 0xa8 + iVar3;
            fVar8 = *(float *)(iVar5 + 0x34);
            fVar11 = *(float *)(iVar5 + 0x38);
            *(float *)(iVar2 + 0x80) = *(float *)(iVar5 + 0x30) - *(float *)(iVar2 + 0x30);
            *(float *)(iVar2 + 0x84) = fVar8 - *(float *)(iVar2 + 0x34);
            *(float *)(iVar2 + 0x88) = fVar11 - *(float *)(iVar2 + 0x38);
            iVar2 = iVar3 + *(int *)((int)param_1 + 0x50);
            uVar1 = tVector::Normalize((tVector *)(iVar2 + 0x80));
            *(undefined4 *)(iVar2 + 0x8c) = uVar1;
            iVar2 = *(int *)((int)param_1 + 0x50) + iVar3;
            iVar3 = iVar3 + 0xa8;
            dVar7 = (double)*(float *)(iVar2 + 0x34);
            wprintf("Path Y %f\n",SUB84(dVar7,0),(int)((ulonglong)dVar7 >> 0x20));
            iVar2 = *(int *)((int)param_1 + 0x38);
          } while (iVar4 < iVar2 + -1);
        }
        iVar2 = *(int *)((int)param_1 + 0x4c) + -0xa8 + iVar2 * 0xa8;
        *(undefined4 *)(iVar2 + 0x84) = 0;
        *(undefined4 *)(iVar2 + 0x80) = 0;
        *(undefined4 *)(iVar2 + 0x88) = 0x3f800000;
        *(undefined4 *)
         (*(int *)((int)param_1 + 0x38) * 0xa8 + *(int *)((int)param_1 + 0x4c) + -0x1c) = 0x3f800000
        ;
        iVar2 = *(int *)((int)param_1 + 0x50) + -0xa8 + *(int *)((int)param_1 + 0x38) * 0xa8;
        *(undefined4 *)(iVar2 + 0x84) = 0;
        *(undefined4 *)(iVar2 + 0x80) = 0;
        *(undefined4 *)(iVar2 + 0x88) = 0x3f800000;
        *(undefined4 *)
         (*(int *)((int)param_1 + 0x38) * 0xa8 + *(int *)((int)param_1 + 0x50) + -0x1c) = 0x3f800000
        ;
        CalcLengthZ((cRPath *)param_1);
        return;
      }
    }
    iVar2 = iVar2 + 0xa8;
    iVar3 = iVar3 + 1;
  } while( true );
}
