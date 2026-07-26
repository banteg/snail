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
  void *pvVar6;
  void *pvVar7;
  void *pvVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
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
  byte *local_60;
  byte *local_58;
  uint local_34;
  int local_30;

  cVar3 = param_1[0x10];
  pvVar6 = (void *)RShellMemoryMalloc((uint)*(ushort *)(param_1 + 0xe),"Tga loop strip");
  uVar1 = (uint)((byte)cVar3 >> 3);
  pvVar7 = (void *)RShellMemoryMalloc((uint)*(ushort *)(param_1 + 0xe),"Tga loop strip");
  pvVar8 = (void *)RShellMemoryMalloc((uint)*(ushort *)(param_1 + 0xe),"Tga loop strip");
  uVar9 = (uint)*(ushort *)(param_1 + 0xc);
  if (uVar9 != 0) {
    local_34 = (uint)*(ushort *)(param_1 + 0xe);
    local_30 = 1;
    iVar11 = 0;
    do {
      if (local_34 != 0) {
        iVar12 = 0;
        while( true ) {
          *(cTgaHeader *)((int)pvVar6 + iVar12) = param_1[uVar1 * (iVar12 * uVar9 + iVar11) + 0x12];
          *(cTgaHeader *)((int)pvVar7 + iVar12) =
               param_1[uVar1 * ((uint)*(ushort *)(param_1 + 0xc) * iVar12 + iVar11) + 0x13];
          *(cTgaHeader *)((int)pvVar8 + iVar12) =
               param_1[uVar1 * ((uint)*(ushort *)(param_1 + 0xc) * iVar12 + iVar11) + 0x14];
          iVar12 = iVar12 + 1;
          local_34 = (uint)*(ushort *)(param_1 + 0xe);
          if ((int)local_34 <= iVar12) break;
          uVar9 = (uint)*(ushort *)(param_1 + 0xc);
        }
        uVar5 = local_34 / 6;
        uVar9 = (uint)*(ushort *)(param_1 + 0xc);
        if (uVar5 != 0) {
          iVar15 = uVar1 * -uVar9;
          iVar10 = (uVar9 * (local_34 - 1) + iVar11) * uVar1;
          local_58 = (byte *)((int)pvVar7 + local_34);
          local_60 = (byte *)((int)pvVar8 + local_34);
          iVar13 = 0;
          iVar12 = iVar10 + 2;
          iVar14 = local_30 + 1;
          iVar16 = iVar10 + 1;
          iVar17 = local_30;
          do {
            fVar19 = (float)VectorSignedToFloat(iVar13,(byte)(in_fpscr >> 0x16) & 3);
            iVar4 = uVar1 * (iVar13 * uVar9 + iVar11);
            fVar20 = (float)VectorSignedToFloat(uVar5,(byte)(in_fpscr >> 0x16) & 3);
            fVar21 = (fVar19 * -0.5) / fVar20 + 0.5;
            fVar18 = 1.0 - fVar21;
            fVar20 = (float)VectorUnsignedToFloat
                                      ((uint)(byte)param_1[iVar4 + 0x12],
                                       (byte)(in_fpscr >> 0x16) & 3);
            fVar19 = (float)VectorUnsignedToFloat
                                      ((uint)*(byte *)((int)pvVar6 + ((local_34 - 1) - iVar13)),
                                       (byte)(in_fpscr >> 0x16) & 3);
            param_1[iVar4 + 0x12] = SUB41((int)(fVar18 * fVar20 + fVar21 * fVar19),0);
            fVar20 = (float)VectorUnsignedToFloat
                                      ((uint)(byte)param_1[iVar10 + 0x12],
                                       (byte)(in_fpscr >> 0x16) & 3);
            fVar19 = (float)VectorUnsignedToFloat
                                      ((uint)*(byte *)((int)pvVar6 + iVar13),
                                       (byte)(in_fpscr >> 0x16) & 3);
            param_1[iVar10 + 0x12] = SUB41((int)(fVar18 * fVar20 + fVar21 * fVar19),0);
            fVar20 = (float)VectorUnsignedToFloat
                                      ((uint)(byte)param_1[iVar17 + 0x12],
                                       (byte)(in_fpscr >> 0x16) & 3);
            local_58 = local_58 + -1;
            fVar19 = (float)VectorUnsignedToFloat((uint)*local_58,(byte)(in_fpscr >> 0x16) & 3);
            param_1[iVar17 + 0x12] = SUB41((int)(fVar18 * fVar20 + fVar21 * fVar19),0);
            fVar20 = (float)VectorUnsignedToFloat
                                      ((uint)(byte)param_1[iVar16 + 0x12],
                                       (byte)(in_fpscr >> 0x16) & 3);
            fVar19 = (float)VectorUnsignedToFloat
                                      ((uint)*(byte *)((int)pvVar7 + iVar13),
                                       (byte)(in_fpscr >> 0x16) & 3);
            param_1[iVar16 + 0x12] = SUB41((int)(fVar18 * fVar20 + fVar21 * fVar19),0);
            fVar20 = (float)VectorUnsignedToFloat
                                      ((uint)(byte)param_1[iVar14 + 0x12],
                                       (byte)(in_fpscr >> 0x16) & 3);
            local_60 = local_60 + -1;
            fVar19 = (float)VectorUnsignedToFloat((uint)*local_60,(byte)(in_fpscr >> 0x16) & 3);
            param_1[iVar14 + 0x12] = SUB41((int)(fVar18 * fVar20 + fVar21 * fVar19),0);
            fVar19 = (float)VectorUnsignedToFloat
                                      ((uint)(byte)param_1[iVar12 + 0x12],
                                       (byte)(in_fpscr >> 0x16) & 3);
            pbVar2 = (byte *)((int)pvVar8 + iVar13);
            iVar13 = iVar13 + 1;
            fVar20 = (float)VectorUnsignedToFloat((uint)*pbVar2,(byte)(in_fpscr >> 0x16) & 3);
            param_1[iVar12 + 0x12] = SUB41((int)(fVar18 * fVar19 + fVar21 * fVar20),0);
            iVar12 = iVar12 + iVar15;
            iVar10 = iVar10 + iVar15;
            iVar14 = iVar14 + uVar9 * uVar1;
            iVar16 = iVar16 + iVar15;
            iVar17 = iVar17 + uVar9 * uVar1;
          } while (iVar13 < (int)uVar5);
        }
      }
      iVar11 = iVar11 + 1;
      local_30 = local_30 + uVar1;
    } while (iVar11 < (int)uVar9);
  }
  RShellMemoryFree(pvVar8);
  RShellMemoryFree(pvVar7);
  RShellMemoryFree(pvVar6);
  return;
}
