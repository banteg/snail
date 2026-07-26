/*
 * mangled: _ZN8cRObject11RequestAnimEiP8cRBodPosfi
 * demangled: cRObject::RequestAnim(int, cRBodPos*, float, int)
 * address: 0002f530
 * size: 1308
 */

/* cRObject::RequestAnim(int, cRBodPos*, float, int) */

void __thiscall
cRObject::RequestAnim(cRObject *this,int param_1,cRBodPos *param_2,float param_3,int param_4)

{
  cRBodPos *pcVar1;
  byte bVar2;
  undefined4 uVar3;
  undefined2 *puVar4;
  undefined4 extraout_r0;
  float *pfVar5;
  int iVar6;
  int iVar7;
  char *pcVar8;
  undefined4 extraout_r1;
  int iVar9;
  undefined4 *puVar10;
  undefined4 uVar11;
  cRBodPos *extraout_r2;
  char *pcVar12;
  char *pcVar13;
  cRBodPos *pcVar14;
  int iVar15;
  uint *puVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  int iVar21;
  undefined4 *puVar22;
  float *pfVar23;
  int iVar24;
  int iVar25;
  bool bVar26;
  uint in_fpscr;
  undefined4 extraout_s0;
  undefined4 extraout_s1;
  float fVar27;
  float fVar28;
  float fVar29;
  float fVar30;
  float fVar31;
  float fVar32;
  uint uVar34;
  longlong lVar33;
  cRBodPos *in_stack_00000000;
  int local_64;
  cRBodPos *local_5c;
  cRBodPos *local_58;
  cRBodPos *local_54;

  iVar20 = DAT_0002fa58;
  iVar7 = DAT_0002fa54 + 0x2f55c;
  if (0 < param_1) {
    local_5c = param_2;
    if (*(int *)(*(int *)(param_2 + 0x24) + 0xa0) != *(int *)(this + 0xa0)) {
LAB_0002fa28:
      RShellError((char *)(iVar7 + DAT_0002fa74),param_3,*(undefined4 *)(local_5c + 0x70));
      return;
    }
    iVar9 = 0;
    pcVar14 = param_2;
LAB_0002f5a0:
    local_5c = pcVar14 + 0x74;
    iVar9 = iVar9 + 1;
    if (iVar9 < param_1) goto LAB_0002f58c;
    iVar21 = 0;
    *(uint *)this = *(uint *)this | 0x1000000;
    iVar9 = RShellMemoryMalloc(param_1 * 8,(char *)(iVar7 + iVar20));
    iVar20 = DAT_0002fa5c;
    iVar15 = *(int *)(this + 0xa0);
    *(int *)(this + 0x108) = iVar9;
    pcVar14 = param_2;
    while( true ) {
      *(undefined4 *)(iVar9 + iVar21 * 8) = *(undefined4 *)(pcVar14 + 0x70);
      uVar3 = RShellMemoryMalloc(iVar15 * 0xc,(char *)(iVar7 + iVar20));
      puVar16 = *(uint **)(pcVar14 + 0x24);
      iVar15 = *(int *)(this + 0xa0);
      *puVar16 = *puVar16 | 0x2000000;
      *(undefined4 *)(iVar9 + iVar21 * 8 + 4) = uVar3;
      if (0 < iVar15) {
        iVar9 = 0;
        iVar25 = 0;
        iVar17 = *(int *)(*(int *)(this + 0x108) + iVar21 * 8 + 4);
        do {
          iVar25 = iVar25 + 1;
          puVar22 = (undefined4 *)(iVar17 + iVar9);
          puVar10 = (undefined4 *)(puVar16[0x29] + iVar9);
          iVar9 = iVar9 + 0xc;
          uVar3 = puVar10[1];
          uVar11 = puVar10[2];
          *puVar22 = *puVar10;
          puVar22[1] = uVar3;
          puVar22[2] = uVar11;
        } while (iVar25 != iVar15);
      }
      iVar21 = iVar21 + 1;
      pcVar14 = pcVar14 + 0x74;
      if (param_1 <= iVar21) break;
      iVar9 = *(int *)(this + 0x108);
    }
    goto LAB_0002f6a8;
  }
  *(uint *)this = *(uint *)this | 0x1000000;
  uVar3 = RShellMemoryMalloc(param_1 * 8,(char *)(iVar7 + iVar20));
  *(undefined4 *)(this + 0x108) = uVar3;
LAB_0002f6a8:
  iVar20 = DAT_0002fa60;
  fVar29 = DAT_0002fa4c / (float)param_4;
  *(uint *)this = *(uint *)this | 0x200000;
  iVar9 = (int)fVar29;
  puVar4 = (undefined2 *)RShellMemoryMalloc(0x18,(char *)(iVar7 + iVar20));
  uVar3 = DAT_0002fa50;
  pcVar8 = (char *)(iVar7 + DAT_0002fa64);
  *(undefined2 **)(this + 0x104) = puVar4;
  *puVar4 = (short)in_stack_00000000;
  *(int *)(puVar4 + 10) = param_4;
  *(int *)(puVar4 + 4) = param_1;
  *(undefined4 *)(puVar4 + 8) = uVar3;
  *(int *)(puVar4 + 2) = iVar9;
  uVar3 = RShellMemoryMalloc(iVar9 << 2,pcVar8);
  bVar26 = param_1 != 1;
  pcVar14 = extraout_r2;
  if (bVar26) {
    pcVar14 = param_2;
  }
  local_54 = *(cRBodPos **)(param_2 + 0x70);
  local_58 = local_54;
  if (bVar26) {
    pcVar14 = *(cRBodPos **)(pcVar14 + 0xe4);
    local_58 = in_stack_00000000;
  }
  *(undefined4 *)(puVar4 + 6) = uVar3;
  fVar29 = DAT_0002fa4c;
  if (bVar26) {
    local_58 = pcVar14;
  }
  if (iVar9 < 1) {
    local_64 = *(int *)(this + 0x104);
  }
  else {
    local_64 = *(int *)(this + 0x104);
    uVar34 = VectorSignedToFloat(iVar9,(byte)(in_fpscr >> 0x16) & 3);
    lVar33 = (ulonglong)uVar34 << 0x20;
    iVar20 = 0;
    iVar15 = 0;
    pcVar8 = (char *)(iVar7 + DAT_0002fa68);
    pcVar12 = (char *)(iVar7 + DAT_0002fa6c);
    pcVar13 = (char *)(iVar7 + DAT_0002fa70);
    do {
      while( true ) {
        iVar17 = *(int *)(local_64 + 0xc);
        uVar3 = RShellMemoryMalloc(0xc,pcVar8);
        iVar21 = *(int *)(this + 0xa0);
        iVar7 = *(int *)(*(int *)(this + 0x104) + 0xc);
        *(undefined4 *)(iVar17 + iVar20 * 4) = uVar3;
        puVar10 = *(undefined4 **)(iVar7 + iVar20 * 4);
        uVar3 = RShellMemoryMalloc(iVar21 * 0xc,pcVar13);
        *puVar10 = uVar3;
        fVar30 = (float)VectorSignedToFloat(*(int *)(param_2 + (param_1 + -1) * 0x74 + 0x70) *
                                            iVar20,(byte)(in_fpscr >> 0x16) & 3);
        fVar27 = (float)((ulonglong)lVar33 >> 0x20);
        floor((double)CONCAT44(extraout_s1,extraout_s0));
        if (((int)local_58 <= (int)(longlong)(double)CONCAT44(extraout_r1,extraout_r0)) &&
           (iVar15 < param_1 + -1)) {
          iVar15 = iVar15 + 1;
          local_54 = *(cRBodPos **)(param_2 + iVar15 * 0x74 + 0x70);
          local_58 = *(cRBodPos **)(param_2 + iVar15 * 0x74 + 0xe4);
        }
        if (param_1 == 1) break;
        fVar28 = (float)VectorSignedToFloat(local_54,(byte)(in_fpscr >> 0x16) & 3);
        fVar31 = (float)VectorSignedToFloat((int)local_58 - (int)local_54,
                                            (byte)(in_fpscr >> 0x16) & 3);
        fVar31 = (fVar30 / fVar27 - fVar28) / fVar31;
        lVar33 = CONCAT44(fVar27,fVar31);
        uVar34 = in_fpscr & 0xfffffff;
        in_fpscr = uVar34 | (uint)(fVar31 < 0.0) << 0x1f;
        if ((SUB41(in_fpscr >> 0x1f,0)) ||
           (uVar34 = uVar34 | (uint)(fVar31 < fVar29) << 0x1f | (uint)(fVar31 == fVar29) << 0x1e,
           in_fpscr = uVar34 | (uint)(NAN(fVar31) || NAN(fVar29)) << 0x1c,
           bVar2 = (byte)(uVar34 >> 0x18),
           !(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(in_fpscr >> 0x1c) & 1))) {
          wprintf(pcVar12,local_54,SUB84((double)fVar31,0),(int)((ulonglong)(double)fVar31 >> 0x20))
          ;
        }
        iVar7 = *(int *)(this + 0xa0);
        if (iVar7 < 1) goto LAB_0002f9b0;
LAB_0002f8cc:
        local_64 = *(int *)(this + 0x104);
        if (param_1 == 1) {
          iVar18 = 0;
          iVar17 = *(int *)(param_2 + iVar15 * 0x74 + 0x24);
          iVar25 = 0;
          iVar21 = *(int *)(local_64 + 0xc);
          do {
            iVar25 = iVar25 + 1;
            puVar10 = (undefined4 *)(*(int *)(iVar17 + 0xa4) + iVar18);
            uVar3 = puVar10[1];
            uVar11 = puVar10[2];
            puVar22 = (undefined4 *)(**(int **)(iVar21 + iVar20 * 4) + iVar18);
            iVar18 = iVar18 + 0xc;
            *puVar22 = *puVar10;
            puVar22[1] = uVar3;
            puVar22[2] = uVar11;
          } while (iVar25 != iVar7);
        }
        else {
          iVar18 = *(int *)(param_2 + iVar15 * 0x74 + 0x24);
          iVar17 = 0;
          iVar25 = *(int *)(local_64 + 0xc);
          iVar19 = *(int *)(param_2 + iVar15 * 0x74 + 0x98);
          iVar21 = 0;
          do {
            iVar21 = iVar21 + 1;
            pfVar23 = (float *)(*(int *)(iVar18 + 0xa4) + iVar17);
            fVar31 = pfVar23[2];
            pfVar5 = (float *)(*(int *)(iVar19 + 0xa4) + iVar17);
            fVar28 = pfVar23[1];
            fVar27 = pfVar5[2];
            fVar30 = pfVar5[1];
            iVar24 = **(int **)(iVar25 + iVar20 * 4);
            iVar6 = iVar24 + iVar17;
            fVar32 = (float)lVar33;
            *(float *)(iVar24 + iVar17) = *pfVar23 + fVar32 * (*pfVar5 - *pfVar23);
            iVar17 = iVar17 + 0xc;
            *(float *)(iVar6 + 4) = fVar28 + fVar32 * (fVar30 - fVar28);
            *(float *)(iVar6 + 8) = fVar31 + fVar32 * (fVar27 - fVar31);
          } while (iVar21 != iVar7);
        }
        iVar20 = iVar20 + 1;
        if (iVar9 <= iVar20) goto LAB_0002f988;
      }
      iVar7 = *(int *)(this + 0xa0);
      lVar33 = CONCAT44(fVar27,DAT_0002fa50);
      if (0 < iVar7) goto LAB_0002f8cc;
LAB_0002f9b0:
      iVar20 = iVar20 + 1;
      local_64 = *(int *)(this + 0x104);
    } while (iVar20 < iVar9);
  }
LAB_0002f988:
  *(undefined4 *)(local_64 + 0x10) = DAT_0002fa50;
  return;
LAB_0002f58c:
  pcVar1 = pcVar14 + 0x98;
  pcVar14 = local_5c;
  if (*(int *)(*(int *)pcVar1 + 0xa0) != *(int *)(*(int *)(param_2 + 0x24) + 0xa0))
  goto LAB_0002fa28;
  goto LAB_0002f5a0;
}
