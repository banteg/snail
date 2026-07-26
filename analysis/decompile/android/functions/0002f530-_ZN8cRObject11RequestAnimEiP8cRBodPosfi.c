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
  undefined4 extraout_r1;
  int iVar7;
  undefined4 *puVar8;
  undefined4 uVar9;
  cRBodPos *extraout_r2;
  cRBodPos *pcVar10;
  int iVar11;
  int iVar12;
  uint *puVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  undefined4 *puVar19;
  float *pfVar20;
  int iVar21;
  int iVar22;
  bool bVar23;
  uint in_fpscr;
  undefined4 extraout_s0;
  undefined4 extraout_s1;
  float fVar24;
  float fVar25;
  float fVar26;
  float fVar27;
  float fVar28;
  uint uVar30;
  longlong lVar29;
  cRBodPos *in_stack_00000000;
  int local_64;
  cRBodPos *local_5c;
  cRBodPos *local_58;
  cRBodPos *local_54;

  if (0 < param_1) {
    local_5c = param_2;
    if (*(int *)(*(int *)(param_2 + 0x24) + 0xa0) != *(int *)(this + 0xa0)) {
LAB_0002fa28:
      RShellError("Anim tween Vertices don\'t match Frame %i",param_3,
                  *(undefined4 *)(local_5c + 0x70));
      return;
    }
    iVar7 = 0;
    pcVar10 = param_2;
LAB_0002f5a0:
    local_5c = pcVar10 + 0x74;
    iVar7 = iVar7 + 1;
    if (iVar7 < param_1) goto LAB_0002f58c;
    iVar18 = 0;
    *(uint *)this = *(uint *)this | 0x1000000;
    iVar7 = RShellMemoryMalloc(param_1 * 8,"Object Animation KeyFrames");
    iVar11 = *(int *)(this + 0xa0);
    *(int *)(this + 0x108) = iVar7;
    pcVar10 = param_2;
    while( true ) {
      *(undefined4 *)(iVar7 + iVar18 * 8) = *(undefined4 *)(pcVar10 + 0x70);
      uVar3 = RShellMemoryMalloc(iVar11 * 0xc,"Object Anim KeyFrame Vertices");
      puVar13 = *(uint **)(pcVar10 + 0x24);
      iVar11 = *(int *)(this + 0xa0);
      *puVar13 = *puVar13 | 0x2000000;
      *(undefined4 *)(iVar7 + iVar18 * 8 + 4) = uVar3;
      if (0 < iVar11) {
        iVar7 = 0;
        iVar22 = 0;
        iVar15 = *(int *)(*(int *)(this + 0x108) + iVar18 * 8 + 4);
        do {
          iVar22 = iVar22 + 1;
          puVar19 = (undefined4 *)(iVar15 + iVar7);
          puVar8 = (undefined4 *)(puVar13[0x29] + iVar7);
          iVar7 = iVar7 + 0xc;
          uVar3 = puVar8[1];
          uVar9 = puVar8[2];
          *puVar19 = *puVar8;
          puVar19[1] = uVar3;
          puVar19[2] = uVar9;
        } while (iVar22 != iVar11);
      }
      iVar18 = iVar18 + 1;
      pcVar10 = pcVar10 + 0x74;
      if (param_1 <= iVar18) break;
      iVar7 = *(int *)(this + 0x108);
    }
    goto LAB_0002f6a8;
  }
  *(uint *)this = *(uint *)this | 0x1000000;
  uVar3 = RShellMemoryMalloc(param_1 * 8,"Object Animation KeyFrames");
  *(undefined4 *)(this + 0x108) = uVar3;
