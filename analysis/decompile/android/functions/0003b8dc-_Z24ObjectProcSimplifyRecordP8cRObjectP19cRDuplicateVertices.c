/*
 * mangled: _Z24ObjectProcSimplifyRecordP8cRObjectP19cRDuplicateVertices
 * demangled: ObjectProcSimplifyRecord(cRObject*, cRDuplicateVertices*)
 * address: 0003b8dc
 * size: 328
 */

/* ObjectProcSimplifyRecord(cRObject*, cRDuplicateVertices*) */

void ObjectProcSimplifyRecord(cRObject *param_1,cRDuplicateVertices *param_2)

{
  float *pfVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  float fVar12;
  float fVar13;
  float fVar14;

  iVar10 = 0;
  iVar4 = *(int *)(param_1 + 0xa0);
  iVar11 = 0;
  iVar9 = 0;
  if (0 < iVar4) {
    do {
      iVar8 = iVar9 + 1;
      iVar3 = *(int *)(param_1 + 0xa4);
      pfVar1 = (float *)(iVar3 + iVar11);
      if (iVar4 <= iVar8) {
        iVar11 = iVar11 + 0xc;
      }
      fVar13 = pfVar1[2];
      fVar14 = pfVar1[1];
      fVar12 = *pfVar1;
      if (iVar8 < iVar4) {
        iVar11 = iVar11 + 0xc;
        iVar7 = iVar8 * 0x10;
        iVar5 = iVar11;
        iVar6 = iVar8;
        do {
          pfVar1 = (float *)(iVar3 + iVar5);
          if (((*pfVar1 == fVar12) && (fVar13 == pfVar1[2])) && (fVar14 == pfVar1[1])) {
            if ((*(uint *)param_1 & 0x10000) != 0) {
              pfVar1 = (float *)(*(int *)(param_1 + 0xb4) + iVar10);
              pfVar2 = (float *)(*(int *)(param_1 + 0xb4) + iVar7);
              if (((*pfVar1 != *pfVar2) || (pfVar1[1] != pfVar2[1])) ||
                 ((pfVar1[2] != pfVar2[2] || (pfVar1[3] != pfVar2[3])))) goto LAB_0003b9f4;
            }
            cRDuplicateVertices::Add(param_2,iVar9,iVar6);
            iVar4 = *(int *)(param_1 + 0xa0);
          }
LAB_0003b9f4:
          iVar6 = iVar6 + 1;
          iVar5 = iVar5 + 0xc;
          iVar7 = iVar7 + 0x10;
          if (iVar4 <= iVar6) break;
          iVar3 = *(int *)(param_1 + 0xa4);
        } while( true );
      }
      iVar10 = iVar10 + 0x10;
      iVar9 = iVar8;
    } while (iVar8 < iVar4);
  }
  return;
}
