/*
 * mangled: _ZN8cRObject11RequestAnimEiP8cRBodPosfi
 * demangled: cRObject::RequestAnim(int, cRBodPos*, float, int)
 * address: 00012798
 * size: 1108
 */

/* cRObject::RequestAnim(int, cRBodPos*, float, int) */

void __thiscall
cRObject::RequestAnim(cRObject *this,int param_1,cRBodPos *param_2,float param_3,int param_4)

{
  int iVar1;
  cRBodPos *pcVar2;
  uint uVar3;
  cRBodPos *pcVar4;
  byte bVar5;
  undefined4 uVar6;
  undefined4 *puVar7;
  float fVar8;
  float *pfVar9;
  int iVar10;
  undefined4 uVar11;
  float *pfVar12;
  int iVar13;
  undefined4 *puVar14;
  float *pfVar15;
  cRBodPos *pcVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  uint in_fpscr;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  ulonglong uVar25;
  float fVar26;
  int local_38;

  uVar25 = (ulonglong)(uint)param_3;
  if (param_1 < 1) {
    *(uint *)this = *(uint *)this | 0x1000000;
    uVar6 = RShellMemoryMalloc(param_1 * 8,"Object Animation KeyFrames");
    *(undefined4 *)(this + 0x108) = uVar6;
LAB_0001290c:
    *(uint *)this = *(uint *)this | 0x200000;
    iVar13 = (int)(1.0 / param_3);
    iVar10 = RShellMemoryMalloc(0x18,"Object Animation");
    *(int *)(this + 0x104) = iVar10;
    *(int *)(iVar10 + 4) = iVar13;
    *(int *)(*(int *)(this + 0x104) + 8) = param_1;
    **(undefined2 **)(this + 0x104) = (undefined2)param_4;
    *(undefined4 *)(*(int *)(this + 0x104) + 0x10) = 0;
    *(float *)(*(int *)(this + 0x104) + 0x14) = param_3;
    iVar10 = *(int *)(this + 0x104);
    uVar6 = RShellMemoryMalloc(iVar13 << 2,"Object Animation Frame array");
    *(undefined4 *)(iVar10 + 0xc) = uVar6;
    iVar10 = *(int *)(param_2 + 0x70);
    local_38 = iVar10;
    if (param_1 != 1) {
      local_38 = *(int *)(param_2 + 0xe4);
    }
    if (0 < iVar13) {
      fVar26 = (float)VectorSignedToFloat(iVar13,(byte)(in_fpscr >> 0x16) & 3);
      iVar18 = 0;
      iVar20 = 0;
      do {
        iVar1 = iVar18 * 4;
        iVar17 = *(int *)(*(int *)(this + 0x104) + 0xc);
        uVar6 = RShellMemoryMalloc(0xc,"Object Animation Frame");
        *(undefined4 *)(iVar17 + iVar18 * 4) = uVar6;
        puVar7 = *(undefined4 **)(*(int *)(*(int *)(this + 0x104) + 0xc) + iVar1);
        uVar6 = RShellMemoryMalloc(*(int *)(this + 0xa0) * 0xc,"Object Animation Frame Vertices");
        *puVar7 = uVar6;
        fVar21 = (float)VectorSignedToFloat(*(int *)(param_2 + param_1 * 0x74 + -4) * iVar18,
                                            (byte)(in_fpscr >> 0x16) & 3);
        fVar21 = fVar21 / fVar26;
        fVar8 = (float)_floorf(fVar21);
        if ((local_38 <= (int)fVar8) && (iVar20 < param_1 + -1)) {
          iVar20 = iVar20 + 1;
          iVar10 = *(int *)(param_2 + iVar20 * 0x74 + 0x70);
          local_38 = *(int *)(param_2 + iVar20 * 0x74 + 0xe4);
        }
        if (param_1 == 1) {
          fVar8 = 0.0;
        }
        else {
          fVar22 = (float)VectorSignedToFloat(iVar10,(byte)(in_fpscr >> 0x16) & 3);
          fVar8 = (float)VectorSignedToFloat(local_38 - iVar10,(byte)(in_fpscr >> 0x16) & 3);
          fVar8 = (fVar21 - fVar22) / fVar8;
          uVar3 = in_fpscr & 0xfffffff;
          in_fpscr = uVar3 | (uint)(fVar8 < 0.0) << 0x1f;
          if ((SUB41(in_fpscr >> 0x1f,0)) ||
             (uVar3 = uVar3 | (uint)(fVar8 < 1.0) << 0x1f | (uint)(fVar8 == 1.0) << 0x1e,
             in_fpscr = uVar3 | (uint)NAN(fVar8) << 0x1c, bVar5 = (byte)(uVar3 >> 0x18),
             !(bool)(bVar5 >> 6 & 1) && bVar5 >> 7 == ((byte)(in_fpscr >> 0x1c) & 1))) {
            wprintf("RequestAnim Dodgy Tween %f\n",SUB84((double)fVar8,0),
                    (int)((ulonglong)(double)fVar8 >> 0x20));
          }
        }
        if (0 < *(int *)(this + 0xa0)) {
          if (param_1 == 1) {
            iVar17 = 0;
            iVar19 = 0;
            do {
              iVar17 = iVar17 + 1;
              puVar7 = (undefined4 *)
                       (*(int *)(*(int *)(param_2 + iVar20 * 0x74 + 0x24) + 0xa4) + iVar19);
              uVar6 = puVar7[1];
              uVar11 = puVar7[2];
              puVar14 = (undefined4 *)
                        (**(int **)(*(int *)(*(int *)(this + 0x104) + 0xc) + iVar1) + iVar19);
              iVar19 = iVar19 + 0xc;
              *puVar14 = *puVar7;
              puVar14[1] = uVar6;
              puVar14[2] = uVar11;
            } while (iVar17 < *(int *)(this + 0xa0));
          }
          else {
            iVar19 = 0;
            iVar17 = 0;
            do {
              iVar19 = iVar19 + 1;
              pfVar9 = (float *)(iVar17 + **(int **)(iVar1 + *(int *)(*(int *)(this + 0x104) + 0xc))
                                );
              pfVar12 = (float *)(iVar17 + *(int *)(*(int *)(param_2 + iVar20 * 0x74 + 0x98) + 0xa4)
                                 );
              pfVar15 = (float *)(iVar17 + *(int *)(*(int *)(param_2 + iVar20 * 0x74 + 0x24) + 0xa4)
                                 );
              iVar17 = iVar17 + 0xc;
              fVar21 = pfVar15[1];
              fVar22 = pfVar15[2];
              fVar23 = pfVar12[1];
              *pfVar9 = *pfVar15 + fVar8 * (*pfVar12 - *pfVar15);
              fVar24 = pfVar12[2];
              pfVar9[1] = fVar21 + fVar8 * (fVar23 - fVar21);
              pfVar9[2] = fVar22 + fVar8 * (fVar24 - fVar22);
            } while (iVar19 < *(int *)(this + 0xa0));
          }
        }
        iVar18 = iVar18 + 1;
      } while (iVar18 != iVar13);
    }
    *(undefined4 *)(*(int *)(this + 0x104) + 0x10) = 0;
  }
  else {
    pcVar16 = param_2;
    if (*(int *)(*(int *)(param_2 + 0x24) + 0xa0) == *(int *)(this + 0xa0)) {
      iVar10 = 0;
      pcVar4 = param_2;
LAB_00012800:
      iVar10 = iVar10 + 1;
      if (iVar10 != param_1) goto LAB_000127e8;
      *(uint *)this = *(uint *)this | 0x1000000;
      uVar6 = RShellMemoryMalloc(param_1 * 8,"Object Animation KeyFrames");
      iVar10 = 0;
      *(undefined4 *)(this + 0x108) = uVar6;
      pcVar16 = param_2;
      do {
        *(undefined4 *)(*(int *)(this + 0x108) + iVar10 * 8) = *(undefined4 *)(pcVar16 + 0x70);
        iVar13 = *(int *)(this + 0x108);
        uVar6 = RShellMemoryMalloc(*(int *)(this + 0xa0) * 0xc,"Object Anim KeyFrame Vertices");
        param_3 = (float)uVar25;
        *(undefined4 *)(iVar10 * 8 + iVar13 + 4) = uVar6;
        **(uint **)(pcVar16 + 0x24) = **(uint **)(pcVar16 + 0x24) | 0x2000000;
        if (0 < *(int *)(this + 0xa0)) {
          iVar20 = 0;
          iVar13 = 0;
          do {
            iVar20 = iVar20 + 1;
            puVar7 = (undefined4 *)(*(int *)(*(int *)(pcVar16 + 0x24) + 0xa4) + iVar13);
            uVar6 = puVar7[1];
            uVar11 = puVar7[2];
            puVar14 = (undefined4 *)(*(int *)(*(int *)(this + 0x108) + iVar10 * 8 + 4) + iVar13);
            iVar13 = iVar13 + 0xc;
            *puVar14 = *puVar7;
            puVar14[1] = uVar6;
            puVar14[2] = uVar11;
          } while (iVar20 < *(int *)(this + 0xa0));
        }
        iVar10 = iVar10 + 1;
        pcVar16 = pcVar16 + 0x74;
      } while (iVar10 != param_1);
      goto LAB_0001290c;
    }
LAB_000128d0:
    RShellError("Anim tween Vertices don\'t match Frame %i",*(undefined4 *)(pcVar16 + 0x70));
  }
  return;
LAB_000127e8:
  pcVar2 = pcVar4 + 0x98;
  pcVar16 = pcVar4 + 0x74;
  pcVar4 = pcVar4 + 0x74;
  if (*(int *)(*(int *)pcVar2 + 0xa0) != *(int *)(*(int *)(param_2 + 0x24) + 0xa0))
  goto LAB_000128d0;
  goto LAB_00012800;
}
