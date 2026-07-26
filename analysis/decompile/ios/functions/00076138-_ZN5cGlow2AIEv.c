/*
 * mangled: _ZN5cGlow2AIEv
 * demangled: cGlow::AI()
 * address: 00076138
 * size: 784
 */

/* cGlow::AI() */

void __thiscall cGlow::AI(cGlow *this)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float local_68;
  float local_64;
  float local_60;
  undefined4 local_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;

  fVar1 = *(float *)(this + 4);
  fVar2 = 1.0;
  *(float *)(this + 4) = fVar1 + *(float *)(this + 8);
  if (1.0 < fVar1 + *(float *)(this + 8)) {
    *(undefined4 *)this = 0;
  }
  else {
    tColour::tColour((tColour *)&local_58);
    tColour::tColour((tColour *)&local_68);
    fVar4 = *(float *)(this + 0xc);
    fVar6 = *(float *)(this + 0x14);
    fVar5 = *(float *)(this + 0x18);
    fVar8 = fVar4 + fVar6;
    fVar3 = (*(float *)(this + 0x10) + *(float *)(*(int *)PTR__Game_001b60b8 + 0xc08)) -
            *(float *)(*(int *)PTR__Game_001b60b8 + 0xc04);
    tColour::White((tColour *)&local_68);
    tColour::Set((tColour *)&local_58,local_68,local_64,local_60,fVar2 - *(float *)(this + 4));
    fVar1 = (fVar2 + *(float *)(this + 4) * 0.7) * 8.0;
    fVar7 = fVar3 - fVar1;
    fVar9 = fVar4 - fVar1;
    OSDPrintUV(0x57,fVar9,fVar7,fVar1,fVar1,0x1000000,local_58,uStack_54,uStack_50,uStack_4c,0,0,
               0x3dcccccd,0x3dcccccd,1,0);
    OSDPrintUV(0x57,fVar4,fVar7,fVar6,fVar1,0x1000000,local_58,uStack_54,uStack_50,uStack_4c,
               0x3dcccccd,0,0x3f666666,0x3dcccccd,1,0);
    OSDPrintUV(0x57,fVar8,fVar7,fVar1,fVar1,0x1000000,local_58,uStack_54,uStack_50,uStack_4c,
               0x3f666666,0,fVar2,0x3dcccccd,1,0);
    fVar7 = fVar3 + fVar5;
    OSDPrintUV(0x57,fVar9,fVar3,fVar1,fVar5,0x1000000,local_58,uStack_54,uStack_50,uStack_4c,0,
               0x3dcccccd,0x3dcccccd,0x3f666666,1,0);
    OSDPrintUV(0x57,fVar8,fVar3,fVar1,fVar5,0x1000000,local_58,uStack_54,uStack_50,uStack_4c,
               0x3f666666,0x3dcccccd,fVar2,0x3f666666,1,0);
    OSDPrintUV(0x57,fVar9,fVar7,fVar1,fVar1,0x1000000,local_58,uStack_54,uStack_50,uStack_4c,0,
               0x3f666666,0x3dcccccd,fVar2,1,0);
    OSDPrintUV(0x57,fVar4,fVar7,fVar6,fVar1,0x1000000,local_58,uStack_54,uStack_50,uStack_4c,
               0x3dcccccd,0x3f666666,0x3f666666,fVar2,1,0);
    OSDPrintUV(0x57,fVar8,fVar7,fVar1,fVar1,0x1000000,local_58,uStack_54,uStack_50,uStack_4c,
               0x3f666666,0x3f666666,fVar2,fVar2,1,0);
  }
  return;
}
