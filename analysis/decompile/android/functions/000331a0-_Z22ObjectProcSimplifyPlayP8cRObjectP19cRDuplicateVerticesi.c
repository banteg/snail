/*
 * mangled: _Z22ObjectProcSimplifyPlayP8cRObjectP19cRDuplicateVerticesi
 * demangled: ObjectProcSimplifyPlay(cRObject*, cRDuplicateVertices*, int)
 * address: 000331a0
 * size: 736
 */

/* ObjectProcSimplifyPlay(cRObject*, cRDuplicateVertices*, int) */

void ObjectProcSimplifyPlay(cRObject *param_1,cRDuplicateVertices *param_2,int param_3)

{
  bool bVar1;
  undefined2 *puVar2;
  short sVar3;
  ushort uVar4;
  undefined4 uVar5;
  uint uVar6;
  int iVar7;
  undefined4 uVar8;
  uint uVar9;
  int iVar10;
  undefined4 uVar11;
  uint uVar12;
  int iVar13;
  short *psVar14;
  undefined4 *puVar15;
  int iVar16;
  undefined4 *puVar17;
  int iVar18;
  uint uVar19;
  undefined4 *puVar20;
  int iVar21;
  int iVar22;
  int iVar23;
  uint uVar24;
  undefined4 *puVar25;

  iVar21 = *(int *)param_2;
  if (0 < iVar21) {
    iVar13 = 0;
    iVar18 = *(int *)(param_2 + 4);
    iVar7 = 0;
    do {
      iVar10 = iVar18 + iVar13;
      iVar7 = iVar7 + 1;
      *(undefined2 *)(iVar10 + 6) = *(undefined2 *)(iVar10 + 2);
      puVar2 = (undefined2 *)(iVar18 + iVar13);
      iVar13 = iVar13 + 10;
      *(undefined2 *)(iVar10 + 4) = *puVar2;
    } while (iVar7 != iVar21);
    iVar7 = 1;
    do {
      if (*(short *)(iVar18 + 8) == param_3) {
        uVar4 = *(ushort *)(iVar18 + 4);
        uVar24 = (uint)*(short *)(iVar18 + 6);
        if (((short)uVar4 != -1 && uVar24 != 0xffffffff) && ((int)(short)uVar4 < (int)uVar24)) {
          if (iVar7 < iVar21) {
            psVar14 = (short *)(iVar18 + 0xe);
            iVar13 = iVar7;
            do {
              sVar3 = *psVar14;
              if ((int)uVar24 < (int)sVar3) {
                *psVar14 = sVar3 + -1;
              }
              else if (uVar24 == (int)sVar3) {
                *psVar14 = -1;
              }
              sVar3 = psVar14[1];
              if ((int)uVar24 < (int)sVar3) {
                psVar14[1] = sVar3 + -1;
              }
              else if (uVar24 == (int)sVar3) {
                psVar14[1] = -1;
              }
              iVar13 = iVar13 + 1;
              psVar14 = psVar14 + 5;
            } while (iVar13 != iVar21);
          }
          iVar13 = *(int *)(param_1 + 0xa0) + -1;
          if ((int)uVar24 < iVar13) {
            iVar10 = *(int *)(param_1 + 0xa4);
            if ((*(uint *)param_1 & 0x10000) == 0) {
              puVar20 = (undefined4 *)(iVar10 + uVar24 * 0xc);
              puVar15 = (undefined4 *)(iVar10 + (uVar24 + 1) * 0xc);
              iVar10 = 0;
              do {
                uVar5 = *puVar15;
                uVar8 = puVar15[1];
                uVar11 = puVar15[2];
                iVar10 = iVar10 + 1;
                puVar15 = puVar15 + 3;
                *puVar20 = uVar5;
                puVar20[1] = uVar8;
                puVar20[2] = uVar11;
                puVar20 = puVar20 + 3;
              } while (iVar10 != iVar13 - uVar24);
            }
            else {
              iVar22 = (uVar24 + 1) * 0x10;
              iVar16 = *(int *)(param_1 + 0xb4);
              puVar20 = (undefined4 *)(iVar10 + uVar24 * 0xc);
              iVar23 = uVar24 << 4;
              puVar15 = (undefined4 *)(iVar10 + (uVar24 + 1) * 0xc);
              iVar10 = 0;
              do {
                uVar5 = *puVar15;
                uVar8 = puVar15[1];
                uVar11 = puVar15[2];
                puVar17 = (undefined4 *)(iVar16 + iVar22);
                iVar10 = iVar10 + 1;
                puVar25 = (undefined4 *)(iVar16 + iVar23);
                puVar15 = puVar15 + 3;
                iVar23 = iVar23 + 0x10;
                iVar22 = iVar22 + 0x10;
                *puVar20 = uVar5;
                puVar20[1] = uVar8;
                puVar20[2] = uVar11;
                puVar20 = puVar20 + 3;
                uVar5 = puVar17[1];
                uVar8 = puVar17[2];
                uVar11 = puVar17[3];
                *puVar25 = *puVar17;
                puVar25[1] = uVar5;
                puVar25[2] = uVar8;
                puVar25[3] = uVar11;
              } while (iVar10 != iVar13 - uVar24);
            }
          }
          iVar10 = *(int *)(param_1 + 0xc0);
          *(int *)(param_1 + 0xa0) = iVar13;
          iVar13 = *(int *)(param_1 + 200);
          if (0 < iVar10) {
            iVar23 = 0;
            iVar22 = 0;
            do {
              iVar16 = iVar13 + iVar23;
              iVar22 = iVar22 + 1;
              iVar23 = iVar23 + 0x30;
              uVar19 = (uint)*(ushort *)(iVar16 + 2);
              uVar6 = (uint)*(ushort *)(iVar16 + 4);
              uVar9 = (uint)*(ushort *)(iVar16 + 6);
              uVar12 = (uint)*(ushort *)(iVar16 + 8);
              if (uVar19 == uVar24) {
                uVar19 = (uint)uVar4;
                *(ushort *)(iVar16 + 2) = uVar4;
              }
              if (uVar6 == uVar24) {
                uVar6 = (uint)uVar4;
                *(ushort *)(iVar16 + 4) = uVar4;
              }
              if (uVar9 == uVar24) {
                *(ushort *)(iVar16 + 6) = uVar4;
                uVar9 = (uint)uVar4;
              }
              if (uVar12 == uVar24) {
                uVar12 = (uint)uVar4;
                *(ushort *)(iVar16 + 8) = uVar4;
              }
              if ((int)uVar24 < (int)uVar19) {
                *(short *)(iVar16 + 2) = (short)uVar19 + -1;
              }
              if ((int)uVar24 < (int)uVar6) {
                *(short *)(iVar16 + 4) = (short)uVar6 + -1;
              }
              if ((int)uVar24 < (int)uVar9) {
                *(short *)(iVar16 + 6) = (short)uVar9 + -1;
              }
              if ((int)uVar24 < (int)uVar12) {
                *(short *)(iVar16 + 8) = (short)uVar12 + -1;
              }
            } while (iVar22 != iVar10);
          }
        }
      }
      bVar1 = iVar7 < iVar21;
      iVar7 = iVar7 + 1;
      iVar18 = iVar18 + 10;
    } while (bVar1);
  }
  return;
}
