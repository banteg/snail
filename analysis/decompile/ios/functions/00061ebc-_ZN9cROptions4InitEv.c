/*
 * mangled: _ZN9cROptions4InitEv
 * demangled: cROptions::Init()
 * address: 00061ebc
 * size: 1020
 */

/* cROptions::Init() */

void __thiscall cROptions::Init(cROptions *this)

{
  undefined *puVar1;
  undefined4 uVar2;
  int iVar3;
  size_t sVar4;
  undefined4 local_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 local_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
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

  *(undefined1 *)(*(int *)PTR__Game_001b60b8 + 0x324) = 1;
  uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
  *(undefined4 *)(this + 0x14) = uVar2;
  tColour::tColour((tColour *)&local_30,1.0,1.0,1.0,1.0);
  cRBorder::Init(uVar2,0x14,"",0x14,0x42b40000,0x42be0000,local_30,uStack_2c,uStack_28,uStack_24,2,0
                );
  *(float *)(*(int *)(this + 0x14) + 0x6f0) = *(float *)(*(int *)(this + 0x14) + 0x6f0) + 8.0;
  uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
  *(undefined4 *)(this + 0x18) = uVar2;
  tColour::tColour((tColour *)&local_40,1.0,1.0,1.0,1.0);
  cRBorder::Init(uVar2,0x900004,"Sounds Volume",0x14,0x42b40000,0x43c80000,local_40,uStack_3c,
                 uStack_38,uStack_34,2,0);
  cRBorder::SetBelow(*(cRBorder **)(this + 0x18),*(cRBorder **)(this + 0x14));
  puVar1 = PTR__gConfig_001b60d4;
  *(undefined4 *)(*(int *)(this + 0x18) + 0x170) = *(undefined4 *)PTR__gConfig_001b60d4;
  *(undefined4 *)(*(int *)(this + 0x18) + 0x174) = *(undefined4 *)puVar1;
  (**(code **)**(undefined4 **)(this + 0x18))();
  uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
  *(undefined4 *)(this + 0x1c) = uVar2;
  tColour::tColour((tColour *)&local_50,1.0,1.0,1.0,1.0);
  cRBorder::Init(uVar2,0x100004,"Music Volume",0x14,0x42b40000,0x43c80000,local_50,uStack_4c,
                 uStack_48,uStack_44,2,0);
  cRBorder::SetBelow(*(cRBorder **)(this + 0x1c),*(cRBorder **)(this + 0x18));
  *(undefined4 *)(*(int *)(this + 0x1c) + 0x170) = *(undefined4 *)(puVar1 + 4);
  *(undefined4 *)(*(int *)(this + 0x1c) + 0x174) = *(undefined4 *)(puVar1 + 4);
  (**(code **)**(undefined4 **)(this + 0x1c))();
  uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
  *(undefined4 *)(this + 0x10) = uVar2;
  tColour::tColour((tColour *)&local_60,1.0,1.0,1.0,1.0);
  cRBorder::Init(uVar2,0x14,"Back",0x14,0x42b40000,0x43c80000,local_60,uStack_5c,uStack_58,uStack_54
                 ,2,0);
  cRBorder::SetBelow(*(cRBorder **)(this + 0x10),*(cRBorder **)(this + 0x1c));
  *(undefined4 *)(this + 0x24) = *(undefined4 *)puVar1;
  uVar2 = cRBorderManager::GetBorder((cRBorderManager *)(*(int *)PTR__Game_001b60b8 + 0xd14));
  *(undefined4 *)(this + 0x20) = uVar2;
  iVar3 = Rstrcmp("Fluctuosa",puVar1 + 0x60);
  if (iVar3 == 0) {
    uVar2 = *(undefined4 *)(this + 0x20);
    tColour::tColour((tColour *)&local_80,0.5,0.0,0.0,0.25);
    cRBorder::Init(uVar2,0x20400000,"V1.3.0.02",0x14,0x44128000,0x43e80000,local_80,uStack_7c,
                   uStack_78,uStack_74,0,0);
    iVar3 = *(int *)(this + 0x20);
    sVar4 = _strlen((char *)(iVar3 + 0x2c4));
    *(undefined1 *)(iVar3 + sVar4 + 0x2c2) = 0;
  }
  else {
    uVar2 = *(undefined4 *)(this + 0x20);
    tColour::tColour((tColour *)&local_70,0.5,0.0,0.0,0.25);
    cRBorder::Init(uVar2,0x20400000,"V1.3.0.02",0x14,0x440d8000,0x43e80000,local_70,uStack_6c,
                   uStack_68,uStack_64,0,0);
  }
  tColour::Set((tColour *)(*(int *)(this + 0x20) + 0x1e0),0.5,0.5,0.5,0.36);
  *(undefined1 *)(*(int *)(this + 0x20) + 0x228) = 1;
  *(undefined4 *)(*(int *)(this + 0x20) + 0x6e8) = 0x3f19999a;
  return;
}
