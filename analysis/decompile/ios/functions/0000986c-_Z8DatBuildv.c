/*
 * mangled: _Z8DatBuildv
 * demangled: DatBuild()
 * address: 0000986c
 * size: 856
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* DatBuild() */

void DatBuild(void)

{
  int iVar1;
  FILE *pFVar2;
  void *pvVar3;
  int *piVar4;
  int iVar5;
  char *pcVar6;
  int iVar7;
  char *pcVar8;
  char *pcVar9;
  char cVar10;
  undefined1 *puVar11;
  int *piVar12;
  void *pvVar13;
  int iVar14;
  bool bVar15;
  bool bVar16;
  int local_23c;
  char local_234 [512];
  int local_34;
  int local_30;
  int local_2c;
  char *local_28;
  int local_24;

  pFVar2 = _fopen("iSM.dat","rb");
  if (pFVar2 == (FILE *)0x0) {
    pFVar2 = _fopen("iSM.dam","rb");
    if (pFVar2 != (FILE *)0x0) {
      _fclose(pFVar2);
      pvVar3 = _malloc(0x1900000);
      piVar4 = (int *)LoadFile("iSM.dam",(void *)0x0,&local_24);
      if (0 < local_24) {
        iVar5 = 0;
        do {
          *(byte *)(iVar5 + (int)piVar4) = *(byte *)(iVar5 + (int)piVar4) ^ 0x80;
          iVar5 = iVar5 + 1;
        } while (iVar5 != local_24);
      }
      _memcpy(pvVar3,piVar4,piVar4[2]);
      local_28 = (char *)0x0;
      puVar11 = (undefined1 *)((int)pvVar3 + *(int *)((int)pvVar3 + 8));
      if (0 < *piVar4) {
        local_23c = 0;
        piVar12 = piVar4;
        pvVar13 = pvVar3;
        do {
          pcVar8 = (char *)((int)pvVar3 + piVar12[1]);
          cVar10 = *(char *)((int)pvVar3 + piVar12[1]);
          pcVar9 = pcVar8;
          if (cVar10 == '\0' || cVar10 == '.') {
            pcVar6 = local_234;
          }
          else {
            pcVar6 = local_234;
            do {
              pcVar6 = pcVar6 + 1;
              pcVar6[-1] = cVar10;
              pcVar9 = pcVar9 + 1;
              cVar10 = *pcVar9;
            } while (cVar10 != '\0' && cVar10 != '.');
          }
          *pcVar6 = '\0';
          if (*pcVar9 == '\0') {
LAB_000099bc:
            _memcpy(puVar11,(void *)((int)piVar4 + piVar12[2]),piVar12[3]);
            *(int *)((int)pvVar13 + 8) = (int)puVar11 - (int)pvVar3;
            puVar11 = puVar11 + piVar12[3] + ((uint)(puVar11 + piVar12[3]) & 3);
            *(int *)((int)pvVar13 + 0xc) = piVar12[3];
          }
          else {
            cVar10 = pcVar9[1];
            bVar15 = cVar10 == 'T';
            if (bVar15) {
              cVar10 = pcVar9[2];
            }
            bVar16 = bVar15 && cVar10 == 'G';
            if (bVar15 && cVar10 == 'G') {
              bVar16 = pcVar9[3] == 'A';
            }
            if (!bVar16) goto LAB_000099bc;
            SaveFile("0.png",(void *)((int)piVar4 + piVar12[2]),piVar12[3],false);
            PngLoadImage("0.png",&local_28,&local_2c,&local_30,&local_34);
            *(int *)((int)pvVar13 + 8) = (int)puVar11 - (int)pvVar3;
            puVar11[7] = 0;
            puVar11[6] = 0;
            puVar11[5] = 0;
            puVar11[4] = 0;
            puVar11[3] = 0;
            puVar11[1] = 0;
            *puVar11 = 0;
            puVar11[0x11] = 8;
            *(undefined2 *)(puVar11 + 0xe) = (undefined2)local_30;
            puVar11[2] = 2;
            puVar11[0x10] = (char)(local_34 << 3);
            *(undefined2 *)(puVar11 + 8) = 0;
            *(undefined2 *)(puVar11 + 10) = 0;
            *(undefined2 *)(puVar11 + 0xc) = (undefined2)local_2c;
            if (0 < local_2c) {
              iVar5 = 0;
              do {
                if (0 < local_30) {
                  iVar14 = 0;
                  do {
                    iVar1 = local_34 * (local_2c * ((local_30 + -1) - iVar14) + iVar5);
                    iVar7 = local_34 * (local_2c * iVar14 + iVar5);
                    iVar14 = iVar14 + 1;
                    puVar11[iVar1 + 0x14] = local_28[iVar7];
                    puVar11[iVar1 + 0x13] = local_28[iVar7 + 1];
                    puVar11[iVar1 + 0x12] = local_28[iVar7 + 2];
                    if (local_34 == 4) {
                      puVar11[iVar1 + 0x15] = local_28[iVar7 + 3];
                    }
                  } while (iVar14 < local_30);
                }
                iVar5 = iVar5 + 1;
              } while (iVar5 < local_2c);
            }
            iVar5 = local_2c * local_30 * local_34 + 0x14;
            *(int *)((int)pvVar13 + 0xc) = iVar5;
            puVar11 = puVar11 + iVar5 + ((uint)(puVar11 + iVar5) & 3);
            _printf("extracting %s\n",pcVar8);
            _free(local_28);
            local_28 = (char *)0x0;
          }
          piVar12 = piVar12 + 3;
          pvVar13 = (void *)((int)pvVar13 + 0xc);
          local_23c = local_23c + 1;
        } while (local_23c < *piVar4);
      }
      SaveFile("iSM.dat",pvVar3,(int)puVar11 - (int)pvVar3,true);
      _remove("iSM.dam");
      _remove("0.png");
      _free(pvVar3);
    }
  }
  else {
    _fclose(pFVar2);
  }
  return;
}
