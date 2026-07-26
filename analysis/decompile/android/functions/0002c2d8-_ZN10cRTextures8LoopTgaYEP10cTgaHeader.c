/*
 * mangled: _ZN10cRTextures8LoopTgaYEP10cTgaHeader
 * demangled: cRTextures::LoopTgaY(cTgaHeader*)
 * address: 0002c2d8
 * size: 960
 */

/* cRTextures::LoopTgaY(cTgaHeader*) */

void __thiscall cRTextures::LoopTgaY(cRTextures *this,cTgaHeader *param_1)

{
  uint uVar1;
  byte *pbVar2;
  cTgaHeader cVar3;
  int iVar4;
  uint uVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  void *pvVar9;
  void *pvVar10;
  void *pvVar11;
  uint uVar12;
  int iVar13;
  int iVar14;
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
  byte *local_60;
  byte *local_58;
  uint local_34;
  int local_30;

  pcVar17 = (char *)(DAT_0002c6a4 + 0x2c2ec + DAT_0002c6a8);
  cVar3 = param_1[0x10];
  pvVar9 = (void *)RShellMemoryMalloc((uint)*(ushort *)(param_1 + 0xe),pcVar17);
  uVar1 = (uint)((byte)cVar3 >> 3);
  pvVar10 = (void *)RShellMemoryMalloc((uint)*(ushort *)(param_1 + 0xe),pcVar17);
  pvVar11 = (void *)RShellMemoryMalloc((uint)*(ushort *)(param_1 + 0xe),pcVar17);
  fVar8 = DAT_0002c6a0;
  fVar7 = DAT_0002c69c;
  fVar6 = DAT_0002c698;
  uVar12 = (uint)*(ushort *)(param_1 + 0xc);
  if (uVar12 != 0) {
    local_34 = (uint)*(ushort *)(param_1 + 0xe);
    local_30 = 1;
    iVar14 = 0;
    do {
      if (local_34 != 0) {
        iVar15 = 0;
        while( true ) {
          *(cTgaHeader *)((int)pvVar9 + iVar15) = param_1[uVar1 * (iVar15 * uVar12 + iVar14) + 0x12]
          ;
          *(cTgaHeader *)((int)pvVar10 + iVar15) =
               param_1[uVar1 * ((uint)*(ushort *)(param_1 + 0xc) * iVar15 + iVar14) + 0x13];
          *(cTgaHeader *)((int)pvVar11 + iVar15) =
               param_1[uVar1 * ((uint)*(ushort *)(param_1 + 0xc) * iVar15 + iVar14) + 0x14];
          iVar15 = iVar15 + 1;
          local_34 = (uint)*(ushort *)(param_1 + 0xe);
          if ((int)local_34 <= iVar15) break;
          uVar12 = (uint)*(ushort *)(param_1 + 0xc);
        }
        uVar5 = local_34 / 6;
        uVar12 = (uint)*(ushort *)(param_1 + 0xc);
        if (uVar5 != 0) {
          iVar19 = uVar1 * -uVar12;
          iVar13 = (uVar12 * (local_34 - 1) + iVar14) * uVar1;
          local_58 = (byte *)((int)pvVar10 + local_34);
          local_60 = (byte *)((int)pvVar11 + local_34);
          iVar16 = 0;
          iVar15 = iVar13 + 2;
          iVar18 = local_30 + 1;
          iVar20 = iVar13 + 1;
          iVar21 = local_30;
          do {
            fVar23 = (float)VectorSignedToFloat(iVar16,(byte)(in_fpscr >> 0x16) & 3);
            iVar4 = uVar1 * (iVar16 * uVar12 + iVar14);
            fVar24 = (float)VectorSignedToFloat(uVar5,(byte)(in_fpscr >> 0x16) & 3);
            fVar25 = (fVar23 * fVar6) / fVar24 + fVar7;
            fVar22 = fVar8 - fVar25;
            fVar24 = (float)VectorUnsignedToFloat
                                      ((uint)(byte)param_1[iVar4 + 0x12],
                                       (byte)(in_fpscr >> 0x16) & 3);
            fVar23 = (float)VectorUnsignedToFloat
                                      ((uint)*(byte *)((int)pvVar9 + ((local_34 - 1) - iVar16)),
                                       (byte)(in_fpscr >> 0x16) & 3);
            param_1[iVar4 + 0x12] = SUB41((int)(fVar22 * fVar24 + fVar25 * fVar23),0);
            fVar24 = (float)VectorUnsignedToFloat
                                      ((uint)(byte)param_1[iVar13 + 0x12],
                                       (byte)(in_fpscr >> 0x16) & 3);
            fVar23 = (float)VectorUnsignedToFloat
                                      ((uint)*(byte *)((int)pvVar9 + iVar16),
                                       (byte)(in_fpscr >> 0x16) & 3);
            param_1[iVar13 + 0x12] = SUB41((int)(fVar22 * fVar24 + fVar25 * fVar23),0);
            fVar24 = (float)VectorUnsignedToFloat
                                      ((uint)(byte)param_1[iVar21 + 0x12],
                                       (byte)(in_fpscr >> 0x16) & 3);
            local_58 = local_58 + -1;
            fVar23 = (float)VectorUnsignedToFloat((uint)*local_58,(byte)(in_fpscr >> 0x16) & 3);
            param_1[iVar21 + 0x12] = SUB41((int)(fVar22 * fVar24 + fVar25 * fVar23),0);
            fVar24 = (float)VectorUnsignedToFloat
                                      ((uint)(byte)param_1[iVar20 + 0x12],
                                       (byte)(in_fpscr >> 0x16) & 3);
            fVar23 = (float)VectorUnsignedToFloat
                                      ((uint)*(byte *)((int)pvVar10 + iVar16),
                                       (byte)(in_fpscr >> 0x16) & 3);
            param_1[iVar20 + 0x12] = SUB41((int)(fVar22 * fVar24 + fVar25 * fVar23),0);
            fVar24 = (float)VectorUnsignedToFloat
                                      ((uint)(byte)param_1[iVar18 + 0x12],
                                       (byte)(in_fpscr >> 0x16) & 3);
            local_60 = local_60 + -1;
            fVar23 = (float)VectorUnsignedToFloat((uint)*local_60,(byte)(in_fpscr >> 0x16) & 3);
            param_1[iVar18 + 0x12] = SUB41((int)(fVar22 * fVar24 + fVar25 * fVar23),0);
            fVar23 = (float)VectorUnsignedToFloat
                                      ((uint)(byte)param_1[iVar15 + 0x12],
                                       (byte)(in_fpscr >> 0x16) & 3);
            pbVar2 = (byte *)((int)pvVar11 + iVar16);
            iVar16 = iVar16 + 1;
            fVar24 = (float)VectorUnsignedToFloat((uint)*pbVar2,(byte)(in_fpscr >> 0x16) & 3);
            param_1[iVar15 + 0x12] = SUB41((int)(fVar22 * fVar23 + fVar25 * fVar24),0);
            iVar15 = iVar15 + iVar19;
            iVar13 = iVar13 + iVar19;
            iVar18 = iVar18 + uVar12 * uVar1;
            iVar20 = iVar20 + iVar19;
            iVar21 = iVar21 + uVar12 * uVar1;
          } while (iVar16 < (int)uVar5);
        }
      }
      iVar14 = iVar14 + 1;
      local_30 = local_30 + uVar1;
    } while (iVar14 < (int)uVar12);
  }
  RShellMemoryFree(pvVar11);
  RShellMemoryFree(pvVar10);
  RShellMemoryFree(pvVar9);
  return;
}
