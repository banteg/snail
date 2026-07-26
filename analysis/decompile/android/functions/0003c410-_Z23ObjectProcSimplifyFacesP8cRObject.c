/*
 * mangled: _Z23ObjectProcSimplifyFacesP8cRObject
 * demangled: ObjectProcSimplifyFaces(cRObject*)
 * address: 0003c410
 * size: 764
 */

/* ObjectProcSimplifyFaces(cRObject*) */

void ObjectProcSimplifyFaces(cRObject *param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 uVar7;
  int iVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  int local_74;
  uint local_48;
  uint local_44;
  uint local_40;
  uint local_3c;
  uint local_38;
  uint local_34;
  uint local_30;
  uint local_2c;

  iVar1 = *(int *)(param_1 + 0xc0);
  iVar4 = *(int *)(param_1 + 200);
  if (0 < iVar1) {
    local_74 = 0;
    do {
      iVar8 = local_74 + 1;
      if (iVar1 <= iVar8) {
        return;
      }
      do {
        puVar9 = (undefined4 *)(iVar4 + iVar8 * 0x30);
        local_40 = (uint)*(ushort *)((int)puVar9 + 6);
        local_48 = (uint)*(ushort *)((int)puVar9 + 2);
        puVar10 = (undefined4 *)(iVar4 + local_74 * 0x30);
        local_44 = (uint)*(ushort *)(puVar9 + 1);
        local_38 = (uint)*(ushort *)((int)puVar10 + 2);
        local_34 = (uint)*(ushort *)(puVar10 + 1);
        local_30 = (uint)*(ushort *)((int)puVar10 + 6);
        local_3c = (uint)*(ushort *)(puVar9 + 2);
        local_2c = (uint)*(ushort *)(puVar10 + 2);
        if ((local_34 + local_38 + local_30 + local_2c == local_44 + local_48 + local_40 + local_3c)
           && (iVar2 = local_34 * (local_38 + 1) + local_38 + 1,
              iVar6 = local_44 * (local_48 + 1) + local_48 + 1, iVar2 = local_30 * iVar2 + iVar2,
              iVar6 = local_40 * iVar6 + iVar6, local_2c * iVar2 + iVar2 == local_3c * iVar6 + iVar6
              )) {
          qsort(&local_38,4,4,ObjectProcVertexCompare);
          qsort(&local_48,4,4,ObjectProcVertexCompare);
          if ((local_38 == local_48) &&
             (((local_34 == local_44 && (local_30 == local_40)) && (local_2c == local_3c)))) {
            iVar1 = *(int *)(param_1 + 0xc0) + -1;
            if (iVar8 < iVar1) {
              puVar11 = (undefined4 *)((iVar8 + 1) * 0x30 + iVar4);
              do {
                iVar8 = iVar8 + 1;
                uVar3 = puVar11[1];
                uVar5 = puVar11[2];
                uVar7 = puVar11[3];
                *puVar9 = *puVar11;
                puVar9[1] = uVar3;
                puVar9[2] = uVar5;
                puVar9[3] = uVar7;
                uVar3 = puVar11[5];
                uVar5 = puVar11[6];
                uVar7 = puVar11[7];
                puVar9[4] = puVar11[4];
                puVar9[5] = uVar3;
                puVar9[6] = uVar5;
                puVar9[7] = uVar7;
                uVar3 = puVar11[9];
                uVar5 = puVar11[10];
                uVar7 = puVar11[0xb];
                puVar9[8] = puVar11[8];
                puVar9[9] = uVar3;
                puVar9[10] = uVar5;
                puVar9[0xb] = uVar7;
                puVar11 = puVar11 + 0xc;
                puVar9 = puVar9 + 0xc;
              } while (iVar8 < iVar1);
            }
            if (local_74 < iVar1) {
              iVar8 = local_74;
              puVar9 = (undefined4 *)((local_74 + 1) * 0x30 + iVar4);
              do {
                iVar8 = iVar8 + 1;
                uVar3 = puVar9[1];
                uVar5 = puVar9[2];
                uVar7 = puVar9[3];
                *puVar10 = *puVar9;
                puVar10[1] = uVar3;
                puVar10[2] = uVar5;
                puVar10[3] = uVar7;
                uVar3 = puVar9[5];
                uVar5 = puVar9[6];
                uVar7 = puVar9[7];
                puVar10[4] = puVar9[4];
                puVar10[5] = uVar3;
                puVar10[6] = uVar5;
                puVar10[7] = uVar7;
                uVar3 = puVar9[9];
                uVar5 = puVar9[10];
                uVar7 = puVar9[0xb];
                puVar10[8] = puVar9[8];
                puVar10[9] = uVar3;
                puVar10[10] = uVar5;
                puVar10[0xb] = uVar7;
                puVar10 = puVar10 + 0xc;
                puVar9 = puVar9 + 0xc;
              } while (iVar8 < iVar1);
            }
            *(int *)(param_1 + 0xc0) = iVar1;
            local_74 = local_74 + -1;
            iVar8 = iVar1;
          }
          else {
            wprintf("Gotcha %i %i %i %i == %i %i %i %i\n",(uint)*(ushort *)((int)puVar10 + 2),
                    (uint)*(ushort *)(puVar10 + 1),(uint)*(ushort *)((int)puVar10 + 6),
                    (uint)*(ushort *)(puVar10 + 2),(uint)*(ushort *)((int)puVar9 + 2),
                    (uint)*(ushort *)(puVar9 + 1),(uint)*(ushort *)((int)puVar9 + 6),
                    (uint)*(ushort *)(puVar9 + 2));
            iVar1 = *(int *)(param_1 + 0xc0);
          }
        }
        iVar8 = iVar8 + 1;
      } while (iVar8 < iVar1);
      local_74 = local_74 + 1;
    } while (local_74 < iVar1);
  }
  return;
}
