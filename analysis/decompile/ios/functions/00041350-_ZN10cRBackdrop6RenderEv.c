/*
 * mangled: _ZN10cRBackdrop6RenderEv
 * demangled: cRBackdrop::Render()
 * address: 00041350
 * size: 692
 */

/* cRBackdrop::Render() */

void __thiscall cRBackdrop::Render(cRBackdrop *this)

{
  float fVar1;
  float fVar2;
  uint *puVar3;
  uint uVar4;
  cRTexture *pcVar5;
  float *pfVar6;
  int iVar7;
  int iVar8;
  cGLVertexUV *pcVar9;
  float *pfVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  ulonglong uVar17;

  if (this[0x34] == (cRBackdrop)0x0) {
    fVar14 = *(float *)(this + 0x13c8);
    uVar17 = (ulonglong)
             (uint)((*(float *)(this + 0x2c) / *(float *)(this + 0x2c) + fVar14 * -2.0) / 10.0);
    fVar2 = (fVar14 * -2.0 + *(float *)(this + 0x30) / *(float *)(this + 0x30)) / 10.0;
  }
  else {
    if (((&DAT_003594e4)[*(int *)(this + 0x50) * 0x1ac + *(int *)PTR__Game_001b60b8] == '\0') ||
       ((fVar14 = *(float *)(*(int *)PTR__Game_001b60b8 + 0x3c), fVar14 != 0.0 && (fVar14 != 180.0))
       )) {
      fVar14 = (float)RShellGetScreenHeight();
      fVar15 = -2.0;
      uVar17 = CONCAT44(0x41200000,
                        (fVar14 / *(float *)(this + 0x2c) + *(float *)(this + 0x13c8) * -2.0) / 10.0
                       );
      fVar2 = (float)RShellGetScreenWidth();
    }
    else {
      fVar14 = (float)RShellGetScreenWidth();
      fVar15 = -2.0;
      uVar17 = CONCAT44(0x41200000,
                        (fVar14 / *(float *)(this + 0x2c) + *(float *)(this + 0x13c8) * -2.0) / 10.0
                       );
      fVar2 = (float)RShellGetScreenHeight();
    }
    fVar14 = *(float *)(this + 0x13c8);
    fVar2 = (fVar2 / *(float *)(this + 0x30) + fVar14 * fVar15) / (float)(uVar17 >> 0x20);
  }
  fVar16 = (float)uVar17;
  iVar8 = 0;
  puVar3 = (uint *)cRSpriteManager::GetTexture((cRSpriteManager *)PTR__gRSpriteManager_001b61e4,7);
  fVar15 = 0.0;
  uVar4 = *puVar3;
  pfVar6 = *(float **)(this + 0x40);
  do {
    fVar13 = 0.0;
    pfVar10 = pfVar6 + 0x37;
    fVar12 = fVar14 + fVar16 * fVar15;
    fVar11 = fVar15 * 64.0 * 0.5;
    if ((uVar4 & 0x40000) == 0) {
      do {
        *pfVar6 = fVar11;
        iVar7 = (int)fVar15 * 0x28 + (int)fVar13 * 0x1b8;
        pfVar6[1] = fVar13 * 48.0;
        pfVar6[3] = *(float *)(this + iVar7 + 0x80) / 640.0 + fVar12;
        fVar1 = fVar2 * fVar13;
        fVar13 = fVar13 + 1.0;
        pfVar6[4] = (1.0 - (fVar14 + fVar1)) + *(float *)(this + iVar7 + 0x84) / 640.0;
        pfVar6 = pfVar6 + 5;
      } while (pfVar6 != pfVar10);
    }
    else {
      do {
        *pfVar6 = fVar11;
        pfVar6[1] = fVar13 * 48.0;
        fVar1 = fVar2 * fVar13;
        iVar7 = (int)fVar15 * 0x28 + (int)fVar13 * 0x1b8;
        pfVar6[3] = *(float *)(this + iVar7 + 0x80) / 640.0 + fVar12;
        fVar13 = fVar13 + 1.0;
        pfVar6[4] = fVar14 + fVar1 + *(float *)(this + iVar7 + 0x84) / 640.0;
        pfVar6 = pfVar6 + 5;
      } while (pfVar6 != pfVar10);
    }
    iVar8 = iVar8 + 1;
    fVar15 = fVar15 + 1.0;
    pfVar6 = pfVar10;
  } while (iVar8 != 0xb);
  pcVar9 = *(cGLVertexUV **)(this + 0x40);
  uVar4 = *(uint *)(this + 0x48);
  iVar8 = *(int *)(this + 0x3c);
  pcVar5 = (cRTexture *)
           cRSpriteManager::GetTexture((cRSpriteManager *)PTR__gRSpriteManager_001b61e4,7);
  G0RenderBackdrop(pcVar9,uVar4,iVar8,pcVar5);
  return;
}
