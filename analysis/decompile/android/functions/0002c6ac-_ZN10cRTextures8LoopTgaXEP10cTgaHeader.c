/*
 * mangled: _ZN10cRTextures8LoopTgaXEP10cTgaHeader
 * demangled: cRTextures::LoopTgaX(cTgaHeader*)
 * address: 0002c6ac
 * size: 900
 */

/* cRTextures::LoopTgaX(cTgaHeader*) */

void __thiscall cRTextures::LoopTgaX(cRTextures *this,cTgaHeader *param_1)

{
  uint uVar1;
  byte *pbVar2;
  cTgaHeader cVar3;
  int iVar4;
  int iVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  void *pvVar9;
  void *pvVar10;
  void *pvVar11;
  int iVar12;
  uint uVar13;
  uint uVar14;
  int iVar15;
  int iVar16;
  char *pcVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  int iVar21;
  uint in_fpscr;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  byte *local_54;
  byte *local_50;

  pcVar17 = (char *)(DAT_0002ca3c + 0x2c6c0 + DAT_0002ca40);
  cVar3 = param_1[0x10];
  pvVar9 = (void *)RShellMemoryMalloc((uint)*(ushort *)(param_1 + 0xc),pcVar17);
  uVar1 = (uint)((byte)cVar3 >> 3);
  pvVar10 = (void *)RShellMemoryMalloc((uint)*(ushort *)(param_1 + 0xc),pcVar17);
  pvVar11 = (void *)RShellMemoryMalloc((uint)*(ushort *)(param_1 + 0xc),pcVar17);
  fVar8 = DAT_0002ca38;
  fVar7 = DAT_0002ca34;
  fVar6 = DAT_0002ca30;
  uVar14 = (uint)*(ushort *)(param_1 + 0xe);
  if (uVar14 != 0) {
    uVar13 = (uint)*(ushort *)(param_1 + 0xc);
    iVar12 = 0;
    iVar5 = -uVar1;
    do {
      if (uVar13 != 0) {
        iVar15 = 0;
        do {
          *(cTgaHeader *)((int)pvVar9 + iVar15) = param_1[uVar1 * (iVar12 * uVar13 + iVar15) + 0x12]
          ;
          *(cTgaHeader *)((int)pvVar10 + iVar15) =
               param_1[uVar1 * ((uint)*(ushort *)(param_1 + 0xc) * iVar12 + iVar15) + 0x13];
          *(cTgaHeader *)((int)pvVar11 + iVar15) =
               param_1[uVar1 * ((uint)*(ushort *)(param_1 + 0xc) * iVar12 + iVar15) + 0x14];
          iVar15 = iVar15 + 1;
          uVar13 = (uint)*(ushort *)(param_1 + 0xc);
        } while (iVar15 < (int)uVar13);
        uVar14 = uVar13 / 6;
        if (uVar14 != 0) {
          iVar15 = ((uVar13 - 1) + uVar13 * iVar12) * uVar1;
          local_50 = (byte *)((int)pvVar10 + uVar13);
          iVar20 = iVar12 * uVar13 * uVar1;
          iVar16 = 0;
          local_54 = (byte *)((int)pvVar11 + uVar13);
          iVar18 = iVar15 + 2;
          iVar19 = iVar15 + 1;
          iVar21 = iVar20 + 1;
          iVar20 = iVar20 + 2;
          do {
            fVar23 = (float)VectorSignedToFloat(iVar16,(byte)(in_fpscr >> 0x16) & 3);
            iVar4 = uVar1 * (uVar13 * iVar12 + iVar16);
            fVar24 = (float)VectorSignedToFloat(uVar14,(byte)(in_fpscr >> 0x16) & 3);
            fVar25 = (fVar23 * fVar6) / fVar24 + fVar7;
            fVar22 = fVar8 - fVar25;
            fVar24 = (float)VectorUnsignedToFloat
                                      ((uint)(byte)param_1[iVar4 + 0x12],
                                       (byte)(in_fpscr >> 0x16) & 3);
            fVar23 = (float)VectorUnsignedToFloat
                                      ((uint)*(byte *)((int)pvVar9 + ((uVar13 - 1) - iVar16)),
                                       (byte)(in_fpscr >> 0x16) & 3);
            param_1[iVar4 + 0x12] = SUB41((int)(fVar22 * fVar24 + fVar25 * fVar23),0);
            fVar24 = (float)VectorUnsignedToFloat
                                      ((uint)(byte)param_1[iVar15 + 0x12],
                                       (byte)(in_fpscr >> 0x16) & 3);
            fVar23 = (float)VectorUnsignedToFloat
                                      ((uint)*(byte *)((int)pvVar9 + iVar16),
                                       (byte)(in_fpscr >> 0x16) & 3);
            param_1[iVar15 + 0x12] = SUB41((int)(fVar22 * fVar24 + fVar25 * fVar23),0);
            fVar24 = (float)VectorUnsignedToFloat
                                      ((uint)(byte)param_1[iVar21 + 0x12],
                                       (byte)(in_fpscr >> 0x16) & 3);
            local_50 = local_50 + -1;
            fVar23 = (float)VectorUnsignedToFloat((uint)*local_50,(byte)(in_fpscr >> 0x16) & 3);
            param_1[iVar21 + 0x12] = SUB41((int)(fVar22 * fVar24 + fVar25 * fVar23),0);
            fVar24 = (float)VectorUnsignedToFloat
                                      ((uint)(byte)param_1[iVar19 + 0x12],
                                       (byte)(in_fpscr >> 0x16) & 3);
            fVar23 = (float)VectorUnsignedToFloat
                                      ((uint)*(byte *)((int)pvVar10 + iVar16),
                                       (byte)(in_fpscr >> 0x16) & 3);
            param_1[iVar19 + 0x12] = SUB41((int)(fVar22 * fVar24 + fVar25 * fVar23),0);
            fVar24 = (float)VectorUnsignedToFloat
                                      ((uint)(byte)param_1[iVar20 + 0x12],
                                       (byte)(in_fpscr >> 0x16) & 3);
            local_54 = local_54 + -1;
            fVar23 = (float)VectorUnsignedToFloat((uint)*local_54,(byte)(in_fpscr >> 0x16) & 3);
            param_1[iVar20 + 0x12] = SUB41((int)(fVar22 * fVar24 + fVar25 * fVar23),0);
            fVar23 = (float)VectorUnsignedToFloat
                                      ((uint)(byte)param_1[iVar18 + 0x12],
                                       (byte)(in_fpscr >> 0x16) & 3);
            pbVar2 = (byte *)((int)pvVar11 + iVar16);
            iVar16 = iVar16 + 1;
            fVar24 = (float)VectorUnsignedToFloat((uint)*pbVar2,(byte)(in_fpscr >> 0x16) & 3);
            param_1[iVar18 + 0x12] = SUB41((int)(fVar22 * fVar23 + fVar25 * fVar24),0);
            iVar15 = iVar15 + iVar5;
            iVar18 = iVar18 + iVar5;
            iVar19 = iVar19 + iVar5;
            iVar21 = iVar21 + uVar1;
            iVar20 = iVar20 + uVar1;
          } while (iVar16 < (int)uVar14);
        }
        uVar14 = (uint)*(ushort *)(param_1 + 0xe);
      }
      iVar12 = iVar12 + 1;
    } while (iVar12 < (int)uVar14);
  }
  RShellMemoryFree(pvVar11);
  RShellMemoryFree(pvVar10);
  RShellMemoryFree(pvVar9);
  return;
}