LAB_0002f6a8:
  *(uint *)this = *(uint *)this | 0x200000;
  iVar7 = (int)(1.0 / (float)param_4);
  puVar4 = (undefined2 *)RShellMemoryMalloc(0x18,"Object Animation");
  *(undefined2 **)(this + 0x104) = puVar4;
  *puVar4 = (short)in_stack_00000000;
  *(int *)(puVar4 + 10) = param_4;
  *(int *)(puVar4 + 4) = param_1;
  *(undefined4 *)(puVar4 + 8) = 0;
  *(int *)(puVar4 + 2) = iVar7;
  uVar3 = RShellMemoryMalloc(iVar7 << 2,"Object Animation Frame array");
  bVar23 = param_1 != 1;
  pcVar10 = extraout_r2;
  if (bVar23) {
    pcVar10 = param_2;
  }
  local_54 = *(cRBodPos **)(param_2 + 0x70);
  local_58 = local_54;
  if (bVar23) {
    pcVar10 = *(cRBodPos **)(pcVar10 + 0xe4);
    local_58 = in_stack_00000000;
  }
  *(undefined4 *)(puVar4 + 6) = uVar3;
  if (bVar23) {
    local_58 = pcVar10;
  }
  if (iVar7 < 1) {
    local_64 = *(int *)(this + 0x104);
  }
  else {
    local_64 = *(int *)(this + 0x104);
    uVar30 = VectorSignedToFloat(iVar7,(byte)(in_fpscr >> 0x16) & 3);
    lVar29 = (ulonglong)uVar30 << 0x20;
    iVar11 = 0;
    iVar18 = 0;
    do {
      while( true ) {
        iVar12 = *(int *)(local_64 + 0xc);
        uVar3 = RShellMemoryMalloc(0xc,"Object Animation Frame");
        iVar22 = *(int *)(this + 0xa0);
        iVar15 = *(int *)(*(int *)(this + 0x104) + 0xc);
        *(undefined4 *)(iVar12 + iVar11 * 4) = uVar3;
        puVar8 = *(undefined4 **)(iVar15 + iVar11 * 4);
        uVar3 = RShellMemoryMalloc(iVar22 * 0xc,"Object Animation Frame Vertices");
        *puVar8 = uVar3;
        fVar26 = (float)VectorSignedToFloat(*(int *)(param_2 + (param_1 + -1) * 0x74 + 0x70) *
                                            iVar11,(byte)(in_fpscr >> 0x16) & 3);
        fVar24 = (float)((ulonglong)lVar29 >> 0x20);
        floor((double)CONCAT44(extraout_s1,extraout_s0));
        if (((int)local_58 <= (int)(longlong)(double)CONCAT44(extraout_r1,extraout_r0)) &&
           (iVar18 < param_1 + -1)) {
          iVar18 = iVar18 + 1;
          local_54 = *(cRBodPos **)(param_2 + iVar18 * 0x74 + 0x70);
          local_58 = *(cRBodPos **)(param_2 + iVar18 * 0x74 + 0xe4);
        }
        if (param_1 == 1) break;
        fVar25 = (float)VectorSignedToFloat(local_54,(byte)(in_fpscr >> 0x16) & 3);
        fVar27 = (float)VectorSignedToFloat((int)local_58 - (int)local_54,
                                            (byte)(in_fpscr >> 0x16) & 3);
        fVar27 = (fVar26 / fVar24 - fVar25) / fVar27;
        lVar29 = CONCAT44(fVar24,fVar27);
        uVar30 = in_fpscr & 0xfffffff;
        in_fpscr = uVar30 | (uint)(fVar27 < 0.0) << 0x1f;
        if ((SUB41(in_fpscr >> 0x1f,0)) ||
           (uVar30 = uVar30 | (uint)(fVar27 < 1.0) << 0x1f | (uint)(fVar27 == 1.0) << 0x1e,
           in_fpscr = uVar30 | (uint)NAN(fVar27) << 0x1c, bVar2 = (byte)(uVar30 >> 0x18),
           !(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(in_fpscr >> 0x1c) & 1))) {
          wprintf("RequestAnim Dodgy Tween %f\n",local_54,SUB84((double)fVar27,0),
                  (int)((ulonglong)(double)fVar27 >> 0x20));
        }
        iVar15 = *(int *)(this + 0xa0);
        if (iVar15 < 1) goto LAB_0002f9b0;
LAB_0002f8cc:
        local_64 = *(int *)(this + 0x104);
        if (param_1 == 1) {
          iVar16 = 0;
          iVar12 = *(int *)(param_2 + iVar18 * 0x74 + 0x24);
          iVar14 = 0;
          iVar22 = *(int *)(local_64 + 0xc);
          do {
            iVar14 = iVar14 + 1;
            puVar8 = (undefined4 *)(*(int *)(iVar12 + 0xa4) + iVar16);
            uVar3 = puVar8[1];
            uVar9 = puVar8[2];
            puVar19 = (undefined4 *)(**(int **)(iVar22 + iVar11 * 4) + iVar16);
            iVar16 = iVar16 + 0xc;
            *puVar19 = *puVar8;
            puVar19[1] = uVar3;
            puVar19[2] = uVar9;
          } while (iVar14 != iVar15);
        }
        else {
          iVar16 = *(int *)(param_2 + iVar18 * 0x74 + 0x24);
          iVar12 = 0;
          iVar14 = *(int *)(local_64 + 0xc);
          iVar17 = *(int *)(param_2 + iVar18 * 0x74 + 0x98);
          iVar22 = 0;
          do {
            iVar22 = iVar22 + 1;
            pfVar20 = (float *)(*(int *)(iVar16 + 0xa4) + iVar12);
            fVar27 = pfVar20[2];
            pfVar5 = (float *)(*(int *)(iVar17 + 0xa4) + iVar12);
            fVar25 = pfVar20[1];
            fVar24 = pfVar5[2];
            fVar26 = pfVar5[1];
            iVar21 = **(int **)(iVar14 + iVar11 * 4);
            iVar6 = iVar21 + iVar12;
            fVar28 = (float)lVar29;
            *(float *)(iVar21 + iVar12) = *pfVar20 + fVar28 * (*pfVar5 - *pfVar20);
            iVar12 = iVar12 + 0xc;
            *(float *)(iVar6 + 4) = fVar25 + fVar28 * (fVar26 - fVar25);
            *(float *)(iVar6 + 8) = fVar27 + fVar28 * (fVar24 - fVar27);
          } while (iVar22 != iVar15);
        }
        iVar11 = iVar11 + 1;
        if (iVar7 <= iVar11) goto LAB_0002f988;
      }
      iVar15 = *(int *)(this + 0xa0);
      lVar29 = (ulonglong)(uint)fVar24 << 0x20;
      if (0 < iVar15) goto LAB_0002f8cc;
LAB_0002f9b0:
      iVar11 = iVar11 + 1;
      local_64 = *(int *)(this + 0x104);
    } while (iVar11 < iVar7);
  }
LAB_0002f988:
  *(undefined4 *)(local_64 + 0x10) = 0;
  return;
LAB_0002f58c:
  pcVar1 = pcVar10 + 0x98;
  pcVar10 = local_5c;
  if (*(int *)(*(int *)pcVar1 + 0xa0) != *(int *)(*(int *)(param_2 + 0x24) + 0xa0))
  goto LAB_0002fa28;
  goto LAB_0002f5a0;
}
