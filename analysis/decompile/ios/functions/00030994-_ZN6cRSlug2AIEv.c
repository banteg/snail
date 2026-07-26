/*
 * mangled: _ZN6cRSlug2AIEv
 * demangled: cRSlug::AI()
 * address: 00030994
 * size: 1644
 */

/* cRSlug::AI() */

void __thiscall cRSlug::AI(cRSlug *this)

{
  byte bVar1;
  undefined *puVar2;
  float fVar3;
  cRSprite *this_00;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  bool bVar8;
  uint in_fpscr;
  uint uVar9;
  uint uVar10;
  float fVar11;
  float fVar12;

  if (*(char *)(*(int *)(this + 0x7c) + 0x12) != '\0') {
    return;
  }
  switch(*(undefined4 *)(this + 0x74)) {
  case 0:
    goto switchD_000309c0_caseD_0;
  case 1:
    if ((this[0xc0] != (cRSlug)0x0) && (*PTR__G0RenderNextFlag_001b60f4 != '\0')) {
      *(undefined4 *)(this + 0xc4) = *(undefined4 *)(this + 200);
      this[0xc0] = (cRSlug)0x0;
    }
    if (*(float *)(this + 0xc4) == 0.0) {
      fVar11 = *(float *)(this + 0xdc);
      uVar9 = in_fpscr & 0xfffffff | (uint)(fVar11 < 0.0) << 0x1f | (uint)(fVar11 == 0.0) << 0x1e;
      uVar10 = uVar9 | (uint)NAN(fVar11) << 0x1c;
      bVar1 = (byte)(uVar9 >> 0x18);
      if ((bool)(bVar1 >> 6 & 1) || bVar1 >> 7 != ((byte)(uVar10 >> 0x1c) & 1)) {
        this_00 = *(cRSprite **)(this + 0xa0);
        iVar4 = 0x6b;
      }
      else {
        this_00 = *(cRSprite **)(this + 0xa0);
        iVar4 = 0x6a;
      }
      *(float *)(this + 0xd8) = *(float *)(this + 0xd8) + fVar11;
      cRSprite::SetTextureRef(this_00,iVar4,0);
      *(undefined4 *)(*(int *)(this + 0xa0) + 0x28) = 1;
      tColour::Set((tColour *)(*(int *)(this + 0xa0) + 0x2c),1.0,1.0,1.0,1.0);
      fVar11 = *(float *)(this + 0xd8);
      uVar9 = uVar10 & 0xfffffff | (uint)(fVar11 < 0.0) << 0x1f;
      if (SUB41(uVar9 >> 0x1f,0)) {
        *(undefined4 *)(this + 0xd8) = 0;
        iVar7 = *(int *)PTR__Game_001b60b8;
        iVar4 = (*(int *)((int)&DAT_00081f5c + iVar7) + 1) % 0x18;
        *(int *)((int)&DAT_00081f5c + iVar7) = iVar4;
        *(undefined4 *)(this + 0xdc) =
             *(undefined4 *)(OFChatRoomInstanceService::setLastRoom_ + iVar4 * 4 + iVar7);
      }
      else {
        uVar10 = uVar10 & 0xfffffff | (uint)(fVar11 < 1.0) << 0x1f | (uint)(fVar11 == 1.0) << 0x1e;
        uVar9 = uVar10 | (uint)NAN(fVar11) << 0x1c;
        bVar1 = (byte)(uVar10 >> 0x18);
        if (!(bool)(bVar1 >> 6 & 1) && bVar1 >> 7 == ((byte)(uVar9 >> 0x1c) & 1)) {
          *(undefined4 *)(this + 0xd8) = 0x3f800000;
          *(undefined4 *)(this + 0xdc) = 0xbe2aaaab;
        }
      }
    }
    else {
      fVar3 = 1.0;
      fVar11 = *(float *)(this + 0xc4) + *(float *)(this + 200);
      uVar10 = in_fpscr & 0xfffffff | (uint)(fVar11 < 1.0) << 0x1f | (uint)(fVar11 == 1.0) << 0x1e;
      uVar9 = uVar10 | (uint)NAN(fVar11) << 0x1c;
      *(float *)(this + 0xc4) = fVar11;
      bVar1 = (byte)(uVar10 >> 0x18);
      if ((bool)(bVar1 >> 6 & 1) || bVar1 >> 7 != ((byte)(uVar9 >> 0x1c) & 1)) {
        *(undefined4 *)(*(int *)(this + 0xa0) + 0x28) = 5;
        cRSprite::SetTextureRef(*(cRSprite **)(this + 0xa0),0x6c,0);
        tColour::Set((tColour *)(*(int *)(this + 0xa0) + 0x2c),fVar3,0.0,0.0,0.99);
      }
      else {
        *(undefined4 *)(this + 0xc4) = 0;
        *(undefined4 *)(this + 0xd8) = 0x3f800000;
        *(undefined4 *)(this + 0xdc) = 0xbe2aaaab;
        *(undefined4 *)(*(int *)(this + 0xa0) + 0x28) = 1;
        tColour::Set((tColour *)(*(int *)(this + 0xa0) + 0x2c),1.0,1.0,1.0,1.0);
        cRSprite::SetTextureRef(*(cRSprite **)(this + 0xa0),0x6b,0);
      }
    }
    iVar4 = *(int *)(this + 0xb4);
    fVar12 = 1.0;
    fVar11 = *(float *)(this + 100);
    fVar3 = *(float *)(iVar4 + 100);
    uVar9 = uVar9 & 0xfffffff | (uint)(fVar11 < fVar3 + 1.0) << 0x1f;
    if ((SUB41(uVar9 >> 0x1f,0)) && (this[0xcd] == (cRSlug)0x0)) {
      this[0xcd] = (cRSlug)0x1;
      uVar5 = gRMathRand2();
      fVar3 = 3.0517578e-05;
      fVar11 = (float)VectorSignedToFloat(uVar5,(byte)(uVar9 >> 0x16) & 3);
      fVar11 = fVar11 * 3.0517578e-05;
      uVar9 = uVar9 & 0xfffffff | (uint)(fVar11 < 0.6) << 0x1f | (uint)(fVar11 == 0.6) << 0x1e;
      uVar10 = uVar9 | (uint)NAN(fVar11) << 0x1c;
      bVar1 = (byte)(uVar9 >> 0x18);
      if ((!(bool)(bVar1 >> 6 & 1) && bVar1 >> 7 == ((byte)(uVar10 >> 0x1c) & 1)) &&
         ((uVar5 = gRMathRand2(), puVar2 = PTR__Game_001b60b8, this[0xcc] == (cRSlug)0x0 &&
          (iVar4 = *(int *)PTR__Game_001b60b8, *(char *)(iVar4 + 0x7b14c) == '\0')))) {
        fVar11 = (float)VectorSignedToFloat(uVar5,(byte)(uVar10 >> 0x16) & 3);
        *(undefined4 *)(iVar4 + 0x7b150) = *(undefined4 *)((int)&DAT_0007b154 + iVar4);
        *(undefined1 *)(*(int *)puVar2 + 0x7b14c) = 1;
        this[0xcc] = (cRSlug)0x1;
        *(undefined4 *)(this + 0xd0) = 0;
        RShellVoicePlay((int)(fVar11 * fVar3 * 4.0) + 0x1e,fVar12,-1.0,0.0);
      }
      iVar4 = *(int *)(this + 0xb4);
      fVar11 = *(float *)(this + 100);
      fVar3 = *(float *)(iVar4 + 100);
    }
    if ((fVar11 < fVar3) && (this[0xa8] == (cRSlug)0x0)) {
      this[0xa8] = (cRSlug)0x1;
    }
    if ((*(int *)(this + 0xb8) == 1) && (fVar11 < *(float *)(iVar4 + 100) + 16.0)) {
      *(undefined4 *)(this + 0xb8) = 0;
      cRVoiceManager::Play((cRVoiceManager *)PTR__gVoiceManager_001b61d8,2,1,-1);
    }
    iVar4 = *(int *)(this + 0xa0);
    uVar5 = *(undefined4 *)(this + 0x60);
    uVar6 = *(undefined4 *)(this + 100);
    *(undefined4 *)(iVar4 + 0x48) = *(undefined4 *)(this + 0x5c);
    *(undefined4 *)(iVar4 + 0x4c) = uVar5;
    *(undefined4 *)(iVar4 + 0x50) = uVar6;
    if (*(float *)(this + 100) < *(float *)(&DAT_000027f4 + *(int *)(this + 0xb4))) {
      *(undefined4 *)(this + 0x74) = 0;
      goto LAB_00030b3c;
    }
    if (0.0 < *(float *)(*(int *)(this + 0xb4) + 0x364)) {
      Kill(this);
    }
    cREnemyManager::Register
              ((cREnemyManager *)(&DAT_00303ab4 + *(int *)(this + 0x7c)),(tVector *)(this + 0x5c),
               2.0,1,(cRBodPos *)this);
    iVar4 = *(int *)(this + 0xb4);
    break;
  case 2:
    fVar12 = 0.1;
    *(undefined4 *)(this + 0x74) = 3;
    fVar11 = (float)SRAND(0.1,"SDI");
    fVar3 = (float)RAND(0.2,(char *)0x0);
    uVar5 = RAND(0.3,(char *)0x0);
    *(float *)(this + 0x80) = fVar11;
    bVar8 = *(int *)(this + 0x78) == 1;
    if (bVar8) {
      fVar11 = ABS(fVar11);
    }
    *(float *)(this + 0x84) = fVar3 + fVar12;
    if (bVar8) {
      *(float *)(this + 0x80) = fVar11;
    }
    *(undefined4 *)(this + 0x88) = uVar5;
    if ((!bVar8) && (*(int *)(this + 0x78) == 2)) {
      *(float *)(this + 0x80) = -ABS(fVar11);
    }
    fVar11 = *(float *)(this + 0x80);
    if (fVar11 < 0.0) {
      fVar3 = -0.2;
    }
    else if (fVar11 == 0.0) {
      fVar3 = 0.0;
    }
    else {
      fVar3 = 0.2;
    }
    *(undefined4 *)(this + 0x90) = 0;
    *(float *)(this + 0x80) = fVar3 + fVar11;
    fVar11 = *(float *)(*(int *)(this + 0x7c) + 0x4c);
    *(undefined4 *)(this + 0x98) = 0;
    *(float *)(this + 0x94) = fVar11 * 0.008333334;
    *(float *)(this + 0x9c) = *(float *)(*(int *)(this + 0x7c) + 0x4c) * 0.16666667;
  case 3:
    *(undefined4 *)(this + 0x74) = 0;
LAB_00030b3c:
    iVar4 = *(int *)PTR__Game_001b60b8;
    if ((*(uint *)(this + 4) & 0x200) == 0) {
      RShellError("List remove");
    }
    else if ((*(uint *)(this + 4) & 0x40) == 0) {
      iVar7 = *(int *)(this + 0xc);
      if (iVar7 != 0) {
        *(undefined4 *)(iVar7 + 8) = *(undefined4 *)(this + 8);
      }
      if (*(int *)(this + 8) == 0) {
        *(int *)(iVar4 + 0x35c) = iVar7;
      }
      else {
        *(int *)(*(int *)(this + 8) + 0xc) = iVar7;
      }
      *(undefined4 *)(this + 0xc) = *(undefined4 *)(iVar4 + 0x360);
      *(cRSlug **)(iVar4 + 0x360) = this;
      *(uint *)(this + 4) = *(uint *)(this + 4) & 0xfffffdff;
    }
    else {
      RShellError("List remove NEXTBOD");
    }
    cRSprite::Kill(*(cRSprite **)(this + 0xa0));
    return;
  case 4:
    fVar11 = *(float *)(this + 0xac) + *(float *)(this + 0xb0);
    *(float *)(this + 0xac) = fVar11;
    if (6.2831855 < fVar11) {
      fVar11 = fVar11 - 6.2831855;
      *(float *)(this + 0xac) = fVar11;
    }
    fVar11 = (float)Sin(fVar11);
    *(float *)(this + 0x5c) = fVar11 * 3.0;
    if ((*(float *)(this + 100) < *(float *)(*(int *)(this + 0xb4) + 100)) &&
       (this[0xa8] == (cRSlug)0x0)) {
      this[0xa8] = (cRSlug)0x1;
    }
    iVar4 = *(int *)(this + 0xa0);
    uVar5 = *(undefined4 *)(this + 0x60);
    uVar6 = *(undefined4 *)(this + 100);
    *(undefined4 *)(iVar4 + 0x48) = *(undefined4 *)(this + 0x5c);
    *(undefined4 *)(iVar4 + 0x4c) = uVar5;
    *(undefined4 *)(iVar4 + 0x50) = uVar6;
    iVar4 = *(int *)(this + 0xb4);
    if (*(float *)(this + 100) < *(float *)(&DAT_000027f4 + iVar4)) {
      *(undefined4 *)(this + 0x74) = 0;
      goto LAB_00030b3c;
    }
    if (0.0 < *(float *)(iVar4 + 0x364)) {
      Kill(this);
      iVar4 = *(int *)(this + 0xb4);
    }
    break;
  default:
    iVar4 = *(int *)(this + 0xb4);
  }
  *(float *)(*(int *)(this + 0xa0) + 0x7c) =
       *(float *)(iVar4 + 0x360) + *(float *)(this + 0x8c) + *(float *)(iVar4 + 0x34c);
  iVar4 = *(int *)(this + 0xb4);
  if (*(char *)(iVar4 + 0x374) != '\0') {
    *(float *)(*(int *)(this + 0xa0) + 0x7c) =
         *(float *)(*(int *)(this + 0xa0) + 0x7c) +
         *(float *)(iVar4 + 0x390) + *(float *)(iVar4 + 0x38c);
  }
  if ((this[0xcc] != (cRSlug)0x0) &&
     (fVar11 = *(float *)(this + 0xd0), *(float *)(this + 0xd0) = fVar11 + *(float *)(this + 0xd4),
     1.0 < fVar11 + *(float *)(this + 0xd4))) {
    *(undefined4 *)(this + 0xd0) = 0;
    this[0xcc] = (cRSlug)0x0;
  }
switchD_000309c0_caseD_0:
  return;
}
