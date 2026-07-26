/*
 * mangled: _ZN9cRDirectX4LoadEPcP8cRObjecti
 * demangled: cRDirectX::Load(char*, cRObject*, int)
 * address: 00067a20
 * size: 1900
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
  int iVar11;
  char *pcVar12;
  uint *puVar13;
  char *pcVar14;
  char cVar15;
  char *pcVar16;
  undefined4 *puVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  char *pcVar21;
  char *pcVar22;
  undefined2 local_344;
  int local_340;
  char local_338 [6];
  char local_332 [250];
  char acStack_238 [254];
  char acStack_13a [258];
  char *local_38;
  int local_34;
  char *local_30;
  char *local_2c;
  char *local_28;
  char *local_24;

  _sprintf(acStack_13a + 2,param_1);
  sVar3 = _strlen(acStack_13a + 2);
  acStack_13a[sVar3] = '\0';
  _sprintf(acStack_238,"Data/O_%s.smo",acStack_13a + 2);
  iVar4 = RShellFindFile(acStack_238,false);
  if (iVar4 == 0) {
    pcVar5 = (char *)RShellMemoryScratch();
    _sprintf(acStack_13a + 2,"X/%s",param_1);
    RShellLoadFile(acStack_13a + 2,pcVar5,&local_34);
    pcVar5[local_34 + -2] = '\0';
    pcVar5 = (char *)Rstrfind("Frame ",pcVar5);
    if (pcVar5 == (char *)0x0) {
      RShellError("No \'Frame \' Data in %s",acStack_13a + 2);
    }
    else {
      local_24 = (char *)Rstrfind("Mesh ",pcVar5);
      if (local_24 == (char *)0x0) {
        RShellError("No \'VertexDuplicationIndices \'Data in %s",acStack_13a + 2);
      }
      local_24 = (char *)Rstrfind("{",local_24);
      local_28 = (char *)Rstrfind("Mesh ",pcVar5);
      if (local_28 == (char *)0x0) {
        RShellError("No \'Mesh \'Data in %s",acStack_13a + 2);
      }
      local_28 = (char *)Rstrfind("{",local_28);
      local_2c = (char *)Rstrfind("MeshMaterialList ",pcVar5);
      if (local_2c == (char *)0x0) {
        RShellError("No \'MeshMaterialList \'Data in %s",acStack_13a + 2);
      }
      local_2c = (char *)Rstrfind("{",local_2c);
      Rstrint(&local_2c);
      sVar1 = Rstrint(&local_2c);
      sVar2 = Rstrint(&local_24);
      iVar19 = (int)sVar2;
      iVar4 = Rstrint(&local_28);
      if (iVar19 != iVar4) {
        RShellError("Mesh vertices count does not match vertext duplicate vertices count in %s",
                    acStack_13a + 2);
      }
      Rstrint(&local_24);
      local_30 = (char *)Rstrfind("MeshTextureCoords ",pcVar5);
      if (local_30 == (char *)0x0) {
        RShellError("No \'Mesh \'Data in %s",acStack_13a + 2);
      }
      local_30 = (char *)Rstrfind("{",local_30);
      iVar4 = Rstrint(&local_30);
      if (iVar19 != iVar4) {
        RShellError("Mesh texture coords number does not match mesh vertext count in %s",
                    acStack_13a + 2);
      }
      iVar4 = (int)sVar1;
      cRObject::RequestFaceQuads(param_2,iVar4);
      cRObject::RequestVertices(param_2,iVar19);
      pvVar6 = (void *)RShellMemoryMalloc(iVar19 << 2,"Mesh vertex remap");
      puVar7 = (undefined4 *)RShellMemoryMalloc(iVar19 << 3,"Mesh texture coords");
      if (0 < iVar19) {
        iVar18 = 0;
        puVar17 = puVar7;
        do {
          uVar8 = Rstrfloat(&local_30);
          iVar18 = iVar18 + 1;
          *puVar17 = uVar8;
          uVar8 = Rstrfloat(&local_30);
          puVar17[1] = uVar8;
          puVar17 = puVar17 + 2;
        } while (iVar18 != iVar19);
        if (0 < iVar19) {
          sVar1 = 0;
          iVar19 = 0;
          do {
            iVar18 = *(int *)(param_2 + 0xa4);
            uVar8 = Rstrfloat(&local_28);
            *(undefined4 *)(iVar19 + iVar18) = uVar8;
            iVar18 = *(int *)(param_2 + 0xa4);
            uVar8 = Rstrfloat(&local_28);
            *(undefined4 *)(iVar19 + iVar18 + 4) = uVar8;
            iVar18 = iVar19 + *(int *)(param_2 + 0xa4);
            uVar8 = Rstrfloat(&local_28);
            sVar1 = sVar1 + 1;
            iVar19 = iVar19 + 0xc;
            *(undefined4 *)(iVar18 + 8) = uVar8;
          } while (sVar1 != sVar2);
        }
      }
      iVar19 = Rstrint(&local_28);
      if (iVar4 != iVar19) {
        RShellError("Mesh face count does not match material face count in %s",acStack_13a + 2);
      }
      if (0 < iVar4) {
        iVar19 = 0;
        local_340 = 0;
        do {
          *(undefined2 *)(*(int *)(param_2 + 200) + iVar19) = 0;
          iVar18 = Rstrint(&local_28);
          iVar20 = Rstrint(&local_28);
          iVar11 = Rstrint(&local_28);
          iVar9 = Rstrint(&local_28);
          if (iVar18 == 4) {
            iVar10 = Rstrint(&local_28);
            iVar18 = iVar10 << 3;
            local_344 = (undefined2)iVar10;
          }
          else {
            *(ushort *)(iVar19 + *(int *)(param_2 + 200)) =
                 *(ushort *)(iVar19 + *(int *)(param_2 + 200)) | 0x80;
            iVar18 = 0;
            local_344 = 0;
          }
          *(undefined4 *)(*(int *)(param_2 + 200) + iVar19 + 0x20) = puVar7[iVar20 * 2];
          *(undefined4 *)(*(int *)(param_2 + 200) + iVar19 + 0x24) = puVar7[iVar20 * 2 + 1];
          *(undefined4 *)(*(int *)(param_2 + 200) + iVar19 + 0x18) = puVar7[iVar11 * 2];
          *(undefined4 *)(*(int *)(param_2 + 200) + iVar19 + 0x1c) = puVar7[iVar11 * 2 + 1];
          *(undefined4 *)(iVar19 + *(int *)(param_2 + 200) + 0x10) = puVar7[iVar9 * 2];
          *(undefined4 *)(iVar19 + *(int *)(param_2 + 200) + 0x14) = puVar7[iVar9 * 2 + 1];
          *(undefined4 *)(iVar19 + *(int *)(param_2 + 200) + 0x28) =
               *(undefined4 *)((int)puVar7 + iVar18);
          *(undefined4 *)(iVar19 + *(int *)(param_2 + 200) + 0x2c) =
               *(undefined4 *)((int)puVar7 + iVar18 + 4);
          iVar18 = *(int *)(param_2 + 200);
          uVar8 = cRTextures::Add((cRTextures *)PTR__gTextureList_001b61d0,"X/snail-turbo.tga",
                                  (cTgaHeader *)0x0,0);
          *(undefined4 *)(iVar19 + iVar18 + 0xc) = uVar8;
          puVar13 = *(uint **)(iVar19 + *(int *)(param_2 + 200) + 0xc);
          *puVar13 = *puVar13 | 0x1000;
          *(short *)(iVar19 + *(int *)(param_2 + 200) + 6) = (short)iVar20;
          *(short *)(iVar19 + *(int *)(param_2 + 200) + 4) = (short)iVar11;
          *(short *)(iVar19 + *(int *)(param_2 + 200) + 2) = (short)iVar9;
          iVar18 = iVar19 + *(int *)(param_2 + 200);
          iVar19 = iVar19 + 0x30;
          *(undefined2 *)(iVar18 + 8) = local_344;
          local_340 = local_340 + 1;
        } while (local_340 != iVar4);
      }
      *(uint *)param_2 = *(uint *)param_2 | 0x100000;
      RShellMemoryFree(puVar7);
      RShellMemoryFree(pvVar6);
      local_38 = (char *)Rstrfind("MeshMaterialList",pcVar5);
      if (local_38 == (char *)0x0) {
        RShellError("No MeshMaterialList { in %s",acStack_13a + 2);
      }
      else {
        local_38 = (char *)Rstrfind("{",local_38);
        iVar19 = Rstrint(&local_38);
        iVar18 = Rstrint(&local_38);
        if (iVar4 == iVar18) {
          pvVar6 = (void *)RShellMemoryMalloc(iVar19 << 2,"Direct X Materiallist");
          pcVar5 = local_38;
          wprintf("MaterialNumber=%i\n",iVar19);
          if (0 < iVar19) {
            iVar20 = 0;
            iVar18 = 0;
            do {
              pcVar5 = (char *)Rstrfind("TextureFilename ",pcVar5);
              if (pcVar5 == (char *)0x0) {
                if ((param_3 & 2U) == 0) {
                  RShellWarning("No TextureFilename for Material %i in %s",iVar20,acStack_13a + 2);
                }
                uVar8 = cRTextures::Add((cRTextures *)PTR__gTextureList_001b61d0,"Sprites/debug.tga"
                                        ,(cTgaHeader *)0x0,0);
                *(undefined4 *)(iVar18 + (int)pvVar6) = uVar8;
                pcVar5 = local_38;
              }
              else {
                iVar11 = Rstrfind("\"",pcVar5);
                local_338[0] = 'X';
                local_338[1] = 0x2f;
                cVar15 = *(char *)(iVar11 + 1);
                pcVar5 = (char *)(iVar11 + 1);
                if (cVar15 == '.') {
                  pcVar14 = local_338 + 2;
                  pcVar16 = local_338 + 3;
                  pcVar22 = local_338 + 4;
                  pcVar12 = local_338 + 5;
                  pcVar21 = local_332;
                }
                else {
                  pcVar16 = local_338 + 3;
                  do {
                    pcVar14 = pcVar16;
                    pcVar14[-1] = cVar15;
                    pcVar5 = pcVar5 + 1;
                    cVar15 = *pcVar5;
                    pcVar16 = pcVar14 + 1;
                  } while (cVar15 != '.');
                  pcVar22 = pcVar14 + 2;
                  pcVar12 = pcVar14 + 3;
                  pcVar21 = pcVar14 + 4;
                }
                *pcVar14 = '.';
                *pcVar16 = 't';
                *pcVar22 = 'g';
                *pcVar12 = 'a';
                *pcVar21 = '\0';
                puVar13 = (uint *)cRTextures::Add((cRTextures *)PTR__gTextureList_001b61d0,local_338
                                                  ,(cTgaHeader *)0x0,0);
                *(uint **)(iVar18 + (int)pvVar6) = puVar13;
                *puVar13 = *puVar13 | 0x1000;
                if ((param_3 & 2U) != 0) {
                  **(uint **)(iVar18 + (int)pvVar6) = **(uint **)(iVar18 + (int)pvVar6) | 0x8000;
                }
              }
              iVar20 = iVar20 + 1;
              iVar18 = iVar18 + 4;
            } while (iVar20 != iVar19);
          }
          if (0 < iVar4) {
            iVar18 = 0;
            iVar19 = 0;
            do {
              sVar1 = Rstrint(&local_38);
              iVar18 = iVar18 + 1;
              iVar20 = iVar19 + *(int *)(param_2 + 200);
              iVar19 = iVar19 + 0x30;
              *(undefined4 *)(iVar20 + 0xc) = *(undefined4 *)((int)pvVar6 + sVar1 * 4);
            } while (iVar18 != iVar4);
          }
          RShellMemoryFree(pvVar6);
          ObjectProcSimplifyFaces(param_2);
          _strcpy((char *)(param_2 + 0x20),param_1);
          sVar3 = _strlen((char *)(param_2 + 0x20));
          param_2[sVar3 + 0x1e] = (cRObject)0x0;
        }
        else {
          RShellError("No MeshMaterialList face number is not equal to Mesh face number in %s",
                      acStack_13a + 2);
        }
      }
    }
  }
  else {
    cRObject::Load(param_2,acStack_238);
  }
  return;
}
