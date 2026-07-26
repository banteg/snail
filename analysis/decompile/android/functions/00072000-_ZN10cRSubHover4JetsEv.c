/*
 * mangled: _ZN10cRSubHover4JetsEv
 * demangled: cRSubHover::Jets()
 * address: 00072000
 * size: 732
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
  int iVar9;
  uint in_fpscr;
  float extraout_s0;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
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
  undefined4 local_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;

  if ((*(int *)(this + 0xc) == 1) &&
     (*(int *)((int)&__DT_SYMTAB[0xbb].st_value + *(int *)(this + 0x200)) ==
      *(int *)(*(int *)((int)&__DT_SYMTAB[0xc1].st_value + *(int *)(this + 0x200)) + 0x104))) {
    uVar3 = gRMathRand2();
    fVar14 = (float)VectorSignedToFloat(uVar3,(byte)(in_fpscr >> 0x16) & 3);
    uVar3 = gRMathRand2();
    fVar15 = (float)VectorSignedToFloat(uVar3,(byte)(in_fpscr >> 0x16) & 3);
    iVar9 = 0;
    do {
      fVar11 = (float)VectorSignedToFloat(iVar9,(byte)(in_fpscr >> 0x16) & 3);
      fVar16 = *(float *)(this + 0x210);
      iVar8 = iVar9 + 1;
      iVar6 = 0;
      pcVar7 = this + iVar8 * 0x20;
      fVar17 = fVar16 * (fVar15 * 3.0517578e-05 * 0.05 + 0.12) * (1.0 - fVar11 / 14.0);
      while( true ) {
        if (iVar6 == 0) {
          iVar4 = *(int *)(this + 0x200);
          fVar19 = *(float *)((int)&__DT_SYMTAB[0x10b].st_size + iVar4);
          fVar18 = *(float *)((int)&__DT_SYMTAB[0x10c].st_name + iVar4);
          fVar20 = *(float *)(&__DT_SYMTAB[0x10b].st_info + iVar4);
        }
        else {
          iVar4 = *(int *)(this + 0x200);
          fVar19 = *(float *)((int)&__DT_SYMTAB[0x10c].st_value + iVar4);
          fVar18 = *(float *)(&__DT_SYMTAB[0x10c].st_info + iVar4);
          fVar20 = *(float *)((int)&__DT_SYMTAB[0x10c].st_size + iVar4);
        }
        iVar4 = *(int *)(this + 0x10);
        fVar10 = *(float *)(iVar4 + 0x2854);
        iVar5 = *(int *)pcVar7;
        fVar12 = *(float *)(iVar4 + 0x284c);
        iVar6 = iVar6 + 1;
        fVar13 = *(float *)(iVar4 + 0x2850);
        pcVar7 = pcVar7 + 0x10;
        *(float *)(iVar5 + 100) = fVar17;
        *(float *)(iVar5 + 0x60) = fVar17;
        fVar16 = -(fVar16 * (fVar11 / 14.0)) * (fVar14 * 3.0517578e-05 * 0.05 + 0.4);
        fVar18 = fVar18 + fVar16 * fVar10;
        fVar19 = fVar19 + fVar16 * fVar12;
        *(float *)(iVar5 + 0x50) = fVar18;
        fVar20 = fVar20 + fVar16 * fVar13;
        *(float *)(iVar5 + 0x48) = fVar19;
        *(float *)(iVar5 + 0x4c) = fVar20;
        if (iVar9 == 0xe) {
          uVar3 = gRMathRand2();
          fVar16 = (float)VectorSignedToFloat(uVar3,(byte)(in_fpscr >> 0x16) & 3);
          fVar16 = fVar16 * 3.0517578e-05;
          uVar1 = in_fpscr & 0xfffffff | (uint)(fVar16 < 0.9) << 0x1f |
                  (uint)(fVar16 == 0.9) << 0x1e;
          in_fpscr = uVar1 | (uint)NAN(fVar16) << 0x1c;
          bVar2 = (byte)(uVar1 >> 0x18);
          if (!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(in_fpscr >> 0x1c) & 1)) {
            iVar4 = cRSpriteManager::New
                              ((int)&gRSpriteManager,*(int *)(*(int *)(this + 0x200) + 0xfe34),0x13,
                               -1);
            *(undefined4 *)(iVar4 + 0x68) = 0;
            *(undefined4 *)(iVar4 + 0x6c) = 0x3e0e38e4;
            *(undefined4 *)(iVar4 + 0x70) = 0;
            *(undefined4 *)(iVar4 + 0x74) = 0;
            *(uint *)(iVar4 + 4) = *(uint *)(iVar4 + 4) | 0x800;
            tColour::tColour((tColour *)&local_78,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
            *(undefined4 *)(iVar4 + 0x60) = 0x3dcccccd;
            *(undefined4 *)(iVar4 + 100) = 0x3e99999a;
            iVar5 = *(int *)(this + 0x200);
            *(undefined4 *)(iVar4 + 0x2c) = local_78;
            *(undefined4 *)(iVar4 + 0x30) = uStack_74;
            *(undefined4 *)(iVar4 + 0x34) = uStack_70;
            *(undefined4 *)(iVar4 + 0x38) = uStack_6c;
            fVar16 = *(float *)(iVar5 + 0xfed4);
            fVar10 = *(float *)(iVar5 + 0xfecc);
            *(float *)(iVar4 + 0x50) = fVar18;
            fVar18 = *(float *)(iVar5 + 0xfed0);
            *(float *)(iVar4 + 0x48) = fVar19;
            *(undefined4 *)(iVar4 + 0x78) = 0x3a83126f;
            *(float *)(iVar4 + 0x4c) = fVar20;
            *(float *)(iVar4 + 0x5c) = fVar16 * 0.85;
            *(float *)(iVar4 + 0x54) = fVar10 * 0.85;
            *(float *)(iVar4 + 0x58) = fVar18 * 0.85;
          }
        }
        if (iVar6 == 2) break;
        fVar16 = *(float *)(this + 0x210);
      }
      iVar9 = iVar8;
    } while (iVar8 != 0xf);
  }
  return;
}
