/*
 * mangled: _ZN9cRSubGame20PlaceParcelsSurvivalEv
 * demangled: cRSubGame::PlaceParcelsSurvival()
 * address: 0001f3a0
 * size: 840
 */

/* cRSubGame::PlaceParcelsSurvival() */

void __thiscall cRSubGame::PlaceParcelsSurvival(cRSubGame *this)

{
  cRPath *this_00;
  int iVar1;
  int iVar2;
  cRSubGame *pcVar3;
  uint uVar4;
  int iVar5;
  undefined4 *puVar6;
  int iVar7;
  bool bVar8;
  uint in_fpscr;
  float fVar9;
  tMatrix atStack_60 [48];
  undefined4 local_30;
  undefined4 local_2c;
  float fStack_20;

  fVar9 = (float)VectorSignedToFloat(*(undefined4 *)(this + 0x3c),(byte)(in_fpscr >> 0x16) & 3);
  iVar5 = (int)((fVar9 * 50.0) / 100.0 + *(float *)(this + 0x48) * 50.0) + 1;
  *(int *)(this + 0x12fc) = iVar5;
  *(int *)(this + 0x1304) = iVar5;
  puVar6 = (undefined4 *)&_gGroup0;
  do {
    iVar5 = 0;
    puVar6[0x80] = 0;
    puVar6 = puVar6 + 0x83;
  } while (puVar6 != &_gParcelGroupSurvival0);
  iVar1 = *(int *)(this + 0x6c);
  if (iVar1 < 1) {
    iVar7 = 0;
  }
  else {
    pcVar3 = this + 0x1e41d8;
    iVar7 = 0;
    do {
      if (((*(uint *)pcVar3 & 1) != 0) && (*(int *)(pcVar3 + 0x90) == 0)) {
        (&_gParcelGroupSurvival0)[iVar7] = iVar5;
        iVar1 = *(int *)(this + 0x6c);
        iVar7 = iVar7 + 1;
      }
      iVar5 = iVar5 + 1;
      pcVar3 = pcVar3 + 0xdc;
    } while (iVar5 < iVar1);
  }
  iVar1 = 0;
  iVar5 = *(int *)(this + 0x12fc);
  if (0 < *(int *)(this + 0x12fc)) {
    iVar5 = iVar7;
  }
  if (0 < iVar5) {
    do {
      fVar9 = (float)VectorSignedToFloat(iVar7,(byte)(in_fpscr >> 0x16) & 3);
      fVar9 = (float)RAND(fVar9,"P3");
      iVar5 = (int)fVar9;
      iVar2 = (&_gParcelGroupSurvival0)[iVar5];
      uVar4 = *(uint *)(this + iVar2 * 0xdc + 0x1e41d8);
      *(uint *)(this + iVar2 * 0xdc + 0x1e41d8) = uVar4 | 0x11;
      *(float *)(this + iVar2 * 0xdc + 0x1e4260) = *(float *)(this + iVar2 * 0xdc + 0x1e4260) + 1.0;
      if ((uVar4 & 0x20) != 0) {
        *(float *)(this + iVar2 * 0xdc + 0x1e425c) = -*(float *)(this + iVar2 * 0xdc + 0x1e425c);
      }
      if ((uVar4 & 0x4000) != 0) {
        fVar9 = (float)VectorSignedToFloat(iVar2,(byte)(in_fpscr >> 0x16) & 3);
        *(float *)(this + iVar2 * 0xdc + 0x1e4264) =
             *(float *)(this + iVar2 * 0xdc + 0x1e4264) + fVar9 + 0.5;
      }
      iVar7 = iVar7 + -1;
      if (iVar5 < iVar7) {
        puVar6 = &_gParcelGroupSurvival0 + iVar5 + 1;
        do {
          iVar5 = iVar5 + 1;
          puVar6[-1] = *puVar6;
          puVar6 = puVar6 + 1;
        } while (iVar5 < iVar7);
      }
      iVar1 = iVar1 + 1;
      iVar2 = *(int *)(this + 0x12fc);
      bVar8 = iVar2 == iVar1;
      iVar5 = iVar2 - iVar1;
      if (iVar2 > iVar1) {
        bVar8 = iVar7 == 0;
        iVar5 = iVar7;
      }
    } while (!bVar8 && iVar5 < 0 == (iVar2 <= iVar1 && SBORROW4(iVar2,iVar1)));
  }
  iVar7 = 0;
  *(int *)(this + 0x12fc) = iVar1;
  wprintf("Challenge parcel count %i\n",iVar1);
  iVar5 = *(int *)(this + 0x6c);
  if (0 < iVar5) {
    pcVar3 = this + 0x1e41d8;
    do {
      if (((*(uint *)pcVar3 & 1) != 0) && ((*(uint *)pcVar3 & 0x40) != 0)) {
        iVar5 = *(int *)(pcVar3 + 0x98);
        this_00 = *(cRPath **)(iVar5 + 0x2c);
        iVar1 = ((int)(iVar5 - ((*(byte *)(iVar5 + 0x32) & 7) * 0x44 + 0x85fd0 +
                               *(int *)PTR__Game_001b60b8)) >> 2) * -0xf0f0f0f;
        iVar5 = iVar1 + 7;
        if (-1 < iVar1) {
          iVar5 = iVar1;
        }
        uVar4 = (int)*(float *)(pcVar3 + 0x8c) - (iVar5 >> 3);
        uVar4 = uVar4 & ~((int)uVar4 >> 0x1f);
        if (*(int *)(this_00 + 0x2c) == 0x39) {
          cRPath::HalfPipePos(this_00,*(float *)(uVar4 * 0xa8 + *(int *)(this_00 + 0x4c) + 0xa0),
                              *(float *)(pcVar3 + 0x84),*(float *)(pcVar3 + 0x88),atStack_60,
                              &fStack_20);
        }
        else {
          if (*(int *)(this_00 + 0x2c) != 0x3a) {
            cRPath::GetPos(this_00,(tVector *)(this + iVar7 * 0xdc + 0x1e425c),uVar4,iVar5 >> 3,
                           (tVector *)(this + iVar7 * 0xdc + 0x1e425c));
            iVar5 = *(int *)(this + 0x6c);
            goto LAB_0001f614;
          }
          cRPath::HalfPolePos(this_00,*(float *)(uVar4 * 0xa8 + *(int *)(this_00 + 0x4c) + 0xa0),
                              *(float *)(pcVar3 + 0x84),*(float *)(pcVar3 + 0x88),atStack_60,
                              &fStack_20);
        }
        *(undefined4 *)(pcVar3 + 0x84) = local_30;
        *(undefined4 *)(pcVar3 + 0x88) = local_2c;
        iVar5 = *(int *)(this + 0x6c);
      }
LAB_0001f614:
      iVar7 = iVar7 + 1;
      pcVar3 = pcVar3 + 0xdc;
    } while (iVar7 < iVar5);
  }
  return;
}
