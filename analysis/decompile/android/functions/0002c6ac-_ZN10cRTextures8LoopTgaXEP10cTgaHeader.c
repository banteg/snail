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
  void *pvVar6;
  void *pvVar7;
  void *pvVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  uint in_fpscr;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  byte *local_54;
  byte *local_50;

  cVar3 = param_1[0x10];
  pvVar6 = (void *)RShellMemoryMalloc((uint)*(ushort *)(param_1 + 0xc),"Tga loop strip");
  uVar1 = (uint)((byte)cVar3 >> 3);
  pvVar7 = (void *)RShellMemoryMalloc((uint)*(ushort *)(param_1 + 0xc),"Tga loop strip");
  pvVar8 = (void *)RShellMemoryMalloc((uint)*(ushort *)(param_1 + 0xc),"Tga loop strip");
  uVar11 = (uint)*(ushort *)(param_1 + 0xe);
  if (uVar11 != 0) {
    uVar10 = (uint)*(ushort *)(param_1 + 0xc);
    iVar9 = 0;
    iVar5 = -uVar1;
    do {
      if (uVar10 != 0) {
        iVar12 = 0;
        do {
          *(cTgaHeader *)((int)pvVar6 + iVar12) = param_1[uVar1 * (iVar9 * uVar10 + iVar12) + 0x12];
          *(cTgaHeader *)((int)pvVar7 + iVar12) =
               param_1[uVar1 * ((uint)*(ushort *)(param_1 + 0xc) * iVar9 + iVar12) + 0x13];
          *(cTgaHeader *)((int)pvVar8 + iVar12) =
               param_1[uVar1 * ((uint)*(ushort *)(param_1 + 0xc) * iVar9 + iVar12) + 0x14];
          iVar12 = iVar12 + 1;
          uVar10 = (uint)*(ushort *)(param_1 + 0xc);
        } while (iVar12 < (int)uVar10);
        uVar11 = uVar10 / 6;
        if (uVar11 != 0) {
          iVar12 = ((uVar10 - 1) + uVar10 * iVar9) * uVar1;
          local_50 = (byte *)((int)pvVar7 + uVar10);
          iVar16 = iVar9 * uVar10 * uVar1;
          iVar13 = 0;
          local_54 = (byte *)((int)pvVar8 + uVar10);
          iVar14 = iVar12 + 2;
          iVar15 = iVar12 + 1;
          iVar17 = iVar16 + 1;
          iVar16 = iVar16 + 2;
          do {
            fVar19 = (float)VectorSignedToFloat(iVar13,(byte)(in_fpscr >> 0x16) & 3);
            iVar4 = uVar1 * (uVar10 * iVar9 + iVar13);
            fVar20 = (float)VectorSignedToFloat(uVar11,(byte)(in_fpscr >> 0x16) & 3);
            fVar21 = (fVar19 * -0.5) / fVar20 + 0.5;
            fVar18 = 1.0 - fVar21;
            fVar20 = (float)VectorUnsignedToFloat
                                      ((uint)(byte)param_1[iVar4 + 0x12],
                                       (byte)(in_fpscr >> 0x16) & 3);
            fVar19 = (float)VectorUnsignedToFloat
                                      ((uint)*(byte *)((int)pvVar6 + ((uVar10 - 1) - iVar13)),
                                       (byte)(in_fpscr >> 0x16) & 3);
            param_1[iVar4 + 0x12] = SUB41((int)(fVar18 * fVar20 + fVar21 * fVar19),0);
            fVar20 = (float)VectorUnsignedToFloat
                                      ((uint)(byte)param_1[iVar12 + 0x12],
                                       (byte)(in_fpscr >> 0x16) & 3);
            fVar19 = (float)VectorUnsignedToFloat
                                      ((uint)*(byte *)((int)pvVar6 + iVar13),
                                       (byte)(in_fpscr >> 0x16) & 3);
            param_1[iVar12 + 0x12] = SUB41((int)(fVar18 * fVar20 + fVar21 * fVar19),0);
            fVar20 = (float)VectorUnsignedToFloat
                                      ((uint)(byte)param_1[iVar17 + 0x12],
                                       (byte)(in_fpscr >> 0x16) & 3);
            local_50 = local_50 + -1;
            fVar19 = (float)VectorUnsignedToFloat((uint)*local_50,(byte)(in_fpscr >> 0x16) & 3);
            param_1[iVar17 + 0x12] = SUB41((int)(fVar18 * fVar20 + fVar21 * fVar19),0);
            fVar20 = (float)VectorUnsignedToFloat
                                      ((uint)(byte)param_1[iVar15 + 0x12],
                                       (byte)(in_fpscr >> 0x16) & 3);
            fVar19 = (float)VectorUnsignedToFloat
                                      ((uint)*(byte *)((int)pvVar7 + iVar13),
                                       (byte)(in_fpscr >> 0x16) & 3);
            param_1[iVar15 + 0x12] = SUB41((int)(fVar18 * fVar20 + fVar21 * fVar19),0);
            fVar20 = (float)VectorUnsignedToFloat
                                      ((uint)(byte)param_1[iVar16 + 0x12],
                                       (byte)(in_fpscr >> 0x16) & 3);
            local_54 = local_54 + -1;
            fVar19 = (float)VectorUnsignedToFloat((uint)*local_54,(byte)(in_fpscr >> 0x16) & 3);
            param_1[iVar16 + 0x12] = SUB41((int)(fVar18 * fVar20 + fVar21 * fVar19),0);
            fVar19 = (float)VectorUnsignedToFloat
                                      ((uint)(byte)param_1[iVar14 + 0x12],
                                       (byte)(in_fpscr >> 0x16) & 3);
            pbVar2 = (byte *)((int)pvVar8 + iVar13);
            iVar13 = iVar13 + 1;
            fVar20 = (float)VectorUnsignedToFloat((uint)*pbVar2,(byte)(in_fpscr >> 0x16) & 3);
            param_1[iVar14 + 0x12] = SUB41((int)(fVar18 * fVar19 + fVar21 * fVar20),0);
            iVar12 = iVar12 + iVar5;
            iVar14 = iVar14 + iVar5;
            iVar15 = iVar15 + iVar5;
            iVar17 = iVar17 + uVar1;
            iVar16 = iVar16 + uVar1;
          } while (iVar13 < (int)uVar11);
        }
        uVar11 = (uint)*(ushort *)(param_1 + 0xe);
      }
      iVar9 = iVar9 + 1;
    } while (iVar9 < (int)uVar11);
  }
  RShellMemoryFree(pvVar8);
  RShellMemoryFree(pvVar7);
  RShellMemoryFree(pvVar6);
  return;
}
