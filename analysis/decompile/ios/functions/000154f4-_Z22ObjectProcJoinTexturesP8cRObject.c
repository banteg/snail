/*
 * mangled: _Z22ObjectProcJoinTexturesP8cRObject
 * demangled: ObjectProcJoinTextures(cRObject*)
 * address: 000154f4
 * size: 320
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
  int iVar14;
  int iVar15;
  int iVar16;
  int *piVar17;
  int *piVar18;
  int iVar19;
  int iVar20;
  int iVar21;

  iVar1 = *(int *)(param_1 + 200);
  iVar8 = *(int *)(param_1 + 0xc0);
  if (0 < iVar8) {
    iVar3 = 0;
    do {
      iVar20 = iVar3 + 1;
      iVar21 = *(int *)(iVar3 * 0x30 + iVar1 + 0xc);
      iVar19 = iVar3 + 1;
      if (iVar8 <= iVar20) {
        return;
      }
      iVar2 = iVar3;
      piVar18 = (int *)(iVar20 * 0x30 + iVar1 + 0xc);
      iVar3 = iVar20;
LAB_0001556c:
      do {
        if (*piVar18 == iVar21) {
          if (iVar3 != iVar19) {
            iVar19 = iVar19 + 1;
            piVar17 = (int *)(iVar1 + 0x30 + iVar2 * 0x30);
            iVar8 = *piVar17;
            iVar4 = piVar17[1];
            iVar9 = piVar17[2];
            iVar13 = piVar17[3];
            iVar20 = piVar17[4];
            iVar5 = piVar17[5];
            iVar10 = piVar17[6];
            iVar14 = piVar17[7];
            iVar2 = piVar17[8];
            iVar6 = piVar17[9];
            iVar11 = piVar17[10];
            iVar15 = piVar17[0xb];
            iVar7 = piVar18[-2];
            iVar12 = piVar18[-1];
            iVar16 = *piVar18;
            *piVar17 = piVar18[-3];
            piVar17[1] = iVar7;
            piVar17[2] = iVar12;
            piVar17[3] = iVar16;
            iVar7 = piVar18[2];
            iVar12 = piVar18[3];
            iVar16 = piVar18[4];
            piVar17[4] = piVar18[1];
            piVar17[5] = iVar7;
            piVar17[6] = iVar12;
            piVar17[7] = iVar16;
            iVar7 = piVar18[6];
            iVar12 = piVar18[7];
            iVar16 = piVar18[8];
            piVar17[8] = piVar18[5];
            piVar17[9] = iVar7;
            piVar17[10] = iVar12;
            piVar17[0xb] = iVar16;
            piVar18[-3] = iVar8;
            piVar18[-2] = iVar4;
            piVar18[-1] = iVar9;
            *piVar18 = iVar13;
            piVar18[1] = iVar20;
            piVar18[2] = iVar5;
            piVar18[3] = iVar10;
            piVar18[4] = iVar14;
            piVar18[5] = iVar2;
            piVar18[6] = iVar6;
            piVar18[7] = iVar11;
            piVar18[8] = iVar15;
            iVar20 = iVar3 + 1;
            iVar8 = *(int *)(param_1 + 0xc0);
            iVar2 = iVar3;
            piVar18 = piVar18 + 0xc;
            iVar3 = iVar20;
            if (iVar8 <= iVar19) break;
            goto LAB_0001556c;
          }
          iVar2 = iVar3;
          iVar3 = iVar3 + 1;
        }
        iVar19 = iVar19 + 1;
        piVar18 = piVar18 + 0xc;
      } while (iVar19 < iVar8);
    } while (iVar3 < iVar8);
  }
  return;
}
