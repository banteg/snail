/*
 * mangled: _ZN7cRIntro2AIEv
 * demangled: cRIntro::AI()
 * address: 00067ab8
 * size: 1520
 */

/* cRIntro::AI() */

void __thiscall cRIntro::AI(cRIntro *this)

{
  byte bVar1;
  bool bVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  undefined4 uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int *piVar11;
  uint in_fpscr;
  uint uVar12;
  float fVar13;
  float fVar14;
  int iVar15;

  iVar8 = DAT_00067ec0;
  iVar9 = DAT_00067ebc + 0x67ad4;
  uVar12 = in_fpscr & 0xfffffff |
           (uint)(*(float *)(**(int **)(iVar9 + DAT_00067ec0) + 0x3c) ==
                 *(float *)(**(int **)(iVar9 + DAT_00067ec0) + 0x44)) << 0x1e;
  if (!SUB41(uVar12 >> 0x1e,0)) {
    UnInit();
    Init(this);
  }
  iVar5 = RShellInkey();
  if ((iVar5 == 0) &&
     ((*(uint *)(*(int *)(**(int **)(iVar9 + iVar8) + 0x224) + 0x30) & 0x4000) == 0)) {
    iVar5 = *(int *)(this + 0x30);
    uVar7 = *(uint *)(iVar5 + 0x194);
  }
  else {
    *(undefined4 *)(this + 0x10) = DAT_00067ea8;
    if (this[4] != (cRIntro)0x0) {
      cRBorder::UnHideInit(*(cRBorder **)(this + 0x30));
      cRBorder::UnHideInit(*(cRBorder **)(this + 0x34));
      cRBorder::UnHideInit(*(cRBorder **)(this + 0x40));
      cRBorder::UnHideInit(*(cRBorder **)(this + 0x38));
      cRBorder::UnHideInit(*(cRBorder **)(this + 0x3c));
      cRBorder::UnHideInit(*(cRBorder **)(this + 0x44));
      cRBorder::UnHideInit(*(cRBorder **)(this + 0x48));
      cRMouse::SetActive((cRMouse *)(**(int **)(iVar9 + iVar8) + 0x228));
      this[4] = (cRIntro)0x0;
    }
    iVar5 = *(int *)(this + 0x30);
    uVar7 = *(uint *)(iVar5 + 0x194);
  }
  if ((uVar7 & 0x20) == 0) {
    uVar7 = *(uint *)(*(int *)(this + 0x34) + 0x194);
    if ((uVar7 & 0x20) == 0) {
      uVar7 = *(uint *)(*(int *)(this + 0x38) + 0x194);
      if ((uVar7 & 0x20) != 0) {
        piVar11 = *(int **)(iVar9 + iVar8);
        *(uint *)(*(int *)(this + 0x38) + 0x194) = uVar7 & 0xffffffdf;
        *(undefined4 *)(gOFOData + *piVar11 + 0x1ebc) = 0;
        UnInit();
        iVar8 = *piVar11;
        *(undefined4 *)(iVar8 + 0x15c) = 10;
        *(undefined4 *)(iVar8 + 0x71900) = 4;
        *(undefined1 *)(iVar8 + 0x2c0) = 1;
        return;
      }
      uVar7 = *(uint *)(*(int *)(this + 0x40) + 0x194);
      if ((uVar7 & 0x20) != 0) {
        piVar11 = *(int **)(iVar9 + iVar8);
        *(uint *)(*(int *)(this + 0x40) + 0x194) = uVar7 & 0xffffffdf;
        *(undefined4 *)(gOFOData + *piVar11 + 0x1ebc) = 0;
        UnInit();
        iVar8 = *piVar11;
        *(undefined1 *)(iVar8 + 0x2c0) = 1;
        *(undefined4 *)(iVar8 + 0x15c) = 10;
        *(undefined4 *)(iVar8 + 0x71900) = 7;
        cRTutorial::Init((cRTutorial *)(iVar8 + 0x71924));
        *(undefined1 *)(*(int *)(iVar9 + DAT_00067ec4) + 0xc0) = 1;
        return;
      }
      uVar7 = *(uint *)(*(int *)(this + 0x3c) + 0x194);
      if ((uVar7 & 0x20) != 0) {
        piVar11 = *(int **)(iVar9 + iVar8);
        *(uint *)(*(int *)(this + 0x3c) + 0x194) = uVar7 & 0xffffffdf;
        *(undefined4 *)(gOFOData + *piVar11 + 0x1ebc) = 0;
        UnInit();
        iVar8 = *piVar11;
        *(undefined1 *)(iVar8 + 0x2c0) = 1;
        *(undefined4 *)(iVar8 + 0x15c) = 10;
        *(undefined4 *)(iVar8 + 0x71900) = 1;
        return;
      }
      uVar7 = *(uint *)(*(int *)(this + 0x48) + 0x194);
      if ((uVar7 & 0x20) == 0) {
        uVar7 = *(uint *)(*(int *)(this + 0x44) + 0x194);
        if ((uVar7 & 0x20) != 0) {
          *(uint *)(*(int *)(this + 0x44) + 0x194) = uVar7 & 0xffffffdf;
          UnInit();
          iVar5 = **(int **)(iVar9 + iVar8);
          *(undefined1 *)(iVar5 + 0x2c0) = 1;
          *(undefined4 *)(iVar5 + 0x15c) = 0x1f;
        }
      }
      else {
        *(uint *)(*(int *)(this + 0x48) + 0x194) = uVar7 & 0xffffffdf;
        UnInit();
        iVar5 = **(int **)(iVar9 + iVar8);
        *(undefined1 *)(iVar5 + 0x2c0) = 1;
        *(undefined4 *)(iVar5 + 0x15c) = 4;
      }
      fVar13 = *(float *)(this + 0x10) + *(float *)(this + 0x14);
      uVar12 = uVar12 & 0xfffffff | (uint)(fVar13 < DAT_00067eac) << 0x1f |
               (uint)(fVar13 == DAT_00067eac) << 0x1e;
      uVar7 = uVar12 | (uint)(NAN(fVar13) || NAN(DAT_00067eac)) << 0x1c;
      *(float *)(this + 0x10) = fVar13;
      bVar1 = (byte)(uVar12 >> 0x18);
      if ((bool)(bVar1 >> 6 & 1) || bVar1 >> 7 != ((byte)(uVar7 >> 0x1c) & 1)) {
        return;
      }
      iVar5 = 0;
      *(undefined4 *)(this + 0x10) = DAT_00067ea8;
      fVar4 = DAT_00067eb8;
      fVar3 = DAT_00067eb4;
      fVar13 = DAT_00067eb0;
      do {
        iVar10 = *(int *)this;
        iVar5 = iVar5 + 1;
        if (iVar10 == 1) {
          uVar6 = gRMathRand2();
          piVar11 = *(int **)(iVar9 + iVar8);
          iVar15 = *piVar11;
          fVar14 = (float)VectorSignedToFloat(uVar6,(byte)(uVar7 >> 0x16) & 3);
          iVar10 = (int)(fVar14 * fVar13 * fVar3) + 0xb;
          if (*(int *)(gGroup0 + iVar15 + iVar10 * 0x38 + 0xce69c) == 1) {
            cRSubHighScore::MiniLoad((cRSubHighScore *)(gGroup0 + iVar15 + 0xce694),iVar10);
            *(undefined4 *)(*piVar11 + 0x71900) = 1;
            iVar10 = *(int *)this;
            bVar2 = true;
          }
          else {
LAB_00067c30:
            iVar10 = *(int *)this;
LAB_00067c34:
            bVar2 = false;
          }
        }
        else if (iVar10 == 3) {
          uVar6 = gRMathRand2();
          piVar11 = *(int **)(iVar9 + iVar8);
          iVar15 = *piVar11;
          fVar14 = (float)VectorSignedToFloat(uVar6,(byte)(uVar7 >> 0x16) & 3);
          iVar10 = (int)(fVar14 * fVar13 * fVar4) + 0x16;
          if (*(int *)(gGroup0 + iVar15 + iVar10 * 0x38 + 0xce69c) != 1) goto LAB_00067c30;
          cRSubHighScore::MiniLoad((cRSubHighScore *)(gGroup0 + iVar15 + 0xce694),iVar10);
          *(undefined4 *)(*piVar11 + 0x71900) = 4;
          iVar10 = *(int *)this;
          bVar2 = true;
        }
        else {
          if (iVar10 != 0) goto LAB_00067c34;
          uVar6 = gRMathRand2();
          piVar11 = *(int **)(iVar9 + iVar8);
          iVar10 = *piVar11;
          fVar14 = (float)VectorSignedToFloat(uVar6,(byte)(uVar7 >> 0x16) & 3);
          iVar15 = (int)(fVar14 * fVar13 * fVar3);
          if (*(int *)(gGroup0 + iVar10 + iVar15 * 0x38 + 0xce69c) != 1) goto LAB_00067c30;
          cRSubHighScore::MiniLoad((cRSubHighScore *)(gGroup0 + iVar10 + 0xce694),iVar15);
          *(undefined4 *)(*piVar11 + 0x71900) = 0;
          iVar10 = *(int *)this;
          bVar2 = true;
        }
        iVar10 = iVar10 + 1;
        if (iVar10 == 5) {
          iVar10 = 0;
        }
        *(int *)this = iVar10;
        if (bVar2) {
          if (iVar5 < 1000) {
            iVar8 = **(int **)(iVar9 + iVar8);
            this[4] = (cRIntro)0x1;
            uVar6 = DAT_00067ea8;
            *(undefined4 *)(iVar8 + 0x15c) = 10;
            *(undefined4 *)(this + 8) = uVar6;
            *(undefined1 *)(iVar8 + 0x2c0) = 1;
            uVar6 = DAT_00067ecc;
            *(undefined4 *)(gDirectory + iVar8 + 0x254c) = 2;
            *(undefined4 *)(this + 0xc) = uVar6;
            gDirectory[iVar8 + 0x2545] = 1;
            gDirectory[iVar8 + 0x2544] = 1;
            UnInit();
            return;
          }
          goto LAB_00067ed8;
        }
        if (iVar5 == 1000) {
LAB_00067ed8:
          *(undefined4 *)(this + 8) = DAT_00067ec8;
          *(undefined4 *)(this + 0xc) = DAT_00067ecc;
          return;
        }
      } while( true );
    }
    *(uint *)(*(int *)(this + 0x34) + 0x194) = uVar7 & 0xffffffdf;
    UnInit();
    iVar5 = *(int *)(iVar9 + DAT_00067ec4);
    iVar8 = **(int **)(iVar9 + iVar8);
    *(undefined4 *)(gOFOData + iVar8 + 0x1ebc) = 1;
    *(undefined4 *)(iVar8 + 0x15c) = 10;
    *(undefined4 *)(iVar8 + 0x71900) = 0;
    *(undefined4 *)(&DAT_003a463c + iVar8) = 2;
    iVar9 = *(int *)(iVar5 + 0xe0);
    *(undefined1 *)(iVar8 + 0x2c0) = 1;
  }
  else {
    *(uint *)(iVar5 + 0x194) = uVar7 & 0xffffffdf;
    UnInit();
    iVar5 = *(int *)(iVar9 + DAT_00067ec4);
    iVar8 = **(int **)(iVar9 + iVar8);
    *(undefined4 *)(gOFOData + iVar8 + 0x1ebc) = 0;
    *(undefined4 *)(iVar8 + 0x15c) = 10;
    *(undefined4 *)(iVar8 + 0x71900) = 0;
    *(undefined4 *)(&DAT_003a463c + iVar8) = 2;
    iVar9 = *(int *)(iVar5 + 0xd0);
    *(undefined1 *)(iVar8 + 0x2c0) = 1;
  }
  if (0 < iVar9) {
    *(undefined4 *)(iVar8 + 0x15c) = 0x21;
  }
  return;
}
