/*
 * mangled: _Z22ObjectProcJoinTexturesP8cRObject
 * demangled: ObjectProcJoinTextures(cRObject*)
 * address: 00033490
 * size: 292
 */

/* ObjectProcJoinTextures(cRObject*) */

void ObjectProcJoinTextures(cRObject *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int *piVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  int *piVar19;
  int iVar20;
  int iVar21;
  int iVar22;

  iVar20 = *(int *)(param_1 + 0xc0);
  iVar1 = *(int *)(param_1 + 200);
  if (0 < iVar20) {
    iVar13 = 0;
    do {
      iVar22 = iVar13 + 1;
      iVar21 = *(int *)(iVar1 + iVar13 * 0x30 + 0xc);
      if (iVar20 <= iVar22) {
        return;
      }
      piVar19 = (int *)(iVar1 + iVar22 * 0x30 + 0xc);
      do {
        while (*piVar19 != iVar21) {
LAB_000334e4:
          iVar22 = iVar22 + 1;
          piVar19 = piVar19 + 0xc;
          if (iVar22 == iVar20) goto LAB_0003359c;
        }
        iVar13 = iVar13 + 1;
        if (iVar13 == iVar22) goto LAB_000334e4;
        iVar22 = iVar22 + 1;
        piVar14 = (int *)(iVar1 + iVar13 * 0x30);
        iVar2 = *piVar14;
        iVar5 = piVar14[1];
        iVar9 = piVar14[2];
        iVar15 = piVar14[3];
        iVar3 = piVar14[4];
        iVar6 = piVar14[5];
        iVar10 = piVar14[6];
        iVar16 = piVar14[7];
        iVar4 = piVar14[8];
        iVar7 = piVar14[9];
        iVar11 = piVar14[10];
        iVar17 = piVar14[0xb];
        iVar8 = piVar19[-2];
        iVar12 = piVar19[-1];
        iVar18 = *piVar19;
        *piVar14 = piVar19[-3];
        piVar14[1] = iVar8;
        piVar14[2] = iVar12;
        piVar14[3] = iVar18;
        iVar8 = piVar19[2];
        iVar12 = piVar19[3];
        iVar18 = piVar19[4];
        piVar14[4] = piVar19[1];
        piVar14[5] = iVar8;
        piVar14[6] = iVar12;
        piVar14[7] = iVar18;
        iVar8 = piVar19[6];
        iVar12 = piVar19[7];
        iVar18 = piVar19[8];
        piVar14[8] = piVar19[5];
        piVar14[9] = iVar8;
        piVar14[10] = iVar12;
        piVar14[0xb] = iVar18;
        piVar19[-3] = iVar2;
        piVar19[-2] = iVar5;
        piVar19[-1] = iVar9;
        *piVar19 = iVar15;
        piVar19[1] = iVar3;
        piVar19[2] = iVar6;
        piVar19[3] = iVar10;
        piVar19[4] = iVar16;
        piVar19[5] = iVar4;
        piVar19[6] = iVar7;
        piVar19[7] = iVar11;
        piVar19[8] = iVar17;
        piVar19 = piVar19 + 0xc;
      } while (iVar22 != iVar20);
LAB_0003359c:
      iVar13 = iVar13 + 1;
    } while (iVar13 < iVar20);
  }
  return;
}
