/*
 * mangled: _ZN8cRObject4SaveEv
 * demangled: cRObject::Save()
 * address: 00011d38
 * size: 2344
 */

/* WARNING: Removing unreachable block (ram,0x00011e6c) */
/* cRObject::Save() */

void __thiscall cRObject::Save(cRObject *this)

{
  undefined *puVar1;
  undefined4 *puVar2;
  int iVar3;
  uint *puVar4;
  uint *puVar5;
  int iVar6;
  undefined4 *puVar7;
  int iVar8;
  undefined4 *puVar9;
  char *pcVar10;
  char cVar11;
  uint uVar12;
  uint uVar13;
  uint *puVar14;
  uint uVar15;
  uint uVar16;
  int iVar17;
  undefined4 *local_86c;
  int local_868;
  int local_864;
  char local_860 [2048];
  char acStack_60 [64];

  if ((*(uint *)this & 0x2000000) != 0) {
    return;
  }
  puVar2 = (undefined4 *)RShellMemoryScratch();
  _sprintf(acStack_60,"Data/O_%s.smo",this + 0x20);
  if ((*(uint *)(this + 0x20) & 0xffffff) == 0x6f614e) {
    return;
  }
  *puVar2 = 0;
  puVar2[1] = *(undefined4 *)this;
  puVar7 = puVar2 + 3;
  puVar2[2] = *(undefined4 *)(this + 0xa0);
  if (*(int *)(this + 0xa4) != 0) {
    puVar2[3] = 1;
    puVar7 = puVar2 + 4;
    if (0 < *(int *)(this + 0xa0)) {
      iVar3 = 0;
      puVar9 = puVar2;
      do {
        iVar3 = iVar3 + 1;
        puVar9[4] = *(undefined4 *)((int)puVar9 + (*(int *)(this + 0xa4) - (int)puVar2));
        puVar9[5] = *(undefined4 *)((int)puVar9 + (*(int *)(this + 0xa4) - (int)puVar2) + 4);
        puVar7 = puVar9 + 7;
        puVar9[6] = *(undefined4 *)((int)puVar9 + (*(int *)(this + 0xa4) - (int)puVar2) + 8);
        puVar9 = puVar9 + 3;
      } while (iVar3 < *(int *)(this + 0xa0));
    }
  }
  local_86c = puVar7;
  if ((*(uint *)this & 0x10000) != 0) {
    *puVar7 = 7;
    local_86c = puVar7 + 1;
    if (0 < *(int *)(this + 0xa0)) {
      iVar3 = 0;
      puVar7 = puVar7 + 5;
      do {
        local_86c = puVar7;
        iVar6 = iVar3 * 0x10;
        iVar3 = iVar3 + 1;
        local_86c[-4] = *(undefined4 *)(*(int *)(this + 0xb4) + iVar6);
        local_86c[-3] = *(undefined4 *)(*(int *)(this + 0xb4) + iVar6 + 4);
        local_86c[-2] = *(undefined4 *)(*(int *)(this + 0xb4) + iVar6 + 8);
        local_86c[-1] = *(undefined4 *)(*(int *)(this + 0xb4) + iVar6 + 0xc);
        puVar7 = local_86c + 4;
      } while (iVar3 < *(int *)(this + 0xa0));
    }
  }
  iVar3 = *(int *)(this + 200);
  if (iVar3 == 0) {
    if (*(int **)(this + 0x10c) == (int *)0x0) goto LAB_00012630;
    Rstrcpy(local_860,(char *)(**(int **)(this + 0x10c) + 0xc));
    wprintf("SAVE:Texturenum=%i\n",1);
    uVar16 = 1;
    *local_86c = 3;
    local_86c[1] = 1;
  }
  else {
    if (*(int *)(this + 0xc0) < 1) {
LAB_00012630:
      wprintf("SAVE:Texturenum=%i\n",0);
      uVar16 = 0;
      *local_86c = 3;
      puVar5 = local_86c + 2;
      local_86c[1] = 0;
      goto joined_r0x00011f98;
    }
    uVar15 = 0;
    local_868 = 0;
    uVar12 = 0;
    uVar16 = uVar15;
LAB_00011ef0:
    Rstrcpy(local_860,(char *)(*(int *)(iVar3 + uVar15 + 0xc) + 0xc));
    while( true ) {
      uVar16 = uVar16 + 1;
      local_868 = local_868 + 1;
      if (*(int *)(this + 0xc0) <= local_868) break;
      while( true ) {
        uVar15 = uVar15 + 0x30;
        if (0 < (int)uVar16) {
          uVar12 = 0;
        }
        iVar3 = *(int *)(this + 200);
        uVar13 = uVar12;
        if ((int)uVar16 < 1) goto LAB_00011ef0;
        while( true ) {
          iVar6 = uVar12 * 0x40;
          uVar12 = uVar12 + 1;
          iVar3 = Rstrcmp(local_860 + iVar6,(char *)(*(int *)(uVar15 + iVar3 + 0xc) + 0xc));
          if (iVar3 != 0) {
            uVar13 = 1;
          }
          if (uVar12 == uVar16) break;
          iVar3 = *(int *)(this + 200);
        }
        if (uVar13 == 0) break;
        local_868 = local_868 + 1;
        if (*(int *)(this + 0xc0) <= local_868) goto LAB_00011f2c;
      }
      Rstrcpy(local_860 + uVar16 * 0x40,
              (char *)(*(int *)(*(int *)(this + 200) + uVar15 + 0xc) + 0xc));
    }
LAB_00011f2c:
    wprintf("SAVE:Texturenum=%i\n",uVar16);
    *local_86c = 3;
    puVar5 = local_86c + 2;
    local_86c[1] = uVar16;
    if ((int)uVar16 < 1) goto joined_r0x00011f98;
  }
  iVar3 = 0;
  puVar4 = local_86c + 2;
  do {
    cVar11 = local_860[iVar3 * 0x40];
    if (cVar11 != '\0') {
      pcVar10 = local_860 + iVar3 * 0x40;
      puVar5 = puVar4;
      do {
        puVar4 = (uint *)((int)puVar5 + 1);
        *(char *)puVar5 = cVar11;
        pcVar10 = pcVar10 + 1;
        cVar11 = *pcVar10;
        puVar5 = puVar4;
      } while (cVar11 != '\0');
    }
    iVar3 = iVar3 + 1;
    puVar5 = (uint *)((int)puVar4 + 1);
    *(char *)puVar4 = '\0';
    puVar4 = puVar5;
  } while (iVar3 < (int)uVar16);
joined_r0x00011f98:
  for (; ((uint)puVar5 & 3) != 0; puVar5 = (uint *)((int)puVar5 + 1)) {
    *(char *)puVar5 = '\0';
  }
  puVar4 = puVar5;
  if (*(int *)(this + 200) != 0) {
    *puVar5 = 2;
    puVar4 = puVar5 + 2;
    puVar5[1] = *(uint *)(this + 0xc0);
    if (0 < *(int *)(this + 0xc0)) {
      iVar3 = 0;
      local_864 = 0;
      do {
        puVar5 = puVar4 + 1;
        *puVar4 = (uint)*(ushort *)(*(int *)(this + 200) + iVar3);
        if (uVar16 == 1) {
          puVar4[1] = 0;
          puVar5 = puVar4 + 2;
        }
        else if (0 < (int)uVar16) {
          uVar12 = 0;
          puVar4 = puVar5;
          do {
            iVar6 = Rstrcmp(local_860 + uVar12 * 0x40,
                            (char *)(*(int *)(*(int *)(this + 200) + iVar3 + 0xc) + 0xc));
            puVar5 = puVar4;
            if (iVar6 != 0) {
              puVar5 = puVar4 + 1;
              *puVar4 = uVar12;
            }
            uVar12 = uVar12 + 1;
            puVar4 = puVar5;
          } while (uVar12 != uVar16);
        }
        *puVar5 = *(uint *)(*(int *)(this + 200) + iVar3 + 0x10);
        puVar5[1] = *(uint *)(*(int *)(this + 200) + iVar3 + 0x18);
        puVar5[2] = *(uint *)(*(int *)(this + 200) + iVar3 + 0x20);
        puVar5[3] = *(uint *)(*(int *)(this + 200) + iVar3 + 0x28);
        puVar5[4] = *(uint *)(*(int *)(this + 200) + iVar3 + 0x14);
        puVar5[5] = *(uint *)(*(int *)(this + 200) + iVar3 + 0x1c);
        puVar5[6] = *(uint *)(*(int *)(this + 200) + iVar3 + 0x24);
        puVar5[7] = *(uint *)(*(int *)(this + 200) + iVar3 + 0x2c);
        *(undefined2 *)(puVar5 + 8) = *(undefined2 *)(*(int *)(this + 200) + iVar3 + 2);
        *(undefined2 *)((int)puVar5 + 0x22) = *(undefined2 *)(*(int *)(this + 200) + iVar3 + 4);
        *(undefined2 *)(puVar5 + 9) = *(undefined2 *)(*(int *)(this + 200) + iVar3 + 6);
        iVar6 = *(int *)(this + 200) + iVar3;
        iVar3 = iVar3 + 0x30;
        *(undefined2 *)((int)puVar5 + 0x26) = *(undefined2 *)(iVar6 + 8);
        puVar4 = puVar5 + 10;
        local_864 = local_864 + 1;
      } while (local_864 < *(int *)(this + 0xc0));
    }
  }
  if (*(int *)(this + 0x10c) != 0) {
    *puVar4 = 5;
    puVar5 = puVar4 + 2;
    puVar4[1] = *(uint *)(*(int *)(this + 0x10c) + 4);
    iVar3 = *(int *)(this + 0x10c);
    if (0 < *(int *)(iVar3 + 4)) {
      iVar6 = 0;
      puVar14 = puVar4;
      do {
        iVar6 = iVar6 + 1;
        puVar5 = puVar14 + 7;
        puVar14[2] = *(uint *)((int)puVar14 + (*(int *)(iVar3 + 8) - (int)puVar4));
        puVar14[3] = *(uint *)((int)puVar14 +
                              (*(int *)(*(int *)(this + 0x10c) + 8) - (int)puVar4) + 4);
        puVar14[4] = *(uint *)((int)puVar14 +
                              (*(int *)(*(int *)(this + 0x10c) + 8) - (int)puVar4) + 8);
        puVar14[5] = *(uint *)((int)puVar14 +
                              (*(int *)(*(int *)(this + 0x10c) + 8) - (int)puVar4) + 0xc);
        puVar14[6] = *(uint *)((int)puVar14 +
                              (*(int *)(*(int *)(this + 0x10c) + 8) - (int)puVar4) + 0x10);
        iVar3 = *(int *)(this + 0x10c);
        puVar14 = puVar14 + 5;
      } while (iVar6 < *(int *)(iVar3 + 4));
    }
    puVar4 = puVar5 + 1;
    *puVar5 = *(uint *)(iVar3 + 0xc);
    iVar3 = *(int *)(this + 0x10c);
    if (0 < *(int *)(iVar3 + 0xc)) {
      iVar6 = 0;
      puVar5 = puVar5 + 3;
      do {
        puVar4 = puVar5;
        iVar8 = iVar6 * 8;
        iVar6 = iVar6 + 1;
        puVar4[-2] = *(uint *)(iVar8 + *(int *)(iVar3 + 0x10));
        puVar4[-1] = *(uint *)(iVar8 + *(int *)(*(int *)(this + 0x10c) + 0x10) + 4);
        iVar3 = *(int *)(this + 0x10c);
        puVar5 = puVar4 + 2;
      } while (iVar6 < *(int *)(iVar3 + 0xc));
    }
    puVar5 = puVar4 + 1;
    *puVar4 = *(uint *)(iVar3 + 0x14);
    iVar3 = *(int *)(this + 0x10c);
    if (0 < *(int *)(iVar3 + 0x14)) {
      iVar6 = 0;
      puVar4 = puVar4 + 2;
      do {
        puVar5 = puVar4;
        iVar8 = iVar6 * 2;
        iVar6 = iVar6 + 1;
        *(undefined2 *)(puVar5 + -1) = *(undefined2 *)(iVar8 + *(int *)(iVar3 + 0x18));
        iVar3 = *(int *)(this + 0x10c);
        puVar4 = puVar5 + 1;
      } while (iVar6 < *(int *)(iVar3 + 0x14));
    }
    puVar4 = puVar5 + 1;
    *puVar5 = *(uint *)(iVar3 + 0x44);
    iVar3 = *(int *)(this + 0x10c);
    if (0 < *(int *)(iVar3 + 0x44)) {
      iVar6 = 0;
      puVar5 = puVar5 + 2;
      do {
        puVar4 = puVar5;
        iVar8 = iVar6 * 2;
        iVar6 = iVar6 + 1;
        *(undefined2 *)(puVar4 + -1) = *(undefined2 *)(iVar8 + *(int *)(iVar3 + 0x48));
        iVar3 = *(int *)(this + 0x10c);
        puVar5 = puVar4 + 1;
      } while (iVar6 < *(int *)(iVar3 + 0x44));
    }
  }
  if ((*(uint *)this & 0x1000000) != 0) {
    *puVar4 = 4;
    puVar4[1] = (int)**(short **)(this + 0x104);
    puVar4[2] = *(uint *)(*(int *)(this + 0x104) + 4);
    puVar4[3] = *(uint *)(*(int *)(this + 0x104) + 8);
    puVar4[4] = *(uint *)(*(int *)(this + 0x104) + 0x10);
    puVar4[5] = *(uint *)(*(int *)(this + 0x104) + 0x14);
    puVar4[6] = *(uint *)(this + 0xd0);
    iVar3 = *(int *)(this + 0x104);
    puVar5 = puVar4 + 7;
    if (0 < *(int *)(iVar3 + 4)) {
      iVar6 = 0;
      do {
        if (0 < *(int *)(this + 0xa0)) {
          iVar8 = iVar6 * 4;
          iVar17 = 0;
          puVar4 = puVar5;
          while( true ) {
            iVar17 = iVar17 + 1;
            *puVar4 = *(uint *)((int)puVar4 +
                               (**(int **)(*(int *)(iVar3 + 0xc) + iVar8) - (int)puVar5));
            puVar4[1] = *(uint *)((int)puVar4 +
                                 (**(int **)(*(int *)(*(int *)(this + 0x104) + 0xc) + iVar8) -
                                 (int)puVar5) + 4);
            puVar4[2] = *(uint *)((int)puVar4 +
                                 (**(int **)(*(int *)(*(int *)(this + 0x104) + 0xc) + iVar8) -
                                 (int)puVar5) + 8);
            puVar4 = puVar4 + 3;
            if (*(int *)(this + 0xa0) <= iVar17) break;
            iVar3 = *(int *)(this + 0x104);
          }
          iVar3 = *(int *)(this + 0x104);
          puVar5 = puVar4;
        }
        puVar1 = PTR__gObjectList_001b61cc;
        if (0 < *(int *)(this + 0xd0)) {
          iVar8 = 0;
          puVar4 = puVar5;
          while( true ) {
            iVar17 = iVar8 * 4;
            iVar8 = iVar8 + 1;
            puVar5 = puVar4 + 1;
            *puVar4 = (*(int *)(*(int *)(*(int *)(*(int *)(iVar3 + 0xc) + iVar6 * 4) + 8) + iVar17)
                       - *(int *)(puVar1 + 0x10) >> 2) * -0x55555555;
            if (*(int *)(this + 0xd0) <= iVar8) break;
            iVar3 = *(int *)(this + 0x104);
            puVar4 = puVar5;
          }
          iVar3 = *(int *)(this + 0x104);
        }
        iVar6 = iVar6 + 1;
      } while (iVar6 < *(int *)(iVar3 + 4));
    }
    puVar4 = puVar5;
    if ((*(uint *)this & 0x4000) != 0) {
      *puVar5 = 6;
      puVar5[1] = *(uint *)(this + 0xe4);
      puVar4 = puVar5 + 2;
      if (0 < *(int *)(this + 0xe4)) {
        iVar6 = 0;
        iVar3 = 0;
        puVar5 = puVar5 + 7;
        do {
          puVar4 = puVar5;
          iVar6 = iVar6 + 1;
          puVar4[-5] = (uint)*(ushort *)(*(int *)(this + 0xe8) + iVar3);
          *(undefined2 *)(puVar4 + -4) = *(undefined2 *)(*(int *)(this + 0xe8) + iVar3 + 6);
          *(undefined2 *)(puVar4 + -3) = *(undefined2 *)(*(int *)(this + 0xe8) + iVar3 + 8);
          *(undefined2 *)(puVar4 + -2) = *(undefined2 *)(*(int *)(this + 0xe8) + iVar3 + 2);
          iVar8 = *(int *)(this + 0xe8) + iVar3;
          iVar3 = iVar3 + 10;
          *(undefined2 *)(puVar4 + -1) = *(undefined2 *)(iVar8 + 4);
          puVar5 = puVar4 + 5;
        } while (iVar6 < *(int *)(this + 0xe4));
      }
    }
  }
  *puVar4 = 8;
  RShellSaveFile(acStack_60,puVar2,(int)((int)puVar4 + (4 - (int)puVar2)));
  return;
}
