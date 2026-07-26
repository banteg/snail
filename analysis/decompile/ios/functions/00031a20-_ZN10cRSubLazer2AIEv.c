/*
 * mangled: _ZN10cRSubLazer2AIEv
 * demangled: cRSubLazer::AI()
 * address: 00031a20
 * size: 1012
 */

/* cRSubLazer::AI() */

void __thiscall cRSubLazer::AI(cRSubLazer *this)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  uint uVar12;
  uint uVar13;

  if (*(char *)(*(int *)(this + 0x7c) + 0x12) != '\0') {
    return;
  }
  if (*(int *)(this + 0x74) == 1) {
    fVar10 = *(float *)(this + 0x8c);
    *(float *)(this + 0x8c) = fVar10 + *(float *)(this + 0x90);
    if (1.0 < fVar10 + *(float *)(this + 0x90)) {
      *(undefined4 *)(this + 0x74) = 2;
      return;
    }
    fVar11 = *(float *)(this + 0x5c);
    fVar10 = *(float *)(this + 0x80);
    fVar7 = *(float *)(this + 0x84);
    fVar6 = *(float *)(this + 0x88);
    fVar9 = *(float *)(this + 0x60) + fVar7;
    *(float *)(this + 0x5c) = fVar11 + fVar10;
    fVar8 = *(float *)(this + 100) + fVar6;
    *(float *)(this + 0x60) = fVar9;
    *(float *)(this + 100) = fVar8;
    if ((fVar9 < 0.0) || (fVar8 < *(float *)(*(int *)(this + 0x7c) + 0x11c3c))) goto LAB_00031aec;
    iVar2 = *(int *)PTR__Game_001b60b8;
    uVar12 = (uint)(*(float *)(this + 0x5c) + 4.0);
    if (6 < (int)uVar12) {
      uVar12 = 7;
    }
    uVar13 = (uint)*(float *)(this + 100);
    if (0xdaa < (int)uVar13) {
      uVar13 = 0xdab;
    }
    uVar1 = *(undefined4 *)(this + 0x5c);
    uVar3 = *(undefined4 *)(this + 0x60);
    if ((*(char *)((uVar12 & ~((int)uVar12 >> 0x1f)) * 0x44 +
                   (uVar13 & ~((int)uVar13 >> 0x1f)) * 0x220 + iVar2 + 0x86000) == '\x0e') &&
       (fVar9 < 7.0)) {
      if ((*(uint *)(this + 4) & 0x200) == 0) goto LAB_00031b4c;
      if ((*(uint *)(this + 4) & 0x40) == 0) {
        iVar4 = *(int *)(this + 0xc);
        if (iVar4 != 0) {
          *(undefined4 *)(iVar4 + 8) = *(undefined4 *)(this + 8);
        }
        if (*(int *)(this + 8) == 0) {
          *(int *)(iVar2 + 0x35c) = iVar4;
        }
        else {
          *(int *)(*(int *)(this + 8) + 0xc) = iVar4;
        }
        *(undefined4 *)(this + 0xc) = *(undefined4 *)(iVar2 + 0x360);
        *(cRSubLazer **)(iVar2 + 0x360) = this;
        *(uint *)(this + 4) = *(uint *)(this + 4) & 0xfffffdff;
        goto LAB_00031b40;
      }
      goto LAB_00031b58;
    }
    uVar12 = (int)*(float *)(this + 100);
    if (0xdaa < (int)*(float *)(this + 100)) {
      uVar12 = 0xdab;
    }
    uVar12 = uVar12 & ~((int)uVar12 >> 0x1f);
    iVar4 = uVar12 * 0xdc + iVar2;
    uVar13 = *(uint *)(&DAT_00256d50 + iVar4);
    if ((uVar13 & 0x40) != 0) {
      iVar5 = cRPath::SearchPos(*(cRPath **)(*(int *)(&DAT_00256de8 + iVar4) + 0x2c),
                                fVar11 + fVar10 + fVar10,fVar9 + fVar7,fVar8 + fVar6,fVar10 * 1.05,
                                fVar7 * 1.05,fVar6 * 1.05,*(int *)(&DAT_00256de8 + iVar4),uVar1,
                                uVar3);
      if (iVar5 != 0) goto LAB_00031aec;
      uVar13 = *(uint *)(&DAT_00256d50 + iVar4);
    }
    if ((uVar13 & 0x80) == 0) {
      return;
    }
    iVar2 = *(int *)(uVar12 * 0xdc + iVar2 + 0x256dec);
    iVar2 = cRPath::SearchPos(*(cRPath **)(iVar2 + 0x2c),
                              *(float *)(this + 0x5c) + *(float *)(this + 0x80),
                              *(float *)(this + 0x60) + *(float *)(this + 0x84),
                              *(float *)(this + 100) + *(float *)(this + 0x88),
                              *(float *)(this + 0x80) * 1.05,*(float *)(this + 0x84) * 1.05,
                              *(float *)(this + 0x88) * 1.05,iVar2,uVar1,uVar3);
    if (iVar2 == 0) {
      return;
    }
    iVar2 = *(int *)PTR__Game_001b60b8;
    if ((*(uint *)(this + 4) & 0x200) != 0) {
      if ((*(uint *)(this + 4) & 0x40) == 0) {
        iVar4 = *(int *)(this + 0xc);
        if (iVar4 != 0) {
          *(undefined4 *)(iVar4 + 8) = *(undefined4 *)(this + 8);
        }
        iVar5 = *(int *)(this + 8);
        if (iVar5 != 0) {
          *(int *)(iVar5 + 0xc) = iVar4;
        }
        if (iVar5 == 0) {
          *(int *)(iVar2 + 0x35c) = iVar4;
        }
        *(undefined4 *)(this + 0xc) = *(undefined4 *)(iVar2 + 0x360);
        *(cRSubLazer **)(iVar2 + 0x360) = this;
        *(uint *)(this + 4) = *(uint *)(this + 4) & 0xfffffdff;
        goto LAB_00031b40;
      }
      goto LAB_00031b58;
    }
  }
  else {
    if (*(int *)(this + 0x74) != 2) {
      return;
    }
LAB_00031aec:
    iVar2 = *(int *)PTR__Game_001b60b8;
    if ((*(uint *)(this + 4) & 0x200) != 0) {
      if ((*(uint *)(this + 4) & 0x40) == 0) {
        iVar4 = *(int *)(this + 0xc);
        if (iVar4 != 0) {
          *(undefined4 *)(iVar4 + 8) = *(undefined4 *)(this + 8);
        }
        if (*(int *)(this + 8) == 0) {
          *(int *)(iVar2 + 0x35c) = iVar4;
        }
        else {
          *(int *)(*(int *)(this + 8) + 0xc) = iVar4;
        }
        *(undefined4 *)(this + 0xc) = *(undefined4 *)(iVar2 + 0x360);
        *(cRSubLazer **)(iVar2 + 0x360) = this;
        *(uint *)(this + 4) = *(uint *)(this + 4) & 0xfffffdff;
        goto LAB_00031b40;
      }
LAB_00031b58:
      RShellError("List remove NEXTBOD");
      goto LAB_00031b40;
    }
  }
LAB_00031b4c:
  RShellError("List remove");
LAB_00031b40:
  *(undefined4 *)(this + 0x74) = 0;
  return;
}
