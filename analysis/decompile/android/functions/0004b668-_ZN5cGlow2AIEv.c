/*
 * mangled: _ZN5cGlow2AIEv
 * demangled: cGlow::AI()
 * address: 0004b668
 * size: 744
 */

/* cGlow::AI() */

void __thiscall cGlow::AI(cGlow *this)

{
  float extraout_s0;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  tColour local_70 [16];
  undefined4 local_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;

  fVar1 = *(float *)(this + 4);
  *(float *)(this + 4) = fVar1 + *(float *)(this + 8);
  if (1.0 < fVar1 + *(float *)(this + 8)) {
    *(undefined4 *)this = 0;
  }
  else {
    tColour::tColour((tColour *)&local_60);
    tColour::tColour(local_70);
    fVar4 = *(float *)(this + 0xc);
    fVar8 = *(float *)(this + 0x14);
    fVar6 = *(float *)(this + 0x18);
    fVar9 = fVar4 + fVar8;
    fVar3 = (*(float *)(this + 0x10) + *(float *)(Game + 0xc08)) - *(float *)(Game + 0xc04);
    tColour::White();
    tColour::Set((tColour *)&local_60,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
    fVar2 = (*(float *)(this + 4) * 0.7 + 1.0) * 8.0;
    fVar7 = fVar4 - fVar2;
    fVar5 = fVar3 - fVar2;
    fVar1 = fVar3 + fVar6;
    OSDPrintUV(0x57,fVar7,fVar5);
    OSDPrintUV(0x57,fVar4,fVar5,fVar8,fVar2,0x1000000,local_60,uStack_5c,uStack_58,uStack_54,
               0x3dcccccd,0,0x3f666666,0x3dcccccd,1,0);
    OSDPrintUV(0x57,fVar9,fVar5,fVar2,fVar2,0x1000000,local_60,uStack_5c,uStack_58,uStack_54,
               0x3f666666,0,0x3f800000,0x3dcccccd,1,0);
    OSDPrintUV(0x57,fVar7,fVar3,fVar2,fVar6,0x1000000,local_60,uStack_5c,uStack_58,uStack_54,0,
               0x3dcccccd,0x3dcccccd,0x3f666666,1,0);
    OSDPrintUV(0x57,fVar9,fVar3,fVar2,fVar6,0x1000000,local_60,uStack_5c,uStack_58,uStack_54,
               0x3f666666,0x3dcccccd,0x3f800000,0x3f666666,1,0);
    OSDPrintUV(0x57,fVar7,fVar1,fVar2,fVar2,0x1000000,local_60,uStack_5c,uStack_58,uStack_54,0,
               0x3f666666,0x3dcccccd,0x3f800000,1,0);
    OSDPrintUV(0x57,fVar4,fVar1,fVar8,fVar2,0x1000000,local_60,uStack_5c,uStack_58,uStack_54,
               0x3dcccccd,0x3f666666,0x3f666666,0x3f800000,1,0);
    OSDPrintUV(0x57,fVar9,fVar1,fVar2,fVar2,0x1000000,local_60,uStack_5c,uStack_58,uStack_54,
               0x3f666666,0x3f666666,0x3f800000,0x3f800000,1,0);
  }
  return;
}
