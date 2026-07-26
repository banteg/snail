/*
 * mangled: _Z23ObjectProcSimplifyFacesP8cRObject
 * demangled: ObjectProcSimplifyFaces(cRObject*)
 * address: 000166c0
 * size: 732
 */

/* ObjectProcSimplifyFaces(cRObject*) */

void ObjectProcSimplifyFaces(cRObject *param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 *puVar8;
  int iVar9;
  int iVar10;
  int local_58;
  int local_44;
  uint local_40;
  uint local_3c;
  uint local_38;
  uint local_34;
  uint local_30;
  uint local_2c;
  uint local_28;
  uint local_24;

  iVar3 = *(int *)(param_1 + 200);
  local_58 = *(int *)(param_1 + 0xc0);
  if (0 < local_58) {
    local_44 = 0;
    do {
      iVar10 = local_44 + 1;
      if (local_58 <= iVar10) {
        return;
      }
      do {
        while( true ) {
          iVar7 = local_44 * 0x30 + iVar3;
          local_30 = (uint)*(ushort *)(iVar7 + 2);
          iVar9 = iVar10 * 0x30 + iVar3;
          iVar6 = iVar10;
          if ((*(ushort *)(iVar7 + 4) + local_30 + (uint)*(ushort *)(iVar7 + 6) +
               (uint)*(ushort *)(iVar7 + 8) !=
               (uint)*(ushort *)(iVar9 + 4) + (uint)*(ushort *)(iVar9 + 2) +
               (uint)*(ushort *)(iVar9 + 6) + (uint)*(ushort *)(iVar9 + 8)) ||
             (iVar4 = (uint)*(ushort *)(iVar7 + 4) * (local_30 + 1) + local_30 + 1,
             iVar4 = (uint)*(ushort *)(iVar7 + 6) * iVar4 + iVar4,
             iVar5 = *(ushort *)(iVar9 + 2) + 1,
             iVar5 = (uint)*(ushort *)(iVar9 + 4) * iVar5 + iVar5,
             iVar5 = (uint)*(ushort *)(iVar9 + 6) * iVar5 + iVar5,
             (uint)*(ushort *)(iVar7 + 8) * iVar4 + iVar4 !=
             (uint)*(ushort *)(iVar9 + 8) * iVar5 + iVar5)) break;
          local_2c = (uint)*(ushort *)(iVar7 + 4);
          local_28 = (uint)*(ushort *)(iVar7 + 6);
          local_24 = (uint)*(ushort *)(iVar7 + 8);
          local_40 = (uint)*(ushort *)(iVar9 + 2);
          local_3c = (uint)*(ushort *)(iVar9 + 4);
          local_38 = (uint)*(ushort *)(iVar9 + 6);
          local_34 = (uint)*(ushort *)(iVar9 + 8);
          _qsort(&local_30,4,4,(int *)ObjectProcVertexCompare);
          _qsort(&local_40,4,4,(int *)ObjectProcVertexCompare);
          if (local_30 == local_40) {
            uVar1 = local_3c;
            uVar2 = local_2c;
            if (local_2c == local_3c) {
              uVar1 = local_38;
              uVar2 = local_28;
            }
            if ((local_2c == local_3c && uVar2 == uVar1) && (local_24 == local_34)) {
              iVar6 = *(int *)(param_1 + 0xc0) + -1;
              if (iVar10 < iVar6) {
                puVar8 = (undefined4 *)(iVar3 + 0x30 + iVar10 * 0x30);
                do {
                  iVar10 = iVar10 + 1;
                  puVar8[-0xc] = *puVar8;
                  puVar8[-0xb] = puVar8[1];
                  puVar8[-10] = puVar8[2];
                  puVar8[-9] = puVar8[3];
                  puVar8[-8] = puVar8[4];
                  puVar8[-7] = puVar8[5];
                  puVar8[-6] = puVar8[6];
                  puVar8[-5] = puVar8[7];
                  puVar8[-4] = puVar8[8];
                  puVar8[-3] = puVar8[9];
                  puVar8[-2] = puVar8[10];
                  puVar8[-1] = puVar8[0xb];
                  iVar6 = *(int *)(param_1 + 0xc0) + -1;
                  puVar8 = puVar8 + 0xc;
                } while (iVar10 < iVar6);
              }
              if (local_44 < iVar6) {
                puVar8 = (undefined4 *)(iVar3 + 0x30 + local_44 * 0x30);
                iVar10 = local_44;
                do {
                  iVar10 = iVar10 + 1;
                  puVar8[-0xc] = *puVar8;
                  puVar8[-0xb] = puVar8[1];
                  puVar8[-10] = puVar8[2];
                  puVar8[-9] = puVar8[3];
                  puVar8[-8] = puVar8[4];
                  puVar8[-7] = puVar8[5];
                  puVar8[-6] = puVar8[6];
                  puVar8[-5] = puVar8[7];
                  puVar8[-4] = puVar8[8];
                  puVar8[-3] = puVar8[9];
                  puVar8[-2] = puVar8[10];
                  puVar8[-1] = puVar8[0xb];
                  iVar6 = *(int *)(param_1 + 0xc0) + -1;
                  puVar8 = puVar8 + 0xc;
                } while (iVar10 < iVar6);
              }
              local_44 = local_44 + -1;
              *(int *)(param_1 + 0xc0) = iVar6;
              local_58 = iVar6;
              break;
            }
          }
          iVar10 = iVar10 + 1;
          wprintf("Gotcha %i %i %i %i == %i %i %i %i\n",(uint)*(ushort *)(iVar7 + 2),
                  (uint)*(ushort *)(iVar7 + 4),(uint)*(ushort *)(iVar7 + 6),
                  (uint)*(ushort *)(iVar7 + 8),(uint)*(ushort *)(iVar9 + 2),
                  (uint)*(ushort *)(iVar9 + 4),(uint)*(ushort *)(iVar9 + 6),
                  (uint)*(ushort *)(iVar9 + 8));
          local_58 = *(int *)(param_1 + 0xc0);
          if (local_58 <= iVar10) goto LAB_00016894;
        }
        iVar10 = iVar6 + 1;
      } while (iVar10 < local_58);
LAB_00016894:
      local_44 = local_44 + 1;
    } while (local_44 < local_58);
  }
  return;
}
