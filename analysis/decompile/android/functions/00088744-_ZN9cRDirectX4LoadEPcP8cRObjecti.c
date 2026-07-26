/*
 * mangled: _ZN9cRDirectX4LoadEPcP8cRObjecti
 * demangled: cRDirectX::Load(char*, cRObject*, int)
 * address: 00088744
 * size: 2188
 */

/* cRDirectX::Load(char*, cRObject*, int) */

void __thiscall cRDirectX::Load(cRDirectX *this,char *param_1,cRObject *param_2,int param_3)

{
  int iVar1;
  short sVar2;
  short sVar3;
  size_t sVar4;
  int iVar5;
  char *pcVar6;
  char *pcVar7;
  void *pvVar8;
  undefined4 *puVar9;
  undefined4 uVar10;
  cRTextures *this_00;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  char *pcVar15;
  char cVar16;
  uint *puVar17;
  uint uVar18;
  char *pcVar19;
  int iVar20;
  char *pcVar21;
  char *pcVar22;
  uint uVar23;
  int iVar24;
  undefined4 *puVar25;
  int iVar26;
  int iVar27;
  char *pcVar28;
  int iVar29;
  char *pcVar30;
  uint uVar31;
  char *pcVar32;
  int local_37c;
  undefined2 local_378;
  int local_374;
  char *local_344;
  int local_340;
  char *local_33c;
  char *local_338;
  char *local_334;
  char *local_330;
  char local_32c [3];
  char local_329;
  char local_328;
  char local_327;
  char local_326 [250];
  char acStack_22c [254];
  char acStack_12e [258];
  int local_2c;

  iVar1 = DAT_00088fd0;
  pcVar19 = acStack_12e + 2;
  iVar27 = DAT_00088fd4 + 0x8876c;
  local_2c = **(int **)(iVar27 + DAT_00088fd0);
  sprintf(pcVar19,param_1);
  sVar4 = strlen(pcVar19);
  acStack_12e[sVar4] = '\0';
  sprintf(acStack_22c,(char *)(iVar27 + DAT_00088fd8),pcVar19);
  iVar5 = RShellFindFile(acStack_22c,false);
  if (iVar5 == 0) {
    pcVar6 = (char *)RShellMemoryScratch();
    sprintf(pcVar19,(char *)(iVar27 + DAT_00088fdc),param_1);
    RShellLoadFile(pcVar19,pcVar6,&local_340);
    pcVar7 = (char *)(iVar27 + DAT_00088fe0);
    pcVar6[local_340 + -2] = '\0';
    pcVar6 = (char *)Rstrfind(pcVar7,pcVar6);
    iVar5 = DAT_00088fe4;
    if (pcVar6 == (char *)0x0) {
      RShellError((char *)(iVar27 + DAT_00089034),pcVar19);
    }
    else {
      local_330 = (char *)Rstrfind((char *)(iVar27 + DAT_00088fe4),pcVar6);
      if (local_330 == (char *)0x0) {
        RShellError((char *)(iVar27 + DAT_00089040),pcVar19);
      }
      iVar14 = DAT_00088fe8;
      local_330 = (char *)Rstrfind((char *)(iVar27 + DAT_00088fe8),local_330);
      local_334 = (char *)Rstrfind((char *)(iVar27 + iVar5),pcVar6);
      if (local_334 == (char *)0x0) {
        RShellError((char *)(iVar27 + DAT_00089038),acStack_12e + 2);
      }
      local_334 = (char *)Rstrfind((char *)(iVar27 + iVar14),local_334);
      local_338 = (char *)Rstrfind((char *)(iVar27 + DAT_00088fec),pcVar6);
      if (local_338 == (char *)0x0) {
        RShellError((char *)(iVar27 + DAT_0008903c),acStack_12e + 2);
      }
      local_338 = (char *)Rstrfind((char *)(iVar27 + iVar14),local_338);
      Rstrint(&local_338);
      sVar2 = Rstrint(&local_338);
      sVar3 = Rstrint(&local_330);
      iVar24 = (int)sVar3;
      iVar5 = Rstrint(&local_334);
      if (iVar24 != iVar5) {
        RShellError((char *)(iVar27 + DAT_00088ff0),acStack_12e + 2);
      }
      Rstrint(&local_330);
      local_33c = (char *)Rstrfind((char *)(iVar27 + DAT_00088ff4),pcVar6);
      if (local_33c == (char *)0x0) {
        RShellError((char *)(iVar27 + DAT_00089038),acStack_12e + 2);
      }
      local_33c = (char *)Rstrfind((char *)(iVar27 + iVar14),local_33c);
      iVar5 = Rstrint(&local_33c);
      if (iVar24 != iVar5) {
        RShellError((char *)(iVar27 + DAT_00088ff8),acStack_12e + 2);
      }
      iVar5 = (int)sVar2;
      cRObject::RequestFaceQuads(param_2,iVar5);
      cRObject::RequestVertices(param_2,iVar24);
      pvVar8 = (void *)RShellMemoryMalloc(iVar24 << 2,(char *)(iVar27 + DAT_00088ffc));
      puVar9 = (undefined4 *)RShellMemoryMalloc(iVar24 << 3,(char *)(iVar27 + DAT_00089000));
      if (0 < iVar24) {
        iVar26 = 0;
        puVar25 = puVar9;
        do {
          iVar26 = iVar26 + 1;
          uVar10 = Rstrfloat(&local_33c);
          *puVar25 = uVar10;
          uVar10 = Rstrfloat(&local_33c);
          puVar25[1] = uVar10;
          puVar25 = puVar25 + 2;
        } while (iVar26 < iVar24);
      }
      if (0 < iVar24) {
        iVar26 = 0;
        sVar2 = 0;
        do {
          iVar29 = *(int *)(param_2 + 0xa4);
          uVar10 = Rstrfloat(&local_334);
          sVar2 = sVar2 + 1;
          *(undefined4 *)(iVar29 + iVar26) = uVar10;
          iVar29 = *(int *)(param_2 + 0xa4);
          uVar10 = Rstrfloat(&local_334);
          *(undefined4 *)(iVar29 + iVar26 + 4) = uVar10;
          iVar29 = *(int *)(param_2 + 0xa4);
          uVar10 = Rstrfloat(&local_334);
          iVar29 = iVar29 + iVar26;
          iVar26 = iVar26 + 0xc;
          *(undefined4 *)(iVar29 + 8) = uVar10;
        } while (sVar2 < iVar24);
      }
      iVar24 = Rstrint(&local_334);
      if (iVar5 != iVar24) {
        RShellError((char *)(iVar27 + DAT_00089004),acStack_12e + 2);
      }
      iVar24 = DAT_00089008;
      if (0 < iVar5) {
        iVar26 = 0;
        local_37c = 0;
        pcVar19 = (char *)(iVar27 + DAT_0008900c);
        do {
          *(undefined2 *)(*(int *)(param_2 + 200) + iVar26) = 0;
          iVar29 = Rstrint(&local_334);
          iVar11 = Rstrint(&local_334);
          iVar12 = Rstrint(&local_334);
          iVar13 = Rstrint(&local_334);
          if (iVar29 == 4) {
            iVar29 = Rstrint(&local_334);
            iVar20 = *(int *)(param_2 + 200);
            local_378 = (undefined2)iVar29;
            local_374 = iVar29 * 8 + 4;
            iVar29 = iVar29 << 3;
          }
          else {
            iVar20 = *(int *)(param_2 + 200);
            iVar29 = 0;
            local_378 = 0;
            local_374 = 4;
            *(ushort *)(iVar20 + iVar26) = *(ushort *)(iVar20 + iVar26) | 0x80;
          }
          *(undefined4 *)(iVar20 + iVar26 + 0x20) = puVar9[iVar11 * 2];
          *(undefined4 *)(*(int *)(param_2 + 200) + iVar26 + 0x24) = (puVar9 + iVar11 * 2)[1];
          *(undefined4 *)(*(int *)(param_2 + 200) + iVar26 + 0x18) = puVar9[iVar12 * 2];
          this_00 = *(cRTextures **)(iVar27 + iVar24);
          *(undefined4 *)(*(int *)(param_2 + 200) + iVar26 + 0x1c) = (puVar9 + iVar12 * 2)[1];
          *(undefined4 *)(*(int *)(param_2 + 200) + iVar26 + 0x10) = puVar9[iVar13 * 2];
          local_37c = local_37c + 1;
          *(undefined4 *)(*(int *)(param_2 + 200) + iVar26 + 0x14) = (puVar9 + iVar13 * 2)[1];
          *(undefined4 *)(*(int *)(param_2 + 200) + iVar26 + 0x28) =
               *(undefined4 *)(iVar29 + (int)puVar9);
          *(undefined4 *)(*(int *)(param_2 + 200) + iVar26 + 0x2c) =
               *(undefined4 *)((int)puVar9 + local_374);
          iVar20 = *(int *)(param_2 + 200);
          uVar10 = cRTextures::Add(this_00,pcVar19,(cTgaHeader *)0x0,0);
          iVar29 = *(int *)(param_2 + 200);
          *(undefined4 *)(iVar20 + iVar26 + 0xc) = uVar10;
          puVar17 = *(uint **)(iVar29 + iVar26 + 0xc);
          *puVar17 = *puVar17 | 0x1000;
          *(short *)(iVar29 + iVar26 + 6) = (short)iVar11;
          *(short *)(*(int *)(param_2 + 200) + iVar26 + 4) = (short)iVar12;
          *(short *)(*(int *)(param_2 + 200) + iVar26 + 2) = (short)iVar13;
          iVar29 = *(int *)(param_2 + 200) + iVar26;
          iVar26 = iVar26 + 0x30;
          *(undefined2 *)(iVar29 + 8) = local_378;
        } while (local_37c < iVar5);
      }
      *(uint *)param_2 = *(uint *)param_2 | 0x100000;
      RShellMemoryFree(puVar9);
      RShellMemoryFree(pvVar8);
      local_344 = (char *)Rstrfind((char *)(iVar27 + DAT_00089010),pcVar6);
      if (local_344 == (char *)0x0) {
        RShellError((char *)(iVar27 + DAT_00089018),acStack_12e + 2);
      }
      else {
        local_344 = (char *)Rstrfind((char *)(iVar27 + iVar14),local_344);
        iVar14 = Rstrint(&local_344);
        iVar24 = Rstrint(&local_344);
        if (iVar5 == iVar24) {
          pvVar8 = (void *)RShellMemoryMalloc(iVar14 << 2,(char *)(iVar27 + DAT_0008901c));
          pcVar19 = local_344;
          wprintf((char *)(iVar27 + DAT_00089020),iVar14);
          iVar26 = DAT_0008902c;
          iVar24 = DAT_00089008;
          if (0 < iVar14) {
            iVar29 = 0;
            iVar11 = 0;
            pcVar6 = (char *)(iVar27 + DAT_00089024);
            pcVar7 = (char *)(iVar27 + DAT_00089028);
            uVar31 = param_3 & 2;
            pcVar21 = (char *)(iVar27 + DAT_00089030);
            do {
              pcVar19 = (char *)Rstrfind((char *)(iVar27 + iVar26),pcVar19);
              if (pcVar19 == (char *)0x0) {
                if (uVar31 == 0) {
                  RShellWarning(pcVar21,iVar11,acStack_12e + 2);
                }
                uVar10 = cRTextures::Add(*(cRTextures **)(iVar27 + iVar24),pcVar7,(cTgaHeader *)0x0,
                                         0);
                *(undefined4 *)((int)pvVar8 + iVar29) = uVar10;
                pcVar19 = local_344;
              }
              else {
                iVar12 = Rstrfind(pcVar6,pcVar19);
                local_32c[0] = 'X';
                local_32c[1] = 0x2f;
                cVar16 = *(char *)(iVar12 + 1);
                pcVar19 = (char *)(iVar12 + 1);
                if (cVar16 == '.') {
                  pcVar28 = local_326;
                  pcVar15 = &local_327;
                  pcVar32 = &local_329;
                  pcVar30 = &local_328;
                  pcVar22 = local_32c + 2;
                }
                else {
                  pcVar32 = &local_329;
                  do {
                    pcVar22 = pcVar32;
                    pcVar22[-1] = cVar16;
                    pcVar19 = pcVar19 + 1;
                    cVar16 = *pcVar19;
                    pcVar32 = pcVar22 + 1;
                  } while (cVar16 != '.');
                  pcVar30 = pcVar22 + 2;
                  pcVar15 = pcVar22 + 3;
                  pcVar28 = pcVar22 + 4;
                }
                *pcVar22 = '.';
                *pcVar32 = 't';
                *pcVar30 = 'g';
                *pcVar15 = 'a';
                *pcVar28 = '\0';
                puVar17 = (uint *)cRTextures::Add(*(cRTextures **)(iVar27 + iVar24),local_32c,
                                                  (cTgaHeader *)0x0,0);
                uVar23 = *puVar17;
                *(uint **)((int)pvVar8 + iVar29) = puVar17;
                uVar18 = uVar23 | 0x1000;
                if (uVar31 != 0) {
                  uVar23 = uVar23 | 0x9000;
                }
                *puVar17 = uVar18;
                if (uVar31 != 0) {
                  *puVar17 = uVar23;
                }
              }
              iVar11 = iVar11 + 1;
              iVar29 = iVar29 + 4;
            } while (iVar11 < iVar14);
          }
          if (0 < iVar5) {
            iVar14 = 0;
            iVar24 = 0;
            do {
              iVar24 = iVar24 + 1;
              sVar2 = Rstrint(&local_344);
              iVar26 = *(int *)(param_2 + 200) + iVar14;
              iVar14 = iVar14 + 0x30;
              *(undefined4 *)(iVar26 + 0xc) = *(undefined4 *)((int)pvVar8 + sVar2 * 4);
            } while (iVar24 < iVar5);
          }
          RShellMemoryFree(pvVar8);
          ObjectProcSimplifyFaces(param_2);
          strcpy((char *)(param_2 + 0x20),param_1);
          sVar4 = strlen((char *)(param_2 + 0x20));
          param_2[sVar4 + 0x1e] = (cRObject)0x0;
        }
        else {
          RShellError((char *)(iVar27 + DAT_00089014),acStack_12e + 2);
        }
      }
    }
  }
  else {
    cRObject::Load(param_2,acStack_22c);
  }
  if (local_2c != **(int **)(iVar27 + iVar1)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}
