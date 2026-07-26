/*
 * mangled: _ZN13cRDamageGuage2AIEv
 * demangled: cRDamageGuage::AI()
 * address: 00024904
 * size: 1612
 */

/* cRDamageGuage::AI() */

void __thiscall cRDamageGuage::AI(cRDamageGuage *this)

{
  undefined *puVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  tColour local_70 [16];
  tColour local_60 [16];
  tColour local_50 [48];

  if (*(char *)(*(int *)PTR__Game_001b60b8 + 0x72b8a) == '\0') {
    fVar3 = *(float *)(this + 0x20) + (*(float *)(this + 0x1c) - *(float *)(this + 0x20)) * 0.2;
    *(float *)(this + 0x20) = fVar3;
    if ((0.0 < *(float *)(this + 0x24)) &&
       (fVar4 = *(float *)(this + 0x24) + *(float *)(this + 0x28), *(float *)(this + 0x24) = fVar4,
       1.0 < fVar4)) {
      *(undefined4 *)(this + 0x24) = 0;
    }
    puVar1 = PTR__Game_001b60b8;
    iVar2 = *(int *)this;
    if (iVar2 == 1) {
      if ((&DAT_000823f0)[*(int *)PTR__Game_001b60b8] != '\0') {
        *(undefined4 *)(this + 0x10) = 0x3f800000;
      }
      fVar4 = *(float *)(this + 0x10);
      *(float *)(this + 0x10) = fVar4 + *(float *)(this + 0x14);
      if ((1.0 <= fVar4 + *(float *)(this + 0x14)) && (*(float *)(*(int *)puVar1 + 0x82020) == 0.49)
         ) {
        *(undefined4 *)this = 2;
        cRVoiceManager::Play((cRVoiceManager *)PTR__gVoiceManager_001b61d8,0xe,0,-1);
        fVar3 = *(float *)(this + 0x20);
        iVar2 = *(int *)this;
      }
    }
    else if (iVar2 == 2) {
      iVar2 = *(int *)PTR__Game_001b60b8;
      *(undefined4 *)(iVar2 + 0x85f3c) = 1;
      *(undefined4 *)(iVar2 + 0x85f40) = 0;
      *(undefined4 *)(iVar2 + 0x85f28) = 1;
      *(undefined4 *)(iVar2 + 0x85f44) = 0x3daaaaab;
      Take(this,-0.0016666667,true);
      *(undefined4 *)(this + 0x18) = 5;
      if ((&DAT_000823f0)[*(int *)puVar1] != '\0') {
        Take(this,-0.006666667,false);
      }
      if ((((*(float *)(this + 0x1c) != 0.0) || (*(float *)(*(int *)puVar1 + 0x82020) != 0.49)) &&
          (iVar2 = *(int *)puVar1, *(float *)(&DAT_000823f4 + iVar2) <= 0.0)) &&
         ((*(float *)(iVar2 + 0x82040) <= 0.0 && (*(int *)(iVar2 + 0x85f54) == 0))))
      goto LAB_00024b44;
      *(undefined4 *)this = 0;
      iVar2 = *(int *)PTR__Game_001b60b8;
      *(undefined4 *)(&DAT_000823a4 + iVar2) = 0;
      cRBorder::HideInit(*(cRBorder **)(&DAT_000823b0 + iVar2));
      puVar1 = PTR__gRSound_001b61e0;
      iVar2 = cRSound::PlayLooped((cRSound *)PTR__gRSound_001b61e0,0x33);
      cRSound::StopLooped((cRSound *)puVar1,iVar2);
      fVar3 = *(float *)(this + 0x20);
      iVar2 = *(int *)this;
    }
    else if (((iVar2 == 0) && (*(float *)(this + 0x1c) == 1.0)) &&
            (((&DAT_000823cd)[*(int *)PTR__Game_001b60b8] == '\0' &&
             ((&DAT_000823f0)[*(int *)PTR__Game_001b60b8] == '\0')))) {
      *(undefined4 *)(this + 0x10) = 0;
      *(undefined4 *)this = 1;
      *(undefined4 *)(this + 0x14) = 0x3e2aaaab;
      iVar2 = *(int *)puVar1;
      *(undefined4 *)(&DAT_000823a4 + iVar2) = 2;
      *(undefined4 *)(&DAT_000823a8 + iVar2) = 0x3f800000;
      cRBorder::UnHideInit(*(cRBorder **)(&DAT_000823b0 + iVar2));
      fVar3 = *(float *)(this + 0x20);
      iVar2 = *(int *)this;
    }
  }
  else {
LAB_00024b44:
    fVar3 = *(float *)(this + 0x20);
    iVar2 = *(int *)this;
  }
  if (fVar3 <= 0.999) {
    if (0.01 <= fVar3) {
      fVar4 = fVar3 * -308.0 + 351.0;
      fVar9 = fVar4 + 70.0;
      fVar8 = 396.0 - fVar4;
    }
    else {
      fVar4 = 396.0;
      fVar9 = 466.0;
      fVar8 = 0.0;
    }
  }
  else {
    fVar4 = 0.0;
    fVar9 = 70.0;
    fVar8 = 396.0;
  }
  fVar6 = 1.0;
  if (*(char *)(*(int *)PTR__Game_001b60b8 + 0x72b8a) == '\0') {
    fVar5 = *(float *)(this + 4) + *(float *)(this + 8);
    *(float *)(this + 4) = fVar5;
  }
  else {
    fVar5 = *(float *)(this + 4);
  }
  if (1.0 < fVar5) {
    *(float *)(this + 4) = fVar5 - 1.0;
  }
  if (0.9 < fVar3) {
    if (iVar2 == 0) {
      fVar6 = (fVar3 - 0.9) * 10.0;
      fVar3 = fVar6 * -0.5;
    }
    else {
LAB_00024bdc:
      fVar3 = -0.5;
    }
  }
  else {
    if (iVar2 == 0) goto LAB_00024cc8;
    if (0.1 <= fVar3) goto LAB_00024bdc;
    fVar6 = fVar3 * 10.0;
    fVar3 = fVar6 * -0.5;
  }
  fVar7 = 1.0;
  fVar5 = (float)Sin((*(float *)(this + 4) + *(float *)(this + 4)) * 3.1415927);
  tColour::tColour(local_50,fVar7,fVar7,fVar7,fVar6 + fVar3 * (fVar5 * 0.5 + 0.5));
  OSDPrintUV(0x4d,0x440c0000,0x428c0000,0x42800000,0x43c60000,0x1000000);
LAB_00024cc8:
  fVar3 = 1.0;
  tColour::tColour(local_60,1.0,1.0,1.0,1.0);
  OSDPrintUV(0x4b,0x440c0000,0x428c0000,0x42800000,fVar4,0x1000000);
  tColour::tColour(local_70,fVar3,fVar3,fVar3,fVar3);
  OSDPrintUV(0x4c,0x440c0000,fVar9,0x42800000,fVar8,0x1000000);
  return;
}
