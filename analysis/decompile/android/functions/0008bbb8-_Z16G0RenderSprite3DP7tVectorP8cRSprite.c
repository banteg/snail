/*
 * mangled: _Z16G0RenderSprite3DP7tVectorP8cRSprite
 * demangled: G0RenderSprite3D(tVector*, cRSprite*)
 * address: 0008bbb8
 * size: 832
 */

/* G0RenderSprite3D(tVector*, cRSprite*) */

void G0RenderSprite3D(tVector *param_1,cRSprite *param_2)

{
  int iVar1;
  float *pfVar2;
  float *pfVar3;
  undefined1 uVar4;
  int iVar5;
  uint uVar6;
  bool bVar7;
  float fVar8;
  float extraout_s0;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  undefined4 local_44;

  tColourSmall::tColourSmall((tColourSmall *)&local_44);
  fVar8 = (float)tColourSmall::operator=((tColourSmall *)&local_44,(tColour *)(param_2 + 0x2c));
  uVar6 = *(uint *)(param_2 + 4);
  fVar14 = *(float *)(param_2 + 0x68);
  bVar7 = (uVar6 & 0x1000) != 0;
  fVar13 = *(float *)param_1;
  fVar11 = *(float *)(param_1 + 8);
  fVar12 = *(float *)(param_1 + 4);
  fVar17 = *(float *)(param_2 + 0x60);
  fVar16 = *(float *)(param_2 + 100);
  if (bVar7) {
    uVar6 = 0xffffffff;
  }
  fVar15 = 1.0 - fVar14;
  if (bVar7) {
    uVar4 = (undefined1)uVar6;
  }
  else {
    uVar6 = (uint)(fVar15 * *(float *)(param_2 + 0x38) * 255.0);
    if ((uVar6 & 0xff) < 0x1e) {
      return;
    }
    uVar4 = (undefined1)uVar6;
  }
  local_44 = CONCAT13(uVar4,(undefined3)local_44);
  if ((((*(int *)(*(int *)(param_2 + 0x1c) + 0x8c) != BufferTexture) || (local_44 != BufferColour))
      || (*(int *)(param_2 + 0x28) != BufferBlendMode)) || (0xfd < BufferCount)) {
    G0RenderBufferRender();
    G0RenderBufferInit();
    BufferColour = local_44;
    BufferBlendMode = *(int *)(param_2 + 0x28);
    BufferTexture = *(int *)(*(int *)(param_2 + 0x1c) + 0x8c);
    G0BindTexture(BufferTexture);
    G0SetColour((tColourSmall *)&local_44);
    fVar8 = (float)G0SetBlend(*(int *)(param_2 + 0x28));
  }
  pfVar3 = BufferSPA;
  BufferCount = BufferCount + 1;
  fVar14 = fVar14 * fVar16 + fVar17 * fVar15;
  if (*(float *)(param_2 + 0x7c) == 0.0) {
    iVar5 = *(int *)(param_2 + 0x98) * 2 + 1;
    iVar1 = *(int *)(param_2 + 0x98) * 0x20;
    fVar17 = *(float *)(gSpriteReference + iVar5 * 0x10 + 4);
    fVar16 = *(float *)(gSpriteReference + iVar1 + 0x18);
    fVar8 = *(float *)(gSpriteReference + iVar1 + 0x1c);
    fVar15 = *(float *)(gSpriteReference + iVar5 * 0x10);
    BufferSPA[2] = fVar11;
    BufferSPA[3] = fVar15;
    BufferSPA[4] = fVar8;
    BufferSPA[7] = fVar11;
    BufferSPA[9] = fVar8;
    BufferSPA[8] = fVar16;
    BufferSPA[0xd] = fVar16;
    BufferSPA[0xe] = fVar17;
    BufferSPA[0xc] = fVar11;
    pfVar2 = BufferSPA + 0x13;
    BufferSPA = BufferSPA + 0x14;
    *pfVar2 = fVar17;
    pfVar3[0x11] = fVar11;
    pfVar3[0x12] = fVar15;
    pfVar3[10] = fVar14 + fVar13;
    pfVar3[5] = fVar14 + fVar13;
    pfVar3[0xf] = fVar13 - fVar14;
    *pfVar3 = fVar13 - fVar14;
    pfVar3[1] = fVar14 + fVar12;
    pfVar3[6] = fVar14 + fVar12;
    pfVar3[0xb] = fVar12 - fVar14;
    pfVar3[0x10] = fVar12 - fVar14;
  }
  else {
    fVar8 = (float)Cos(fVar8);
    fVar8 = fVar14 * 1.414 * fVar8;
    fVar16 = (float)Sin(extraout_s0);
    pfVar2 = BufferSPA;
    iVar1 = *(int *)(param_2 + 0x98) * 0x20;
    iVar5 = (*(int *)(param_2 + 0x98) * 2 + 1) * 0x10;
    fVar10 = *(float *)(gSpriteReference + iVar1 + 0x18);
    fVar17 = *(float *)(gSpriteReference + iVar5 + 4);
    fVar15 = *(float *)(gSpriteReference + iVar5);
    fVar9 = *(float *)(gSpriteReference + iVar1 + 0x1c);
    BufferSPA[3] = fVar15;
    BufferSPA[8] = fVar10;
    BufferSPA[0xd] = fVar10;
    BufferSPA[4] = fVar9;
    BufferSPA[9] = fVar9;
    BufferSPA[2] = fVar11;
    BufferSPA[0xe] = fVar17;
    BufferSPA[7] = fVar11;
    BufferSPA[0xc] = fVar11;
    pfVar3 = BufferSPA + 5;
    BufferSPA = BufferSPA + 0x14;
    *pfVar3 = fVar8 + fVar13;
    fVar16 = fVar14 * 1.414 * fVar16;
    pfVar2[1] = fVar8 + fVar12;
    *pfVar2 = fVar13 - fVar16;
    pfVar2[6] = fVar16 + fVar12;
    pfVar2[0xb] = fVar12 - fVar8;
    pfVar2[10] = fVar16 + fVar13;
    fVar14 = *(float *)(param_2 + 0x84);
    pfVar2[0x13] = fVar17;
    pfVar2[0x11] = fVar11;
    pfVar2[0x12] = fVar15;
    pfVar2[0x10] = fVar12 - fVar16 * fVar14;
    pfVar2[0xf] = fVar13 - fVar8 * fVar14;
  }
  return;
}
