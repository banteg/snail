/*
 * mangled: _Z18ObjectProcSimplifyP8cRObject
 * demangled: ObjectProcSimplify(cRObject*)
 * address: 0003bd68
 * size: 760
 */

/* ObjectProcSimplify(cRObject*) */

void ObjectProcSimplify(cRObject *param_1)

{
  undefined2 uVar1;
  float *pfVar2;
  float fVar3;
  uint uVar4;
  float *pfVar5;
  float fVar6;
  uint uVar7;
  undefined4 uVar8;
  int iVar9;
  float fVar10;
  uint uVar11;
  undefined4 uVar12;
  float *pfVar13;
  int iVar14;
  undefined4 *puVar15;
  undefined4 uVar16;
  int iVar17;
  uint uVar18;
  uint uVar19;
  uint uVar20;
  int iVar21;
  int iVar22;
  int iVar23;
  uint uVar24;
  undefined4 *puVar25;
  float fVar26;
  float fVar27;
  float fVar28;
  int local_40;
  int local_30;

  iVar17 = *(int *)(param_1 + 0xa0);
  local_40 = 0;
  local_30 = 0;
  uVar18 = 0;
  if (0 < iVar17) {
    do {
      uVar19 = uVar18 + 1;
      iVar9 = *(int *)(param_1 + 0xa4);
      pfVar13 = (float *)(iVar9 + local_40);
      fVar27 = pfVar13[2];
      fVar26 = pfVar13[1];
      fVar28 = *pfVar13;
      if ((int)uVar19 < iVar17) {
        uVar24 = uVar19;
        do {
          pfVar13 = (float *)(iVar9 + uVar24 * 0xc);
          if (((*pfVar13 == fVar28) && (fVar27 == pfVar13[2])) && (fVar26 == pfVar13[1])) {
            if ((*(uint *)param_1 & 0x10000) != 0) {
              pfVar2 = (float *)(*(int *)(param_1 + 0xb4) + uVar18 * 0x10);
              pfVar5 = (float *)(*(int *)(param_1 + 0xb4) + uVar24 * 0x10);
              if (((*pfVar2 != *pfVar5) || (pfVar2[1] != pfVar5[1])) ||
                 ((pfVar2[2] != pfVar5[2] || (pfVar2[3] != pfVar5[3])))) goto LAB_0003bfa8;
            }
            iVar17 = iVar17 + -1;
            local_30 = local_30 + 1;
            if ((int)uVar24 < iVar17) {
              if ((*(uint *)param_1 & 0x10000) == 0) {
                pfVar2 = (float *)(iVar9 + (uVar24 + 1) * 0xc);
                uVar20 = uVar24;
                do {
                  fVar3 = *pfVar2;
                  fVar6 = pfVar2[1];
                  fVar10 = pfVar2[2];
                  uVar20 = uVar20 + 1;
                  pfVar2 = pfVar2 + 3;
                  *pfVar13 = fVar3;
                  pfVar13[1] = fVar6;
                  pfVar13[2] = fVar10;
                  pfVar13 = pfVar13 + 3;
                } while ((int)uVar20 < iVar17);
              }
              else {
                iVar21 = *(int *)(param_1 + 0xb4);
                iVar23 = uVar24 << 4;
                pfVar2 = (float *)(iVar9 + (uVar24 + 1) * 0xc);
                iVar9 = (uVar24 + 1) * 0x10;
                uVar20 = uVar24;
                do {
                  fVar3 = *pfVar2;
                  fVar6 = pfVar2[1];
                  fVar10 = pfVar2[2];
                  puVar15 = (undefined4 *)(iVar21 + iVar9);
                  uVar20 = uVar20 + 1;
                  puVar25 = (undefined4 *)(iVar21 + iVar23);
                  pfVar2 = pfVar2 + 3;
                  iVar23 = iVar23 + 0x10;
                  iVar9 = iVar9 + 0x10;
                  *pfVar13 = fVar3;
                  pfVar13[1] = fVar6;
                  pfVar13[2] = fVar10;
                  pfVar13 = pfVar13 + 3;
                  uVar8 = puVar15[1];
                  uVar12 = puVar15[2];
                  uVar16 = puVar15[3];
                  *puVar25 = *puVar15;
                  puVar25[1] = uVar8;
                  puVar25[2] = uVar12;
                  puVar25[3] = uVar16;
                } while ((int)uVar20 < iVar17);
              }
            }
            iVar9 = *(int *)(param_1 + 0xc0);
            *(int *)(param_1 + 0xa0) = iVar17;
            iVar23 = *(int *)(param_1 + 200);
            if (0 < iVar9) {
              iVar21 = 0;
              iVar22 = 0;
              do {
                iVar14 = iVar23 + iVar21;
                iVar22 = iVar22 + 1;
                iVar21 = iVar21 + 0x30;
                uVar20 = (uint)*(ushort *)(iVar14 + 2);
                uVar4 = (uint)*(ushort *)(iVar14 + 4);
                uVar7 = (uint)*(ushort *)(iVar14 + 6);
                uVar11 = (uint)*(ushort *)(iVar14 + 8);
                uVar1 = (undefined2)uVar18;
                if (uVar20 == uVar24) {
                  uVar20 = uVar18 & 0xffff;
                  *(undefined2 *)(iVar14 + 2) = uVar1;
                }
                if (uVar4 == uVar24) {
                  uVar4 = uVar18 & 0xffff;
                  *(undefined2 *)(iVar14 + 4) = uVar1;
                }
                if (uVar7 == uVar24) {
                  *(undefined2 *)(iVar14 + 6) = uVar1;
                  uVar7 = uVar18 & 0xffff;
                }
                if (uVar11 == uVar24) {
                  uVar11 = uVar18 & 0xffff;
                  *(undefined2 *)(iVar14 + 8) = uVar1;
                }
                if ((int)uVar24 < (int)uVar20) {
                  *(short *)(iVar14 + 2) = (short)uVar20 + -1;
                }
                if ((int)uVar24 < (int)uVar4) {
                  *(short *)(iVar14 + 4) = (short)uVar4 + -1;
                }
                if ((int)uVar24 < (int)uVar7) {
                  *(short *)(iVar14 + 6) = (short)uVar7 + -1;
                }
                if ((int)uVar24 < (int)uVar11) {
                  *(short *)(iVar14 + 8) = (short)uVar11 + -1;
                }
              } while (iVar22 != iVar9);
            }
            if (iVar17 <= (int)uVar24) break;
          }
          else {
LAB_0003bfa8:
            iVar17 = *(int *)(param_1 + 0xa0);
            uVar24 = uVar24 + 1;
            if (iVar17 <= (int)uVar24) break;
          }
          iVar9 = *(int *)(param_1 + 0xa4);
        } while( true );
      }
      local_40 = local_40 + 0xc;
      uVar18 = uVar19;
    } while ((int)uVar19 < iVar17);
  }
  if (local_30 < 0x65) {
    return;
  }
  wprintf("Vertex pairs %i\n",local_30);
  return;
}
