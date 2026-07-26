/*
 * mangled: _Z10FontMake3Ds
 * demangled: FontMake3D(short)
 * address: 0000eb4c
 * size: 544
 */

/* FontMake3D(short) */

void FontMake3D(short param_1)

{
  int *piVar1;
  float *pfVar2;
  int iVar3;
  cRObject *pcVar4;
  undefined *puVar5;
  float *pfVar6;
  int iVar7;
  int iVar8;
  float fVar9;

  iVar3 = param_1 * 0xa28;
  if (0 < *(int *)(&_RFont + iVar3)) {
    puVar5 = &_RFont3D;
    pfVar6 = (float *)(&DAT_0026f01c + iVar3);
    iVar7 = 0;
    do {
      fVar9 = *pfVar6 / *(float *)(&DAT_0026f21c + iVar3);
      pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)PTR__gObjectList_001b61cc);
      iVar8 = iVar7 + 1;
      cRBod::SetObject((cRBod *)(&_RFont3D + iVar7 * 0x2c),pcVar4);
      ObjectTextLoad("Objects/Font3D",*(cRObject **)(puVar5 + 0x24));
      **(uint **)(puVar5 + 0x24) = **(uint **)(puVar5 + 0x24) | 2;
      **(uint **)(puVar5 + 0x24) = **(uint **)(puVar5 + 0x24) | 0x100000;
      *(undefined4 *)(puVar5 + 0x1c) = 0;
      *(undefined4 *)(puVar5 + 0x20) = 0;
      *(undefined4 *)(*(int *)(*(int *)(puVar5 + 0x24) + 200) + 0xc) =
           *(undefined4 *)(&DAT_0026e818 + iVar3);
      *(float *)(*(int *)(*(int *)(puVar5 + 0x24) + 200) + 0x10) = pfVar6[-0x200];
      *(float *)(*(int *)(*(int *)(puVar5 + 0x24) + 200) + 0x14) = 1.0 - pfVar6[-0x180];
      *(float *)(*(int *)(*(int *)(puVar5 + 0x24) + 200) + 0x18) = pfVar6[-0x100];
      *(float *)(*(int *)(*(int *)(puVar5 + 0x24) + 200) + 0x1c) = 1.0 - pfVar6[-0x180];
      *(float *)(*(int *)(*(int *)(puVar5 + 0x24) + 200) + 0x20) = pfVar6[-0x100];
      *(float *)(*(int *)(*(int *)(puVar5 + 0x24) + 200) + 0x24) = 1.0 - pfVar6[-0x80];
      *(float *)(*(int *)(*(int *)(puVar5 + 0x24) + 200) + 0x28) = pfVar6[-0x200];
      pfVar2 = pfVar6 + -0x80;
      pfVar6 = pfVar6 + 1;
      *(float *)(*(int *)(*(int *)(puVar5 + 0x24) + 200) + 0x2c) = 1.0 - *pfVar2;
      **(float **)(*(int *)(puVar5 + 0x24) + 0xa4) =
           **(float **)(*(int *)(puVar5 + 0x24) + 0xa4) * fVar9;
      *(float *)(*(int *)(*(int *)(puVar5 + 0x24) + 0xa4) + 0xc) =
           *(float *)(*(int *)(*(int *)(puVar5 + 0x24) + 0xa4) + 0xc) * fVar9;
      *(float *)(*(int *)(*(int *)(puVar5 + 0x24) + 0xa4) + 0x18) =
           *(float *)(*(int *)(*(int *)(puVar5 + 0x24) + 0xa4) + 0x18) * fVar9;
      *(float *)(*(int *)(*(int *)(puVar5 + 0x24) + 0xa4) + 0x24) =
           *(float *)(*(int *)(*(int *)(puVar5 + 0x24) + 0xa4) + 0x24) * fVar9;
      piVar1 = (int *)(puVar5 + 0x24);
      puVar5 = puVar5 + 0x2c;
      *(undefined4 *)(*piVar1 + 8) = 1;
      (&DAT_0027083c)[iVar7] = fVar9;
      iVar7 = iVar8;
    } while (iVar8 < *(int *)(&_RFont + iVar3));
  }
  return;
}
