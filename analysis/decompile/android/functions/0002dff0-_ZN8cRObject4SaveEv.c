/*
 * mangled: _ZN8cRObject4SaveEv
 * demangled: cRObject::Save()
 * address: 0002dff0
 * size: 2184
 */

/* WARNING: Removing unreachable block (ram,0x0002e164) */
/* WARNING: Removing unreachable block (ram,0x0002e168) */
/* cRObject::Save() */

void __thiscall cRObject::Save(cRObject *this)

{
  undefined2 *puVar1;
  ushort uVar2;
  short sVar3;
  int iVar4;
  undefined4 *puVar5;
  uint *puVar6;
  uint *puVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  char *pcVar11;
  int iVar12;
  char cVar13;
  int iVar14;
  ushort *puVar15;
  int iVar16;
  uint uVar17;
  int iVar18;
  undefined4 *puVar19;
  int *piVar20;
  undefined4 *puVar21;
  int iVar22;
  int iVar23;
  short *psVar24;
  undefined4 *local_87c;
  char local_86c [2048];
  char acStack_6c [64];
  int local_2c;

  iVar4 = DAT_0002e87c;
  iVar16 = DAT_0002e878 + 0x2e008;
  local_2c = **(int **)(iVar16 + DAT_0002e87c);
  if ((*(uint *)this & 0x2000000) != 0) goto LAB_0002e028;
  puVar5 = (undefined4 *)RShellMemoryScratch();
  sprintf(acStack_6c,(char *)(iVar16 + DAT_0002e880),this + 0x20);
  if ((*(uint *)(this + 0x20) & 0xffffff) == 0x6f614e) goto LAB_0002e028;
  *puVar5 = 0;
  puVar19 = puVar5 + 3;
  puVar5[1] = *(undefined4 *)this;
  puVar5[2] = *(undefined4 *)(this + 0xa0);
  if (*(int *)(this + 0xa4) != 0) {
    puVar5[3] = 1;
    iVar23 = *(int *)(this + 0xa0);
    puVar19 = puVar5 + 4;
    if (0 < iVar23) {
      iVar10 = 0;
      iVar18 = 0;
      puVar21 = puVar5 + 7;
      do {
        puVar19 = puVar21;
        iVar10 = iVar10 + 1;
        puVar19[-3] = *(undefined4 *)(*(int *)(this + 0xa4) + iVar18);
        puVar19[-2] = *(undefined4 *)(*(int *)(this + 0xa4) + iVar18 + 4);
        iVar9 = *(int *)(this + 0xa4) + iVar18;
        iVar18 = iVar18 + 0xc;
        puVar19[-1] = *(undefined4 *)(iVar9 + 8);
        puVar21 = puVar19 + 3;
      } while (iVar10 < iVar23);
    }
  }
  puVar21 = puVar5;
  local_87c = puVar19;
  if ((*(uint *)this & 0x10000) != 0) {
    *puVar19 = 7;
    iVar23 = *(int *)(this + 0xa0);
    local_87c = puVar19 + 1;
    if (0 < iVar23) {
      iVar8 = *(int *)(this + 0xb4);
      iVar12 = 0;
      iVar9 = 0;
      iVar10 = iVar8;
      iVar18 = iVar8;
      puVar19 = puVar19 + 5;
      do {
        puVar21 = puVar19;
        iVar9 = iVar9 + 1;
        puVar19 = (undefined4 *)(iVar8 + iVar12);
        puVar21[-4] = *puVar19;
        iVar12 = iVar12 + 0x10;
        puVar21[-3] = puVar19[1];
        puVar19 = (undefined4 *)(iVar10 + 8);
        iVar10 = iVar10 + 0x10;
        puVar21[-2] = *puVar19;
        puVar19 = (undefined4 *)(iVar18 + 0xc);
        iVar18 = iVar18 + 0x10;
        puVar21[-1] = *puVar19;
        puVar19 = puVar21 + 4;
        local_87c = puVar21;
      } while (iVar9 < iVar23);
    }
  }
  iVar23 = *(int *)(this + 200);
  if (iVar23 == 0) {
    if (*(int **)(this + 0x10c) == (int *)0x0) goto LAB_0002e840;
    Rstrcpy(local_86c,(char *)(**(int **)(this + 0x10c) + 0xc));
    wprintf((char *)(iVar16 + DAT_0002e884),1);
    iVar10 = 1;
    *local_87c = 3;
    local_87c[1] = 1;
LAB_0002e224:
    iVar23 = 0;
    puVar6 = local_87c + 2;
    do {
      cVar13 = local_86c[iVar23 * 0x40];
      if (cVar13 != '\0') {
        pcVar11 = local_86c + iVar23 * 0x40;
        puVar7 = puVar6;
        do {
          puVar6 = (uint *)((int)puVar7 + 1);
          *(char *)puVar7 = cVar13;
          pcVar11 = pcVar11 + 1;
          cVar13 = *pcVar11;
          puVar7 = puVar6;
        } while (cVar13 != '\0');
      }
      iVar23 = iVar23 + 1;
      puVar7 = (uint *)((int)puVar6 + 1);
      *(char *)puVar6 = '\0';
      puVar6 = puVar7;
    } while (iVar23 < iVar10);
  }
  else {
    if (0 < *(int *)(this + 0xc0)) {
      iVar18 = 0;
      iVar10 = 0;
      iVar9 = 0;
LAB_0002e1d0:
      Rstrcpy(local_86c + iVar10 * 0x40,(char *)(*(int *)(iVar23 + iVar18 + 0xc) + 0xc));
      while( true ) {
        iVar10 = iVar10 + 1;
        iVar9 = iVar9 + 1;
        if (*(int *)(this + 0xc0) <= iVar9) break;
        while( true ) {
          iVar18 = iVar18 + 0x30;
          iVar23 = *(int *)(this + 200);
          if (iVar10 == 0) goto LAB_0002e1d0;
          puVar19 = (undefined4 *)0x0;
          puVar21 = puVar19;
          while( true ) {
            iVar12 = (int)puVar19 * 0x40;
            puVar19 = (undefined4 *)((int)puVar19 + 1);
            iVar23 = Rstrcmp(local_86c + iVar12,(char *)(*(int *)(iVar23 + iVar18 + 0xc) + 0xc));
            if (iVar23 != 0) {
              puVar21 = (undefined4 *)0x1;
            }
            if (iVar10 <= (int)puVar19) break;
            iVar23 = *(int *)(this + 200);
          }
          if (puVar21 == (undefined4 *)0x0) break;
          iVar9 = iVar9 + 1;
          if (*(int *)(this + 0xc0) <= iVar9) goto LAB_0002e1fc;
        }
        Rstrcpy(local_86c + iVar10 * 0x40,
                (char *)(*(int *)(*(int *)(this + 200) + iVar18 + 0xc) + 0xc));
      }
LAB_0002e1fc:
      wprintf((char *)(iVar16 + DAT_0002e884),iVar10);
      *local_87c = 3;
      local_87c[1] = iVar10;
      goto LAB_0002e224;
    }
LAB_0002e840:
    wprintf((char *)(iVar16 + DAT_0002e884),0);
    iVar10 = 0;
    *local_87c = 3;
    puVar7 = local_87c + 2;
    local_87c[1] = 0;
  }
  for (; ((uint)puVar7 & 3) != 0; puVar7 = (uint *)((int)puVar7 + 1)) {
    *(char *)puVar7 = '\0';
  }
  iVar23 = *(int *)(this + 200);
  if (iVar23 != 0) {
    *puVar7 = 2;
    puVar7[1] = *(uint *)(this + 0xc0);
    puVar7 = puVar7 + 2;
    if (0 < *(int *)(this + 0xc0)) {
      iVar18 = 0;
      iVar9 = 0;
      do {
        if (iVar10 == 1) {
          puVar21 = (undefined4 *)0x0;
        }
        puVar6 = puVar7 + 1;
        *puVar7 = (uint)*(ushort *)(iVar23 + iVar18);
        if (iVar10 == 1) {
          puVar6 = puVar7 + 2;
          puVar7[1] = (uint)puVar21;
        }
        else if (0 < iVar10) {
          uVar17 = 0;
          puVar7 = puVar6;
          while( true ) {
            iVar23 = Rstrcmp(local_86c + uVar17 * 0x40,
                             (char *)(*(int *)(iVar23 + iVar18 + 0xc) + 0xc));
            puVar6 = puVar7;
            if (iVar23 != 0) {
              puVar6 = puVar7 + 1;
              *puVar7 = uVar17;
            }
            uVar17 = uVar17 + 1;
            if (iVar10 <= (int)uVar17) break;
            iVar23 = *(int *)(this + 200);
            puVar7 = puVar6;
          }
          iVar23 = *(int *)(this + 200);
        }
        iVar12 = iVar23 + iVar18;
        *puVar6 = *(uint *)(iVar12 + 0x10);
        puVar6[1] = *(uint *)(iVar12 + 0x18);
        puVar6[2] = *(uint *)(iVar12 + 0x20);
        puVar6[3] = *(uint *)(iVar12 + 0x28);
        puVar6[4] = *(uint *)(iVar12 + 0x14);
        puVar6[5] = *(uint *)(iVar12 + 0x1c);
        puVar6[6] = *(uint *)(iVar12 + 0x24);
        puVar6[7] = *(uint *)(iVar12 + 0x2c);
        puVar21 = *(undefined4 **)(this + 0xc0);
        iVar9 = iVar9 + 1;
        iVar18 = iVar18 + 0x30;
        *(undefined2 *)(puVar6 + 8) = *(undefined2 *)(iVar12 + 2);
        *(undefined2 *)((int)puVar6 + 0x22) = *(undefined2 *)(iVar12 + 4);
        puVar7 = puVar6 + 10;
        *(undefined2 *)(puVar6 + 9) = *(undefined2 *)(iVar12 + 6);
        *(undefined2 *)((int)puVar6 + 0x26) = *(undefined2 *)(iVar12 + 8);
      } while (iVar9 < (int)puVar21);
    }
  }
  iVar23 = *(int *)(this + 0x10c);
  if (iVar23 != 0) {
    *puVar7 = 5;
    puVar6 = puVar7 + 2;
    puVar7[1] = *(uint *)(iVar23 + 4);
    iVar10 = *(int *)(iVar23 + 4);
    if (0 < iVar10) {
      iVar18 = 0;
      iVar9 = 0;
      puVar7 = puVar7 + 7;
      do {
        puVar6 = puVar7;
        iVar9 = iVar9 + 1;
        puVar6[-5] = *(uint *)(*(int *)(iVar23 + 8) + iVar18);
        puVar6[-4] = *(uint *)(*(int *)(iVar23 + 8) + iVar18 + 4);
        puVar6[-3] = *(uint *)(*(int *)(iVar23 + 8) + iVar18 + 8);
        puVar6[-2] = *(uint *)(*(int *)(iVar23 + 8) + iVar18 + 0xc);
        iVar12 = *(int *)(iVar23 + 8) + iVar18;
        iVar18 = iVar18 + 0x14;
        puVar6[-1] = *(uint *)(iVar12 + 0x10);
        puVar7 = puVar6 + 5;
      } while (iVar9 < iVar10);
    }
    puVar7 = puVar6 + 1;
    *puVar6 = *(uint *)(iVar23 + 0xc);
    iVar10 = *(int *)(iVar23 + 0xc);
    if (0 < iVar10) {
      iVar18 = 0;
      puVar6 = puVar6 + 3;
      do {
        puVar7 = puVar6;
        puVar7[-2] = *(uint *)(*(int *)(iVar23 + 0x10) + iVar18 * 8);
        iVar9 = iVar18 * 8;
        iVar18 = iVar18 + 1;
        puVar7[-1] = *(uint *)(*(int *)(iVar23 + 0x10) + iVar9 + 4);
        puVar6 = puVar7 + 2;
      } while (iVar18 < iVar10);
    }
    puVar6 = puVar7 + 1;
    *puVar7 = *(uint *)(iVar23 + 0x14);
    iVar10 = *(int *)(iVar23 + 0x14);
    if (0 < iVar10) {
      iVar9 = *(int *)(iVar23 + 0x18);
      iVar18 = 0;
      puVar7 = puVar7 + 2;
      do {
        puVar6 = puVar7;
        iVar12 = iVar18 * 2;
        iVar18 = iVar18 + 1;
        *(undefined2 *)(puVar6 + -1) = *(undefined2 *)(iVar9 + iVar12);
        puVar7 = puVar6 + 1;
      } while (iVar18 < iVar10);
    }
    puVar7 = puVar6 + 1;
    *puVar6 = *(uint *)(iVar23 + 0x44);
    iVar10 = *(int *)(iVar23 + 0x44);
    if (0 < iVar10) {
      iVar18 = *(int *)(iVar23 + 0x48);
      iVar23 = 0;
      puVar6 = puVar6 + 2;
      do {
        puVar7 = puVar6;
        iVar9 = iVar23 * 2;
        iVar23 = iVar23 + 1;
        *(undefined2 *)(puVar7 + -1) = *(undefined2 *)(iVar18 + iVar9);
        puVar6 = puVar7 + 1;
      } while (iVar23 < iVar10);
    }
  }
  if ((*(uint *)this & 0x1000000) != 0) {
    psVar24 = *(short **)(this + 0x104);
    uVar17 = *(uint *)(psVar24 + 8);
    *puVar7 = 4;
    sVar3 = *psVar24;
    puVar7[4] = uVar17;
    uVar17 = *(uint *)(psVar24 + 10);
    puVar7[1] = (int)sVar3;
    puVar7[5] = uVar17;
    puVar6 = puVar7 + 7;
    puVar7[2] = *(uint *)(psVar24 + 2);
    puVar7[3] = *(uint *)(psVar24 + 4);
    puVar7[6] = *(uint *)(this + 0xd0);
    if (0 < *(int *)(psVar24 + 2)) {
      iVar9 = 0;
      iVar23 = *(int *)(this + 0xd0);
      iVar18 = 0;
      iVar10 = *(int *)(*(int *)(iVar16 + DAT_0002e888) + 0x10);
      puVar7 = puVar6;
      do {
        iVar12 = *(int *)(this + 0xa0);
        puVar6 = puVar7;
        if (0 < iVar12) {
          iVar14 = 0;
          iVar8 = 0;
          piVar20 = *(int **)(*(int *)(psVar24 + 6) + iVar9);
          do {
            iVar8 = iVar8 + 1;
            *(undefined4 *)((int)puVar7 + iVar14) =
                 *(undefined4 *)(**(int **)(*(int *)(psVar24 + 6) + iVar9) + iVar14);
            puVar6[1] = *(uint *)(*piVar20 + iVar14 + 4);
            iVar22 = *piVar20 + iVar14;
            iVar14 = iVar14 + 0xc;
            puVar6[2] = *(uint *)(iVar22 + 8);
            puVar6 = puVar6 + 3;
          } while (iVar8 < iVar12);
        }
        if (0 < iVar23) {
          iVar12 = 0;
          puVar7 = puVar6;
          do {
            iVar23 = iVar12 * 4;
            iVar12 = iVar12 + 1;
            puVar6 = puVar7 + 1;
            *puVar7 = (*(int *)(*(int *)(*(int *)(*(int *)(psVar24 + 6) + iVar9) + 8) + iVar23) -
                       iVar10 >> 2) * -0x55555555;
            iVar23 = *(int *)(this + 0xd0);
            puVar7 = puVar6;
          } while (iVar12 < iVar23);
        }
        iVar18 = iVar18 + 1;
        iVar9 = iVar9 + 4;
        puVar7 = puVar6;
      } while (iVar18 < *(int *)(psVar24 + 2));
    }
    puVar7 = puVar6;
    if ((*(uint *)this & 0x4000) != 0) {
      *puVar6 = 6;
      puVar6[1] = *(uint *)(this + 0xe4);
      puVar7 = puVar6 + 2;
      if (0 < *(int *)(this + 0xe4)) {
        iVar10 = *(int *)(this + 0xe8);
        iVar9 = 0;
        iVar18 = 0;
        puVar6 = puVar6 + 7;
        iVar23 = iVar10;
        do {
          iVar18 = iVar18 + 1;
          puVar15 = (ushort *)(iVar10 + iVar9);
          iVar9 = iVar9 + 10;
          uVar2 = puVar15[3];
          puVar6[-5] = (uint)*puVar15;
          *(ushort *)(puVar6 + -4) = uVar2;
          puVar1 = (undefined2 *)(iVar23 + 8);
          iVar23 = iVar23 + 10;
          *(undefined2 *)(puVar6 + -3) = *puVar1;
          iVar12 = *(int *)(this + 0xe4);
          *(ushort *)(puVar6 + -2) = puVar15[1];
          *(ushort *)(puVar6 + -1) = puVar15[2];
          puVar7 = puVar6;
          puVar6 = puVar6 + 5;
        } while (iVar18 < iVar12);
      }
    }
  }
  *puVar7 = 8;
  RShellSaveFile(acStack_6c,puVar5,(int)((int)puVar7 + (4 - (int)puVar5)));
LAB_0002e028:
  if (local_2c == **(int **)(iVar16 + iVar4)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}
