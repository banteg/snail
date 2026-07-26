/*
 * mangled: _ZN5cGlow2AIEv
 * demangled: cGlow::AI()
 * address: 0004b668
 * size: 744
 */

/* cGlow::AI() */

void __thiscall cGlow::AI(cGlow *this)

{
  float fVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  float extraout_s0;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  tColour local_70 [16];
  undefined4 local_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;

  fVar1 = DAT_0004b950;
  fVar6 = *(float *)(this + 4);
  iVar5 = DAT_0004b968 + 0x4b694;
  *(float *)(this + 4) = fVar6 + *(float *)(this + 8);
  if (fVar1 < fVar6 + *(float *)(this + 8)) {
    *(undefined4 *)this = 0;
  }
  else {
    tColour::tColour((tColour *)&local_60);
    tColour::tColour(local_70);
    uVar4 = DAT_0004b95c;
    uVar3 = DAT_0004b958;
    uVar2 = DAT_0004b954;
    fVar9 = *(float *)(this + 0xc);
    fVar13 = *(float *)(this + 0x14);
    fVar11 = *(float *)(this + 0x18);
    iVar5 = **(int **)(iVar5 + DAT_0004b96c);
    fVar14 = fVar9 + fVar13;
    fVar8 = (*(float *)(this + 0x10) + *(float *)(iVar5 + 0xc08)) - *(float *)(iVar5 + 0xc04);
    tColour::White();
    tColour::Set((tColour *)&local_60,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
    fVar7 = (fVar1 + DAT_0004b960 * *(float *)(this + 4)) * DAT_0004b964;
    fVar12 = fVar9 - fVar7;
    fVar10 = fVar8 - fVar7;
    fVar6 = fVar8 + fVar11;
    OSDPrintUV(0x57,fVar12,fVar10);
    OSDPrintUV(0x57,fVar9,fVar10,fVar13,fVar7,0x1000000,local_60,uStack_5c,uStack_58,uStack_54,uVar3
               ,uVar2,uVar4,uVar3,1,uVar2);
    OSDPrintUV(0x57,fVar14,fVar10,fVar7,fVar7,0x1000000,local_60,uStack_5c,uStack_58,uStack_54,uVar4
               ,uVar2,fVar1,uVar3,1,uVar2);
    OSDPrintUV(0x57,fVar12,fVar8,fVar7,fVar11,0x1000000,local_60,uStack_5c,uStack_58,uStack_54,uVar2
               ,uVar3,uVar3,uVar4,1,uVar2);
    OSDPrintUV(0x57,fVar14,fVar8,fVar7,fVar11,0x1000000,local_60,uStack_5c,uStack_58,uStack_54,uVar4
               ,uVar3,fVar1,uVar4,1,uVar2);
    OSDPrintUV(0x57,fVar12,fVar6,fVar7,fVar7,0x1000000,local_60,uStack_5c,uStack_58,uStack_54,uVar2,
               uVar4,uVar3,fVar1,1,uVar2);
    OSDPrintUV(0x57,fVar9,fVar6,fVar13,fVar7,0x1000000,local_60,uStack_5c,uStack_58,uStack_54,uVar3,
               uVar4,uVar4,fVar1,1,uVar2);
    OSDPrintUV(0x57,fVar14,fVar6,fVar7,fVar7,0x1000000,local_60,uStack_5c,uStack_58,uStack_54,uVar4,
               uVar4,fVar1,fVar1,1,uVar2);
  }
  return;
}
