/*
 * mangled: _Z10FontMake3Ds
 * demangled: FontMake3D(short)
 * address: 00031fcc
 * size: 396
 */

/* FontMake3D(short) */

void FontMake3D(short param_1)

{
  int iVar1;
  cRObject *pcVar2;
  undefined4 uVar3;
  uint *puVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  float *pfVar8;
  undefined1 *puVar9;
  int iVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;

  iVar5 = param_1 * 0xa28;
  if (0 < *(int *)(RFont + iVar5)) {
    puVar9 = RFont3D;
    pfVar8 = (float *)(RFont + iVar5 + 0x808);
    iVar10 = 0;
    do {
      fVar14 = *pfVar8 / *(float *)(RFont + iVar5 + 0xa08);
      pcVar2 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
      cRBod::SetObject((cRBod *)(RFont3D + iVar10 * 0x2c),pcVar2);
      iVar1 = iVar10 * 4;
      ObjectTextLoad("Objects/Font3D",*(cRObject **)(puVar9 + 0x24));
      puVar4 = *(uint **)(puVar9 + 0x24);
      *(undefined4 *)(puVar9 + 0x1c) = 0;
      *(undefined4 *)(puVar9 + 0x20) = 0;
      uVar3 = *(undefined4 *)(RFont + iVar5 + 4);
      fVar12 = pfVar8[-0x200];
      uVar6 = puVar4[0x32];
      iVar10 = iVar10 + 1;
      *puVar4 = *puVar4 | 0x100002;
      *(float *)(uVar6 + 0x10) = fVar12;
      fVar11 = pfVar8[-0x180];
      *(undefined4 *)(uVar6 + 0xc) = uVar3;
      *(float *)(uVar6 + 0x14) = 1.0 - fVar11;
      fVar13 = pfVar8[-0x100];
      *(float *)(uVar6 + 0x1c) = 1.0 - fVar11;
      *(float *)(uVar6 + 0x20) = fVar13;
      *(float *)(uVar6 + 0x18) = fVar13;
      fVar11 = pfVar8[-0x80];
      *(float *)(uVar6 + 0x28) = fVar12;
      pfVar8 = pfVar8 + 1;
      *(float *)(uVar6 + 0x2c) = 1.0 - fVar11;
      *(float *)(uVar6 + 0x24) = 1.0 - fVar11;
      iVar7 = *(int *)(puVar9 + 0x24);
      puVar9 = puVar9 + 0x2c;
      *(float *)puVar4[0x29] = *(float *)puVar4[0x29] * fVar14;
      *(float *)(*(int *)(iVar7 + 0xa4) + 0xc) = *(float *)(*(int *)(iVar7 + 0xa4) + 0xc) * fVar14;
      *(float *)(*(int *)(iVar7 + 0xa4) + 0x18) = *(float *)(*(int *)(iVar7 + 0xa4) + 0x18) * fVar14
      ;
      *(float *)(*(int *)(iVar7 + 0xa4) + 0x24) = *(float *)(*(int *)(iVar7 + 0xa4) + 0x24) * fVar14
      ;
      *(undefined4 *)(iVar7 + 8) = 1;
      *(float *)(RFont3D + iVar1 + 0x1600) = fVar14;
    } while (iVar10 < *(int *)(RFont + iVar5));
  }
  return;
}
