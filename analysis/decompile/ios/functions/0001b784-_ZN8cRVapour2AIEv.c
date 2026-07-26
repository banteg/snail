/*
 * mangled: _ZN8cRVapour2AIEv
 * demangled: cRVapour::AI()
 * address: 0001b784
 * size: 856
 */

/* cRVapour::AI() */

void __thiscall cRVapour::AI(cRVapour *this)

{
  float *pfVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  float *pfVar6;
  int iVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;

  if (*(int *)(this + 0x74) < 2) {
    *(uint *)(this + 4) = *(uint *)(this + 4) & 0xffffffdf;
    return;
  }
  *(uint *)(this + 4) = *(uint *)(this + 4) | 0x20;
  *(int *)(*(int *)(this + 0x24) + 0xa0) = *(int *)(this + 0x74) * 4 + -4;
  pfVar1 = *(float **)(this + 0x80);
  if (pfVar1 == (float *)0x0) {
    iVar3 = *(int *)(this + 0x74);
  }
  else {
    iVar3 = *(int *)(this + 0x74);
    if (0 < iVar3) {
      iVar7 = 0;
      while( true ) {
        iVar5 = iVar7 * 0x40 + *(int *)(this + 0x84);
        iVar7 = iVar7 + 1;
        if (*(float *)(iVar5 + 0x38) < *pfVar1) {
          *(float *)(iVar5 + 0x38) = *pfVar1;
          iVar3 = *(int *)(this + 0x74);
        }
        if (iVar3 <= iVar7) break;
        pfVar1 = *(float **)(this + 0x80);
      }
    }
  }
  if (0 < iVar3 + -1) {
    iVar5 = 0;
    iVar7 = 0;
    do {
      while( true ) {
        iVar3 = iVar5 * 0x40;
        fVar8 = *(float *)(this + 0x7c);
        pfVar1 = (float *)(iVar7 + *(int *)(*(int *)(this + 0x24) + 0xa4));
        pfVar6 = (float *)(iVar3 + *(int *)(this + 0x84));
        fVar10 = pfVar6[0xd];
        fVar9 = pfVar6[2];
        fVar11 = pfVar6[1];
        fVar12 = pfVar6[0xe];
        *pfVar1 = pfVar6[0xc] + fVar8 * *pfVar6;
        pfVar1[1] = fVar10 + fVar8 * fVar11;
        pfVar1[2] = fVar12 + fVar8 * fVar9;
        fVar8 = *(float *)(this + 0x7c);
        pfVar1 = (float *)(*(int *)(*(int *)(this + 0x24) + 0xa4) + 0xc + iVar7);
        pfVar6 = (float *)(iVar3 + *(int *)(this + 0x84));
        fVar10 = pfVar6[0xd];
        fVar9 = pfVar6[2];
        fVar11 = pfVar6[1];
        fVar12 = pfVar6[0xe];
        *pfVar1 = pfVar6[0xc] - fVar8 * *pfVar6;
        pfVar1[1] = fVar10 - fVar8 * fVar11;
        pfVar1[2] = fVar12 - fVar8 * fVar9;
        fVar8 = *(float *)(this + 0x7c);
        pfVar1 = (float *)(*(int *)(*(int *)(this + 0x24) + 0xa4) + 0x18 + iVar7);
        iVar4 = *(int *)(this + 0x84) + 0x40 + iVar3;
        pfVar6 = (float *)(*(int *)(this + 0x84) + iVar3);
        fVar9 = *(float *)(iVar4 + 0x30);
        fVar11 = *pfVar6;
        fVar10 = *(float *)(iVar4 + 0x34);
        fVar12 = pfVar6[1];
        pfVar1[2] = *(float *)(iVar4 + 0x38) - fVar8 * pfVar6[2];
        pfVar1[1] = fVar10 - fVar8 * fVar12;
        *pfVar1 = fVar9 - fVar8 * fVar11;
        fVar8 = *(float *)(this + 0x7c);
        pfVar1 = (float *)(*(int *)(*(int *)(this + 0x24) + 0xa4) + 0x24 + iVar7);
        iVar4 = *(int *)(this + 0x84) + 0x40 + iVar3;
        pfVar6 = (float *)(*(int *)(this + 0x84) + iVar3);
        fVar10 = *(float *)(iVar4 + 0x34);
        fVar9 = pfVar6[2];
        fVar11 = pfVar6[1];
        fVar12 = *(float *)(iVar4 + 0x38);
        *pfVar1 = *(float *)(iVar4 + 0x30) + fVar8 * *pfVar6;
        pfVar1[1] = fVar10 + fVar8 * fVar11;
        pfVar1[2] = fVar12 + fVar8 * fVar9;
        if (*(int *)(this + 0x74) != 2) break;
        uVar2 = 0;
        iVar3 = *(int *)(*(int *)(*(int *)(this + 0x24) + 0x10c) + 0x10) + iVar5 * 0x20;
LAB_0001ba90:
        *(undefined4 *)(iVar3 + 4) = uVar2;
        *(undefined4 *)
         (iVar5 * 0x20 + *(int *)(*(int *)(*(int *)(this + 0x24) + 0x10c) + 0x10) + 0xc) = uVar2;
        uVar2 = 0x3f800000;
        iVar3 = iVar5 * 0x20 + *(int *)(*(int *)(*(int *)(this + 0x24) + 0x10c) + 0x10);
LAB_0001ba34:
        iVar4 = iVar5 * 0x20;
        *(undefined4 *)(iVar3 + 0x14) = uVar2;
        iVar5 = iVar5 + 1;
        iVar7 = iVar7 + 0x30;
        *(undefined4 *)(iVar4 + *(int *)(*(int *)(*(int *)(this + 0x24) + 0x10c) + 0x10) + 0x1c) =
             uVar2;
        iVar3 = *(int *)(this + 0x74);
        if (iVar3 + -1 <= iVar5) goto LAB_0001ba64;
      }
      if (iVar5 != 0) {
        if (*(int *)(this + 0x74) + -2 == iVar5) {
          uVar2 = 0x3f000000;
          iVar3 = *(int *)(*(int *)(*(int *)(this + 0x24) + 0x10c) + 0x10) + iVar5 * 0x20;
          goto LAB_0001ba90;
        }
        iVar3 = iVar5 * 0x20;
        uVar2 = 0x3f000000;
        *(undefined4 *)(iVar3 + *(int *)(*(int *)(*(int *)(this + 0x24) + 0x10c) + 0x10) + 4) =
             0x3f000000;
        *(undefined4 *)(iVar3 + *(int *)(*(int *)(*(int *)(this + 0x24) + 0x10c) + 0x10) + 0xc) =
             0x3f000000;
        iVar3 = iVar3 + *(int *)(*(int *)(*(int *)(this + 0x24) + 0x10c) + 0x10);
        goto LAB_0001ba34;
      }
      iVar5 = 1;
      iVar7 = iVar7 + 0x30;
      *(undefined4 *)(*(int *)(*(int *)(*(int *)(this + 0x24) + 0x10c) + 0x10) + 4) = 0;
      *(undefined4 *)(*(int *)(*(int *)(*(int *)(this + 0x24) + 0x10c) + 0x10) + 0xc) = 0;
      *(undefined4 *)(*(int *)(*(int *)(*(int *)(this + 0x24) + 0x10c) + 0x10) + 0x14) = 0x3f000000;
      *(undefined4 *)(*(int *)(*(int *)(*(int *)(this + 0x24) + 0x10c) + 0x10) + 0x1c) = 0x3f000000;
      iVar3 = *(int *)(this + 0x74);
    } while (1 < iVar3 + -1);
  }
LAB_0001ba64:
  *(int *)(*(int *)(*(int *)(this + 0x24) + 0x10c) + 0x14) = iVar3 << 2;
  return;
}
