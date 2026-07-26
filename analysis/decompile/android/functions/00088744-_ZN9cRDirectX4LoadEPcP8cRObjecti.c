/*
 * mangled: _ZN9cRDirectX4LoadEPcP8cRObjecti
 * demangled: cRDirectX::Load(char*, cRObject*, int)
 * address: 00088744
 * size: 2188
 */

/* cRDirectX::Load(char*, cRObject*, int) */

void __thiscall cRDirectX::Load(cRDirectX *this,char *param_1,cRObject *param_2,int param_3)

{
  short sVar1;
  short sVar2;
  size_t sVar3;
  int iVar4;
  char *pcVar5;
  void *pvVar6;
  undefined4 *puVar7;
  undefined4 uVar8;
  int iVar9;
  int iVar10;
  char *pcVar11;
  char *pcVar12;
  char cVar13;
  uint *puVar14;
  uint uVar15;
  int iVar16;
  char *pcVar17;
  uint uVar18;
  int iVar19;
  undefined4 *puVar20;
  int iVar21;
  char *pcVar22;
  int iVar23;
  char *pcVar24;
  uint uVar25;
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

  pcVar11 = acStack_12e + 2;
  local_2c = __stack_chk_guard;
  sprintf(pcVar11,param_1);
  sVar3 = strlen(pcVar11);
  acStack_12e[sVar3] = '\0';
  sprintf(acStack_22c,"Data/O_%s.smo",pcVar11);
  iVar4 = RShellFindFile(acStack_22c,false);
  if (iVar4 == 0) {
    pcVar5 = (char *)RShellMemoryScratch();
    sprintf(pcVar11,"X/%s",param_1);
    RShellLoadFile(pcVar11,pcVar5,&local_340);
    pcVar5[local_340 + -2] = '\0';
    pcVar5 = (char *)Rstrfind("Frame ",pcVar5);
    if (pcVar5 == (char *)0x0) {
      RShellError("No \'Frame \' Data in %s",pcVar11);
    }
    else {
      local_330 = (char *)Rstrfind("Mesh ",pcVar5);
      if (local_330 == (char *)0x0) {
        RShellError("No \'VertexDuplicationIndices \'Data in %s",pcVar11);
      }
      local_330 = (char *)Rstrfind("{",local_330);
      local_334 = (char *)Rstrfind("Mesh ",pcVar5);
      if (local_334 == (char *)0x0) {
        RShellError("No \'Mesh \'Data in %s",acStack_12e + 2);
      }
      local_334 = (char *)Rstrfind("{",local_334);
      local_338 = (char *)Rstrfind("MeshMaterialList ",pcVar5);
      if (local_338 == (char *)0x0) {
        RShellError("No \'MeshMaterialList \'Data in %s",acStack_12e + 2);
      }
      local_338 = (char *)Rstrfind("{",local_338);
      Rstrint(&local_338);
      sVar1 = Rstrint(&local_338);
      sVar2 = Rstrint(&local_330);
      iVar19 = (int)sVar2;
      iVar4 = Rstrint(&local_334);
      if (iVar19 != iVar4) {
        RShellError("Mesh vertices count does not match vertext duplicate vertices count in %s",
                    acStack_12e + 2);
      }
      Rstrint(&local_330);
      local_33c = (char *)Rstrfind("MeshTextureCoords ",pcVar5);
      if (local_33c == (char *)0x0) {
        RShellError("No \'Mesh \'Data in %s",acStack_12e + 2);
      }
      local_33c = (char *)Rstrfind("{",local_33c);
      iVar4 = Rstrint(&local_33c);
      if (iVar19 != iVar4) {
        RShellError("Mesh texture coords number does not match mesh vertext count in %s",
                    acStack_12e + 2);
      }
      iVar4 = (int)sVar1;
      cRObject::RequestFaceQuads(param_2,iVar4);
      cRObject::RequestVertices(param_2,iVar19);
      pvVar6 = (void *)RShellMemoryMalloc(iVar19 << 2,"Mesh vertex remap");
      puVar7 = (undefined4 *)RShellMemoryMalloc(iVar19 << 3,"Mesh texture coords");
      if (0 < iVar19) {
        iVar21 = 0;
        puVar20 = puVar7;
        do {
          iVar21 = iVar21 + 1;
          uVar8 = Rstrfloat(&local_33c);
          *puVar20 = uVar8;
          uVar8 = Rstrfloat(&local_33c);
          puVar20[1] = uVar8;
          puVar20 = puVar20 + 2;
        } while (iVar21 < iVar19);
      }
      if (0 < iVar19) {
        iVar21 = 0;
        sVar1 = 0;
        do {
          iVar23 = *(int *)(param_2 + 0xa4);
          uVar8 = Rstrfloat(&local_334);
          sVar1 = sVar1 + 1;
          *(undefined4 *)(iVar23 + iVar21) = uVar8;
          iVar23 = *(int *)(param_2 + 0xa4);
          uVar8 = Rstrfloat(&local_334);
          *(undefined4 *)(iVar23 + iVar21 + 4) = uVar8;
          iVar23 = *(int *)(param_2 + 0xa4);
          uVar8 = Rstrfloat(&local_334);
          iVar23 = iVar23 + iVar21;
          iVar21 = iVar21 + 0xc;
          *(undefined4 *)(iVar23 + 8) = uVar8;
        } while (sVar1 < iVar19);
      }
      iVar19 = Rstrint(&local_334);
      if (iVar4 != iVar19) {
        RShellError("Mesh face count does not match material face count in %s",acStack_12e + 2);
      }
      if (0 < iVar4) {
        iVar19 = 0;
        local_37c = 0;
        do {
          *(undefined2 *)(*(int *)(param_2 + 200) + iVar19) = 0;
          iVar21 = Rstrint(&local_334);
          iVar23 = Rstrint(&local_334);
          iVar9 = Rstrint(&local_334);
          iVar10 = Rstrint(&local_334);
          if (iVar21 == 4) {
            iVar21 = Rstrint(&local_334);
            iVar16 = *(int *)(param_2 + 200);
            local_378 = (undefined2)iVar21;
            local_374 = iVar21 * 8 + 4;
            iVar21 = iVar21 << 3;
          }
          else {
            iVar16 = *(int *)(param_2 + 200);
            iVar21 = 0;
            local_378 = 0;
            local_374 = 4;
            *(ushort *)(iVar16 + iVar19) = *(ushort *)(iVar16 + iVar19) | 0x80;
          }
          *(undefined4 *)(iVar16 + iVar19 + 0x20) = puVar7[iVar23 * 2];
          *(undefined4 *)(*(int *)(param_2 + 200) + iVar19 + 0x24) = (puVar7 + iVar23 * 2)[1];
          *(undefined4 *)(*(int *)(param_2 + 200) + iVar19 + 0x18) = puVar7[iVar9 * 2];
          *(undefined4 *)(*(int *)(param_2 + 200) + iVar19 + 0x1c) = (puVar7 + iVar9 * 2)[1];
          *(undefined4 *)(*(int *)(param_2 + 200) + iVar19 + 0x10) = puVar7[iVar10 * 2];
          local_37c = local_37c + 1;
          *(undefined4 *)(*(int *)(param_2 + 200) + iVar19 + 0x14) = (puVar7 + iVar10 * 2)[1];
          *(undefined4 *)(*(int *)(param_2 + 200) + iVar19 + 0x28) =
               *(undefined4 *)(iVar21 + (int)puVar7);
          *(undefined4 *)(*(int *)(param_2 + 200) + iVar19 + 0x2c) =
               *(undefined4 *)((int)puVar7 + local_374);
          iVar16 = *(int *)(param_2 + 200);
          uVar8 = cRTextures::Add((cRTextures *)gTextureList,"X/snail-turbo.tga",(cTgaHeader *)0x0,0
                                 );
          iVar21 = *(int *)(param_2 + 200);
          *(undefined4 *)(iVar16 + iVar19 + 0xc) = uVar8;
          puVar14 = *(uint **)(iVar21 + iVar19 + 0xc);
          *puVar14 = *puVar14 | 0x1000;
          *(short *)(iVar21 + iVar19 + 6) = (short)iVar23;
          *(short *)(*(int *)(param_2 + 200) + iVar19 + 4) = (short)iVar9;
          *(short *)(*(int *)(param_2 + 200) + iVar19 + 2) = (short)iVar10;
          iVar21 = *(int *)(param_2 + 200) + iVar19;
          iVar19 = iVar19 + 0x30;
          *(undefined2 *)(iVar21 + 8) = local_378;
        } while (local_37c < iVar4);
      }
      *(uint *)param_2 = *(uint *)param_2 | 0x100000;
      RShellMemoryFree(puVar7);
      RShellMemoryFree(pvVar6);
      local_344 = (char *)Rstrfind("MeshMaterialList",pcVar5);
      if (local_344 == (char *)0x0) {
        RShellError("No MeshMaterialList { in %s",acStack_12e + 2);
      }
      else {
        local_344 = (char *)Rstrfind("{",local_344);
        iVar19 = Rstrint(&local_344);
        iVar21 = Rstrint(&local_344);
        if (iVar4 == iVar21) {
          pvVar6 = (void *)RShellMemoryMalloc(iVar19 << 2,"Direct X Materiallist");
          pcVar11 = local_344;
          wprintf("MaterialNumber=%i\n",iVar19);
          if (0 < iVar19) {
            iVar21 = 0;
            iVar23 = 0;
            uVar25 = param_3 & 2;
            do {
              pcVar11 = (char *)Rstrfind("TextureFilename ",pcVar11);
              if (pcVar11 == (char *)0x0) {
                if (uVar25 == 0) {
                  RShellWarning("No TextureFilename for Material %i in %s",iVar23,acStack_12e + 2);
                }
                uVar8 = cRTextures::Add((cRTextures *)gTextureList,"Sprites/debug.tga",
                                        (cTgaHeader *)0x0,0);
                *(undefined4 *)((int)pvVar6 + iVar21) = uVar8;
                pcVar11 = local_344;
              }
              else {
                iVar9 = Rstrfind("\"",pcVar11);
                local_32c[0] = 'X';
                local_32c[1] = 0x2f;
                cVar13 = *(char *)(iVar9 + 1);
                pcVar11 = (char *)(iVar9 + 1);
                if (cVar13 == '.') {
                  pcVar22 = local_326;
                  pcVar12 = &local_327;
                  pcVar5 = &local_329;
                  pcVar24 = &local_328;
                  pcVar17 = local_32c + 2;
                }
                else {
                  pcVar5 = &local_329;
                  do {
                    pcVar17 = pcVar5;
                    pcVar17[-1] = cVar13;
                    pcVar11 = pcVar11 + 1;
                    cVar13 = *pcVar11;
                    pcVar5 = pcVar17 + 1;
                  } while (cVar13 != '.');
                  pcVar24 = pcVar17 + 2;
                  pcVar12 = pcVar17 + 3;
                  pcVar22 = pcVar17 + 4;
                }
                *pcVar17 = '.';
                *pcVar5 = 't';
                *pcVar24 = 'g';
                *pcVar12 = 'a';
                *pcVar22 = '\0';
                puVar14 = (uint *)cRTextures::Add((cRTextures *)gTextureList,local_32c,
                                                  (cTgaHeader *)0x0,0);
                uVar18 = *puVar14;
                *(uint **)((int)pvVar6 + iVar21) = puVar14;
                uVar15 = uVar18 | 0x1000;
                if (uVar25 != 0) {
                  uVar18 = uVar18 | 0x9000;
                }
                *puVar14 = uVar15;
                if (uVar25 != 0) {
                  *puVar14 = uVar18;
                }
              }
              iVar23 = iVar23 + 1;
              iVar21 = iVar21 + 4;
            } while (iVar23 < iVar19);
          }
          if (0 < iVar4) {
            iVar19 = 0;
            iVar21 = 0;
            do {
              iVar21 = iVar21 + 1;
              sVar1 = Rstrint(&local_344);
              iVar23 = *(int *)(param_2 + 200) + iVar19;
              iVar19 = iVar19 + 0x30;
              *(undefined4 *)(iVar23 + 0xc) = *(undefined4 *)((int)pvVar6 + sVar1 * 4);
            } while (iVar21 < iVar4);
          }
          RShellMemoryFree(pvVar6);
          ObjectProcSimplifyFaces(param_2);
          strcpy((char *)(param_2 + 0x20),param_1);
          sVar3 = strlen((char *)(param_2 + 0x20));
          param_2[sVar3 + 0x1e] = (cRObject)0x0;
        }
        else {
          RShellError("No MeshMaterialList face number is not equal to Mesh face number in %s",
                      acStack_12e + 2);
        }
      }
    }
  }
  else {
    cRObject::Load(param_2,acStack_22c);
  }
  if (local_2c != __stack_chk_guard) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}
