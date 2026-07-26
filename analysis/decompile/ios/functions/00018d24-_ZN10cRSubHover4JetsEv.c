/*
 * mangled: _ZN10cRSubHover4JetsEv
 * demangled: cRSubHover::Jets()
 * address: 00018d24
 * size: 952
 */

/* cRSubHover::Jets() */

void __thiscall cRSubHover::Jets(cRSubHover *this)

{
  uint uVar1;
  byte bVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  cRSubHover *pcVar7;
  int iVar8;
  uint in_fpscr;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  undefined4 local_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;

  if ((*(int *)(this + 0xc) == 1) &&
     (*(int *)(*(int *)(this + 0x200) + 0x12dcc) ==
      *(int *)(*(int *)(*(int *)(this + 0x200) + 0x12e2c) + 0x104))) {
    uVar3 = gRMathRand2();
    fVar11 = 3.0517578e-05;
    fVar12 = 0.05;
    fVar17 = 0.12;
    iVar8 = 0;
    fVar9 = (float)VectorSignedToFloat(uVar3,(byte)(in_fpscr >> 0x16) & 3);
    fVar16 = fVar9 * 3.0517578e-05 * 0.05 + 0.4;
    uVar3 = gRMathRand2();
    fVar9 = (float)VectorSignedToFloat(uVar3,(byte)(in_fpscr >> 0x16) & 3);
    fVar17 = fVar17 + fVar9 * fVar11 * fVar12;
    pcVar7 = this;
    do {
      fVar15 = 1.0;
      iVar5 = *(int *)(this + 0x200);
      fVar11 = (float)VectorSignedToFloat(iVar8,(byte)(in_fpscr >> 0x16) & 3);
      iVar4 = *(int *)(this + 0x10);
      fVar11 = fVar11 / 14.0;
      fVar14 = *(float *)(this + 0x210) * fVar17 * (1.0 - fVar11);
      fVar9 = -(*(float *)(this + 0x210) * fVar11) * fVar16;
      fVar12 = *(float *)(iVar5 + 0x132d0) + fVar9 * *(float *)(&DAT_00002844 + iVar4);
      fVar13 = *(float *)(iVar5 + 0x132d4) + fVar9 * *(float *)(&DAT_00002848 + iVar4);
      iVar6 = *(int *)(pcVar7 + 0x20);
      fVar9 = *(float *)(iVar5 + 0x132d8) + fVar9 * *(float *)(&DAT_0000284c + iVar4);
      *(float *)(iVar6 + 100) = fVar14;
      *(float *)(iVar6 + 0x60) = fVar14;
      iVar4 = *(int *)(pcVar7 + 0x20);
      *(float *)(iVar4 + 0x50) = fVar9;
      *(float *)(iVar4 + 0x4c) = fVar13;
      *(float *)(iVar4 + 0x48) = fVar12;
      if (iVar8 == 0xe) {
        uVar3 = gRMathRand2();
        fVar10 = (float)VectorSignedToFloat(uVar3,(byte)(in_fpscr >> 0x16) & 3);
        fVar10 = fVar10 * 3.0517578e-05;
        uVar1 = in_fpscr & 0xfffffff | (uint)(fVar10 < 0.9) << 0x1f | (uint)(fVar10 == 0.9) << 0x1e;
        in_fpscr = uVar1 | (uint)NAN(fVar10) << 0x1c;
        bVar2 = (byte)(uVar1 >> 0x18);
        if (!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(in_fpscr >> 0x1c) & 1)) {
          iVar4 = cRSpriteManager::New
                            ((int)PTR__gRSpriteManager_001b61e4,
                             *(int *)(*(int *)(this + 0x200) + 0xf7b8),0x13,-1);
          *(undefined4 *)(iVar4 + 0x6c) = 0x3e0e38e4;
          *(uint *)(iVar4 + 4) = *(uint *)(iVar4 + 4) | 0x800;
          *(undefined4 *)(iVar4 + 0x68) = 0;
          *(undefined4 *)(iVar4 + 0x70) = 0;
          *(undefined4 *)(iVar4 + 0x74) = 0;
          tColour::tColour((tColour *)&local_4c,fVar15,fVar15,fVar15,fVar15);
          *(undefined4 *)(iVar4 + 0x2c) = local_4c;
          *(undefined4 *)(iVar4 + 0x30) = uStack_48;
          *(undefined4 *)(iVar4 + 0x34) = uStack_44;
          *(undefined4 *)(iVar4 + 0x38) = uStack_40;
          *(undefined4 *)(iVar4 + 0x60) = 0x3dcccccd;
          *(undefined4 *)(iVar4 + 100) = 0x3e99999a;
          iVar5 = *(int *)(this + 0x200);
          fVar15 = *(float *)(iVar5 + 0xf848);
          *(float *)(iVar4 + 0x48) = fVar12;
          fVar12 = *(float *)(iVar5 + 0xf84c);
          *(float *)(iVar4 + 0x4c) = fVar13;
          fVar13 = *(float *)(iVar5 + 0xf850);
          *(float *)(iVar4 + 0x54) = fVar15 * 0.85;
          *(float *)(iVar4 + 0x50) = fVar9;
          *(undefined4 *)(iVar4 + 0x78) = 0x3a83126f;
          *(float *)(iVar4 + 0x58) = fVar12 * 0.85;
          *(float *)(iVar4 + 0x5c) = fVar13 * 0.85;
        }
      }
      iVar5 = *(int *)(this + 0x200);
      iVar4 = *(int *)(this + 0x10);
      fVar9 = -(*(float *)(this + 0x210) * fVar11) * fVar16;
      fVar11 = *(float *)(iVar5 + 0x132dc) + fVar9 * *(float *)(&DAT_00002844 + iVar4);
      fVar12 = *(float *)(iVar5 + 0x132e0) + fVar9 * *(float *)(&DAT_00002848 + iVar4);
      iVar6 = *(int *)(pcVar7 + 0x30);
      fVar9 = *(float *)(iVar5 + 0x132e4) + fVar9 * *(float *)(&DAT_0000284c + iVar4);
      *(float *)(iVar6 + 100) = fVar14;
      *(float *)(iVar6 + 0x60) = fVar14;
      iVar4 = *(int *)(pcVar7 + 0x30);
      *(float *)(iVar4 + 0x50) = fVar9;
      *(float *)(iVar4 + 0x4c) = fVar12;
      *(float *)(iVar4 + 0x48) = fVar11;
      if (iVar8 == 0xe) {
        uVar3 = gRMathRand2();
        fVar13 = (float)VectorSignedToFloat(uVar3,(byte)(in_fpscr >> 0x16) & 3);
        fVar13 = fVar13 * 3.0517578e-05;
        uVar1 = in_fpscr & 0xfffffff | (uint)(fVar13 < 0.9) << 0x1f | (uint)(fVar13 == 0.9) << 0x1e;
        in_fpscr = uVar1 | (uint)NAN(fVar13) << 0x1c;
        bVar2 = (byte)(uVar1 >> 0x18);
        if (!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(in_fpscr >> 0x1c) & 1)) {
          iVar8 = cRSpriteManager::New
                            ((int)PTR__gRSpriteManager_001b61e4,
                             *(int *)(*(int *)(this + 0x200) + 0xf7b8),0x13,-1);
          *(undefined4 *)(iVar8 + 0x6c) = 0x3e0e38e4;
          *(uint *)(iVar8 + 4) = *(uint *)(iVar8 + 4) | 0x800;
          *(undefined4 *)(iVar8 + 0x68) = 0;
          *(undefined4 *)(iVar8 + 0x70) = 0;
          *(undefined4 *)(iVar8 + 0x74) = 0;
          tColour::tColour((tColour *)&local_4c,1.0,1.0,1.0,1.0);
          *(undefined4 *)(iVar8 + 0x2c) = local_4c;
          *(undefined4 *)(iVar8 + 0x30) = uStack_48;
          *(undefined4 *)(iVar8 + 0x34) = uStack_44;
          *(undefined4 *)(iVar8 + 0x38) = uStack_40;
          *(undefined4 *)(iVar8 + 0x60) = 0x3dcccccd;
          *(undefined4 *)(iVar8 + 100) = 0x3e99999a;
          iVar4 = *(int *)(this + 0x200);
          fVar16 = *(float *)(iVar4 + 0xf848);
          fVar17 = *(float *)(iVar4 + 0xf84c);
          *(float *)(iVar8 + 0x4c) = fVar12;
          *(float *)(iVar8 + 0x48) = fVar11;
          fVar11 = *(float *)(iVar4 + 0xf850);
          *(undefined4 *)(iVar8 + 0x78) = 0x3a83126f;
          *(float *)(iVar8 + 0x54) = fVar16 * 0.85;
          *(float *)(iVar8 + 0x50) = fVar9;
          *(float *)(iVar8 + 0x58) = fVar17 * 0.85;
          *(float *)(iVar8 + 0x5c) = fVar11 * 0.85;
          return;
        }
      }
      iVar8 = iVar8 + 1;
      pcVar7 = pcVar7 + 0x20;
    } while (iVar8 != 0xf);
  }
  return;
}
