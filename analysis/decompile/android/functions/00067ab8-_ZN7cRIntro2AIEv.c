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
  int iVar3;
  undefined4 uVar4;
  cRTutorial *this_00;
  uint uVar5;
  int iVar6;
  uint in_fpscr;
  uint uVar7;
  float fVar8;

  uVar7 = in_fpscr & 0xfffffff | (uint)(*(float *)(Game + 0x3c) == *(float *)(Game + 0x44)) << 0x1e;
  if (!SUB41(uVar7 >> 0x1e,0)) {
    UnInit();
    Init(this);
  }
  iVar3 = RShellInkey();
  if ((iVar3 == 0) && ((*(uint *)(*(int *)(Game + 0x224) + 0x30) & 0x4000) == 0)) {
    iVar3 = *(int *)(this + 0x30);
    uVar5 = *(uint *)(iVar3 + 0x194);
  }
  else {
    *(undefined4 *)(this + 0x10) = 0;
    if (this[4] != (cRIntro)0x0) {
      cRBorder::UnHideInit(*(cRBorder **)(this + 0x30));
      cRBorder::UnHideInit(*(cRBorder **)(this + 0x34));
      cRBorder::UnHideInit(*(cRBorder **)(this + 0x40));
      cRBorder::UnHideInit(*(cRBorder **)(this + 0x38));
      cRBorder::UnHideInit(*(cRBorder **)(this + 0x3c));
      cRBorder::UnHideInit(*(cRBorder **)(this + 0x44));
      cRBorder::UnHideInit(*(cRBorder **)(this + 0x48));
      cRMouse::SetActive((cRMouse *)(Game + 0x228));
      this[4] = (cRIntro)0x0;
    }
    iVar3 = *(int *)(this + 0x30);
    uVar5 = *(uint *)(iVar3 + 0x194);
  }
  if ((uVar5 & 0x20) == 0) {
    uVar5 = *(uint *)(*(int *)(this + 0x34) + 0x194);
    if ((uVar5 & 0x20) == 0) {
      uVar5 = *(uint *)(*(int *)(this + 0x38) + 0x194);
      if ((uVar5 & 0x20) != 0) {
        *(uint *)(*(int *)(this + 0x38) + 0x194) = uVar5 & 0xffffffdf;
        *(undefined4 *)(gOFOData + Game + 0x1ebc) = 0;
        UnInit();
        iVar3 = Game;
        *(undefined4 *)(Game + 0x15c) = 10;
        *(undefined4 *)(iVar3 + 0x71900) = 4;
        *(undefined1 *)(iVar3 + 0x2c0) = 1;
        return;
      }
      uVar5 = *(uint *)(*(int *)(this + 0x40) + 0x194);
      if ((uVar5 & 0x20) != 0) {
        *(uint *)(*(int *)(this + 0x40) + 0x194) = uVar5 & 0xffffffdf;
        *(undefined4 *)(gOFOData + Game + 0x1ebc) = 0;
        UnInit();
        iVar3 = Game;
        this_00 = (cRTutorial *)(Game + 0x71924);
        *(undefined1 *)(Game + 0x2c0) = 1;
        *(undefined4 *)(iVar3 + 0x15c) = 10;
        *(undefined4 *)(iVar3 + 0x71900) = 7;
        cRTutorial::Init(this_00);
        gConfig[0xc0] = 1;
        return;
      }
      uVar5 = *(uint *)(*(int *)(this + 0x3c) + 0x194);
      if ((uVar5 & 0x20) != 0) {
        *(uint *)(*(int *)(this + 0x3c) + 0x194) = uVar5 & 0xffffffdf;
        *(undefined4 *)(gOFOData + Game + 0x1ebc) = 0;
        UnInit();
        iVar3 = Game;
        *(undefined1 *)(Game + 0x2c0) = 1;
        *(undefined4 *)(iVar3 + 0x15c) = 10;
        *(undefined4 *)(iVar3 + 0x71900) = 1;
        return;
      }
      uVar5 = *(uint *)(*(int *)(this + 0x48) + 0x194);
      if ((uVar5 & 0x20) == 0) {
        uVar5 = *(uint *)(*(int *)(this + 0x44) + 0x194);
        if ((uVar5 & 0x20) != 0) {
          *(uint *)(*(int *)(this + 0x44) + 0x194) = uVar5 & 0xffffffdf;
          UnInit();
          iVar3 = Game;
          *(undefined1 *)(Game + 0x2c0) = 1;
          *(undefined4 *)(iVar3 + 0x15c) = 0x1f;
        }
      }
      else {
        *(uint *)(*(int *)(this + 0x48) + 0x194) = uVar5 & 0xffffffdf;
        UnInit();
        iVar3 = Game;
        *(undefined1 *)(Game + 0x2c0) = 1;
        *(undefined4 *)(iVar3 + 0x15c) = 4;
      }
      fVar8 = *(float *)(this + 0x10) + *(float *)(this + 0x14);
      uVar7 = uVar7 & 0xfffffff | (uint)(fVar8 < 1.0) << 0x1f | (uint)(fVar8 == 1.0) << 0x1e;
      uVar5 = uVar7 | (uint)NAN(fVar8) << 0x1c;
      *(float *)(this + 0x10) = fVar8;
      bVar1 = (byte)(uVar7 >> 0x18);
      if ((bool)(bVar1 >> 6 & 1) || bVar1 >> 7 != ((byte)(uVar5 >> 0x1c) & 1)) {
        return;
      }
      iVar3 = 0;
      *(undefined4 *)(this + 0x10) = 0;
      do {
        iVar6 = *(int *)this;
        iVar3 = iVar3 + 1;
        if (iVar6 == 1) {
          uVar4 = gRMathRand2();
          fVar8 = (float)VectorSignedToFloat(uVar4,(byte)(uVar5 >> 0x16) & 3);
          iVar6 = (int)(fVar8 * 3.0517578e-05 * 4.0) + 0xb;
          if (*(int *)(gGroup0 + Game + iVar6 * 0x38 + 0xce69c) == 1) {
            cRSubHighScore::MiniLoad((cRSubHighScore *)(gGroup0 + Game + 0xce694),iVar6);
            *(undefined4 *)(Game + 0x71900) = 1;
            iVar6 = *(int *)this;
            bVar2 = true;
          }
          else {
LAB_00067c30:
            iVar6 = *(int *)this;
LAB_00067c34:
            bVar2 = false;
          }
        }
        else if (iVar6 == 3) {
          uVar4 = gRMathRand2();
          fVar8 = (float)VectorSignedToFloat(uVar4,(byte)(uVar5 >> 0x16) & 3);
          iVar6 = (int)(fVar8 * 3.0517578e-05 * 51.0) + 0x16;
          if (*(int *)(gGroup0 + Game + iVar6 * 0x38 + 0xce69c) != 1) goto LAB_00067c30;
          cRSubHighScore::MiniLoad((cRSubHighScore *)(gGroup0 + Game + 0xce694),iVar6);
          *(undefined4 *)(Game + 0x71900) = 4;
          iVar6 = *(int *)this;
          bVar2 = true;
        }
        else {
          if (iVar6 != 0) goto LAB_00067c34;
          uVar4 = gRMathRand2();
          fVar8 = (float)VectorSignedToFloat(uVar4,(byte)(uVar5 >> 0x16) & 3);
          iVar6 = (int)(fVar8 * 3.0517578e-05 * 4.0);
          if (*(int *)(gGroup0 + Game + iVar6 * 0x38 + 0xce69c) != 1) goto LAB_00067c30;
          cRSubHighScore::MiniLoad((cRSubHighScore *)(gGroup0 + Game + 0xce694),iVar6);
          *(undefined4 *)(Game + 0x71900) = 0;
          iVar6 = *(int *)this;
          bVar2 = true;
        }
        iVar6 = iVar6 + 1;
        if (iVar6 == 5) {
          iVar6 = 0;
        }
        *(int *)this = iVar6;
        iVar6 = Game;
        if (bVar2) {
          if (iVar3 < 1000) {
            this[4] = (cRIntro)0x1;
            *(undefined4 *)(iVar6 + 0x15c) = 10;
            *(undefined4 *)(this + 8) = 0;
            *(undefined1 *)(iVar6 + 0x2c0) = 1;
            *(undefined4 *)(gDirectory + iVar6 + 0x254c) = 2;
            *(undefined4 *)(this + 0xc) = 0x3991a2b4;
            gDirectory[iVar6 + 0x2545] = 1;
            gDirectory[iVar6 + 0x2544] = 1;
            UnInit();
            return;
          }
          goto LAB_00067ed8;
        }
        if (iVar3 == 1000) {
LAB_00067ed8:
          *(undefined4 *)(this + 8) = 0;
          *(undefined4 *)(this + 0xc) = 0x3991a2b4;
          return;
        }
      } while( true );
    }
    *(uint *)(*(int *)(this + 0x34) + 0x194) = uVar5 & 0xffffffdf;
    UnInit();
    iVar3 = Game;
    *(undefined4 *)(gOFOData + Game + 0x1ebc) = 1;
    *(undefined4 *)(iVar3 + 0x15c) = 10;
    *(undefined4 *)(iVar3 + 0x71900) = 0;
    *(undefined4 *)(&DAT_003a463c + iVar3) = 2;
    iVar6 = gConfig._224_4_;
    *(undefined1 *)(iVar3 + 0x2c0) = 1;
  }
  else {
    *(uint *)(iVar3 + 0x194) = uVar5 & 0xffffffdf;
    UnInit();
    iVar3 = Game;
    *(undefined4 *)(gOFOData + Game + 0x1ebc) = 0;
    *(undefined4 *)(iVar3 + 0x15c) = 10;
    *(undefined4 *)(iVar3 + 0x71900) = 0;
    *(undefined4 *)(&DAT_003a463c + iVar3) = 2;
    iVar6 = gConfig._208_4_;
    *(undefined1 *)(iVar3 + 0x2c0) = 1;
  }
  if (0 < iVar6) {
    *(undefined4 *)(iVar3 + 0x15c) = 0x21;
  }
  return;
}
