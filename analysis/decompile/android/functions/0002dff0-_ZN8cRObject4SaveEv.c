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
  undefined4 uVar4;
  undefined4 *puVar5;
  uint *puVar6;
  uint *puVar7;
  int iVar8;
  int iVar9;
  char *pcVar10;
  int iVar11;
  char cVar12;
  int iVar13;
  ushort *puVar14;
  uint uVar15;
  int iVar16;
  undefined4 *puVar17;
  int *piVar18;
  undefined4 *puVar19;
  int iVar20;
  int iVar21;
  short *psVar22;
  undefined4 *local_87c;
  char local_86c [2048];
  char acStack_6c [64];
  int local_2c;

  local_2c = __stack_chk_guard;
  if ((*(uint *)this & 0x2000000) != 0) goto LAB_0002e028;
  puVar5 = (undefined4 *)RShellMemoryScratch();
  sprintf(acStack_6c,"Data/O_%s.smo",this + 0x20);
  if ((*(uint *)(this + 0x20) & 0xffffff) == 0x6f614e) goto LAB_0002e028;
  *puVar5 = 0;
  puVar17 = puVar5 + 3;
  puVar5[1] = *(undefined4 *)this;
  puVar5[2] = *(undefined4 *)(this + 0xa0);
  if (*(int *)(this + 0xa4) != 0) {
    puVar5[3] = 1;
    iVar21 = *(int *)(this + 0xa0);
    puVar17 = puVar5 + 4;
    if (0 < iVar21) {
      iVar9 = 0;
      iVar16 = 0;
      puVar19 = puVar5 + 7;
      do {
        puVar17 = puVar19;
        iVar9 = iVar9 + 1;
        puVar17[-3] = *(undefined4 *)(*(int *)(this + 0xa4) + iVar16);
        puVar17[-2] = *(undefined4 *)(*(int *)(this + 0xa4) + iVar16 + 4);
        iVar8 = *(int *)(this + 0xa4) + iVar16;
        iVar16 = iVar16 + 0xc;
        puVar17[-1] = *(undefined4 *)(iVar8 + 8);
        puVar19 = puVar17 + 3;
      } while (iVar9 < iVar21);
    }
  }
  puVar19 = puVar5;
  local_87c = puVar17;
  if ((*(uint *)this & 0x10000) != 0) {
    *puVar17 = 7;
    iVar21 = *(int *)(this + 0xa0);
    local_87c = puVar17 + 1;
    if (0 < iVar21) {
      iVar13 = *(int *)(this + 0xb4);
      iVar11 = 0;
      iVar8 = 0;
      iVar9 = iVar13;
      iVar16 = iVar13;
      puVar17 = puVar17 + 5;
      do {
        puVar19 = puVar17;
        iVar8 = iVar8 + 1;
        puVar17 = (undefined4 *)(iVar13 + iVar11);
        puVar19[-4] = *puVar17;
        iVar11 = iVar11 + 0x10;
        puVar19[-3] = puVar17[1];
        puVar17 = (undefined4 *)(iVar9 + 8);
        iVar9 = iVar9 + 0x10;
        puVar19[-2] = *puVar17;
        puVar17 = (undefined4 *)(iVar16 + 0xc);
        iVar16 = iVar16 + 0x10;
        puVar19[-1] = *puVar17;
        puVar17 = puVar19 + 4;
        local_87c = puVar19;
      } while (iVar8 < iVar21);
    }
  }
  iVar21 = *(int *)(this + 200);
  if (iVar21 == 0) {
    if (*(int **)(this + 0x10c) == (int *)0x0) goto LAB_0002e840;
    Rstrcpy(local_86c,(char *)(**(int **)(this + 0x10c) + 0xc));
    wprintf("SAVE:Texturenum=%i\n",1);
    iVar9 = 1;
    *local_87c = 3;
    local_87c[1] = 1;
LAB_0002e224:
    iVar21 = 0;
    puVar6 = local_87c + 2;
    do {
      cVar12 = local_86c[iVar21 * 0x40];
      if (cVar12 != '\0') {
        pcVar10 = local_86c + iVar21 * 0x40;
        puVar7 = puVar6;
        do {
          puVar6 = (uint *)((int)puVar7 + 1);
          *(char *)puVar7 = cVar12;
          pcVar10 = pcVar10 + 1;
          cVar12 = *pcVar10;
          puVar7 = puVar6;
        } while (cVar12 != '\0');
      }
      iVar21 = iVar21 + 1;
      puVar7 = (uint *)((int)puVar6 + 1);
      *(char *)puVar6 = '\0';
      puVar6 = puVar7;
    } while (iVar21 < iVar9);
  }
  else {
    if (0 < *(int *)(this + 0xc0)) {
      iVar16 = 0;
      iVar9 = 0;
      iVar8 = 0;
LAB_0002e1d0:
      Rstrcpy(local_86c + iVar9 * 0x40,(char *)(*(int *)(iVar21 + iVar16 + 0xc) + 0xc));
      while( true ) {
        iVar9 = iVar9 + 1;
        iVar8 = iVar8 + 1;
        if (*(int *)(this + 0xc0) <= iVar8) break;
        while( true ) {
          iVar16 = iVar16 + 0x30;
          iVar21 = *(int *)(this + 200);
          if (iVar9 == 0) goto LAB_0002e1d0;
          puVar17 = (undefined4 *)0x0;
          puVar19 = puVar17;
          while( true ) {
            iVar11 = (int)puVar17 * 0x40;
            puVar17 = (undefined4 *)((int)puVar17 + 1);
            iVar21 = Rstrcmp(local_86c + iVar11,(char *)(*(int *)(iVar21 + iVar16 + 0xc) + 0xc));
            if (iVar21 != 0) {
              puVar19 = (undefined4 *)0x1;
            }
            if (iVar9 <= (int)puVar17) break;
            iVar21 = *(int *)(this + 200);
          }
          if (puVar19 == (undefined4 *)0x0) break;
          iVar8 = iVar8 + 1;
          if (*(int *)(this + 0xc0) <= iVar8) goto LAB_0002e1fc;
        }
        Rstrcpy(local_86c + iVar9 * 0x40,
                (char *)(*(int *)(*(int *)(this + 200) + iVar16 + 0xc) + 0xc));
      }
LAB_0002e1fc:
      wprintf("SAVE:Texturenum=%i\n",iVar9);
      *local_87c = 3;
      local_87c[1] = iVar9;
      goto LAB_0002e224;
    }
LAB_0002e840:
    wprintf("SAVE:Texturenum=%i\n",0);
    iVar9 = 0;
    *local_87c = 3;
    puVar7 = local_87c + 2;
    local_87c[1] = 0;
  }
  for (; ((uint)puVar7 & 3) != 0; puVar7 = (uint *)((int)puVar7 + 1)) {
    *(char *)puVar7 = '\0';
  }
  iVar21 = *(int *)(this + 200);
  if (iVar21 != 0) {
    *puVar7 = 2;
    puVar7[1] = *(uint *)(this + 0xc0);
    puVar7 = puVar7 + 2;
    if (0 < *(int *)(this + 0xc0)) {
      iVar16 = 0;
      iVar8 = 0;
      do {
        if (iVar9 == 1) {
          puVar19 = (undefined4 *)0x0;
        }
        puVar6 = puVar7 + 1;
        *puVar7 = (uint)*(ushort *)(iVar21 + iVar16);
        if (iVar9 == 1) {
          puVar6 = puVar7 + 2;
          puVar7[1] = (uint)puVar19;
        }
        else if (0 < iVar9) {
          uVar15 = 0;
          puVar7 = puVar6;
          while( true ) {
            iVar21 = Rstrcmp(local_86c + uVar15 * 0x40,
                             (char *)(*(int *)(iVar21 + iVar16 + 0xc) + 0xc));
            puVar6 = puVar7;
            if (iVar21 != 0) {
              puVar6 = puVar7 + 1;
              *puVar7 = uVar15;
            }
            uVar15 = uVar15 + 1;
            if (iVar9 <= (int)uVar15) break;
            iVar21 = *(int *)(this + 200);
            puVar7 = puVar6;
          }
          iVar21 = *(int *)(this + 200);
        }
        iVar11 = iVar21 + iVar16;
        *puVar6 = *(uint *)(iVar11 + 0x10);
        puVar6[1] = *(uint *)(iVar11 + 0x18);
        puVar6[2] = *(uint *)(iVar11 + 0x20);
        puVar6[3] = *(uint *)(iVar11 + 0x28);
        puVar6[4] = *(uint *)(iVar11 + 0x14);
        puVar6[5] = *(uint *)(iVar11 + 0x1c);
        puVar6[6] = *(uint *)(iVar11 + 0x24);
        puVar6[7] = *(uint *)(iVar11 + 0x2c);
        puVar19 = *(undefined4 **)(this + 0xc0);
        iVar8 = iVar8 + 1;
        iVar16 = iVar16 + 0x30;
        *(undefined2 *)(puVar6 + 8) = *(undefined2 *)(iVar11 + 2);
        *(undefined2 *)((int)puVar6 + 0x22) = *(undefined2 *)(iVar11 + 4);
        puVar7 = puVar6 + 10;
        *(undefined2 *)(puVar6 + 9) = *(undefined2 *)(iVar11 + 6);
        *(undefined2 *)((int)puVar6 + 0x26) = *(undefined2 *)(iVar11 + 8);
      } while (iVar8 < (int)puVar19);
    }
  }
  iVar21 = *(int *)(this + 0x10c);
  if (iVar21 != 0) {
    *puVar7 = 5;
    puVar6 = puVar7 + 2;
    puVar7[1] = *(uint *)(iVar21 + 4);
    iVar9 = *(int *)(iVar21 + 4);
    if (0 < iVar9) {
      iVar16 = 0;
      iVar8 = 0;
      puVar7 = puVar7 + 7;
      do {
        puVar6 = puVar7;
        iVar8 = iVar8 + 1;
        puVar6[-5] = *(uint *)(*(int *)(iVar21 + 8) + iVar16);
        puVar6[-4] = *(uint *)(*(int *)(iVar21 + 8) + iVar16 + 4);
        puVar6[-3] = *(uint *)(*(int *)(iVar21 + 8) + iVar16 + 8);
        puVar6[-2] = *(uint *)(*(int *)(iVar21 + 8) + iVar16 + 0xc);
        iVar11 = *(int *)(iVar21 + 8) + iVar16;
        iVar16 = iVar16 + 0x14;
        puVar6[-1] = *(uint *)(iVar11 + 0x10);
        puVar7 = puVar6 + 5;
      } while (iVar8 < iVar9);
    }
    puVar7 = puVar6 + 1;
    *puVar6 = *(uint *)(iVar21 + 0xc);
    iVar9 = *(int *)(iVar21 + 0xc);
    if (0 < iVar9) {
      iVar16 = 0;
      puVar6 = puVar6 + 3;
      do {
        puVar7 = puVar6;
        puVar7[-2] = *(uint *)(*(int *)(iVar21 + 0x10) + iVar16 * 8);
        iVar8 = iVar16 * 8;
        iVar16 = iVar16 + 1;
        puVar7[-1] = *(uint *)(*(int *)(iVar21 + 0x10) + iVar8 + 4);
        puVar6 = puVar7 + 2;
      } while (iVar16 < iVar9);
    }
    puVar6 = puVar7 + 1;
    *puVar7 = *(uint *)(iVar21 + 0x14);
    iVar9 = *(int *)(iVar21 + 0x14);
    if (0 < iVar9) {
      iVar8 = *(int *)(iVar21 + 0x18);
      iVar16 = 0;
      puVar7 = puVar7 + 2;
      do {
        puVar6 = puVar7;
        iVar11 = iVar16 * 2;
        iVar16 = iVar16 + 1;
        *(undefined2 *)(puVar6 + -1) = *(undefined2 *)(iVar8 + iVar11);
        puVar7 = puVar6 + 1;
      } while (iVar16 < iVar9);
    }
    puVar7 = puVar6 + 1;
    *puVar6 = *(uint *)(iVar21 + 0x44);
    iVar9 = *(int *)(iVar21 + 0x44);
    if (0 < iVar9) {
      iVar16 = *(int *)(iVar21 + 0x48);
      iVar21 = 0;
      puVar6 = puVar6 + 2;
      do {
        puVar7 = puVar6;
        iVar8 = iVar21 * 2;
        iVar21 = iVar21 + 1;
        *(undefined2 *)(puVar7 + -1) = *(undefined2 *)(iVar16 + iVar8);
        puVar6 = puVar7 + 1;
      } while (iVar21 < iVar9);
    }
  }
  if ((*(uint *)this & 0x1000000) != 0) {
    psVar22 = *(short **)(this + 0x104);
    uVar15 = *(uint *)(psVar22 + 8);
    *puVar7 = 4;
    sVar3 = *psVar22;
    puVar7[4] = uVar15;
    uVar15 = *(uint *)(psVar22 + 10);
    puVar7[1] = (int)sVar3;
    puVar7[5] = uVar15;
    puVar6 = puVar7 + 7;
    puVar7[2] = *(uint *)(psVar22 + 2);
    puVar7[3] = *(uint *)(psVar22 + 4);
    puVar7[6] = *(uint *)(this + 0xd0);
    uVar4 = gObjectList._16_4_;
    if (0 < *(int *)(psVar22 + 2)) {
      iVar16 = 0;
      iVar21 = *(int *)(this + 0xd0);
      iVar9 = 0;
      puVar7 = puVar6;
      do {
        iVar8 = *(int *)(this + 0xa0);
        puVar6 = puVar7;
        if (0 < iVar8) {
          iVar13 = 0;
          iVar11 = 0;
          piVar18 = *(int **)(*(int *)(psVar22 + 6) + iVar16);
          do {
            iVar11 = iVar11 + 1;
            *(undefined4 *)((int)puVar7 + iVar13) =
                 *(undefined4 *)(**(int **)(*(int *)(psVar22 + 6) + iVar16) + iVar13);
            puVar6[1] = *(uint *)(*piVar18 + iVar13 + 4);
            iVar20 = *piVar18 + iVar13;
            iVar13 = iVar13 + 0xc;
            puVar6[2] = *(uint *)(iVar20 + 8);
            puVar6 = puVar6 + 3;
          } while (iVar11 < iVar8);
        }
        if (0 < iVar21) {
          iVar8 = 0;
          puVar7 = puVar6;
          do {
            iVar21 = iVar8 * 4;
            iVar8 = iVar8 + 1;
            puVar6 = puVar7 + 1;
            *puVar7 = (*(int *)(*(int *)(*(int *)(*(int *)(psVar22 + 6) + iVar16) + 8) + iVar21) -
                       uVar4 >> 2) * -0x55555555;
            iVar21 = *(int *)(this + 0xd0);
            puVar7 = puVar6;
          } while (iVar8 < iVar21);
        }
        iVar9 = iVar9 + 1;
        iVar16 = iVar16 + 4;
        puVar7 = puVar6;
      } while (iVar9 < *(int *)(psVar22 + 2));
    }
    puVar7 = puVar6;
    if ((*(uint *)this & 0x4000) != 0) {
      *puVar6 = 6;
      puVar6[1] = *(uint *)(this + 0xe4);
      puVar7 = puVar6 + 2;
      if (0 < *(int *)(this + 0xe4)) {
        iVar9 = *(int *)(this + 0xe8);
        iVar8 = 0;
        iVar16 = 0;
        puVar6 = puVar6 + 7;
        iVar21 = iVar9;
        do {
          iVar16 = iVar16 + 1;
          puVar14 = (ushort *)(iVar9 + iVar8);
          iVar8 = iVar8 + 10;
          uVar2 = puVar14[3];
          puVar6[-5] = (uint)*puVar14;
          *(ushort *)(puVar6 + -4) = uVar2;
          puVar1 = (undefined2 *)(iVar21 + 8);
          iVar21 = iVar21 + 10;
          *(undefined2 *)(puVar6 + -3) = *puVar1;
          iVar11 = *(int *)(this + 0xe4);
          *(ushort *)(puVar6 + -2) = puVar14[1];
          *(ushort *)(puVar6 + -1) = puVar14[2];
          puVar7 = puVar6;
          puVar6 = puVar6 + 5;
        } while (iVar16 < iVar11);
      }
    }
  }
  *puVar7 = 8;
  RShellSaveFile(acStack_6c,puVar5,(int)((int)puVar7 + (4 - (int)puVar5)));
LAB_0002e028:
  if (local_2c == __stack_chk_guard) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}
