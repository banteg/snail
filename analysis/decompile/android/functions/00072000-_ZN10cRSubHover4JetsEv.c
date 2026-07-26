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
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  float fVar11;
  int iVar12;
  undefined4 uVar13;
  undefined4 uVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  cRSubHover *pcVar18;
  int iVar19;
  int iVar20;
  int iVar21;
  uint in_fpscr;
  float extraout_s0;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  float fVar26;
  float fVar27;
  float fVar28;
  float fVar29;
  float fVar30;
  float fVar31;
  float fVar32;
  undefined4 local_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;

  iVar19 = DAT_00072310 + 0x72020;
  if ((*(int *)(this + 0xc) == 1) &&
     (*(int *)((int)&__DT_SYMTAB[0xbb].st_value + *(int *)(this + 0x200)) ==
      *(int *)(*(int *)((int)&__DT_SYMTAB[0xc1].st_value + *(int *)(this + 0x200)) + 0x104))) {
    uVar13 = gRMathRand2();
    iVar12 = DAT_00072314;
    uVar8 = DAT_000722f4;
    fVar7 = DAT_000722f0;
    fVar6 = DAT_000722ec;
    fVar5 = DAT_000722e8;
    fVar4 = DAT_000722e0;
    fVar3 = DAT_000722dc;
    fVar26 = (float)VectorSignedToFloat(uVar13,(byte)(in_fpscr >> 0x16) & 3);
    fVar32 = DAT_000722e4 + fVar26 * DAT_000722dc * DAT_000722e0;
    uVar13 = gRMathRand2();
    fVar26 = (float)VectorSignedToFloat(uVar13,(byte)(in_fpscr >> 0x16) & 3);
    iVar21 = 0;
    do {
      fVar11 = DAT_00072308;
      uVar10 = DAT_00072304;
      uVar9 = DAT_00072300;
      uVar13 = DAT_000722fc;
      fVar23 = (float)VectorSignedToFloat(iVar21,(byte)(in_fpscr >> 0x16) & 3);
      fVar27 = *(float *)(this + 0x210);
      iVar20 = iVar21 + 1;
      iVar17 = 0;
      pcVar18 = this + iVar20 * 0x20;
      fVar28 = fVar27 * (fVar5 + fVar26 * fVar3 * fVar4) * (DAT_000722f8 - fVar23 / fVar6);
      while( true ) {
        if (iVar17 == 0) {
          iVar15 = *(int *)(this + 0x200);
          fVar30 = *(float *)((int)&__DT_SYMTAB[0x10b].st_size + iVar15);
          fVar29 = *(float *)((int)&__DT_SYMTAB[0x10c].st_name + iVar15);
          fVar31 = *(float *)(&__DT_SYMTAB[0x10b].st_info + iVar15);
        }
        else {
          iVar15 = *(int *)(this + 0x200);
          fVar30 = *(float *)((int)&__DT_SYMTAB[0x10c].st_value + iVar15);
          fVar29 = *(float *)(&__DT_SYMTAB[0x10c].st_info + iVar15);
          fVar31 = *(float *)((int)&__DT_SYMTAB[0x10c].st_size + iVar15);
        }
        iVar15 = *(int *)(this + 0x10);
        fVar22 = *(float *)(iVar15 + 0x2854);
        iVar16 = *(int *)pcVar18;
        fVar24 = *(float *)(iVar15 + 0x284c);
        iVar17 = iVar17 + 1;
        fVar25 = *(float *)(iVar15 + 0x2850);
        pcVar18 = pcVar18 + 0x10;
        *(float *)(iVar16 + 100) = fVar28;
        *(float *)(iVar16 + 0x60) = fVar28;
        fVar27 = -(fVar27 * (fVar23 / fVar6)) * fVar32;
        fVar29 = fVar29 + fVar27 * fVar22;
        fVar30 = fVar30 + fVar27 * fVar24;
        *(float *)(iVar16 + 0x50) = fVar29;
        fVar31 = fVar31 + fVar27 * fVar25;
        *(float *)(iVar16 + 0x48) = fVar30;
        *(float *)(iVar16 + 0x4c) = fVar31;
        if (iVar21 == 0xe) {
          uVar14 = gRMathRand2();
          fVar27 = (float)VectorSignedToFloat(uVar14,(byte)(in_fpscr >> 0x16) & 3);
          fVar27 = fVar27 * fVar3;
          uVar1 = in_fpscr & 0xfffffff | (uint)(fVar27 < fVar7) << 0x1f |
                  (uint)(fVar27 == fVar7) << 0x1e;
          in_fpscr = uVar1 | (uint)(NAN(fVar27) || NAN(fVar7)) << 0x1c;
          bVar2 = (byte)(uVar1 >> 0x18);
          if (!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(in_fpscr >> 0x1c) & 1)) {
            iVar15 = cRSpriteManager::New
                               (*(int *)(iVar19 + iVar12),*(int *)(*(int *)(this + 0x200) + 0xfe34),
                                0x13,-1);
            *(undefined4 *)(iVar15 + 0x68) = uVar8;
            *(undefined4 *)(iVar15 + 0x6c) = uVar13;
            *(undefined4 *)(iVar15 + 0x70) = uVar8;
            *(undefined4 *)(iVar15 + 0x74) = uVar8;
            *(uint *)(iVar15 + 4) = *(uint *)(iVar15 + 4) | 0x800;
            tColour::tColour((tColour *)&local_78,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
            *(undefined4 *)(iVar15 + 0x60) = uVar9;
            *(undefined4 *)(iVar15 + 100) = uVar10;
            uVar14 = DAT_0007230c;
            iVar16 = *(int *)(this + 0x200);
            *(undefined4 *)(iVar15 + 0x2c) = local_78;
            *(undefined4 *)(iVar15 + 0x30) = uStack_74;
            *(undefined4 *)(iVar15 + 0x34) = uStack_70;
            *(undefined4 *)(iVar15 + 0x38) = uStack_6c;
            fVar27 = *(float *)(iVar16 + 0xfed4);
            fVar22 = *(float *)(iVar16 + 0xfecc);
            *(float *)(iVar15 + 0x50) = fVar29;
            fVar29 = *(float *)(iVar16 + 0xfed0);
            *(float *)(iVar15 + 0x48) = fVar30;
            *(undefined4 *)(iVar15 + 0x78) = uVar14;
            *(float *)(iVar15 + 0x4c) = fVar31;
            *(float *)(iVar15 + 0x5c) = fVar27 * fVar11;
            *(float *)(iVar15 + 0x54) = fVar11 * fVar22;
            *(float *)(iVar15 + 0x58) = fVar11 * fVar29;
          }
        }
        if (iVar17 == 2) break;
        fVar27 = *(float *)(this + 0x210);
      }
      iVar21 = iVar20;
    } while (iVar20 != 0xf);
  }
  return;
}
