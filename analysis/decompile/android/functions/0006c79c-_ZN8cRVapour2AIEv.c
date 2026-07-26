/*
 * mangled: _ZN8cRVapour2AIEv
 * demangled: cRVapour::AI()
 * address: 0006c79c
 * size: 940
 */

/* cRVapour::AI() */

void __thiscall cRVapour::AI(cRVapour *this)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  float *pfVar6;
  float *pfVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  float *pfVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  int local_44;
  int local_40;
  int local_3c;
  int local_34;
  int local_30;

  iVar2 = *(int *)(this + 0x74);
  if (iVar2 < 2) {
    *(uint *)(this + 4) = *(uint *)(this + 4) & 0xffffffdf;
  }
  else {
    pfVar1 = *(float **)(this + 0x80);
    iVar8 = *(int *)(this + 0x24);
    iVar4 = iVar2 + -1;
    *(uint *)(this + 4) = *(uint *)(this + 4) | 0x20;
    *(int *)(iVar8 + 0xa0) = iVar4 * 4;
    if ((pfVar1 != (float *)0x0) && (0 < iVar2)) {
      iVar5 = *(int *)(this + 0x84);
      iVar3 = 0;
      do {
        fVar20 = *pfVar1;
        iVar3 = iVar3 + 1;
        if (*(float *)(iVar5 + 0x38) < fVar20) {
          *(float *)(iVar5 + 0x38) = fVar20;
        }
        iVar5 = iVar5 + 0x40;
      } while (iVar3 != iVar2);
    }
    if (0 < iVar4) {
      iVar13 = 0;
      pfVar6 = *(float **)(this + 0x84);
      iVar10 = 0;
      iVar12 = *(int *)(iVar8 + 0xa4);
      local_44 = 0x18;
      local_40 = 0x10;
      local_3c = 8;
      iVar9 = 0;
      pfVar1 = pfVar6;
      pfVar7 = pfVar6;
      iVar3 = iVar12;
      iVar5 = iVar12;
      pfVar14 = pfVar6;
      local_34 = iVar12;
      do {
        fVar17 = *(float *)(this + 0x7c);
        fVar20 = pfVar7[2];
        fVar16 = pfVar7[1];
        fVar18 = pfVar7[0xe];
        fVar21 = pfVar7[0xd];
        *(float *)(local_34 + iVar10) = pfVar7[0xc] + fVar17 * *pfVar7;
        fVar15 = *pfVar14;
        *(float *)(local_34 + iVar10 + 8) = fVar18 + fVar17 * fVar20;
        fVar19 = pfVar14[0xc];
        fVar20 = pfVar14[2];
        fVar18 = pfVar14[0xe];
        *(float *)(local_34 + iVar10 + 4) = fVar21 + fVar17 * fVar16;
        fVar21 = -*(float *)(this + 0x7c);
        fVar16 = pfVar14[1];
        fVar22 = pfVar14[0xd];
        *(float *)(iVar5 + 0x14) = fVar18 + fVar21 * fVar20;
        fVar20 = pfVar6[2];
        fVar18 = pfVar6[0x1e];
        *(float *)(iVar5 + 0xc) = fVar19 + fVar21 * fVar15;
        fVar17 = *pfVar6;
        fVar19 = pfVar6[0x1c];
        *(float *)(iVar5 + 0x10) = fVar22 + fVar21 * fVar16;
        fVar21 = -*(float *)(this + 0x7c);
        fVar15 = pfVar6[1];
        fVar22 = pfVar6[0x1d];
        *(float *)(iVar3 + 0x20) = fVar18 + fVar21 * fVar20;
        fVar16 = pfVar1[2];
        fVar18 = pfVar1[0x1e];
        *(float *)(iVar3 + 0x18) = fVar19 + fVar21 * fVar17;
        *(float *)(iVar3 + 0x1c) = fVar22 + fVar21 * fVar15;
        fVar20 = *pfVar1;
        fVar17 = *(float *)(this + 0x7c);
        fVar21 = pfVar1[0x1c];
        fVar19 = pfVar1[0x1d];
        fVar15 = pfVar1[1];
        *(float *)(iVar12 + 0x2c) = fVar18 + fVar17 * fVar16;
        *(float *)(iVar12 + 0x24) = fVar21 + fVar17 * fVar20;
        *(float *)(iVar12 + 0x28) = fVar19 + fVar17 * fVar15;
        if (iVar2 == 2) {
          local_34 = *(int *)(iVar8 + 0x10c);
          iVar11 = *(int *)(local_34 + 0x10);
          *(undefined4 *)(iVar11 + iVar13 + 4) = 0;
          *(undefined4 *)(iVar11 + local_3c + 4) = 0;
LAB_0006cac0:
          local_30 = iVar11 + local_44;
          *(undefined4 *)(iVar11 + local_40 + 4) = 0x3f800000;
          *(undefined4 *)(local_30 + 4) = 0x3f800000;
        }
        else {
          if (iVar9 == 0) {
            local_34 = *(int *)(iVar8 + 0x10c);
            iVar11 = *(int *)(local_34 + 0x10);
            *(undefined4 *)(iVar11 + iVar13 + 4) = 0;
            *(undefined4 *)(iVar11 + local_3c + 4) = 0;
          }
          else {
            if (iVar2 + -2 == iVar9) {
              local_34 = *(int *)(iVar8 + 0x10c);
              iVar11 = *(int *)(local_34 + 0x10);
              *(undefined4 *)(iVar11 + iVar13 + 4) = 0x3f000000;
              *(undefined4 *)(iVar11 + local_3c + 4) = 0x3f000000;
              goto LAB_0006cac0;
            }
            local_34 = *(int *)(iVar8 + 0x10c);
            iVar11 = *(int *)(local_34 + 0x10);
            *(undefined4 *)(iVar11 + iVar13 + 4) = 0x3f000000;
            *(undefined4 *)(iVar11 + local_3c + 4) = 0x3f000000;
          }
          local_30 = iVar11 + local_44;
          *(undefined4 *)(iVar11 + local_40 + 4) = 0x3f000000;
          *(undefined4 *)(local_30 + 4) = 0x3f000000;
        }
        iVar9 = iVar9 + 1;
        iVar10 = iVar10 + 0x30;
        local_3c = local_3c + 0x20;
        local_40 = local_40 + 0x20;
        iVar13 = iVar13 + 0x20;
        local_44 = local_44 + 0x20;
        pfVar1 = pfVar1 + 0x10;
        iVar12 = iVar12 + 0x30;
        pfVar6 = pfVar6 + 0x10;
        iVar3 = iVar3 + 0x30;
        pfVar14 = pfVar14 + 0x10;
        iVar5 = iVar5 + 0x30;
        pfVar7 = pfVar7 + 0x10;
        if (iVar4 <= iVar9) goto LAB_0006cb1c;
        local_34 = *(int *)(iVar8 + 0xa4);
      } while( true );
    }
    local_34 = *(int *)(iVar8 + 0x10c);
LAB_0006cb1c:
    *(int *)(local_34 + 0x14) = iVar2 << 2;
  }
  return;
}
