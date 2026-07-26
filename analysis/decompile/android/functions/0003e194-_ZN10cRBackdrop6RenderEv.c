/*
 * mangled: _ZN10cRBackdrop6RenderEv
 * demangled: cRBackdrop::Render()
 * address: 0003e194
 * size: 688
 */

/* cRBackdrop::Render() */

void __thiscall cRBackdrop::Render(cRBackdrop *this)

{
  float fVar1;
  uint *puVar2;
  cRTexture *pcVar3;
  int iVar4;
  cGLVertexUV *pcVar5;
  int iVar6;
  cGLVertexUV *pcVar7;
  int iVar8;
  uint uVar9;
  uint in_fpscr;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;

  fVar20 = (float)VectorSignedToFloat(*(undefined4 *)(this + 0x3c),(byte)(in_fpscr >> 0x16) & 3);
  if (this[0x34] == (cRBackdrop)0x0) {
    fVar13 = (float)RShellGetScreenWidth();
    fVar16 = (float)RShellGetScreenHeight();
    fVar18 = *(float *)(this + 0xf0);
    fVar17 = fVar18 * -2.0 + *(float *)(this + 0x30) / *(float *)(this + 0x30);
    fVar15 = *(float *)(this + 0x2c) / *(float *)(this + 0x2c) + fVar18 * -2.0;
    goto LAB_0003e23c;
  }
  if (gSegmentText[*(int *)(this + 0x5c) * 0x1ac + Game + 0x4e4] == '\0') {
LAB_0003e1ec:
    fVar13 = 320.0;
    fVar15 = 480.0 / *(float *)(this + 0x2c);
    fVar16 = *(float *)(this + 0x30);
    fVar18 = *(float *)(this + 0xf0);
  }
  else {
    uVar9 = in_fpscr & 0xfffffff;
    in_fpscr = uVar9 | (uint)(*(float *)(Game + 0x3c) == 0.0) << 0x1e;
    if ((!SUB41(in_fpscr >> 0x1e,0)) &&
       (in_fpscr = uVar9 | (uint)(*(float *)(Game + 0x3c) == 180.0) << 0x1e,
       !SUB41(in_fpscr >> 0x1e,0))) goto LAB_0003e1ec;
    fVar13 = 480.0;
    fVar15 = 320.0 / *(float *)(this + 0x2c);
    fVar16 = *(float *)(this + 0x30);
    fVar18 = *(float *)(this + 0xf0);
  }
  fVar17 = fVar18 * -2.0 + fVar13 / fVar16;
  fVar15 = fVar15 + fVar18 * -2.0;
  fVar13 = (float)RShellGetScreenWidth();
  fVar16 = (float)RShellGetScreenHeight();
  fVar18 = *(float *)(this + 0xf0);
LAB_0003e23c:
  puVar2 = (uint *)cRSpriteManager::GetTexture((cRSpriteManager *)&gRSpriteManager,7);
  fVar14 = (float)VectorSignedToFloat(*(int *)(this + 0x3c),(byte)(in_fpscr >> 0x16) & 3);
  pcVar7 = *(cGLVertexUV **)(this + 0x44);
  uVar9 = *puVar2;
  if (0.0 <= fVar14) {
    iVar8 = *(int *)(this + 0x7c);
    iVar6 = *(int *)(this + 0x3c) + 1;
    fVar10 = 0.0;
    pcVar5 = pcVar7;
    do {
      while( true ) {
        fVar11 = fVar10 * (fVar13 / fVar20);
        fVar12 = fVar18 + (fVar15 / fVar20) * fVar10;
        if ((uVar9 & 0x40000) != 0) break;
        fVar19 = 0.0;
        do {
          *(float *)pcVar5 = fVar11;
          iVar4 = iVar8 + (iVar6 * (int)fVar19 + (int)fVar10) * 0x28;
          *(float *)(pcVar5 + 4) = fVar19 * (fVar16 / fVar20);
          *(float *)(pcVar5 + 0xc) = fVar12 + *(float *)(iVar4 + 0x10) / 640.0;
          fVar1 = (fVar17 / fVar20) * fVar19;
          fVar19 = fVar19 + 1.0;
          *(float *)(pcVar5 + 0x10) = (1.0 - (fVar18 + fVar1)) + *(float *)(iVar4 + 0x14) / 640.0;
          pcVar5 = pcVar5 + 0x14;
        } while (fVar19 <= fVar14);
        fVar10 = fVar10 + 1.0;
        if (fVar14 < fVar10) goto LAB_0003e318;
      }
      fVar19 = 0.0;
      do {
        *(float *)pcVar5 = fVar11;
        iVar4 = iVar8 + (iVar6 * (int)fVar19 + (int)fVar10) * 0x28;
        *(float *)(pcVar5 + 4) = fVar19 * (fVar16 / fVar20);
        *(float *)(pcVar5 + 0xc) = fVar12 + *(float *)(iVar4 + 0x10) / 640.0;
        fVar1 = (fVar17 / fVar20) * fVar19;
        fVar19 = fVar19 + 1.0;
        *(float *)(pcVar5 + 0x10) = fVar18 + fVar1 + *(float *)(iVar4 + 0x14) / 640.0;
        pcVar5 = pcVar5 + 0x14;
      } while (fVar19 <= fVar14);
      fVar10 = fVar10 + 1.0;
    } while (fVar10 <= fVar14);
  }
LAB_0003e318:
  iVar6 = *(int *)(this + 0x40);
  uVar9 = *(uint *)(this + 0x4c);
  pcVar3 = (cRTexture *)cRSpriteManager::GetTexture((cRSpriteManager *)&gRSpriteManager,7);
  G0RenderBackdrop(pcVar7,uVar9,iVar6,pcVar3);
  return;
}
