/*
 * mangled: _ZN8cRVapour2AIEv
 * demangled: cRVapour::AI()
 * address: 0006c79c
 * size: 940
 */

/* cRVapour::AI() */

void __thiscall cRVapour::AI(cRVapour *this)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  float *pfVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  float *pfVar9;
  float *pfVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  float *pfVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  int local_44;
  int local_40;
  int local_3c;
  int local_34;
  int local_30;

  iVar5 = *(int *)(this + 0x74);
  if (iVar5 < 2) {
    *(uint *)(this + 4) = *(uint *)(this + 4) & 0xffffffdf;
  }
  else {
    pfVar4 = *(float **)(this + 0x80);
    iVar11 = *(int *)(this + 0x24);
    iVar7 = iVar5 + -1;
    *(uint *)(this + 4) = *(uint *)(this + 4) | 0x20;
    *(int *)(iVar11 + 0xa0) = iVar7 * 4;
    if ((pfVar4 != (float *)0x0) && (0 < iVar5)) {
      iVar8 = *(int *)(this + 0x84);
      iVar6 = 0;
      do {
        fVar23 = *pfVar4;
        iVar6 = iVar6 + 1;
        if (*(float *)(iVar8 + 0x38) < fVar23) {
          *(float *)(iVar8 + 0x38) = fVar23;
        }
        iVar8 = iVar8 + 0x40;
      } while (iVar6 != iVar5);
    }
    uVar3 = DAT_0006cb50;
    uVar2 = DAT_0006cb4c;
    uVar1 = DAT_0006cb48;
    if (0 < iVar7) {
      iVar16 = 0;
      pfVar9 = *(float **)(this + 0x84);
      iVar13 = 0;
      iVar15 = *(int *)(iVar11 + 0xa4);
      local_44 = 0x18;
      local_40 = 0x10;
      local_3c = 8;
      iVar12 = 0;
      pfVar4 = pfVar9;
      pfVar10 = pfVar9;
      iVar6 = iVar15;
      iVar8 = iVar15;
      pfVar17 = pfVar9;
      local_34 = iVar15;
      do {
        fVar20 = *(float *)(this + 0x7c);
        fVar23 = pfVar10[2];
        fVar19 = pfVar10[1];
        fVar21 = pfVar10[0xe];
        fVar24 = pfVar10[0xd];
        *(float *)(local_34 + iVar13) = pfVar10[0xc] + fVar20 * *pfVar10;
        fVar18 = *pfVar17;
        *(float *)(local_34 + iVar13 + 8) = fVar21 + fVar20 * fVar23;
        fVar22 = pfVar17[0xc];
        fVar23 = pfVar17[2];
        fVar21 = pfVar17[0xe];
        *(float *)(local_34 + iVar13 + 4) = fVar24 + fVar20 * fVar19;
        fVar24 = -*(float *)(this + 0x7c);
        fVar19 = pfVar17[1];
        fVar25 = pfVar17[0xd];
        *(float *)(iVar8 + 0x14) = fVar21 + fVar24 * fVar23;
        fVar23 = pfVar9[2];
        fVar21 = pfVar9[0x1e];
        *(float *)(iVar8 + 0xc) = fVar22 + fVar24 * fVar18;
        fVar20 = *pfVar9;
        fVar22 = pfVar9[0x1c];
        *(float *)(iVar8 + 0x10) = fVar25 + fVar24 * fVar19;
        fVar24 = -*(float *)(this + 0x7c);
        fVar18 = pfVar9[1];
        fVar25 = pfVar9[0x1d];
        *(float *)(iVar6 + 0x20) = fVar21 + fVar24 * fVar23;
        fVar19 = pfVar4[2];
        fVar21 = pfVar4[0x1e];
        *(float *)(iVar6 + 0x18) = fVar22 + fVar24 * fVar20;
        *(float *)(iVar6 + 0x1c) = fVar25 + fVar24 * fVar18;
        fVar23 = *pfVar4;
        fVar20 = *(float *)(this + 0x7c);
        fVar24 = pfVar4[0x1c];
        fVar22 = pfVar4[0x1d];
        fVar18 = pfVar4[1];
        *(float *)(iVar15 + 0x2c) = fVar21 + fVar20 * fVar19;
        *(float *)(iVar15 + 0x24) = fVar24 + fVar20 * fVar23;
        *(float *)(iVar15 + 0x28) = fVar22 + fVar20 * fVar18;
        if (iVar5 == 2) {
          local_34 = *(int *)(iVar11 + 0x10c);
          iVar14 = *(int *)(local_34 + 0x10);
          *(undefined4 *)(iVar14 + iVar16 + 4) = uVar3;
          *(undefined4 *)(iVar14 + local_3c + 4) = uVar3;
LAB_0006cac0:
          local_30 = iVar14 + local_44;
          *(undefined4 *)(iVar14 + local_40 + 4) = uVar2;
          *(undefined4 *)(local_30 + 4) = uVar2;
        }
        else {
          if (iVar12 == 0) {
            local_34 = *(int *)(iVar11 + 0x10c);
            iVar14 = *(int *)(local_34 + 0x10);
            *(undefined4 *)(iVar14 + iVar16 + 4) = uVar3;
            *(undefined4 *)(iVar14 + local_3c + 4) = uVar3;
          }
          else {
            if (iVar5 + -2 == iVar12) {
              local_34 = *(int *)(iVar11 + 0x10c);
              iVar14 = *(int *)(local_34 + 0x10);
              *(undefined4 *)(iVar14 + iVar16 + 4) = uVar1;
              *(undefined4 *)(iVar14 + local_3c + 4) = uVar1;
              goto LAB_0006cac0;
            }
            local_34 = *(int *)(iVar11 + 0x10c);
            iVar14 = *(int *)(local_34 + 0x10);
            *(undefined4 *)(iVar14 + iVar16 + 4) = uVar1;
            *(undefined4 *)(iVar14 + local_3c + 4) = uVar1;
          }
          local_30 = iVar14 + local_44;
          *(undefined4 *)(iVar14 + local_40 + 4) = uVar1;
          *(undefined4 *)(local_30 + 4) = uVar1;
        }
        iVar12 = iVar12 + 1;
        iVar13 = iVar13 + 0x30;
        local_3c = local_3c + 0x20;
        local_40 = local_40 + 0x20;
        iVar16 = iVar16 + 0x20;
        local_44 = local_44 + 0x20;
        pfVar4 = pfVar4 + 0x10;
        iVar15 = iVar15 + 0x30;
        pfVar9 = pfVar9 + 0x10;
        iVar6 = iVar6 + 0x30;
        pfVar17 = pfVar17 + 0x10;
        iVar8 = iVar8 + 0x30;
        pfVar10 = pfVar10 + 0x10;
        if (iVar7 <= iVar12) goto LAB_0006cb1c;
        local_34 = *(int *)(iVar11 + 0xa4);
      } while( true );
    }
    local_34 = *(int *)(iVar11 + 0x10c);
LAB_0006cb1c:
    *(int *)(local_34 + 0x14) = iVar5 << 2;
  }
  return;
}
