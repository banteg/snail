/*
 * mangled: _Z16G0RenderSprite3DP7tVectorP8cRSprite
 * demangled: G0RenderSprite3D(tVector*, cRSprite*)
 * address: 000705ac
 * size: 1056
 */

/* G0RenderSprite3D(tVector*, cRSprite*) */

void G0RenderSprite3D(tVector *param_1,cRSprite *param_2)

{
  float *pfVar1;
  undefined1 uVar2;
  uint uVar3;
  int iVar4;
  float fVar5;
  uint uVar6;
  uint uVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  bool bVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  undefined4 local_3c;

  tColourSmall::tColourSmall((tColourSmall *)&local_3c);
  tColourSmall::operator=((tColourSmall *)&local_3c,(tColour *)(param_2 + 0x2c));
  uVar6 = *(uint *)(param_2 + 4);
  fVar12 = *(float *)(param_2 + 0x68);
  bVar11 = (uVar6 & 0x1000) != 0;
  if (bVar11) {
    uVar6 = 0xffffffff;
  }
  fVar8 = *(float *)(param_1 + 8);
  fVar15 = *(float *)(param_1 + 4);
  fVar14 = *(float *)param_1;
  fVar17 = *(float *)(param_2 + 0x60);
  fVar13 = 1.0 - fVar12;
  fVar16 = *(float *)(param_2 + 100);
  if (bVar11) {
    uVar2 = (undefined1)uVar6;
  }
  else {
    uVar6 = (uint)(fVar13 * *(float *)(param_2 + 0x38) * 255.0);
    uVar2 = (undefined1)uVar6;
    if ((uVar6 & 0xff) < 0x1e) {
      return;
    }
  }
  local_3c = CONCAT13(uVar2,(undefined3)local_3c);
  uVar7 = *(uint *)(*(int *)(param_2 + 0x1c) + 0x8c);
  uVar6 = _BufferTexture;
  uVar3 = uVar7;
  if (uVar7 == _BufferTexture) {
    uVar6 = _BufferColour;
    uVar3 = local_3c;
  }
  if (((uVar7 != _BufferTexture || uVar3 != uVar6) || (*(int *)(param_2 + 0x28) != _BufferBlendMode)
      ) || (0xfd < _BufferCount)) {
    if (0 < _BufferCount) {
      _glDrawElements(5,_BufferCount * 6,0x1403,0);
    }
    _BufferTexture = 0xffffffff;
    _BufferCount = 0;
    _BufferColour = 0;
    _BufferUVArray = (float *)RShellMemoryScratch();
    _BufferBlendMode = 0xffffffff;
    _BufferSPA = _BufferUVArray;
    _glVertexPointer(3,0x1406,0x14,_BufferUVArray);
    _glTexCoordPointer(2,0x1406,0x14,_BufferUVArray + 3);
    _glBindBuffer(0x8893,_gSpriteIndexArrayVBO);
    _BufferColour = local_3c;
    _BufferTexture = *(uint *)(*(int *)(param_2 + 0x1c) + 0x8c);
    _BufferBlendMode = *(int *)(param_2 + 0x28);
    G0BindTexture(*(int *)(*(int *)(param_2 + 0x1c) + 0x8c));
    if (_GLColour != local_3c) {
      _GLColour = local_3c;
      _glColor4ub(local_3c._2_1_,local_3c._1_1_,local_3c & 0xff,local_3c._3_1_);
    }
    G0SetBlend(*(int *)(param_2 + 0x28));
  }
  _BufferCount = _BufferCount + 1;
  fVar12 = fVar12 * fVar16 + fVar17 * fVar13;
  if (*(float *)(param_2 + 0x7c) == 0.0) {
    iVar4 = *(int *)(param_2 + 0x98);
    fVar10 = *(float *)(PTR__gSpriteReference_001b61c8 + iVar4 * 0x20 + 0x14);
    fVar9 = *(float *)(PTR__gSpriteReference_001b61c8 + iVar4 * 0x20 + 0x10);
    fVar13 = *(float *)(PTR__gSpriteReference_001b61c8 + iVar4 * 0x20 + 0x18);
    fVar16 = *(float *)(PTR__gSpriteReference_001b61c8 + iVar4 * 0x20 + 0x1c);
    *_BufferSPA = fVar14 - fVar12;
    _BufferSPA[1] = fVar12 + fVar15;
    _BufferSPA[2] = fVar8;
    _BufferSPA[3] = fVar9;
    _BufferSPA[4] = fVar16;
    pfVar1 = _BufferSPA + 5;
    _BufferSPA = _BufferSPA + 5;
    *pfVar1 = fVar12 + fVar14;
    _BufferSPA[1] = fVar12 + fVar15;
    _BufferSPA[2] = fVar8;
    _BufferSPA[3] = fVar13;
    _BufferSPA[4] = fVar16;
    pfVar1 = _BufferSPA + 5;
    _BufferSPA = _BufferSPA + 5;
    *pfVar1 = fVar12 + fVar14;
    _BufferSPA[1] = fVar15 - fVar12;
    _BufferSPA[2] = fVar8;
    _BufferSPA[3] = fVar13;
    _BufferSPA[4] = fVar10;
    pfVar1 = _BufferSPA + 5;
    _BufferSPA = _BufferSPA + 5;
    *pfVar1 = fVar14 - fVar12;
    _BufferSPA[1] = fVar15 - fVar12;
  }
  else {
    fVar16 = 0.7853982;
    fVar12 = fVar12 * 1.414;
    fVar13 = (float)Cos(*(float *)(param_2 + 0x7c) + 0.7853982);
    fVar13 = fVar12 * fVar13;
    fVar16 = (float)Sin(*(float *)(param_2 + 0x7c) + fVar16);
    iVar4 = *(int *)(param_2 + 0x98);
    fVar9 = *(float *)(PTR__gSpriteReference_001b61c8 + iVar4 * 0x20 + 0x10);
    fVar10 = *(float *)(PTR__gSpriteReference_001b61c8 + iVar4 * 0x20 + 0x14);
    fVar5 = *(float *)(PTR__gSpriteReference_001b61c8 + iVar4 * 0x20 + 0x1c);
    fVar17 = *(float *)(PTR__gSpriteReference_001b61c8 + iVar4 * 0x20 + 0x18);
    fVar12 = fVar12 * fVar16;
    *_BufferSPA = fVar14 - fVar12;
    _BufferSPA[1] = fVar13 + fVar15;
    _BufferSPA[2] = fVar8;
    _BufferSPA[3] = fVar9;
    _BufferSPA[4] = fVar5;
    pfVar1 = _BufferSPA + 5;
    _BufferSPA = _BufferSPA + 5;
    *pfVar1 = fVar13 + fVar14;
    _BufferSPA[1] = fVar12 + fVar15;
    _BufferSPA[2] = fVar8;
    _BufferSPA[3] = fVar17;
    _BufferSPA[4] = fVar5;
    pfVar1 = _BufferSPA + 5;
    _BufferSPA = _BufferSPA + 5;
    *pfVar1 = fVar12 + fVar14;
    _BufferSPA[1] = fVar15 - fVar13;
    _BufferSPA[2] = fVar8;
    _BufferSPA[3] = fVar17;
    _BufferSPA[4] = fVar10;
    pfVar1 = _BufferSPA + 5;
    _BufferSPA = _BufferSPA + 5;
    *pfVar1 = fVar14 - fVar13 * *(float *)(param_2 + 0x84);
    _BufferSPA[1] = fVar15 - fVar12 * *(float *)(param_2 + 0x84);
  }
  _BufferSPA[2] = fVar8;
  _BufferSPA[3] = fVar9;
  _BufferSPA[4] = fVar10;
  _BufferSPA = _BufferSPA + 5;
  return;
}
