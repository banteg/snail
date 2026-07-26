/*
 * mangled: _ZN5cRGUI4InitEv
 * demangled: cRGUI::Init()
 * address: 00064208
 * size: 952
 */

/* cRGUI::Init() */

void __thiscall cRGUI::Init(cRGUI *this)

{
  undefined *puVar1;
  undefined4 uVar2;
  uint in_fpscr;
  float fVar3;
  float fVar4;
  float fVar5;
  undefined4 local_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 local_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 local_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 local_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;

  puVar1 = PTR__Game_001b60b8;
  cRFade::FadeIn((cRFade *)(*(int *)PTR__Game_001b60b8 + 0x24));
  cRMouse::SetActive((cRMouse *)(*(int *)puVar1 + 0x228));
  if (*(int *)(*(int *)this + 0x58) == 1) {
    fVar4 = 100.0;
    uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)puVar1 + 0xd14));
    fVar5 = 0.0;
    *(undefined4 *)(this + 0x20) = uVar2;
    tColour::tColour((tColour *)&local_38,1.0,1.0,1.0,1.0);
    cRBorder::Init(uVar2,0x100004,"Select Difficulty",0x14,0x41a00000,fVar4,local_38,uStack_34,
                   uStack_30,uStack_2c,2,fVar5);
    fVar3 = (float)VectorSignedToFloat(*(undefined4 *)(PTR__gConfig_001b60d4 + 0x48),
                                       (byte)(in_fpscr >> 0x16) & 3);
    *(float *)(*(int *)(this + 0x20) + 0x170) = fVar3 / fVar4;
    *(undefined4 *)(*(int *)(this + 0x20) + 0x174) = *(undefined4 *)(*(int *)(this + 0x20) + 0x170);
    (**(code **)**(undefined4 **)(this + 0x20))();
    uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)puVar1 + 0xd14));
    *(undefined4 *)(this + 0x1c) = uVar2;
    tColour::tColour((tColour *)&local_48,1.0,1.0,1.0,1.0);
    cRBorder::Init(uVar2,0x100004,"Select Speed",0x14,0x41a00000,0x43110000,local_48,uStack_44,
                   uStack_40,uStack_3c,2,fVar5);
    fVar3 = (float)VectorSignedToFloat(*(undefined4 *)(PTR__gConfig_001b60d4 + 0x40),
                                       (byte)(in_fpscr >> 0x16) & 3);
    *(float *)(*(int *)(this + 0x1c) + 0x170) = fVar3 / fVar4;
    *(undefined4 *)(*(int *)(this + 0x1c) + 0x174) = *(undefined4 *)(*(int *)(this + 0x1c) + 0x170);
    cRBorder::SetBelow(*(cRBorder **)(this + 0x1c),*(cRBorder **)(this + 0x20));
    (**(code **)**(undefined4 **)(this + 0x1c))();
    if (*(int *)(&DAT_002a11a8 + *(int *)this) != 1) {
      fVar4 = fVar5;
    }
    uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)puVar1 + 0xd14));
    *(undefined4 *)(this + 0x10) = uVar2;
    tColour::tColour((tColour *)&local_58,1.0,1.0,1.0,1.0);
    cRBorder::Init(uVar2,0x40000016,"Play",0x14,0x41a00000,0x437a0000,local_58,uStack_54,uStack_50,
                   uStack_4c,2,fVar4);
    cRBorder::SetBelow(*(cRBorder **)(this + 0x10),*(cRBorder **)(this + 0x1c));
    *(undefined4 *)(*(int *)(this + 0x10) + 0x264) = 0x41000000;
    uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)puVar1 + 0xd14));
    *(undefined4 *)(this + 0x24) = uVar2;
    tColour::tColour((tColour *)&local_68,1.0,1.0,1.0,1.0);
    cRBorder::Init(uVar2,0x40000016,"Watch Replay",0x14,0x41a00000,0x428c0000,local_68,uStack_64,
                   uStack_60,uStack_5c,2,0xc2c80000);
    cRBorder::SetBelow(*(cRBorder **)(this + 0x24),*(cRBorder **)(this + 0x1c));
    *(undefined4 *)(*(int *)(this + 0x24) + 0x264) = 0x41000000;
    if (*(int *)(&DAT_002a11a8 + *(int *)this) == 1) {
      cRBorder::SetRight(*(cRBorder **)(this + 0x10),*(cRBorder **)(this + 0x24));
    }
    else {
      cRBorder::HideInit(*(cRBorder **)(this + 0x24));
    }
    puVar1 = PTR__Game_001b60b8;
    cRBorderManager::CentreRow
              ((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14),*(cRBorder **)(this + 0x10),
               false,100.0);
    uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)puVar1 + 0xd14));
    *(undefined4 *)(this + 0x18) = uVar2;
    tColour::tColour((tColour *)&local_78,1.0,1.0,1.0,1.0);
    cRBorder::Init(uVar2,0x16,"Back",0x14,0x41a00000,0x41a00000,local_78,uStack_74,uStack_70,
                   uStack_6c,2,0);
    cRBorder::SetBelow(*(cRBorder **)(this + 0x18),*(cRBorder **)(this + 0x24));
  }
  return;
}
