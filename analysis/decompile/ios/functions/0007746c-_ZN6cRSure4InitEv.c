/*
 * mangled: _ZN6cRSure4InitEv
 * demangled: cRSure::Init()
 * address: 0007746c
 * size: 656
 */

/* cRSure::Init() */

void __thiscall cRSure::Init(cRSure *this)

{
  undefined *puVar1;
  int iVar2;
  undefined4 uVar3;
  char *pcVar4;
  undefined4 local_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 local_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;

  puVar1 = PTR__Game_001b60b8;
  cRFade::FadeIn((cRFade *)(*(int *)PTR__Game_001b60b8 + 0x24));
  cRStarManager::Hide((cRStarManager *)(*(int *)puVar1 + 0x4e718));
  cRBorderManager::SetJustifyCentre((cRBorderManager *)(*(int *)puVar1 + 0xd14),20.0);
  iVar2 = *(int *)puVar1;
  if (*(int *)(&DAT_00364944 + iVar2) == 0) {
    uVar3 = cRBorderManager::GetBorder((cRBorderManager *)(iVar2 + 0xd14));
    *(undefined4 *)this = uVar3;
    tColour::tColour((tColour *)&local_30,1.0,1.0,1.0,1.0);
    pcVar4 =
    "Are you sure you>want to start a>new adventure?>You will lose your>current high score.";
  }
  else {
    uVar3 = cRBorderManager::GetBorder((cRBorderManager *)(iVar2 + 0xd14));
    *(undefined4 *)this = uVar3;
    tColour::tColour((tColour *)&local_40,1.0,1.0,1.0,1.0);
    pcVar4 =
    "Are you sure you>want to start a>new challenge?>You will lose your>current high score.";
    local_30 = local_40;
    uStack_2c = uStack_3c;
    uStack_28 = uStack_38;
    uStack_24 = uStack_34;
  }
  cRBorder::Init(uVar3,0,pcVar4,0x14,0x41a00000,0x42e40000,local_30,uStack_2c,uStack_28,uStack_24,2,
                 0);
  *(undefined4 *)(*(int *)this + 0x264) = 0x42700000;
  uVar3 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
  *(undefined4 *)(this + 4) = uVar3;
  tColour::tColour((tColour *)&local_50,1.0,1.0,1.0,1.0);
  cRBorder::Init(uVar3,0x40000014,"Yes",0x14,0x41a00000,0x41a00000,local_50,uStack_4c,uStack_48,
                 uStack_44,2,0);
  *(undefined4 *)(*(int *)(this + 4) + 0x264) = 0x42700000;
  cRBorder::SetBelow(*(cRBorder **)(this + 4),*(cRBorder **)this);
  uVar3 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
  *(undefined4 *)(this + 8) = uVar3;
  tColour::tColour((tColour *)&local_60,1.0,1.0,1.0,1.0);
  cRBorder::Init(uVar3,0x14,"No",0x14,0x41a00000,0x43240000,local_60,uStack_5c,uStack_58,uStack_54,2
                 ,0);
  *(undefined4 *)(*(int *)(this + 8) + 0x264) = 0x42700000;
  cRBorder::SetRight(*(cRBorder **)(this + 8),*(cRBorder **)(this + 4));
  cRBorderManager::CentreRow
            ((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14),*(cRBorder **)(this + 8),false,
             20.0);
  return;
}
