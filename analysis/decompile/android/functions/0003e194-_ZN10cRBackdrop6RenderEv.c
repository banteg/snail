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
  float fVar2;
  int iVar3;
  float fVar4;
  uint *puVar5;
  cRTexture *pcVar6;
  int iVar7;
  cGLVertexUV *pcVar8;
  int iVar9;
  int iVar10;
  cGLVertexUV *pcVar11;
  int iVar12;
  uint uVar13;
  uint in_fpscr;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;

  iVar10 = DAT_0003e460 + 0x3e1b8;
  fVar24 = (float)VectorSignedToFloat(*(undefined4 *)(this + 0x3c),(byte)(in_fpscr >> 0x16) & 3);
  if (this[0x34] == (cRBackdrop)0x0) {
    fVar4 = (float)RShellGetScreenWidth();
    fVar19 = (float)RShellGetScreenHeight();
    fVar21 = *(float *)(this + 0xf0);
    fVar20 = fVar21 * DAT_0003e44c + *(float *)(this + 0x30) / *(float *)(this + 0x30);
    fVar18 = *(float *)(this + 0x2c) / *(float *)(this + 0x2c) + fVar21 * DAT_0003e44c;
    goto LAB_0003e23c;
  }
  if (gSegmentText[*(int *)(this + 0x5c) * 0x1ac + **(int **)(iVar10 + DAT_0003e464) + 0x4e4] ==
      '\0') {
LAB_0003e1ec:
    fVar18 = DAT_0003e444 / *(float *)(this + 0x2c);
    fVar19 = *(float *)(this + 0x30);
    fVar21 = *(float *)(this + 0xf0);
    fVar4 = DAT_0003e448;
  }
  else {
    fVar4 = *(float *)(**(int **)(iVar10 + DAT_0003e464) + 0x3c);
    uVar13 = in_fpscr & 0xfffffff;
    in_fpscr = uVar13 | (uint)(fVar4 == 0.0) << 0x1e;
    if ((!SUB41(in_fpscr >> 0x1e,0)) &&
       (in_fpscr = uVar13 | (uint)(fVar4 == DAT_0003e45c) << 0x1e, !SUB41(in_fpscr >> 0x1e,0)))
    goto LAB_0003e1ec;
    fVar18 = DAT_0003e448 / *(float *)(this + 0x2c);
    fVar19 = *(float *)(this + 0x30);
    fVar21 = *(float *)(this + 0xf0);
    fVar4 = DAT_0003e444;
  }
  fVar20 = DAT_0003e44c * fVar21 + fVar4 / fVar19;
  fVar18 = fVar18 + DAT_0003e44c * fVar21;
  fVar4 = (float)RShellGetScreenWidth();
  fVar19 = (float)RShellGetScreenHeight();
  fVar21 = *(float *)(this + 0xf0);
LAB_0003e23c:
  iVar3 = DAT_0003e468;
  puVar5 = (uint *)cRSpriteManager::GetTexture(*(cRSpriteManager **)(iVar10 + DAT_0003e468),7);
  fVar2 = DAT_0003e458;
  fVar1 = DAT_0003e454;
  fVar17 = (float)VectorSignedToFloat(*(int *)(this + 0x3c),(byte)(in_fpscr >> 0x16) & 3);
  pcVar11 = *(cGLVertexUV **)(this + 0x44);
  uVar13 = *puVar5;
  if (0.0 <= fVar17) {
    iVar12 = *(int *)(this + 0x7c);
    iVar9 = *(int *)(this + 0x3c) + 1;
    pcVar8 = pcVar11;
    fVar14 = DAT_0003e450;
    do {
      while( true ) {
        fVar15 = fVar14 * (fVar4 / fVar24);
        fVar16 = fVar21 + (fVar18 / fVar24) * fVar14;
        fVar23 = DAT_0003e450;
        if ((uVar13 & 0x40000) != 0) break;
        do {
          *(float *)pcVar8 = fVar15;
          iVar7 = iVar12 + (iVar9 * (int)fVar23 + (int)fVar14) * 0x28;
          *(float *)(pcVar8 + 4) = fVar23 * (fVar19 / fVar24);
          *(float *)(pcVar8 + 0xc) = fVar16 + *(float *)(iVar7 + 0x10) / fVar1;
          fVar22 = fVar23 + fVar2;
          *(float *)(pcVar8 + 0x10) =
               (fVar2 - (fVar21 + (fVar20 / fVar24) * fVar23)) + *(float *)(iVar7 + 0x14) / fVar1;
          pcVar8 = pcVar8 + 0x14;
          fVar23 = fVar22;
        } while (fVar22 <= fVar17);
        fVar14 = fVar14 + fVar2;
        if (fVar17 < fVar14) goto LAB_0003e318;
      }
      do {
        *(float *)pcVar8 = fVar15;
        iVar7 = iVar12 + (iVar9 * (int)fVar23 + (int)fVar14) * 0x28;
        *(float *)(pcVar8 + 4) = fVar23 * (fVar19 / fVar24);
        *(float *)(pcVar8 + 0xc) = fVar16 + *(float *)(iVar7 + 0x10) / fVar1;
        fVar22 = fVar23 + fVar2;
        *(float *)(pcVar8 + 0x10) =
             fVar21 + (fVar20 / fVar24) * fVar23 + *(float *)(iVar7 + 0x14) / fVar1;
        pcVar8 = pcVar8 + 0x14;
        fVar23 = fVar22;
      } while (fVar22 <= fVar17);
      fVar14 = fVar14 + fVar2;
    } while (fVar14 <= fVar17);
  }
LAB_0003e318:
  iVar9 = *(int *)(this + 0x40);
  uVar13 = *(uint *)(this + 0x4c);
  pcVar6 = (cRTexture *)cRSpriteManager::GetTexture(*(cRSpriteManager **)(iVar10 + iVar3),7);
  G0RenderBackdrop(pcVar11,uVar13,iVar9,pcVar6);
  return;
}
