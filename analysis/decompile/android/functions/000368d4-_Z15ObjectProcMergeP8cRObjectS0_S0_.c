/*
 * mangled: _Z15ObjectProcMergeP8cRObjectS0_S0_
 * demangled: ObjectProcMerge(cRObject*, cRObject*, cRObject*)
 * address: 000368d4
 * size: 704
 */

/* ObjectProcMerge(cRObject*, cRObject*, cRObject*) */

void ObjectProcMerge(cRObject *param_1,cRObject *param_2,cRObject *param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 *puVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  undefined4 *puVar14;
  undefined4 *puVar15;

  cRObject::RequestVertices(param_1,*(int *)(param_3 + 0xa0) + *(int *)(param_2 + 0xa0));
  if ((*(uint *)param_2 & 0x10000) != 0) {
    cRObject::RequestColours(param_1);
  }
  cRObject::RequestFaceQuads(param_1,*(int *)(param_3 + 0xc0) + *(int *)(param_2 + 0xc0));
  iVar2 = *(int *)(param_2 + 0xa0);
  if ((*(uint *)param_2 & 0x10000) != 0) {
    *(uint *)param_1 = *(uint *)param_1 | 0x10000;
  }
  if (0 < iVar2) {
    iVar11 = *(int *)(param_2 + 0xa4);
    iVar10 = *(int *)(param_1 + 0xa4);
    if ((*(uint *)param_1 & 0x10000) == 0) {
      iVar5 = 0;
      iVar8 = 0;
      do {
        puVar3 = (undefined4 *)(iVar11 + iVar5);
        iVar8 = iVar8 + 1;
        puVar14 = (undefined4 *)(iVar10 + iVar5);
        uVar1 = puVar3[1];
        uVar4 = puVar3[2];
        iVar5 = iVar5 + 0xc;
        *puVar14 = *puVar3;
        puVar14[1] = uVar1;
        puVar14[2] = uVar4;
      } while (iVar8 != iVar2);
    }
    else {
      iVar5 = 0;
      iVar12 = *(int *)(param_2 + 0xb4);
      iVar8 = 0;
      iVar9 = *(int *)(param_1 + 0xb4);
      do {
        puVar3 = (undefined4 *)(iVar11 + iVar5);
        iVar13 = iVar8 * 0x10;
        puVar14 = (undefined4 *)(iVar12 + iVar13);
        puVar7 = (undefined4 *)(iVar10 + iVar5);
        uVar1 = puVar3[1];
        uVar4 = puVar3[2];
        iVar8 = iVar8 + 1;
        puVar15 = (undefined4 *)(iVar9 + iVar13);
        iVar5 = iVar5 + 0xc;
        *puVar7 = *puVar3;
        puVar7[1] = uVar1;
        puVar7[2] = uVar4;
        uVar1 = puVar14[1];
        uVar4 = puVar14[2];
        uVar6 = puVar14[3];
        *puVar15 = *puVar14;
        puVar15[1] = uVar1;
        puVar15[2] = uVar4;
        puVar15[3] = uVar6;
      } while (iVar8 != iVar2);
    }
  }
  iVar10 = *(int *)(param_3 + 0xa0);
  if (0 < iVar10) {
    iVar11 = *(int *)(param_3 + 0xa4);
    if ((*(uint *)param_1 & 0x10000) == 0) {
      puVar3 = (undefined4 *)(*(int *)(param_1 + 0xa4) + iVar2 * 0xc);
      iVar5 = 0;
      iVar8 = 0;
      do {
        puVar14 = (undefined4 *)(iVar11 + iVar8);
        iVar5 = iVar5 + 1;
        iVar8 = iVar8 + 0xc;
        uVar1 = puVar14[1];
        uVar4 = puVar14[2];
        *puVar3 = *puVar14;
        puVar3[1] = uVar1;
        puVar3[2] = uVar4;
        puVar3 = puVar3 + 3;
      } while (iVar5 != iVar10);
    }
    else {
      iVar9 = 0;
      iVar12 = 0;
      iVar13 = *(int *)(param_1 + 0xb4);
      iVar5 = iVar2 << 4;
      iVar8 = *(int *)(param_3 + 0xb4);
      puVar3 = (undefined4 *)(*(int *)(param_1 + 0xa4) + iVar2 * 0xc);
      do {
        puVar14 = (undefined4 *)(iVar11 + iVar9);
        puVar7 = (undefined4 *)(iVar8 + iVar12 * 0x10);
        iVar12 = iVar12 + 1;
        puVar15 = (undefined4 *)(iVar13 + iVar5);
        uVar1 = puVar14[1];
        uVar4 = puVar14[2];
        iVar9 = iVar9 + 0xc;
        iVar5 = iVar5 + 0x10;
        *puVar3 = *puVar14;
        puVar3[1] = uVar1;
        puVar3[2] = uVar4;
        puVar3 = puVar3 + 3;
        uVar1 = puVar7[1];
        uVar4 = puVar7[2];
        uVar6 = puVar7[3];
        *puVar15 = *puVar7;
        puVar15[1] = uVar1;
        puVar15[2] = uVar4;
        puVar15[3] = uVar6;
      } while (iVar12 != iVar10);
    }
  }
  iVar10 = *(int *)(param_2 + 0xc0);
  if (0 < iVar10) {
    iVar11 = 0;
    iVar8 = *(int *)(param_2 + 200);
    iVar5 = 0;
    iVar12 = *(int *)(param_1 + 200);
    do {
      puVar3 = (undefined4 *)(iVar8 + iVar11);
      puVar14 = (undefined4 *)(iVar12 + iVar11);
      iVar5 = iVar5 + 1;
      iVar11 = iVar11 + 0x30;
      uVar1 = puVar3[1];
      uVar4 = puVar3[2];
      uVar6 = puVar3[3];
      *puVar14 = *puVar3;
      puVar14[1] = uVar1;
      puVar14[2] = uVar4;
      puVar14[3] = uVar6;
      uVar1 = puVar3[5];
      uVar4 = puVar3[6];
      uVar6 = puVar3[7];
      puVar14[4] = puVar3[4];
      puVar14[5] = uVar1;
      puVar14[6] = uVar4;
      puVar14[7] = uVar6;
      uVar1 = puVar3[9];
      uVar4 = puVar3[10];
      uVar6 = puVar3[0xb];
      puVar14[8] = puVar3[8];
      puVar14[9] = uVar1;
      puVar14[10] = uVar4;
      puVar14[0xb] = uVar6;
    } while (iVar5 != iVar10);
  }
  iVar11 = *(int *)(param_3 + 0xc0);
  if (0 < iVar11) {
    iVar5 = 0;
    puVar14 = *(undefined4 **)(param_3 + 200);
    puVar3 = (undefined4 *)(*(int *)(param_1 + 200) + iVar10 * 0x30);
    do {
      uVar1 = puVar14[1];
      uVar4 = puVar14[2];
      uVar6 = puVar14[3];
      *puVar3 = *puVar14;
      puVar3[1] = uVar1;
      puVar3[2] = uVar4;
      puVar3[3] = uVar6;
      uVar1 = puVar14[5];
      uVar4 = puVar14[6];
      uVar6 = puVar14[7];
      puVar3[4] = puVar14[4];
      puVar3[5] = uVar1;
      puVar3[6] = uVar4;
      puVar3[7] = uVar6;
      uVar1 = puVar14[9];
      uVar4 = puVar14[10];
      uVar6 = puVar14[0xb];
      puVar3[8] = puVar14[8];
      puVar3[9] = uVar1;
      puVar3[10] = uVar4;
      puVar3[0xb] = uVar6;
      iVar10 = 0;
      do {
        iVar8 = iVar10 + 2;
        *(short *)((int)puVar3 + iVar10 + 2) = (short)iVar2 + *(short *)((int)puVar14 + iVar10 + 2);
        iVar10 = iVar8;
      } while (iVar8 != 8);
      iVar5 = iVar5 + 1;
      puVar14 = puVar14 + 0xc;
      puVar3 = puVar3 + 0xc;
    } while (iVar5 != iVar11);
  }
  return;
}
